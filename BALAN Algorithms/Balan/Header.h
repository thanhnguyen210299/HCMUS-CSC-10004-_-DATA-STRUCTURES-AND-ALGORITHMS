struct Token
{
	int Kieu;
	double GiaTri;
};

struct Nod
{
	Token key;
	Nod *next;
};

struct Stack
{
	Nod * stackTop;
};

struct Queue
{
	Nod *head;
	Nod *tail;
};
bool IsEmpty(Stack stack)
{
	if (stack.stackTop == NULL)
		return true;
	else
		return false;
}

bool IsEmpty(Queue queue)
{
	if (queue.head == NULL)
		return true;
	else
		return false;
}

void InitStack(Stack &stack)
{
	stack.stackTop = NULL;
}

void InitQueue(Queue &queue)
{
	queue.head = NULL;
	queue.tail = NULL;
}

void PushStack(Token a, Stack &stack) //Thêm phần tử vào Stack
{
	Nod * p = new Nod;
	p->key = a;
	p->next = stack.stackTop;
	stack.stackTop = p;
}

void PushQueue(Token a, Queue &queue) //Thêm phần tử vào Queue
{
	Nod * p = new Nod;
	p->key = a;
	p->next = NULL;
	if (queue.head == NULL)
		queue.head = queue.tail = p;
	else 
	{
		queue.tail->next = p;
		queue.tail = p;
	}
}

Token PopStack(Stack &stack) //Lấy phần tử ở đỉnh khỏi Stack
{
	Nod * p = stack.stackTop;
	Token tmp = p->key;
	stack.stackTop = stack.stackTop->next;
	delete p;
	return tmp;
}

Token PopQueue(Queue &queue) //Lấy phần tử ở đỉnh ra khỏi Queue
{
	Nod * p = queue.head;
	Token tmp = p->key;
	queue.head = queue.head->next;
	delete p;
	return tmp;
}

Token TopStack(Stack stack) //Xem giá trị phần tử ở đỉnh (không Pop).
{
	return stack.stackTop->key;
}