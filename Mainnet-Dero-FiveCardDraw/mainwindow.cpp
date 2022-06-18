/// dReam Tables Five Card Draw Poker
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"
#include "rpc/rpc.h"
#include "handranks.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFonts();
    MainWindow::startUpSkip = true;
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
    ui->logTextBrowser->setText("dReam Tables, Built on Dero\n\nTable v1.0.2");
    MainWindow::skipCount = 0;
    ui->dealHandPushButton->setEnabled(false);
    ui->drawPushButton->setEnabled(false);
    ui->drawComboBox->setEnabled(false);
    ui->betButton->setEnabled(false);
    ui->checkButton->setEnabled(false);
    ui->leaveButton->setEnabled(false);
    ui->payoutPushButton->setEnabled(false);
    ui->winnerComboBox->setEnabled(false);
    clicked = false;
    blankDisplay();

    connect(ui->drawComboBox, SIGNAL(activated(int)),
          this, SLOT(highlightCards()));

}


MainWindow::~MainWindow()
{
    Worker::workThread.quit();
    delete ui;
}


void MainWindow::offset()            /// Offset timer
{
    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::setFonts()
{
    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular23(fontFamily);
    QFont macondoRegular20(fontFamily);
    QFont macondoRegular11(fontFamily);
    macondoRegular23.setPointSize(23);
    macondoRegular20.setPointSize(20);
    macondoRegular11.setPointSize(11);
    macondoRegular23.setBold(true);
    macondoRegular20.setBold(true);
    macondoRegular11.setBold(true);
    ui->logTextBrowser->setFont(macondoRegular23);
    ui->turnReadOut->setFont(macondoRegular20);
    ui->p1CheckBox->setFont(macondoRegular11);
    ui->p2CheckBox->setFont(macondoRegular11);
    ui->p3CheckBox->setFont(macondoRegular11);
    ui->p4CheckBox->setFont(macondoRegular11);
    ui->p5CheckBox->setFont(macondoRegular11);
    ui->p6CheckBox->setFont(macondoRegular11);

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(10);
    ui->groupBoxP1->setFont(ubuntuRegular);
    ui->payoutPushButton->setFont(ubuntuRegular);
    ui->winnerComboBox->setFont(ubuntuRegular);
    ui->balanceDoubleSpinBox->setFont(ubuntuRegular);
    ui->menuButton->setFont(ubuntuRegular);
    ui->leaveButton->setFont(ubuntuRegular);
    ui->entryPushButton->setFont(ubuntuRegular);
    ui->anteIsDSB->setFont(ubuntuRegular);
    ui->dsbPot->setFont(ubuntuRegular);
    ui->dsbSeats->setFont(ubuntuRegular);
    ui->handRankButton->setFont(ubuntuRegular);
}


void MainWindow::refresh()
{
    offset();
    if(clicked == false){
        controller();
    }else {
        MainWindow::skipCount++;
        if(MainWindow::skipCount >= 7){
            clicked = false;
            MainWindow::skipCount = 0;
        }

    }
}


void MainWindow::buttonCatch()
{
    buttonDelay();
    clicked = true;
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
    ui->winnerComboBox->setEnabled(false);
    ui->turnReadOut->setStyleSheet( "QTextBrowser{border-color: rgb(128, 128, 128); border-style: inset; border-width: 2px; border-radius: 6px; padding: 3px; background-color: rgb(85, 88, 93, 90); color: rgb(255, 255, 255);};" );
    ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 2px solid gray; border-radius: 5px; };" );
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
    winner();
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


void MainWindow::highlightCards()
{
    ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 0px; };" );
    ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 0px; };" );

        switch(ui->drawComboBox->currentIndex()){
        case 1: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 2: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 3: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 4: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 5: ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 6: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 7: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 8: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 9: ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 10: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 11: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 12: ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 13: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 14: ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

        case 15: ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );
                 ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 1px solid gray; border-radius: 5px; };" );  break;

    }

}
