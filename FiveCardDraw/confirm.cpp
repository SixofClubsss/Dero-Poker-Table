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
#include "confirm.h"
#include "ui_confirm.h"


bool Confirm::actionConfirmed;
int Confirm::whichText;


Confirm::Confirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Confirm)
{
    ui->setupUi(this);
    setFonts();

    if(Confirm::whichText == 1){           /// Confirm menu will look at which button was clicked
        getTableText();

    }else if(Confirm::whichText == 2){
        newTableText();

    }else if(Confirm::whichText == 3){
        listTableText();

    }else if(Confirm::whichText == 4){
        delistTableText();

    }else if(Confirm::whichText == 5){
        forceStartText();
    }

}

Confirm::~Confirm()
{
    delete ui;
}

void Confirm::setFonts()
{

    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont ubuntuRegular12(fontFamily1);
    ubuntuRegular12.setPointSize(12);
    ui->confirmTextBrowser->setFont(ubuntuRegular12);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(10);
    ui->buttonBox->setFont(ubuntuRegular);
}


void Confirm::on_buttonBox_accepted()
{
    Confirm::actionConfirmed = true;
}


void Confirm::getTableText()   /// Readout for Get table
{
    ui->confirmTextBrowser->setText("This unlocks the smart contract, automatically set up your first table and send you 33 dReams.\n\nTo help support the project, we have attached a 1 Dero donation to preform this first auto upload.\n\n"
                                    "Once the contract is unlocked you can generate as many new tables as you'd like for public/private games using the 'New Table' button inside the owner control box.\n\nYour new table ID will be saved in Tables.txt"
                                    "\n\nClick Ok to confirm");
}


void Confirm::newTableText()   /// Read out for New Table
{
    ui->confirmTextBrowser->setText("This will create a new table contract ID\n\nEnsure you have any previous table contract IDs backed up\n\n"
                                    "Your new table ID will be saved in Tables.txt\n\n\nClick Ok to confirm");
}


void Confirm::listTableText()   /// Read out for List Table
{
    ui->confirmTextBrowser->setText("This will list the current table address for public sit & go play.\n\nBe aware anyone can join the table if the address is listed. If you'd like your table to remain private, or you are not the owner of the table DO NOT LIST. "
                                    "Remember to remove your listing when you close the table.\n\n0.1 Dero listing fee, you can remove your listing at any time.\n\nClick Ok to confirm");
}


void Confirm::delistTableText()   /// Read out for remove listing
{
    ui->confirmTextBrowser->setText("Remove your table listing.\n\n\nClick Ok to confirm");
}


void Confirm::forceStartText()   /// Read out for remove listing
{
    ui->confirmTextBrowser->setText("Start game with empty seats?\n\n\nClick Ok to confirm");
}

