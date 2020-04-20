#include "QtTBroShop.h"

void QtTBroShop::vipShopdef()
{
	ui.vipShoptreeWidget->setColumnWidth(0, 100);
	ui.vipShoptreeWidget->setColumnWidth(1, 140);
	ui.vipShoptreeWidget->setColumnWidth(2, 140);
	ui.vipShoptreeWidget->setColumnWidth(3, 630);
	ui.vipShoptreeWidget->setColumnWidth(4, 300);
	ui.vipShoptreeWidget->setColumnWidth(5, 125);
	CreateTopvipShops("ID", "item", "100", QString::fromLocal8Bit("物品示例"), "", false)->addChild(CreatevipShopItems("item", "10", "0", QString::fromLocal8Bit("蓝图代码"), false, false));
	CreateTopvipShops("ID", "dino", "100", QString::fromLocal8Bit("恐龙示例"), "", false)->addChild(CreatevipShopDinos("", "", "225", QString::fromLocal8Bit("蓝图代码"), "", false));
	QTreeWidgetItem* dinoitem = CreateTopvipShops("ID", "dino", "200", QString::fromLocal8Bit("恐龙加物品示例"), "", false);
	dinoitem->addChild(CreatevipShopDinos("", "", "225", QString::fromLocal8Bit("蓝图代码"), "", false));
	dinoitem->addChild(CreatevipShopItems("item", "10", "0", QString::fromLocal8Bit("蓝图代码"), false, false));
	ui.vipShoptreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.vipShoptreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sltvipShopPopMenu(const QPoint&)));

	connect(ui.vipShopopenallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::openallvipShops);
	connect(ui.vipShopcloseallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::closeallvipShops);

	connect(ui.vipShopadditembutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopItem);
	connect(ui.vipShopadddinobutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopDino);
	connect(ui.vipShopupvipbutton, &QPushButton::clicked, this, &QtTBroShop::vipShopupvip);
	connect(ui.vipShopaddbeaconbutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopBeacon);
	connect(ui.vipShopaddexperiencebutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopExperience);
	connect(ui.vipShopaddcommandbutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopCommand);
	connect(ui.vipShopaddunlockengrambutton, &QPushButton::clicked, this, &QtTBroShop::AddvipShopUnlockengram);
}


