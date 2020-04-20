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
			itemitems->setText(4, QString::fromLocal8Bit("��Ҫ�̶�������������ֵ"));
		else
			itemitems->setText(4, healthbase);
		itemitems->setText(5, QString::fromLocal8Bit("�Ƿ����"));
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
		itemitems->setText(4, QString::fromLocal8Bit("�Ƿ�Ϊͼֽ"));
		itemitems->setText(5, QString::fromLocal8Bit("�̶�����Ʒ��"));

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
	CreateTopKits("ID", QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�۸�"), QString::fromLocal8Bit("�����ʾ��"),false,"")->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false,false));
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
	//sListHeader << QString::fromLocal8Bit("���ID/����") << QString::fromLocal8Bit("�������/��Ʒ����") << QString::fromLocal8Bit("����۸�/Ʒ��") << QString::fromLocal8Bit("�����/��ͼ����") << QString::fromLocal8Bit("�Ƿ�ֻ�ܸ���ʱ��ȡ"); 
	//ui.KitstreeWidget->setHeaderLabels(sListHeader);

	QTreeWidgetItem* item = CreateTopKits("ID", QString::fromLocal8Bit("����ȡ����"), QString::fromLocal8Bit("�۸�"), QString::fromLocal8Bit("�����ʾ��"), false, "");

	item->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false,false));
	item->addChild(CreateKitsDinos("Dinos", "", "225", QString::fromLocal8Bit("��ͼ����"),"",false));
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
		QAction DelWell(QString::fromLocal8Bit("&ɾ��"), this);
		connect(&DelWell, SIGNAL(triggered()), this, SLOT(KitsDelWell())); 
		QPoint pos;
		QMenu menu(ui.KitstreeWidget);
		menu.addAction(&DelWell);
		menu.exec(QCursor::pos());  //�ڵ�ǰ���λ����ʾ
		return;
	}
	QAction AdditemsWell(QString::fromLocal8Bit("&�½���Ʒ"), this);
	QAction AdddinosWell(QString::fromLocal8Bit("&�½�����"), this);
	QAction AddpointsWell(QString::fromLocal8Bit("&�½����"), this);
	QAction DelWell(QString::fromLocal8Bit("&ɾ��"), this);
	//�ڽ�����ɾ����item
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
	menu.exec(QCursor::pos());  //�ڵ�ǰ���λ����ʾ
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
	curItem->addChild(CreateKitsItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false,false));
}

void QtTBroShop::KitsAddDinos()
{
	QTreeWidgetItem* curItem = ui.KitstreeWidget->currentItem();
		curItem->addChild(CreateKitsDinos("Dinos", "", "225", QString::fromLocal8Bit("��ͼ����"), "",false));
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
	//	//����и��ڵ��Ҫ�ø��ڵ��takeChildɾ���ڵ�
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