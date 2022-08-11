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
    case 1: arrSplit [0] = 14;
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
    case 14: arrSplit [0] = 14;
             arrSplit [1] = 13; break;

    case 15: arrSplit [0] = 2;
             arrSplit [1] = 13; break;

    case 16: arrSplit [0] = 3;
             arrSplit [1] = 13; break;

    case 17: arrSplit [0] = 4;
             arrSplit [1] = 13; break;

    case 18: arrSplit [0] = 5;
             arrSplit [1] = 13; break;

    case 19: arrSplit [0] = 6;
             arrSplit [1] = 13; break;

    case 20: arrSplit [0] = 7;
             arrSplit [1] = 13; break;

    case 21: arrSplit [0] = 8;
             arrSplit [1] = 13; break;

    case 22: arrSplit [0] = 9;
             arrSplit [1] = 13; break;

    case 23: arrSplit [0] = 10;
             arrSplit [1] = 13; break;

    case 24: arrSplit [0] = 11;
             arrSplit [1] = 13; break;

    case 25: arrSplit [0] = 12;
             arrSplit [1] = 13; break;

    case 26: arrSplit [0] = 13;
             arrSplit [1] = 13; break;

             ////// Clubs
    case 27: arrSplit [0] = 14;
             arrSplit [1] = 26; break;

    case 28: arrSplit [0] = 2;
             arrSplit [1] = 26; break;

    case 29: arrSplit [0] = 3;
             arrSplit [1] = 26; break;

    case 30: arrSplit [0] = 4;
             arrSplit [1] = 26; break;

    case 31: arrSplit [0] = 5;
             arrSplit [1] = 26; break;

    case 32: arrSplit [0] = 6;
             arrSplit [1] = 26; break;

    case 33: arrSplit [0] = 7;
             arrSplit [1] = 26; break;

    case 34: arrSplit [0] = 8;
             arrSplit [1] = 26; break;

    case 35: arrSplit [0] = 9;
             arrSplit [1] = 26; break;

    case 36: arrSplit [0] = 10;
             arrSplit [1] = 26; break;

    case 37: arrSplit [0] = 11;
             arrSplit [1] = 26; break;

    case 38: arrSplit [0] = 12;
             arrSplit [1] = 26; break;

    case 39: arrSplit [0] = 13;
             arrSplit [1] = 26; break;

             ////// Diamonds
    case 40: arrSplit [0] = 14;
             arrSplit [1] = 39; break;

    case 41: arrSplit [0] = 2;
             arrSplit [1] = 39; break;

    case 42: arrSplit [0] = 3;
             arrSplit [1] = 39; break;

    case 43: arrSplit [0] = 4;
             arrSplit [1] = 39; break;

    case 44: arrSplit [0] = 5;
             arrSplit [1] = 39; break;

    case 45: arrSplit [0] = 6;
             arrSplit [1] = 39; break;

    case 46: arrSplit [0] = 7;
             arrSplit [1] = 39; break;

    case 47: arrSplit [0] = 8;
             arrSplit [1] = 39; break;

    case 48: arrSplit [0] = 9;
             arrSplit [1] = 39; break;

    case 49: arrSplit [0] = 10;
             arrSplit [1] = 39; break;

    case 50: arrSplit [0] = 11;
             arrSplit [1] = 39; break;

    case 51: arrSplit [0] = 12;
             arrSplit [1] = 39; break;

    case 52: arrSplit [0] = 13;
             arrSplit [1] = 39; break;

    }
    return 0;

}


int MainWindow::getHighPair(int h[5])    /// Make high pair from hand
{

    int hand[5] = {h[0], h[1], h[2], h[3], h[4]};
    int highPair = 0;

    for (int i = 0; i < 4; ++i){
        if(hand[i] == hand[i+1]){
            if(hand[i] > highPair){
                highPair = hand[i];
            }
        }
    }

    return highPair;
}


int MainWindow::getHighTrip(int h[5])    /// Make high pair from hand
{

    int hand[5] = {h[0], h[1], h[2], h[3], h[4]};
    int highTrip = 0;

    for (int i = 0; i < 3; ++i){
        if(hand[i] == hand[i+1] && hand[i] == hand[i+2]){
            if(hand[i] > highTrip){
                highTrip = hand[i];
            }
        }
    }

    return highTrip;
}


