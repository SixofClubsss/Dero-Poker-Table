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

QString MainWindow::faceUrl;
QString MainWindow::backUrl;
bool MainWindow::notified;
bool MainWindow::emptyBool;
bool MainWindow::shared0;
bool MainWindow::shared1;
bool MainWindow::shared2;
bool MainWindow::shared3;
bool MainWindow::shared4;
bool MainWindow::shared5;
bool MainWindow::shared6;
bool MainWindow::shared7;
bool MainWindow::clicked;
bool MainWindow::startUpSkip;
bool MainWindow::displayedRes;
int MainWindow::skipCount;

bool Hand::hasBet;
bool Hand::called;
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
int rpc::count;
int rpc::draw;
int rpc::end;
int rpc::bet;
int rpc::IV;
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

int rpc::flopBool;
int rpc::turnBool;
int rpc::riverBool;
int rpc::revealBool;

double rpc::blockHeight;
double rpc::clickedHeight;
double rpc::ante;
double rpc::bigBlind;
double rpc::smallBlind;
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
QString rpc::salt;

QString rpc::IdHash;

QString rpc::contractSeed;
QString rpc::clientKey;

QString rpc::hashOne;
QString rpc::hashTwo;

QString rpc::hashOneone;
QString rpc::hashOnetwo;;

QString rpc::hashTwoone;
QString rpc::hashTwotwo;

QString rpc::hashThreeone;
QString rpc::hashThreetwo;

QString rpc::hashFourone;
QString rpc::hashFourtwo;

QString rpc::hashFiveone;
QString rpc::hashFivetwo;

QString rpc::hashSixone;
QString rpc::hashSixtwo;

QString rpc::sharedBack;
QString rpc::sharedFace;

int rpc::flopCard1;
int rpc::flopCard2;
int rpc::flopCard3;
int rpc::riverCard;
int rpc::turnCard;

QString rpc::key1;
QString rpc::key2;
QString rpc::key3;
QString rpc::key4;
QString rpc::key5;
QString rpc::key6;


void MainWindow::payoutDelay(int seconds)            /// Delay for payout button to allow time to see end results
{
    QTime dieTime = QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::controller()       /// Ui control
{
    if(rpc::flopBool == 1 && rpc::wager == 0){
        Hand::called = true;
    }else {
        Hand::called = false;
    }

    if(Hand::called == true){
        Hand::hasBet = false;
    }

    displayLocalHand(rpc::hashOne, rpc::hashTwo);
    displayFlop(rpc::flopCard1, rpc::flopCard2, rpc::flopCard3);
    displayTurnCard(rpc::turnCard);
    displayRiverCard(rpc::riverCard);
    checkBalance(rpc::balance);

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
    localPlayerControl(rpc::bet, rpc::wager, rpc::ante, rpc::raised);
    storedEnd(rpc::end, rpc::oneId);
    localEndSignal(rpc::oneId);
    disableButtons();
}


void MainWindow::checkBalance(double balance)   /// Gets players Dero balance
{
    ui->balanceDoubleSpinBox->setValue(balance/100000);
    MainWindow::startUpSkip = false;
}


void MainWindow::setOpenClosed(int seats, double ante, double dealer)       /// Sets display for seats open or closed, set dealer display, sets minium bet == ante
{
    ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; background-color: rgba(85, 88, 93, 90); color: rgb(255, 255, 255);};" );
    ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 2px solid gray; border-radius: 5px; background-color: rgba(0, 0, 0, 120); };" );
    ui->betSpinBox->setMinimum(ante/100000);
    ui->anteIsDSB->setValue(ante/100000);
    QString bb = QString::number(rpc::smallBlind*2/100000);
    ui->blindIsDSB->setPrefix("Blinds: "+bb+" / ");
    ui->blindIsDSB->setValue(rpc::smallBlind/100000);
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
    }else if (twoId == rpc::IdHash){
       ui->playerId->setValue(2);
    }else if (threeId == rpc::IdHash){
       ui->playerId->setValue(3);
    }else if (fourId == rpc::IdHash){
       ui->playerId->setValue(4);
    }else if (fiveId == rpc::IdHash){
       ui->playerId->setValue(5);
    }else if (sixId == rpc::IdHash){
       ui->playerId->setValue(6);
    }else {
        ui->playerId->setValue(0);
    }
}


