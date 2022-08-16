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
#include "rpc/rpc.h"
#include "menu.h"


bool MainWindow::clicked;
bool MainWindow::startUpSkip;
bool MainWindow::displayedRes;
int MainWindow::skipCount;

bool Hand::hasBet;
bool Hand::endSignal;
bool Hand::foldOne;
bool Hand::foldTwo;
bool Hand::foldThree;
bool Hand::foldFour;
bool Hand::foldFive;
bool Hand::foldSix;
bool Hand::keyIsPub;

string rpc::rpcLogin;
bool rpc::inGame;
bool rpc::paidOut;
bool rpc::assetConfirmed;
int rpc::checkPlayerId;
int rpc::seats;
int rpc::draw;
int rpc::end;
int rpc::bet;
int rpc::IV;
int rpc::OBF;
int rpc::p1Fold;
int rpc::p2Fold;
int rpc::p3Fold;
int rpc::p4Fold;
int rpc::p5Fold;
int rpc::p6Fold;
int rpc::p1Out;
int rpc::p2Out;
int rpc::p3Out;
int rpc::p4Out;
int rpc::p5Out;
int rpc::p6Out;
int rpc::full;
int rpc::open;
int rpc::salt;
int rpc::revealBool;

double rpc::blockHeight;
double rpc::clickedHeight;
double rpc::ante;
double rpc::turn;
double rpc::dealer;
double rpc::balance;
double rpc::pot;
double rpc::wager;
double rpc::raised;

QString rpc::daemonAddress;
QString rpc::playerAddress;
QString rpc::oneId;
QString rpc::twoId;
QString rpc::threeId;
QString rpc::fourId;
QString rpc::fiveId;
QString rpc::sixId;
QString rpc::IdHash;
QString rpc::contractSeed;
QString rpc::clientKey;

QString rpc::hashOne;
QString rpc::hashTwo;
QString rpc::hashThree;
QString rpc::hashFour;
QString rpc::hashFive;

QString rpc::hashOneone;
QString rpc::hashOnetwo;
QString rpc::hashOnethree;
QString rpc::hashOnefour;
QString rpc::hashOnefive;

QString rpc::hashTwoone;
QString rpc::hashTwotwo;
QString rpc::hashTwothree;
QString rpc::hashTwofour;
QString rpc::hashTwofive;

QString rpc::hashThreeone;
QString rpc::hashThreetwo;
QString rpc::hashThreethree;
QString rpc::hashThreefour;
QString rpc::hashThreefive;

QString rpc::hashFourone ;
QString rpc::hashFourtwo ;
QString rpc::hashFourthree ;
QString rpc::hashFourfour ;
QString rpc::hashFourfive ;

QString rpc::hashFiveone ;
QString rpc::hashFivetwo ;
QString rpc::hashFivethree ;
QString rpc::hashFivefour ;
QString rpc::hashFivefive ;

QString rpc::hashSixone;
QString rpc::hashSixtwo;
QString rpc::hashSixthree;
QString rpc::hashSixfour;
QString rpc::hashSixfive;

QString rpc::key1;
QString rpc::key2;
QString rpc::key3;
QString rpc::key4;
QString rpc::key5;
QString rpc::key6;


void MainWindow::payoutDelay(int seconds)            /// Delay for payout button to allow time to see end results
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::controller()       /// Ui control
{
    rpc::checkPlayerId = ui->playerId->value();
    foldedBools(rpc::p1Fold, rpc::p2Fold, rpc::p3Fold, rpc::p4Fold, rpc::p5Fold, rpc::p6Fold);
    hasLeft(rpc::p1Out, rpc::p2Out, rpc::p3Out, rpc::p4Out, rpc::p5Out, rpc::p6Out);
    clearFoldedDisplay(rpc::p1Fold, rpc::p2Fold, rpc::p3Fold, rpc::p4Fold, rpc::p5Fold, rpc::p6Fold);
    localEnd(rpc::oneId, rpc::seats, rpc::p1Fold, rpc::p2Fold, rpc::p3Fold, rpc::p4Fold, rpc::p5Fold, rpc::p6Fold);
    setOpenClosed(rpc::seats, rpc::ante, rpc::dealer);
    setPlayerStatus(rpc::p1Out, rpc::oneId, rpc::twoId, rpc::threeId, rpc::fourId, rpc::fiveId, rpc::sixId);
    highlightWhosTurn(rpc::turn, rpc::seats);
    isClosed(rpc::seats, rpc::full);
    setPlayerId(rpc::oneId, rpc::twoId, rpc::threeId, rpc::fourId, rpc::fiveId, rpc::sixId);
    potEmpty(rpc::pot);
    setMinBet(rpc::wager, rpc::raised);
    atTable();
    ownerAtTable(rpc::p1Out, rpc::oneId);
    isTableFull(rpc::seats, rpc::pot, rpc::turn);
    localPlayerControl(rpc::bet, rpc::draw, rpc::wager, rpc::ante, rpc::raised);
    storedEnd(rpc::end, rpc::oneId);
    localEndSignal(rpc::oneId);
    disableButtons();
    displayLocalHand(rpc::hashOne, rpc::hashTwo, rpc::hashThree, rpc::hashFour, rpc::hashFive);
    checkBalance(rpc::balance);
}


void MainWindow::checkBalance(double balance)
{
    ui->balanceDoubleSpinBox->setValue(balance/100000);
    MainWindow::startUpSkip = false;
}


void MainWindow::setOpenClosed(int seats, double ante, double dealer)       /// Sets display for seats open or closed, set dealer display, sets minium bet == ante
{
    ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; background-color: rgba(85, 88, 93, 90); color: rgb(255, 255, 255);};" );
    ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 2px solid gray; border-radius: 5px; };" );
    ui->betSpinBox->setMinimum(ante/100000);
    ui->anteIsDSB->setValue(ante/100000);
    ui->dsbDealer->setValue(dealer+1);

    switch(seats){
    case 0: ui->p1CheckBox->setText("Closed");
            ui->p2CheckBox->setText("Closed");
            ui->p3CheckBox->setText("Closed");
            ui->p4CheckBox->setText("Closed");
            ui->p5CheckBox->setText("Closed");
            ui->p6CheckBox->setText("Closed");
        break;

    case 2: ui->p2CheckBox->setText("Seat Open");
        break;

    case 3: ui->p2CheckBox->setText("Seat Open");
            ui->p3CheckBox->setText("Seat Open");
        break;

    case 4: ui->p2CheckBox->setText("Seat Open");
            ui->p3CheckBox->setText("Seat Open");
            ui->p4CheckBox->setText("Seat Open");
        break;

    case 5: ui->p2CheckBox->setText("Seat Open");
            ui->p3CheckBox->setText("Seat Open");
            ui->p4CheckBox->setText("Seat Open");
            ui->p5CheckBox->setText("Seat Open");
        break;

    case 6: ui->p2CheckBox->setText("Seat Open");
            ui->p3CheckBox->setText("Seat Open");
            ui->p4CheckBox->setText("Seat Open");
            ui->p5CheckBox->setText("Seat Open");
            ui->p6CheckBox->setText("Seat Open");
        break;
    }
}


void MainWindow::setPlayerStatus(int p1Out, QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId)   ///Sets player indicator if players are at table and folded or in pot
{
    if(!oneId.isEmpty()){
        ui->p1CheckBox->setChecked(true);

        if(Hand::foldOne == true){
            ui->p1CheckBox->setText("Player 1 Folded");
            if(p1Out == 1){
                ui->p1CheckBox->setText("Sitting Out");
            }
        }else {
            ui->p1CheckBox->setText("Player 1");
        }

    }else {
        ui->p1CheckBox->setChecked(false);
    }


    if(!twoId.isEmpty()){
        ui->p2CheckBox->setChecked(true);

        if(Hand::foldTwo == true){
            ui->p2CheckBox->setText("Player 2 Folded");
        }else {
            ui->p2CheckBox->setText("Player 2");
        }

    }else {
        ui->p2CheckBox->setChecked(false);
    }


    if(!threeId.isEmpty()){
        ui->p3CheckBox->setChecked(true);

        if(Hand::foldThree == true){
            ui->p3CheckBox->setText("Player 3 Folded");
        }else {
            ui->p3CheckBox->setText("Player 3");
        }

    }else {
        ui->p3CheckBox->setChecked(false);
    }


    if(!fourId.isEmpty()){
        ui->p4CheckBox->setChecked(true);

        if(Hand::foldFour == true){
            ui->p4CheckBox->setText("Player 4 Folded");
        }else {
            ui->p4CheckBox->setText("Player 4");
        }

    }else {
        ui->p4CheckBox->setChecked(false);
    }


    if(!fiveId.isEmpty()){
        ui->p5CheckBox->setChecked(true);

        if(Hand::foldFive == true){
            ui->p5CheckBox->setText("Player 5 Folded");
        }else {
            ui->p5CheckBox->setText("Player 5");
        }

    }else {
        ui->p5CheckBox->setChecked(false);
    }


    if(!sixId.isEmpty()){
        ui->p6CheckBox->setChecked(true);

        if(Hand::foldSix == true){
            ui->p6CheckBox->setText("Player 6 Folded");
        }else {
            ui->p6CheckBox->setText("Player 6");
        }

    }else {
        ui->p6CheckBox->setChecked(false);
    }
}


void MainWindow::highlightWhosTurn(int turn, int seats)     /// Highlight player indicator when player turn
{
    ui->p1CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );
    ui->p2CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );
    ui->p3CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );
    ui->p4CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );
    ui->p5CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );
    ui->p6CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgba(255, 255, 255, 180); border: 2px solid gray; border-radius: 5px; border-style: inset; };" );

    if(turn != seats){
        switch(turn){
        case 0: ui->p1CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        case 1: ui->p2CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        case 2: ui->p3CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        case 3: ui->p4CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        case 4: ui->p5CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        case 5: ui->p6CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" ); break;
        }
    }
}


void MainWindow::isClosed(int seats, int full)         /// When table is closed or full
{
    if(seats == 0){
       ui->entryPushButton->setEnabled(false);
       ui->playerId->setValue(0);
    }else {
       ui->entryPushButton->setEnabled(true);
    }

    if(rpc::open <= 1 && rpc::p1Out == 1){
        ui->entryPushButton->setEnabled(false);
    }

    if(full == 1){
        ui->entryPushButton->setEnabled(false);
    }
}


void MainWindow::setPlayerId(QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId)       /// Sets player Id by IdHash
{
    if(oneId == rpc::IdHash){
       ui->playerId->setValue(1);

    }else if(twoId == rpc::IdHash){
       ui->playerId->setValue(2);

    }else if(threeId == rpc::IdHash){
       ui->playerId->setValue(3);

    }else if(fourId == rpc::IdHash){
       ui->playerId->setValue(4);

    }else if(fiveId == rpc::IdHash){
       ui->playerId->setValue(5);

    }else if(sixId == rpc::IdHash){
       ui->playerId->setValue(6);

    }else {
        ui->playerId->setValue(0);
    }
}