int MainWindow::compareThese()   /// Search thorugh all hand combinations to find best hand
{
    int fRank;
    int nRank;

    /// All community
    int e0Hand[5] = {cc1[0], cc2[0], cc3[0], cc4[0], cc5[0]};
    int e0Suits[5] = {cc1[1], cc2[1], cc3[1], cc4[1], cc5[1]};
    fRank = makeHand(e0Hand, e0Suits);
    std::copy(e0Hand, e0Hand + 5, fHighCardArr);
    // std::copy(e0Suits, e0Suits + 5, fSuitsArr);

    /// Two Hole cards
    int e1Hand[5] = {cc1[0], cc2[0], cc3[0], suitSplit1[0], suitSplit2[0]};
    int e1Suits[5] = {cc1[1], cc2[1], cc3[1], suitSplit1[1], suitSplit2[1]};
    nRank = makeHand(e1Hand, e1Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e1Hand, e1Hand + 5, fHighCardArr);
        // std::copy(e1Suits, e1Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e1Hand, e1Suits);
    }

    int e2Hand[5] = {cc1[0], cc2[0], suitSplit1[0], cc4[0], suitSplit2[0]};
    int e2Suits[5] = {cc1[1], cc2[1], suitSplit1[1], cc4[1], suitSplit2[1]};
    nRank = makeHand(e2Hand, e2Suits);
    if(nRank < fRank){
        fRank = nRank;
        std::copy(e2Hand, e2Hand + 5, fHighCardArr);
        // std::copy(e2Suits, e2Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e2Hand, e2Suits);
        // std::copy(e2Suits, e2Suits + 5, fSuitsArr);
    }

    int e3Hand[5] = {cc1[0], suitSplit1[0], cc3[0], cc4[0], suitSplit2[0]};
    int e3Suits[5] = {cc1[1], suitSplit1[1], cc3[1], cc4[1], suitSplit2[1]};
    nRank = makeHand(e3Hand, e3Suits);
    if(nRank < fRank){
        fRank = nRank;
        std::copy(e3Hand, e3Hand + 5, fHighCardArr);
        // std::copy(e3Suits, e3Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e3Hand, e3Suits);
        // std::copy(e3Suits, e3Suits + 5, fSuitsArr);
    }

    int e4Hand[5] = {suitSplit1[0], cc2[0], cc3[0], cc4[0], suitSplit2[0]};
    int e4Suits[5] = {suitSplit1[1], cc2[1], cc3[1], cc4[1], suitSplit2[1]};
    nRank = makeHand(e4Hand, e4Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e4Hand, e4Hand + 5, fHighCardArr);
        // std::copy(e4Suits, e4Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e4Hand, e4Suits);
        // std::copy(e4Suits, e4Suits + 5, fSuitsArr);
    }

    int e5Hand[5] = {cc1[0], cc2[0], suitSplit1[0], suitSplit2[0], cc5[0]};
    int e5Suits[5] = {cc1[1], cc2[1], suitSplit1[1], suitSplit2[1], cc5[1]};
    nRank = makeHand(e5Hand, e5Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e5Hand, e5Hand + 5, fHighCardArr);
        // std::copy(e5Suits, e5Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e5Hand, e5Suits);
        // std::copy(e5Suits, e5Suits + 5, fSuitsArr);
    }

    int e6Hand[5] = {cc1[0], suitSplit1[0], cc3[0], suitSplit2[0], cc5[0]};
    int e6Suits[5] = {cc1[1], suitSplit1[1], cc3[1], suitSplit2[1], cc5[1]};
    nRank = makeHand(e6Hand, e6Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e6Hand, e6Hand + 5, fHighCardArr);
        // std::copy(e6Suits, e6Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e6Hand, e6Suits);
        // std::copy(e6Suits, e6Suits + 5, fSuitsArr);
    }


    int e7Hand[5] = {suitSplit1[0], cc2[0], cc3[0], suitSplit2[0], cc5[0]};
    int e7Suits[5] = {suitSplit1[1], cc2[1], cc3[1], suitSplit2[1], cc5[1]};
    nRank = makeHand(e7Hand, e7Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e7Hand, e7Hand + 5, fHighCardArr);
        // std::copy(e7Suits, e7Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e7Hand, e7Suits);
        // std::copy(e7Suits, e7Suits + 5, fSuitsArr);
    }

    int e8Hand[5] = {cc1[0], suitSplit1[0], suitSplit2[0], cc4[0], cc5[0]};
    int e8Suits[5] = {cc1[1], suitSplit1[1], suitSplit2[1], cc4[1], cc5[1]};
    nRank = makeHand(e8Hand, e8Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e8Hand, e8Hand + 5, fHighCardArr);
        // std::copy(e8Suits, e8Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e8Hand, e8Suits);
        // std::copy(e8Suits, e8Suits + 5, fSuitsArr);
    }

    int e9Hand[5] = {suitSplit1[0], cc2[0], suitSplit2[0], cc4[0], cc5[0]};
    int e9Suits[5] = {suitSplit1[1], cc2[1], suitSplit2[1], cc4[1], cc5[1]};
    nRank = makeHand(e9Hand, e9Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e9Hand, e9Hand + 5, fHighCardArr);
        // std::copy(e9Suits, e9Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e9Hand, e9Suits);
        // std::copy(e9Suits, e9Suits + 5, fSuitsArr);
    }

    int e10Hand[5] = {suitSplit1[0], suitSplit2[0], cc3[0], cc4[0], cc5[0]};
    int e10Suits[5] = {suitSplit1[1], suitSplit2[1], cc3[1], cc4[1], cc5[1]};
    nRank = makeHand(e10Hand, e10Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e10Hand, e10Hand + 5, fHighCardArr);
        // std::copy(e10Suits, e10Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e10Hand, e10Suits);
        // std::copy(e10Suits, e10Suits + 5, fSuitsArr);
    }

    /// First Hole card
    int e11Hand[5] = {cc1[0], cc2[0], cc3[0], cc4[0], suitSplit1[0]};
    int e11Suits[5] = {cc1[1], cc2[1], cc3[1], cc4[1], suitSplit1[1]};
    nRank = makeHand(e11Hand, e11Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e11Hand, e11Hand + 5, fHighCardArr);
        // std::copy(e11Suits, e11Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e11Hand, e11Suits);
        // std::copy(e11Suits, e11Suits + 5, fSuitsArr);
    }

    int e12Hand[5] = {cc1[0], cc2[0], cc3[0], suitSplit1[0], cc5[0]};
    int e12Suits[5] = {cc1[1], cc2[1], cc3[1], suitSplit1[1], cc5[1]};
    nRank = makeHand(e12Hand, e12Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e12Hand, e12Hand + 5, fHighCardArr);
        // std::copy(e12Suits, e12Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e12Hand, e12Suits);
        // std::copy(e12Suits, e12Suits + 5, fSuitsArr);
    }

    int e13Hand[5] = {cc1[0], cc2[0], suitSplit1[0], cc4[0], cc5[0]};
    int e13Suits[5] = {cc1[1], cc2[1], suitSplit1[1], cc4[1], cc5[1]};
    nRank = makeHand(e13Hand, e13Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e13Hand, e13Hand + 5, fHighCardArr);
        // std::copy(e13Suits, e13Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e13Hand, e13Suits);
        // std::copy(e13Suits, e13Suits + 5, fSuitsArr);
    }

    int e14Hand[5] = {cc1[0], suitSplit1[0], cc3[0], cc4[0], cc5[0]};
    int e14Suits[5] = {cc1[1], suitSplit1[1], cc3[1], cc4[1], cc5[1]};
    nRank = makeHand(e14Hand, e14Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e14Hand, e14Hand + 5, fHighCardArr);
        // std::copy(e14Suits, e14Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e14Hand, e14Suits);
        // std::copy(e14Suits, e14Suits + 5, fSuitsArr);
    }

    int e15Hand[5] = {suitSplit1[0], cc2[0], cc3[0], cc4[0], cc5[0]};
    int e15Suits[5] = {suitSplit1[1], cc2[1], cc3[1], cc4[1], cc5[1]};
    nRank = makeHand(e15Hand, e15Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e15Hand, e15Hand + 5, fHighCardArr);
        // std::copy(e15Suits, e15Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e15Hand, e15Suits);
        // std::copy(e15Suits, e15Suits + 5, fSuitsArr);
    }

    /// Second Hole card
    int e16Hand[5] = {cc1[0], cc2[0], cc3[0], cc4[0], suitSplit2[0]};
    int e16Suits[5] = {cc1[1], cc2[1], cc3[1], cc4[1], suitSplit2[1]};
    nRank = makeHand(e16Hand, e16Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e16Hand, e16Hand + 5, fHighCardArr);
        // std::copy(e16Suits, e16Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e16Hand, e16Suits);
        // std::copy(e16Suits, e16Suits + 5, fSuitsArr);

    }

    int e17Hand[5] = {cc1[0], cc2[0], cc3[0], suitSplit2[0], cc5[0]};
    int e17Suits[5] = {cc1[1], cc2[1], cc3[1], suitSplit2[1], cc5[1]};
    nRank = makeHand(e17Hand, e17Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e17Hand, e17Hand + 5, fHighCardArr);
        // std::copy(e17Suits, e17Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e17Hand, e17Suits);
        // std::copy(e17Suits, e17Suits + 5, fSuitsArr);
    }

    int e18Hand[5] = {cc1[0], cc2[0], suitSplit2[0], cc4[0], cc5[0]};
    int e18Suits[5] = {cc1[1], cc2[1], suitSplit2[1], cc4[1], cc5[1]};
    nRank = makeHand(e18Hand, e18Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e18Hand, e18Hand + 5, fHighCardArr);
        // std::copy(e18Suits, e18Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e18Hand, e18Suits);
        // std::copy(e18Suits, e18Suits + 5, fSuitsArr);
    }

    int e19Hand[5] = {cc1[0], suitSplit2[0], cc3[0], cc4[0], cc5[0]};
    int e19Suits[5] = {cc1[1], suitSplit2[1], cc3[1], cc4[1], cc5[1]};
    nRank = makeHand(e19Hand, e19Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e19Hand, e19Hand + 5, fHighCardArr);
        // std::copy(e19Suits, e19Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e19Hand, e19Suits);
        // std::copy(e19Suits, e19Suits + 5, fSuitsArr);
    }

    int e20Hand[5] = {suitSplit2[0], cc2[0], cc3[0], cc4[0], cc5[0]};
    int e20Suits[5] = {suitSplit2[1], cc2[1], cc3[1], cc4[1], cc5[1]};
    nRank = makeHand(e20Hand, e20Suits);
    if(nRank < fRank) {
        fRank = nRank;
        std::copy(e20Hand, e20Hand + 5, fHighCardArr);
        // std::copy(e20Suits, e20Suits + 5, fSuitsArr);

    }else if(nRank == fRank){
        fRank = nRank;
        findBest(fRank, fHighCardArr, e20Hand, e20Suits);
    }

    return fRank;
}