void MainWindow::potEmpty(double pot)       ///  When post is empty or has pot & shared controls
{
    if(pot == 0 && MainWindow::emptyBool == false){
        Hand::hasBet = false;
        Hand::endSignal = false;
        blankDisplay();
        ui->payoutPushButton->setEnabled(false);
        ui->winnerComboBox->setEnabled(false);
        rpc::paidOut = false;
        Hand::keyIsPub = false;
        MainWindow::displayedRes = false;
        MainWindow::shared0 = false;
        MainWindow::shared1 = false;
        MainWindow::shared2 = false;
        MainWindow::shared3 = false;
        MainWindow::shared4 = false;
        MainWindow::shared5 = false;
        MainWindow::shared6 = false;
        MainWindow::shared7 = false;
        MainWindow::emptyBool = true;

        if(Menu::os == "macos" || Menu::os == "osx" || Menu::os == "darwin" ){
            ui->logTextBrowser->setFontPointSize(30);
        }else {
            ui->logTextBrowser->setFontPointSize(24);
        }

    }else if(pot > 0){
        MainWindow::emptyBool = false;
    }

    if(Menu::sharedDeck == true && ui->playerId->value() > 1){
        ui->deckComboBox->setEnabled(false);
        ui->backComboBox->setEnabled(false);
    }else {
        ui->deckComboBox->setEnabled(true);
        ui->backComboBox->setEnabled(true);
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


void MainWindow::localPlayerControl(int bet, double wager, double ante, double raised)        /// Is players turn
{
    if(ui->dsbTurn->value() == ui->playerId->value()){   /// Local players turn button control
        if(rpc::end != 1 || rpc::revealBool != 1){
            ui->dealHandPushButton->setEnabled(true);
            ui->leaveButton->setEnabled(true);
        }

        if(rpc::revealBool == 1){
            ui->dealHandPushButton->setEnabled(false);
            ui->leaveButton->setEnabled(false);
        }

        if(bet >= 1 || rpc::turnBool == 1 || rpc::riverBool == 1){                          /// Sets buttons when in bet
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
            ui->leaveButton->setEnabled(false);
            QString w = QString::number(wager/100000);
            ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; color: rgb(255, 255, 255); background-color: rgb(56, 47, 165); };" );
            ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); background-color: rgba(0, 0, 0, 150); };" );
            ui->turnReadOut->setText("Bet is "+w);
            ui->turnReadOut->insertPlainText("Your Turn    ");
        }else {
            if(Hand::keyIsPub == false){
                ui->turnReadOut->setText("Your Turn");
            }
            ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; color: rgb(255, 255, 255); background-color: rgb(56, 47, 165); };" );
            ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); background-color: rgba(0, 0, 0, 150); };" );

        }

        if(wager == 0){                        /// Sets min bet amount when there is no wager
            if(ante != 0){
             ui->betSpinBox->setMinimum(ante/100000);
             ui->betSpinBox->setMaximum(100000000);
            }else {
                ui->betSpinBox->setMinimum(rpc::smallBlind/100000);
                ui->betSpinBox->setMaximum(100000000);
            }
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
                emit revealSignal();
            }
        }else {
            emit turnSignal();
        }

    }else {
        MainWindow::notified = false;
        ui->dealHandPushButton->setEnabled(false);            /// Not your turn controls
        ui->checkButton->setEnabled(false);
        ui->betButton->setEnabled(false);
        ui->leaveButton->setEnabled(false);
        QString p = QString::number(ui->dsbTurn->value());
        ui->turnReadOut->setText("Player "+p+"'s Turn");
    }
}


