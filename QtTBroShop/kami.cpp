#include "QtTBroShop.h"

void QtTBroShop::Removekami()
{
	int cout = ui.kamitreeWidget->topLevelItemCount();
	ui.kamitreeWidget->takeTopLevelItem(cout - 1);
}

QTreeWidgetItem* QtTBroShop::CreatekamiDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();

	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);

	if (type == "Dinos")
	{
		if (healthbase == "")
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
QTreeWidgetItem* QtTBroShop::CreatekamiItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed)
{
	QTreeWidgetItem* itemitems = new QTreeWidgetItem();

	itemitems->setText(0, type);
	itemitems->setText(1, amount);
	itemitems->setText(2, leave);
	itemitems->setText(3, bluph);
	if (type == "Items")
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

QTreeWidgetItem* QtTBroShop::CreateTopkami(QString id, QString amount, QString price, QString name, bool isdefkit, QString vip)
{

	QTreeWidgetItem* item = new QTreeWidgetItem();
	item->setText(0, id);
	item->setText(1, amount);
	item->setText(2, price);
	item->setText(3, name);
	
	item->setFlags(item->flags() | Qt::ItemIsEditable);

	item->setText(5, vip);

	item->setBackgroundColor(0, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(1, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(2, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(3, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(4, QColorConstants::Svg::lightcyan);
	item->setBackgroundColor(5, QColorConstants::Svg::lightcyan);
	ui.kamitreeWidget->addTopLevelItem(item);
	return item;
}

void QtTBroShop::AddTopkami()
{
	CreateTopkami("ID", QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�۸�"), QString::fromLocal8Bit("�����ʾ��"), false, "")->addChild(CreatekamiItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false, true));
}

void QtTBroShop::kamidef()
{
	//ui.kamitreeWidget->setColumnCount(5);
	ui.kamitreeWidget->setColumnWidth(0, 120);
	ui.kamitreeWidget->setColumnWidth(1, 100);
	ui.kamitreeWidget->setColumnWidth(2, 120);
	ui.kamitreeWidget->setColumnWidth(3, 660);
	ui.kamitreeWidget->setColumnWidth(4, 300);
	ui.kamitreeWidget->setColumnWidth(5, 130);
	//QStringList sListHeader;
	//sListHeader << QString::fromLocal8Bit("���ID/����") << QString::fromLocal8Bit("�������/��Ʒ����") << QString::fromLocal8Bit("����۸�/Ʒ��") << QString::fromLocal8Bit("�����/��ͼ����") << QString::fromLocal8Bit("�Ƿ�ֻ�ܸ���ʱ��ȡ"); 
	//ui.kamitreeWidget->setHeaderLabels(sListHeader);

	QTreeWidgetItem* item = CreateTopkami("ID", "","", "", false, "");

	item->addChild(CreatekamiItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false, true));
	item->addChild(CreatekamiDinos("Dinos", "", "225", QString::fromLocal8Bit("��ͼ����"), "", false));
	item->addChild(CreatekamiItems("Points", "1000", "", "", false, false));

	ui.kamitreeWidget->addTopLevelItem(item);

	ui.kamitreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.kamitreeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(sltkamiPopMenu(const QPoint&)));

	connect(ui.kamiopenallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::openallkami);
	connect(ui.kamicloseallgroupbutton, &QPushButton::clicked, this, &QtTBroShop::closeallkami);

	connect(ui.kamiaddgroupbutton, &QPushButton::clicked, this, &QtTBroShop::AddTopkami);
	connect(ui.kamiremovegroupbutton, &QPushButton::clicked, this, &QtTBroShop::Removekami);

}
void QtTBroShop::sltkamiPopMenu(const QPoint&)
{
	QTreeWidgetItem* curItem = ui.kamitreeWidget->currentItem();
	QTreeWidgetItem* parent = curItem->parent();
	if (curItem == NULL)
		return;

	if (parent)
	{
		QAction DelWell(QString::fromLocal8Bit("&ɾ��"), this);
		connect(&DelWell, SIGNAL(triggered()), this, SLOT(kamiDelWell()));
		QPoint pos;
		QMenu menu(ui.kamitreeWidget);
		menu.addAction(&DelWell);
		menu.exec(QCursor::pos());  //�ڵ�ǰ���λ����ʾ
		return;
	}
	QAction AdditemsWell(QString::fromLocal8Bit("&�½���Ʒ"), this);
	QAction AdddinosWell(QString::fromLocal8Bit("&�½�����"), this);
	QAction AddpointsWell(QString::fromLocal8Bit("&�½����"), this);
	QAction DelWell(QString::fromLocal8Bit("&ɾ��"), this);
	//�ڽ�����ɾ����item
	connect(&AdditemsWell, SIGNAL(triggered()), this, SLOT(kamiAddItem()));
	connect(&AdddinosWell, SIGNAL(triggered()), this, SLOT(kamiAddDinos()));
	connect(&AddpointsWell, SIGNAL(triggered()), this, SLOT(kamiAddPoints()));
	connect(&DelWell, SIGNAL(triggered()), this, SLOT(kamiDelWell()));

	QPoint pos;
	QMenu menu(ui.kamitreeWidget);
	menu.addAction(&AdditemsWell);
	menu.addAction(&AdddinosWell);
	menu.addAction(&AddpointsWell);
	menu.addAction(&DelWell);
	menu.exec(QCursor::pos());  //�ڵ�ǰ���λ����ʾ
}
void QtTBroShop::openallkami()
{
	ui.kamitreeWidget->expandAll();
	//ui.kamitreeWidget->collapseAll();
}

void QtTBroShop::closeallkami()
{
	//ui.kamitreeWidget->expandAll();
	ui.kamitreeWidget->collapseAll();
}
void QtTBroShop::kamiAddItem()
{
	QTreeWidgetItem* curItem = ui.kamitreeWidget->currentItem();
	curItem->addChild(CreatekamiItems("Items", "1", "0", QString::fromLocal8Bit("��ͼ����"), false, true));
}

void QtTBroShop::kamiAddDinos()
{
	QTreeWidgetItem* curItem = ui.kamitreeWidget->currentItem();
	curItem->addChild(CreatekamiDinos("Dinos", "", "225", QString::fromLocal8Bit("��ͼ����"), "", false));
}
void QtTBroShop::kamiAddPoints()
{
	QTreeWidgetItem* curItem = ui.kamitreeWidget->currentItem();
	curItem->addChild(CreatekamiItems("Points", "1000", "", "", false, false));
}
void QtTBroShop::kamiDelWell()
{
	//if (ui.kamitreeWidget->currentItem()->parent() == NULL)
	//{
	//	delete ui.kamitreeWidget->takeTopLevelItem(ui.kamitreeWidget->currentIndex().row());
	//}
	//else
	//{
	//	//����и��ڵ��Ҫ�ø��ڵ��takeChildɾ���ڵ�
	//	delete ui.kamitreeWidget->currentItem()->parent()->takeChild(ui.kamitreeWidget->currentIndex().row());
	//}
	QTreeWidgetItem* curItem = ui.kamitreeWidget->currentItem();
	curItem->~QTreeWidgetItem();
}




void QtTBroShop::loadkamiconfig()
{
	const int kitnum = ui.kamitreeWidget->topLevelItemCount();
	for (int i = 0; i < kitnum; i++)
		ui.kamitreeWidget->takeTopLevelItem(0);
	if (loadjson["kami"].empty())
		return;
	ui.nokami->setText(QString::fromStdString(loadjson["kami"].value("nokami","û�п���")));
	ui.kamivipmessage->setText(QString::fromStdString(loadjson["kami"].value("vipmessage", "��ɹ���ֵ{}��Ա")));
	ui.havevipmessage->setText(QString::fromStdString(loadjson["kami"].value("havevipmessage", "���Ѿ���{}��Ա���ܳ�ֵ")));
	ui.vippointsmessage->setText(QString::fromStdString(loadjson["kami"].value("vippointsmessage", "�ɹ���ֵ{}��ȯ")));
	ui.pointsmessage->setText(QString::fromStdString(loadjson["kami"].value("pointsmessage", "�ɹ���ֵ{}���")));
	ui.kamiCmd->setText(QString::fromStdString(loadjson["kami"].value("kamiCmd", "/cz")));
	ui.kamiCmd1->setText(QString::fromStdString(loadjson["kami"].value("kamiCmd1", "/��ֵ")));
	ui.kamiCmd2->setText(QString::fromStdString(loadjson["kami"].value("kamiCmd2", "/recharge")));
	ui.kamiPathOverride->setText(QString::fromStdString(loadjson["kami"].value("kamiPathOverride", "")));
	ui.kamilogpath->setText(QString::fromStdString(loadjson["kami"].value("kamilogpath", "")));
	
	auto kami_map = loadjson["kami"]["Kits"];
	for (auto iter = kami_map.begin(); iter != kami_map.end(); ++iter)
	{
		const QString id = QString::fromStdString(iter.key());

		auto iter_value = iter.value();

		QTreeWidgetItem* kititems = CreateTopkami(id, "","", "", false, "");

		auto items_map = iter_value.value("Items", nlohmann::json::array());
		for (const auto& item : items_map)
		{
			const int amount = item["Amount"];
			const float quality = item["Quality"];
			const bool force_blueprint = item["ForceBlueprint"];
			QString blueprint = QString::fromStdString(item["Blueprint"]);
			bool gudingshuxing = item.value("Fixed", loadjson["General"].value("Fixed", true));
			gudingshuxing = item.value("isfix", loadjson["General"].value("isfix", gudingshuxing));


			kititems->addChild(CreatekamiItems("Items", QString::number(amount), QString::number(quality), blueprint, force_blueprint, gudingshuxing));
		}

		auto dinos_map = iter_value.value("Dinos", nlohmann::json::array());
		for (const auto& dino : dinos_map)
		{
			const int level = dino["Level"];
			const bool neutered = dino.value("Neutered", false);
			QString blueprint = QString::fromStdString(dino["Blueprint"]);
			QString healthbase = "";
			const float HealthBase = dino.value("HealthBase", 0.0);
			if (HealthBase > 0)
			{
				healthbase = QString::number(HealthBase);
			}
			kititems->addChild(CreatekamiDinos("Dinos", "", QString::number(level), blueprint, healthbase, neutered));
		}

		const int points_map = iter_value.value("Points", 0);
		if (points_map > 0)
		{
			kititems->addChild(CreatekamiItems("Points", QString::number(points_map), "", "", false, false));
		}
	}
}



void QtTBroShop::savekamiconfig()
{
	savejson["kami"]["nokami"] = ui.nokami->toPlainText().toStdString();
	savejson["kami"]["vipmessage"] = ui.kamivipmessage->toPlainText().toStdString();
	savejson["kami"]["havevipmessage"] = ui.havevipmessage->toPlainText().toStdString();
	savejson["kami"]["vippointsmessage"] = ui.vippointsmessage->toPlainText().toStdString();
	savejson["kami"]["pointsmessage"] = ui.pointsmessage->toPlainText().toStdString();
	savejson["kami"]["kamiCmd"] = ui.kamiCmd->toPlainText().toStdString();
	savejson["kami"]["kamiCmd1"] = ui.kamiCmd1->toPlainText().toStdString();
	savejson["kami"]["kamiCmd2"] = ui.kamiCmd2->toPlainText().toStdString();
	savejson["kami"]["kamiPathOverride"] = ui.kamiPathOverride->toPlainText().toStdString();
	savejson["kami"]["kamilogpath"] = ui.kamilogpath->toPlainText().toStdString();

	int kitnum = ui.kamitreeWidget->topLevelItemCount();
	for (int i = 0; i < kitnum; i++)
	{
		QTreeWidgetItem* kit = ui.kamitreeWidget->topLevelItem(i);
		QString kitid = kit->text(0);
		int di = 0;
		int it = 0;
		for (int j = 0; j < kit->childCount(); j++)
		{
			QTreeWidgetItem* kititem = kit->child(j);
			if (kititem->text(0) == "Dinos")
			{
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Level"] = kititem->text(2).toInt();
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Blueprint"] = getblu(kititem->text(3).toStdString());
				if (kititem->text(4).toDouble() > 0)
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["HealthBase"] = kititem->text(4).toDouble();
				if (kititem->checkState(5) == Qt::CheckState::Checked)
				{
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][di]["Neutered"] = true;
				}
				di++;
			}

			if (kititem->text(0) == "Items")
			{
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Amount"] = kititem->text(1).toInt();
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Quality"] = kititem->text(2).toDouble();
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Blueprint"] = getblu(kititem->text(3).toStdString());
				if (kititem->checkState(4) == Qt::CheckState::Checked)
				{
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["ForceBlueprint"] = true;
				}
				else if (kititem->checkState(4) == Qt::CheckState::Unchecked)
				{
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["ForceBlueprint"] = false;
				}
				if (kititem->checkState(5) == Qt::CheckState::Checked)
				{
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Fixed"] = true;
				}
				else if (kititem->checkState(5) == Qt::CheckState::Unchecked)
				{
					savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()][it]["Fixed"] = false;
				}
				it++;
			}


			if (kititem->text(0) == "Points")
			{
				savejson["kami"]["Kits"][kitid.toStdString()][kititem->text(0).toStdString()] = kititem->text(1).toInt();
			}
		}

	}
}