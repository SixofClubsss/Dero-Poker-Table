#ifndef HANDRANKS_H
#define HANDRANKS_H
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

#include "QDialog"
#include "menu.h"


namespace Ui {
class HandRanks;
}

class HandRanks : public QDialog
{
    Q_OBJECT

public:
    explicit HandRanks(QWidget *parent = nullptr);
    ~HandRanks();
    void setRanksTheme();
    void setFonts(QString);

private:
    Ui::HandRanks *ui;
};


class Hand
{
public:
    static bool hasBet;
    static bool endSignal;
    static bool foldOne;
    static bool foldTwo;
    static bool foldThree;
    static bool foldFour;
    static bool foldFive;
    static bool foldSix;
    static bool keyIsPub;
    static bool push;

    static QImage sharedImage0;
    static QImage sharedImage1;
    static QImage sharedImage2;
    static QImage sharedImage3;
    static QImage sharedImage4;
    static QImage sharedImage5;
    static QImage sharedImage6;
    static QImage sharedImage7;
    static QImage sharedImage8;
    static QImage sharedImage9;
    static QImage sharedImage10;
    static QImage sharedImage11;
    static QImage sharedImage12;
    static QImage sharedImage13;
    static QImage sharedImage14;
    static QImage sharedImage15;
    static QImage sharedImage16;
    static QImage sharedImage17;
    static QImage sharedImage18;
    static QImage sharedImage19;
    static QImage sharedImage20;
    static QImage sharedImage21;
    static QImage sharedImage22;
    static QImage sharedImage23;
    static QImage sharedImage24;
    static QImage sharedImage25;
    static QImage sharedImage26;
    static QImage sharedImage27;
    static QImage sharedImage28;
    static QImage sharedImage29;
    static QImage sharedImage30;
    static QImage sharedImage31;
    static QImage sharedImage32;
    static QImage sharedImage33;
    static QImage sharedImage34;
    static QImage sharedImage35;
    static QImage sharedImage36;
    static QImage sharedImage37;
    static QImage sharedImage38;
    static QImage sharedImage39;
    static QImage sharedImage40;
    static QImage sharedImage41;
    static QImage sharedImage42;
    static QImage sharedImage43;
    static QImage sharedImage44;
    static QImage sharedImage45;
    static QImage sharedImage46;
    static QImage sharedImage47;
    static QImage sharedImage48;
    static QImage sharedImage49;
    static QImage sharedImage50;
    static QImage sharedImage51;
    static QImage sharedImage52;

};

#endif // HANDRANKS_H
