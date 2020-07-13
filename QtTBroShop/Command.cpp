#include "QtTBroShop.h"

void QtTBroShop::loadCommandconfig()
{
	ui.ShopCmd->setText(QString::fromStdString(loadjson["Messages"].value("ShopCmd",ui.ShopCmd->toPlainText().toStdString().c_str())));
	ui.KitCmd->setText(QString::fromStdString(loadjson["Messages"].value("KitCmd", ui.KitCmd->toPlainText().toStdString().c_str())));
	ui.PointsCmd->setText(QString::fromStdString(loadjson["Messages"].value("PointsCmd", ui.PointsCmd->toPlainText().toStdString().c_str())));
	ui.BuyCmd->setText(QString::fromStdString(loadjson["Messages"].value("BuyCmd", ui.BuyCmd->toPlainText().toStdString().c_str())));
	ui.TradeCmd->setText(QString::fromStdString(loadjson["Messages"].value("TradeCmd", ui.TradeCmd->toPlainText().toStdString().c_str())));
	ui.BuyKitCmd->setText(QString::fromStdString(loadjson["Messages"].value("BuyKitCmd", ui.BuyKitCmd->toPlainText().toStdString().c_str())));
	ui.SellCmd->setText(QString::fromStdString(loadjson["Messages"].value("SellCmd", ui.SellCmd->toPlainText().toStdString().c_str())));
	ui.ShopSellCmd->setText(QString::fromStdString(loadjson["Messages"].value("ShopSellCmd", ui.ShopSellCmd->toPlainText().toStdString().c_str())));
	ui.HelpCmd->setText(QString::fromStdString(loadjson["Messages"].value("HelpCmd", ui.HelpCmd->toPlainText().toStdString().c_str())));
}

void QtTBroShop::saveCommandconfig()
{
	savejson["Messages"]["ShopCmd"] = ui.ShopCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["PointsCmd"] = ui.PointsCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["TradeCmd"] = ui.TradeCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyCmd"] = ui.BuyCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["KitCmd"] = ui.KitCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyKitCmd"] = ui.BuyKitCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["SellCmd"] = ui.SellCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopSellCmd"] = ui.ShopSellCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["HelpCmd"] = ui.HelpCmd->toPlainText().toStdString().c_str();
}