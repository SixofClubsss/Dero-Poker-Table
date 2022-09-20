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
#include "ui_mainwindow.h"
#include "menu.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette;
    if(Menu::theme.isNull()){
        QPixmap bkgnd(":/images/background.png");
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }else {
        setMainTheme();
    }
    setFonts(Menu::os);
    MainWindow::startUpSkip = true;
    createIcons();
    createActions();
    createTrayIcon();
    ui->p1CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p1CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p2CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p2CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p3CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p3CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p4CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p4CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p5CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p5CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->p6CheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->p6CheckBox->setFocusPolicy(Qt::NoFocus);
    ui->logTextBrowser->setText("dReam Tables, Built on Dero\n\nFive Card Table v1.4.0");
    MainWindow::skipCount = 0;
    ui->entryPushButton->setEnabled(false);
    ui->dealHandPushButton->setEnabled(false);
    ui->drawPushButton->setEnabled(false);
    ui->drawComboBox->setEnabled(false);
    ui->betButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->leaveButton->setEnabled(false);
    ui->payoutPushButton->setEnabled(false);
    MainWindow::clicked = false;
    blankDisplay();
    generateKey();
    checkDecks();
}


MainWindow::~MainWindow()
{
    QFile keyFile(".handKey");
    keyFile.open(QIODevice::ReadWrite);

    if(keyFile.exists()) {
        keyFile.remove();
    }

    if(Menu::os == "windows"){
        if(!QDir::setCurrent(QDir::currentPath()+QStringLiteral("/contract"))){
            qInfo() << ("\037[36mCould Not Navigate to /contract\033[0m");
        }else {
            QFile wscriptFile("createTable.cmd");
            wscriptFile.open(QIODevice::ReadWrite);
            if(wscriptFile.exists()){
                wscriptFile.remove();
            }
        }
    }else {
        QFile uscriptFile("contract/createTable.sh");
        uscriptFile.open(QIODevice::ReadWrite);
        if(uscriptFile.exists()){
            uscriptFile.remove();
        }
    }

    qInfo() << ("\033[36m ♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
    qInfo() << ("\033[36m           Exiting...\033[0m");
    qInfo() << ("\033[36m ♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
    delete trayIcon;
    Worker::workThread.quit();
    delete ui;
}


void MainWindow::offset()            /// Offset timer
{
    QTime dieTime = QTime::currentTime().addMSecs(500);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::setMainTheme()
{
    QPalette palette;
    palette.setBrush(QPalette::Window, Menu::theme);
    this->setPalette(palette);
}


void MainWindow::setFonts(QString os)
{  
    int mcR1;
    int mcR2;
    int mcR3;
    int ubR;

    if(os == "macos" || os == "osx" || os == "darwin"){
        mcR1 = 30;
        mcR2 = 24;
        mcR3 = 16;
        ubR = 13;
    }else {
        mcR1 = 24;
        mcR2 = 20;
        mcR3 = 12;
        ubR = 10;
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular1(fontFamily);
    QFont macondoRegular2(fontFamily);
    QFont macondoRegular3(fontFamily);
    macondoRegular1.setPointSize(mcR1);
    macondoRegular2.setPointSize(mcR2);
    macondoRegular3.setPointSize(mcR3);
    ui->logTextBrowser->setFont(macondoRegular1);
    ui->turnReadOut->setFont(macondoRegular2);
    ui->p1CheckBox->setFont(macondoRegular3);
    ui->p2CheckBox->setFont(macondoRegular3);
    ui->p3CheckBox->setFont(macondoRegular3);
    ui->p4CheckBox->setFont(macondoRegular3);
    ui->p5CheckBox->setFont(macondoRegular3);
    ui->p6CheckBox->setFont(macondoRegular3);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(ubR);
    ui->groupBoxP1->setFont(ubuntuRegular);
    ui->playerId->setFont(ubuntuRegular);
    ui->dsbTurn->setFont(ubuntuRegular);
    ui->dsbDealer->setFont(ubuntuRegular);
    ui->betSpinBox->setFont(ubuntuRegular);
    ui->checkButton->setFont(ubuntuRegular);
    ui->betButton->setFont(ubuntuRegular);
    ui->dealHandPushButton->setFont(ubuntuRegular);
    ui->drawPushButton->setFont(ubuntuRegular);
    ui->drawComboBox->setFont(ubuntuRegular);
    ui->payoutPushButton->setFont(ubuntuRegular);
    ui->balanceDoubleSpinBox->setFont(ubuntuRegular);
    ui->menuButton->setFont(ubuntuRegular);
    ui->leaveButton->setFont(ubuntuRegular);
    ui->entryPushButton->setFont(ubuntuRegular);
    ui->anteIsDSB->setFont(ubuntuRegular);
    ui->dsbPot->setFont(ubuntuRegular);
    ui->dsbSeats->setFont(ubuntuRegular);
    ui->handRankButton->setFont(ubuntuRegular);
    ui->dsbBlockHeight->setFont(ubuntuRegular);
    ui->txLogTextBrowser->setFont(ubuntuRegular);
    ui->backComboBox->setFont(ubuntuRegular);
    ui->deckComboBox->setFont(ubuntuRegular);
    ui->deckButton->setFont(ubuntuRegular);
}


void MainWindow::checkDecks()
{
    qInfo() << ("\033[36m ♤♡♧♢♧♡♤ Looking for NFA ♤♡♧♢♧♡♤\033[0m");
    rpc r;
    QString pre = QDir().absolutePath();
    AZYPC(pre, r);
    AZYPCB(pre, r);
    SIXPC(pre, r);
    SIXPCB(pre, r);
    qInfo() << ("\033[36m ♤♡♧♢♧♡♤ Starting  Table ♤♡♧♢♧♡♤\033[0m");
}


void MainWindow::refresh()      /// Controller refresh rate
{

    if((rpc::turn != ui->playerId->value()-1 && rpc::blockHeight > rpc::clickedHeight+1 && ui->playerId->value() != 0) ||
            (rpc::turn == ui->playerId->value()-1 && rpc::blockHeight > rpc::clickedHeight+3)){
        MainWindow::clicked = false;
    }

    if(Menu::themeChanged == true){
        setMainTheme();
        Menu::themeChanged = false;
    }

    ui->dsbBlockHeight->setValue(rpc::blockHeight);
    offset();
    if(MainWindow::clicked == false){
        controller();
        MainWindow::skipCount = 0;
    }else {
        MainWindow::skipCount++;
        if(MainWindow::skipCount >= 8){
            MainWindow::clicked = false;
            MainWindow::skipCount = 0;
        }
    }
}


void MainWindow::buttonCatch()  /// When player confirms a action
{
    buttonDelay();
    MainWindow::clicked = true;
    rpc::clickedHeight = ui->dsbBlockHeight->value();
}


void MainWindow::buttonDelay()  /// When any button has been pressed disabled all button for buffer period
{
    ui->entryPushButton->setEnabled(false);
    ui->leaveButton->setEnabled(false);
    ui->dealHandPushButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->betButton->setEnabled(false);
    ui->drawPushButton->setEnabled(false);
    ui->drawComboBox->setEnabled(false);
    ui->payoutPushButton->setEnabled(false);
    ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; background-color: rgba(85, 88, 93, 90); color: rgb(255, 255, 255);};" );
    ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 3px solid gray; border-radius: 60px; background-color: rgba(0, 0, 0, 150);};" );
    ui->turnReadOut->setText("Wait For Block");
}


void MainWindow::on_menuButton_clicked()
{
    Menu m;
    m.setModal(true);
    m.exec();
}


void MainWindow::on_dealHandPushButton_clicked()
{
    buttonCatch();
    dealFiveCardHand();
}


void MainWindow::on_drawPushButton_clicked()
{
    buttonCatch();
    Hand::hasBet = false;
    drawCards();
}


void MainWindow::on_entryPushButton_clicked()
{
    buttonCatch();
    playerEntry();
}


void MainWindow::on_payoutPushButton_clicked()
{
    buttonCatch();
    Hand::endSignal = false;
    if(Hand::push == true){
        splitWinner(rpc::p1Fold, rpc::p2Fold, rpc::p3Fold, rpc::p4Fold, rpc::p5Fold, rpc::p6Fold);
    }else {
        payWinner();
    }
}


void MainWindow::on_betButton_clicked()
{
    buttonCatch();
    bet();
}


void MainWindow::on_checkButton_clicked()
{
    buttonCatch();
    check();
}


void MainWindow::on_leaveButton_clicked()
{
    buttonCatch();
    playerLeave();
}


void MainWindow::on_handRankButton_clicked()
{
    HandRanks hr;
    hr.setModal(false);
    hr.exec();

}


void MainWindow::clearHighlight()
{
    ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard1->setGeometry(10, 12, 150, 209);
    ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard2->setGeometry(80, 12, 150, 209);
    ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard3->setGeometry(160, 12, 150, 209);
    ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard4->setGeometry(250, 12, 150, 209);
    ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard5->setGeometry(340, 12, 150, 209);

}


void MainWindow::highlightCards()
{
    clearHighlight();

    if(rpc::draw == 1 && Hand::endSignal == false){
        if(ui->deckComboBox->currentIndex() > 1){
            switch(ui->drawComboBox->currentIndex()){
            case 1: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                break;

            case 2: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                break;

            case 3: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 4: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 5: ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 6: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                break;

            case 7: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 8: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 9: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 10: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 11: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 12: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 13: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 14: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 15: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 2px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;
            }
        }else {
            switch(ui->drawComboBox->currentIndex()){
            case 1: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                break;

            case 2: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                break;

            case 3: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 4: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 5: ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 6: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                break;

            case 7: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 8: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 9: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                    ui->localPlayerCard1->setGeometry(10, 5, 150, 209);
                    ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 10: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                break;

            case 11: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 12: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard2->setGeometry(80, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 13: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                break;

            case 14: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard3->setGeometry(160, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;

            case 15: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                     ui->localPlayerCard4->setGeometry(250, 5, 150, 209);
                     ui->localPlayerCard5->setGeometry(340, 5, 150, 209);
                break;
            }

        }

    }

}


void MainWindow::manualReveal()
{
    revealKey();
}


void MainWindow::createActions()    /// Tray actions
{
    connect(ui->drawComboBox, SIGNAL(activated(int)),this, SLOT(highlightCards()));
    connect(this, SIGNAL(turnSignal()), this, SLOT(turnNotify()));
    connect(this, SIGNAL(revealSignal()), this, SLOT(revealNotify()));

    minimizeAction = new QAction(tr("&Hide"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

    maximizeAction = new QAction(tr("&Show"), this);
    connect(maximizeAction, SIGNAL(triggered()), this, SLOT(show()));

    revealAction = new QAction(tr("&Reveal Key"), this);
    connect(revealAction, SIGNAL(triggered()), this, SLOT(manualReveal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void MainWindow::createIcons()  /// Tray icon images
{
    QPixmap tPixmap(32,32);
    tPixmap.load(":/images/dReamTablesIcon.png");
    MainWindow::tIcon = tPixmap;

    QPixmap bPixmap(32,32);
    bPixmap.load(":/images/dReamTablesBIcon.png");
    MainWindow::bIcon = bPixmap;
}


void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(maximizeAction);
    trayIconMenu->addAction(revealAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(tIcon);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setVisible(true);
}


void MainWindow::turnNotify()
{
    if(MainWindow::notified == false){
        trayIcon->showMessage("Five Card Draw", "Your Turn", bIcon, 7500);
        MainWindow::notified = true;
    }
}


void MainWindow::revealNotify()
{
    if(MainWindow::notified == false){
        trayIcon->showMessage("Five Card Draw", "Revealing hand key", bIcon, 7500);
        MainWindow::notified = true;
    }
}


void MainWindow::on_deckComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 != "Light" && arg1 != "Dark"){
        QString collec = arg1;
        collec.chop(4);
        if(collec == "AZYPC"){
            MainWindow::faceUrl = "https://raw.githubusercontent.com/Azylem/"+arg1+"/main/"+arg1+"/";
        }else if (collec == "SIXPC"){
            MainWindow::faceUrl = "https://raw.githubusercontent.com/SixofClubsss/"+arg1+"/main/"+arg1+"/";
        }
    }
}


void MainWindow::on_backComboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 != "Light" && arg1 != "Dark"){
        QString collec = arg1;
        collec.chop(4);
        if(collec == "AZYPCB"){
            MainWindow::backUrl = "https://raw.githubusercontent.com/Azylem/"+arg1+"/main/"+arg1+".png";
        }else if (collec == "SIXPCB"){
            MainWindow::backUrl = "https://raw.githubusercontent.com/SixofClubsss/"+arg1+"/main/"+arg1+".png";
        }
    }
}


void MainWindow::on_deckButton_clicked()
{
    ViewDeck vd;
    vd.setModal(true);
    vd.exec();
}
