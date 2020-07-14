#include "QtTBroShop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtTBroShop w;
	w.setWindowFlags(w.windowFlags() & ~Qt::WindowMaximizeButtonHint );
	w.setWindowTitle(QString::fromLocal8Bit("ArkShopEditingTools2.1"));
	w.setWindowIcon(QIcon("./iconengines/TBro.ico"));
	w.show(); 
	return a.exec();
}
