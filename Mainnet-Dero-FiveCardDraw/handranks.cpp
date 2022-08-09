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

#include "handranks.h"
#include "ui_handranks.h"
#include "mainwindow.h"


HandRanks::HandRanks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HandRanks)
{
    ui->setupUi(this);
    setFonts();
}


HandRanks::~HandRanks()
{
    delete ui;
}


void HandRanks::setFonts()
{

    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont ubuntuRegular(fontFamily1);
    ui->hrTextBrowser->setFont(ubuntuRegular);
    ui->buttonBox->setFont(ubuntuRegular);

}


int MainWindow::getArray(int card)  /// Splipts card into value and suit for hand compare
{
    switch(card){
    ////// Spades
    case 1: arrSplit [0] = 1;
            arrSplit [1] = 0; break;

    case 2: arrSplit [0] = 2;
            arrSplit [1] = 0; break;

    case 3: arrSplit [0] = 3;
            arrSplit [1] = 0; break;

    case 4: arrSplit [0] = 4;
            arrSplit [1] = 0; break;

    case 5: arrSplit [0] = 5;
            arrSplit [1] = 0; break;

    case 6: arrSplit [0] = 6;
            arrSplit [1] = 0; break;

    case 7: arrSplit [0] = 7;
            arrSplit [1] = 0; break;

    case 8: arrSplit [0] = 8;
            arrSplit [1] = 0; break;

    case 9: arrSplit [0] = 9;
            arrSplit [1] = 0; break;

    case 10: arrSplit [0] = 10;
             arrSplit [1] = 0; break;

    case 11: arrSplit [0] = 11;
             arrSplit [1] = 0; break;

    case 12: arrSplit [0] = 12;
             arrSplit [1] = 0; break;

    case 13: arrSplit [0] = 13;
             arrSplit [1] = 0; break;

             ////// Hearts
    case 14: arrSplit [0] = 1;
             arrSplit [1] = 1; break;

    case 15: arrSplit [0] = 2;
             arrSplit [1] = 1; break;

    case 16: arrSplit [0] = 3;
             arrSplit [1] = 1; break;

    case 17: arrSplit [0] = 4;
             arrSplit [1] = 1; break;

    case 18: arrSplit [0] = 5;
             arrSplit [1] = 1; break;

    case 19: arrSplit [0] = 6;
             arrSplit [1] = 1; break;

    case 20: arrSplit [0] = 7;
             arrSplit [1] = 1; break;

    case 21: arrSplit [0] = 8;
             arrSplit [1] = 1; break;

    case 22: arrSplit [0] = 9;
             arrSplit [1] = 1; break;

    case 23: arrSplit [0] = 10;
             arrSplit [1] = 1; break;

    case 24: arrSplit [0] = 11;
             arrSplit [1] = 1; break;

    case 25: arrSplit [0] = 12;
             arrSplit [1] = 1; break;

    case 26: arrSplit [0] = 13;
             arrSplit [1] = 1; break;

             ////// Clubs
    case 27: arrSplit [0] = 1;
             arrSplit [1] = 2; break;

    case 28: arrSplit [0] = 2;
             arrSplit [1] = 2; break;

    case 29: arrSplit [0] = 3;
             arrSplit [1] = 2; break;

    case 30: arrSplit [0] = 4;
             arrSplit [1] = 2; break;

    case 31: arrSplit [0] = 5;
             arrSplit [1] = 2; break;

    case 32: arrSplit [0] = 6;
             arrSplit [1] = 2; break;

    case 33: arrSplit [0] = 7;
             arrSplit [1] = 2; break;

    case 34: arrSplit [0] = 8;
             arrSplit [1] = 2; break;

    case 35: arrSplit [0] = 9;
             arrSplit [1] = 2; break;

    case 36: arrSplit [0] = 10;
             arrSplit [1] = 2; break;

    case 37: arrSplit [0] = 11;
             arrSplit [1] = 2; break;

    case 38: arrSplit [0] = 12;
             arrSplit [1] = 2; break;

    case 39: arrSplit [0] = 13;
             arrSplit [1] = 2; break;

             ////// Diamonds
    case 40: arrSplit [0] = 1;
             arrSplit [1] = 3; break;

    case 41: arrSplit [0] = 2;
             arrSplit [1] = 3; break;

    case 42: arrSplit [0] = 3;
             arrSplit [1] = 3; break;

    case 43: arrSplit [0] = 4;
             arrSplit [1] = 3; break;

    case 44: arrSplit [0] = 5;
             arrSplit [1] = 3; break;

    case 45: arrSplit [0] = 6;
             arrSplit [1] = 3; break;

    case 46: arrSplit [0] = 7;
             arrSplit [1] = 3; break;

    case 47: arrSplit [0] = 8;
             arrSplit [1] = 3; break;

    case 48: arrSplit [0] = 9;
             arrSplit [1] = 3; break;

    case 49: arrSplit [0] = 10;
             arrSplit [1] = 3; break;

    case 50: arrSplit [0] = 11;
             arrSplit [1] = 3; break;

    case 51: arrSplit [0] = 12;
             arrSplit [1] = 3; break;

    case 52: arrSplit [0] = 13;
             arrSplit [1] = 3; break;

    }
    return 0;

}