void MainWindow::storedEnd(int end, QString oneId)     /// End game show all hands,  start up skip
{
    if(end == 1){
        ui->turnReadOut->setText("Hand over, payout");
        ui->betButton->setEnabled(false);
        ui->checkButton->setEnabled(false);;
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
        ui->payoutPushButton->setEnabled(false);
        ui->winnerComboBox->setEnabled(false);
        blankDisplay();
    }

    if(rpc::revealBool == 1){
        ui->betButton->setEnabled(false);
        ui->checkButton->setEnabled(false);
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
    int end = seats - 1;

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


void MainWindow::displayLocalHand(QString hashOne, QString hashTwo) /// Displays players hole cards
{
    if(card(hashOne) > 0){
        if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
            if(ui->deckComboBox->currentIndex() > 1){
                ui->holeCard1Label->setGeometry(70, 20, 166, 227);
                ui->holeCard2Label->setGeometry(0, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap::fromImage(displayCustom(card(hashOne))));
                ui->holeCard2Label->setPixmap(QPixmap::fromImage(displayCustom(card(hashTwo))));
            }else {
                ui->holeCard1Label->setGeometry(80, 20, 166, 227);
                ui->holeCard2Label->setGeometry(-10, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap(displayStandard(card(hashOne))));
                ui->holeCard2Label->setPixmap(QPixmap(displayStandard(card(hashTwo))));
            }
        }else {
            ui->holeCard1Label->setGeometry(70, 20, 166, 227);
            ui->holeCard2Label->setGeometry(0, 10, 166, 227);
            displayShared(card(hashOne), 1);
            displayShared(card(hashTwo), 2);
        }
    }else {
        if(Menu::sharedDeck == false || ui->playerId->value() == 0){
            if(ui->backComboBox->currentIndex() > 1){
                ui->holeCard1Label->setGeometry(70, 20, 166, 227);
                ui->holeCard2Label->setGeometry(0, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->holeCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->holeCard1Label->setGeometry(80, 20, 166, 227);
                ui->holeCard2Label->setGeometry(-10, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap(displayStandard(0)));
                ui->holeCard2Label->setPixmap(QPixmap(displayStandard(0)));
            }
        }else if(ui->playerId->value() > 1){
            ui->holeCard1Label->setGeometry(70, 20, 166, 227);
            ui->holeCard2Label->setGeometry(0, 10, 166, 227);
            displayShared(0, 0);
        }else {
            if(ui->backComboBox->currentIndex() > 1){
                ui->holeCard1Label->setGeometry(70, 20, 166, 227);
                ui->holeCard2Label->setGeometry(0, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->holeCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->holeCard1Label->setGeometry(80, 20, 166, 227);
                ui->holeCard2Label->setGeometry(-10, 10, 166, 227);
                ui->holeCard1Label->setPixmap(QPixmap(displayStandard(0)));
                ui->holeCard2Label->setPixmap(QPixmap(displayStandard(0)));
            }
        }
    }
}


int MainWindow::card(QString hash)  /// Gets local cards and decrypt with local key
{
    for (int i = 1; i < 53; i++) {
         QString finder = QString::number(i);
         QString pcSeed = rpc::clientKey;
         QString scSeed = rpc::contractSeed;
         QString add = rpc::clientKey+finder+scSeed;
         QString card = QString(QCryptographicHash::hash((add.toUtf8()),QCryptographicHash::Sha256).toHex());

         if(card == hash){
             return i;
         }

    }
    return 0;

}


int MainWindow::keyCard(QString hash, int who)  /// Gets other player cards and decrypt with their keys after reveal
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

         QString finder = QString::number(i);
         QString scSeed = rpc::contractSeed;
         QString add = keyCheck+finder+scSeed;
         QString card = QString(QCryptographicHash::hash((add.toUtf8()),QCryptographicHash::Sha256).toHex());

         if(card == hash){
             return i;
         }

    }
    return 0;

}


void MainWindow::pEndTextLine(QString t, QString h1, QString h2, int p, int r)
{
    int ps1;
    int ps2;

    if(Menu::os == "macos" || Menu::os == "osx" || Menu::os == "darwin" || Menu::os == "arch"){
        ps1 = 45;
        ps2 = 72;
    }else if(Menu::os == "windows"){
        ps1 = 30;
        ps2 = 51;
    }else {
        ps1 = 30;
        ps2 = 33;
    }

    ui->logTextBrowser->setFontPointSize(ps1);
    ui->logTextBrowser->append(t);

    ui->logTextBrowser->moveCursor(QTextCursor::End);
    ui->logTextBrowser->setFontPointSize(ps2);
    ui->logTextBrowser->insertPlainText(findCards(keyCard(h1, p))+" ");
    ui->logTextBrowser->moveCursor(QTextCursor::End);
    ui->logTextBrowser->insertPlainText(findCards(keyCard(h2, p))+" ");
    ui->logTextBrowser->moveCursor(QTextCursor::End);

    ui->logTextBrowser->setFontPointSize(ps1);
    ui->logTextBrowser->insertPlainText(handToText(r)+" ");
    ui->logTextBrowser->moveCursor(QTextCursor::End);
    ui->logTextBrowser->insertPlainText(thisHandIs(p));
}


void MainWindow::endResults(int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold)      /// Show all player cards and end results
{

    if(Hand::endSignal == false && ui->playerId->value() > 0 && rpc::inGame == true){
        getCommunity();
        ///Player 1 decode hand result, sort and split into value and suits
        if(seats >= 2 && p1Fold != 1){
            p1Rank = getPlayer1();
        }else{
            p1Rank = 100;
        }

        ///Player 2 decode
        if(seats >= 2 && p2Fold != 1){
            p2Rank = getPlayer2();
        }else{
            p2Rank = 100;
        }

        ///Player 3 decode
        if(seats >= 3 && p3Fold != 1){
            p3Rank = getPlayer3();
        }else{
            p3Rank = 100;
        }

        ///Player 4 decode
        if(seats >= 4 && p4Fold != 1){
            p4Rank = getPlayer4();
        }else{
            p4Rank = 100;
        }

        ///Player 5 Decode
        if(seats >= 5 && p5Fold != 1){
            p5Rank = getPlayer5();
        }else{
            p5Rank = 100;
        }

        ///Player 6 decode
        if(seats == 6 && p6Fold != 1){
            p6Rank = getPlayer6();
        }else{
            p6Rank = 100;
        }

        if(MainWindow::displayedRes == false){
            switch (seats){
            /// Display players who are in game and not folded
            case 2:
                ui->logTextBrowser->setText("");
                pEndTextLine("Player 1 Has: ", rpc::hashOneone, rpc::hashOnetwo, 1, p1Rank);
                pEndTextLine("Player 2 Has: ", rpc::hashTwoone, rpc::hashTwotwo, 2, p2Rank);
                break;

            case 3:
                ui->logTextBrowser->setText("");

                if(p1Fold != 1){
                    pEndTextLine("Player 1 Has: ", rpc::hashOneone, rpc::hashOnetwo, 1, p1Rank);
                }

                if(p2Fold != 1){
                    pEndTextLine("Player 2 Has: ", rpc::hashTwoone, rpc::hashTwotwo, 2, p2Rank);
                }

                if(p3Fold != 1){
                    pEndTextLine("Player 3 Has: ", rpc::hashThreeone, rpc::hashThreetwo, 3, p3Rank);
                }
                break;

            case 4:
                ui->logTextBrowser->setText("");

                if(p1Fold != 1){
                    pEndTextLine("Player 1 Has: ", rpc::hashOneone, rpc::hashOnetwo, 1, p1Rank);
                }

                if(p2Fold != 1){
                    pEndTextLine("Player 2 Has: ", rpc::hashTwoone, rpc::hashTwotwo, 2, p2Rank);
                }

                if(p3Fold != 1){
                    pEndTextLine("Player 3 Has: ", rpc::hashThreeone, rpc::hashThreetwo, 3, p3Rank);
                }

                if(p4Fold != 1){
                    pEndTextLine("Player 4 Has: ", rpc::hashFourone, rpc::hashFourtwo, 4, p4Rank);
                }
                break;

            case 5:
                ui->logTextBrowser->setText("");

                if(p1Fold != 1){
                    pEndTextLine("Player 1 Has: ", rpc::hashOneone, rpc::hashOnetwo, 1, p1Rank);
                }

                if(p2Fold != 1){
                    pEndTextLine("Player 2 Has: ", rpc::hashTwoone, rpc::hashTwotwo, 2, p2Rank);
                }

                if(p3Fold != 1){
                    pEndTextLine("Player 3 Has: ", rpc::hashThreeone, rpc::hashThreetwo, 3, p3Rank);
                }

                if(p4Fold != 1){
                    pEndTextLine("Player 4 Has: ", rpc::hashFourone, rpc::hashFourtwo, 4, p4Rank);
                }

                if(p5Fold != 1){
                    pEndTextLine("Player 5 Has: ", rpc::hashFiveone, rpc::hashFivetwo, 5, p5Rank);
                }
                break;

            case 6:
                ui->logTextBrowser->setText("");

                if(p1Fold != 1){
                    pEndTextLine("Player 1 Has: ", rpc::hashOneone, rpc::hashOnetwo, 1, p1Rank);
                }

                if(p2Fold != 1){
                    pEndTextLine("Player 2 Has: ", rpc::hashTwoone, rpc::hashTwotwo, 2, p2Rank);
                }

                if(p3Fold != 1){
                    pEndTextLine("Player 3 Has: ", rpc::hashThreeone, rpc::hashThreetwo, 3, p3Rank);
                }

                if(p4Fold != 1){
                    pEndTextLine("Player 4 Has: ", rpc::hashFourone, rpc::hashFourtwo, 4, p4Rank);
                }

                if(p5Fold != 1){
                    pEndTextLine("Player 5 Has: ", rpc::hashFiveone, rpc::hashFivetwo, 5, p5Rank);
                }

                if(p6Fold != 1){
                    pEndTextLine("Player 6 Has: ", rpc::hashSixone, rpc::hashSixtwo, 6, p6Rank);
                }
                break;

            }
        }

        /// Get all ranks and compare
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
            /// Compare if there is no outright winner, or two hands of same lowest rank
            int highestPair[] = { p1HighPair, p2HighPair, p3HighPair, p4HighPair, p5HighPair, p6HighPair };
            int highestTrip[] = { p1HighTrip, p2HighTrip, p3HighTrip, p4HighTrip, p5HighTrip, p6HighTrip };
            std::sort(highestPair, highestPair + 6);
            std::sort(highestTrip, highestTrip + 6);
            /// If player hand is not the winning rank or if doesn't have high pair or trip, strip hand
            if(p1Rank != winningRank[0] || (winningRank[0] == 9 && p1HighPair != highestPair[5]) || (winningRank[0] == 8 && p1HighPair != highestPair[5]) || (winningRank[0] == 7 && p1HighPair != highestPair[5]) || (winningRank[0] == 4 && p1HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p1HighTrip != highestTrip[5])){
                less1();
            }

            if(p2Rank != winningRank[0] || (winningRank[0] == 9 && p2HighPair != highestPair[5]) || (winningRank[0] == 8 && p2HighPair != highestPair[5]) || (winningRank[0] == 7 && p2HighPair != highestPair[5]) || (winningRank[0] == 4 && p2HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p2HighTrip != highestTrip[5])){
                less2();
            }

            if(p3Rank != winningRank[0] || (winningRank[0] == 9 && p3HighPair != highestPair[5]) || (winningRank[0] == 8 && p3HighPair != highestPair[5]) || (winningRank[0] == 7 && p3HighPair != highestPair[5]) || (winningRank[0] == 4 && p3HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p3HighTrip != highestTrip[5])){
                less3();
            }

            if(p4Rank != winningRank[0] || (winningRank[0] == 9 && p4HighPair != highestPair[5]) || (winningRank[0] == 8 && p4HighPair != highestPair[5]) || (winningRank[0] == 7 && p4HighPair != highestPair[5]) || (winningRank[0] == 4 && p4HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p4HighTrip != highestTrip[5])){
                less4();
            }

            if(p5Rank != winningRank[0] || (winningRank[0] == 9 && p5HighPair != highestPair[5]) || (winningRank[0] == 8 && p5HighPair != highestPair[5]) || (winningRank[0] == 7 && p5HighPair != highestPair[5]) || (winningRank[0] == 4 && p5HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p5HighTrip != highestTrip[5])){
                less5();
            }

            if(p6Rank != winningRank[0] || (winningRank[0] == 9 && p6HighPair != highestPair[5]) || (winningRank[0] == 8 && p6HighPair != highestPair[5]) || (winningRank[0] == 7 && p6HighPair != highestPair[5]) || (winningRank[0] == 4 && p6HighTrip != highestTrip[5]) || (winningRank[0] == 3 && p6HighTrip != highestTrip[5])){
                less6();
            }


            if(winningRank[0] == 10 || winningRank[0] == 6 || winningRank[0] == 5 || winningRank[0] == 2){       /// Compares and strips loosing hands for high card situations
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
                }       /// Comapres all left over hands for highcard
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
                ui->turnReadOut->setText("Push, Split pot");
                compareLoop();
                if(rpc::oneId == rpc::IdHash){

                    if(Menu::autoPayout == true && rpc::paidOut == false && rpc::pot != 0){     /// Contract not set up for split pot situation, owner will split
                        rpc::paidOut = true;
                        payoutDelay(30);
                        splitWinner(p1Fold, p2Fold, p3Fold, p4Fold, p5Fold, p6Fold);
                    }

                }

            }

        }

    }
    MainWindow::displayedRes = true;
    if(Menu::os == "macos" || Menu::os == "osx" || Menu::os == "darwin" ){
        ui->logTextBrowser->setFontPointSize(30);
    }else {
        ui->logTextBrowser->setFontPointSize(24);
    }
}


