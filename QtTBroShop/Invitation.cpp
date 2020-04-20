#include "QtTBroShop.h"

void QtTBroShop::loadInvitationconfig()
{
	if (loadjson["Invitation"].empty())
		return;
	ui.InvitationSender->setText(QString::fromStdString(loadjson["Invitation"].value("Sender", ui.InvitationSender->toPlainText().toStdString().c_str())));
	ui.InvitationCodeUsed->setText(QString::fromStdString(loadjson["Invitation"].value("InvitationCodeUsed", ui.InvitationCodeUsed->toPlainText().toStdString().c_str())));
	ui.IsMyselfInvitationCode->setText(QString::fromStdString(loadjson["Invitation"].value("IsMyselfInvitationCode", ui.IsMyselfInvitationCode->toPlainText().toStdString().c_str())));
	ui.UsedInvitationCodeSuccess->setText(QString::fromStdString(loadjson["Invitation"].value("UsedInvitationCodeSuccess", ui.UsedInvitationCodeSuccess->toPlainText().toStdString().c_str())));
	ui.IsUsedInvitationCode->setText(QString::fromStdString(loadjson["Invitation"].value("IsUsedInvitationCode", ui.IsUsedInvitationCode->toPlainText().toStdString().c_str())));
	ui.InvitePlayerPoints->setValue(loadjson["Invitation"].value("InvitePlayerPoints", 300));
	ui.NewPlayerInvitePoints->setValue(loadjson["Invitation"].value("NewPlayerInvitePoints", 300));
	ui.UseInvitation->setChecked(loadjson["Invitation"].value("UseInvitation", false));
	ui.InviteCmd->setText(QString::fromStdString(loadjson["Invitation"].value("InviteCmd", ui.InviteCmd->toPlainText().toStdString().c_str())));
	ui.InviteCmd1->setText(QString::fromStdString(loadjson["Invitation"].value("InviteCmd1", ui.InviteCmd1->toPlainText().toStdString().c_str())));
	ui.InviteCmd2->setText(QString::fromStdString(loadjson["Invitation"].value("InviteCmd2", ui.InviteCmd2->toPlainText().toStdString().c_str())));
}

void QtTBroShop::saveInvitationconfig()
{
	savejson["Invitation"]["Sender"] = ui.InvitationSender->toPlainText().toStdString().c_str();
	savejson["Invitation"]["InvitationCodeUsed"] = ui.InvitationCodeUsed->toPlainText().toStdString().c_str();
	savejson["Invitation"]["IsMyselfInvitationCode"] = ui.IsMyselfInvitationCode->toPlainText().toStdString().c_str();
	savejson["Invitation"]["UsedInvitationCodeSuccess"] = ui.UsedInvitationCodeSuccess->toPlainText().toStdString().c_str();
	savejson["Invitation"]["IsUsedInvitationCode"] = ui.IsUsedInvitationCode->toPlainText().toStdString().c_str();
	savejson["Invitation"]["InvitePlayerPoints"] = ui.InvitePlayerPoints->value();
	savejson["Invitation"]["NewPlayerInvitePoints"] = ui.NewPlayerInvitePoints->value();
	savejson["Invitation"]["UseInvitation"] = ui.UseInvitation->isChecked();

	savejson["Invitation"]["InviteCmd"] = ui.InviteCmd->toPlainText().toStdString().c_str();
	savejson["Invitation"]["InviteCmd1"] = ui.InviteCmd1->toPlainText().toStdString().c_str();
	savejson["Invitation"]["InviteCmd2"] = ui.InviteCmd2->toPlainText().toStdString().c_str();
}