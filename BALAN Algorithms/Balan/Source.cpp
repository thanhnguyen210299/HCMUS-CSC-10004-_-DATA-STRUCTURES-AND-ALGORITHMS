#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Header.h"
#include <math.h>

using namespace std;

void checkString(string &s)
{
	int i = 0;
	bool kt = false;
	while (i < s.length())
	{
		if (s[i] == '-' && '0' <= s[i + 1] && s[i + 1] <= '9')
		{
			i++;
			continue;
		}
		if (s[i] == '-')
		{
			if (i < 2)
				s.insert(0, "0 ");
			else
				if (s[i - 2] == '(')
					s.insert(i - 1, "0 ");
		}
		i++;
	}
}

bool CreateToken(string s, Token a[], int &n)
{
	bool kt;
	int i = 0;
	n = 0;
	int countL = 0, countR = 0;
	while (i <= s.length())
	{
		kt = false;
		bool ck = false, negative = false;
		double tmp = 0, t = 1;
		while (('0' <= s[i] && s[i] <= '9') || s[i] == '.' || (s[i] == '-' && s[i + 1] != ' '))    //  Tao token so (xu li so am, so thap phan)
		{
			if (s[i] == '-')
				negative = true;
			if (s[i] == '.' && ck)
			{
				return false;
			}
			if (s[i] == '.')
				ck = true;
			if ('0' <= s[i] && s[i] <= '9')
			{
				tmp = tmp * 10 + (int)(s[i] - '0');
				if (ck)
					t *= 10;
			}
			kt = true;
			i++;
		}
		if (kt)
		{
			a[n].Kieu = 0;
			a[n].GiaTri = tmp / t;
			if (negative)
				a[n].GiaTri = -a[n].GiaTri;
			//printf("%.15f %.15f %.15f\n", tmp, a[n].GiaTri, t);
			n++;
		}
		if (s[i] == '(')
		{
			countL++;
			a[n].Kieu = -1;
			a[n].GiaTri = (double)s[i];
			n++;
			kt = true;
		}
		if (s[i] == ')')
		{
			countR++;
			a[n].Kieu = -1;
			a[n].GiaTri = (double)s[i];
			n++;
			kt = true;
		}
		if (s[i] == '+' || ((s[i] == '-') && (s[i + 1] = ' ')))
		{
			a[n].Kieu = 1;
			a[n].GiaTri = (double)s[i];
			n++;
			kt = true;
		}
		if (s[i] == '*' || s[i] == '/')
		{
			a[n].Kieu = 2;
			a[n].GiaTri = (double)s[i];
			n++;
			kt = true;
		}
		if (s[i] == '^' || s[i] == '!')
		{
			a[n].Kieu = 3;
			a[n].GiaTri = (double)s[i];
			n++;
			kt = true;
		}
		if (s[i] == ' ' || s[i] == '\0')
			kt = true;
		//cout << s[i] << " " << kt << endl;
		if (!kt)
			return false;
		i++;
	}
	if (countL != countR)
		return false;
	return true;
}

void InFixToPostFix(Token a[], int n, Stack &stack, Queue &queue)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i].GiaTri == (double)'(')
			PushStack(a[i], stack);
		if (a[i].GiaTri == (double)')')
		{
			Token tmp = PopStack(stack);
			while (tmp.GiaTri != (double)'(')
			{
				PushQueue(tmp, queue);
				tmp = PopStack(stack);
			}	
		}
		if (a[i].Kieu == 1 || a[i].Kieu == 2 || a[i].Kieu == 3)
		{
			if (!IsEmpty(stack))
			{
				while (a[i].Kieu <= TopStack(stack).Kieu)
				{
					Token tmp = PopStack(stack);
					PushQueue(tmp, queue);
					if (IsEmpty(stack))
						break;
				}
			}
			PushStack(a[i], stack);
		}
		if (a[i].Kieu == 0)
			PushQueue(a[i], queue);
	}
	while (!IsEmpty(stack))
	{
		Token tmp = PopStack(stack);
		PushQueue(tmp, queue);
	}
	/*Nod *t = queue.head;
	while (t)
	{
		cout << t->key.Kieu << " " << t->key.GiaTri << endl;
		t = t->next;
	}*/
}

