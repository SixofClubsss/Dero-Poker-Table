#ifndef HANDRANKS_H
#define HANDRANKS_H
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

#include "QDialog"
#include "algorithm"
#include "array"


namespace Ui {
class HandRanks;
}

class HandRanks : public QDialog
{
    Q_OBJECT

public:
    explicit HandRanks(QWidget *parent = nullptr);
    ~HandRanks();
     void setFonts();

private:
    Ui::HandRanks *ui;
};


class Hand
{
public:
    static bool hasBet;
    static bool called;
    static bool endSignal;
    static bool foldOne;
    static bool foldTwo;
    static bool foldThree;
    static bool foldFour;
    static bool foldFive;
    static bool foldSix;
    static bool keyIsPub;

};

#endif // HANDRANKS_H
