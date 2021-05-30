#include "SearchWord.h"
#include "Dictionary.h"
#include <qlineedit.h>
#include <qtextedit.h>
#include <qmessagebox.h>

SearchWord::SearchWord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

SearchWord::~SearchWord()
{
}

void SearchWord::searchAWord()
{
	QString qword, qmeaning;
	qword = ui.txt_WordSearch->text();

	if (qword.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Input word", QMessageBox::Ok);
		return;
	}

	string word = qword.toStdString();
	HashNode * node = NULL;

	node = Dictionary::dic.Search(word);
	if (node != NULL)
	{
		qmeaning = Dictionary::dic.getMeaning(node).c_str();
		ui.txt_MeaningSearch->setText(qmeaning);
		QMessageBox::information(this, "Message", "Search sucessfully!", QMessageBox::Ok);
	}
	else
		QMessageBox::critical(this, "Message", "This word is not founded in the dictionary!", QMessageBox::Ok);
}

void SearchWord::back()
{
	ui.txt_WordSearch->setText("");
	ui.txt_MeaningSearch->setText("");
	this->hide();
}