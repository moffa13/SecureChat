#ifndef SSLSERVER_H
#define SSLSERVER_H

#include <QTcpServer>

class SSLServer : public QTcpServer
{
	public:
		SSLServer();
	protected:
		void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SSLSERVER_H
