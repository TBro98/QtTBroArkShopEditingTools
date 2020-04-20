#pragma once

#include <QWidget>
#include "ui_yjsd.h"

#include <QDir>
#include <fstream>
#include <qdir.h>
#include <QMessageBox>
#include "json.hpp"
class yjsd : public QWidget
{
	Q_OBJECT

public:
	yjsd(QWidget *parent = Q_NULLPTR);
	void zxyjsd();
	~yjsd();

private:
	Ui::yjsd ui;
};
