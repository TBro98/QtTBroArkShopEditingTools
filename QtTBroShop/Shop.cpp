#include "QtTBroShop.h"

void QtTBroShop::Shopdef()
{
	ui.ShoptreeWidget->setColumnWidth(0, 130);
	ui.ShoptreeWidget->setColumnWidth(1, 140);
	ui.ShoptreeWidget->setColumnWidth(2, 80);
	ui.ShoptreeWidget->setColumnWidth(3, 470);
	ui.ShoptreeWidget->setColumnWidth(4, 300);
	ui.ShoptreeWidget->setColumnWidth(5, 125);
	CreateTopShops("ID", "item", "100", QString::fromLocal8Bit("A Item"), "", "")->addChild(CreateShopItems("item", "10", "0", QString::fromLocal8Bit("Blueprint"), false, false));
	CreateTopShops("ID", "dino", "100", QString::fromLocal8Bit("A Dino"), "", "")->addChild(CreateShopDinos("dino", "", "225", QString::fromLocal8Bit("Blueprint"), "", false));
	ui.ShoptreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.ShoptreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sltShopPopMenu(const QPoint&)));

	connect(ui.Shopopenallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::openallShops);
	connect(ui.Shopcloseallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::closeallShops);

	connect(ui.Shopadditembutton, &QPushButton::clicked, this, &QtTBroShop::AddShopItem);
	connect(ui.Shopadddinobutton, &QPushButton::clicked, this, &QtTBroShop::AddShopDino);
	connect(ui.Shopaddbeaconbutton, &QPushButton::clicked, this, &QtTBroShop::AddShopBeacon);
	connect(ui.Shopaddexperiencebutton, &QPushButton::clicked, this, &QtTBroShop::AddShopExperience);
	connect(ui.Shopaddcommandbutton, &QPushButton::clicked, this, &QtTBroShop::AddShopCommand);
	connect(ui.Shopaddunlockengrambutton, &QPushButton::clicked, this, &QtTBroShop::AddShopUnlockengram);
}


QTreeWidgetItem* QtTBroShop::CreateTopShops(QString id, QString type, QString price, QString name, QString maxtimeordino, QString Permissions)
{

	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, id);
	item->setText(1, type);
	item->setText(2, price);
	item->setText(3, name);
	if (maxtimeordino != "")
		item->setText(4, maxtimeordino);
	item->setText(5, Permissions);

	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setBackgroundColor(0, QColorConstants::Svg::cyan);
	item->setBackgroundColor(1, QColorConstants::Svg::cyan);
	item->setBackgroundColor(2, QColorConstants::Svg::cyan);
	item->setBackgroundColor(3, QColorConstants::Svg::cyan);
	item->setBackgroundColor(4, QColorConstants::Svg::cyan);
	item->setBackgroundColor(5, QColorConstants::Svg::cyan);
	ui.ShoptreeWidget->addTopLevelItem(item);
	return item;
}
QTreeWidgetItem* QtTBroShop::CreateShopDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();
	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	itemitems->setText(4, healthbase);
	itemitems->setText(4, QString::fromLocal8Bit("Neutered"));
	if (Fixed)
		itemitems->setCheckState(4, Qt::CheckState::Checked);
	else
		itemitems->setCheckState(4, Qt::CheckState::Unchecked);


	itemitems->setToolTip(0, QString::fromLocal8Bit("Dino"));
	itemitems->setToolTip(1, QString::fromLocal8Bit("null"));
	itemitems->setToolTip(2, QString::fromLocal8Bit("Level"));
	itemitems->setToolTip(3, QString::fromLocal8Bit("Blueprint"));
	itemitems->setFlags(itemitems->flags() | Qt::ItemIsEditable);
	return itemitems;

}
QTreeWidgetItem* QtTBroShop::CreateShopItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();
	if(type=="item")
	itemitems->setText(0, "Items");
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	if (type == "item")
	{
		itemitems->setText(4, QString::fromLocal8Bit("ForceBlueprint"));

		if (isbluph)
			itemitems->setCheckState(4, Qt::CheckState::Checked);
		else
			itemitems->setCheckState(4, Qt::CheckState::Unchecked);

		itemitems->setToolTip(0, QString::fromLocal8Bit("Items"));
		itemitems->setToolTip(1, QString::fromLocal8Bit("Amount"));
		itemitems->setToolTip(2, QString::fromLocal8Bit("Quality"));
		itemitems->setToolTip(3, QString::fromLocal8Bit("Blueprint"));
	}
	if (type == "experience")
	{
		itemitems->setText(4, QString::fromLocal8Bit("GiveToDino")); 
		if (isbluph)
			itemitems->setCheckState(4, Qt::CheckState::Checked);
		else
			itemitems->setCheckState(4, Qt::CheckState::Unchecked);


		itemitems->setToolTip(2, QString::fromLocal8Bit("experience"));
	}

	itemitems->setFlags(itemitems->flags() | Qt::ItemIsEditable);
	return itemitems;
}

