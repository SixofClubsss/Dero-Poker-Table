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
#include "rpc/rpc.h"
#include "hands/handranks.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFonts();
    MainWindow::startUpSkip = true;
    ui->p1CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p1CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p2CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p2CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p3CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p3CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p4CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p4CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p5CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p5CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p6CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p6CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->logTextBrowser->setText("dReam Tables, Built on Dero\n\nHoldero Table v1.0.0");
    MainWindow::skipCount = 0;
    ui->entryPushButton->setEnabled(false);
    ui->dealHandPushButton->setEnabled(false);
    ui->betButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->leaveButton->setEnabled(false);
    ui->payoutPushButton->setEnabled(false);
    ui->winnerComboBox->setEnabled(false);
    MainWindow::clicked = false;
    blankDisplay();
    generateKey();
    checkDecks();
}


MainWindow::~MainWindow()
{
    QFile keyFile(".handKey");
    keyFile.open(QIODevice::ReadWrite);

    if(keyFile.exists()) {
        keyFile.remove();
    }

    QFile scriptFile("contract/createTable.sh");
    scriptFile.open(QIODevice::ReadWrite);

    if(scriptFile.exists()) {
        scriptFile.remove();
    }

    qInfo() << ("\033[36m♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
    qInfo() << ("\033[36m          Exiting...\033[0m");
    qInfo() << ("\033[36m♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");

    Worker::workThread.quit();
    delete ui;
}


void MainWindow::offset()            /// Offset timer
{
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::setFonts()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular23(fontFamily);
    QFont macondoRegular20(fontFamily);
    QFont macondoRegular11(fontFamily);
    macondoRegular23.setPointSize(23);
    macondoRegular20.setPointSize(20);
    macondoRegular11.setPointSize(11);
    macondoRegular23.setBold(true);
    macondoRegular20.setBold(true);
    macondoRegular11.setBold(true);
    ui->logTextBrowser->setFont(macondoRegular23);
    ui->turnReadOut->setFont(macondoRegular20);
    ui->p1CheckBox->setFont(macondoRegular11);
    ui->p2CheckBox->setFont(macondoRegular11);
    ui->p3CheckBox->setFont(macondoRegular11);
    ui->p4CheckBox->setFont(macondoRegular11);
    ui->p5CheckBox->setFont(macondoRegular11);
    ui->p6CheckBox->setFont(macondoRegular11);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(10);
    ui->groupBoxP1->setFont(ubuntuRegular);
    ui->playerId->setFont(ubuntuRegular);
    ui->dsbTurn->setFont(ubuntuRegular);
    ui->dsbDealer->setFont(ubuntuRegular);
    ui->betSpinBox->setFont(ubuntuRegular);
    ui->checkButton->setFont(ubuntuRegular);
    ui->betButton->setFont(ubuntuRegular);
    ui->dealHandPushButton->setFont(ubuntuRegular);
    ui->payoutPushButton->setFont(ubuntuRegular);
    ui->winnerComboBox->setFont(ubuntuRegular);
    ui->balanceDoubleSpinBox->setFont(ubuntuRegular);
    ui->menuButton->setFont(ubuntuRegular);
    ui->leaveButton->setFont(ubuntuRegular);
    ui->entryPushButton->setFont(ubuntuRegular);
    ui->anteIsDSB->setFont(ubuntuRegular);
    ui->dsbPot->setFont(ubuntuRegular);
    ui->dsbSeats->setFont(ubuntuRegular);
    ui->handRankButton->setFont(ubuntuRegular);
    ui->dsbBlockHeight->setFont(ubuntuRegular);
    ui->txLogTextBrowser->setFont(ubuntuRegular);
}


void MainWindow::checkDecks()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Looking for NFA ♤♡♧♢♧♡♤\033[0m");
    rpc r;
    QString pre = QDir().absolutePath();
    AZYPC(pre, r);
    AZYPCB(pre, r);
    SIXPC(pre, r);
    SIXPCB(pre, r);
}


void MainWindow::refresh()      /// Controller refresh rate
{
    if((rpc::turn != ui->playerId->value()-1 && rpc::blockHeight > rpc::clickedHeight+1 && ui->playerId->value() != 0) ||
            (rpc::turn == ui->playerId->value()-1 && rpc::blockHeight > rpc::clickedHeight+3)){
        MainWindow::clicked = false;
    }

    ui->dsbBlockHeight->setValue(rpc::blockHeight);
    offset();
    if(MainWindow::clicked == false){
        controller();
        MainWindow::skipCount = 0;
    }else {
        MainWindow::skipCount++;
        if(MainWindow::skipCount >= 8){
            MainWindow::clicked = false;
            MainWindow::skipCount = 0;
        }
    }
}


void MainWindow::buttonCatch()  /// When player confirms a action
{
    buttonDelay();
    MainWindow::clicked = true;
    rpc::clickedHeight = ui->dsbBlockHeight->value();
}


void MainWindow::buttonDelay()  /// When any button has been pressed disabled all button for buffer period
{
    ui->entryPushButton->setEnabled(false);
    ui->leaveButton->setEnabled(false);
    ui->dealHandPushButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->betButton->setEnabled(false);

    ui->payoutPushButton->setEnabled(false);
    ui->winnerComboBox->setEnabled(false);
    ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; background-color: rgba(85, 88, 93, 90); color: rgb(255, 255, 255);};" );
    ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 2px solid gray; border-radius: 5px; };" );
    ui->turnReadOut->setText("Wait For Block");
}


void MainWindow::on_menuButton_clicked()
{
    Menu m;
    m.setModal(true);
    m.exec();
}


void MainWindow::on_dealHandPushButton_clicked()
{
    buttonCatch();
    dealHand();
}


void MainWindow::on_entryPushButton_clicked()
{
    buttonCatch();
    playerEntry();
}


void MainWindow::on_payoutPushButton_clicked()
{
    buttonCatch();
    Hand::endSignal = false;
    winner();
}


void MainWindow::on_betButton_clicked()
{
    buttonCatch();
    bet();
}


void MainWindow::on_checkButton_clicked()
{
    buttonCatch();
    check();
}


void MainWindow::on_leaveButton_clicked()
{
    buttonCatch();
    playerLeave();
}


void MainWindow::on_handRankButton_clicked()
{
    HandRanks hr;
    hr.setModal(false);
    hr.exec();
}
