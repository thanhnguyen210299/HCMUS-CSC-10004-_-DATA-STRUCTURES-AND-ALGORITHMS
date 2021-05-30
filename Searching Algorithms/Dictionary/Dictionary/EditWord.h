#pragma once

#include <QWidget>
#include "ui_EditWord.h"

class EditWord : public QWidget
{
	Q_OBJECT

public:
	EditWord(QWidget *parent = Q_NULLPTR);
	~EditWord();

private:
	Ui::EditWord ui;
	private slots:
	void editAWord();
};
