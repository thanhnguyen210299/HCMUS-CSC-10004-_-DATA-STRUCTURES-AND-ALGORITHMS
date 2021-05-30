#include "EditWord.h"
#include "Dictionary.h"
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qtextedit.h>

EditWord::EditWord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

EditWord::~EditWord()
{
}

void EditWord::editAWord()
{
	QString qword, qmeaning;
	qword = ui.txt_WordEdit->text();
	qmeaning = ui.txt_MeaningEdit->toPlainText();

	if (qword.isEmpty() || qmeaning.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Input word/meaning", QMessageBox::Ok);
		return;
	}

	WORD word;
	word.m_Word = qword.toStdString();
	word.m_Meaning = qmeaning.toStdString();

	HashNode * node = NULL;
	node = Dictionary::dic.Search(word.m_Word);
	if (node)
	{
		Dictionary::dic.edit(node, word.m_Meaning);
		QMessageBox::information(this, "Message", "Edit Sucessfully!", QMessageBox::Ok);
	}
	else
		QMessageBox::critical(this, "Message", "This word is not founded in the dictionary!", QMessageBox::Ok);
	ui.txt_WordEdit->setText("");
	ui.txt_MeaningEdit->setText("");
	this->hide();
}