QTreeWidgetItem* QtTBroShop::CreateTopvipShops(QString id, QString type, QString price, QString name, QString maxtimeordino, QString Permissions)
{

	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, id);
	item->setText(1, type);
	item->setText(2, price);
	item->setText(3, name);
	if (type == "vip")
	{
		item->setText(4, QString::fromLocal8Bit("新的vip"));
	}

	if (maxtimeordino != "")
		item->setText(4, maxtimeordino);
	item->setText(5, Permissions);
	item->setFlags(item->flags() | Qt::ItemIsEditable);
	item->setBackgroundColor(0, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(1, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(2, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(3, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(4, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(5, QColorConstants::Svg::lightcyan);
	ui.vipShoptreeWidget->addTopLevelItem(item);
	return item;
}

QTreeWidgetItem* QtTBroShop::CreatevipShopDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Neutered)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();
	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	if (healthbase == "")
		itemitems->setText(4, QString::fromLocal8Bit("如要固定属性则设置数值"));
	else
		itemitems->setText(4, healthbase);
	itemitems->setText(5, QString::fromLocal8Bit("是否绝育"));
	if (Neutered)
		itemitems->setCheckState(5, Qt::CheckState::Checked);
	else
		itemitems->setCheckState(5, Qt::CheckState::Unchecked);
	itemitems->setFlags(itemitems->flags() | Qt::ItemIsEditable);
	return itemitems;

}
QTreeWidgetItem* QtTBroShop::CreatevipShopItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();
	if (type == "item")
		itemitems->setText(0, "Items");
	else if(type=="Points")
		itemitems->setText(0, "Points");
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	if (type == "experience")
	{
		itemitems->setText(4, QString::fromLocal8Bit("能否给恐龙"));
		if (isbluph)
			itemitems->setCheckState(4, Qt::CheckState::Checked);
		else 
			itemitems->setCheckState(4, Qt::CheckState::Unchecked);
	}
	if (type == "item")
	{
		itemitems->setText(4, QString::fromLocal8Bit("是否为图纸"));
		itemitems->setText(5, QString::fromLocal8Bit("固定属性品质"));

		if (isbluph)
			itemitems->setCheckState(4, Qt::CheckState::Checked);
		else
			itemitems->setCheckState(4, Qt::CheckState::Unchecked);
		if (Fixed)
			itemitems->setCheckState(5, Qt::CheckState::Checked);
		else
			itemitems->setCheckState(5, Qt::CheckState::Unchecked);
	}

	itemitems->setFlags(itemitems->flags() | Qt::ItemIsEditable);
	return itemitems;
}

void QtTBroShop::sltvipShopPopMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.vipShoptreeWidget->currentItem();
	QTreeWidgetItem* parent = curItem->parent();
	if (curItem == NULL)
		return;

	if (parent)
	{
		QAction DelWell(QString::fromLocal8Bit("&删除"), this);
		connect(&DelWell, SIGNAL(triggered()), this, SLOT(vipShopDelWell()));
		QPoint pos;
		QMenu menu(ui.vipShoptreeWidget);
		menu.addAction(&DelWell);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
		return;
	}
	QAction AdditemsWell(QString::fromLocal8Bit("&新建物品"), this);
	QAction DelWell(QString::fromLocal8Bit("&删除"), this);
	//在界面上删除该item
	connect(&AdditemsWell, SIGNAL(triggered()), this, SLOT(vipShopAddItem()));
	connect(&DelWell, SIGNAL(triggered()), this, SLOT(vipShopDelWell()));

	QPoint pos;
	QMenu menu(ui.vipShoptreeWidget);
	QAction AdddinosWell(QString::fromLocal8Bit("&新建恐龙"), this);
	QAction AddpointsWell(QString::fromLocal8Bit("&新建金币"), this);
	connect(&AdddinosWell, SIGNAL(triggered()), this, SLOT(vipShopvipAddDinos()));
	connect(&AddpointsWell, SIGNAL(triggered()), this, SLOT(vipShopvipAddPoints()));
	if (curItem->text(1) == "vip")
	{
		menu.addAction(&AdddinosWell);
		menu.addAction(&AddpointsWell);
	}
	menu.addAction(&AdditemsWell);
	menu.addAction(&DelWell);
	menu.exec(QCursor::pos());  //在当前鼠标位置显示
}
void QtTBroShop::vipShopAddItem()
{
	QTreeWidgetItem* curItem = ui.vipShoptreeWidget->currentItem();

	bool fix = false;
	if (ui.Fixed->isChecked())
		fix = true;
	if (curItem->text(1) == "command")
		curItem->addChild(CreatevipShopItems("command", "", "", QString::fromLocal8Bit("命令代码"), false, false));
	else if (curItem->text(1) == "unlockengram")
		curItem->addChild(CreatevipShopItems("unlockengram", "", "", QString::fromLocal8Bit("蓝图代码"), false, false));
	else
		curItem->addChild(CreatevipShopItems("item", "10", "0", QString::fromLocal8Bit("蓝图代码"), false, fix));
}

void QtTBroShop::vipShopDelWell()
{
	//if (ui.vipShoptreeWidget->currentItem()->parent() == NULL)
	//{
	//	delete ui.vipShoptreeWidget->takeTopLevelItem(ui.vipShoptreeWidget->currentIndex().row());
	//}
	//else
	//{
	//	//如果有父节点就要用父节点的takeChild删除节点
	//	delete ui.vipShoptreeWidget->currentItem()->parent()->takeChild(ui.vipShoptreeWidget->currentIndex().row());
	//}
	QTreeWidgetItem* curItem = ui.vipShoptreeWidget->currentItem();
	curItem->~QTreeWidgetItem();
}
void QtTBroShop::vipShopvipAddDinos()
{
	QTreeWidgetItem* curItem = ui.vipShoptreeWidget->currentItem();
	curItem->addChild(CreatevipShopDinos("Dinos", "", "225", QString::fromLocal8Bit("蓝图代码"), "", false));

}
void QtTBroShop::vipShopvipAddPoints()
{
	QTreeWidgetItem* curItem = ui.vipShoptreeWidget->currentItem();
	curItem->addChild(CreatevipShopItems("Points", "1000", "", "", false, false));

}
void QtTBroShop::openallvipShops()
{
	ui.vipShoptreeWidget->expandAll();
}
void QtTBroShop::closeallvipShops()
{
	ui.vipShoptreeWidget->collapseAll();
}

