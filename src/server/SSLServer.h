#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>
#include <QSslSocket>

class SSLServer : public QTcpServer
{
	public:
		SSLServer();
		SSLServer(QSslCertificate const& serverCertificate, QSslKey const& privateKey);
		void setCertificate(const QSslCertificate &key);
		void setPrivateKey(const QSslKey &privateKey);
		void setServerCertificate(const QSslCertificate &serverCertificate);
		QSslSocket* nextPendingConnection();
	protected:
		void incomingConnection(qintptr socketDescriptor) override;
	private:
		QSslKey _privateKey;
		QSslCertificate _serverCertificate;
};

#endif // SSLSERVER_H
