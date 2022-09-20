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

#include "viewdeck.h"
#include "ui_viewdeck.h"

ViewDeck::ViewDeck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDeck)
{
    ui->setupUi(this);

    QPalette palette;
    if(Menu::theme.isNull()){
        QPixmap bkgnd(":/images/background.png");
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }else {
        setViewTheme();
    }

    ui->backLabel_1->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_2->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_3->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_4->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_5->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_6->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_7->setPixmap(QPixmap::fromImage(Hand::sharedImage0));
    ui->backLabel_8->setPixmap(QPixmap::fromImage(Hand::sharedImage0));

    ui->cardLabel_1->setPixmap(QPixmap::fromImage(Hand::sharedImage1));
    ui->cardLabel_2->setPixmap(QPixmap::fromImage(Hand::sharedImage2));
    ui->cardLabel_3->setPixmap(QPixmap::fromImage(Hand::sharedImage3));
    ui->cardLabel_4->setPixmap(QPixmap::fromImage(Hand::sharedImage4));
    ui->cardLabel_5->setPixmap(QPixmap::fromImage(Hand::sharedImage5));
    ui->cardLabel_6->setPixmap(QPixmap::fromImage(Hand::sharedImage6));
    ui->cardLabel_7->setPixmap(QPixmap::fromImage(Hand::sharedImage7));
    ui->cardLabel_8->setPixmap(QPixmap::fromImage(Hand::sharedImage8));
    ui->cardLabel_9->setPixmap(QPixmap::fromImage(Hand::sharedImage9));
    ui->cardLabel_10->setPixmap(QPixmap::fromImage(Hand::sharedImage10));
    ui->cardLabel_11->setPixmap(QPixmap::fromImage(Hand::sharedImage11));
    ui->cardLabel_12->setPixmap(QPixmap::fromImage(Hand::sharedImage12));
    ui->cardLabel_13->setPixmap(QPixmap::fromImage(Hand::sharedImage13));
    ui->cardLabel_14->setPixmap(QPixmap::fromImage(Hand::sharedImage14));
    ui->cardLabel_15->setPixmap(QPixmap::fromImage(Hand::sharedImage15));
    ui->cardLabel_16->setPixmap(QPixmap::fromImage(Hand::sharedImage16));
    ui->cardLabel_17->setPixmap(QPixmap::fromImage(Hand::sharedImage17));
    ui->cardLabel_18->setPixmap(QPixmap::fromImage(Hand::sharedImage18));
    ui->cardLabel_19->setPixmap(QPixmap::fromImage(Hand::sharedImage19));
    ui->cardLabel_20->setPixmap(QPixmap::fromImage(Hand::sharedImage20));
    ui->cardLabel_21->setPixmap(QPixmap::fromImage(Hand::sharedImage21));
    ui->cardLabel_22->setPixmap(QPixmap::fromImage(Hand::sharedImage22));
    ui->cardLabel_23->setPixmap(QPixmap::fromImage(Hand::sharedImage23));
    ui->cardLabel_24->setPixmap(QPixmap::fromImage(Hand::sharedImage24));
    ui->cardLabel_25->setPixmap(QPixmap::fromImage(Hand::sharedImage25));
    ui->cardLabel_26->setPixmap(QPixmap::fromImage(Hand::sharedImage26));
    ui->cardLabel_27->setPixmap(QPixmap::fromImage(Hand::sharedImage27));
    ui->cardLabel_28->setPixmap(QPixmap::fromImage(Hand::sharedImage28));
    ui->cardLabel_29->setPixmap(QPixmap::fromImage(Hand::sharedImage29));
    ui->cardLabel_30->setPixmap(QPixmap::fromImage(Hand::sharedImage30));
    ui->cardLabel_31->setPixmap(QPixmap::fromImage(Hand::sharedImage31));
    ui->cardLabel_32->setPixmap(QPixmap::fromImage(Hand::sharedImage32));
    ui->cardLabel_33->setPixmap(QPixmap::fromImage(Hand::sharedImage33));
    ui->cardLabel_34->setPixmap(QPixmap::fromImage(Hand::sharedImage34));
    ui->cardLabel_35->setPixmap(QPixmap::fromImage(Hand::sharedImage35));
    ui->cardLabel_36->setPixmap(QPixmap::fromImage(Hand::sharedImage36));
    ui->cardLabel_37->setPixmap(QPixmap::fromImage(Hand::sharedImage37));
    ui->cardLabel_38->setPixmap(QPixmap::fromImage(Hand::sharedImage38));
    ui->cardLabel_39->setPixmap(QPixmap::fromImage(Hand::sharedImage39));
    ui->cardLabel_40->setPixmap(QPixmap::fromImage(Hand::sharedImage40));
    ui->cardLabel_41->setPixmap(QPixmap::fromImage(Hand::sharedImage41));
    ui->cardLabel_42->setPixmap(QPixmap::fromImage(Hand::sharedImage42));
    ui->cardLabel_43->setPixmap(QPixmap::fromImage(Hand::sharedImage43));
    ui->cardLabel_44->setPixmap(QPixmap::fromImage(Hand::sharedImage44));
    ui->cardLabel_45->setPixmap(QPixmap::fromImage(Hand::sharedImage45));
    ui->cardLabel_46->setPixmap(QPixmap::fromImage(Hand::sharedImage46));
    ui->cardLabel_47->setPixmap(QPixmap::fromImage(Hand::sharedImage47));
    ui->cardLabel_48->setPixmap(QPixmap::fromImage(Hand::sharedImage48));
    ui->cardLabel_49->setPixmap(QPixmap::fromImage(Hand::sharedImage49));
    ui->cardLabel_50->setPixmap(QPixmap::fromImage(Hand::sharedImage50));
    ui->cardLabel_51->setPixmap(QPixmap::fromImage(Hand::sharedImage51));
    ui->cardLabel_52->setPixmap(QPixmap::fromImage(Hand::sharedImage52));
}


ViewDeck::~ViewDeck()
{
    delete ui;
}


void ViewDeck::setViewTheme()
{
    QPalette palette;
    palette.setBrush(QPalette::Window, Menu::theme);
    this->setPalette(palette);
}