void QtTBroShop::AddvipShopItem()
{
	bool fix = false;
	if (ui.Fixed->isChecked())
		fix = true;
	CreateTopvipShops("ID", "item", "100", QString::fromLocal8Bit("物品示例"), "", "")->addChild(CreatevipShopItems("item", "10", "0", QString::fromLocal8Bit("蓝图代码"), false, fix));
}
void QtTBroShop::AddvipShopDino()
{
	CreateTopvipShops("ID", "dino", "100", QString::fromLocal8Bit("恐龙示例"), "", "")->addChild(CreatevipShopDinos("", "", "225", QString::fromLocal8Bit("蓝图代码"), "", false));
}

void QtTBroShop::vipShopupvip()
{
	CreateTopvipShops("ID", "vip", "100", QString::fromLocal8Bit("v6升级v7"), "vip7", "vip6");
}

void QtTBroShop::AddvipShopBeacon()
{
	CreateTopvipShops("ID", "beacon", "100", QString::fromLocal8Bit("宝箱光柱示例"), QString::fromLocal8Bit("宝箱光柱代码"), false);
}
void QtTBroShop::AddvipShopExperience()
{
	bool fix = true;
	CreateTopvipShops("ID", "experience", "100", QString::fromLocal8Bit("经验示例"), "", "")->addChild(CreatevipShopItems("experience", "", "10000","", fix, false));
}
void QtTBroShop::AddvipShopCommand()
{
	CreateTopvipShops("ID", "command", "100", QString::fromLocal8Bit("命令示例"), "", "")->addChild(CreatevipShopItems("command", "", "", QString::fromLocal8Bit("命令代码"), false, false));
}
void QtTBroShop::AddvipShopUnlockengram()
{
	bool fix = true;
	CreateTopvipShops("ID", "unlockengram", "100", QString::fromLocal8Bit("解锁技能示例"), "", "")->addChild(CreatevipShopItems("unlockengram", "", "", QString::fromLocal8Bit("蓝图代码"), false, false));
}