void MainWindow::potEmpty(double pot)       ///  Blank display when hand is payed out
{
    if(pot == 0){
        Hand::hasBet = false;
        Hand::endSignal = false;
        blankDisplay();
        ui->payoutPushButton->setEnabled(false);
        ui->winnerComboBox->setEnabled(false);
        rpc::paidOut = false;
        Hand::keyIsPub = false;
        MainWindow::displayedRes = false;
    }
}


void MainWindow::setMinBet(double wager, double raised)     /// Sets minimum bet to wager or raised depending on local bet bool
{
    if(Hand::hasBet == true){
        if(raised > 0){
            ui->betSpinBox->setMinimum(raised/100000);
            ui->betSpinBox->setMaximum(raised/100000);
        }else {
            if(wager > 0){
                ui->betSpinBox->setMinimum(wager/100000);
                ui->betSpinBox->setMaximum(100000000);
            }else{
                ui->betSpinBox->setMinimum(rpc::ante/100000);
            }
        }

    }else {
        ui->betSpinBox->setMinimum(wager/100000);
        ui->betSpinBox->setMaximum(100000000);

        if(raised > 0){
            ui->betSpinBox->setMaximum(wager/100000);
        }
    }
}


void MainWindow::atTable()                  /// Player table button control
{
    if(ui->playerId->value()  > 1){
        ui->winnerComboBox->setEnabled(false);
        ui->payoutPushButton->setEnabled(false);
        ui->entryPushButton->setEnabled(false);
    }
}


void MainWindow::ownerAtTable(int p1Out, QString oneId)        /// Owner table button controls
{
    if(oneId == rpc::IdHash){
        ui->entryPushButton->setEnabled(false);

        if(p1Out == 1){
            ui->entryPushButton->setEnabled(true);
        }

    }
}


void MainWindow::isTableFull(double seats, double pot, double turn)      /// When table is full owner can start game
{
    if(seats == turn){
        ui->dsbTurn->setValue(1);
        ui->dsbSeats->setValue(seats);
        ui->dsbPot->setValue(pot/100000);
        ui->p1CheckBox->setStyleSheet( "QCheckBox{ color: rgb(0, 0, 0); background-color: rgb(255, 255, 255); border: 3px solid gray; border-radius: 5px; border-color: rgb(56, 47, 165); };" );
    }else {
        ui->dsbTurn->setValue(turn+1);
        ui->dsbSeats->setValue(seats);
        ui->dsbPot->setValue(pot/100000);
    }

}


void MainWindow::localPlayerControl(int bet, int draw, double wager, double ante, double raised)        /// Is players turn
{
    if(ui->dsbTurn->value() == ui->playerId->value()){   /// Local players turn button control
        if(rpc::end != 1){
        ui->dealHandPushButton->setEnabled(true);
        }
        ui->leaveButton->setEnabled(true);

        if(bet >= 1){                          /// Sets buttons when in bet
            ui->dealHandPushButton->setEnabled(false);
            ui->checkButton->setText("Check");
            ui->checkButton->setEnabled(true);
            ui->betButton->setText("Bet");
            ui->betButton->setEnabled(true);
            ui->leaveButton->setEnabled(false);
            ui->entryPushButton->setEnabled(false);
        }else {
            ui->betButton->setEnabled(false);
        }


        if(wager > 0){                    /// Sets buttons when wager in play
            ui->dealHandPushButton->setEnabled(false);
            ui->checkButton->setText("Fold");
            ui->checkButton->setEnabled(true);
            ui->betButton->setText("Call/Raise");
            ui->betButton->setEnabled(true);
            ui->drawPushButton->setEnabled(false);
            ui->drawComboBox->setEnabled(false);
            ui->leaveButton->setEnabled(false);
            QString w = QString::number(wager/100000);
            ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; color: rgb(255, 255, 255); background-color: rgb(56, 47, 165); };" );
            ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); };" );
            ui->turnReadOut->setText("Bet is "+w);
            ui->turnReadOut->insertPlainText("Your Turn    ");
        }else {
            if(Hand::keyIsPub == false){
                ui->turnReadOut->setText("Your Turn");
            }
            ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; color: rgb(255, 255, 255); background-color: rgb(56, 47, 165); };" );
            ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); };" );


            if(draw == 1){                 /// Local player draw button control
                ui->drawPushButton->setEnabled(true);
                ui->drawComboBox->setEnabled(true);
                ui->dealHandPushButton->setEnabled(false);
                ui->checkButton->setEnabled(false);
                ui->leaveButton->setEnabled(false);
                ui->turnReadOut->insertPlainText("Draw, ");
                highlightCards();

            }else {
                ui->drawPushButton->setEnabled(false);
                ui->drawComboBox->setEnabled(false);
                clearHighlight();
            }
        }


        if(wager == 0){                        /// Sets min bet amount when there is no wager
             ui->betSpinBox->setMinimum(ante/100000);
             ui->betSpinBox->setMaximum(100000000);
        }


        if(raised > 0){                    /// Sets buttons when raised in play
            QString w = QString::number(wager/100000);
            QString r = QString::number(raised/100000);
            ui->betButton->setText("Call");
            ui->turnReadOut->setText("     Raised "+r);
            ui->turnReadOut->insertPlainText("Your Turn    ");
            ui->turnReadOut->insertPlainText("Bet is "+w);
        }

        if(rpc::revealBool == 1 && Hand::keyIsPub == false){
            if(Hand::endSignal == false){
                ui->turnReadOut->setText("Revealing key");
                revealKey();
            }
        }

    }else {
        ui->dealHandPushButton->setEnabled(false);            /// Not your turn controls
        ui->checkButton->setEnabled(false);
        ui->betButton->setEnabled(false);
        ui->drawPushButton->setEnabled(false);
        ui->drawComboBox->setEnabled(false);
        ui->leaveButton->setEnabled(false);
        QString p = QString::number(ui->dsbTurn->value());
        ui->turnReadOut->setText("Player "+p+"'s Turn");
    }
}


void MainWindow::storedEnd(int end, QString oneId)     /// End game show all hands,  start up skip
{
    if(end == 1){
        ui->betButton->setEnabled(false);
        ui->checkButton->setEnabled(false);
        ui->drawPushButton->setEnabled(false);
        ui->drawComboBox->setEnabled(false);
        ui->dealHandPushButton->setEnabled(false);
        ui->leaveButton->setEnabled(false);
        endResults(rpc::seats, rpc::p1Fold, rpc::p2Fold, rpc::p3Fold, rpc::p4Fold, rpc::p5Fold, rpc::p6Fold);

        if(MainWindow::startUpSkip == false){

            if(oneId == rpc::IdHash){

                if(Menu::autoPayout == false){
                    payoutDelay(30);
                    ui->payoutPushButton->setEnabled(true);
                    ui->winnerComboBox->setEnabled(true);
                }
            }
        }
    }
}


void MainWindow::localEndSignal(QString oneId)     /// Local end signal, all players have folded
{
    if(Hand::endSignal == true){
        ui->turnReadOut->setText("Players have all folded, payout");
        ui->betButton->setEnabled(false);
        ui->checkButton->setEnabled(false);
        ui->drawPushButton->setEnabled(false);
        ui->drawComboBox->setEnabled(false);
        ui->dealHandPushButton->setEnabled(false);
        ui->leaveButton->setEnabled(false);
        if(oneId == rpc::IdHash && Menu::autoPayout == false){
            ui->payoutPushButton->setEnabled(true);
            ui->winnerComboBox->setEnabled(true);
        }
    }
}


void MainWindow::disableButtons()   /// Buttons not in play
{
    if(ui->dealHandPushButton->isEnabled()){
        ui->checkButton->setEnabled(false);
        ui->betButton->setEnabled(false);
        ui->drawPushButton->setEnabled(false);
        ui->drawComboBox->setEnabled(false);
        ui->payoutPushButton->setEnabled(false);
        ui->winnerComboBox->setEnabled(false);
        blankDisplay();

    }

    if(rpc::revealBool == 1){
        ui->betButton->setEnabled(false);
        ui->checkButton->setEnabled(false);
        ui->drawPushButton->setEnabled(false);
        ui->drawComboBox->setEnabled(false);
        ui->dealHandPushButton->setEnabled(false);
        ui->leaveButton->setEnabled(false);
    }

}


void MainWindow::foldedBools(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold)      /// Sets player indicator text to fold when player folds and sets payout menu
{
    if(rpc::end != 1){
        ui->winnerComboBox->insertItem(0, "Player1");
        ui->winnerComboBox->insertItem(1, "Player2");
        ui->winnerComboBox->insertItem(2, "Player3");
        ui->winnerComboBox->insertItem(3, "Player4");
        ui->winnerComboBox->insertItem(4, "Player5");
        ui->winnerComboBox->insertItem(5, "Player6");

        ui->winnerComboBox->setMaxCount(rpc::seats);

        if(p6Fold == 1){
            Hand::foldSix = true;
            ui->winnerComboBox->removeItem(5);
        }else {
            Hand::foldSix = false;
        }

        if(p5Fold == 1){
            Hand::foldFive = true;
            ui->winnerComboBox->removeItem(4);
        }else {
            Hand::foldFive = false;
        }

        if(p4Fold == 1){
            Hand::foldFour = true;
            ui->winnerComboBox->removeItem(3);
        }else {
            Hand::foldFour = false;
        }

        if(p3Fold == 1){
            Hand::foldThree = true;
            ui->winnerComboBox->removeItem(2);
        }else {
            Hand::foldThree = false;
        }

        if(p2Fold == 1){
            Hand::foldTwo = true;
            ui->winnerComboBox->removeItem(1);
        }else {
            Hand::foldTwo = false;
        }

        if(p1Fold == 1){
            Hand::foldOne = true;
            ui->winnerComboBox->removeItem(0);
        }else {
            Hand::foldOne = false;
        }
    }

}


void MainWindow::hasLeft(int p1Out, int p2Out, int p3Out, int p4Out, int p5Out, int p6Out)      /// Sets player indicator text when player has left table
{
    if(p1Out == 1){
        ui->p1CheckBox->setText("Sitting Out");
    }

    if(p2Out == 1){
        ui->p2CheckBox->setText("Seat Open");
    }

    if(p3Out == 1){
        ui->p3CheckBox->setText("Seat Open");
    }

    if(p4Out == 1){
        ui->p4CheckBox->setText("Seat Open");
    }

    if(p5Out == 1){
        ui->p5CheckBox->setText("Seat Open");
    }

    if(p6Out == 1){
        ui->p6CheckBox->setText("Seat Open");
    }
}


