#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H

#include <QMainWindow>
#include "Chat.h"

namespace Ui {
class ConnectWindow;
}

class ConnectWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit ConnectWindow(QWidget *parent = 0);
		~ConnectWindow();

	private slots:
		void on_connectButton_clicked();

	private:
		Ui::ConnectWindow *ui;
		Chat *_chat = nullptr;
};

#endif // CONNECTWINDOW_H