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


void MainWindow::deltTo()
{
    if(!rpc::hashOneone.isEmpty()){
        ui->player1ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player1ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }

    if(!rpc::hashTwoone.isEmpty()){
        ui->player2ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player2ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }

    if(!rpc::hashThreeone.isEmpty()){
        ui->player3ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player3ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }

    if(!rpc::hashFourone.isEmpty()){
        ui->player4ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player4ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }

    if(!rpc::hashFiveone.isEmpty()){
        ui->player5ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player5ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }

    if(!rpc::hashSixone.isEmpty()){
        ui->player6ResultLabel_a->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
        ui->player6ResultLabel_b->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    }
}


void MainWindow::blankResult1()
{
    if(!rpc::hashOneone.isEmpty()){
        displayResultCard1_a(0);
        displayResultCard1_b(0);
    }else {
        ui->player1ResultLabel_a->clear();
        ui->player1ResultLabel_b->clear();
    }
}


void MainWindow::displayResult1(int a, int b)
{
    displayResultCard1_a(a);
    displayResultCard1_b(b);
}


void MainWindow::displayResultCard1_a(int card) /// Displays player cards at table
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player1ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player1ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player1ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard1_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player1ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player1ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player1ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::blankResult2()
{
    if(!rpc::hashTwoone.isEmpty()){
        displayResultCard2_a(0);
        displayResultCard2_b(0);
    }else {
        ui->player2ResultLabel_a->clear();
        ui->player2ResultLabel_b->clear();
    }
}


void MainWindow::displayResult2(int a, int b)
{
    displayResultCard2_a(a);
    displayResultCard2_b(b);
}


void MainWindow::displayResultCard2_a(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player2ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player2ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player2ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard2_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player2ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player2ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player2ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::blankResult3()
{
    if(!rpc::hashThreeone.isEmpty()){
        displayResultCard3_a(0);
        displayResultCard3_b(0);
    }else {
        ui->player3ResultLabel_a->clear();
        ui->player3ResultLabel_b->clear();
    }
}


void MainWindow::displayResult3(int a, int b)
{
    displayResultCard3_a(a);
    displayResultCard3_b(b);
}


void MainWindow::displayResultCard3_a(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player3ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player3ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player3ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard3_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player3ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player3ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player3ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::blankResult4()
{
    if(!rpc::hashFourone.isEmpty()){
        displayResultCard4_a(0);
        displayResultCard4_b(0);
    }else {
        ui->player4ResultLabel_a->clear();
        ui->player4ResultLabel_b->clear();
    }
}


void MainWindow::displayResult4(int a, int b)
{
    displayResultCard4_a(a);
    displayResultCard4_b(b);
}


void MainWindow::displayResultCard4_a(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player4ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player4ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player4ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard4_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player4ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player4ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player4ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::blankResult5()
{
    if(!rpc::hashFiveone.isEmpty()){
        displayResultCard5_a(0);
        displayResultCard5_b(0);
    }else {
        ui->player5ResultLabel_a->clear();
        ui->player5ResultLabel_b->clear();
    }
}


void MainWindow::displayResult5(int a, int b)
{
    displayResultCard5_a(a);
    displayResultCard5_b(b);
}


void MainWindow::displayResultCard5_a(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player5ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player5ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player5ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard5_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player5ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player5ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player5ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::blankResult6()
{
    if(!rpc::hashSixone.isEmpty()){
        displayResultCard6_a(0);
        displayResultCard6_b(0);
    }else {
        ui->player6ResultLabel_a->clear();
        ui->player6ResultLabel_b->clear();
    }
}


void MainWindow::displayResult6(int a, int b)
{
    displayResultCard6_a(a);
    displayResultCard6_b(b);
}


void MainWindow::displayResultCard6_a(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player6ResultLabel_a->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player6ResultLabel_a->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player6ResultLabel_a->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}


void MainWindow::displayResultCard6_b(int card)
{
    if(Menu::sharedDeck == false || rpc::IdHash == rpc::oneId || ui->playerId->value() == 0){
        if(ui->deckComboBox->currentIndex() > 1){
            ui->player6ResultLabel_b->setPixmap(QPixmap::fromImage(displayCustom(card)));
        }else {
            ui->player6ResultLabel_b->setPixmap(QPixmap(displayStandard(card)));
        }
    }else {
        ui->player6ResultLabel_b->setPixmap(QPixmap::fromImage(displayShared(card)));
    }
}

