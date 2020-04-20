#include "yjsd.h"
yjsd::yjsd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton, &QPushButton::clicked, this, &yjsd::zxyjsd);
}
void yjsd::zxyjsd()
{
	std::string tbro = ui.textBrowser->toPlainText().toStdString();
	if (tbro == "tbro")
	{
		nlohmann::json tbroload;
		QString saveconfigpath = QDir::currentPath() + "/save.ini";
		std::wstring tbropath = saveconfigpath.toStdWString();
		std::fstream tbrofile{ tbropath };
		if (tbrofile.is_open())
		{
			tbrofile >> tbroload;
			for (int i = 0; i < tbroload["load"].size(); i++)
			{
				std::string server = tbroload["load"][i]["path"];
				if (server != "")
				{
					if (ui.SavedArks->isChecked())
					{
						std::string serverpath = server+ "/ShooterGame/Saved/SavedArks";
						QDir dir(QString::fromStdString(serverpath));
						dir.removeRecursively();
					}
					if(ui.Logs->isChecked())
					{
						std::string serverpath = server + "/ShooterGame/Saved/Logs";
						QDir dir(QString::fromStdString(serverpath));
						dir.removeRecursively();
					}

				}
			}
			ui.yjsdlabel->setText(QString::fromLocal8Bit("已完成一键删档"));
		}
		tbrofile.close();
		
	}
}
yjsd::~yjsd()
{

}