double PostFixToInFix(Stack &stack, Queue &queue, bool &kt)
{
	Token x, u, v, y;
	y.Kieu = 0;
	while (!IsEmpty(queue))
	{
		x = PopQueue(queue);
		if (x.Kieu == 0)
			PushStack(x, stack);
		if (x.Kieu == 1)
		{
			if (!IsEmpty(stack))
				u = PopStack(stack);
			else
			{
				kt = false;
				return 0;
			}
			if (!IsEmpty(stack))
				v = PopStack(stack);
			else
			{
				kt = false;
				return 0;
			}
			//printf("%.15f %.15f\n", u.GiaTri, v.GiaTri);
			if (x.GiaTri == (double) '+')
				y.GiaTri = u.GiaTri + v.GiaTri;
			if (x.GiaTri == (double) '-')
				y.GiaTri = v.GiaTri - u.GiaTri;
			//printf("%.15f\n", y.GiaTri);
			PushStack(y, stack);	
		}
		if (x.Kieu == 2)
		{
			if (!IsEmpty(stack))
				u = PopStack(stack);
			else
			{
				kt = false;
				return 0;
			}
			if (!IsEmpty(stack))
				v = PopStack(stack);
			else
			{
				kt = false;
				return 0;
			}
			//printf("%.15f %.15f\n", u.GiaTri, v.GiaTri);
			if (x.GiaTri == (double) '*')
				y.GiaTri = u.GiaTri * v.GiaTri;
			if (x.GiaTri == (double) '/')
				y.GiaTri = v.GiaTri / u.GiaTri;
			//printf("%.15f\n", y.GiaTri);
			PushStack(y, stack);
		}
		if (x.Kieu == 3)
		{
			if (!IsEmpty(stack))
				u = PopStack(stack);
			else
			{
				kt = false;
				return 0;
			}
			//printf("%.15f\n", u.GiaTri);
			if (x.GiaTri == (double) '!')
			{
				y.GiaTri = 1;
				for (int i = 1; i <= (int)u.GiaTri; i++)
					y.GiaTri *= i;
			}
			if (x.GiaTri == (double)'^')
			{
				if (!IsEmpty(stack))
					v = PopStack(stack);
				else
				{
					kt = false;
					return 0;
				}
				//printf("%.15f\n", v.GiaTri);
				y.GiaTri = 1;
				for (int i = 1; i <= (int)u.GiaTri; i++)
					y.GiaTri *= v.GiaTri;
			}
			//printf("%.15f\n", y.GiaTri);
			PushStack(y, stack);
		}
		
	}
	if (IsEmpty(stack))
	{
		kt = false;
		return 0;
	}
	x = PopStack(stack);
	return x.GiaTri;
}

int main()
{
	// Doc bieu thuc
	ifstream f;
	f.open("Input.inp");
	string c;
	getline(f, c);
	f.close();
	
	Token a[10000];
	int n=0;

	FILE *fo = fopen("Output.out", "w");

	checkString(c);
	//cout << c << endl;
	if (!CreateToken(c, a, n))
	{
		fprintf(fo, "Bieu Thuc Sai\n");
		fclose(fo);
		return 0;
	}
	/*for (int i = 0; i < n; i++)
	{
		cout << a[i].Kieu << " ";
		printf("%.6f\n", a[i].GiaTri);
	}*/

	Stack stack;
	Queue queue;
	InitStack(stack);
	InitQueue(queue);

	InFixToPostFix(a, n, stack, queue);
	bool kt = true;
	double K = PostFixToInFix(stack, queue, kt);
	if (kt)
	{
		fprintf(fo, "%.6f\n", K);
		//printf("%.6f\n", K);
	}
	else
		fprintf(fo,"Bieu thuc sai\n");
	
	fclose(fo);
	_getch();
	return 0;
}