void MainWindow::clearFoldedDisplay(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold)      /// Blank display when folded
{
    if(p1Fold == 1 && rpc::checkPlayerId == 1){
        blankDisplay();
    }

    if(p2Fold == 1 && rpc::checkPlayerId == 2){
        blankDisplay();
    }

    if(p3Fold == 1 && rpc::checkPlayerId == 3){
        blankDisplay();
    }

    if(p4Fold == 1 && rpc::checkPlayerId == 4){
        blankDisplay();
    }

    if(p5Fold == 1 && rpc::checkPlayerId == 5){
        blankDisplay();
    }

    if(p6Fold == 1 && rpc::checkPlayerId == 6){
        blankDisplay();
    }
}


void MainWindow::localEnd(QString oneId, int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold)     /// All folded and Fold autopay
{
    int endCheck = p1Fold+p2Fold+p3Fold+p4Fold+p5Fold+p6Fold;  /// Check if all players have folded
    int end = seats-1;

    if(endCheck == end){   /// Local end signal
      Hand::endSignal = true;

      if(oneId == rpc::IdHash){

          if(Menu::autoPayout == true && rpc::pot != 0){         /// If autopay is selected in menu it will send to remaining player

              if(p1Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player1";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }

              }else if(p2Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player2";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }

              }else if(p3Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player3";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }

              }else if(p4Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player4";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }

              }else if(p5Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player5";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }

              }else if(p6Fold == 0){
                  if(rpc::paidOut == false){
                        rpc::paidOut = true;
                        QString whoWon = "Player6";
                        payoutDelay(15);
                        autopayWinner(whoWon);

                  }
              }

          }

      }

    }else {
      Hand::endSignal = false;
    }
}


void MainWindow::displayLocalHand(QString hashOne, QString hashTwo, QString hashThree, QString hashFour, QString hashFive)
{
    if(card(hashOne, rpc::salt) > 0){
        displayCardOne(card(hashOne, rpc::salt));
        displayCardTwo(card(hashTwo, rpc::salt));
        displayCardThree(card(hashThree, rpc::salt));
        displayCardFour(card(hashFour, rpc::salt));
        displayCardFive(card(hashFive, rpc::salt));
    }else {
        blankDisplay();
    }
}


int MainWindow::card(QString hash, int salt)  /// Gets local player card numbers for display from hash values
{
    for (int i = 1; i < 53; i++) {

         int salted = salt+i;
         QString finder = QString::number(salted);
         QString pcSeed = rpc::clientKey;
         QString scSeed = rpc::contractSeed;
         QString add = rpc::clientKey+finder+scSeed;
         QString naked = QString(QCryptographicHash::hash((add.toUtf8()),QCryptographicHash::Sha256).toHex());
         salted++;

         if(naked == hash){
             return i;
         }

    }
    return 0;

}


int MainWindow::keyCard(QString hash, int salt, int who)  /// After keys are revealed we get other player card numbers for display from hash values
{
    QString keyCheck;
    switch (who){
    case 1: keyCheck = rpc::key1; break;
    case 2: keyCheck = rpc::key2; break;
    case 3: keyCheck = rpc::key3; break;
    case 4: keyCheck = rpc::key4; break;
    case 5: keyCheck = rpc::key5; break;
    case 6: keyCheck = rpc::key6; break;
    }

    for (int i = 1; i < 53; i++) {

         int salted = salt+i;
         QString finder = QString::number(salted);
         QString scSeed = rpc::contractSeed;
         QString add = keyCheck+finder+scSeed;
         QString card = QString(QCryptographicHash::hash((add.toUtf8()),QCryptographicHash::Sha256).toHex());

         if(card == hash){
             return i;
         }

    }
    return 0;

}


