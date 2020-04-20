#include "QtTBroShop.h"

void QtTBroShop::RemoveKits()
{
	int cout = ui.KitstreeWidget->topLevelItemCount();
	ui.KitstreeWidget->takeTopLevelItem(cout-1);
}
QTreeWidgetItem* QtTBroShop::CreateKitsDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();

	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);

	if (type == "Dinos")
	{
		if(healthbase=="")
			itemitems->setText(4, QString::fromLocal8Bit("如要固定属性则设置数值"));
		else
			itemitems->setText(4, healthbase);
		itemitems->setText(5, QString::fromLocal8Bit("是否绝育"));
		if (Fixed)
			itemitems->setCheckState(5, Qt::CheckState::Checked);
		else
			itemitems->setCheckState(5, Qt::CheckState::Unchecked);
	}
	itemitems->setFlags(itemitems->flags() | Qt::ItemIsEditable);
	return itemitems;
}
QTreeWidgetItem* QtTBroShop::CreateKitsItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();

	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	if(type=="Items")
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

QTreeWidgetItem* QtTBroShop::CreateTopKits(QString id, QString amount, QString price, QString name, bool isdefkit,QString vip)
{

	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, id);
	item->setText(1, amount);
	item->setText(2, price);
	item->setText(3, name);
	if(isdefkit)
		item->setCheckState(4, Qt::CheckState::Checked);
	else
		item->setCheckState(4, Qt::CheckState::Unchecked);

	item->setFlags(item->flags() | Qt::ItemIsEditable);

	item->setText(5, vip);

	item->setBackgroundColor(0, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(1, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(2, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(3, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(4, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(5, QColorConstants::Svg::lightcyan);
	ui.KitstreeWidget->addTopLevelItem(item);
	return item;
}

void QtTBroShop::AddTopKits()
{
	CreateTopKits("ID", QString::fromLocal8Bit("数量"), QString::fromLocal8Bit("价格"), QString::fromLocal8Bit("礼包显示名"),false,"")->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("蓝图代码"), false,false));
}

void QtTBroShop::Kitsdef()
{
	//ui.KitstreeWidget->setColumnCount(5);
	ui.KitstreeWidget->setColumnWidth(0, 120);
	ui.KitstreeWidget->setColumnWidth(1, 100);
	ui.KitstreeWidget->setColumnWidth(2, 120);
	ui.KitstreeWidget->setColumnWidth(3, 660);
	ui.KitstreeWidget->setColumnWidth(4, 300);
	ui.KitstreeWidget->setColumnWidth(5, 130);
	//QStringList sListHeader;
	//sListHeader << QString::fromLocal8Bit("礼包ID/类型") << QString::fromLocal8Bit("礼包数量/物品数量") << QString::fromLocal8Bit("购买价格/品质") << QString::fromLocal8Bit("礼包名/蓝图代码") << QString::fromLocal8Bit("是否只能复活时获取"); 
	//ui.KitstreeWidget->setHeaderLabels(sListHeader);

	QTreeWidgetItem* item = CreateTopKits("ID", QString::fromLocal8Bit("可领取数量"), QString::fromLocal8Bit("价格"), QString::fromLocal8Bit("礼包显示名"), false, "");

	item->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("蓝图代码"), false,false));
	item->addChild(CreateKitsDinos("Dinos", "", "225", QString::fromLocal8Bit("蓝图代码"),"",false));
	item->addChild(CreateKitsItems("Points","1000","","",false,false));

	ui.KitstreeWidget->addTopLevelItem(item);

	ui.KitstreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.KitstreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sltKitsPopMenu(const QPoint&)));

	connect(ui.Kitsopenallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::openallKits);
	connect(ui.Kitscloseallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::closeallKits);

	connect(ui.Kitsaddgroupbutton, &QPushButton::clicked, this, &QtTBroShop::AddTopKits);
	connect(ui.Kitsremovegroupbutton, &QPushButton::clicked, this, &QtTBroShop::RemoveKits);

}
void QtTBroShop::sltKitsPopMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
	QTreeWidgetItem* parent = curItem->parent();
	if (curItem == NULL)
		return;

	if (parent)
	{
		QAction DelWell(QString::fromLocal8Bit("&删除"), this);
		connect(&DelWell, SIGNAL(triggered()), this, SLOT(KitsDelWell())); 
		QPoint pos;
		QMenu menu(ui.KitstreeWidget);
		menu.addAction(&DelWell);
		menu.exec(QCursor::pos());  //在当前鼠标位置显示
		return;
	}
	QAction AdditemsWell(QString::fromLocal8Bit("&新建物品"), this);
	QAction AdddinosWell(QString::fromLocal8Bit("&新建恐龙"), this);
	QAction AddpointsWell(QString::fromLocal8Bit("&新建金币"), this);
	QAction DelWell(QString::fromLocal8Bit("&删除"), this);
	//在界面上删除该item
	connect(&AdditemsWell, SIGNAL(triggered()), this, SLOT(KitsAddItem()));
	connect(&AdddinosWell, SIGNAL(triggered()), this, SLOT(KitsAddDinos()));
	connect(&AddpointsWell, SIGNAL(triggered()), this, SLOT(KitsAddPoints()));
	connect(&DelWell, SIGNAL(triggered()), this, SLOT(KitsDelWell()));

	QPoint pos;
	QMenu menu(ui.KitstreeWidget);
	menu.addAction(&AdditemsWell);
	menu.addAction(&AdddinosWell);
	menu.addAction(&AddpointsWell);
	menu.addAction(&DelWell);
	menu.exec(QCursor::pos());  //在当前鼠标位置显示
}
void QtTBroShop::openallKits()
{
	ui.KitstreeWidget->expandAll();
	//ui.KitstreeWidget->collapseAll();
}

