#pragma once

#include <QWidget>
#include "ui_DeleteWord.h"

class DeleteWord : public QWidget
{
	Q_OBJECT

public:
	DeleteWord(QWidget *parent = Q_NULLPTR);
	~DeleteWord();

private:
	Ui::DeleteWord ui;
	private slots:
	void DeleteAWord();
};
