#pragma once

#include <QWidget>
#include "ui_AddWord.h"

class AddWord : public QWidget
{
	Q_OBJECT

public:
	AddWord(QWidget *parent = Q_NULLPTR);
	~AddWord();
	private slots:
	void addNewWord();
private:
	Ui::AddWord ui;
};
