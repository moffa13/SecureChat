#include "ConnectWindow.h"
#include "ui_ConnectWindow.h"

ConnectWindow::ConnectWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ConnectWindow)
{
	ui->setupUi(this);
	setFixedSize(sizeHint());
	setWindowTitle("SecureChat");
}

ConnectWindow::~ConnectWindow(){
	delete ui;
}

void ConnectWindow::on_connectButton_clicked(){
	_chat = new Chat{"127.0.0.1", 8888, "cacert.pem", "clientcert.pem"};
	connect(_chat, &Chat::destroyed, [this](){
		show();
		_chat = nullptr;
	});
	_chat->show();
	hide();
}