void QtTBroShop::sltShopPopMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.ShoptreeWidget->currentItem();
	QTreeWidgetItem* parent = curItem->parent();
	if (curItem == NULL)
		return;

	if (parent)
	{
		QAction DelWell(QString::fromLocal8Bit("&Remove"), this);
		connect(&DelWell, SIGNAL(triggered()), this, SLOT(ShopDelWell()));
		QPoint pos;
		QMenu menu(ui.ShoptreeWidget);
		menu.addAction(&DelWell);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
		return;
	}
	QAction AdditemsWell(QString::fromLocal8Bit("&Add item"), this);
	QAction DelWell(QString::fromLocal8Bit("&Remove"), this);
	//在界面上删除该item
	connect(&AdditemsWell, SIGNAL(triggered()), this, SLOT(ShopAddItem()));
	connect(&DelWell, SIGNAL(triggered()), this, SLOT(ShopDelWell()));

	QPoint pos;
	QMenu menu(ui.ShoptreeWidget);

	if (curItem->text(1) != QString::fromStdString("beacon")&& curItem->text(1) != QString::fromStdString("dino"))
	menu.addAction(&AdditemsWell);
	menu.addAction(&DelWell);
	menu.exec(QCursor::pos());  
}

void QtTBroShop::ShopAddItem()
{
	QTreeWidgetItem* curItem = ui.ShoptreeWidget->currentItem();
	if(curItem->text(1)=="command")
		curItem->addChild(CreateShopItems("command", "", "", QString::fromLocal8Bit("Command"), false, false));
	else if(curItem->text(1) == "unlockengram")
		curItem->addChild(CreateShopItems("unlockengram", "", "", QString::fromLocal8Bit("Blueprint"), false, false));
	else
		curItem->addChild(CreateShopItems("item", "10", "0", QString::fromLocal8Bit("Blueprint"), false, false));
}

void QtTBroShop::ShopDelWell()
{
	QTreeWidgetItem* curItem = ui.ShoptreeWidget->currentItem();
	curItem->~QTreeWidgetItem();
}

void QtTBroShop::openallShops()
{
	ui.ShoptreeWidget->expandAll();
}
void QtTBroShop::closeallShops()
{
	ui.ShoptreeWidget->collapseAll();
}

void QtTBroShop::AddShopItem()
{
	CreateTopShops("ID", "item", "100", QString::fromLocal8Bit("The item"), "", "")->addChild(CreateShopItems("item", "10", "0", QString::fromLocal8Bit("Blueprint"), false, false));
}
void QtTBroShop::AddShopDino()
{
	CreateTopShops("ID", "dino", "100", QString::fromLocal8Bit("The dino"), "", "")->addChild(CreateShopDinos("dino", "", "225", QString::fromLocal8Bit("Blueprint"), "", false));
}
void QtTBroShop::AddShopBeacon()
{
	CreateTopShops("ID", "beacon", "100", QString::fromLocal8Bit("The beacon"), QString::fromLocal8Bit("ClassName"), false);
}
void QtTBroShop::AddShopExperience()
{
	bool fix = true;
	CreateTopShops("ID", "experience", "100", QString::fromLocal8Bit("The experience"), "", "")->addChild(CreateShopItems("experience", "", "10000", "", fix, false));
}
void QtTBroShop::AddShopCommand()
{
	CreateTopShops("ID", "command", "100", QString::fromLocal8Bit("The command"), "", "")->addChild(CreateShopItems("command", "", "", QString::fromLocal8Bit("Command"), false, false));
}
void QtTBroShop::AddShopUnlockengram()
{
	bool fix = true;
	CreateTopShops("ID", "unlockengram", "100", QString::fromLocal8Bit("The unlockengram"), "", "")->addChild(CreateShopItems("unlockengram", "", "", QString::fromLocal8Bit("Blueprint"), false, false));
}

void QtTBroShop::loadShopconfig()
{
	const int shopnum = ui.ShoptreeWidget->topLevelItemCount();
	for (int i = 0; i < shopnum; i++)
		ui.ShoptreeWidget->topLevelItem(0)->~QTreeWidgetItem();
	auto shop_map = loadjson["ShopItems"];
	for (auto iter = shop_map.begin(); iter != shop_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();
		const QString type = QString::fromStdString(iter_value["Type"]);
		const int price = iter_value["Price"];
		const QString Description = QString::fromStdString(iter_value.value("Description", ""));
		QString Permissions = QString::fromStdString(iter_value.value("Permissions",""));
		QString maxtime = "";
		if (type == "beacon")
		{
			maxtime = QString::fromStdString(iter_value["ClassName"]);
		}

		QTreeWidgetItem* shopitems = CreateTopShops(id, type, QString::number(price), Description, maxtime, Permissions);
		if (type == "dino"|| type == "item")
		{
			if (type == "dino")
			{
				bool neutered = iter_value.value("Neutered", false);
				QString Blueprint = QString::fromStdString(iter_value["Blueprint"]);
				const int Level = iter_value["Level"];
				QString level = QString::number(Level);
				QString healthbase = "";
				shopitems->addChild(CreateShopDinos("", "", level, Blueprint, healthbase, neutered));
			}

			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				const int amount = item["Amount"];
				const float quality = item["Quality"];
				const bool force_blueprint = item["ForceBlueprint"];
				QString blueprint = QString::fromStdString(item["Blueprint"]);

				shopitems->addChild(CreateShopItems("item", QString::number(amount), QString::number(quality), blueprint, force_blueprint, false));
			}
		}
		if (type == "unlockengram")
		{
			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				QString blueprint = QString::fromStdString(item["Blueprint"]);
				shopitems->addChild(CreateShopItems("", "", "", blueprint, false, false));
			}
		}
		if (type=="command")
		{
			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				QString Command = QString::fromStdString(item["Command"]);
				shopitems->addChild(CreateShopItems("", "", "", Command, false, false));
			}
		}
		if (type == "experience")
		{
			float Amount = iter_value["Amount"];
			bool GiveToDino = iter_value.value("GiveToDino", true);
			shopitems->addChild(CreateShopItems("experience", "", QString::number(Amount,'f', 1),"" , GiveToDino, false));
		}
	}
}


