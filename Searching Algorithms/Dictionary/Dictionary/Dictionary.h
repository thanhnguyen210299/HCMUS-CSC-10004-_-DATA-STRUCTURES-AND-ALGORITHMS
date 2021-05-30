#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Dictionary.h"
#include "AddWord.h"
#include "SearchWord.h"
#include "EditWord.h"
#include "DeleteWord.h"
#include "HashTable.h"

class Dictionary : public QMainWindow
{
	Q_OBJECT

public:
	Dictionary(QWidget *parent = Q_NULLPTR);
	static HashTable dic;
private:
	Ui::DictionaryClass ui;

	AddWord add;
	SearchWord search;
	EditWord edit;
	DeleteWord Delete;

	private slots:
	void AddWord();
	void PrintFile();
	void SearchWord();
	void EditWord();
	void DeleteWord();
};
