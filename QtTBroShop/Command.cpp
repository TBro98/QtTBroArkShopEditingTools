#include "QtTBroShop.h"

void QtTBroShop::loadCommandconfig()
{
	ui.ShopCmd->setText(QString::fromStdString(loadjson["Messages"].value("ShopCmd",ui.ShopCmd->toPlainText().toStdString().c_str())));
	ui.ShopCmd1->setText(QString::fromStdString(loadjson["Messages"].value("ShopCmd1", ui.ShopCmd1->toPlainText().toStdString().c_str())));
	ui.ShopCmd2->setText(QString::fromStdString(loadjson["Messages"].value("ShopCmd2", ui.ShopCmd2->toPlainText().toStdString().c_str())));
	ui.KitCmd->setText(QString::fromStdString(loadjson["Messages"].value("KitCmd", ui.KitCmd->toPlainText().toStdString().c_str())));
	ui.KitCmd1->setText(QString::fromStdString(loadjson["Messages"].value("KitCmd1", ui.KitCmd1->toPlainText().toStdString().c_str())));
	ui.KitCmd2->setText(QString::fromStdString(loadjson["Messages"].value("KitCmd2", ui.KitCmd2->toPlainText().toStdString().c_str())));
	ui.PointsCmd->setText(QString::fromStdString(loadjson["Messages"].value("PointsCmd", ui.PointsCmd->toPlainText().toStdString().c_str())));
	ui.PointsCmd1->setText(QString::fromStdString(loadjson["Messages"].value("PointsCmd1", ui.PointsCmd1->toPlainText().toStdString().c_str())));
	ui.PointsCmd2->setText(QString::fromStdString(loadjson["Messages"].value("PointsCmd2", ui.PointsCmd2->toPlainText().toStdString().c_str())));
	ui.BuyCmd->setText(QString::fromStdString(loadjson["Messages"].value("BuyCmd", ui.BuyCmd->toPlainText().toStdString().c_str())));
	ui.BuyCmd1->setText(QString::fromStdString(loadjson["Messages"].value("BuyCmd1", ui.BuyCmd1->toPlainText().toStdString().c_str())));
	ui.BuyCmd2->setText(QString::fromStdString(loadjson["Messages"].value("BuyCmd2", ui.BuyCmd2->toPlainText().toStdString().c_str())));
	ui.TradeCmd->setText(QString::fromStdString(loadjson["Messages"].value("TradeCmd", ui.TradeCmd->toPlainText().toStdString().c_str())));
	ui.TradeCmd1->setText(QString::fromStdString(loadjson["Messages"].value("TradeCmd1", ui.TradeCmd1->toPlainText().toStdString().c_str())));
	ui.TradeCmd2->setText(QString::fromStdString(loadjson["Messages"].value("TradeCmd2", ui.TradeCmd2->toPlainText().toStdString().c_str())));
	ui.BuyKitCmd->setText(QString::fromStdString(loadjson["Messages"].value("BuyKitCmd", ui.BuyKitCmd->toPlainText().toStdString().c_str())));
	ui.BuyKitCmd1->setText(QString::fromStdString(loadjson["Messages"].value("BuyKitCmd1", ui.BuyKitCmd1->toPlainText().toStdString().c_str())));
	ui.BuyKitCmd2->setText(QString::fromStdString(loadjson["Messages"].value("BuyKitCmd2", ui.BuyKitCmd2->toPlainText().toStdString().c_str())));
	ui.SellCmd->setText(QString::fromStdString(loadjson["Messages"].value("SellCmd", ui.SellCmd->toPlainText().toStdString().c_str())));
	ui.SellCmd1->setText(QString::fromStdString(loadjson["Messages"].value("SellCmd1", ui.SellCmd1->toPlainText().toStdString().c_str())));
	ui.SellCmd2->setText(QString::fromStdString(loadjson["Messages"].value("SellCmd2", ui.SellCmd2->toPlainText().toStdString().c_str())));
	ui.ShopSellCmd->setText(QString::fromStdString(loadjson["Messages"].value("ShopSellCmd", ui.ShopSellCmd->toPlainText().toStdString().c_str())));
	ui.ShopSellCmd1->setText(QString::fromStdString(loadjson["Messages"].value("ShopSellCmd1", ui.ShopSellCmd1->toPlainText().toStdString().c_str())));
	ui.ShopSellCmd2->setText(QString::fromStdString(loadjson["Messages"].value("ShopSellCmd2", ui.ShopSellCmd2->toPlainText().toStdString().c_str())));
	ui.HelpCmd->setText(QString::fromStdString(loadjson["Messages"].value("HelpCmd", ui.HelpCmd->toPlainText().toStdString().c_str())));
	ui.HelpCmd1->setText(QString::fromStdString(loadjson["Messages"].value("HelpCmd1", ui.HelpCmd1->toPlainText().toStdString().c_str())));
	ui.HelpCmd2->setText(QString::fromStdString(loadjson["Messages"].value("HelpCmd2", ui.HelpCmd2->toPlainText().toStdString().c_str())));
	ui.tradeservice->setValue(loadjson["Messages"].value("tradeservice", 0));


	if (loadjson["vipMessages"].empty())
		return;
	ui.vipShopCmd->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopCmd", ui.vipShopCmd->toPlainText().toStdString().c_str())));
	ui.vipShopCmd1->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopCmd1", ui.vipShopCmd1->toPlainText().toStdString().c_str())));
	ui.vipShopCmd2->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopCmd2", ui.vipShopCmd2->toPlainText().toStdString().c_str())));
	ui.vipPointsCmd->setText(QString::fromStdString(loadjson["vipMessages"].value("PointsCmd", ui.vipPointsCmd->toPlainText().toStdString().c_str())));
	ui.vipPointsCmd1->setText(QString::fromStdString(loadjson["vipMessages"].value("PointsCmd1", ui.vipPointsCmd1->toPlainText().toStdString().c_str())));
	ui.vipPointsCmd2->setText(QString::fromStdString(loadjson["vipMessages"].value("PointsCmd2", ui.vipPointsCmd2->toPlainText().toStdString().c_str())));
	ui.exchangeCmd->setText(QString::fromStdString(loadjson["vipMessages"].value("exchangeCmd", ui.exchangeCmd->toPlainText().toStdString().c_str())));
	ui.exchangeCmd1->setText(QString::fromStdString(loadjson["vipMessages"].value("exchangeCmd1", ui.exchangeCmd1->toPlainText().toStdString().c_str())));
	ui.exchangeCmd2->setText(QString::fromStdString(loadjson["vipMessages"].value("exchangeCmd2", ui.exchangeCmd2->toPlainText().toStdString().c_str())));
	ui.vipSellCmd->setText(QString::fromStdString(loadjson["vipMessages"].value("SellCmd", ui.vipSellCmd->toPlainText().toStdString().c_str())));
	ui.vipSellCmd1->setText(QString::fromStdString(loadjson["vipMessages"].value("SellCmd1", ui.vipSellCmd1->toPlainText().toStdString().c_str())));
	ui.vipSellCmd2->setText(QString::fromStdString(loadjson["vipMessages"].value("SellCmd2", ui.vipSellCmd->toPlainText().toStdString().c_str())));
	ui.vipShopSellCmd->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopSellCmd", ui.vipShopSellCmd->toPlainText().toStdString().c_str())));
	ui.vipShopSellCmd1->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopSellCmd1", ui.vipShopSellCmd1->toPlainText().toStdString().c_str())));
	ui.vipShopSellCmd2->setText(QString::fromStdString(loadjson["vipMessages"].value("ShopSellCmd2", ui.vipShopSellCmd2->toPlainText().toStdString().c_str())));
	ui.exchangeRatio->setValue(loadjson["vipMessages"].value("exchangeRatio", 100));
}