void QtTBroShop::loadvipShopconfig()
{
	const int vipShopnum = ui.vipShoptreeWidget->topLevelItemCount();
	for (int i = 0; i < vipShopnum; i++)
		ui.vipShoptreeWidget->topLevelItem(0)->~QTreeWidgetItem();
	auto vipShop_map = loadjson["vipShopItems"];
	if (vipShop_map.empty())
		return;

	for (auto iter = vipShop_map.begin(); iter != vipShop_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();
		const QString type = QString::fromStdString(iter_value["Type"]);
		const int price = iter_value["Price"];
		const QString Description = QString::fromStdString(iter_value.value("Description", ""));
		QString Permissions = QString::fromStdString(iter_value.value("Permissions", ""));
		QString maxtime = "";
		if (type == "item")
		{
			int MaxAmount = iter_value.value("MaxAmount", 0);
			if (MaxAmount != 0)
				maxtime = QString::number(MaxAmount);
		}
		if (type == "beacon")
		{
			maxtime = QString::fromStdString(iter_value["ClassName"]);
		}

		QTreeWidgetItem* vipShopitems = CreateTopvipShops(id, type, QString::number(price), Description, maxtime, Permissions);
		if (type == "dino" || type == "item")
		{
			if (type == "dino")
			{
				bool neutered = iter_value.value("Neutered", false);
				QString Blueprint = QString::fromStdString(iter_value["Blueprint"]);
				const int Level = iter_value["Level"];
				QString level = QString::number(Level);
				QString healthbase = "";
				const float HealthBase = iter_value.value("HealthBase", 0.0);
				if (HealthBase > 0)
					healthbase = QString::number(HealthBase);
				vipShopitems->addChild(CreatevipShopDinos("", "", level, Blueprint, healthbase, neutered));
			}

			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				const int amount = item["Amount"];
				const float quality = item["Quality"];
				const bool force_blueprint = item["ForceBlueprint"];
				QString blueprint = QString::fromStdString(item["Blueprint"]);
				const bool gudingshuxing = item.value("Fixed", loadjson["General"].value("Fixed", true));

				vipShopitems->addChild(CreatevipShopItems("item", QString::number(amount), QString::number(quality), blueprint, force_blueprint, gudingshuxing));
			}
		}
		if (type == "unlockengram")
		{
			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				QString blueprint = QString::fromStdString(item["Blueprint"]);
				vipShopitems->addChild(CreatevipShopItems("", "", "", blueprint, false, false));
			}
		}
		if (type == "command")
		{
			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				QString Command = QString::fromStdString(item["Command"]);
				vipShopitems->addChild(CreatevipShopItems("", "", "", Command, false, false));
			}
		}
		if (type == "experience")
		{
			float Amount = iter_value["Amount"];
			bool GiveToDino = iter_value.value("GiveToDino", true);
			vipShopitems->addChild(CreateShopItems("experience", "", QString::number(Amount, 'f', 1), "", GiveToDino, false));
		}
		if (type == "vip")
		{
			QString newvip= QString::fromStdString(iter_value["newvip"]);
			vipShopitems->setText(4, newvip);
			auto items_map = iter_value.value("Items", nlohmann::json::array());
			for (const auto& item : items_map)
			{
				const int amount = item["Amount"];
				const float quality = item["Quality"];
				const bool force_blueprint = item["ForceBlueprint"];
				QString blueprint = QString::fromStdString(item["Blueprint"]);
				bool gudingshuxing = item.value("isfix", loadjson["General"].value("isfix", true));
				gudingshuxing = item.value("Fixed", loadjson["General"].value("Fixed", gudingshuxing));

				vipShopitems->addChild(CreatevipShopItems("item", QString::number(amount), QString::number(quality), blueprint, force_blueprint, gudingshuxing));
			}

			auto dinos_map = iter_value.value("Dinos", nlohmann::json::array());
			for (const auto& dino : dinos_map)
			{
				const int level = dino["Level"];
				const bool neutered = dino.value("Neutered", false);
				QString blueprint = QString::fromStdString(dino["Blueprint"]);

				vipShopitems->addChild(CreatevipShopDinos("Dinos", "", QString::number(level), blueprint, "", false));
			}

			const int points_map = iter_value.value("Points", 0);
			if (points_map > 0)
			{
				vipShopitems->addChild(CreatevipShopItems("Points", QString::number(points_map), "", "", false, false));
			}
		}

	}
}


