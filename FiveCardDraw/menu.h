#ifndef MENU_H
#define MENU_H
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

#include "rpc/rpc.h"
#include "aes/qaesencryption.h"
#include "QDialog"
#include "QFile"


namespace Ui { class Menu; }

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    static QString userInfo;
    static QString passInfo;
    static QString contractAddress;
    static QString listingAddress;
    static QString donationAddress;
    static bool daemonConnected;
    static bool walletConnected;
    static bool mainnet;
    static bool dReams;
    static bool autoPayout;
    void setFonts();
    void loginInfo();
    void delay();
    void unlockTable();
    int getDreams();
    int checkDaemon();
    int checkWallet();
    int checkContract();
    int checkAddress();
    int fetchInfo();
    int setTable();
    int cleanTable();
    int fetchListingScData();
    int checkIfListed();
    int listTable();
    int delistTable();
    int forceStart();


private slots:
    void daemonToggle();

    void walletToggle();

    void contractToggle();

    void confirmationBox();

    void on_contractButton_clicked();

    void on_daemonRPCbutton_clicked();

    void on_walletRPCbutton_clicked();

    void on_setTableButton_clicked();

    void on_cleanTableButton_clicked();

    void on_getTableButton_clicked();

    void on_newTableButton_clicked();

    void on_listTableButton_clicked();

    void on_delistTableButton_clicked();

    void on_findTablesButton_clicked();

    void on_autoPayRButton_clicked();

    void on_forceButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
