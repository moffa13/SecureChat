#include <QApplication>

#include "ui/ConnectWindow.h"

int main(int argc, char* argv[]){

	QApplication app{argc, argv};

	app.setQuitOnLastWindowClosed(false);

	ConnectWindow c;
	c.show();

	return app.exec();
}
