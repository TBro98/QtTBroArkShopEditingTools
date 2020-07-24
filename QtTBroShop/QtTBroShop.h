#pragma once

#include <QtWidgets/QWidget>
#include <QMenuBar>
#include <QMessageBox>
#include "ui_QtTBroShop.h"
#include "json.hpp"
#include <QFile>
#include <fstream>
#include <qdir.h>
class QtTBroShop : public QWidget
{
	Q_OBJECT
public:

	QtTBroShop(QWidget *parent = Q_NULLPTR);

	//General
	void Generaldef();


	//Kits
	void Kitsdef();

	//Shop
	void Shopdef();

private slots:

	//General
	void removegroup();
	void addgroup(QString Permission, int Amount);
	void addnewgroup();

	//Kits
	void sltKitsPopMenu(const QPoint&);

	void RemoveKits();
	QTreeWidgetItem* CreateKitsDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Neutered);
	void AddTopKits();

	void KitsAddItem();
	void KitsAddDinos();
	void KitsDelWell();

	void openallKits();
	void closeallKits();


	//Shop
	void sltShopPopMenu(const QPoint&);
	void ShopAddItem();
	void ShopDelWell();

	void openallShops();
	void closeallShops();
	void AddShopItem();
	void AddShopDino();

	void AddShopBeacon();

	void AddShopExperience();

	void AddShopCommand();

	void AddShopUnlockengram();

private:
	Ui::QtTBroShopClass ui;
	//General

	nlohmann::json loadjson;
	nlohmann::json Permissionsjson;
	nlohmann::json savejson;
	nlohmann::json saveiniload;
	//Kits

	QTreeWidgetItem* CreateTopKits(QString id, QString amount, QString price, QString name, bool OnlyFromSpawn, QString vip);
	QTreeWidgetItem* CreateKitsItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool ForceBlueprint);
	//Shop

	QTreeWidgetItem* CreateTopShops(QString id, QString type, QString price, QString name, QString maxtimeordino, QString Permissions);
	QTreeWidgetItem* CreateShopDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed);
	QTreeWidgetItem* CreateShopItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed);


	QTreeWidgetItem* CreateTopsell(QString id, QString amount, QString price, QString name, QString blup);


	void Serversdef();
	void saveini();
	void chooseconfigfile();
	void LoadJson(QString filepath);
	void SaveiniLoad();
	QString read_ip_address();
	std::string getblu(std::string blu);
	void addnewserver(QString path, QString mapname, QString rconport);
	void saveall();
	void addserver();
	void removeserver();
	void openserverconfig();
	void clearfilelabel();
	//file
	void openfile(QString filepath);
	void savefile();
	void loadgeneralconfig();
	void savegeneralconfig();

	void loadkitsconfig();
	void savekitsconfig();

	void loadShopconfig();
	void saveShopconfig();


	void loadCommandconfig();
	void saveCommandconfig();

	void Messagedef();

	void loadMessageconfig();
	void saveMessageconfig();

	void selldef();
	void AddSellItem();
	void RemoveSellItem();
	void loadSellItem();
	void saveSellconfig();
};
