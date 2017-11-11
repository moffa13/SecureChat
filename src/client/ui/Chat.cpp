#include "Chat.h"
#include "ui_Chat.h"
#include <QSslCertificate>

Chat::Chat(QString host, quint16 port, QString cacert, QString clientcert, QWidget *parent):
	QMainWindow(parent),
	_host{std::move(host)},
	_port{port},
	_cacert{cacert},
	_clientcert{clientcert},
	ui(new Ui::Chat)
{

	setAttribute(Qt::WA_DeleteOnClose);

	_socket.addCaCertificates(cacert);
	_socket.setLocalCertificate(clientcert);

	_socket.connectToHostEncrypted(_host, _port);


	ui->setupUi(this);
}

Chat::~Chat()
{
	delete ui;
}
