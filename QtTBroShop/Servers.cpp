#include "QtTBroShop.h"
void QtTBroShop::Serversdef()
{
	ui.serverstableWidget->setColumnWidth(0, 700);
	ui.serverstableWidget->setColumnWidth(1, 200);
	
	for (int i = 0; i < saveiniload["load"].size(); i++)
	{
		try {
			addnewserver(QString::fromStdString(saveiniload["load"][i]["path"]), "", "");
		}
		catch (std::exception&)
		{
			addnewserver(QString::fromStdString(saveiniload["load"]["path"][i]), "", "");
		}
	}
	/*
	int colora = ui.servercolora->value();
	int colorb = ui.servercolorb->value();
	int colorc = ui.servercolorc->value();
	for (int i = 0; i < ui.serverstableWidget->rowCount(); i++) 
	{
		QTableWidgetItem* item = ui.serverstableWidget->item(i, 1);
		if (item)
		{
			const QColor color = QColor(colora, colorb, colorc);
			item->setBackgroundColor(color);
		}
	}
	connect(ui.servercolora, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::servercolorchange);
	connect(ui.servercolorb, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::servercolorchange);
	connect(ui.servercolorc, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtTBroShop::servercolorchange);

	connect(ui.RconCrossServerChat, &QPushButton::clicked, this, &QtTBroShop::SaveRconCrossServerChat);
	*/

	
	openserverconfig();
}
/*
void QtTBroShop::SaveRconCrossServerChat()
{
	saveini();
	const std::string colora = std::to_string(ui.servercolora->value());
	const std::string colorb = std::to_string(ui.servercolorb->value());
	const std::string colorc = std::to_string(ui.servercolorc->value());
	nlohmann::json RconServers;
	for (int i = 0; i < ui.serverstableWidget->rowCount(); i++)
	{
		QString rconport= ui.serverstableWidget->item(i, 2)->text();
		RconServers[i] = read_ip_address().toStdString() + ":" + rconport.toStdString();
	}
	for (int i = 0; i < ui.serverstableWidget->rowCount(); i++)
	{
		nlohmann::json RconCrossServerChatjson;
		RconCrossServerChatjson["CrossChatKey"] = ui.CrossChatKey->toPlainText().toStdString();
		RconCrossServerChatjson["CrossChatMapNameInclude"] = true;
		RconCrossServerChatjson["Async"] = true; 
		RconCrossServerChatjson["RconServers"] = RconServers;
		std::string CrossChatMapNameOverride = "<RichColor Color=\""+ colora+","+colorb+","+colorc+",255"+"\">" + ui.serverstableWidget->item(i, 1)->text().toStdString() + "</>";
		RconCrossServerChatjson["CrossChatMapNameOverride"] = CrossChatMapNameOverride;

		QString filepath = ui.serverstableWidget->item(i, 0)->text() + "/ShooterGame/Binaries/Win64/ArkApi/Plugins/RconCrossServerChat/config.json";
		std::ofstream tbrofile(filepath.toStdString());
		if (tbrofile.is_open())
		{
			tbrofile << RconCrossServerChatjson.dump(4);
			ui.filelabel->setText(QString::number(i + 1) + QString::fromLocal8Bit("个跨服一键保存成功!"));
		}
		else
		{
			ui.filelabel->setText(QString::number(i + 1) + QString::fromLocal8Bit("及之后的跨服保存失败!"));
			tbrofile.close();
			return;
		}
		tbrofile.close();
	}

}
void QtTBroShop::servercolorchange()
{
	int colora = ui.servercolora->value();
	int colorb = ui.servercolorb->value();
	int colorc = ui.servercolorc->value();
	for (int i = 0; i < ui.serverstableWidget->rowCount(); i++)
	{
		QTableWidgetItem* item = ui.serverstableWidget->item(i, 1);
		if (item)
		{
			const QColor color = QColor(colora, colorb, colorc);
			item->setBackgroundColor(color);
		}
	}
}
*/


