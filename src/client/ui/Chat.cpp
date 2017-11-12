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

	_socket.setPeerVerifyMode(QSslSocket::QueryPeer);
	_socket.addCaCertificates(cacert);
	_socket.setLocalCertificate(clientcert);

	connect(&_socket, static_cast<void (QSslSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [this](QAbstractSocket::SocketError error){
		qDebug() << error << _socket.error() << _socket.errorString();
	});

	connect(&_socket, &QSslSocket::peerVerifyError, [](const QSslError & error){
		qDebug() << "Cannot verify server identity " << error;
	});

	connect(&_socket, static_cast<void(QSslSocket::*)(const QList<QSslError>&)>(&QSslSocket::sslErrors), [](const QList<QSslError> &errors){
		qDebug() << "SSL Error";
		for(auto error : errors){
			qDebug() << error;
		}
	});

	connect(&_socket, &QSslSocket::encrypted, [](){
		qDebug() << "Connection encrypted";
	});


	_socket.connectToHostEncrypted(_host, _port);

	ui->setupUi(this);
}

Chat::~Chat()
{
	delete ui;
}
