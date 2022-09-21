# dReam Tables Five Card Draw Poker

# Copyright (C) 2022  dReam Tables

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

# Always play responsibly.

# https://dreamtables.net

QT += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lcurl

# Windows static
# CONFIG += c++11 static
# LIBS += -llibcurl

# CONFIG += link_pkgconfig
# PKGCONFIG += curl

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aes/qaesencryption.cpp \
    confirm.cpp \
    controller.cpp \
    hands/handranks.cpp \
    hands/decks.cpp \
    hands/endhands.cpp \
    hands/viewdeck.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    rpc/daemon_rpc.cpp \
    rpc/menu_rpc.cpp \
    rpc/wallet_rpc.cpp \
    shared/filedownloader.cpp

HEADERS += \
    aes/qaesencryption.h \
    confirm.h \
    hands/handranks.h \
    hands/viewdeck.h \
    mainwindow.h \
    menu.h \
    rpc/rpc.h \
    shared/filedownloader.h

FORMS += \
    confirm.ui \
    hands/handranks.ui \
    hands/viewdeck.ui \
    mainwindow.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
