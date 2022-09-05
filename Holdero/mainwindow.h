#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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

#include "iostream"
#include "QMainWindow"
#include "QCryptographicHash"
#include "QThread"
#include "QTimer"
#include "QFont"
#include "QFontDatabase"
#include "QImageReader"
#include "QAction"
#include "QMenu"
#include "QSystemTrayIcon"
#include "rpc/rpc.h"
#include "shared/filedownloader.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QIcon tIcon;
    QIcon bIcon;
    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;
    FileDownloader *b_ImgCtrl;
    FileDownloader *c1_ImgCtrl;
    FileDownloader *c2_ImgCtrl;
    FileDownloader *c3_ImgCtrl;
    FileDownloader *c4_ImgCtrl;
    FileDownloader *c5_ImgCtrl;
    FileDownloader *c6_ImgCtrl;
    FileDownloader *c7_ImgCtrl;
    static QString faceUrl;
    static QString backUrl;
    static bool notified;
    static bool emptyBool;
    static bool shared0;
    static bool shared1;
    static bool shared2;
    static bool shared3;
    static bool shared4;
    static bool shared5;
    static bool shared6;
    static bool shared7;
    static bool clicked;
    static bool startUpSkip;
    static bool displayedRes;
    static int skipCount;
    void offset();
    void setFonts(QString);
    void checkDecks();
    void AZYPC(QString, rpc&);
    void AZYPCB(QString, rpc&);
    void SIXPC(QString, rpc&);
    void SIXPCB(QString, rpc&);
    void buttonDelay();
    void payoutDelay(int seconds);
    void loginInfo();
    void checkBalance(double balance);
    void displayLocalHand(QString hashOne, QString hashTwo);
    void endResults(int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void generateKey();
    int playerEntry();
    int playerLeave();
    int dealHand();
    int check();
    int bet();
    int card(QString hash);
    int keyCard(QString hash, int);
    QString readmeStandard(QString);
    QString hasDisplay(int);
    QString thisHandIs(int);
    QString findCards(int);
    QString deckSelect(int);
    QString backSelect(int);
    QImage displayCustom(int);
    QString displayStandard(int);
    void displayFlop(int, int, int);
    void displayTurnCard(int);
    void displayRiverCard(int);
    void blankDisplay();
    int winner();
    int autopayWinner(QString whoWon);
    int splitWinner(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    int revealKey();
    void setOpenClosed(int seats, double ante, double dealer);
    void setPlayerStatus(int p1Out, QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId);
    void highlightWhosTurn(int turn, int seats);
    void isClosed(int seats, int full);
    void setPlayerId(QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId);
    void potEmpty(double pot);
    void setMinBet(double wager, double raised);
    void atTable();
    void ownerAtTable(int p1Out, QString oneId);
    void isTableFull(double seats, double pot, double turn);
    void localPlayerControl(int bet, double wager, double ante, double raised);
    void storedEnd(int end, QString ondId);
    void localEndSignal(QString oneId);
    void disableButtons();
    void foldedBools(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void hasLeft(int p1Out, int p2Out, int p3Out, int p4Out, int p5Out, int p6Out);
    void clearFoldedDisplay(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void localEnd(QString oneId, int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void displayShared(int, int);


signals:
    void turnSignal();

    void revealSignal();


private slots:
    void setMainTheme();

    void buttonCatch();

    void controller();

    void refresh();

    void on_menuButton_clicked();

    void on_dealHandPushButton_clicked();

    void on_entryPushButton_clicked();

    void on_payoutPushButton_clicked();

    void on_betButton_clicked();

    void on_checkButton_clicked();

    void on_leaveButton_clicked();

    void on_handRankButton_clicked();

    void loadBackImage();

    void loadCardImage1();

    void loadCardImage2();

    void loadCardImage3();

    void loadCardImage4();

    void loadCardImage5();

    void loadCardImage6();

    void loadCardImage7();

    void revealNotify();

    void turnNotify();

    void manualReveal();

    void on_deckComboBox_currentTextChanged(const QString &arg1);

    void on_backComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QAction *minimizeAction;
    QAction *maximizeAction;
    QAction *revealAction;
    QAction *quitAction;

    void createIcons();
    void createActions();
    void createTrayIcon();
    void findBest(int r, int fR[], int h[]);
    void compareLoop();
    void getCommunity();
    int compareThese();
    int getPlayer1();
    int getPlayer2();
    int getPlayer3();
    int getPlayer4();
    int getPlayer5();
    int getPlayer6();
    void compare1_2();
    void compare1_3();
    void compare1_4();
    void compare1_5();
    void compare1_6();
    void compare2_1();
    void compare2_3();
    void compare2_4();
    void compare2_5();
    void compare2_6();
    void compare3_1();
    void compare3_2();
    void compare3_4();
    void compare3_5();
    void compare3_6();
    void compare4_1();
    void compare4_2();
    void compare4_3();
    void compare4_5();
    void compare4_6();
    void compare5_1();
    void compare5_2();
    void compare5_3();
    void compare5_4();
    void compare5_6();
    void compare6_1();
    void compare6_2();
    void compare6_3();
    void compare6_4();
    void compare6_5();
    void less6();
    void less5();
    void less4();
    void less3();
    void less2();
    void less1();
    void pEndTextLine(QString t, QString h1, QString h2, int p, int r);

    int cc1[2];
    int cc2[2];
    int cc3[2];
    int cc4[2];
    int cc5[2];
    int fHighCardArr[5];
    int fSuitsArr[5];
    int fDisplay[5];
    int communityCard[5];
    int arrSplit[2];
    int suitSplit1[2];
    int suitSplit2[2];
    int suitSplit3[2];
    int suitSplit4[2];
    int suitSplit5[2];
    int p1Rank;
    int p1HighPair = 0;
    int p1HighTrip = 0;
    int p1HighCardArr[5];
    int p1SuitsArr[5];
    int p1Display[5];
    int p2Rank;
    int p2HighPair = 0;
    int p2HighTrip = 0;
    int p2HighCardArr[5];
    int p2SuitsArr[5];
    int p2Display[5];
    int p3Rank;
    int p3HighPair = 0;
    int p3HighTrip = 0;
    int p3HighCardArr[5];
    int p3SuitsArr[5];
    int p3Display[5];
    int p4Rank;
    int p4HighPair = 0;
    int p4HighTrip = 0;
    int p4HighCardArr[5];
    int p4SuitsArr[5];
    int p4Display[5];
    int p5Rank;
    int p5HighPair = 0;
    int p5HighTrip = 0;
    int p5HighCardArr[5];
    int p5SuitsArr[5];
    int p5Display[5];
    int p6Rank;
    int p6HighPair = 0;
    int p6HighTrip = 0;
    int p6HighCardArr[5];
    int p6SuitsArr[5];
    int p6Display[5];
    int getArray(int card);
    int getHighPair(int h[5]);
    int getHighTrip(int h[5]);
    int makeHand(int h[], int s[]);
    QString handToText(int rank);

};

#endif // MAINWINDOW_H
