#include "handranks.h"
#include "ui_handranks.h"
#include "mainwindow.h"

HandRanks::HandRanks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HandRanks)
{
    ui->setupUi(this);
    setFonts();
}

HandRanks::~HandRanks()
{
    delete ui;
}

void HandRanks::setFonts()
{

    int fontId1 = QFontDatabase::addApplicationFont(":/fonts/Ubuntu-R.ttf");
    QString fontFamily1 = QFontDatabase::applicationFontFamilies(fontId1).at(0);
    QFont ubuntuRegular(fontFamily1);
    ui->hrTextBrowser->setFont(ubuntuRegular);

}