int MainWindow::makeHand()
{
   int nakedHand[] = {suitSplit1[0], suitSplit2[0], suitSplit3[0], suitSplit4[0], suitSplit5[0]};
   int nakedSuits[] = {suitSplit1[1], suitSplit2[1], suitSplit3[1], suitSplit4[1], suitSplit5[1]};

   int n = sizeof(nakedHand) / sizeof(nakedHand[0]);
   std::sort(nakedHand, nakedHand + n);

   /// Royal flush
   if(nakedHand[0] == 1 && nakedHand[1] == 10 && nakedHand[2] == 11 && nakedHand[3] == 12 && nakedHand[4] == 13 &&
      nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4]){
       return 1;
   }

   /// Straight flush
   if(nakedHand[0]+1 == nakedHand[1] && nakedHand[1]+1 == nakedHand[2] && nakedHand[2]+1 == nakedHand[3] && nakedHand[3]+1 == nakedHand[4] && nakedHand[0]+4 == nakedHand[4] &&
      nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4]){
       return 2;
   }

   /// Four of a Kind
   if((nakedHand[0] == nakedHand[1] && nakedHand[1] == nakedHand[2] && nakedHand[2] == nakedHand[3]) ||
      (nakedHand[1] == nakedHand[2] && nakedHand[2] == nakedHand[3] && nakedHand[3] == nakedHand[4])){
       return 3;
   }

   /// Full House
   if((nakedHand[0] == nakedHand[1] && nakedHand[1] == nakedHand[2] && nakedHand[3] == nakedHand[4]) ||
      (nakedHand[0] == nakedHand[1] && nakedHand[2] == nakedHand[3] && nakedHand[3] == nakedHand[4])){
       return 4;
   }

   /// Flush
   if(nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4]){
       return 5;
   }

   /// Straight
   if((nakedHand[0]+1 == nakedHand[1] && nakedHand[1]+1 == nakedHand[2] && nakedHand[2]+1 == nakedHand[3] && nakedHand[3]+1 == nakedHand[4] && nakedHand[0]+4 == nakedHand[4]) ||
      (nakedHand[0] == 1 && nakedHand[1] == 10 && nakedHand[2] == 11 && nakedHand[3] == 12 && nakedHand[4] == 13)){
       return 6;
   }

   /// Three of a Kind
   if((nakedHand[0] == nakedHand[1] && nakedHand[1] == nakedHand[2]) ||
      (nakedHand[1] == nakedHand[2] && nakedHand[2] == nakedHand[3]) ||
      (nakedHand[2] == nakedHand[3] && nakedHand[3] == nakedHand[4])){
       return 7;
   }

   /// Two Pair
   if((nakedHand[0] == nakedHand[1] && nakedHand[2] == nakedHand[3]) ||
      (nakedHand[1] == nakedHand[2] && nakedHand[3] == nakedHand[4]) ||
      (nakedHand[0] == nakedHand[1] && nakedHand[3] == nakedHand[4])){
       return 8;
   }

   /// Pair
   if(nakedHand[0] == nakedHand[1] || nakedHand[0] == nakedHand[2] || nakedHand[0] == nakedHand[3] || nakedHand[0] == nakedHand[4] ||
      nakedHand[1] == nakedHand[2] || nakedHand[1] == nakedHand[3] || nakedHand[1] == nakedHand[4] ||
      nakedHand[2] == nakedHand[3] || nakedHand[2] == nakedHand[4] ||
      nakedHand[3] == nakedHand[4]){;
       return 9;
   }else {
       return 10;
   }

}