QString MainWindow::deckSelect(int d)   /// Gets deck path prefix for card images
{
    QString path;
    QString pre = QDir().absolutePath();
    QString post;
    switch(d){
    case 0: post = ":/images/cards/standard/light/"; break;
    case 1: post = ":/images/cards/standard/dark/"; break;
    default: post = "/cards/"+ui->deckComboBox->currentText()+"/"+ui->deckComboBox->currentText()+"/"; break;
    }

    path = pre+post;
    if(d < 2){
        return post;
    }else {
        return path;
    }
}


QString MainWindow::backSelect(int d)   /// Gets back path prefix for card images
{
    QString path;
    QString pre = QDir().absolutePath();
    QString post;
    switch(d){
    case 0: post = ":/images/cards/backs/back1.png"; break;
    case 1: post = ":/images/cards/backs/back2.png"; break;
    default: post = "/cards/backs/"+ui->backComboBox->currentText()+"/"+ui->backComboBox->currentText()+".png"; break;
    }
    path = pre+post;
    if(d < 2){
        return post;
    }else {
        return path;
    }
}


void MainWindow::blankDisplay()  /// Shows null cards when not playing
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->backComboBox->currentIndex() > 1){
            ui->flopCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->flopCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->flopCard3Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->turnCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->riverCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->holeCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->holeCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
        }else {
            ui->flopCard1Label->setPixmap(QPixmap(displayStandard(0)));
            ui->flopCard2Label->setPixmap(QPixmap(displayStandard(0)));
            ui->flopCard3Label->setPixmap(QPixmap(displayStandard(0)));
            ui->turnCardLabel->setPixmap(QPixmap(displayStandard(0)));
            ui->riverCardLabel->setPixmap(QPixmap(displayStandard(0)));
            ui->holeCard1Label->setPixmap(QPixmap(displayStandard(0)));
            ui->holeCard2Label->setPixmap(QPixmap(displayStandard(0)));
        }
    }else if(ui->playerId->value() > 1){
        ui->holeCard1Label->setGeometry(70, 20, 166, 227);
        ui->holeCard2Label->setGeometry(0, 10, 166, 227);
        displayShared(0, 0);
    }else {
        if(ui->backComboBox->currentIndex() > 1){
            ui->flopCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->flopCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->flopCard3Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->turnCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->riverCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->holeCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            ui->holeCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
        }else {
            ui->flopCard1Label->setPixmap(QPixmap(displayStandard(0)));
            ui->flopCard2Label->setPixmap(QPixmap(displayStandard(0)));
            ui->flopCard3Label->setPixmap(QPixmap(displayStandard(0)));
            ui->turnCardLabel->setPixmap(QPixmap(displayStandard(0)));
            ui->riverCardLabel->setPixmap(QPixmap(displayStandard(0)));
            ui->holeCard1Label->setPixmap(QPixmap(displayStandard(0)));
            ui->holeCard2Label->setPixmap(QPixmap(displayStandard(0)));
        }
    }
}


