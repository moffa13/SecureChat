#ifndef CHAT_H
#define CHAT_H

#include <QMainWindow>
#include <QString>
#include <QSslSocket>

namespace Ui {
class Chat;
}

class Chat : public QMainWindow
{
		Q_OBJECT

	public:
		Chat(QString host, quint16 port, QString cacert, QString clientcert, QWidget *parent = 0);
		~Chat();

	private:
		Ui::Chat *ui;
		quint16 _port;
		QString _host;
		QString _cacert;
		QString _clientcert;
		QSslSocket _socket;

};

#endif // CHAT_H
