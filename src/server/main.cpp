#include "SSLServer.h"
#include <QCoreApplication>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslKey>
#include <QFile>

int main(int argc, char* argv[]){

	QCoreApplication app{argc, argv};

	qDebug() << "Using openssl " << QSslSocket::sslLibraryBuildVersionString();

	QFile serverCert{"server.crt"};
	serverCert.open(QFile::ReadOnly);

	QFile serverKey{"server.key"};
	serverKey.open(QFile::ReadOnly);


	SSLServer serv{QSslCertificate{&serverCert, QSsl::Pem}, QSslKey{&serverKey, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey}};

	serverCert.close();
	serverKey.close();

	serv.listen(QHostAddress::Any, 8888);

	return app.exec();
}