QString MainWindow::handToText(int rank)       /// Player card value for end text readout
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


QString MainWindow::hasDisplay(int c)         /// Displays which final hand combination player has after evaluating winner
{
    QString cardEquiv;
    switch (c){
    case 2: cardEquiv = "2 "; break;
    case 3: cardEquiv = "3 "; break;
    case 4: cardEquiv = "4 "; break;
    case 5: cardEquiv = "5 "; break;
    case 6: cardEquiv = "6 "; break;
    case 7: cardEquiv = "7 "; break;
    case 8: cardEquiv = "8 "; break;
    case 9: cardEquiv = "9 "; break;
    case 10: cardEquiv = "10 "; break;
    case 11: cardEquiv = "J "; break;
    case 12: cardEquiv = "Q "; break;
    case 13: cardEquiv = "K "; break;
    case 14: cardEquiv = "A "; break;
    }
    return cardEquiv;
}


QString MainWindow::thisHandIs(int p)        /// Displays the hand which we evaluated
{   
    QString combined;
    switch (p){
    case 1: combined = "- "+hasDisplay(p1HighCardArr[0])+hasDisplay(p1HighCardArr[1])+hasDisplay(p1HighCardArr[2])+hasDisplay(p1HighCardArr[3])+hasDisplay(p1HighCardArr[4]);
        break;
    case 2: combined = "- "+hasDisplay(p2HighCardArr[0])+hasDisplay(p2HighCardArr[1])+hasDisplay(p2HighCardArr[2])+hasDisplay(p2HighCardArr[3])+hasDisplay(p2HighCardArr[4]);
        break;
    case 3: combined = "- "+hasDisplay(p3HighCardArr[0])+hasDisplay(p3HighCardArr[1])+hasDisplay(p3HighCardArr[2])+hasDisplay(p3HighCardArr[3])+hasDisplay(p3HighCardArr[4]);
        break;
    case 4: combined = "- "+hasDisplay(p4HighCardArr[0])+hasDisplay(p4HighCardArr[1])+hasDisplay(p4HighCardArr[2])+hasDisplay(p4HighCardArr[3])+hasDisplay(p4HighCardArr[4]);
        break;
    case 5: combined = "- "+hasDisplay(p5HighCardArr[0])+hasDisplay(p5HighCardArr[1])+hasDisplay(p5HighCardArr[2])+hasDisplay(p5HighCardArr[3])+hasDisplay(p5HighCardArr[4]);
        break;
    case 6: combined = "- "+hasDisplay(p6HighCardArr[0])+hasDisplay(p6HighCardArr[1])+hasDisplay(p6HighCardArr[2])+hasDisplay(p6HighCardArr[3])+hasDisplay(p6HighCardArr[4]);
        break;
    }
    return combined;
}