void QtTBroShop::closeallKits()
{
	//ui.KitstreeWidget->expandAll();
	ui.KitstreeWidget->collapseAll();
}
void QtTBroShop::KitsAddItem()
{
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
	curItem->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("蓝图代码"), false,false));
}

void QtTBroShop::KitsAddDinos()
{
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
		curItem->addChild(CreateKitsDinos("Dinos", "", "225", QString::fromLocal8Bit("蓝图代码"), "",false));
}
void QtTBroShop::KitsAddPoints()
{
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
	curItem->addChild(CreateKitsItems("Points", "1000", "", "", false,false));
}
void QtTBroShop::KitsDelWell()
{
	//if (ui.KitstreeWidget->currentItem()->parent() == NULL)
	//{
	//	delete ui.KitstreeWidget->takeTopLevelItem(ui.KitstreeWidget->currentIndex().row());
	//}
	//else
	//{
	//	//如果有父节点就要用父节点的takeChild删除节点
	//	delete ui.KitstreeWidget->currentItem()->parent()->takeChild(ui.KitstreeWidget->currentIndex().row());
	//}
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
	curItem->~QTreeWidgetItem();
}




void QtTBroShop::loadkitsconfig()
{
	if (loadjson["Kits"].empty())
		return;
	ui.DefaultKit->setText(QString::fromStdString(loadjson["General"]["DefaultKit"]));
	const bool KitsShowWithoutPermission = loadjson["General"].value("KitsShowWithoutPermission",false);
	ui.KitsShowWithoutPermission->setChecked(KitsShowWithoutPermission);
	const int kitnum = ui.KitstreeWidget->topLevelItemCount();
	for (int i = 0; i < kitnum; i++)
		ui.KitstreeWidget->takeTopLevelItem(0);
	auto kits_map = loadjson["Kits"];
	for (auto iter = kits_map.begin(); iter != kits_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();

		const int price = iter_value.value("Price", 0);
		const int DefaultAmount = iter_value.value("DefaultAmount", 1);
		const bool OnlyFromSpawn = iter_value.value("OnlyFromSpawn",false);
		const QString Description = QString::fromStdString(iter_value.value("Description",""));
		const QString vip = QString::fromStdString(iter_value.value("Permissions",""));

		QTreeWidgetItem* kititems= CreateTopKits(id, QString::number(DefaultAmount), QString::number(price), Description, OnlyFromSpawn, vip);

		auto items_map = iter_value.value("Items", nlohmann::json::array());
		for (const auto& item : items_map)
		{
			const int amount = item["Amount"];
			const float quality = item["Quality"];
			const bool force_blueprint = item["ForceBlueprint"];
			QString blueprint = QString::fromStdString(item["Blueprint"]);
			bool gudingshuxing = item.value("isfix", loadjson["General"].value("isfix", true));
			gudingshuxing = item.value("Fixed", loadjson["General"].value("Fixed", gudingshuxing));


			kititems->addChild(CreateKitsItems("Items",QString::number(amount),QString::number(quality),blueprint, force_blueprint, gudingshuxing));
		}

		auto dinos_map = iter_value.value("Dinos", nlohmann::json::array());
		for (const auto& dino : dinos_map)
		{
			const int level = dino["Level"];
			const bool neutered = dino.value("Neutered", false);
			QString blueprint = QString::fromStdString(dino["Blueprint"]);
			QString healthbase ;
			double HealthBase = dino.value("HealthBase", 0.0);
			if (HealthBase > 0)
			{
				healthbase = QString::number(HealthBase);
			}
			kititems->addChild(CreateKitsDinos("Dinos", "", QString::number(level), blueprint, healthbase, neutered));
		}

		const int points_map = iter_value.value("Points", 0);
		if (points_map > 0)
		{
			kititems->addChild(CreateKitsItems("Points", QString::number(points_map), "", "", false,false));
		}
	}
}



