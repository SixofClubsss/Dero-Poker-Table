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
#include "menu.h"
#include "ui_menu.h"
#include "rpc/rpc.h"

QImage Menu::theme;
QString Menu::os;
QString Menu::userInfo;
QString Menu::passInfo;
QString Menu::contractAddress;
QString Menu::listingAddress;
QString Menu::donationAddress;
int Menu::themeIndex;
bool Menu::loading;
bool Menu::mainnet;
bool Menu::autoPayout;
bool Menu::sharedDeck;
bool Menu::themeChanged;


Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    Menu::os = QSysInfo::productType();
    QPalette palette;
    if(Menu::theme.isNull()){
        QPixmap bkgnd(":/images/background.png");
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }else {
        setMenuTheme();
    }

    setFonts(Menu::os);
    ui->contractCheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->contractCheckBox->setFocusPolicy(Qt::NoFocus);
    ui->daemonConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->daemonConnectedBox->setFocusPolicy(Qt::NoFocus);
    ui->walletConnectedBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->walletConnectedBox->setFocusPolicy(Qt::NoFocus);
    rpc::IdHash = "null";
    Menu::listingAddress = "f5d17b7b867105c0b47d68149d57f426a97d3e29bbb23bcabddfdee210859e93";
    Menu::donationAddress = "dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn";
    ui->autoPayRButton->setEnabled(false);
    ui->listTableButton->setEnabled(false);
    ui->delistTableButton->setEnabled(false);
    ui->getTableButton->setEnabled(false);
    ui->findTablesButton->setEnabled(false);
    ui->ownerGroupBox->setEnabled(false);
    ui->daemonRPCinput->setText(rpc::daemonAddress);
    ui->walletRPCinput->setText(rpc::playerAddress);
    ui->contractLineEdit->setText(Menu::contractAddress);
    for (int i = 0; i < 9; i++) {
        ui->daemonRPCinput->backspace();
        ui->walletRPCinput->backspace();
    }
    ui->userpassInput->setText(Menu::userInfo);

    if(Menu::autoPayout == true){
        ui->autoPayRButton->setChecked(true);
    }

    if(Menu::sharedDeck == true){
        ui->sharedRButton->setChecked(true);
    }

    connect(ui->daemonRPCinput, SIGNAL(textChanged(QString)),
          this, SLOT(daemonToggle()));

    connect(ui->walletRPCinput, SIGNAL(textChanged(QString)),
          this, SLOT(walletToggle()));

    connect(ui->userpassInput, SIGNAL(textChanged(QString)),
          this, SLOT(walletToggle()));

    connect(ui->contractLineEdit, SIGNAL(textChanged(QString)),
          this, SLOT(contractToggle()));

    if(rpc::inGame == true){
        checkDaemon();
        checkAddress();
        checkWallet();
        checkContract();
        checkIfListed();
    }

    qInfo() << ("\033[36m ♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
    qInfo() << ("\033[36mdReam Tables Five Card Draw Poker\033[0m");
    qInfo() << ("\033[36m   https://dreamtables.net\033[0m");
    qInfo() << ("\033[36m     © 2022 dReam Tables\033[0m");
    qInfo() << ("\033[36m ♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
}


Menu::~Menu()
{
    if(Menu::loading == true){
        QTime dieTime = QTime::currentTime().addSecs(6);
        while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    delete ui;
}


void Menu::daemonToggle()
{
    rpc::daemonAddress =  ui->daemonRPCinput->text();
    ui->daemonConnectedBox->setChecked(false);
    ui->ownerGroupBox->setEnabled(false);
    ui->getTableButton->setEnabled(false);
    ui->findTablesButton->setEnabled(false);
    ui->menuTextBrowser->setText("Daemon Not Connected");
}


void Menu::walletToggle()
{
    rpc::playerAddress = ui->walletRPCinput->text();
    loginInfo();
    ui->walletConnectedBox->setChecked(false);
    ui->ownerGroupBox->setEnabled(false);
    ui->getTableButton->setEnabled(false);
    ui->menuTextBrowser->setText("Wallet Not Connected");
}


void Menu::contractToggle()
{
    Menu::contractAddress = ui->contractLineEdit->text();
    ui->contractCheckBox->setChecked(false);
    ui->ownerGroupBox->setEnabled(false);
    ui->menuTextBrowser->setText("Could Not Connect To Contract");
}


void Menu::setFonts(QString os)
{
    int mcR;
    int ubR;

    if(os == "macos" || os == "osx" || os == "darwin"){
        mcR = 23;
        ubR = 13;
        ui->themeComboBox->setEnabled(false);
    }else {
        mcR = 17;
        ubR = 10;
    }

    int fontId = QFontDatabase::addApplicationFont(":/fonts/Macondo-Regular.ttf");
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont macondoRegular(fontFamily);
    macondoRegular.setPointSize(mcR);
    ui->menuTextBrowser->setFont(macondoRegular);
    ui->menuTextBrowser->setText("Welcome to dReam Tables Five Card Poker\nTable v1.3.1");

    int fontId2 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily2 = QFontDatabase::applicationFontFamilies(fontId2).at(0);
    QFont ubuntuRegular(fontFamily2);
    ubuntuRegular.setPointSize(ubR);
    ui->playerGroupBox->setFont(ubuntuRegular);
    ui->userpassInput->setFont(ubuntuRegular);
    ui->daemonRPCinput->setFont(ubuntuRegular);
    ui->daemonConnectedBox->setFont(ubuntuRegular);
    ui->daemonRPCbutton->setFont(ubuntuRegular);
    ui->walletRPCinput->setFont(ubuntuRegular);
    ui->walletConnectedBox->setFont(ubuntuRegular);
    ui->walletRPCbutton->setFont(ubuntuRegular);
    ui->contractLineEdit->setFont(ubuntuRegular);
    ui->contractCheckBox->setFont(ubuntuRegular);
    ui->contractButton->setFont(ubuntuRegular);
    ui->findTablesButton->setFont(ubuntuRegular);
    ui->getTableButton->setFont(ubuntuRegular);
    ui->ownerGroupBox->setFont(ubuntuRegular);
    ui->playersComboBox->setFont(ubuntuRegular);
    ui->anteSpinBox->setFont(ubuntuRegular);
    ui->setTableButton->setFont(ubuntuRegular);
    ui->cleanTableButton->setFont(ubuntuRegular);
    ui->delistTableButton->setFont(ubuntuRegular);
    ui->listTableButton->setFont(ubuntuRegular);
    ui->newTableButton->setFont(ubuntuRegular);
    ui->autoPayRButton->setFont(ubuntuRegular);
    ui->sharedRButton->setFont(ubuntuRegular);
    ui->forceButton->setFont(ubuntuRegular);
    ui->buttonBox->setFont(ubuntuRegular);
}


void Menu::checkThemes()
{
    qInfo() << ("\033[36m ♤♡♧ Looking for NFA Themes  ♧♡♤\033[0m");
    rpc r;
    QString pre = QDir().absolutePath();
    AZYDS(pre, r);
    qInfo() << ("\033[36m ♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤♡♧♢♧♡♤\033[0m");
}


void Menu::setMenuTheme()
{
    QPalette palette;
    palette.setBrush(QPalette::Window, Menu::theme);
    this->setPalette(palette);
}


void Menu::on_contractButton_clicked()
{
    Menu::contractAddress = ui->contractLineEdit->text();
    checkContract();
    checkIfListed();
}


void Menu::on_daemonRPCbutton_clicked()
{
    rpc::daemonAddress = ui->daemonRPCinput->text()+"/json_rpc";
    checkDaemon();
}


void Menu::on_walletRPCbutton_clicked()
{
    loginInfo();
    rpc::playerAddress = ui->walletRPCinput->text()+"/json_rpc";
    checkAddress();
    checkWallet();
}


void Menu::on_setTableButton_clicked()
{
    setTable();
}


void Menu::on_cleanTableButton_clicked()
{
    cleanTable();
}


void Menu::on_getTableButton_clicked()
{
    Confirm::whichText = 1;
    confirmationBox();

    if(Confirm::actionConfirmed == true){
            getDreams();
            ui->menuTextBrowser->setText("Your table is being prepared and will be ready for use in one moment...");
            delay();
            fetchInfo();
            ui->getTableButton->setEnabled(false);

            Confirm::actionConfirmed = false;
    }else {

        Confirm::actionConfirmed = false;
    }
}


void Menu::on_newTableButton_clicked()
{
    Confirm::whichText = 2;
    confirmationBox();

    if(Confirm::actionConfirmed == true){
        QFile unlockedFile("contract/Holdero.bas");
        unlockedFile.open(QIODevice::ReadWrite);
        if(unlockedFile.exists()){
            if(Menu::os == "windows"){
                if(!QDir::setCurrent(QDir::currentPath()+QStringLiteral("/contract"))){
                    ui->menuTextBrowser->setText("Could Not Navigate to /contract");
                }else {
                    windowsUpload(unlockedFile.exists());
                    QDir dir = QDir::currentPath();
                    dir.cdUp();
                    QDir::setCurrent(dir.path());
                }
            }else {
                unixUpload(unlockedFile.exists());
            }
        }else {
            ui->menuTextBrowser->setText("No Contract File To Upload");
        }

        Confirm::actionConfirmed = false;
    }else {

        Confirm::actionConfirmed = false;
    }

}


void Menu::confirmationBox()
{
    Confirm m;
    m.setModal(true);
    m.exec();
}


void Menu::on_autoPayRButton_clicked()
{
    if(ui->autoPayRButton->isChecked()){
        Menu::autoPayout = true;
    }else {
        Menu::autoPayout = false;
    }

}


void Menu::on_sharedRButton_clicked()
{
    if(ui->sharedRButton->isChecked()){
        Menu::sharedDeck = true;
        MainWindow::shared0 = false;
        MainWindow::shared1 = false;
        MainWindow::shared2 = false;
        MainWindow::shared3 = false;
        MainWindow::shared4 = false;
        MainWindow::shared5 = false;
        if(rpc::oneId == rpc::IdHash){
            ownerShare();
        }
    }else {
        Menu::sharedDeck = false;
    }
}


void Menu::on_listTableButton_clicked() /// Listing disabled for contract migration
{
    Confirm::whichText = 3;
    confirmationBox();

    if(Confirm::actionConfirmed == true){
        listTable();
        Confirm::actionConfirmed = false;
        ui->listTableButton->setEnabled(false);
        ui->delistTableButton->setEnabled(true);
    }else {

        Confirm::actionConfirmed = false;
    }

}


void Menu::on_delistTableButton_clicked()
{
    Confirm::whichText = 4;
    confirmationBox();

    if(Confirm::actionConfirmed == true){
        delistTable();
        ui->delistTableButton->setEnabled(false);
        ui->listTableButton->setEnabled(true);
        Confirm::actionConfirmed = false;
    }else {

        Confirm::actionConfirmed = false;
    }

}


void Menu::on_findTablesButton_clicked()
{
    ui->menuTextBrowser->setText("Public Tables:\n");
    fetchListingScData();
}


void Menu::on_forceButton_clicked()
{
    Confirm::whichText = 5;
    confirmationBox();

    if(Confirm::actionConfirmed == true){
        forceStart();
        Confirm::actionConfirmed = false;
    }else {

        Confirm::actionConfirmed = false;
    }

}


void Menu::loadThemeImage()
{
    Menu::theme.loadFromData(tImgCtrl->downloadedData());
    setMenuTheme();
    Menu::loading = false;
    Menu::themeChanged = true;
}


void Menu::on_themeComboBox_currentTextChanged(const QString &arg1)
{
    QUrl imageUrl;

    if(arg1 == "Main Theme"){
        Menu::theme.load(":/images/background.png");
        setMenuTheme();
        Menu::themeChanged = true;
        Menu::themeIndex = 0;
        qInfo() << ("\033[36m ♤♡♧♢ Loading Standard Theme♢♧♡♤\033[0m");
    }

    if(arg1 == "AZYDS0001"){
        qInfo() << ("\033[36m ♤♡♧♢♧♡♤Loading AZYDS0001♤♡♧♢♧♡♤\033[0m");
        Menu::loading = true;
        Menu::themeIndex = 1;
        imageUrl = "https://raw.githubusercontent.com/Azylem/AZYDS0001/main/AZYDS0001-EnterTheMachine-DS.png";
        tImgCtrl = new FileDownloader(imageUrl, this);
        connect(tImgCtrl, SIGNAL (downloaded()), this, SLOT (loadThemeImage()));
    }

    if(arg1 == "AZYDS0002"){
        qInfo() << ("\033[36m ♤♡♧♢♧♡♤Loading AZYDS0002♤♡♧♢♧♡♤\033[0m");
        Menu::loading = true;
        Menu::themeIndex = 2;
        imageUrl = "https://raw.githubusercontent.com/Azylem/AZYDS0002/main/AZYDS0002-CriticalMass-DS.png";
        tImgCtrl = new FileDownloader(imageUrl, this);
        connect(tImgCtrl, SIGNAL (downloaded()), this, SLOT (loadThemeImage()));
    }

    if(arg1 == "AZYDS0003"){
        qInfo() << ("\033[36m ♤♡♧♢♧♡♤Loading AZYDS0003♤♡♧♢♧♡♤\033[0m");
        Menu::loading = true;
        Menu::themeIndex = 3;
        imageUrl = "https://raw.githubusercontent.com/Azylem/AZYDS0003/main/AZYDS0003-GateReactor-DS.png";
        tImgCtrl = new FileDownloader(imageUrl, this);
        connect(tImgCtrl, SIGNAL (downloaded()), this, SLOT (loadThemeImage()));
    }

    if(arg1 == "AZYDS0004"){
        qInfo() << ("\033[36m ♤♡♧♢♧♡♤Loading AZYDS0004♤♡♧♢♧♡♤\033[0m");
        Menu::loading = true;
        Menu::themeIndex = 4;
        imageUrl = "https://raw.githubusercontent.com/Azylem/AZYDS0004/main/AZYDS0004-MaximumSimplicity-DS.png";
        tImgCtrl = new FileDownloader(imageUrl, this);
        connect(tImgCtrl, SIGNAL (downloaded()), this, SLOT (loadThemeImage()));
    }

    if(arg1 == "AZYDS0005"){
        qInfo() << ("\033[36m ♤♡♧♢♧♡♤Loading AZYDS0005♤♡♧♢♧♡♤\033[0m");
        Menu::loading = true;
        Menu::themeIndex = 5;
        imageUrl = "https://raw.githubusercontent.com/Azylem/AZYDS0005/main/AZYDS0005-ConstructReality-DS.png";
        tImgCtrl = new FileDownloader(imageUrl, this);
        connect(tImgCtrl, SIGNAL (downloaded()), this, SLOT (loadThemeImage()));
    }
}
