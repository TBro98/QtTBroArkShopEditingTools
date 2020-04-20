#include "QtTBroShop.h"
void QtTBroShop::addgroup(QString vip,int points, int week,int sales)
{
	int iRow = ui.GeneraltableWidget->rowCount();
	ui.GeneraltableWidget->setRowCount(iRow + 1);
	QTableWidgetItem* Default = new QTableWidgetItem(vip);
	ui.GeneraltableWidget->setItem(iRow, 0, Default);
	QSpinBox* Defaultpoints = new QSpinBox();
	Defaultpoints->setMinimum(0);
	Defaultpoints->setMaximum(10000000000);
	Defaultpoints->setValue(points);
	ui.GeneraltableWidget->setCellWidget(iRow, 1, Defaultpoints);
	QSpinBox* Defaultweek = new QSpinBox();
	Defaultweek->setMinimum(0);
	Defaultweek->setMaximum(10000000000);
	Defaultweek->setValue(week);
	ui.GeneraltableWidget->setCellWidget(iRow, 2, Defaultweek);
	QSpinBox* Defaultsales = new QSpinBox();
	Defaultsales->setMinimum(0);
	Defaultsales->setMaximum(100);
	Defaultsales->setSuffix(" %");
	Defaultsales->setValue(sales);
	ui.GeneraltableWidget->setCellWidget(iRow, 3, Defaultsales);
}
void QtTBroShop::addnewgroup()
{
	addgroup("",10,5,100);
}
void QtTBroShop::removegroup()
{
	int iRow = ui.GeneraltableWidget->rowCount();
	ui.GeneraltableWidget->setRowCount(iRow - 1);
}
void QtTBroShop::Generaldef()
{
	ui.GeneraltableWidget->setColumnCount(4);
	ui.GeneraltableWidget->setColumnWidth(0, 200);
	ui.GeneraltableWidget->setColumnWidth(1, 100);
	ui.GeneraltableWidget->setColumnWidth(2, 100);
	ui.GeneraltableWidget->setColumnWidth(3, 100);
	QStringList sListHeader;
	sListHeader << QString::fromLocal8Bit("分组名") << QString::fromLocal8Bit("在线金币") << QString::fromLocal8Bit("周末加成") << QString::fromLocal8Bit("商店折扣");
	ui.GeneraltableWidget->setHorizontalHeaderLabels(sListHeader);

	addgroup("Default",5,5,100);

	addgroup("vip1", 10, 5, 95);
	generalcolorchange();
	connect(ui.colora, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::generalcolorchange);
	connect(ui.colorb, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::generalcolorchange);
	connect(ui.colorc, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::generalcolorchange);

	connect(ui.Generaladdgroupbutton, &QPushButton::clicked, this, &QtTBroShop::addnewgroup);
	connect(ui.Generalremovegroupbutton, &QPushButton::clicked, this, &QtTBroShop::removegroup);


}
void QtTBroShop::generalcolorchange()
{
	int colora = ui.colora->value();
	int colorb = ui.colorb->value();
	int colorc = ui.colorc->value();
	const QColor color = QColor(colora, colorb, colorc);
	QPalette palete;
	palete.setColor(QPalette::Background, color); 
	ui.label_9->setAutoFillBackground(true);
	ui.label_9->setPalette(palete);
	ui.tabWidget->setPalette(palete);
}
void QtTBroShop::loadgeneralconfig()
{
	const QString tbro = QString::number(loadjson["General"].value("tbro", 0));
	ui.tbro->setText(tbro);
	const QString tbrokami = QString::number(loadjson["General"].value("tbrokami", 0));
	ui.tbrokami->setText(tbrokami); 
	bool tbroserver;
	try
	{
		tbroserver = loadjson["General"].value("tbroserver", false);
	}
	catch (const std::exception &)
	{
		tbroserver = false;
	}
	ui.tbroserver->setChecked(tbroserver);

	const int ItemsPerPage = loadjson["General"].value("ItemsPerPage", 15);
	ui.ItemsPerPage->setValue(ItemsPerPage);
	const float ShopDisplayTime = loadjson["General"].value("ShopDisplayTime", 15);
	ui.ShopDisplayTime->setValue(ShopDisplayTime);
	const float ShopTextSize = loadjson["General"].value("ShopTextSize", 1.3);
	ui.ShopTextSize->setValue(ShopTextSize);


	const QString DbPathOverride = QString::fromStdString(loadjson["General"].value("DbPathOverride", "C:\\ArkShop.db"));
	ui.DbPathOverride->setText(DbPathOverride);

	ui.isChatBan->setChecked(loadjson["General"].value("ChatBan", false)); 
	const QString ChatBan = QString::fromStdString(loadjson["Messages"].value("ChatBan", ui.ChatBan->toPlainText().toStdString()));
	ui.ChatBan->setText(ChatBan);

	bool Fixed = loadjson["General"].value("Fixed", true); 
	Fixed = loadjson["General"].value("isfix", Fixed);
	ui.Fixed->setChecked(Fixed);
	nlohmann::json default_color = { 0,255,0,255 };
	nlohmann::json color = loadjson["General"].value("Color", default_color);
	ui.colora->setValue(color[0]);
	ui.colorb->setValue(color[1]);
	ui.colorc->setValue(color[2]);
	ui.colord->setValue(color[3]);

	const bool Enabled = loadjson["General"]["TimedPointsReward"].value("Enabled", true);
	ui.Enabled->setChecked(Enabled);

	const int Interval = loadjson["General"]["TimedPointsReward"].value("Interval", 5);
	ui.Interval->setValue(Interval);

	const int UnlockLevel = loadjson["General"].value("UnlockLevel", 300);
	ui.UnlockLevel->setValue(UnlockLevel);

	auto groups = loadjson["General"]["TimedPointsReward"]["Groups"];
	ui.GeneraltableWidget->setRowCount(0);
	for (auto group_iter = groups.begin(); group_iter != groups.end(); ++group_iter)
	{
		const int Amount = group_iter.value().value("Amount",10);
		const int Add = group_iter.value().value("Add", 5);
		const int Sale = group_iter.value().value("Sale", 100);
		addgroup(QString::fromStdString(group_iter.key()),Amount,Add,Sale);
	}
}