QString MainWindow::findCards(int card)     /// To show all hand results at end
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
        QImageReader reader(backSelect(ui->backComboBox->currentIndex()));
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
           case 0: suffix = "card1.png"; break;
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


void MainWindow::displayShared(int card, int where)   /// Gets shared card image
{
    QByteArray backData = rpc::sharedBack.toUtf8();
    QByteArray faceData = rpc::sharedFace.toUtf8();
    QByteArray backText = QByteArray::fromHex(backData);
    QByteArray faceText = QByteArray::fromHex(faceData);
    QString back = QString::fromLatin1(backText.data());
    QString face = QString::fromLatin1(faceText.data());
    QString suffix;

    if(card > 0){
        switch (card){
        case 0: suffix = "card1.png"; break;
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

        QUrl imageUrl(face+suffix);

        if(where == 1 && MainWindow::shared1 == false){
            c1_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c1_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage1()));

        }else if(where == 2 && MainWindow::shared2 == false) {
            c2_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c2_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage2()));

        }else if(where == 3 && MainWindow::shared3 == false) {
            c3_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c3_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage3()));

        }else if(where == 4 && MainWindow::shared4 == false) {
            c4_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c4_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage4()));

        }else if(where == 5 && MainWindow::shared5 == false) {
            c5_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c5_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage5()));

        }else if(where == 6 && MainWindow::shared6 == false) {
            c6_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c6_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage6()));

        }else if(where == 7 && MainWindow::shared7 == false) {
            c7_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(c7_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadCardImage7()));
        }

    }else {
        if(MainWindow::shared0 == false){
            QUrl imageUrl(back);
            b_ImgCtrl = new FileDownloader(imageUrl, this);
            connect(b_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadBackImage()));
        }

    }

}


