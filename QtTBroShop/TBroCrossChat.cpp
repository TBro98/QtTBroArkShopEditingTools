#include "QtTBroShop.h"
void QtTBroShop::CrossChatsdef()
{
	ui.SocketCrosstableWidget->setColumnWidth(0, 800);
	ui.SocketCrosstableWidget->setColumnWidth(1, 300);
	for (int i = 0; i < saveiniload["load"].size(); i++)
	{
		try {
			addnewceosschat(QString::fromStdString(saveiniload["load"][i]["path"]), QString::fromStdString(saveiniload["load"][i]["mapname"]), QString::fromStdString(saveiniload["load"][i]["rconport"]));
		}
		catch (std::exception&)
		{
			addnewceosschat(QString::fromStdString(saveiniload["load"]["path"][i]), "", "");
		}
	}

	connect(ui.addserver_2, &QPushButton::clicked, this, &QtTBroShop::addcross);
	connect(ui.removeserver_2, &QPushButton::clicked, this, &QtTBroShop::removecross);
}


void QtTBroShop::addnewceosschat(QString path, QString mapname, QString rconport)
{
	int iRow = ui.SocketCrosstableWidget->rowCount();
	ui.SocketCrosstableWidget->setRowCount(iRow + 1);
	QTableWidgetItem* item0 = new QTableWidgetItem();
	item0->setText(path);
	ui.SocketCrosstableWidget->setItem(iRow, 0, item0);
	QTableWidgetItem* item1 = new QTableWidgetItem();
	item1->setText(mapname);
	ui.SocketCrosstableWidget->setItem(iRow, 1, item1);
	QTableWidgetItem* item2 = new QTableWidgetItem();
	item2->setText(rconport);
	ui.SocketCrosstableWidget->setItem(iRow, 2, item2);

}

void QtTBroShop::addcross()
{
	addnewceosschat("", "", "");
}

void QtTBroShop::removecross()
{
	int iRow = ui.SocketCrosstableWidget->rowCount();
	ui.SocketCrosstableWidget->setRowCount(iRow - 1);

	savecrossini();
}

void QtTBroShop::savecrossini()
{
	nlohmann::json tbrosave;
	QString saveconfigpath = QDir::currentPath() + "/save.ini";
	std::wstring tbropath = saveconfigpath.toStdWString();
	std::ofstream tbrofile{ tbropath };
	int iRow = ui.SocketCrosstableWidget->rowCount();
	if (tbrofile.is_open())
	{
		for (int i = 0; i < iRow; i++)
		{
			tbrosave["load"][i]["path"] = ui.SocketCrosstableWidget->item(i, 0)->text().toStdString();
			tbrosave["load"][i]["mapname"] = ui.SocketCrosstableWidget->item(i, 1)->text().toStdString();
			tbrosave["load"][i]["rconport"] = ui.SocketCrosstableWidget->item(i, 2)->text().toStdString();

		}
		tbrofile << tbrosave;
		tbrofile.close();
	}
}