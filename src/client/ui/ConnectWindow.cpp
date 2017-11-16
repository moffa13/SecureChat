#include "ConnectWindow.h"
#include "ui_ConnectWindow.h"
#include <QCloseEvent>

ConnectWindow::ConnectWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ConnectWindow)
{
	ui->setupUi(this);
	setFixedSize(sizeHint());
	setWindowTitle("SecureChat");

	ui->cacertEdit->setText(QApplication::applicationDirPath() + "/ca.crt");
	ui->clientcertEdit->setText(QApplication::applicationDirPath() + "/client.crt");
	ui->clientPrivateKeyEdit->setText(QApplication::applicationDirPath() + "/client.key");

}

ConnectWindow::~ConnectWindow(){
	delete ui;
}

void ConnectWindow::closeEvent(QCloseEvent *event){
	QMainWindow::closeEvent(event);
	event->accept();
	qApp->quit();
}

void ConnectWindow::on_connectButton_clicked(){
	_chat.reset(new Chat{"127.0.0.1", 8888, ui->cacertEdit->text(), ui->clientcertEdit->text(), ""});
	connect(_chat.data(), &Chat::destroyed, [this](){
		show();
		_chat.take();
	});
	_chat->show();
	hide();
}