void MainWindow::displayFlop(int flop1, int flop2, int flop3)   /// Displays 3 flop cards
{
    if(flop1 > 0){
        if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
            if(ui->deckComboBox->currentIndex() > 1){
                ui->flopCard1Label->setPixmap(QPixmap::fromImage(displayCustom(flop1)));
                ui->flopCard2Label->setPixmap(QPixmap::fromImage(displayCustom(flop2)));
                ui->flopCard3Label->setPixmap(QPixmap::fromImage(displayCustom(flop3)));
            }else {
                ui->flopCard1Label->setPixmap(QPixmap(displayStandard(flop1)));
                ui->flopCard2Label->setPixmap(QPixmap(displayStandard(flop2)));
                ui->flopCard3Label->setPixmap(QPixmap(displayStandard(flop3)));
            }
        }else {
            displayShared(flop1, 3);
            displayShared(flop2, 4);
            displayShared(flop3, 5);
        }

    }else {
        if(Menu::sharedDeck == false || ui->playerId->value() == 0){
            if(ui->backComboBox->currentIndex() > 1){
                ui->flopCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->flopCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->flopCard3Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->flopCard1Label->setPixmap(QPixmap(displayStandard(0)));
                ui->flopCard2Label->setPixmap(QPixmap(displayStandard(0)));
                ui->flopCard3Label->setPixmap(QPixmap(displayStandard(0)));
            }
        }else if(ui->playerId->value() > 1){
            displayShared(0, 0);
        }else {
            if(ui->backComboBox->currentIndex() > 1){
                ui->flopCard1Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->flopCard2Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
                ui->flopCard3Label->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->flopCard1Label->setPixmap(QPixmap(displayStandard(0)));
                ui->flopCard2Label->setPixmap(QPixmap(displayStandard(0)));
                ui->flopCard3Label->setPixmap(QPixmap(displayStandard(0)));
            }
        }
    }
}