void QtTBroShop::saveCommandconfig()
{
	savejson["Messages"]["ShopCmd"] = ui.ShopCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopCmd1"] = ui.ShopCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopCmd2"] = ui.ShopCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["PointsCmd"] = ui.PointsCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["PointsCmd1"] = ui.PointsCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["PointsCmd2"] = ui.PointsCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["TradeCmd"] = ui.TradeCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["TradeCmd1"] = ui.TradeCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["TradeCmd2"] = ui.TradeCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyCmd"] = ui.BuyCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyCmd1"] = ui.BuyCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyCmd2"] = ui.BuyCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["KitCmd"] = ui.KitCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["KitCmd1"] = ui.KitCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["KitCmd2"] = ui.KitCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyKitCmd"] = ui.BuyKitCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyKitCmd1"] = ui.BuyKitCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["BuyKitCmd2"] = ui.BuyKitCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["SellCmd"] = ui.SellCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["SellCmd1"] = ui.SellCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["SellCmd2"] = ui.SellCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopSellCmd"] = ui.ShopSellCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopSellCmd1"] = ui.ShopSellCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["ShopSellCmd2"] = ui.ShopSellCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["HelpCmd"] = ui.HelpCmd->toPlainText().toStdString().c_str();
	savejson["Messages"]["HelpCmd1"] = ui.HelpCmd1->toPlainText().toStdString().c_str();
	savejson["Messages"]["HelpCmd2"] = ui.HelpCmd2->toPlainText().toStdString().c_str();
	savejson["Messages"]["tradeservice"] = ui.tradeservice->value();

	savejson["vipMessages"]["ShopCmd"] = ui.vipShopCmd->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["ShopCmd1"] = ui.vipShopCmd1->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["ShopCmd2"] = ui.vipShopCmd2->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["PointsCmd"] = ui.vipPointsCmd->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["PointsCmd1"] = ui.vipPointsCmd1->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["PointsCmd2"] = ui.vipPointsCmd2->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["exchangeCmd"] = ui.exchangeCmd->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["exchangeCmd1"] = ui.exchangeCmd1->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["exchangeCmd2"] = ui.exchangeCmd2->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["SellCmd"] = ui.vipSellCmd->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["SellCmd1"] = ui.vipSellCmd1->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["SellCmd2"] = ui.vipSellCmd2->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["ShopSellCmd"] = ui.vipShopSellCmd->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["ShopSellCmd1"] = ui.vipShopSellCmd1->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["ShopSellCmd2"] = ui.vipShopSellCmd2->toPlainText().toStdString().c_str();
	savejson["vipMessages"]["exchangeRatio"] = ui.exchangeRatio->value();
}