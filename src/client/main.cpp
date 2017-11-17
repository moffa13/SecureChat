#include <QApplication>
#include <QSslSocket>
#include <QHostInfo>
#include "ui/ConnectWindow.h"
#define QHOSTINFO_DEBUG

int main(int argc, char* argv[]){

	QApplication app{argc, argv};

	qDebug() << "Using openssl " << QSslSocket::sslLibraryBuildVersionString();


	   QHostInfo returnedHost = QHostInfo::fromName("google.comss");
	   qDebug() << returnedHost.errorString();

	   if (returnedHost.error() != QHostInfo::NoError) {
			qDebug() << "Lookup failed:" << returnedHost.errorString();
	   }

	app.setQuitOnLastWindowClosed(false);

	ConnectWindow c;
	c.show();

	return app.exec();
}