void QtTBroShop::addnewserver(QString path, QString mapname, QString rconport)
{
	int iRow = ui.serverstableWidget->rowCount();
	ui.serverstableWidget->setRowCount(iRow + 1);
	QTableWidgetItem* item0 = new QTableWidgetItem();
	item0->setText(path);
	ui.serverstableWidget->setItem(iRow, 0, item0);
	/*
	int colora = ui.servercolora->value();
	int colorb = ui.servercolorb->value();
	int colorc = ui.servercolorc->value(); 
	const QColor color = QColor(colora, colorb, colorc);
	item1->setBackgroundColor(color);
	*/
}
void QtTBroShop::saveall()
{
	Permissionsjson["DbPathOverride"] = ui.PermissionsDbPathOverride->toPlainText().toStdString();
	Permissionsjson["Database"] = ui.Database->currentText().toStdString();
	Permissionsjson["MysqlDB"] = ui.PermissionsMysqlDB->toPlainText().toStdString();
	Permissionsjson["MysqlHost"] = ui.PermissionsMysqlHost->toPlainText().toStdString();
	Permissionsjson["MysqlPass"] = ui.PermissionsMysqlPass->toPlainText().toStdString();
	Permissionsjson["MysqlUser"] = ui.PermissionsMysqlUser->toPlainText().toStdString();
	Permissionsjson["MysqlPort"] = ui.PermissionsMysqlPort->value();
	Permissionsjson["Database"]=ui.Database->currentText().toStdString();

	std::string Permissionsavestr = Permissionsjson.dump(4);
	savegeneralconfig();
	savekitsconfig();
	saveShopconfig();
	saveCommandconfig();
	saveMessageconfig();
	saveSellconfig();
	saveini();

	int iRow = ui.serverstableWidget->rowCount();
	std::string savestr = savejson.dump(4);
	for (int i = 0; i < iRow; i++)
	{
		QString Permissionfilepath = ui.serverstableWidget->item(i, 0)->text() + "/ShooterGame/Binaries/Win64/ArkApi/Plugins/Permissions/config.json";
		std::wstring Permissionpath = Permissionfilepath.toStdWString();
		std::ofstream Permissionfile{ Permissionpath };
		if (Permissionfile.is_open())
		{
			Permissionfile << Permissionsavestr;
		}
		else
		{
			ui.filelabel->setText("Failed to save Permissions after "+QString::number(i + 1));
			Permissionfile.close();
			return;
		}
		Permissionfile.close();

		QString filepath = ui.serverstableWidget->item(i, 0)->text() + "/ShooterGame/Binaries/Win64/ArkApi/Plugins/ArkShop/config.json";
		std::wstring path = filepath.toStdWString();
		std::ofstream file{ path };
		if (file.is_open())
		{
			file << savestr;
			ui.filelabel->setText(QString::number(i + 1) + QString::fromLocal8Bit(" save success!"));
		}
		else
		{
			ui.filelabel->setText("Failed to save ArkShop after " + QString::number(i + 1));
			file.close();
			return;
		}
		file.close();
	}
	savejson.clear();

}
void QtTBroShop::addserver()
{
	addnewserver("","","");
}
void QtTBroShop::removeserver()
{
	int iRow = ui.serverstableWidget->rowCount();
	ui.serverstableWidget->setRowCount(iRow - 1);

	saveini();
}
void QtTBroShop::openserverconfig()
{
	saveini();
	//close Permissions setting
	ui.PermissionsDbPathOverride->setEnabled(false);
	ui.PermissionsMysqlHost->setEnabled(false);
	ui.PermissionsMysqlUser->setEnabled(false);
	ui.PermissionsMysqlPass->setEnabled(false);
	ui.PermissionsMysqlDB->setEnabled(false);
	ui.PermissionsMysqlPort->setEnabled(false);
	ui.Database->setEnabled(false);

	if (ui.serverstableWidget->rowCount() > 0)
	{
		if (ui.serverstableWidget->item(0, 0)->text().isEmpty())
			return;
		/*
		//open Permissions config.json
		*/
		QString Permissionfilepath = ui.serverstableWidget->item(0, 0)->text() + "/ShooterGame/Binaries/Win64/ArkApi/Plugins/Permissions/config.json";
		std::wstring Permissionpath = Permissionfilepath.toStdWString();
		std::fstream Permissionfile{ Permissionpath };
		if (Permissionfile.is_open())
		{
			Permissionfile >> Permissionsjson;

			ui.PermissionsDbPathOverride->setEnabled(true);
			ui.PermissionsMysqlHost->setEnabled(true);
			ui.PermissionsMysqlUser->setEnabled(true);
			ui.PermissionsMysqlPass->setEnabled(true);
			ui.PermissionsMysqlDB->setEnabled(true);
			ui.PermissionsMysqlPort->setEnabled(true);
			ui.Database->setEnabled(true);

			if(Permissionsjson["Database"]=="sqlite")
				ui.Database->setCurrentIndex(0);
			else if (Permissionsjson["Database"] == "mysql")
				ui.Database->setCurrentIndex(1);
			ui.PermissionsDbPathOverride->setText(QString::fromStdString(Permissionsjson["DbPathOverride"]));
			ui.PermissionsMysqlHost->setText(QString::fromStdString(Permissionsjson["MysqlHost"]));
			ui.PermissionsMysqlUser->setText(QString::fromStdString(Permissionsjson["MysqlUser"]));
			ui.PermissionsMysqlPass->setText(QString::fromStdString(Permissionsjson["MysqlPass"]));
			ui.PermissionsMysqlDB->setText(QString::fromStdString(Permissionsjson["MysqlDB"]));
			ui.PermissionsMysqlPort->setValue(Permissionsjson["MysqlPort"]);
		}
		else
		{
			ui.filelabel->setText("Failed to open Permissions config.json in directory!");

			Permissionfile.close();
			return;
		}
		Permissionfile.close();

		/*
		//open ArkShop config.json
		*/
		QString filepath = ui.serverstableWidget->item(0, 0)->text() + "/ShooterGame/Binaries/Win64/ArkApi/Plugins/ArkShop/config.json";
		openfile(filepath);
	}
	else
	{
		ui.filelabel->setText("No directory!");
	}

}