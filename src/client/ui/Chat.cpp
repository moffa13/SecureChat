#include "Chat.h"
#include "ui_Chat.h"
#include <QSslCertificate>
#include <QFile>
#include <QDir>

Chat::Chat(QString host, quint16 port, QString const& cacert, QString const& clientcert, QString const& clientkey, QString const& clientKeyPassword, QWidget *parent):
	QMainWindow(parent),
	_host{std::move(host)},
	_port{port},
	_cacert{initCert(cacert)},
	_clientcert{initCert(clientcert)},
	_clientKey{initKey(clientkey, clientKeyPassword)},
	ui(new Ui::Chat)
{
	setAttribute(Qt::WA_DeleteOnClose);

	_socket.setPeerVerifyMode(QSslSocket::VerifyPeer);
	QList<QSslCertificate> cacerts;
	cacerts << _cacert;
	_socket.setCaCertificates(cacerts);

	_socket.setProtocol(QSsl::SslV3);

	_socket.setLocalCertificate(clientcert);
	_socket.setPrivateKey(_clientKey);

	connect(&_socket, static_cast<void (QSslSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), [this](QAbstractSocket::SocketError error){
		qDebug() << error << _socket.error() << _socket.errorString();
	});

	connect(&_socket, &QSslSocket::peerVerifyError, [](const QSslError & error){

		qDebug() << "Cannot verify server identity " << error;
	});

	connect(&_socket, static_cast<void(QSslSocket::*)(const QList<QSslError> &errors)>(&QSslSocket::sslErrors), [this](const QList<QSslError> &errors){
		Q_UNUSED(errors);
		QList<QSslError> ignoreableErrors;
		ignoreableErrors << QSslError{QSslError::CertificateSignatureFailed};
		ignoreableErrors << QSslError{QSslError::SelfSignedCertificateInChain, _cacert};
		_socket.ignoreSslErrors(ignoreableErrors);
	});

	connect(&_socket, &QSslSocket::stateChanged, [](QAbstractSocket::SocketState state){
		qDebug() << state;
	});

	connect(&_socket, &QSslSocket::encrypted, [](){
		qDebug() << "Connection encrypted";
	});


	_socket.connectToHost(_host, _port);
	_socket.waitForConnected();
	_socket.startClientEncryption();

	ui->setupUi(this);
}

Chat::~Chat(){
	delete ui;
}

QSslCertificate Chat::initCert(const QString &certPath){
	QFile certFile{certPath};
	certFile.open(QFile::ReadOnly);
	QSslCertificate cert{&certFile};
	certFile.close();
	return cert;
}

QSslKey Chat::initKey(const QString& keyPath, const QString& keyPassword){
	QFile keyFile{keyPath};
	keyFile.open(QFile::ReadOnly);
	QSslKey key{&keyFile, QSsl::Rsa, QSsl::Pem, QSsl::PrivateKey, keyPassword.toLocal8Bit()};
	keyFile.close();
	return key;
}
