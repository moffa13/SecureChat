#include <QApplication>
#include <QSslSocket>
#include "ui/ConnectWindow.h"

int main(int argc, char* argv[]){

	QApplication app{argc, argv};

	qDebug() << "Using openssl " << QSslSocket::sslLibraryBuildVersionString();

	app.setQuitOnLastWindowClosed(false);

	ConnectWindow c;
	c.show();

	return app.exec();
}