void MainWindow::compare1_2()   /// Compares two players hands
{
    if((p1HighCardArr[4] > p2HighCardArr[4]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] > p2HighCardArr[3]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] > p2HighCardArr[2]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] == p2HighCardArr[2] && p1HighCardArr[1] > p2HighCardArr[1]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] == p2HighCardArr[2] && p1HighCardArr[1] == p2HighCardArr[1] && p1HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare1_3()
{
    if((p1HighCardArr[4] > p3HighCardArr[4]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] > p3HighCardArr[3]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] > p3HighCardArr[2]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] == p3HighCardArr[2] && p1HighCardArr[1] > p3HighCardArr[1]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] == p3HighCardArr[2] && p1HighCardArr[1] == p3HighCardArr[1] && p1HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare1_4()
{
    if((p1HighCardArr[4] > p4HighCardArr[4]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] > p4HighCardArr[3]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] > p4HighCardArr[2]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] == p4HighCardArr[2] && p1HighCardArr[1] > p4HighCardArr[1]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] == p4HighCardArr[2] && p1HighCardArr[1] == p4HighCardArr[1] && p1HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare1_5()
{
    if((p1HighCardArr[4] > p5HighCardArr[4]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] > p5HighCardArr[3]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] > p5HighCardArr[2]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] == p5HighCardArr[2] && p1HighCardArr[1] > p5HighCardArr[1]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] == p5HighCardArr[2] && p1HighCardArr[1] == p5HighCardArr[1] && p1HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare1_6()
{
    if((p1HighCardArr[4] > p6HighCardArr[4]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] > p6HighCardArr[3]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] > p6HighCardArr[2]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] == p6HighCardArr[2] && p1HighCardArr[1] > p6HighCardArr[1]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] == p6HighCardArr[2] && p1HighCardArr[1] == p6HighCardArr[1] && p1HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare2_1()
{
    if((p2HighCardArr[4] > p1HighCardArr[4]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] > p1HighCardArr[3]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] > p1HighCardArr[2]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] == p1HighCardArr[2] && p2HighCardArr[1] > p1HighCardArr[1]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] == p1HighCardArr[2] && p2HighCardArr[1] == p1HighCardArr[1] && p2HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare2_3()
{
    if((p2HighCardArr[4] > p3HighCardArr[4]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] > p3HighCardArr[3]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] > p3HighCardArr[2]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] == p3HighCardArr[2] && p2HighCardArr[1] > p3HighCardArr[1]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] == p3HighCardArr[2] && p2HighCardArr[1] == p3HighCardArr[1] && p2HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare2_4()
{
    if((p2HighCardArr[4] > p4HighCardArr[4]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] > p4HighCardArr[3]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] > p4HighCardArr[2]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] == p4HighCardArr[2] && p2HighCardArr[1] > p4HighCardArr[1]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] == p4HighCardArr[2] && p2HighCardArr[1] == p4HighCardArr[1] && p2HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare2_5()
{
    if((p2HighCardArr[4] > p5HighCardArr[4]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] > p5HighCardArr[3]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] > p5HighCardArr[2]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] == p5HighCardArr[2] && p2HighCardArr[1] > p5HighCardArr[1]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] == p5HighCardArr[2] && p2HighCardArr[1] == p5HighCardArr[1] && p2HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare2_6()
{
    if((p2HighCardArr[4] > p6HighCardArr[4]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] > p6HighCardArr[3]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] > p6HighCardArr[2]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] == p6HighCardArr[2] && p2HighCardArr[1] > p6HighCardArr[1]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] == p6HighCardArr[2] && p2HighCardArr[1] == p6HighCardArr[1] && p2HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare3_1()
{
    if((p3HighCardArr[4] > p1HighCardArr[4]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] > p1HighCardArr[3]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] > p1HighCardArr[2]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] == p1HighCardArr[2] && p3HighCardArr[1] > p1HighCardArr[1]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] == p1HighCardArr[2] && p3HighCardArr[1] == p1HighCardArr[1] && p3HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare3_2()
{
    if((p3HighCardArr[4] > p2HighCardArr[4]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] > p2HighCardArr[3]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] > p2HighCardArr[2]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] == p2HighCardArr[2] && p3HighCardArr[1] > p2HighCardArr[1]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] == p2HighCardArr[2] && p3HighCardArr[1] == p2HighCardArr[1] && p3HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare3_4()
{
    if((p3HighCardArr[4] > p4HighCardArr[4]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] > p4HighCardArr[3]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] > p4HighCardArr[2]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] == p4HighCardArr[2] && p3HighCardArr[1] > p4HighCardArr[1]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] == p4HighCardArr[2] && p3HighCardArr[1] == p4HighCardArr[1] && p3HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare3_5()
{
    if((p3HighCardArr[4] > p5HighCardArr[4]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] > p5HighCardArr[3]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] > p5HighCardArr[2]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] == p5HighCardArr[2] && p3HighCardArr[1] > p5HighCardArr[1]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] == p5HighCardArr[2] && p3HighCardArr[1] == p5HighCardArr[1] && p3HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare3_6()
{
    if((p3HighCardArr[4] > p6HighCardArr[4]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] > p6HighCardArr[3]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] > p6HighCardArr[2]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] == p6HighCardArr[2] && p3HighCardArr[1] > p6HighCardArr[1]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] == p6HighCardArr[2] && p3HighCardArr[1] == p6HighCardArr[1] && p3HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare4_1()
{
    if((p4HighCardArr[4] > p1HighCardArr[4]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] > p1HighCardArr[3]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] > p1HighCardArr[2]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] == p1HighCardArr[2] && p4HighCardArr[1] > p1HighCardArr[1]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] == p1HighCardArr[2] && p4HighCardArr[1] == p1HighCardArr[1] && p4HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare4_2()
{
    if((p4HighCardArr[4] > p2HighCardArr[4]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] > p2HighCardArr[3]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] > p2HighCardArr[2]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] == p2HighCardArr[2] && p4HighCardArr[1] > p2HighCardArr[1]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] == p2HighCardArr[2] && p4HighCardArr[1] == p2HighCardArr[1] && p4HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare4_3()
{
    if((p4HighCardArr[4] > p3HighCardArr[4]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] > p3HighCardArr[3]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] > p3HighCardArr[2]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] == p3HighCardArr[2] && p4HighCardArr[1] > p3HighCardArr[1]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] == p3HighCardArr[2] && p4HighCardArr[1] == p3HighCardArr[1] && p4HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare4_5()
{
    if((p4HighCardArr[4] > p5HighCardArr[4]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] > p5HighCardArr[3]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] > p5HighCardArr[2]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] == p5HighCardArr[2] && p4HighCardArr[1] > p5HighCardArr[1]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] == p5HighCardArr[2] && p4HighCardArr[1] == p5HighCardArr[1] && p4HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare4_6()
{
    if((p4HighCardArr[4] > p6HighCardArr[4]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] > p6HighCardArr[3]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] > p6HighCardArr[2]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] == p6HighCardArr[2] && p4HighCardArr[1] > p6HighCardArr[1]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] == p6HighCardArr[2] && p4HighCardArr[1] == p6HighCardArr[1] && p4HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare5_1()
{
    if((p5HighCardArr[4] > p1HighCardArr[4]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] > p1HighCardArr[3]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] > p1HighCardArr[2]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] == p1HighCardArr[2] && p5HighCardArr[1] > p1HighCardArr[1]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] == p1HighCardArr[2] && p5HighCardArr[1] == p1HighCardArr[1] && p5HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare5_2()
{
    if((p5HighCardArr[4] > p2HighCardArr[4]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] > p2HighCardArr[3]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] > p2HighCardArr[2]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] == p2HighCardArr[2] && p5HighCardArr[1] > p2HighCardArr[1]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] == p2HighCardArr[2] && p5HighCardArr[1] == p2HighCardArr[1] && p5HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare5_3()
{
    if((p5HighCardArr[4] > p3HighCardArr[4]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] > p3HighCardArr[3]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] > p3HighCardArr[2]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] == p3HighCardArr[2] && p5HighCardArr[1] > p3HighCardArr[1]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] == p3HighCardArr[2] && p5HighCardArr[1] == p3HighCardArr[1] && p5HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare5_4()
{
    if((p5HighCardArr[4] > p4HighCardArr[4]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] > p4HighCardArr[3]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] > p4HighCardArr[2]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] == p4HighCardArr[2] && p5HighCardArr[1] > p4HighCardArr[1]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] == p4HighCardArr[2] && p5HighCardArr[1] == p4HighCardArr[1] && p5HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare5_6()
{
    if((p5HighCardArr[4] > p6HighCardArr[4]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] > p6HighCardArr[3]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] > p6HighCardArr[2]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] == p6HighCardArr[2] && p5HighCardArr[1] > p6HighCardArr[1]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] == p6HighCardArr[2] && p5HighCardArr[1] == p6HighCardArr[1] && p5HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare6_1()
{
    if((p6HighCardArr[4] > p1HighCardArr[4]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] > p1HighCardArr[3]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] > p1HighCardArr[2]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] == p1HighCardArr[2] && p6HighCardArr[1] > p1HighCardArr[1]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] == p1HighCardArr[2] && p6HighCardArr[1] == p1HighCardArr[1] && p6HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare6_2()
{
    if((p6HighCardArr[4] > p2HighCardArr[4]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] > p2HighCardArr[3]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] > p2HighCardArr[2]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] == p2HighCardArr[2] && p6HighCardArr[1] > p2HighCardArr[1]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] == p2HighCardArr[2] && p6HighCardArr[1] == p2HighCardArr[1] && p6HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare6_3()
{
    if((p6HighCardArr[4] > p3HighCardArr[4]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] > p3HighCardArr[3]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] > p3HighCardArr[2]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] == p3HighCardArr[2] && p6HighCardArr[1] > p3HighCardArr[1]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] == p3HighCardArr[2] && p6HighCardArr[1] == p3HighCardArr[1] && p6HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare6_4()
{
    if((p6HighCardArr[4] > p4HighCardArr[4]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] > p4HighCardArr[3]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] > p4HighCardArr[2]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] == p4HighCardArr[2] && p6HighCardArr[1] > p4HighCardArr[1]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] == p4HighCardArr[2] && p6HighCardArr[1] == p4HighCardArr[1] && p6HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare6_5()
{
    if((p6HighCardArr[4] > p5HighCardArr[4]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] > p5HighCardArr[3]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] > p5HighCardArr[2]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] == p5HighCardArr[2] && p6HighCardArr[1] > p5HighCardArr[1]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] == p5HighCardArr[2] && p6HighCardArr[1] == p5HighCardArr[1] && p6HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}



