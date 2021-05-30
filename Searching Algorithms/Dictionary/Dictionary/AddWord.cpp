#include "AddWord.h"
#include <qlineedit.h>
#include <qtextedit.h>
#include <qmessagebox.h>
#include "Dictionary.h"

AddWord::AddWord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

AddWord::~AddWord()
{
}

void AddWord::addNewWord()
{
	QString qword, qmeaning;
	qword = ui.txt_WordAdd->text();
	qmeaning = ui.txt_MeaningAdd->toPlainText();

	if (qword.isEmpty() || qmeaning.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Input word/meaning", QMessageBox::Ok);
		return;
	}
	
	WORD word;
	word.m_Word = qword.toStdString();
	word.m_Meaning = qmeaning.toStdString();

	Dictionary::dic.Insert(word);
	QMessageBox::information(this, "Message", "Add sucessfully!", QMessageBox::Ok);
	ui.txt_WordAdd->setText("");
	ui.txt_MeaningAdd->setText("");
	this->hide();
}
