#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QMainWindow"
#include "iostream"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loginInfo();
    void delay();
    int fetchScData(void);
    int fetchHandData(void);
    int fetchResultsData(void);
    int checkDaemon(void);
    int checkWallet(void);
    int setTable(void);
    int playerEntry(void);
    void showGameKey();
    void verifyGameKey();
    int dealFiveCardHand(void);
    int check(void);
    int bet(void);
    int drawCards(void);
    QString findCards(int);
    void displayCardOne(int);
    void displayCardTwo(int);
    void displayCardThree(int);
    void displayCardFour(int);
    void displayCardFive(int);
    void blankDisplay();
    int winner(void);
    int shuffleDeck(void);


private slots:

    void refresh();

    void on_daemonRPCbutton_clicked(bool checked);

    void on_walletRPCbutton_clicked(bool checked);

    void on_helpButton_clicked();

    void on_gameKeyPushButton_clicked();

    void on_dealHandPushButton_clicked();

    void on_ownerPushButton_clicked();

    void on_drawPushButton_clicked();

    void on_entryPushButton_clicked();

    void on_payoutPushButton_clicked();

    void on_betButton_clicked();

    void on_checkButton_clicked();

    void on_shuffleButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
