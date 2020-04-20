#include "QtTBroShop.h"

QTreeWidgetItem* QtTBroShop::CreateTopsell(QString id, QString amount, QString price, QString name, QString blup)
{

	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, id);
	item->setText(1, amount);
	item->setText(2, price);
	item->setText(3, name);
	item->setText(4, blup);


	item->setBackgroundColor(0, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(1, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(2, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(3, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(4, QColorConstants::Svg::lightcyan);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	return item;
}
void QtTBroShop::selldef()
{
	//ui.kamitreeWidget->setColumnCount(5);
	ui.selltreeWidget->setColumnWidth(0, 100);
	ui.selltreeWidget->setColumnWidth(1, 100);
	ui.selltreeWidget->setColumnWidth(2, 100);
	ui.selltreeWidget->setColumnWidth(3, 100);
	ui.selltreeWidget->setColumnWidth(4, 1000);


	ui.vipselltreeWidget->setColumnWidth(0, 100);
	ui.vipselltreeWidget->setColumnWidth(1, 100);
	ui.vipselltreeWidget->setColumnWidth(2, 100);
	ui.vipselltreeWidget->setColumnWidth(3, 100);
	ui.vipselltreeWidget->setColumnWidth(4, 1000);

	connect(ui.AddSellbutton, &QPushButton::clicked, this, &QtTBroShop::AddSellItem);
	connect(ui.Removesellbutton, &QPushButton::clicked, this, &QtTBroShop::RemoveSellItem);

	connect(ui.AddvipSellbutton, &QPushButton::clicked, this, &QtTBroShop::AddvipSellItem);
	connect(ui.Removevipsellbutton, &QPushButton::clicked, this, &QtTBroShop::RemovevipSellItem);

}

void QtTBroShop::AddSellItem()
{
	QTreeWidgetItem* item = CreateTopsell("ID", "1", "10", QString::fromLocal8Bit("Ãû³Æ"),QString::fromLocal8Bit("À¶Í¼´úÂë"));

	ui.selltreeWidget->addTopLevelItem(item);
}

void QtTBroShop::RemoveSellItem()
{
	int cout = ui.selltreeWidget->topLevelItemCount();
	ui.selltreeWidget->takeTopLevelItem(cout - 1);
}

void QtTBroShop::AddvipSellItem()
{
	QTreeWidgetItem* item = CreateTopsell("ID", "1", "10", QString::fromLocal8Bit("Ãû³Æ"), QString::fromLocal8Bit("À¶Í¼´úÂë"));

	ui.vipselltreeWidget->addTopLevelItem(item);
}

void QtTBroShop::RemovevipSellItem()
{
	int cout = ui.vipselltreeWidget->topLevelItemCount();
	ui.vipselltreeWidget->takeTopLevelItem(cout - 1);
}

void QtTBroShop::loadSellItem()
{
	const int sellnum = ui.selltreeWidget->topLevelItemCount();
	for (int i = 0; i < sellnum; i++)
		ui.selltreeWidget->takeTopLevelItem(0);
	if (loadjson["SellItems"].empty())
		return;

	auto sell_map = loadjson["SellItems"];
	for (auto iter = sell_map.begin(); iter != sell_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();
		QString Description = QString::fromStdString(iter_value.value("Description",""));
		QString Blueprint = QString::fromStdString(iter_value.value("Blueprint", ""));
		const int price = iter_value.value("Price", 0);
		const int Amount = iter_value.value("Amount", 0);
		QTreeWidgetItem* item = CreateTopsell(id, QString::number(Amount), QString::number(price), Description,Blueprint);

		ui.selltreeWidget->addTopLevelItem(item);
	}
}
void QtTBroShop::loadvipSellItem()
{
	const int sellnum = ui.vipselltreeWidget->topLevelItemCount();
	for (int i = 0; i < sellnum; i++)
		ui.vipselltreeWidget->takeTopLevelItem(0);
	if (loadjson["vipSellItems"].empty())
		return;

	auto sell_map = loadjson["vipSellItems"];
	for (auto iter = sell_map.begin(); iter != sell_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();
		QString Description = QString::fromStdString(iter_value.value("Description", ""));
		QString Blueprint = QString::fromStdString(iter_value.value("Blueprint", ""));
		const int price = iter_value.value("Price", 0);
		const int Amount = iter_value.value("Amount", 0);
		QTreeWidgetItem* item = CreateTopsell(id, QString::number(Amount), QString::number(price), Description,Blueprint);

		ui.vipselltreeWidget->addTopLevelItem(item);
	}
}

void QtTBroShop::saveSellconfig()
{
	int sellnum = ui.selltreeWidget->topLevelItemCount();
	for (int i = 0; i < sellnum; i++)
	{
		QTreeWidgetItem* sell = ui.selltreeWidget->topLevelItem(i);
		QString sellid = sell->text(0);
		savejson["SellItems"][sellid.toStdString()]["Amount"] = sell->text(1).toInt();
		savejson["SellItems"][sellid.toStdString()]["Price"] = sell->text(2).toInt();
		savejson["SellItems"][sellid.toStdString()]["Description"] = sell->text(3).toStdString();
		savejson["SellItems"][sellid.toStdString()]["Blueprint"] = getblu(sell->text(4).toStdString());
		savejson["SellItems"][sellid.toStdString()]["Type"] = "item";
	}
}
void QtTBroShop::savevipSellconfig()
{
	int sellnum = ui.vipselltreeWidget->topLevelItemCount();
	for (int i = 0; i < sellnum; i++)
	{
		QTreeWidgetItem* sell = ui.vipselltreeWidget->topLevelItem(i);
		QString sellid = sell->text(0);
		savejson["vipSellItems"][sellid.toStdString()]["Amount"] = sell->text(1).toInt();
		savejson["vipSellItems"][sellid.toStdString()]["Price"] = sell->text(2).toInt();
		savejson["vipSellItems"][sellid.toStdString()]["Description"] = sell->text(3).toStdString();
		savejson["vipSellItems"][sellid.toStdString()]["Blueprint"] = getblu(sell->text(4).toStdString());
		savejson["vipSellItems"][sellid.toStdString()]["Type"] = "item";
	}
}