void QtTBroShop::savevipShopconfig()
{
	int vipShopnum = ui.vipShoptreeWidget->topLevelItemCount();
	for (int i = 0; i < vipShopnum; i++)
	{
		QTreeWidgetItem* vipShop = ui.vipShoptreeWidget->topLevelItem(i);
		QString vipShopid = vipShop->text(0);
		savejson["vipShopItems"][vipShopid.toStdString()]["Type"] = vipShop->text(1).toStdString();
		savejson["vipShopItems"][vipShopid.toStdString()]["Price"] = vipShop->text(2).toInt();
		savejson["vipShopItems"][vipShopid.toStdString()]["Description"] = vipShop->text(3).toStdString();
		if (vipShop->text(5).toStdString() != "")
		savejson["vipShopItems"][vipShopid.toStdString()]["Permissions"] = vipShop->text(5).toStdString();
		if (vipShop->text(1) == "item" && vipShop->text(4) != "")
		{
			savejson["vipShopItems"][vipShopid.toStdString()]["MaxAmount"] = vipShop->text(4).toInt();
		}
		if (vipShop->text(1) == "item" || vipShop->text(1) == "dino")
		{
			int it = 0;
			for (int j = 0; j < vipShop->childCount(); j++)
			{
				QTreeWidgetItem* vipShopitem = vipShop->child(j);
				if (vipShopitem->text(0) == "Items")
				{
					savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["Amount"] = vipShopitem->text(1).toInt();
					savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["Quality"] = vipShopitem->text(2).toFloat();
					savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["Blueprint"] = getblu(vipShopitem->text(3).toStdString());
					if (vipShopitem->checkState(4) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["ForceBlueprint"] = true;
					}
					else if (vipShopitem->checkState(4) == Qt::CheckState::Unchecked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["ForceBlueprint"] = false;
					}
					if (vipShopitem->checkState(5) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["Fixed"] = true;
					}
					else if (vipShopitem->checkState(5) == Qt::CheckState::Unchecked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()]["Items"][it]["Fixed"] = false;
					}
					it++;
				}
				else
				{
					savejson["vipShopItems"][vipShopid.toStdString()]["Blueprint"] = getblu(vipShopitem->text(3).toStdString());
					savejson["vipShopItems"][vipShopid.toStdString()]["Level"] = vipShopitem->text(2).toInt();
					if (vipShopitem->text(4).toDouble() > 0)
					savejson["vipShopItems"][vipShopid.toStdString()]["HealthBase"] = vipShopitem->text(4).toFloat();
					if (vipShopitem->checkState(5) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()]["Neutered"] = true;
					}
				}
			}
		}
		if (vipShop->text(1) == "beacon")
		{
			savejson["vipShopItems"][vipShopid.toStdString()]["ClassName"] = vipShop->text(4).toStdString();
		}
		if (vipShop->text(1) == "experience")
		{
			savejson["vipShopItems"][vipShopid.toStdString()]["Amount"] = vipShop->child(0)->text(2).toFloat();
			if (vipShop->child(0)->checkState(4) == Qt::CheckState::Checked)
			{
				savejson["vipShopItems"][vipShopid.toStdString()]["GiveToDino"] = true;
			}
			else if (vipShop->child(0)->checkState(4) == Qt::CheckState::Unchecked)
			{
				savejson["vipShopItems"][vipShopid.toStdString()]["GiveToDino"] = false;
			}
		}
		if (vipShop->text(1) == "unlockengram")
		{
			for (int j = 0; j < vipShop->childCount(); j++)
			{
				QTreeWidgetItem* vipShopitem = vipShop->child(j);
				savejson["vipShopItems"][vipShopid.toStdString()]["Items"][j]["Blueprint"] = getblu(vipShopitem->text(3).toStdString());
			}
		}
		if (vipShop->text(1) == "command")
		{
			for (int j = 0; j < vipShop->childCount(); j++)
			{
				QTreeWidgetItem* vipShopitem = vipShop->child(j);
				savejson["vipShopItems"][vipShopid.toStdString()]["Items"][j]["Command"] = vipShopitem->text(3).toStdString();
			}
		}
		if (vipShop->text(1) == "vip")
		{
			savejson["vipShopItems"][vipShopid.toStdString()]["newvip"] = vipShop->text(4).toStdString();

			int di = 0;
			int it = 0;
			for (int j = 0; j < vipShop->childCount(); j++)
			{
				QTreeWidgetItem* vipShopvip = vipShop->child(j);
				if (vipShopvip->text(0) == "Dinos")
				{
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][di]["Level"] = vipShopvip->text(2).toInt();
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][di]["Blueprint"] = getblu(vipShopvip->text(3).toStdString());
					if (vipShopvip->checkState(4) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][di]["Neutered"] = true;
					}
					di++;
				}

				if (vipShopvip->text(0) == "Items")
				{
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["Amount"] = vipShopvip->text(1).toInt();
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["Quality"] = vipShopvip->text(2).toFloat();
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["Blueprint"] = getblu(vipShopvip->text(3).toStdString());
					if (vipShopvip->checkState(4) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["ForceBlueprint"] = true;
					}
					else if (vipShopvip->checkState(4) == Qt::CheckState::Unchecked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["ForceBlueprint"] = false;
					}
					if (vipShopvip->checkState(5) == Qt::CheckState::Checked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["Fixed"] = true;
					}
					else if (vipShopvip->checkState(5) == Qt::CheckState::Unchecked)
					{
						savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()][it]["Fixed"] = false;
					}
					it++;
				}


				if (vipShopvip->text(0) == "Points")
				{
					savejson["vipShopItems"][vipShopid.toStdString()][vipShopvip->text(0).toStdString()] = vipShopvip->text(1).toInt();
				}
			}
		}



	}
}