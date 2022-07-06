#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/// dReam Tables Five Card Draw Poker
#include "iostream"
#include "QMainWindow"
#include "QCryptographicHash"
#include "QThread"
#include "QTimer"
#include "QFont"
#include "QFontDatabase"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static bool clicked;
    static bool startUpSkip;
    static int skipCount;
    void offset();
    void setFonts();
    void buttonDelay();
    void payoutDelay(int seconds);
    void loginInfo();
    void checkBalance(double balance);
    void displayLocalHand(QString hashOne, QString hashTwo, QString hashThree, QString hashFour, QString hashFive);
    void endResults(int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    int playerEntry();
    int playerLeave();
    int dealFiveCardHand();
    int check();
    int bet();
    int drawCards();
    int card(QString hash, QString salt);
    QString findCards(int);
    void displayCardOne(int);
    void displayCardTwo(int);
    void displayCardThree(int);
    void displayCardFour(int);
    void displayCardFive(int);
    void blankDisplay();
    void clearHighlight();
    int winner();
    int autopayWinner(QString whoWon);
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
    void localPlayerControl(int bet, int draw, double wager, double ante, double raised);
    void storedEnd(int end, QString ondId);
    void localEndSignal(QString oneId);
    void disableButtons();
    void foldedBools(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void hasLeft(int p1Out, int p2Out, int p3Out, int p4Out, int p5Out, int p6Out);
    void clearFoldedDisplay(int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);
    void localEnd(QString oneId, int seats, int p1Fold, int p2Fold, int p3Fold, int p4Fold, int p5Fold, int p6Fold);


private slots:
    void buttonCatch();

    void controller();

    void refresh();

    void highlightCards();

    void on_menuButton_clicked();

    void on_dealHandPushButton_clicked();

    void on_drawPushButton_clicked();

    void on_entryPushButton_clicked();

    void on_payoutPushButton_clicked();

    void on_betButton_clicked();

    void on_checkButton_clicked();

    void on_leaveButton_clicked();

    void on_handRankButton_clicked();

private:
    Ui::MainWindow *ui;

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

    int arrSplit[2];
    int suitSplit1[2];
    int suitSplit2[2];
    int suitSplit3[2];
    int suitSplit4[2];
    int suitSplit5[2];
    int p1Rank;
    int p1HighPair = 0;
    int p1HighCardArr[5];
    int p2Rank;
    int p2HighPair = 0;
    int p2HighCardArr[5];
    int p3Rank;
    int p3HighPair = 0;
    int p3HighCardArr[5];
    int p4Rank;
    int p4HighPair = 0;
    int p4HighCardArr[5];
    int p5Rank;
    int p5HighPair = 0;
    int p5HighCardArr[5];
    int p6Rank;
    int p6HighPair = 0;
    int p6HighCardArr[5];
    int getArray(int card);
    int makeHand();
    QString handToText(int rank);

};

#endif // MAINWINDOW_H

