#pragma once

#include <QtWidgets/QWidget>
#include <QMenuBar>
#include "ui_QtTBroShop.h"
#include "json.hpp"
#include "yjsd.h"
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

	void generalcolorchange();

	//Kits
	void Kitsdef();

	//Shop
	void Shopdef();


	void vipShopdef();


	void kamidef();
private slots:

	//General
	void removegroup();
	void addgroup(QString vip, int points, int week, int sales);
	void addnewgroup();

	//Kits
	void sltKitsPopMenu(const QPoint&);

	void RemoveKits();
	QTreeWidgetItem* CreateKitsDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed);
	void AddTopKits();

	void KitsAddItem();
	void KitsAddDinos();
	void KitsAddPoints();
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


	//vipShop
	void sltvipShopPopMenu(const QPoint&);
	void vipShopupvip();
	void AddvipShopBeacon();
	void AddvipShopExperience();
	void AddvipShopCommand();
	void AddvipShopUnlockengram();
	void vipShopAddItem();
	void vipShopDelWell();
	void vipShopvipAddDinos();
	void vipShopvipAddPoints();
	void openallvipShops();
	void closeallvipShops();
	void AddvipShopItem();
	void AddvipShopDino();


	//kami

	void sltkamiPopMenu(const QPoint&);

	void Removekami();
	void AddTopkami();
	void openallkami();
	void closeallkami();
	void kamiAddItem();
	void kamiAddDinos();
	void kamiAddPoints();
	void kamiDelWell();
private:
	Ui::QtTBroShopClass ui;
	yjsd *sd;
	//General

	nlohmann::json loadjson;
	nlohmann::json savejson;
	nlohmann::json saveiniload;
	//Kits

	QTreeWidgetItem* CreateTopKits(QString id, QString amount, QString price, QString name, bool isdefkit, QString vip);
	QTreeWidgetItem* CreateKitsItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed);
	//Shop

	QTreeWidgetItem* CreateTopShops(QString id, QString type, QString price, QString name, QString maxtimeordino, QString Permissions);
	QTreeWidgetItem* CreateShopDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed);
	QTreeWidgetItem* CreateShopItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed);
	//vipShop

	QTreeWidgetItem* CreatevipShopDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed);

	QTreeWidgetItem* CreatevipShopItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed);
	QTreeWidgetItem* CreateTopvipShops(QString id, QString type, QString price, QString name, QString maxtimeordino, QString Permissions);
	QTreeWidgetItem* CreatekamiDinos(QString type, QString amount, QString leave, QString bluph, QString healthbase, bool Fixed);
	//kami
	QTreeWidgetItem* CreatekamiItems(QString type, QString amount, QString leave, QString bluph, bool isbluph, bool Fixed);
	QTreeWidgetItem* CreateTopkami(QString id, QString amount, QString price, QString name, bool isdefkit, QString vip);


	QTreeWidgetItem* CreateTopsell(QString id, QString amount, QString price, QString name, QString blup);


	void test();
	void Serversdef();
	void SaveRconCrossServerChat();
	void servercolorchange();
	void saveini();
	void openyjsd();
	void SaveiniLoad();
	QString read_ip_address();
	std::string getblu(std::string blu);
	void addnewserver(QString path, QString mapname, QString rconport);
	void saveall();
	void addserver();
	void removeserver();
	void openserverconfig();
	void openurl();
	void openqq();
	void clearfilelabel();
	//file
	void openfile();
	void savefile();
	void loadgeneralconfig();
	void savegeneralconfig();

	void loadkitsconfig();
	void savekitsconfig();

	void loadShopconfig();
	void saveShopconfig();

	void loadvipShopconfig();
	void savevipShopconfig();

	void loadkamiconfig();
	void savekamiconfig();

	void loadSuicideconfig();
	void saveSuicideconfig();

	void loadCommandconfig();
	void saveCommandconfig();

	void Messagedef();

	void loadMessageconfig();
	void saveMessageconfig();
	void loadLotteryconfig();
	void saveLotteryconfig();

	void selldef();
	void AddSellItem();
	void RemoveSellItem();
	void AddvipSellItem();
	void RemovevipSellItem();
	void loadSellItem();
	void loadvipSellItem();
	void saveSellconfig();
	void savevipSellconfig();
	void loadInvitationconfig();
	void saveInvitationconfig();
	void CrossChatsdef();
	void addnewceosschat(QString path, QString mapname, QString rconport);
	void addcross();
	void removecross();
	void savecrossini();
};
