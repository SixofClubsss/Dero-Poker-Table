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
#include "ui_mainwindow.h"
#include "menu.h"
#include "ui_menu.h"


QString MainWindow::readmeStandard(QFile &file)
{
    QString scid;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString s = "SCID:";
        QString line = in.readLine();
        QString check = line;
        check.chop(65);
        if(check == s){
            scid = line;
            scid.remove(0, 6);
            return scid;
        }
    }
    return scid;
}

QString Menu::readmeStandard(QFile &file)
{
    QString scid;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString s = "SCID:";
        QString line = in.readLine();
        QString check = line;
        check.chop(65);
        if(check == s){
            scid = line;
            scid.remove(0, 6);
            return scid;
        }
    }
    return scid;
}


void Menu::AZYDS(QString pre, rpc& r)
{
    QString start;
    QString add;
    int i = 1;

    do {
        start = "000";
        add = start+QString::number(i);
        QFile nfaScape(pre+"/cards/AZYDS"+add+"/README.md");
        nfaScape.open(QIODevice::ReadOnly);

        if(nfaScape.exists()){
            QString findAddr = readmeStandard(nfaScape);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS"+add);
                qInfo() << ("\033[35m♤Loading AZYDS♢\033[0m");
                rpc::assetConfirmed = false;
                nfaScape.close();
            }else {
                rpc::assetConfirmed = false;
                nfaScape.close();
            }

        }
        ++i;
    }while(i < 10);

    do {
        start = "00";
        add = start+QString::number(i);
        QFile nfaScape(pre+"/cards/AZYDS"+add+"/README.md");
        nfaScape.open(QIODevice::ReadOnly);

        if(nfaScape.exists()){
            QString findAddr = readmeStandard(nfaScape);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS"+add);
                qInfo() << ("\033[35m♤Loading AZYDS♢\033[0m");
                rpc::assetConfirmed = false;
                nfaScape.close();
            }else {
                rpc::assetConfirmed = false;
                nfaScape.close();
            }

        }
        ++i;
    }while(i < 100);

    do {
        start = "0";
        add = start+QString::number(i);
        QFile nfaScape(pre+"/cards/AZYDS"+add+"/README.md");
        nfaScape.open(QIODevice::ReadOnly);

        if(nfaScape.exists()){
            QString findAddr = readmeStandard(nfaScape);
            r.verifyNFAcreator(findAddr);
            if(rpc::assetConfirmed == true){
                ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS"+add);
                qInfo() << ("\033[35m♤Loading AZYDS♢\033[0m");
                rpc::assetConfirmed = false;
                nfaScape.close();
            }else {
                rpc::assetConfirmed = false;
                nfaScape.close();
            }

        }
        ++i;
    }while(i < 1000);

    add = start+QString::number(i);
    QFile nfaScape(pre+"/cards/AZYDS"+add+"/README.md");
    nfaScape.open(QIODevice::ReadOnly);

    if(nfaScape.exists()){
        QString findAddr = readmeStandard(nfaScape);
        r.verifyNFAcreator(findAddr);
        if(rpc::assetConfirmed == true){
            ui->themeComboBox->insertItem(ui->themeComboBox->count()+1, "AZYDS"+add);
            qInfo() << ("\033[35m♤Loading AZYDS♢\033[0m");
            rpc::assetConfirmed = false;
            nfaScape.close();
        }else {
            rpc::assetConfirmed = false;
            nfaScape.close();
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
            QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaDeck);
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
        QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaBack);
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
            QString findAddr = readmeStandard(nfaBack);
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
            QString findAddr = readmeStandard(nfaBack);
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
        QString findAddr = readmeStandard(nfaBack);
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
            QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaDeck);
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
        QString findAddr = readmeStandard(nfaDeck);
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
            QString findAddr = readmeStandard(nfaBack);
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
            QString findAddr = readmeStandard(nfaBack);
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
            QString findAddr = readmeStandard(nfaBack);
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
        QString findAddr = readmeStandard(nfaBack);
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