void MainWindow::less6()
{
    p6HighCardArr[0] = 0;
    p6HighCardArr[1] = 0;
    p6HighCardArr[2] = 0;
    p6HighCardArr[3] = 0;
    p6HighCardArr[4] = 0;
    p6HighPair = 0;
}


void MainWindow::less5()
{
    p5HighCardArr[0] = 0;
    p5HighCardArr[1] = 0;
    p5HighCardArr[2] = 0;
    p5HighCardArr[3] = 0;
    p5HighCardArr[4] = 0;
    p5HighPair = 0;
}


void MainWindow::less4()
{
    p4HighCardArr[0] = 0;
    p4HighCardArr[1] = 0;
    p4HighCardArr[2] = 0;
    p4HighCardArr[3] = 0;
    p4HighCardArr[4] = 0;
    p4HighPair = 0;
}

void MainWindow::less3()
{
    p3HighCardArr[0] = 0;
    p3HighCardArr[1] = 0;
    p3HighCardArr[2] = 0;
    p3HighCardArr[3] = 0;
    p3HighCardArr[4] = 0;
    p3HighPair = 0;
}

void MainWindow::less2()
{
    p2HighCardArr[0] = 0;
    p2HighCardArr[1] = 0;
    p2HighCardArr[2] = 0;
    p2HighCardArr[3] = 0;
    p2HighCardArr[4] = 0;
    p2HighPair = 0;
}


void MainWindow::less1()
{
    p1HighCardArr[0] = 0;
    p1HighCardArr[1] = 0;
    p1HighCardArr[2] = 0;
    p1HighCardArr[3] = 0;
    p1HighCardArr[4] = 0;
    p1HighPair = 0;
}

