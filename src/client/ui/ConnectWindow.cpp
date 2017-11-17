#include "ConnectWindow.h"
#include "ui_ConnectWindow.h"
#include <QCloseEvent>
#include <QMessageBox>
#include "utils.h"

#define DEFAULT_CHAT_PORT 8888

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
	try{
		auto addressPort = utils::parseAddress(ui->urlEdit->text(), DEFAULT_CHAT_PORT);

		_chat.reset(new Chat{addressPort.first, addressPort.second, ui->cacertEdit->text(), ui->clientcertEdit->text(), ""});
		connect(_chat.data(), &Chat::destroyed, [this](){
			show();
			_chat.take();
		});
		_chat->show();
		hide();
	}catch(ParseAddressException const& e){
		QMessageBox::critical(this, "Host error", e.code() == 2 ? "Host lookup has failed" : "There is an error with the address you provided", QMessageBox::Ok);
	}
}
