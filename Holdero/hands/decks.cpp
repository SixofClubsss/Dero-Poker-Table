/*
dReam Tables Holdero Poker

Copyright (C) 2022  dReam Tables

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

Always play responsibly.

https://dreamtables.net
*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"
#include "./ui_menu.h"


QString MainWindow::readmeStandard(QString find)
{
    find.remove(0, 123);
    find.remove(0, 1);
    find.chop(78);

    return find;
}


void Menu::AZYDS(QString pre, rpc& r)
{
    QString ds0001 = "93e797c6d8e8d60e720f7cb7f87ae7c050acb601dec9849069ae8b676c7fa6bc";
    QString ds0002 = "f82dd64b0355d23dcb58f6e5aff59194d75e9a7eb4c0520c6b495f2a5933fdcf";
    QString ds0003 = "c5cb0f5b8bfc9fe870c30f206851e0fd5f8a5b415afd90eded81a60d36928ae8";
    QString ds0004 = "bade80d4fa9a246aa43f4853b986a1e5c980f4db84248bec27c0dc41eb6f8284";
    QString ds0005 = "f8811a25186c799b58c8f1cd89f484ef428be662ccc58afc6d67c31095018bba";


    QFile nfaScape1(pre+"/cards/AZYDS0001/README.md");
    nfaScape1.open(QIODevice::ReadOnly);

    if(nfaScape1.exists()){
        r.verifyNFAcreator(ds0001);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS0001");
            qInfo() << ("\033[35m♧Loading AZYDS Theme♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape1.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape1.close();
        }

    }

    QFile nfaScape2(pre+"/cards/AZYDS0002/README.md");
    nfaScape2.open(QIODevice::ReadOnly);

    if(nfaScape2.exists()){
        r.verifyNFAcreator(ds0002);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS0002");
            qInfo() << ("\033[35m♧Loading AZYDS Theme♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape2.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape2.close();
        }

    }

    QFile nfaScape3(pre+"/cards/AZYDS0003/README.md");
    nfaScape3.open(QIODevice::ReadOnly);

    if(nfaScape3.exists()){
        r.verifyNFAcreator(ds0003);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS0003");
            qInfo() << ("\033[35m♧Loading AZYDS Theme♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape3.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape3.close();
        }

    }

    QFile nfaScape4(pre+"/cards/AZYDS0004/README.md");
    nfaScape4.open(QIODevice::ReadOnly);

    if(nfaScape4.exists()){
        r.verifyNFAcreator(ds0004);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS0004");
            qInfo() << ("\033[35m♧Loading AZYDS Theme♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape4.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape4.close();
        }

    }

    QFile nfaScape5(pre+"/cards/AZYDS0005/README.md");
    nfaScape5.open(QIODevice::ReadOnly);

    if(nfaScape5.exists()){
        r.verifyNFAcreator(ds0005);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS0005");
            qInfo() << ("\033[35m♧Loading AZYDS Theme♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape5.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape5.close();
        }

    }
}


void MainWindow::AZYPC(QString pre, rpc& r)
{
    QString start;
    QString add;
    int i = 1;

    do {
        start = "000";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/AZYPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "AZYPC"+add);
                qInfo() << ("\033[35m♤Loading AZYPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 10);

    do {
        start = "00";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/AZYPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "AZYPC"+add);
                qInfo() << ("\033[35m♤Loading AZYPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 100);

    do {
        start = "0";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/AZYPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "AZYPC"+add);
                qInfo() << ("\033[35m♤Loading AZYPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 1000);

    add = start+QString::number(i);
    QFile nfaDeck(pre+"/cards/AZYPC"+add+"/README.md");
    nfaDeck.open(QIODevice::ReadOnly);

    if(nfaDeck.exists()){
        QString findAddr = nfaDeck.readAll();
        findAddr = readmeStandard(findAddr);
        r.verifyNFAcreator(findAddr);
        if(rpc::assetConfirmed == true){
            ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "AZYPC"+add);
            qInfo() << ("\033[35m♤Loading AZYPC Deck♡\033[0m");
            rpc::assetConfirmed = false;
            nfaDeck.close();
        }else {
            rpc::assetConfirmed = false;
            nfaDeck.close();
        }

    }

}


void MainWindow::AZYPCB(QString pre, rpc& r)
{
    QString start;
    QString add;
    int i = 1;

    do {
        start = "000";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/AZYPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "AZYPCB"+add);
                qInfo() << ("\033[35m♧Loading AZYPC Back♢\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 10);

    do {
        start = "00";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/AZYPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "AZYPCB"+add);
                qInfo() << ("\033[35m♧Loading AZYPC Back♢\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 100);

    do {
        start = "0";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/AZYPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "AZYPCB"+add);
                qInfo() << ("\033[35m♧Loading AZYPC Back♢\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 1000);

    add = start+QString::number(i);
    QFile nfaBack(pre+"/cards/AZYPCB"+add+"/README.md");
    nfaBack.open(QIODevice::ReadOnly);

    if(nfaBack.exists()){
        QString findAddr = nfaBack.readAll();
        findAddr = readmeStandard(findAddr);
        r.verifyNFAcreator(findAddr);
        if(rpc::assetConfirmed == true){
            ui->deckComboBox->insertItem(ui->backComboBox->count()+1, "AZYPCB"+add);
            qInfo() << ("\033[35m♧Loading AZYPC Back♢\033[0m");
            rpc::assetConfirmed = false;
            nfaBack.close();
        }else {
            rpc::assetConfirmed = false;
            nfaBack.close();
        }

    }
}


void MainWindow::SIXPC(QString pre, rpc& r)
{
    QString start;
    QString add;
    int i = 1;

    do {
        start = "000";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/SIXPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "SIXPC"+add);
                qInfo() << ("\033[35m♤Loading SIXPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 10);

    do {
        start = "00";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/SIXPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "SIXPC"+add);
                qInfo() << ("\033[35m♤Loading SIXPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 100);

    do {
        start = "0";
        add = start+QString::number(i);
        QFile nfaDeck(pre+"/cards/SIXPC"+add+"/README.md");
        nfaDeck.open(QIODevice::ReadOnly);

        if(nfaDeck.exists()){
            QString findAddr = nfaDeck.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "SIXPC"+add);
                qInfo() << ("\033[35m♤Loading SIXPC Deck♡\033[0m");
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }else {
                rpc::assetConfirmed = false;
                nfaDeck.close();
            }

        }
        ++i;
    }while(i < 1000);

    add = start+QString::number(i);
    QFile nfaDeck(pre+"/cards/SIXPC"+add+"/README.md");
    nfaDeck.open(QIODevice::ReadOnly);

    if(nfaDeck.exists()){
        QString findAddr = nfaDeck.readAll();
        findAddr = readmeStandard(findAddr);
        r.verifyNFAcreator(findAddr);
        if(rpc::assetConfirmed == true){
            ui->deckComboBox->insertItem(ui->deckComboBox->count()+1, "SIXPC"+add);
            qInfo() << ("\033[35m♤Loading SIXPC Deck♡\033[0m");
            rpc::assetConfirmed = false;
            nfaDeck.close();
        }else {
            rpc::assetConfirmed = false;
            nfaDeck.close();
        }

    }

}


void MainWindow::SIXPCB(QString pre, rpc& r)
{
    QString start;
    QString add;
    int i = 1;

    do {
        start = "000";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/SIXPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "SIXPCB"+add);
                qInfo() << ("\033[35m♢Loading SIXPC Back♧\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 10);

    do {
        start = "00";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/SIXPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "SIXPCB"+add);
                qInfo() << ("\033[35m♢Loading SIXPC Back♧\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 100);

    do {
        start = "0";
        add = start+QString::number(i);
        QFile nfaBack(pre+"/cards/backs/SIXPCB"+add+"/README.md");
        nfaBack.open(QIODevice::ReadOnly);

        if(nfaBack.exists()){
            QString findAddr = nfaBack.readAll();
            findAddr = readmeStandard(findAddr);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->backComboBox->insertItem(ui->backComboBox->count()+1, "SIXPCB"+add);
                qInfo() << ("\033[35m♢Loading SIXPC Back♧\033[0m");
                rpc::assetConfirmed = false;
                nfaBack.close();
            }else {
                rpc::assetConfirmed = false;
                nfaBack.close();
            }
        }
        ++i;
    }while(i < 1000);

    add = start+QString::number(i);
    QFile nfaBack(pre+"/cards/SIXPCB"+add+"/README.md");
    nfaBack.open(QIODevice::ReadOnly);

    if(nfaBack.exists()){
        QString findAddr = nfaBack.readAll();
        findAddr = readmeStandard(findAddr);
        r.verifyNFAcreator(findAddr);
        if(rpc::assetConfirmed == true){
            ui->deckComboBox->insertItem(ui->backComboBox->count()+1, "SIXPCB"+add);
            qInfo() << ("\033[35m♢Loading SIXPC Back♧\033[0m");
            rpc::assetConfirmed = false;
            nfaBack.close();
        }else {
            rpc::assetConfirmed = false;
            nfaBack.close();
        }

    }
}
