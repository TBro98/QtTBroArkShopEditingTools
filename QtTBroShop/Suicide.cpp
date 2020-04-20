#include "QtTBroShop.h"

void QtTBroShop::loadSuicideconfig()
{
	if (loadjson["Suicide"].empty())
		return;
	ui.SuicideCMD->setText(QString::fromStdString(loadjson["Suicide"].value("SuicideCMD", ui.SuicideCMD->toPlainText().toStdString().c_str())));
	ui.SuicideCMD1->setText(QString::fromStdString(loadjson["Suicide"].value("SuicideCMD1", ui.SuicideCMD1->toPlainText().toStdString().c_str())));
	ui.SuicideCMD2->setText(QString::fromStdString(loadjson["Suicide"].value("SuicideCMD2", ui.SuicideCMD2->toPlainText().toStdString().c_str())));
	ui.SuicideSender->setText(QString::fromStdString(loadjson["Suicide"].value("Sender", ui.SuicideSender->toPlainText().toStdString().c_str())));
	ui.MsgDead->setText(QString::fromStdString(loadjson["Suicide"].value("MsgDead", ui.MsgDead->toPlainText().toStdString().c_str())));
	ui.MsgAlreadyDead->setText(QString::fromStdString(loadjson["Suicide"].value("MsgAlreadyDead", ui.MsgAlreadyDead->toPlainText().toStdString().c_str())));
	ui.MsgHandcuffs->setText(QString::fromStdString(loadjson["Suicide"].value("MsgHandcuffs", ui.MsgHandcuffs->toPlainText().toStdString().c_str())));
	ui.MsgOnDino->setText(QString::fromStdString(loadjson["Suicide"].value("MsgOnDino", ui.MsgOnDino->toPlainText().toStdString().c_str())));
	ui.MsgSitting->setText(QString::fromStdString(loadjson["Suicide"].value("MsgSitting", ui.MsgSitting->toPlainText().toStdString().c_str())));
	ui.MsgPickedUP->setText(QString::fromStdString(loadjson["Suicide"].value("MsgPickedUP", ui.MsgPickedUP->toPlainText().toStdString().c_str())));
	ui.MsgUnconscious->setText(QString::fromStdString(loadjson["Suicide"].value("MsgUnconscious", ui.MsgUnconscious->toPlainText().toStdString().c_str())));
	ui.SuicidePoints->setValue(loadjson["Suicide"].value("SuicidePoints", 0));
	ui.CanSuicideWhileKnockedOut->setChecked(loadjson["Suicide"].value("CanSuicideWhileKnockedOut", ui.CanSuicideWhileKnockedOut->isChecked()));
	ui.CanSuicideWithHandCuffs->setChecked(loadjson["Suicide"].value("CanSuicideWithHandCuffs", ui.CanSuicideWithHandCuffs->isChecked()));
	ui.CanSuicideWhilePickedUP->setChecked(loadjson["Suicide"].value("CanSuicideWhilePickedUP", ui.CanSuicideWhilePickedUP->isChecked()));
}

void QtTBroShop::saveSuicideconfig()
{
	savejson["Suicide"]["SuicideCMD"]= ui.SuicideCMD->toPlainText().toStdString().c_str();
	savejson["Suicide"]["SuicideCMD1"] = ui.SuicideCMD1->toPlainText().toStdString().c_str();
	savejson["Suicide"]["SuicideCMD2"] = ui.SuicideCMD2->toPlainText().toStdString().c_str();
	savejson["Suicide"]["Sender"] = ui.SuicideSender->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgDead"] = ui.MsgDead->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgAlreadyDead"] = ui.MsgAlreadyDead->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgHandcuffs"] = ui.MsgHandcuffs->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgOnDino"] = ui.MsgOnDino->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgSitting"] = ui.MsgSitting->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgPickedUP"] = ui.MsgPickedUP->toPlainText().toStdString().c_str();
	savejson["Suicide"]["MsgUnconscious"] = ui.MsgUnconscious->toPlainText().toStdString().c_str();
	savejson["Suicide"]["SuicidePoints"] = ui.SuicidePoints->value();
	savejson["Suicide"]["CanSuicideWhileKnockedOut"] = ui.CanSuicideWhileKnockedOut->isChecked();
	savejson["Suicide"]["CanSuicideWithHandCuffs"] = ui.CanSuicideWithHandCuffs->isChecked();
	savejson["Suicide"]["CanSuicideWhilePickedUP"] = ui.CanSuicideWhilePickedUP->isChecked();
	savejson["Suicide"]["SuicideRequiresPermission"] = false;
}