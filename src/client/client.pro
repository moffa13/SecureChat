QT += core gui widgets network
CONFIG += c++14

SOURCES += \
	main.cpp \
	ui/ConnectWindow.cpp \
	ui/Chat.cpp

FORMS += \
	ui/ConnectWindow.ui \
	ui/Chat.ui

HEADERS += \
	ui/ConnectWindow.h \
	ui/Chat.h \
    ui/utils.h
