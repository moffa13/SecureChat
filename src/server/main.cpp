#include "SSLServer.h"
#include <QCoreApplication>


int main(int argc, char* argv[]){

	QCoreApplication app{argc, argv};

	SSLServer serv;
	serv.listen(QHostAddress::Any, 8888);

	return app.exec();
}
