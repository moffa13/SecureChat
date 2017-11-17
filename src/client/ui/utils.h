#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <QString>
#include <QHostInfo>
#include <iostream>

class ParseAddressException : public std::runtime_error{
	int _code;
	public:
	ParseAddressException(int code, std::string error) : _code(code), std::runtime_error(error){}
	ParseAddressException(int code, const char* error) : _code(code), std::runtime_error(error){}
	int code() const noexcept{
		return _code;
	}
};

namespace utils{

	std::pair<QString, quint16> parseAddress(QString const& addr, quint16 defaultPort){

		QStringList splitted = addr.split(':');

		quint16 port = defaultPort;

		if(splitted.size() == 2){
			try{
				port = std::stoi(splitted[1].toStdString());
			}catch(const std::exception &e){
				Q_UNUSED(e);
				throw ParseAddressException{0, "Invalid port supplied"};
			}
		}else if(splitted.size() > 2){
			throw ParseAddressException{1, "Invalid address supplied"};
		}

		QHostInfo address = QHostInfo::fromName(splitted[0]);

		if(address.error() == QHostInfo::HostNotFound){
			qDebug() << address.errorString();
			throw ParseAddressException{2, "Invalid host"};
		}else if(address.error() != QHostInfo::NoError){
			throw ParseAddressException{3, "Unknown error"};
		}

		return std::make_pair(address.addresses()[0].toString(), port);

	}
}

#endif // UTILS_H
