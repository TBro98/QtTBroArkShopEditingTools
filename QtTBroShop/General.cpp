#include "QtTBroShop.h"
void QtTBroShop::addgroup(QString Permission,int Amount)
{
	int iRow = ui.GeneraltableWidget->rowCount();
	ui.GeneraltableWidget->setRowCount(iRow + 1);
	QTableWidgetItem* Default = new QTableWidgetItem(Permission);
	ui.GeneraltableWidget->setItem(iRow, 0, Default);
	QSpinBox* Defaultpoints = new QSpinBox();
	Defaultpoints->setMinimum(0);
	Defaultpoints->setMaximum(10000000000);
	Defaultpoints->setValue(Amount);
	ui.GeneraltableWidget->setCellWidget(iRow, 1, Defaultpoints);
}
void QtTBroShop::addnewgroup()
{
	addgroup("",10);
}
void QtTBroShop::removegroup()
{
	int iRow = ui.GeneraltableWidget->rowCount();
	ui.GeneraltableWidget->setRowCount(iRow - 1);
}
void QtTBroShop::Generaldef()
{
	/*
	ui.GeneraltableWidget->setColumnCount(4);
	ui.GeneraltableWidget->setColumnWidth(1, 100);
	ui.GeneraltableWidget->setColumnWidth(2, 100);
	ui.GeneraltableWidget->setColumnWidth(3, 100);
	QStringList sListHeader;
	sListHeader << QString::fromLocal8Bit("分组名") << QString::fromLocal8Bit("在线金币") << QString::fromLocal8Bit("周末加成") << QString::fromLocal8Bit("商店折扣");
	ui.GeneraltableWidget->setHorizontalHeaderLabels(sListHeader);
	*/

	ui.GeneraltableWidget->setColumnWidth(0, 250);

	addgroup("Default",5);

	connect(ui.Generaladdgroupbutton, &QPushButton::clicked, this, &QtTBroShop::addnewgroup);
	connect(ui.Generalremovegroupbutton, &QPushButton::clicked, this, &QtTBroShop::removegroup);


}
void QtTBroShop::loadgeneralconfig()
{
	const int ItemsPerPage = loadjson["General"].value("ItemsPerPage", 15);
	ui.ItemsPerPage->setValue(ItemsPerPage);
	const float ShopDisplayTime = loadjson["General"].value("ShopDisplayTime", 15);
	ui.ShopDisplayTime->setValue(ShopDisplayTime);
	const float ShopTextSize = loadjson["General"].value("ShopTextSize", 1.3);
	ui.ShopTextSize->setValue(ShopTextSize);


	const QString DbPathOverride = QString::fromStdString(loadjson["General"].value("DbPathOverride", ""));
	ui.DbPathOverride->setText(DbPathOverride);

	const bool Enabled = loadjson["General"]["TimedPointsReward"].value("Enabled", true);
	ui.Enabled->setChecked(Enabled);

	const int Interval = loadjson["General"]["TimedPointsReward"].value("Interval", 5);
	ui.Interval->setValue(Interval);

	auto groups = loadjson["General"]["TimedPointsReward"]["Groups"];
	ui.GeneraltableWidget->setRowCount(0);
	for (auto group_iter = groups.begin(); group_iter != groups.end(); ++group_iter)
	{
		const int Amount = group_iter.value().value("Amount",10);
		const int Add = group_iter.value().value("Add", 5);
		const int Sale = group_iter.value().value("Sale", 100);
		addgroup(QString::fromStdString(group_iter.key()),Amount);
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
	auto vipShop_map = loadjson["vipShopItems"];
	if (vipShop_map.empty())
		savejson["Mysql"] = mysql;
	else
		savejson["Mysql"] = loadjson["Mysql"];
	savejson["General"]["ItemsPerPage"]= ui.ItemsPerPage->value();
	savejson["General"]["ShopDisplayTime"] = ui.ShopDisplayTime->value();
	savejson["General"]["ShopTextSize"] = ui.ShopTextSize->value();
	savejson["General"]["DbPathOverride"] = ui.DbPathOverride->toPlainText().toStdString();
	savejson["General"]["TimedPointsReward"]["Enabled"] = ui.Enabled->isChecked();
	savejson["General"]["TimedPointsReward"]["Interval"] = ui.Interval->value();
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