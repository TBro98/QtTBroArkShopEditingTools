#include "QtTBroShop.h"
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QNetworkInterface>
//#include <QTime>
QtTBroShop::QtTBroShop(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QString filepath=QDir::currentPath() + "/config.json";
	LoadJson(filepath);
	ui.SavePath->setText(filepath);

	Generaldef();
	Kitsdef();
	Shopdef();
	selldef();
	SaveiniLoad();
	Serversdef();

	connect(ui.openbutton, &QPushButton::clicked, this, &QtTBroShop::openfile);
	connect(ui.savebutton, &QPushButton::clicked, this, &QtTBroShop::savefile);

	connect(ui.tabWidget, &QTabWidget::tabBarClicked, this, &QtTBroShop::clearfilelabel);

	connect(ui.addserver, &QPushButton::clicked, this, &QtTBroShop::addserver);
	connect(ui.removeserver, &QPushButton::clicked, this, &QtTBroShop::removeserver);

	connect(ui.openserverconfig, &QPushButton::clicked, this, &QtTBroShop::openserverconfig);
	connect(ui.saveall, &QPushButton::clicked, this, &QtTBroShop::saveall);


}

void QtTBroShop::LoadJson(QString filepath)
{
	std::wstring jsonpath = filepath.toStdWString();
	std::fstream jsonfile{ jsonpath };
	if (jsonfile.is_open())
	{
		jsonfile >> loadjson;

		Messagedef();
	}
	jsonfile.close();
}
void QtTBroShop::SaveiniLoad()
{
	QString saveconfigpath = QDir::currentPath() + "/save.ini";
	std::wstring tbropath = saveconfigpath.toStdWString();
	std::fstream tbrofile{ tbropath };
	if (tbrofile.is_open())
	{
		tbrofile >> saveiniload;
	}
	tbrofile.close();
}

void QtTBroShop::saveini()
{
	nlohmann::json tbrosave;
	QString saveconfigpath = QDir::currentPath() + "/save.ini";
	std::wstring tbropath = saveconfigpath.toStdWString();
	std::ofstream tbrofile{ tbropath };
	int iRow = ui.serverstableWidget->rowCount();
	if (tbrofile.is_open())
	{
		for (int i = 0; i < iRow; i++)
		{
			tbrosave["load"][i]["path"] = ui.serverstableWidget->item(i, 0)->text().toStdString();

		}
		tbrofile << tbrosave;
		tbrofile.close();
	}
}
QString QtTBroShop::read_ip_address()
{
	QString ip_address;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	for (int i = 0; i < ipAddressesList.size(); ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
		{
			ip_address = ipAddressesList.at(i).toString();
			qDebug() << ip_address;  //debug
			//break;
		}
	}
	if (ip_address.isEmpty())
		ip_address = QHostAddress(QHostAddress::LocalHost).toString();
	return ip_address;
}

std::string QtTBroShop::getblu(std::string blu)
{
	if (blu.find("\"") != -1)
	{
		blu = blu.substr(blu.find("\"")+1, blu.rfind("\"")- blu.find("\"")-1 );
		//blu = blu.substr(0,blu.find("\""));
	}
	return blu;
}

void QtTBroShop::clearfilelabel()
{
	ui.filelabel->clear();
}
void QtTBroShop::openfile()
{
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::red);
	ui.filelabel->setPalette(pe);
	//定义文件对话框类
	QFileDialog* fileDialog = new QFileDialog(this);
	//定义文件对话框标题
	fileDialog->setWindowTitle(QStringLiteral("Choose config.json"));
	//设置默认文件路径
	fileDialog->setDirectory(".");
	//设置文件过滤器
	fileDialog->setNameFilter(tr("File(*.*)"));
	//设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//设置视图模式
	fileDialog->setViewMode(QFileDialog::Detail);
	//打印所有选择的文件的路径
	QStringList fileNames;
	if (fileDialog->exec()) {
		fileNames = fileDialog->selectedFiles();
	}
	else
		return;
	//QString filepath = QDir::currentPath() + "/config.json";
	QString filepath = fileNames.first();
	std::wstring path = filepath.toStdWString();
	std::fstream file{ path };
	if (file.is_open())
	{
		ui.SavePath->setText(filepath);
		try
		{
			file >> loadjson;
			ui.filelabel->setText("Open Success");
		}
		catch(const std::exception&)
		{
			ui.filelabel->setText("!!Open Failed!!");
			file.close();
			return;
		}
	}
	else
	{
		ui.filelabel->setText("!!Open Failed!!");
		file.close();
		return;
	}
	file.close();
	std::string errorwhere;
	try
	{
		errorwhere = "General";
		loadgeneralconfig();
		errorwhere = "Kits";
		loadkitsconfig();
		errorwhere = "ShopItems";
		loadShopconfig();
		errorwhere = "Chat";
		loadCommandconfig();
		errorwhere = "Messages";
		loadMessageconfig();
		errorwhere = "Sell";
		loadSellItem();
	}
	catch (const std::exception & error)
	{
		ui.filelabel->setText("!!Open Failed!!");
		std::string errorstr = "Warn from:" + errorwhere;
		errorstr += error.what();
		QMessageBox::information(NULL, "Error", QString::fromLocal8Bit(errorstr.c_str()));
	}
}


void QtTBroShop::savefile()
{
	
	QPalette pe;
	pe.setColor(QPalette::WindowText, Qt::red);
	ui.filelabel->setPalette(pe);
	QString filepath = ui.SavePath->toPlainText();
	std::wstring path = filepath.toStdWString();
	std::ofstream file{ path };
	if (file.is_open())
	{
		savegeneralconfig();
		savekitsconfig();
		saveShopconfig();
		saveCommandconfig();
		saveMessageconfig();
		saveSellconfig();
		std::string savestr = savejson.dump(4); 
		file << savestr;
		savejson.clear();
		ui.filelabel->setText(QString::fromLocal8Bit("Saved!"));
	}
	else
	{
		ui.filelabel->setText(QString::fromLocal8Bit("Save Failed!"));
	}
	file.close();
}