#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QString>
#include <QSslSocket>
#include <QSslKey>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
		Q_OBJECT

	public:
		Chat(QString host, quint16 port, const QString &cacert, const QString &clientcert, const QString &clientkey, const QString &clientKeyPassword = QString{}, QWidget *parent = 0);
		~Chat();

	private:
		static QSslCertificate initCert(QString const& certPath);
		static QSslKey initKey(const QString &keyPath, const QString &keyPassword);
		Ui::Chat *ui;
		quint16 _port;
		QString _host;
		QSslCertificate _cacert;
		QSslCertificate _clientcert;
		QSslKey _clientKey;
		QSslSocket _socket;
};

#endif // CHAT_H
