#include "DeleteWord.h"
#include "Dictionary.h"
#include <qmessagebox.h>
#include <qlineedit.h>
#include <qtextedit.h>

DeleteWord::DeleteWord(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

DeleteWord::~DeleteWord()
{
}

void DeleteWord::DeleteAWord()
{
	QString qword;
	qword = ui.txt_WordDelete->text();

	if (qword.isEmpty())
	{
		QMessageBox::warning(this, "Warning", "Input word", QMessageBox::Ok);
		return;
	}

	string word = qword.toStdString();
	if (Dictionary::dic.Delete(word))
		QMessageBox::information(this, "Message", "Delete Sucessfully!", QMessageBox::Ok);
	else
		QMessageBox::critical(this, "Message", "This word is not founded in the dictionary!", QMessageBox::Ok);
	ui.txt_WordDelete->setText("");
	this->close();
}
