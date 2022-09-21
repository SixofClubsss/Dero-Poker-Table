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

#include "mainwindow.h"
#include "rpc/rpc.h"
#include "aes/qaesencryption.h"
#include "shared/filedownloader.h"
#include "QDialog"
#include "QFile"
#include "QImage"
#include "QDir"


namespace Ui { class Menu; }

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    FileDownloader *tImgCtrl;
    static QImage theme;
    static QString os;
    static QString userInfo;
    static QString passInfo;
    static QString contractAddress;
    static QString listingAddress;
    static QString donationAddress;
    static int themeIndex;
    static bool loading;
    static bool themeChanged;
    static bool daemonConnected;
    static bool walletConnected;
    static bool mainnet;
    static bool dReams;
    static bool autoPayout;
    static bool sharedDeck;
    void AZYDS(QString, rpc&);
    void setFonts(QString);
    void checkThemes();
    void setMenuTheme();
    void loginInfo();
    void delay();
    void loadDelay(int);
    void unlockTable();
    void unixUpload(bool);
    void windowsUpload(bool);
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
    int ownerShare();


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

    void on_sharedRButton_clicked();

    void loadThemeImage();

    void on_themeComboBox_currentTextChanged(const QString &arg1);

    void on_myTablesButton_clicked();

    void loadSharedImage0();
    void loadSharedImage1();
    void loadSharedImage2();
    void loadSharedImage3();
    void loadSharedImage4();
    void loadSharedImage5();
    void loadSharedImage6();
    void loadSharedImage7();
    void loadSharedImage8();
    void loadSharedImage9();
    void loadSharedImage10();
    void loadSharedImage11();
    void loadSharedImage12();
    void loadSharedImage13();
    void loadSharedImage14();
    void loadSharedImage15();
    void loadSharedImage16();
    void loadSharedImage17();
    void loadSharedImage18();
    void loadSharedImage19();
    void loadSharedImage20();
    void loadSharedImage21();
    void loadSharedImage22();
    void loadSharedImage23();
    void loadSharedImage24();
    void loadSharedImage25();
    void loadSharedImage26();
    void loadSharedImage27();
    void loadSharedImage28();
    void loadSharedImage29();
    void loadSharedImage30();
    void loadSharedImage31();
    void loadSharedImage32();
    void loadSharedImage33();
    void loadSharedImage34();
    void loadSharedImage35();
    void loadSharedImage36();
    void loadSharedImage37();
    void loadSharedImage38();
    void loadSharedImage39();
    void loadSharedImage40();
    void loadSharedImage41();
    void loadSharedImage42();
    void loadSharedImage43();
    void loadSharedImage44();
    void loadSharedImage45();
    void loadSharedImage46();
    void loadSharedImage47();
    void loadSharedImage48();
    void loadSharedImage49();
    void loadSharedImage50();
    void loadSharedImage51();
    void loadSharedImage52();

private:
    Ui::Menu *ui;

    void loadFullDeck();

    FileDownloader *s0_ImgCtrl;
    FileDownloader *s1_ImgCtrl;
    FileDownloader *s2_ImgCtrl;
    FileDownloader *s3_ImgCtrl;
    FileDownloader *s4_ImgCtrl;
    FileDownloader *s5_ImgCtrl;
    FileDownloader *s6_ImgCtrl;
    FileDownloader *s7_ImgCtrl;
    FileDownloader *s8_ImgCtrl;
    FileDownloader *s9_ImgCtrl;
    FileDownloader *s10_ImgCtrl;
    FileDownloader *s11_ImgCtrl;
    FileDownloader *s12_ImgCtrl;
    FileDownloader *s13_ImgCtrl;
    FileDownloader *s14_ImgCtrl;
    FileDownloader *s15_ImgCtrl;
    FileDownloader *s16_ImgCtrl;
    FileDownloader *s17_ImgCtrl;
    FileDownloader *s18_ImgCtrl;
    FileDownloader *s19_ImgCtrl;
    FileDownloader *s20_ImgCtrl;
    FileDownloader *s21_ImgCtrl;
    FileDownloader *s22_ImgCtrl;
    FileDownloader *s23_ImgCtrl;
    FileDownloader *s24_ImgCtrl;
    FileDownloader *s25_ImgCtrl;
    FileDownloader *s26_ImgCtrl;
    FileDownloader *s27_ImgCtrl;
    FileDownloader *s28_ImgCtrl;
    FileDownloader *s29_ImgCtrl;
    FileDownloader *s30_ImgCtrl;
    FileDownloader *s31_ImgCtrl;
    FileDownloader *s32_ImgCtrl;
    FileDownloader *s33_ImgCtrl;
    FileDownloader *s34_ImgCtrl;
    FileDownloader *s35_ImgCtrl;
    FileDownloader *s36_ImgCtrl;
    FileDownloader *s37_ImgCtrl;
    FileDownloader *s38_ImgCtrl;
    FileDownloader *s39_ImgCtrl;
    FileDownloader *s40_ImgCtrl;
    FileDownloader *s41_ImgCtrl;
    FileDownloader *s42_ImgCtrl;
    FileDownloader *s43_ImgCtrl;
    FileDownloader *s44_ImgCtrl;
    FileDownloader *s45_ImgCtrl;
    FileDownloader *s46_ImgCtrl;
    FileDownloader *s47_ImgCtrl;
    FileDownloader *s48_ImgCtrl;
    FileDownloader *s49_ImgCtrl;
    FileDownloader *s50_ImgCtrl;
    FileDownloader *s51_ImgCtrl;
    FileDownloader *s52_ImgCtrl;

    QUrl loadSharedCard(int);
    void loadShared0(QUrl);
    void loadShared1(QUrl);
    void loadShared2(QUrl);
    void loadShared3(QUrl);
    void loadShared4(QUrl);
    void loadShared5(QUrl);
    void loadShared6(QUrl);
    void loadShared7(QUrl);
    void loadShared8(QUrl);
    void loadShared9(QUrl);
    void loadShared10(QUrl);
    void loadShared11(QUrl);
    void loadShared12(QUrl);
    void loadShared13(QUrl);
    void loadShared14(QUrl);
    void loadShared15(QUrl);
    void loadShared16(QUrl);
    void loadShared17(QUrl);
    void loadShared18(QUrl);
    void loadShared19(QUrl);
    void loadShared20(QUrl);
    void loadShared21(QUrl);
    void loadShared22(QUrl);
    void loadShared23(QUrl);
    void loadShared24(QUrl);
    void loadShared25(QUrl);
    void loadShared26(QUrl);
    void loadShared27(QUrl);
    void loadShared28(QUrl);
    void loadShared29(QUrl);
    void loadShared30(QUrl);
    void loadShared31(QUrl);
    void loadShared32(QUrl);
    void loadShared33(QUrl);
    void loadShared34(QUrl);
    void loadShared35(QUrl);
    void loadShared36(QUrl);
    void loadShared37(QUrl);
    void loadShared38(QUrl);
    void loadShared39(QUrl);
    void loadShared40(QUrl);
    void loadShared41(QUrl);
    void loadShared42(QUrl);
    void loadShared43(QUrl);
    void loadShared44(QUrl);
    void loadShared45(QUrl);
    void loadShared46(QUrl);
    void loadShared47(QUrl);
    void loadShared48(QUrl);
    void loadShared49(QUrl);
    void loadShared50(QUrl);
    void loadShared51(QUrl);
    void loadShared52(QUrl);

};

#endif // MENU_H
