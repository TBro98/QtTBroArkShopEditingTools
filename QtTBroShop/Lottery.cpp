#include "QtTBroShop.h"


void QtTBroShop::loadLotteryconfig()
{
	if (loadjson["Lottery"].empty())
		return;
	ui.LotteryCmd->setText(QString::fromStdString(loadjson["Lottery"].value("LotteryCmd", ui.LotteryCmd->toPlainText().toStdString().c_str())));
	ui.LotteryCmd1->setText(QString::fromStdString(loadjson["Lottery"].value("LotteryCmd1", ui.LotteryCmd1->toPlainText().toStdString().c_str())));
	ui.LotteryCmd2->setText(QString::fromStdString(loadjson["Lottery"].value("LotteryCmd2", ui.LotteryCmd2->toPlainText().toStdString().c_str())));
	ui.LotterySender->setText(QString::fromStdString(loadjson["Lottery"].value("Sender", ui.LotterySender->toPlainText().toStdString().c_str())));
	ui.NotLotteryList->setText(QString::fromStdString(loadjson["Lottery"].value("NotLotteryList", ui.NotLotteryList->toPlainText().toStdString().c_str())));
	ui.GetLottery->setText(QString::fromStdString(loadjson["Lottery"].value("GetLottery", ui.GetLottery->toPlainText().toStdString().c_str())));
	ui.LotteryNotice->setText(QString::fromStdString(loadjson["Lottery"].value("LotteryNotice", ui.LotteryNotice->toPlainText().toStdString().c_str())));

	ui.LotteryPoints->setValue(loadjson["Lottery"].value("LotteryPoints", 300));

	ui.EnableLottery->setChecked(loadjson["Lottery"].value("EnableLottery", ui.EnableLottery->isChecked()));
	ui.EnableNotice->setChecked(loadjson["Lottery"].value("EnableNotice", ui.EnableNotice->isChecked()));
	ui.ExperienceGiveToDino->setChecked(loadjson["Lottery"].value("ExperienceGiveToDino", ui.ExperienceGiveToDino->isChecked()));
	
	nlohmann::json default_color = { 0,255,0,255 };
	nlohmann::json color = loadjson["Lottery"].value("Color", default_color);
	ui.colora_2->setValue(color[0]);
	ui.colorb_2->setValue(color[1]);
	ui.colorc_2->setValue(color[2]);
	ui.colord_2->setValue(color[3]);
}

void QtTBroShop::saveLotteryconfig()
{
	savejson["Lottery"]["LotteryCmd"] = ui.LotteryCmd->toPlainText().toStdString().c_str();
	savejson["Lottery"]["LotteryCmd1"] = ui.LotteryCmd1->toPlainText().toStdString().c_str();
	savejson["Lottery"]["LotteryCmd2"] = ui.LotteryCmd2->toPlainText().toStdString().c_str();
	savejson["Lottery"]["Sender"] = ui.LotterySender->toPlainText().toStdString().c_str();
	savejson["Lottery"]["NotLotteryList"] = ui.NotLotteryList->toPlainText().toStdString().c_str();
	savejson["Lottery"]["GetLottery"] = ui.GetLottery->toPlainText().toStdString().c_str();
	savejson["Lottery"]["LotteryNotice"] = ui.LotteryNotice->toPlainText().toStdString().c_str();
	
	savejson["Lottery"]["EnableLottery"] = ui.EnableLottery->isChecked();
	savejson["Lottery"]["EnableNotice"] = ui.EnableNotice->isChecked();
	savejson["Lottery"]["ExperienceGiveToDino"] = ui.ExperienceGiveToDino->isChecked();

	savejson["Lottery"]["LotteryPoints"] = ui.LotteryPoints->value();
	nlohmann::json color;
	color[0] = ui.colora_2->value();
	color[1] = ui.colorb_2->value();
	color[2] = ui.colorc_2->value();
	color[3] = ui.colord_2->value();
	savejson["Lottery"]["Color"] = color;
}