void MainWindow::endResults(int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold)      /// Show all player cards
{

  if(Hand::endSignal == false && ui->playerId->value() > 0 && rpc::inGame == true){

    ui->logTextBrowser->setFontPointSize(30);

    ///Player 1 Decode hand result, sort and split into value and suits
    int player1HandRaw[] = { keyCard(rpc::hashOneone, rpc::salt, 1), keyCard(rpc::hashOnetwo, rpc::salt, 1), keyCard(rpc::hashOnethree, rpc::salt, 1), keyCard(rpc::hashOnefour, rpc::salt, 1), keyCard(rpc::hashOnefive, rpc::salt, 1) };

    if(seats >= 2 && rpc::p1Fold != 1){
        p1Rank = 100;
        p1HighPair = 0;
        getArray(player1HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p1HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player1HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p1HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player1HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p1HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player1HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p1HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player1HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p1HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p1Rank = makeHand();

        std::sort(p1HighCardArr, p1HighCardArr + 5);
        p1HighPair = getHighPair(p1HighCardArr);

    }else{
        p1Rank = 100;
    }


    ///Player 2 Decode hand result, sort and split into value and suits
    int player2HandRaw[] = { keyCard(rpc::hashTwoone, rpc::salt, 2), keyCard(rpc::hashTwotwo, rpc::salt, 2), keyCard(rpc::hashTwothree, rpc::salt, 2), keyCard(rpc::hashTwofour, rpc::salt, 2), keyCard(rpc::hashTwofive, rpc::salt, 2) };

    if(seats >= 2 && rpc::p2Fold != 1){
        p2Rank = 100;
        p2HighPair = 0;
        getArray(player2HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p2HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player2HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p2HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player2HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p2HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player2HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p2HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player2HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p2HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p2Rank = makeHand();

        std::sort(p2HighCardArr, p2HighCardArr + 5);
        p2HighPair = getHighPair(p2HighCardArr);

    }else{
        p2Rank = 100;
    }


    ///Player 3 Decode hand result, sort and split into value and suits
    int player3HandRaw[] = { keyCard(rpc::hashThreeone, rpc::salt, 3), keyCard(rpc::hashThreetwo, rpc::salt, 3), keyCard(rpc::hashThreethree, rpc::salt, 3), keyCard(rpc::hashThreefour, rpc::salt, 3), keyCard(rpc::hashThreefive, rpc::salt, 3) };

    if(seats >= 3 && rpc::p3Fold != 1){
        p3Rank = 100;
        p3HighPair = 0;
        getArray(player3HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p3HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player3HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p3HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player3HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p3HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player3HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p3HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player3HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p3HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p3Rank = makeHand();

        std::sort(p3HighCardArr, p3HighCardArr + 5);
        p3HighPair = getHighPair(p3HighCardArr);

    }else{
        p3Rank = 100;
    }


    ///Player 4 Deode hand result, sort and split into value and suits
    int player4HandRaw[] = { keyCard(rpc::hashFourone, rpc::salt, 4), keyCard(rpc::hashFourtwo, rpc::salt, 4), keyCard(rpc::hashFourthree, rpc::salt, 4), keyCard(rpc::hashFourfour, rpc::salt, 4), keyCard(rpc::hashFourfive, rpc::salt, 4) };

    if(seats >= 4 && rpc::p4Fold != 1){
        p4Rank = 100;
        p4HighPair = 0;
        getArray(player4HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p4HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player4HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p4HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player4HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p4HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player4HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p4HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player4HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p4HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p4Rank = makeHand();

        std::sort(p4HighCardArr, p4HighCardArr + 5);
        p4HighPair = getHighPair(p4HighCardArr);

    }else{
        p4Rank = 100;
    }

    ///Player 5 Deode hand result, sort and split into value and suits
    int player5HandRaw[] = { keyCard(rpc::hashFiveone, rpc::salt, 5), keyCard(rpc::hashFivetwo, rpc::salt, 5), keyCard(rpc::hashFivethree, rpc::salt, 5), keyCard(rpc::hashFivefour, rpc::salt, 5), keyCard(rpc::hashFivefive, rpc::salt, 5) };

    if(seats >= 5 && rpc::p5Fold != 1){
        p5Rank = 100;
        p5HighPair = 0;
        getArray(player5HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p5HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player5HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p5HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player5HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p5HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player5HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p5HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player5HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p5HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p5Rank = makeHand();

        std::sort(p5HighCardArr, p5HighCardArr + 5);
        p5HighPair = getHighPair(p5HighCardArr);

    }else{
        p5Rank = 100;
    }

    ///Player 6 Deode hand result, sort and split into value and suits
    int player6HandRaw[] = { keyCard(rpc::hashSixone, rpc::salt, 6), keyCard(rpc::hashSixtwo, rpc::salt, 6), keyCard(rpc::hashSixthree, rpc::salt, 6), keyCard(rpc::hashSixfour, rpc::salt, 6), keyCard(rpc::hashSixfive, rpc::salt, 6) };

    if(seats == 6 && rpc::p6Fold != 1){
        p6Rank = 100;
        p6HighPair = 0;
        getArray(player6HandRaw[0]);
        suitSplit1[0] = arrSplit[0];
        p6HighCardArr[0] = arrSplit[0];
        suitSplit1[1] = arrSplit[1];

        getArray(player6HandRaw[1]);
        suitSplit2[0] = arrSplit[0];
        p6HighCardArr[1] = arrSplit[0];
        suitSplit2[1] = arrSplit[1];

        getArray(player6HandRaw[2]);
        suitSplit3[0] = arrSplit[0];
        p6HighCardArr[2] = arrSplit[0];
        suitSplit3[1] = arrSplit[1];

        getArray(player6HandRaw[3]);
        suitSplit4[0] = arrSplit[0];
        p6HighCardArr[3] = arrSplit[0];
        suitSplit4[1] = arrSplit[1];

        getArray(player6HandRaw[4]);
        suitSplit5[0] = arrSplit[0];
        p6HighCardArr[4] = arrSplit[0];
        suitSplit5[1] = arrSplit[1];
        p6Rank = makeHand();

        std::sort(p6HighCardArr, p6HighCardArr + 5);
        p6HighPair = getHighPair(p6HighCardArr);

    }else{
        p6Rank = 100;
    }

    if(MainWindow::displayedRes == false){
        switch (seats){
        case 2:
            ui->logTextBrowser->setText("Player 1 Has: "+findCards(player1HandRaw[0])+" "+findCards(player1HandRaw[1])+" "+findCards(player1HandRaw[2])+" "+findCards(player1HandRaw[3])+" "+findCards(player1HandRaw[4])+"  "+handToText(p1Rank));
            ui->logTextBrowser->append("Player 2 Has: "+findCards(player2HandRaw[0])+" "+findCards(player2HandRaw[1])+" "+findCards(player2HandRaw[2])+" "+findCards(player2HandRaw[3])+" "+findCards(player2HandRaw[4])+"  "+handToText(p2Rank));
            break;

        case 3:
            ui->logTextBrowser->setText("");

            if(p1Fold != 1){
                ui->logTextBrowser->append("Player 1 Has: "+findCards(player1HandRaw[0])+" "+findCards(player1HandRaw[1])+" "+findCards(player1HandRaw[2])+" "+findCards(player1HandRaw[3])+" "+findCards(player1HandRaw[4])+"  "+handToText(p1Rank));
            }

            if(p2Fold != 1){
                ui->logTextBrowser->append("Player 2 Has: "+findCards(player2HandRaw[0])+" "+findCards(player2HandRaw[1])+" "+findCards(player2HandRaw[2])+" "+findCards(player2HandRaw[3])+" "+findCards(player2HandRaw[4])+"  "+handToText(p2Rank));
            }

            if(p3Fold != 1){
                ui->logTextBrowser->append("Player 3 Has: "+findCards(player3HandRaw[0])+" "+findCards(player3HandRaw[1])+" "+findCards(player3HandRaw[2])+" "+findCards(player3HandRaw[3])+" "+findCards(player3HandRaw[4])+"  "+handToText(p3Rank));
            }
            break;

        case 4:
            ui->logTextBrowser->setText("");

            if(p1Fold != 1){
                ui->logTextBrowser->append("Player 1 Has: "+findCards(player1HandRaw[0])+" "+findCards(player1HandRaw[1])+" "+findCards(player1HandRaw[2])+" "+findCards(player1HandRaw[3])+" "+findCards(player1HandRaw[4])+"  "+handToText(p1Rank));
            }

            if(p2Fold != 1){
                ui->logTextBrowser->append("Player 2 Has: "+findCards(player2HandRaw[0])+" "+findCards(player2HandRaw[1])+" "+findCards(player2HandRaw[2])+" "+findCards(player2HandRaw[3])+" "+findCards(player2HandRaw[4])+"  "+handToText(p2Rank));
            }

            if(p3Fold != 1){
                ui->logTextBrowser->append("Player 3 Has: "+findCards(player3HandRaw[0])+" "+findCards(player3HandRaw[1])+" "+findCards(player3HandRaw[2])+" "+findCards(player3HandRaw[3])+" "+findCards(player3HandRaw[4])+"  "+handToText(p3Rank));
            }

            if(p4Fold != 1){
                ui->logTextBrowser->append("Player 4 Has: "+findCards(player4HandRaw[0])+" "+findCards(player4HandRaw[1])+" "+findCards(player4HandRaw[2])+" "+findCards(player4HandRaw[3])+" "+findCards(player4HandRaw[4])+"  "+handToText(p4Rank));
            }
            break;

        case 5:
            ui->logTextBrowser->setText("");

            if(p1Fold != 1){
                ui->logTextBrowser->append("Player 1 Has: "+findCards(player1HandRaw[0])+" "+findCards(player1HandRaw[1])+" "+findCards(player1HandRaw[2])+" "+findCards(player1HandRaw[3])+" "+findCards(player1HandRaw[4])+"  "+handToText(p1Rank));
            }

            if(p2Fold != 1){
                ui->logTextBrowser->append("Player 2 Has: "+findCards(player2HandRaw[0])+" "+findCards(player2HandRaw[1])+" "+findCards(player2HandRaw[2])+" "+findCards(player2HandRaw[3])+" "+findCards(player2HandRaw[4])+"  "+handToText(p2Rank));
            }

            if(p3Fold != 1){
                ui->logTextBrowser->append("Player 3 Has: "+findCards(player3HandRaw[0])+" "+findCards(player3HandRaw[1])+" "+findCards(player3HandRaw[2])+" "+findCards(player3HandRaw[3])+" "+findCards(player3HandRaw[4])+"  "+handToText(p3Rank));
            }

            if(p4Fold != 1){
                ui->logTextBrowser->append("Player 4 Has: "+findCards(player4HandRaw[0])+" "+findCards(player4HandRaw[1])+" "+findCards(player4HandRaw[2])+" "+findCards(player4HandRaw[3])+" "+findCards(player4HandRaw[4])+"  "+handToText(p4Rank));
            }

            if(p5Fold != 1){
                ui->logTextBrowser->append("Player 5 Has: "+findCards(player5HandRaw[0])+" "+findCards(player5HandRaw[1])+" "+findCards(player5HandRaw[2])+" "+findCards(player5HandRaw[3])+" "+findCards(player5HandRaw[4])+"  "+handToText(p5Rank));
            }
            break;

        case 6:
            ui->logTextBrowser->setText("");

            if(p1Fold != 1){
                ui->logTextBrowser->append("Player 1 Has: "+findCards(player1HandRaw[0])+" "+findCards(player1HandRaw[1])+" "+findCards(player1HandRaw[2])+" "+findCards(player1HandRaw[3])+" "+findCards(player1HandRaw[4])+"  "+handToText(p1Rank));
            }

            if(p2Fold != 1){
                ui->logTextBrowser->append("Player 2 Has: "+findCards(player2HandRaw[0])+" "+findCards(player2HandRaw[1])+" "+findCards(player2HandRaw[2])+" "+findCards(player2HandRaw[3])+" "+findCards(player2HandRaw[4])+"  "+handToText(p2Rank));
            }

            if(p3Fold != 1){
                ui->logTextBrowser->append("Player 3 Has: "+findCards(player3HandRaw[0])+" "+findCards(player3HandRaw[1])+" "+findCards(player3HandRaw[2])+" "+findCards(player3HandRaw[3])+" "+findCards(player3HandRaw[4])+"  "+handToText(p3Rank));
            }

            if(p4Fold != 1){
                ui->logTextBrowser->append("Player 4 Has: "+findCards(player4HandRaw[0])+" "+findCards(player4HandRaw[1])+" "+findCards(player4HandRaw[2])+" "+findCards(player4HandRaw[3])+" "+findCards(player4HandRaw[4])+"  "+handToText(p4Rank));
            }

            if(p5Fold != 1){
                ui->logTextBrowser->append("Player 5 Has: "+findCards(player5HandRaw[0])+" "+findCards(player5HandRaw[1])+" "+findCards(player5HandRaw[2])+" "+findCards(player5HandRaw[3])+" "+findCards(player5HandRaw[4])+"  "+handToText(p5Rank));
            }

            if(p6Fold != 1){
                ui->logTextBrowser->append("Player 6 Has: "+findCards(player6HandRaw[0])+" "+findCards(player6HandRaw[1])+" "+findCards(player6HandRaw[2])+" "+findCards(player6HandRaw[3])+" "+findCards(player6HandRaw[4])+"  "+handToText(p6Rank));
            }
            break;

        }
    }

    int winningRank[] = {p1Rank, p2Rank, p3Rank, p4Rank, p5Rank, p6Rank};
    std::sort(winningRank, winningRank + 6);

    if(p1Rank < p2Rank && p1Rank < p3Rank && p1Rank < p4Rank && p1Rank < p5Rank && p1Rank < p6Rank){    /// If a players hand outrightly beats all other hands
        ui->turnReadOut->setText("Player 1 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player1";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else if(p2Rank < p1Rank && p2Rank < p3Rank && p2Rank < p4Rank && p2Rank < p5Rank && p2Rank < p6Rank){
        ui->turnReadOut->setText("Player 2 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player2";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else if(p3Rank < p1Rank && p3Rank < p2Rank && p3Rank < p4Rank && p3Rank < p5Rank && p3Rank < p6Rank){
        ui->turnReadOut->setText("Player 3 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player3";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else if(p4Rank < p1Rank && p4Rank < p2Rank && p4Rank < p3Rank && p4Rank < p5Rank && p4Rank < p6Rank){
        ui->turnReadOut->setText("Player 4 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player4";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else if(p5Rank < p1Rank && p5Rank < p2Rank && p5Rank < p3Rank && p5Rank < p4Rank && p5Rank < p6Rank){
        ui->turnReadOut->setText("Player 5 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player5";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else if(p6Rank < p1Rank && p6Rank < p2Rank && p6Rank < p3Rank && p6Rank < p4Rank && p6Rank < p5Rank){
        ui->turnReadOut->setText("Player 6 Wins");
        if(rpc::oneId == rpc::IdHash){

            if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                rpc::paidOut = true;
                QString whoWon = "Player6";
                payoutDelay(30);
                autopayWinner(whoWon);
            }

        }
    }else {

        int highestPair[] = { p1HighPair, p2HighPair, p3HighPair, p4HighPair, p5HighPair, p6HighPair };
        std::sort(highestPair, highestPair + 6);

        if(p1Rank != winningRank[0] || (winningRank[0] == 9 && p1HighPair != highestPair[5])){      /// If player hand is not the higest rank or if doesn't have high pair
            less1();
        }

        if(p2Rank != winningRank[0] || (winningRank[0] == 9 && p2HighPair != highestPair[5])){
            less2();
        }

        if(p3Rank != winningRank[0] || (winningRank[0] == 9 && p3HighPair != highestPair[5])){
            less3();
        }

        if((p4Rank != winningRank[0]) || (winningRank[0] == 9 && p4HighPair != highestPair[5])){
            less4();
        }

        if(p5Rank != winningRank[0] || (winningRank[0] == 9 && p5HighPair != highestPair[5])){
            less5();
        }

        if(p6Rank != winningRank[0] || (winningRank[0] == 9 && p6HighPair != highestPair[5])){
            less6();
        }


        if(winningRank[0] == 10){       /// Compares and strips loosing hands in high card situation
            compareLoop();
        }

        if(p1HighPair > p2HighPair && p1HighPair > p3HighPair && p1HighPair > p4HighPair && p1HighPair > p5HighPair && p1HighPair > p6HighPair){  /// If player has highest pairing
            if(p1Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 1 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player1";
                        payoutDelay(30);
                        autopayWinner(whoWon);
                    }

                }
            }
        }else if(p2HighPair > p1HighPair && p2HighPair > p3HighPair && p2HighPair > p4HighPair && p2HighPair > p5HighPair && p2HighPair > p6HighPair){
            if(p2Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 2 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player2";
                        payoutDelay(30);
                        autopayWinner(whoWon);
                    }

                }
            }
        }else if(p3HighPair > p1HighPair && p3HighPair > p2HighPair && p3HighPair > p4HighPair && p3HighPair > p5HighPair && p3HighPair > p6HighPair){
            if(p3Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 3 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player3";
                        payoutDelay(30);
                        autopayWinner(whoWon);
                    }

                }
            }
        }else if(p4HighPair > p1HighPair && p4HighPair > p2HighPair && p4HighPair > p3HighPair && p4HighPair > p5HighPair && p4HighPair > p6HighPair){
            if(p4Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 4 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player4";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }
        }else if(p5HighPair > p1HighPair && p5HighPair > p2HighPair && p5HighPair > p3HighPair && p5HighPair > p4HighPair && p5HighPair > p6HighPair){
            if(p5Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 5 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player5";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }
        }else if(p6HighPair > p1HighPair && p6HighPair > p2HighPair && p6HighPair > p3HighPair && p6HighPair > p4HighPair && p6HighPair > p5HighPair){
            if(p6Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 6 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player6";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }       /// Comapres all left over hands
        }else if((p1HighCardArr[4] > p2HighCardArr[4] && p1HighCardArr[4] > p3HighCardArr[4] && p1HighCardArr[4] > p4HighCardArr[4] && p1HighCardArr[4] > p5HighCardArr[4] && p1HighCardArr[4] > p6HighCardArr[4]) ||

                 (p1HighCardArr[4] >= p2HighCardArr[4] && p1HighCardArr[4] >= p3HighCardArr[4] && p1HighCardArr[4] >= p4HighCardArr[4] && p1HighCardArr[4] >= p5HighCardArr[4] && p1HighCardArr[4] >= p6HighCardArr[4] &&
                  p1HighCardArr[3] > p2HighCardArr[3] && p1HighCardArr[3] > p3HighCardArr[3] && p1HighCardArr[3] > p4HighCardArr[3] && p1HighCardArr[3] > p5HighCardArr[3] && p1HighCardArr[3] > p6HighCardArr[3]) ||

                 (p1HighCardArr[4] >= p2HighCardArr[4] && p1HighCardArr[4] >= p3HighCardArr[4] && p1HighCardArr[4] >= p4HighCardArr[4] && p1HighCardArr[4] >= p5HighCardArr[4] && p1HighCardArr[4] >= p6HighCardArr[4] &&
                  p1HighCardArr[3] >= p2HighCardArr[3] && p1HighCardArr[3] >= p3HighCardArr[3] && p1HighCardArr[3] >= p4HighCardArr[3] && p1HighCardArr[3] >= p5HighCardArr[3] && p1HighCardArr[3] >= p6HighCardArr[3] &&
                  p1HighCardArr[2] > p2HighCardArr[2] && p1HighCardArr[2] > p3HighCardArr[2] && p1HighCardArr[2] > p4HighCardArr[2] && p1HighCardArr[2] > p5HighCardArr[2] && p1HighCardArr[2] > p6HighCardArr[2]) ||

                 (p1HighCardArr[4] >= p2HighCardArr[4] && p1HighCardArr[4] >= p3HighCardArr[4] && p1HighCardArr[4] >= p4HighCardArr[4] && p1HighCardArr[4] >= p5HighCardArr[4] && p1HighCardArr[4] >= p6HighCardArr[4] &&
                  p1HighCardArr[3] >= p2HighCardArr[3] && p1HighCardArr[3] >= p3HighCardArr[3] && p1HighCardArr[3] >= p4HighCardArr[3] && p1HighCardArr[3] >= p5HighCardArr[3] && p1HighCardArr[3] >= p6HighCardArr[3] &&
                  p1HighCardArr[2] >= p2HighCardArr[2] && p1HighCardArr[2] >= p3HighCardArr[2] && p1HighCardArr[2] >= p4HighCardArr[2] && p1HighCardArr[2] >= p5HighCardArr[2] && p1HighCardArr[2] >= p6HighCardArr[2] &&
                  p1HighCardArr[1] > p2HighCardArr[1] && p1HighCardArr[1] > p3HighCardArr[1] && p1HighCardArr[1] > p4HighCardArr[1] && p1HighCardArr[1] > p5HighCardArr[1] && p1HighCardArr[1] > p6HighCardArr[1]) ||

                 (p1HighCardArr[4] >= p2HighCardArr[4] && p1HighCardArr[4] >= p3HighCardArr[4] && p1HighCardArr[4] >= p4HighCardArr[4] && p1HighCardArr[4] >= p5HighCardArr[4] && p1HighCardArr[4] >= p6HighCardArr[4] &&
                  p1HighCardArr[3] >= p2HighCardArr[3] && p1HighCardArr[3] >= p3HighCardArr[3] && p1HighCardArr[3] >= p4HighCardArr[3] && p1HighCardArr[3] >= p5HighCardArr[3] && p1HighCardArr[3] >= p6HighCardArr[3] &&
                  p1HighCardArr[2] >= p2HighCardArr[2] && p1HighCardArr[2] >= p3HighCardArr[2] && p1HighCardArr[2] >= p4HighCardArr[2] && p1HighCardArr[2] >= p5HighCardArr[2] && p1HighCardArr[2] >= p6HighCardArr[2] &&
                  p1HighCardArr[1] >= p2HighCardArr[1] && p1HighCardArr[1] >= p3HighCardArr[1] && p1HighCardArr[1] >= p4HighCardArr[1] && p1HighCardArr[1] >= p5HighCardArr[1] && p1HighCardArr[1] >= p6HighCardArr[1] &&
                  p1HighCardArr[0] > p2HighCardArr[0] && p1HighCardArr[0] > p3HighCardArr[0] && p1HighCardArr[0] > p4HighCardArr[0] && p1HighCardArr[0] > p5HighCardArr[0] && p1HighCardArr[0] > p6HighCardArr[0])){

            if(p1Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 1 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player1";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else if((p2HighCardArr[4] > p1HighCardArr[4] && p2HighCardArr[4] > p3HighCardArr[4] && p2HighCardArr[4] > p4HighCardArr[4] && p2HighCardArr[4] > p5HighCardArr[4] && p2HighCardArr[4] > p6HighCardArr[4])  ||

                 (p2HighCardArr[4] >= p1HighCardArr[4] && p2HighCardArr[4] >= p3HighCardArr[4] && p2HighCardArr[4] >= p4HighCardArr[4] && p2HighCardArr[4] >= p5HighCardArr[4] && p2HighCardArr[4] >= p6HighCardArr[4] &&
                  p2HighCardArr[3] > p1HighCardArr[3] && p2HighCardArr[3] > p3HighCardArr[3] && p2HighCardArr[3] > p4HighCardArr[3] && p2HighCardArr[3] > p5HighCardArr[3] && p2HighCardArr[3] > p6HighCardArr[3]) ||

                 (p2HighCardArr[4] >= p1HighCardArr[4] && p2HighCardArr[4] >= p3HighCardArr[4] && p2HighCardArr[4] >= p4HighCardArr[4] && p2HighCardArr[4] >= p5HighCardArr[4] && p2HighCardArr[4] >= p6HighCardArr[4] &&
                  p2HighCardArr[3] >= p1HighCardArr[3] && p2HighCardArr[3] >= p3HighCardArr[3] && p2HighCardArr[3] >= p4HighCardArr[3] && p2HighCardArr[3] >= p5HighCardArr[3] && p2HighCardArr[3] >= p6HighCardArr[3] &&
                  p2HighCardArr[2] > p1HighCardArr[2] && p2HighCardArr[2] > p3HighCardArr[2] && p2HighCardArr[2] > p4HighCardArr[2] && p2HighCardArr[2] > p5HighCardArr[2] && p2HighCardArr[2] > p6HighCardArr[2]) ||

                 (p2HighCardArr[4] >= p1HighCardArr[4] && p2HighCardArr[4] >= p3HighCardArr[4] && p2HighCardArr[4] >= p4HighCardArr[4] && p2HighCardArr[4] >= p5HighCardArr[4] && p2HighCardArr[4] >= p6HighCardArr[4] &&
                  p2HighCardArr[3] >= p1HighCardArr[3] && p2HighCardArr[3] >= p3HighCardArr[3] && p2HighCardArr[3] >= p4HighCardArr[3] && p2HighCardArr[3] >= p5HighCardArr[3] && p2HighCardArr[3] >= p6HighCardArr[3] &&
                  p2HighCardArr[2] >= p1HighCardArr[2] && p2HighCardArr[2] >= p3HighCardArr[2] && p2HighCardArr[2] >= p4HighCardArr[2] && p2HighCardArr[2] >= p5HighCardArr[2] && p2HighCardArr[2] >= p6HighCardArr[2] &&
                  p2HighCardArr[1] > p1HighCardArr[1] && p2HighCardArr[1] > p3HighCardArr[1] && p2HighCardArr[1] > p4HighCardArr[1] && p2HighCardArr[1] > p5HighCardArr[1] && p2HighCardArr[1] > p6HighCardArr[1]) ||

                 (p2HighCardArr[4] >= p1HighCardArr[4] && p2HighCardArr[4] >= p3HighCardArr[4] && p2HighCardArr[4] >= p4HighCardArr[4] && p2HighCardArr[4] >= p5HighCardArr[4] && p2HighCardArr[4] >= p6HighCardArr[4] &&
                  p2HighCardArr[3] >= p1HighCardArr[3] && p2HighCardArr[3] >= p3HighCardArr[3] && p2HighCardArr[3] >= p4HighCardArr[3] && p2HighCardArr[3] >= p5HighCardArr[3] && p2HighCardArr[3] >= p6HighCardArr[3] &&
                  p2HighCardArr[2] >= p1HighCardArr[2] && p2HighCardArr[2] >= p3HighCardArr[2] && p2HighCardArr[2] >= p4HighCardArr[2] && p2HighCardArr[2] >= p5HighCardArr[2] && p2HighCardArr[2] >= p6HighCardArr[2] &&
                  p2HighCardArr[1] >= p1HighCardArr[1] && p2HighCardArr[1] >= p3HighCardArr[1] && p2HighCardArr[1] >= p4HighCardArr[1] && p2HighCardArr[1] >= p5HighCardArr[1] && p2HighCardArr[1] >= p6HighCardArr[1] &&
                  p2HighCardArr[0] > p1HighCardArr[0] && p2HighCardArr[0] > p3HighCardArr[0] && p2HighCardArr[0] > p4HighCardArr[0] && p2HighCardArr[0] > p5HighCardArr[0] && p2HighCardArr[0] > p6HighCardArr[0])){

            if(p2Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 2 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player2";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else if((p3HighCardArr[4] > p1HighCardArr[4] && p3HighCardArr[4] > p2HighCardArr[4] && p3HighCardArr[4] > p4HighCardArr[4] && p3HighCardArr[4] > p5HighCardArr[4] && p3HighCardArr[4] > p6HighCardArr[4]) ||

                 (p3HighCardArr[4] >= p1HighCardArr[4] && p3HighCardArr[4] >= p2HighCardArr[4] && p3HighCardArr[4] >= p4HighCardArr[4] && p3HighCardArr[4] >= p5HighCardArr[4] && p3HighCardArr[4] >= p6HighCardArr[4] &&
                  p3HighCardArr[3] > p1HighCardArr[3] && p3HighCardArr[3] > p2HighCardArr[3] && p3HighCardArr[3] > p4HighCardArr[3] && p3HighCardArr[3] > p5HighCardArr[3] && p3HighCardArr[3] > p6HighCardArr[3]) ||

                 (p3HighCardArr[4] >= p1HighCardArr[4] && p3HighCardArr[4] >= p2HighCardArr[4] && p3HighCardArr[4] >= p4HighCardArr[4] && p3HighCardArr[4] >= p5HighCardArr[4] && p3HighCardArr[4] >= p6HighCardArr[4] &&
                  p3HighCardArr[3] >= p1HighCardArr[3] && p3HighCardArr[3] >= p2HighCardArr[3] && p3HighCardArr[3] >= p4HighCardArr[3] && p3HighCardArr[3] >= p5HighCardArr[3] && p3HighCardArr[3] >= p6HighCardArr[3] &&
                  p3HighCardArr[2] > p1HighCardArr[2] && p3HighCardArr[2] > p2HighCardArr[2] && p3HighCardArr[2] > p4HighCardArr[2] && p3HighCardArr[2] > p5HighCardArr[2] && p3HighCardArr[2] > p6HighCardArr[2]) ||

                 (p3HighCardArr[4] >= p1HighCardArr[4] && p3HighCardArr[4] >= p2HighCardArr[4] && p3HighCardArr[4] >= p4HighCardArr[4] && p3HighCardArr[4] >= p5HighCardArr[4] && p3HighCardArr[4] >= p6HighCardArr[4] &&
                  p3HighCardArr[3] >= p1HighCardArr[3] && p3HighCardArr[3] >= p2HighCardArr[3] && p3HighCardArr[3] >= p4HighCardArr[3] && p3HighCardArr[3] >= p5HighCardArr[3] && p3HighCardArr[3] >= p6HighCardArr[3] &&
                  p3HighCardArr[2] >= p1HighCardArr[2] && p3HighCardArr[2] >= p2HighCardArr[2] && p3HighCardArr[2] >= p4HighCardArr[2] && p3HighCardArr[2] >= p5HighCardArr[2] && p3HighCardArr[2] >= p6HighCardArr[2] &&
                  p3HighCardArr[1] > p1HighCardArr[1] && p3HighCardArr[1] > p2HighCardArr[1] && p3HighCardArr[1] > p4HighCardArr[1] && p3HighCardArr[1] > p5HighCardArr[1] && p3HighCardArr[1] > p6HighCardArr[1]) ||

                 (p3HighCardArr[4] >= p1HighCardArr[4] && p3HighCardArr[4] >= p2HighCardArr[4] && p3HighCardArr[4] >= p4HighCardArr[4] && p3HighCardArr[4] >= p5HighCardArr[4] && p3HighCardArr[4] >= p6HighCardArr[4] &&
                  p3HighCardArr[3] >= p1HighCardArr[3] && p3HighCardArr[3] >= p2HighCardArr[3] && p3HighCardArr[3] >= p4HighCardArr[3] && p3HighCardArr[3] >= p5HighCardArr[3] && p3HighCardArr[3] >= p6HighCardArr[3] &&
                  p3HighCardArr[2] >= p1HighCardArr[2] && p3HighCardArr[2] >= p2HighCardArr[2] && p3HighCardArr[2] >= p4HighCardArr[2] && p3HighCardArr[2] >= p5HighCardArr[2] && p3HighCardArr[2] >= p6HighCardArr[2] &&
                  p3HighCardArr[1] >= p1HighCardArr[1] && p3HighCardArr[1] >= p2HighCardArr[1] && p3HighCardArr[1] >= p4HighCardArr[1] && p3HighCardArr[1] >= p5HighCardArr[1] && p3HighCardArr[1] >= p6HighCardArr[1] &&
                  p3HighCardArr[0] > p1HighCardArr[0] && p3HighCardArr[0] > p2HighCardArr[0] && p3HighCardArr[0] > p4HighCardArr[0] && p3HighCardArr[0] > p5HighCardArr[0] && p3HighCardArr[0] > p6HighCardArr[0])){

            if(p3Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 3 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player3";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else if((p4HighCardArr[4] > p1HighCardArr[4] && p4HighCardArr[4] > p2HighCardArr[4] && p4HighCardArr[4] > p3HighCardArr[4] && p4HighCardArr[4] > p5HighCardArr[4] && p4HighCardArr[4] > p6HighCardArr[4]) ||

                 (p4HighCardArr[4] >= p1HighCardArr[4] && p4HighCardArr[4] >= p2HighCardArr[4] && p4HighCardArr[4] >= p3HighCardArr[4] && p4HighCardArr[4] >= p5HighCardArr[4] && p4HighCardArr[4] >= p6HighCardArr[4] &&
                  p4HighCardArr[3] > p1HighCardArr[3] && p4HighCardArr[3] > p2HighCardArr[3] && p4HighCardArr[3] > p3HighCardArr[3] && p4HighCardArr[3] > p5HighCardArr[3] && p4HighCardArr[3] > p6HighCardArr[3]) ||

                 (p4HighCardArr[4] >= p1HighCardArr[4] && p4HighCardArr[4] >= p2HighCardArr[4] && p4HighCardArr[4] >= p3HighCardArr[4] && p4HighCardArr[4] >= p5HighCardArr[4] && p4HighCardArr[4] >= p6HighCardArr[4] &&
                  p4HighCardArr[3] >= p1HighCardArr[3] && p4HighCardArr[3] >= p2HighCardArr[3] && p4HighCardArr[3] >= p3HighCardArr[3] && p4HighCardArr[3] >= p5HighCardArr[3] && p4HighCardArr[3] >= p6HighCardArr[3] &&
                  p4HighCardArr[2] > p1HighCardArr[2] && p4HighCardArr[2] > p2HighCardArr[2] && p4HighCardArr[2] > p3HighCardArr[2] && p4HighCardArr[2] > p5HighCardArr[2] && p4HighCardArr[2] > p6HighCardArr[2]) ||

                 (p4HighCardArr[4] >= p1HighCardArr[4] && p4HighCardArr[4] >= p2HighCardArr[4] && p4HighCardArr[4] >= p3HighCardArr[4] && p4HighCardArr[4] >= p5HighCardArr[4] && p4HighCardArr[4] >= p6HighCardArr[4] &&
                  p4HighCardArr[3] >= p1HighCardArr[3] && p4HighCardArr[3] >= p2HighCardArr[3] && p4HighCardArr[3] >= p3HighCardArr[3] && p4HighCardArr[3] >= p5HighCardArr[3] && p4HighCardArr[3] >= p6HighCardArr[3] &&
                  p4HighCardArr[2] >= p1HighCardArr[2] && p4HighCardArr[2] >= p2HighCardArr[2] && p4HighCardArr[2] >= p3HighCardArr[2] && p4HighCardArr[2] >= p5HighCardArr[2] && p4HighCardArr[2] >= p6HighCardArr[2] &&
                  p4HighCardArr[1] > p1HighCardArr[1] && p4HighCardArr[1] > p2HighCardArr[1] && p4HighCardArr[1] > p3HighCardArr[1] && p4HighCardArr[1] > p5HighCardArr[1] && p4HighCardArr[1] > p6HighCardArr[1]) ||

                 (p4HighCardArr[4] >= p1HighCardArr[4] && p4HighCardArr[4] >= p2HighCardArr[4] && p4HighCardArr[4] >= p3HighCardArr[4] && p4HighCardArr[4] >= p5HighCardArr[4] && p4HighCardArr[4] >= p6HighCardArr[4] &&
                  p4HighCardArr[3] >= p1HighCardArr[3] && p4HighCardArr[3] >= p2HighCardArr[3] && p4HighCardArr[3] >= p3HighCardArr[3] && p4HighCardArr[3] >= p5HighCardArr[3] && p4HighCardArr[3] >= p6HighCardArr[3] &&
                  p4HighCardArr[2] >= p1HighCardArr[2] && p4HighCardArr[2] >= p2HighCardArr[2] && p4HighCardArr[2] >= p3HighCardArr[2] && p4HighCardArr[2] >= p5HighCardArr[2] && p4HighCardArr[2] >= p6HighCardArr[2] &&
                  p4HighCardArr[1] >= p1HighCardArr[1] && p4HighCardArr[1] >= p2HighCardArr[1] && p4HighCardArr[1] >= p3HighCardArr[1] && p4HighCardArr[1] >= p5HighCardArr[1] && p4HighCardArr[1] >= p6HighCardArr[1] &&
                  p4HighCardArr[0] > p1HighCardArr[0] && p4HighCardArr[0] > p2HighCardArr[0] && p4HighCardArr[0] > p3HighCardArr[0] && p4HighCardArr[0] > p5HighCardArr[0] && p4HighCardArr[0] > p6HighCardArr[0])){

            if(p4Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 4 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player4";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else if((p5HighCardArr[4] > p1HighCardArr[4] && p5HighCardArr[4] > p2HighCardArr[4] && p5HighCardArr[4] > p3HighCardArr[4] && p5HighCardArr[4] > p4HighCardArr[4] && p5HighCardArr[4] > p6HighCardArr[4]) ||

                 (p5HighCardArr[4] >= p1HighCardArr[4] && p5HighCardArr[4] >= p2HighCardArr[4] && p5HighCardArr[4] >= p3HighCardArr[4] && p5HighCardArr[4] >= p4HighCardArr[4] && p5HighCardArr[4] >= p6HighCardArr[4] &&
                  p5HighCardArr[3] > p1HighCardArr[3] && p5HighCardArr[3] > p2HighCardArr[3] && p5HighCardArr[3] > p3HighCardArr[3] && p5HighCardArr[3] > p4HighCardArr[3] && p5HighCardArr[3] > p6HighCardArr[3]) ||

                 (p5HighCardArr[4] >= p1HighCardArr[4] && p5HighCardArr[4] >= p2HighCardArr[4] && p5HighCardArr[4] >= p3HighCardArr[4] && p5HighCardArr[4] >= p4HighCardArr[4] && p5HighCardArr[4] >= p6HighCardArr[4] &&
                  p5HighCardArr[3] >= p1HighCardArr[3] && p5HighCardArr[3] >= p2HighCardArr[3] && p5HighCardArr[3] >= p3HighCardArr[3] && p5HighCardArr[3] >= p4HighCardArr[3] && p5HighCardArr[3] >= p6HighCardArr[3] &&
                  p5HighCardArr[2] > p1HighCardArr[2] && p5HighCardArr[2] > p2HighCardArr[2] && p5HighCardArr[2] > p3HighCardArr[2] && p5HighCardArr[2] > p4HighCardArr[2] && p5HighCardArr[2] > p6HighCardArr[2]) ||

                 (p5HighCardArr[4] >= p1HighCardArr[4] && p5HighCardArr[4] >= p2HighCardArr[4] && p5HighCardArr[4] >= p3HighCardArr[4] && p5HighCardArr[4] >= p4HighCardArr[4] && p5HighCardArr[4] >= p6HighCardArr[4] &&
                  p5HighCardArr[3] >= p1HighCardArr[3] && p5HighCardArr[3] >= p2HighCardArr[3] && p5HighCardArr[3] >= p3HighCardArr[3] && p5HighCardArr[3] >= p4HighCardArr[3] && p5HighCardArr[3] >= p6HighCardArr[3] &&
                  p5HighCardArr[2] >= p1HighCardArr[2] && p5HighCardArr[2] >= p2HighCardArr[2] && p5HighCardArr[2] >= p3HighCardArr[2] && p5HighCardArr[2] >= p4HighCardArr[2] && p5HighCardArr[2] >= p6HighCardArr[2] &&
                  p5HighCardArr[1] > p1HighCardArr[1] && p5HighCardArr[1] > p2HighCardArr[1] && p5HighCardArr[1] > p3HighCardArr[1] && p5HighCardArr[1] > p4HighCardArr[1] && p5HighCardArr[1] > p6HighCardArr[1]) ||

                 (p5HighCardArr[4] >= p1HighCardArr[4] && p5HighCardArr[4] >= p2HighCardArr[4] && p5HighCardArr[4] >= p3HighCardArr[4] && p5HighCardArr[4] >= p4HighCardArr[4] && p5HighCardArr[4] >= p6HighCardArr[4] &&
                  p5HighCardArr[3] >= p1HighCardArr[3] && p5HighCardArr[3] >= p2HighCardArr[3] && p5HighCardArr[3] >= p3HighCardArr[3] && p5HighCardArr[3] >= p4HighCardArr[3] && p5HighCardArr[3] >= p6HighCardArr[3] &&
                  p5HighCardArr[2] >= p1HighCardArr[2] && p5HighCardArr[2] >= p2HighCardArr[2] && p5HighCardArr[2] >= p3HighCardArr[2] && p5HighCardArr[2] >= p4HighCardArr[2] && p5HighCardArr[2] >= p6HighCardArr[2] &&
                  p5HighCardArr[1] >= p1HighCardArr[1] && p5HighCardArr[1] >= p2HighCardArr[1] && p5HighCardArr[1] >= p3HighCardArr[1] && p5HighCardArr[1] >= p4HighCardArr[1] && p5HighCardArr[1] >= p6HighCardArr[1] &&
                  p5HighCardArr[0] > p1HighCardArr[0] && p5HighCardArr[0] > p2HighCardArr[0] && p5HighCardArr[0] > p3HighCardArr[0] && p5HighCardArr[0] > p4HighCardArr[0] && p5HighCardArr[0] > p6HighCardArr[0])){

            if(p5Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 5 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player5";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else if((p6HighCardArr[4] > p1HighCardArr[4] && p6HighCardArr[4] > p2HighCardArr[4] && p6HighCardArr[4] > p3HighCardArr[4] && p6HighCardArr[4] > p4HighCardArr[4] && p6HighCardArr[4] > p5HighCardArr[4]) ||

                 (p6HighCardArr[4] >= p1HighCardArr[4] && p6HighCardArr[4] >= p2HighCardArr[4] && p6HighCardArr[4] >= p3HighCardArr[4] && p6HighCardArr[4] >= p4HighCardArr[4] && p6HighCardArr[4] >= p5HighCardArr[4] &&
                  p6HighCardArr[3] > p1HighCardArr[3] && p6HighCardArr[3] > p2HighCardArr[3] && p6HighCardArr[3] > p3HighCardArr[3] && p6HighCardArr[3] > p4HighCardArr[3] && p6HighCardArr[3] > p5HighCardArr[3]) ||

                 (p6HighCardArr[4] >= p1HighCardArr[4] && p6HighCardArr[4] >= p2HighCardArr[4] && p6HighCardArr[4] >= p3HighCardArr[4] && p6HighCardArr[4] >= p4HighCardArr[4] && p6HighCardArr[4] >= p5HighCardArr[4] &&
                  p6HighCardArr[3] >= p1HighCardArr[3] && p6HighCardArr[3] >= p2HighCardArr[3] && p6HighCardArr[3] >= p3HighCardArr[3] && p6HighCardArr[3] >= p4HighCardArr[3] && p6HighCardArr[3] >= p5HighCardArr[3] &&
                  p6HighCardArr[2] > p1HighCardArr[2] && p6HighCardArr[2] > p2HighCardArr[2] && p6HighCardArr[2] > p3HighCardArr[2] && p6HighCardArr[2] > p4HighCardArr[2] && p6HighCardArr[2] > p5HighCardArr[2]) ||

                 (p6HighCardArr[4] >= p1HighCardArr[4] && p6HighCardArr[4] >= p2HighCardArr[4] && p6HighCardArr[4] >= p3HighCardArr[4] && p6HighCardArr[4] >= p4HighCardArr[4] && p6HighCardArr[4] >= p5HighCardArr[4] &&
                  p6HighCardArr[3] >= p1HighCardArr[3] && p6HighCardArr[3] >= p2HighCardArr[3] && p6HighCardArr[3] >= p3HighCardArr[3] && p6HighCardArr[3] >= p4HighCardArr[3] && p6HighCardArr[3] >= p5HighCardArr[3] &&
                  p6HighCardArr[2] >= p1HighCardArr[2] && p6HighCardArr[2] >= p2HighCardArr[2] && p6HighCardArr[2] >= p3HighCardArr[2] && p6HighCardArr[2] >= p4HighCardArr[2] && p6HighCardArr[2] >= p5HighCardArr[2] &&
                  p6HighCardArr[1] > p1HighCardArr[1] && p6HighCardArr[1] > p2HighCardArr[1] && p6HighCardArr[1] > p3HighCardArr[1] && p6HighCardArr[1] > p4HighCardArr[1] && p6HighCardArr[1] > p5HighCardArr[1]) ||

                 (p6HighCardArr[4] >= p1HighCardArr[4] && p6HighCardArr[4] >= p2HighCardArr[4] && p6HighCardArr[4] >= p3HighCardArr[4] && p6HighCardArr[4] >= p4HighCardArr[4] && p6HighCardArr[4] >= p5HighCardArr[4] &&
                  p6HighCardArr[3] >= p1HighCardArr[3] && p6HighCardArr[3] >= p2HighCardArr[3] && p6HighCardArr[3] >= p3HighCardArr[3] && p6HighCardArr[3] >= p4HighCardArr[3] && p6HighCardArr[3] >= p5HighCardArr[3] &&
                  p6HighCardArr[2] >= p1HighCardArr[2] && p6HighCardArr[2] >= p2HighCardArr[2] && p6HighCardArr[2] >= p3HighCardArr[2] && p6HighCardArr[2] >= p4HighCardArr[2] && p6HighCardArr[2] >= p5HighCardArr[2] &&
                  p6HighCardArr[1] >= p1HighCardArr[1] && p6HighCardArr[1] >= p2HighCardArr[1] && p6HighCardArr[1] >= p3HighCardArr[1] && p6HighCardArr[1] >= p4HighCardArr[1] && p6HighCardArr[1] >= p5HighCardArr[1] &&
                  p6HighCardArr[0] > p1HighCardArr[0] && p6HighCardArr[0] > p2HighCardArr[0] && p6HighCardArr[0] > p3HighCardArr[0] && p6HighCardArr[0] > p4HighCardArr[0] && p6HighCardArr[0] > p5HighCardArr[0])){

            if(p6Rank == winningRank[0]){
                ui->turnReadOut->setText("Hand Over, Player 6 Wins");
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){
                        rpc::paidOut = true;
                        QString whoWon = "Player6";
                        payoutDelay(30);
                        autopayWinner(whoWon);

                    }

                }
            }

        }else {
            ui->turnReadOut->setText("Push, Split Pot");
            compareLoop();
            if(rpc::oneId == rpc::IdHash){

                if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){     /// Contract not set up for split pot situation, owner will split
                    rpc::paidOut = true;
                    payoutDelay(30);
                    splitWinner();
                }

            }

        }

    }

  }
  MainWindow::displayedRes = true;
  ui->logTextBrowser->setFontPointSize(23);

}


QString MainWindow::deckSelect(int d)   /// Gets deck path prefix for card images
{
    QString path;
    QString pre = QDir().absolutePath();
    QString post;
    switch(d){
    case 0: post = "/cards/standard/light/"; break;
    case 1: post = "/cards/standard/dark/"; break;
    default: post = "/cards/"+ui->deckComboBox->currentText()+"/"+ui->deckComboBox->currentText()+"/"; break;
    }
    path = pre+post;

    return path;
}


QString MainWindow::backSelect(int d)   /// Gets back path prefix for card images
{
    QString path;
    QString pre = QDir().absolutePath();
    QString post;
    switch(d){
    case 0: post = "/cards/backs/"; break;
    case 1: post = "/cards/backs/"; break;
    default: post = "/cards/backs/"+ui->backComboBox->currentText()+"/"+ui->backComboBox->currentText()+"/"; break;
    }
    path = pre+post;

    return path;
}


void MainWindow::blankDisplay()  /// Shows null cards when not playing
{
    if(Menu::sharedDeck == false){
        if(ui->backComboBox->currentIndex() > 1){
            ui->localPlayerCard1->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->localPlayerCard2->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->localPlayerCard3->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->localPlayerCard4->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->localPlayerCard5->setPixmap(QPixmap::fromImage(displayCustom(0)));
        }else {
            ui->localPlayerCard1->setPixmap(QPixmap(displayStandard(0)));
            ui->localPlayerCard2->setPixmap(QPixmap(displayStandard(0)));
            ui->localPlayerCard3->setPixmap(QPixmap(displayStandard(0)));
            ui->localPlayerCard4->setPixmap(QPixmap(displayStandard(0)));
            ui->localPlayerCard5->setPixmap(QPixmap(displayStandard(0)));
        }
    }else {
        ui->localPlayerCard1->setPixmap(QPixmap(displayStandard(0)));
        ui->localPlayerCard2->setPixmap(QPixmap(displayStandard(0)));
        ui->localPlayerCard3->setPixmap(QPixmap(displayStandard(0)));
        ui->localPlayerCard4->setPixmap(QPixmap(displayStandard(0)));
        ui->localPlayerCard5->setPixmap(QPixmap(displayStandard(0)));
    }
}


QString MainWindow::handToText(int rank)        /// Hand value for text readout
{
    QString handRankText;
    switch (rank){
    case 1: handRankText = "Royal Flush"; break;
    case 2: handRankText = "Straight Flush"; break;
    case 3: handRankText = "Four of a Kind"; break;
    case 4: handRankText = "Full House"; break;
    case 5: handRankText = "Flush"; break;
    case 6: handRankText = "Straight"; break;
    case 7: handRankText = "Three of a Kind"; break;
    case 8: handRankText = "Two Pair"; break;
    case 9: handRankText = "Pair"; break;
    case 10: handRankText = "High Card"; break;
    }
    return handRankText;
}


QString MainWindow::findCards(int card) /// To show all hand results at end
{
    QString cardEquiv;
    switch (card){
    case 1: cardEquiv = "🂡"; break;
    case 2: cardEquiv = "🂢"; break;
    case 3: cardEquiv = "🂣"; break;
    case 4: cardEquiv = "🂤"; break;
    case 5: cardEquiv = "🂥"; break;
    case 6: cardEquiv = "🂦"; break;
    case 7: cardEquiv = "🂧"; break;
    case 8: cardEquiv = "🂨"; break;
    case 9: cardEquiv = "🂩"; break;
    case 10: cardEquiv = "🂪"; break;
    case 11: cardEquiv = "🂫"; break;
    case 12: cardEquiv = "🂭"; break;
    case 13: cardEquiv = "🂮"; break;
    case 14: cardEquiv = "🂱"; break;
    case 15: cardEquiv = "🂲"; break;
    case 16: cardEquiv = "🂳"; break;
    case 17: cardEquiv = "🂴"; break;
    case 18: cardEquiv = "🂵"; break;
    case 19: cardEquiv = "🂶"; break;
    case 20: cardEquiv = "🂷"; break;
    case 21: cardEquiv = "🂸"; break;
    case 22: cardEquiv = "🂹"; break;
    case 23: cardEquiv = "🂺"; break;
    case 24: cardEquiv = "🂻"; break;
    case 25: cardEquiv = "🂽"; break;
    case 26: cardEquiv = "🂾"; break;
    case 27: cardEquiv = "🃑"; break;
    case 28: cardEquiv = "🃒"; break;
    case 29: cardEquiv = "🃓"; break;
    case 30: cardEquiv = "🃔"; break;
    case 31: cardEquiv = "🃕"; break;
    case 32: cardEquiv = "🃖"; break;
    case 33: cardEquiv = "🃗"; break;
    case 34: cardEquiv = "🃘"; break;
    case 35: cardEquiv = "🃙"; break;
    case 36: cardEquiv = "🃚"; break;
    case 37: cardEquiv = "🃛"; break;
    case 38: cardEquiv = "🃝"; break;
    case 39: cardEquiv = "🃞"; break;
    case 40: cardEquiv = "🃁"; break;
    case 41: cardEquiv = "🃂"; break;
    case 42: cardEquiv = "🃃"; break;
    case 43: cardEquiv = "🃄"; break;
    case 44: cardEquiv = "🃅"; break;
    case 45: cardEquiv = "🃆"; break;
    case 46: cardEquiv = "🃇"; break;
    case 47: cardEquiv = "🃈"; break;
    case 48: cardEquiv = "🃉"; break;
    case 49: cardEquiv = "🃊"; break;
    case 50: cardEquiv = "🃋"; break;
    case 51: cardEquiv = "🃍"; break;
    case 52: cardEquiv = "🃎"; break;
    }
    return cardEquiv;
}


void MainWindow::displayCardOne(int card) /// Displays local card one
{

    if(Menu::sharedDeck == false){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->localPlayerCard1->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->localPlayerCard1->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->localPlayerCard1->setPixmap(QPixmap(displayStandard(card)));
    }
}


void MainWindow::displayCardTwo(int card)  /// Displays local card two
{
    if(Menu::sharedDeck == false){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->localPlayerCard2->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->localPlayerCard2->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->localPlayerCard2->setPixmap(QPixmap(displayStandard(card)));
    }
}


void MainWindow::displayCardThree(int card)    /// Displays local card three
{
    if(Menu::sharedDeck == false){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->localPlayerCard3->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->localPlayerCard3->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->localPlayerCard3->setPixmap(QPixmap(displayStandard(card)));
    }
}


void MainWindow::displayCardFour(int card)   ///  Displays local card four
{
    if(Menu::sharedDeck == false){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->localPlayerCard4->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->localPlayerCard4->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->localPlayerCard4->setPixmap(QPixmap(displayStandard(card)));
    }
}


void MainWindow::displayCardFive(int card)   ///  Displays local card five
{
    if(Menu::sharedDeck == false){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->localPlayerCard5->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->localPlayerCard5->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->localPlayerCard5->setPixmap(QPixmap(displayStandard(card)));
    }
}


QImage MainWindow::displayCustom(int card)   /// Gets suffix for custom card image display
{
    QString suffix;
    QImage path;
    if(card > 0){
        switch (card){
           case 1: suffix = "card1.png"; break;
           case 2: suffix = "card2.png"; break;
           case 3: suffix = "card3.png"; break;
           case 4: suffix = "card4.png"; break;
           case 5: suffix = "card5.png"; break;
           case 6: suffix = "card6.png"; break;
           case 7: suffix = "card7.png"; break;
           case 8: suffix = "card8.png"; break;
           case 9: suffix = "card9.png"; break;
           case 10: suffix = "card10.png" ; break;
           case 11: suffix = "card11.png" ; break;
           case 12: suffix = "card12.png" ; break;
           case 13: suffix = "card13.png" ; break;
           case 14: suffix = "card14.png" ; break;
           case 15: suffix = "card15.png" ; break;
           case 16: suffix = "card16.png" ; break;
           case 17: suffix = "card17.png" ; break;
           case 18: suffix = "card18.png" ; break;
           case 19: suffix = "card19.png" ; break;
           case 20: suffix = "card20.png" ; break;
           case 21: suffix = "card21.png" ; break;
           case 22: suffix = "card22.png" ; break;
           case 23: suffix = "card23.png" ; break;
           case 24: suffix = "card24.png" ; break;
           case 25: suffix = "card25.png" ; break;
           case 26: suffix = "card26.png" ; break;
           case 27: suffix = "card27.png" ; break;
           case 28: suffix = "card28.png" ; break;
           case 29: suffix = "card29.png" ; break;
           case 30: suffix = "card30.png" ; break;
           case 31: suffix = "card31.png" ; break;
           case 32: suffix = "card32.png" ; break;
           case 33: suffix = "card33.png" ; break;
           case 34: suffix = "card34.png" ; break;
           case 35: suffix = "card35.png" ; break;
           case 36: suffix = "card36.png" ; break;
           case 37: suffix = "card37.png" ; break;
           case 38: suffix = "card38.png" ; break;
           case 39: suffix = "card39.png" ; break;
           case 40: suffix = "card40.png" ; break;
           case 41: suffix = "card41.png" ; break;
           case 42: suffix = "card42.png" ; break;
           case 43: suffix = "card43.png" ; break;
           case 44: suffix = "card44.png" ; break;
           case 45: suffix = "card45.png" ; break;
           case 46: suffix = "card46.png" ; break;
           case 47: suffix = "card47.png" ; break;
           case 48: suffix = "card48.png" ; break;
           case 49: suffix = "card49.png" ; break;
           case 50: suffix = "card50.png" ; break;
           case 51: suffix = "card51.png" ; break;
           case 52: suffix = "card52.png" ; break;
           }

        QImageReader reader(deckSelect(ui->deckComboBox->currentIndex())+suffix);
        path = reader.read();
    }else {
        QImageReader reader(backSelect(ui->backComboBox->currentIndex())+"back.png");
        path = reader.read();
    }

    return path;
}


QString MainWindow::displayStandard(int card)   /// Gets suffix for standard card image display
{
    QString pre;
    QString suffix;
    QString path;
    if(card > 0){
        if(ui->deckComboBox->currentIndex() == 1){
            pre = ":/images/cards/standard/dark/";

        }else {
            pre = ":/images/cards/standard/light/";
        }

        switch (card){
           case 1: suffix = "card1.png"; break;
           case 2: suffix = "card2.png"; break;
           case 3: suffix = "card3.png"; break;
           case 4: suffix = "card4.png"; break;
           case 5: suffix = "card5.png"; break;
           case 6: suffix = "card6.png"; break;
           case 7: suffix = "card7.png"; break;
           case 8: suffix = "card8.png"; break;
           case 9: suffix = "card9.png"; break;
           case 10: suffix = "card10.png" ; break;
           case 11: suffix = "card11.png" ; break;
           case 12: suffix = "card12.png" ; break;
           case 13: suffix = "card13.png" ; break;
           case 14: suffix = "card14.png" ; break;
           case 15: suffix = "card15.png" ; break;
           case 16: suffix = "card16.png" ; break;
           case 17: suffix = "card17.png" ; break;
           case 18: suffix = "card18.png" ; break;
           case 19: suffix = "card19.png" ; break;
           case 20: suffix = "card20.png" ; break;
           case 21: suffix = "card21.png" ; break;
           case 22: suffix = "card22.png" ; break;
           case 23: suffix = "card23.png" ; break;
           case 24: suffix = "card24.png" ; break;
           case 25: suffix = "card25.png" ; break;
           case 26: suffix = "card26.png" ; break;
           case 27: suffix = "card27.png" ; break;
           case 28: suffix = "card28.png" ; break;
           case 29: suffix = "card29.png" ; break;
           case 30: suffix = "card30.png" ; break;
           case 31: suffix = "card31.png" ; break;
           case 32: suffix = "card32.png" ; break;
           case 33: suffix = "card33.png" ; break;
           case 34: suffix = "card34.png" ; break;
           case 35: suffix = "card35.png" ; break;
           case 36: suffix = "card36.png" ; break;
           case 37: suffix = "card37.png" ; break;
           case 38: suffix = "card38.png" ; break;
           case 39: suffix = "card39.png" ; break;
           case 40: suffix = "card40.png" ; break;
           case 41: suffix = "card41.png" ; break;
           case 42: suffix = "card42.png" ; break;
           case 43: suffix = "card43.png" ; break;
           case 44: suffix = "card44.png" ; break;
           case 45: suffix = "card45.png" ; break;
           case 46: suffix = "card46.png" ; break;
           case 47: suffix = "card47.png" ; break;
           case 48: suffix = "card48.png" ; break;
           case 49: suffix = "card49.png" ; break;
           case 50: suffix = "card50.png" ; break;
           case 51: suffix = "card51.png" ; break;
           case 52: suffix = "card52.png" ; break;
           }

        path = pre+suffix;

    }else {
        if(ui->backComboBox->currentIndex() == 1){
            path = ":/images/cards/backs/back2.png";

        }else {
            path = ":/images/cards/backs/back1.png";
        }

    }

    return path;
}