int MainWindow::makeHand(int h[5], int s[5])    /// Makes hand rank from hand input
{
   int nakedHand[5] = {h[0], h[1], h[2], h[3], h[4],};
   int nakedSuits[5] = {s[0], s[1], s[2], s[3], s[4],};

   std::sort(nakedHand, nakedHand + 5);

   /// Royal flush
   if(nakedHand[0] == 10 && nakedHand[1] == 11 && nakedHand[2] == 12 && nakedHand[3] == 13 && nakedHand[4] == 14 &&
      nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4]){
       return 1;
   }

   /// Straight flush
   if((nakedHand[0]+1 == nakedHand[1] && nakedHand[1]+1 == nakedHand[2] && nakedHand[2]+1 == nakedHand[3] && nakedHand[3]+1 == nakedHand[4] && nakedHand[0]+4 == nakedHand[4] &&
      nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4]) ||
      (nakedHand[0] == 2 && nakedHand[1] == 3 && nakedHand[2] == 4 && nakedHand[3] == 5 && nakedHand[4] == 14 &&
      nakedSuits[0] == nakedSuits[1] && nakedSuits[0] == nakedSuits[2] && nakedSuits[0] == nakedSuits[3] && nakedSuits[0] == nakedSuits[4])){
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
      (nakedHand[0] == 2 && nakedHand[1] == 3 && nakedHand[2] == 4 && nakedHand[3] == 5 && nakedHand[4] == 14)){
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


void MainWindow::findBest(int r, int fR[5], int h[5], int s[5])     /// Finds best combination on same rank hands
{
    int hand[5] = {h[0], h[1], h[2], h[3], h[4]};
    int swap[5] = {fR[0], fR[1], fR[2], fR[3], fR[4]};
    int suits[5] = {s[0], s[1], s[2], s[3], s[4]};
    int hole[] = {suitSplit1[0], suitSplit2[0]};
    std::sort(hole, hole + 2);
    std::sort(swap, swap + 5);
    std::sort(hand, hand + 5);

    if(r == 6 || r == 2) {  /// If straight or straight flush
        if(hole[0] == swap[4]+1 && hole[1] == swap[4]+2) {
            int temp[5] = {swap[2], swap[3], swap[4], hole[0], hole[1]};
            std::copy(temp, temp + 5, swap);
        }else if (hole[0] == swap[4]+1) {
            int temp[5] = {swap[1], swap[2], swap[3], swap[4], hole[0]};
            std::copy(temp, temp + 5, swap);
        } else if (hole[1] == swap[4]+1) {
            int temp[5] = {swap[1], swap[2], swap[3], swap[4], hole[1]};
            std::copy(temp, temp + 5, swap);
        }

    }else if(r == 4 && hole[0] == hole[1]){ /// If full house
        if(hole[0] > swap[4] && hole[1] > swap[3] && swap[4] != swap[2]){
            int temp[5] = {swap[0], swap[1], swap[2], hole[1], hole[0]};
            std::copy(temp, temp + 5, swap);

    }else if (hole[0] > swap[0] && hole[1] > swap[1] && swap[0] != swap[2]){
            int temp[5] = {hole[0], hole[1], swap[2], swap[3], swap[4]};
            std::copy(temp, temp + 5, swap);
        }

    }else if (r == 10 || r == 9 || r == 8 || r == 7 || r == 5 || r == 4 || r == 3) {    /// If all else
        if(hand[4] >= swap[4] && hand[3] >= swap[3] && hand[2] >= swap[2] && hand[1] >= swap[1] && hand[0] >= swap[0]){
            int temp[5] = {hand[0], hand[1], hand[2], hand[3], hand[4]};
            std::copy(temp, temp + 5, swap);
        }

    }
    std::copy(swap, swap + 5, fHighCardArr);
}


void MainWindow::compareLoop()  /// Compare each players hand against each other and strip lesser hand
{
    compare1_2();
    compare2_1();
    if(p1HighCardArr[4] > p2HighCardArr[4]){
        compare3_1();
        compare1_3();
    }else {
        compare3_2();
        compare2_3();
    }

    if(p1HighCardArr[4] > p3HighCardArr[4]){
        compare1_4();
        compare4_1();
    }else if(p2HighCardArr[4] > p3HighCardArr[4]){
        compare2_4();
        compare4_2();
    }else {
        compare3_4();
        compare4_3();
    }

    if(p1HighCardArr[4] > p4HighCardArr[4]){
        compare1_5();
        compare5_1();
    }else if(p2HighCardArr[4] > p4HighCardArr[4]){
        compare2_5();
        compare5_2();
    }else if(p3HighCardArr[4] > p4HighCardArr[4]){
        compare3_5();
        compare5_3();
    }else {
        compare4_5();
        compare5_4();
    }

    if(p1HighCardArr[4] > p5HighCardArr[4]){
        compare1_6();
        compare6_1();
    }else if(p2HighCardArr[4] > p5HighCardArr[4]){
        compare2_6();
        compare6_2();
    }else if(p3HighCardArr[4] > p5HighCardArr[4]){
        compare3_6();
        compare6_3();
    }else if(p4HighCardArr[4] > p5HighCardArr[4]){
        compare4_6();
        compare6_4();
    }else {
        compare5_6();
        compare6_5();
    }
}
