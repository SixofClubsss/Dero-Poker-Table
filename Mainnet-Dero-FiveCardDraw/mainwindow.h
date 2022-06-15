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
    bool clicked;
    static bool startUpSkip;
    static int skipCount;
    void offset();
    void setFonts();
    void buttonDelay();
    void payoutDelay();
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
    int winner();
    int allFoldedWinner(QString whoWon);
    void setOpenClosed(int seats, double ante, double dealer);
    void setPlayerStatus(int p1Out, QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId);
    void highlightWhosTurn(int turn, int seats);
    void isClosed(int seats);
    void setPlayerId(QString oneId, QString twoId, QString threeId, QString fourId, QString fiveId, QString sixId);
    void potEmpty(double pot);
    void setMinBet(double wager, double raised);
    void atTable();
    void ownerAtTable(int p1Out);
    void isTableFull(double seats, double pot, double turn);
    void localPlayerControl(int bet, int draw, double wager, double ante, double raised);
    void storedEnd(int end);
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

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

