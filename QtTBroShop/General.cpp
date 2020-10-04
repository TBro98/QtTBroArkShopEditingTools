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

	nlohmann::json mysqljson = loadjson.value("Mysql",nlohmann::json::object());
	ui.UseMysql->setChecked(mysqljson.value("UseMysql", false));
	ui.ArkShopMysqlHost->setText(QString::fromStdString(mysqljson.value("MysqlHost", "localhost")));
	ui.ArkShopMysqlUser->setText(QString::fromStdString(mysqljson.value("MysqlUser", "MysqlUser")));
	ui.ArkShopMysqlPass->setText(QString::fromStdString(mysqljson.value("MysqlPass", "MysqlPass")));
	ui.ArkShopMysqlDB->setText(QString::fromStdString(mysqljson.value("MysqlDB", "MysqlDB")));

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
		addgroup(QString::fromStdString(group_iter.key()),Amount);
	}
}


void QtTBroShop::savegeneralconfig()
{
	savejson["Mysql"]["UseMysql"] = ui.UseMysql->isChecked();
	savejson["Mysql"]["MysqlHost"] =ui.ArkShopMysqlHost->toPlainText().toStdString();
	savejson["Mysql"]["MysqlUser"] = ui.ArkShopMysqlUser->toPlainText().toStdString();
	savejson["Mysql"]["MysqlPass"] = ui.ArkShopMysqlPass->toPlainText().toStdString();
	savejson["Mysql"]["MysqlDB"] = ui.ArkShopMysqlDB->toPlainText().toStdString();

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
		savejson["General"]["TimedPointsReward"]["Groups"][vip.toStdString()]["Amount"]= Amount->value();
	}
}