void QtTBroShop::saveShopconfig()
{
	int shopnum = ui.ShoptreeWidget->topLevelItemCount();
	for (int i = 0; i < shopnum; i++)
	{
		QTreeWidgetItem* shop = ui.ShoptreeWidget->topLevelItem(i);
		QString shopid = shop->text(0);
		savejson["ShopItems"][shopid.toStdString()]["Type"] = shop->text(1).toStdString();
		savejson["ShopItems"][shopid.toStdString()]["Price"] = shop->text(2).toInt();
		savejson["ShopItems"][shopid.toStdString()]["Description"] = shop->text(3).toStdString();
		if(shop->text(5).toStdString()!="")
		savejson["ShopItems"][shopid.toStdString()]["Permissions"] = shop->text(5).toStdString();
		if (shop->text(1) == "item"&& shop->text(4)!="")
		{
			savejson["ShopItems"][shopid.toStdString()]["MaxAmount"] = shop->text(4).toInt();
		}
		if (shop->text(1) == "item"|| shop->text(1) == "dino")
		{
			int it = 0;
			for (int j = 0; j < shop->childCount(); j++)
			{
				QTreeWidgetItem* shopitem = shop->child(j);
				if (shopitem->text(0)=="Items")
				{
					savejson["ShopItems"][shopid.toStdString()]["Items"][it]["Amount"] = shopitem->text(1).toInt();
					savejson["ShopItems"][shopid.toStdString()]["Items"][it]["Quality"] = shopitem->text(2).toFloat();
					savejson["ShopItems"][shopid.toStdString()]["Items"][it]["Blueprint"] = getblu(shopitem->text(3).toStdString());
					if (shopitem->checkState(4) == Qt::CheckState::Checked)
					{
						savejson["ShopItems"][shopid.toStdString()]["Items"][it]["ForceBlueprint"] = true;
					}
					else if (shopitem->checkState(4) == Qt::CheckState::Unchecked)
					{
						savejson["ShopItems"][shopid.toStdString()]["Items"][it]["ForceBlueprint"] = false;
					}
					it++;
				}
				else
				{
					savejson["ShopItems"][shopid.toStdString()]["Blueprint"] = getblu(shopitem->text(3).toStdString());
					savejson["ShopItems"][shopid.toStdString()]["Level"] = shopitem->text(2).toInt();
					if (shopitem->checkState(4) == Qt::CheckState::Checked)
					{
						savejson["ShopItems"][shopid.toStdString()]["Neutered"] = true;
					}
				}
			}
		}
		if (shop->text(1) == "beacon")
		{
			savejson["ShopItems"][shopid.toStdString()]["ClassName"] = shop->text(4).toStdString();
		}
		if (shop->text(1) == "experience")
		{
			savejson["ShopItems"][shopid.toStdString()]["Amount"] = shop->child(0)->text(2).toFloat();
			if (shop->child(0)->checkState(4) == Qt::CheckState::Checked)
			{
				savejson["ShopItems"][shopid.toStdString()]["GiveToDino"] = true;
			}
			else if (shop->child(0)->checkState(4) == Qt::CheckState::Unchecked)
			{
				savejson["ShopItems"][shopid.toStdString()]["GiveToDino"] = false;
			}
		}
		if (shop->text(1) == "unlockengram")
		{
			for (int j = 0; j < shop->childCount(); j++)
			{
				QTreeWidgetItem* shopitem = shop->child(j);
				savejson["ShopItems"][shopid.toStdString()]["Items"][j]["Blueprint"] = getblu(shopitem->text(3).toStdString());
			}
		}
		if (shop->text(1) == "command")
		{
			for (int j = 0; j < shop->childCount(); j++)
			{
				QTreeWidgetItem* shopitem = shop->child(j);
				savejson["ShopItems"][shopid.toStdString()]["Items"][j]["Command"] = shopitem->text(3).toStdString();
			}
		}




	}
}