void MainWindow::displayTurnCard(int card)   ///  Displays turn card
{
    if(card > 0){
        if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
            if(ui->deckComboBox->currentIndex() > 1){
                ui->turnCardLabel->setPixmap(QPixmap::fromImage(displayCustom(card)));
            }else {
                ui->turnCardLabel->setPixmap(QPixmap(displayStandard(card)));
            }
        }else {
            displayShared(card, 6);
        }
    }else {
        if(Menu::sharedDeck == false || ui->playerId->value() == 0){
            if(ui->backComboBox->currentIndex() > 1){
                ui->turnCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->turnCardLabel->setPixmap(QPixmap(displayStandard(0)));
            }
        }else if(ui->playerId->value() > 1){
            displayShared(0, 0);
        }else {
            if(ui->backComboBox->currentIndex() > 1){
                ui->turnCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->turnCardLabel->setPixmap(QPixmap(displayStandard(0)));
            }
        }
    }
}


void MainWindow::displayRiverCard(int card)   ///  Displays river card
{
    if(card > 0){
        if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
            if(ui->deckComboBox->currentIndex() > 1){
                ui->riverCardLabel->setPixmap(QPixmap::fromImage(displayCustom(card)));
            }else {
                ui->riverCardLabel->setPixmap(QPixmap(displayStandard(card)));
            }
        }else {
            displayShared(card, 7);
        }
    }else {
        if(Menu::sharedDeck == false || ui->playerId->value() == 0){
            if(ui->backComboBox->currentIndex() > 1){
                ui->riverCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->riverCardLabel->setPixmap(QPixmap(displayStandard(0)));
            }
        }else if(ui->playerId->value() > 1){
            displayShared(0, 0);
        }else {
            if(ui->backComboBox->currentIndex() > 1){
                ui->riverCardLabel->setPixmap(QPixmap::fromImage(displayCustom(0)));
            }else {
                ui->riverCardLabel->setPixmap(QPixmap(displayStandard(0)));
            }
        }
    }
}
