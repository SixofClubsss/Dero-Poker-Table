/*
dReam Tables Five Card Draw Poker

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
#include "rpc.h"
#include "QTimer"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->daemonConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->daemonConnectedBox->setFocusPolicy(Qt::NoFocus);
    this->ui->walletConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->walletConnectedBox->setFocusPolicy(Qt::NoFocus);
    this->ui->p1CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->p1CheckBox->setFocusPolicy(Qt::NoFocus);
    this->ui->p2CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->p2CheckBox->setFocusPolicy(Qt::NoFocus);
    this->ui->p3CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->p3CheckBox->setFocusPolicy(Qt::NoFocus);
    this->ui->p4CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->p4CheckBox->setFocusPolicy(Qt::NoFocus);
    this->ui->p5CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->p5CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->logTextBrowser->setText("Welcome to the Table, Thanks for Testing");
    ui->daemonRPCinput->setText(rpc::daemonAddressToMain);
    fetchScData();
    ui->dealHandPushButton->setEnabled(false);
    ui->drawPushButton->setEnabled(false);
    ui->drawComboBox->setEnabled(false);
    ui->betButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->gameKeyPushButton->setEnabled(false);
    ui->payoutPushButton->setEnabled(false);
    ui->shuffleButton->setEnabled(false);
    blankDisplay();
    /// SC refresh
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),
          this, SLOT(refresh()));
    timer->start(9000);

}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::refresh()
{
    fetchScData();
    fetchHandData();
}


void MainWindow::on_helpButton_clicked()
{
    Menu m;
    m.setModal(true);
    m.exec();
}

void MainWindow::on_daemonRPCbutton_clicked(bool checked)
{
    checkDaemon();
}


void MainWindow::on_walletRPCbutton_clicked(bool checked)
{
    checkWallet();
}

void MainWindow::on_gameKeyPushButton_clicked()
{
    verifyGameKey();
    fetchScData();
}


void MainWindow::on_dealHandPushButton_clicked()
{
    dealFiveCardHand();
}

void MainWindow::on_ownerPushButton_clicked()
{
    setTable();
    delay();
    showGameKey();
}

void MainWindow::on_drawPushButton_clicked()
{
    Hand::hasBet = false;
    drawCards();
}

void MainWindow::on_entryPushButton_clicked()
{
    playerEntry();
    delay();
    verifyGameKey();
}

void MainWindow::on_payoutPushButton_clicked()
{
    Hand::endSignal = false;
    winner();
}

void MainWindow::on_betButton_clicked()
{
    bet();
}

void MainWindow::on_checkButton_clicked()
{
    check();
}

void MainWindow::on_shuffleButton_clicked()
{
    shuffleDeck();
}