void QtTBroShop::savekitsconfig()
{
	savejson["General"]["DefaultKit"] = ui.DefaultKit->toPlainText().toStdString();
	savejson["General"]["KitsShowWithoutPermission"] = ui.KitsShowWithoutPermission->isChecked();
	int kitnum=ui.KitstreeWidget->topLevelItemCount();
	for (int i = 0; i < kitnum; i++)
	{
		QTreeWidgetItem* kit = ui.KitstreeWidget->topLevelItem(i);
		QString kitid = kit->text(0);
		savejson["Kits"][kitid.toStdString()]["DefaultAmount"] = kit->text(1).toInt();
		savejson["Kits"][kitid.toStdString()]["Price"] = kit->text(2).toInt();
		savejson["Kits"][kitid.toStdString()]["Description"] = kit->text(3).toStdString();
		if (!kit->text(5).isEmpty())
		{
			savejson["Kits"][kitid.toStdString()]["Permissions"] = kit->text(5).toStdString();
		}
		if (kit->checkState(4) == Qt::CheckState::Checked)
		{
			savejson["Kits"][kitid.toStdString()]["OnlyFromSpawn"] = true;
		}
		int di = 0;
		int it = 0;
		for (int j=0;j< kit->childCount();j++)
		{
			QTreeWidgetItem* kititem=kit->child(j);
			if (kititem->text(0) == "Dinos")
			{
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Level"] = kititem->text(2).toInt();
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Blueprint"] = getblu(kititem->text(3).toStdString());
				if (kititem->text(4).toDouble() > 0)
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["HealthBase"] = kititem->text(4).toDouble();
				if (kititem->checkState(5) == Qt::CheckState::Checked)
				{
					savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Neutered"] = true;
				}
				di++;
			}

			if (kititem->text(0) == "Items")
			{
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Amount"] = kititem->text(1).toInt();
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Quality"] = kititem->text(2).toDouble();
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Blueprint"] = getblu(kititem->text(3).toStdString());
				if (kititem->checkState(4) == Qt::CheckState::Checked)
				{
					savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["ForceBlueprint"] = true;
				}
				else if (kititem->checkState(4) == Qt::CheckState::Unchecked)
				{
					savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["ForceBlueprint"] = false;
				}
				if (kititem->checkState(5) == Qt::CheckState::Checked)
				{
					savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Fixed"] = true;
				}
				else if(kititem->checkState(5) == Qt::CheckState::Unchecked)
				{
					savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Fixed"] = false;
				}
				it++;
			}


			if (kititem->text(0) == "Points")
			{
				savejson["Kits"][kitid.toStdString()][kititem->text(0).toStdString()] = kititem->text(1).toInt();
			}
		}

	}
}