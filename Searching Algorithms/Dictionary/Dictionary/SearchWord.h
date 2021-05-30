#pragma once

#include <QWidget>
#include "ui_SearchWord.h"

class SearchWord : public QWidget
{
	Q_OBJECT

public:
	SearchWord(QWidget *parent = Q_NULLPTR);
	~SearchWord();

private:
	Ui::SearchWord ui;
	private slots:
	void searchAWord();
	void back();
};

