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
	ui.SavePath->setText(filepath);

	Generaldef();
	Kitsdef();
	Shopdef();
	vipShopdef();
	kamidef();
	selldef();
	Messagedef();
	Serversdef();

	connect(ui.openbutton, &QPushButton::clicked, this, &QtTBroShop::openfile);
	connect(ui.savebutton, &QPushButton::clicked, this, &QtTBroShop::savefile);

	connect(ui.openurlbutton, &QPushButton::clicked, this, &QtTBroShop::openurl);
	connect(ui.openqqbutton, &QPushButton::clicked, this, &QtTBroShop::openqq);

	connect(ui.tabWidget, &QTabWidget::tabBarClicked, this, &QtTBroShop::clearfilelabel);

	connect(ui.addserver, &QPushButton::clicked, this, &QtTBroShop::addserver);
	connect(ui.removeserver, &QPushButton::clicked, this, &QtTBroShop::removeserver);

	connect(ui.openserverconfig, &QPushButton::clicked, this, &QtTBroShop::openserverconfig);
	connect(ui.saveall, &QPushButton::clicked, this, &QtTBroShop::saveall);
	connect(ui.yjsdbtn, &QPushButton::clicked, this, &QtTBroShop::openyjsd);


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




void QtTBroShop::openurl()
{
	QDesktopServices::openUrl(QUrl("https://arkfgf.com/archives/581"));
}

void QtTBroShop::openqq()
{
	QDesktopServices::openUrl(QUrl("https://jq.qq.com/?_wv=1027&k=5zp0syp"));
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
	//�����ļ��Ի�����
	QFileDialog* fileDialog = new QFileDialog(this);
	//�����ļ��Ի������
	fileDialog->setWindowTitle(QStringLiteral("ѡ���ļ�"));
	//����Ĭ���ļ�·��
	fileDialog->setDirectory(".");
	//�����ļ�������
	fileDialog->setNameFilter(tr("File(*.*)"));
	//���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles
	fileDialog->setFileMode(QFileDialog::ExistingFiles);
	//������ͼģʽ
	fileDialog->setViewMode(QFileDialog::Detail);
	//��ӡ����ѡ����ļ���·��
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
			ui.filelabel->setText(QString::fromLocal8Bit("�򿪳ɹ�"));
		}
		catch(const std::exception&)
		{
			ui.filelabel->setText(QString::fromLocal8Bit("!!��ʧ��!!"));
			file.close();
			return;
		}
	}
	else
	{
		ui.filelabel->setText(QString::fromLocal8Bit("!!��ʧ��!!"));
		file.close();
		return;
	}
	file.close();
	try
	{
		loadgeneralconfig();
		loadkitsconfig();
		loadShopconfig();
		loadvipShopconfig(); 
		loadkamiconfig();
		loadSuicideconfig(); 
		loadCommandconfig();
		loadMessageconfig();
		loadLotteryconfig();
		loadSellItem();
		loadvipSellItem();
		loadInvitationconfig();
	}
	catch (const std::exception & error)
	{
		QMessageBox::information(NULL, QString::fromLocal8Bit("����"), error.what());
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
		savekamiconfig();
		saveShopconfig();
		savevipShopconfig();
		saveSuicideconfig();
		saveCommandconfig();
		saveMessageconfig();
		saveLotteryconfig();
		saveSellconfig();
		savevipSellconfig();
		saveInvitationconfig();
		std::string savestr = savejson.dump(4); 
		file << savestr;
		savejson.clear();
		ui.filelabel->setText(QString::fromLocal8Bit("����ɹ�!"));
	}
	else
	{
		ui.filelabel->setText(QString::fromLocal8Bit("����ʧ��!"));
	}
	file.close();
}