void QtTBroShop::savegeneralconfig()
{
	nlohmann::json mysql;
	mysql["UseMysql"] = false;
	mysql["MysqlHost"] = "localhost";
	mysql["MysqlUser"] = "apitest";
	mysql["MysqlPass"] = "12345";
	mysql["MysqlDB"] = "apitest";
	savejson["Mysql"] = mysql;
	savejson["General"]["tbro"] = ui.tbro->toPlainText().toInt();
	savejson["General"]["tbrokami"] = ui.tbrokami->toPlainText().toInt();
	savejson["General"]["tbroserver"] = ui.tbroserver->isChecked();
	savejson["General"]["ItemsPerPage"]= ui.ItemsPerPage->value();
	savejson["General"]["ShopDisplayTime"] = ui.ShopDisplayTime->value();
	savejson["General"]["ShopTextSize"] = ui.ShopTextSize->value();
	savejson["General"]["DbPathOverride"] = ui.DbPathOverride->toPlainText().toStdString();
	savejson["General"]["Fixed"] = ui.Fixed->isChecked();
	savejson["General"]["ChatBan"] = ui.isChatBan->isChecked();
	savejson["General"]["TimedPointsReward"]["Enabled"] = ui.Enabled->isChecked();
	savejson["Messages"]["ChatBan"] = ui.ChatBan->toPlainText().toStdString();
	nlohmann::json color;
	color[0] = ui.colora->value();
	color[1] = ui.colorb->value();
	color[2] = ui.colorc->value();
	color[3] = ui.colord->value();
	savejson["General"]["Color"] = color;
	savejson["General"]["TimedPointsReward"]["Interval"] = ui.Interval->value();
	savejson["General"]["UnlockLevel"] = ui.UnlockLevel->value();
	for (int i = 0; i < ui.GeneraltableWidget->rowCount(); i++)
	{
		QString vip = ui.GeneraltableWidget->item(i, 0)->text();
		QSpinBox* Amount=(QSpinBox*)ui.GeneraltableWidget->cellWidget(i,1);
		QSpinBox* Add = (QSpinBox*)ui.GeneraltableWidget->cellWidget(i, 2);
		QSpinBox* Sale = (QSpinBox*)ui.GeneraltableWidget->cellWidget(i, 3);
		savejson["General"]["TimedPointsReward"]["Groups"][vip.toStdString()]["Amount"]= Amount->value();
		savejson["General"]["TimedPointsReward"]["Groups"][vip.toStdString()]["Add"]=Add->value();
		savejson["General"]["TimedPointsReward"]["Groups"][vip.toStdString()]["Sale"]= Sale->value();
	}
}