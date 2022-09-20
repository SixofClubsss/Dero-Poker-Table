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

#include "filedownloader.h"
#include "hands/handranks.h"


QImage Hand::sharedImage1;
QImage Hand::sharedImage2;
QImage Hand::sharedImage3;
QImage Hand::sharedImage4;
QImage Hand::sharedImage5;
QImage Hand::sharedImage6;
QImage Hand::sharedImage7;
QImage Hand::sharedImage8;
QImage Hand::sharedImage9;
QImage Hand::sharedImage10;
QImage Hand::sharedImage11;
QImage Hand::sharedImage12;
QImage Hand::sharedImage13;
QImage Hand::sharedImage14;
QImage Hand::sharedImage15;
QImage Hand::sharedImage16;
QImage Hand::sharedImage17;
QImage Hand::sharedImage18;
QImage Hand::sharedImage19;
QImage Hand::sharedImage20;
QImage Hand::sharedImage21;
QImage Hand::sharedImage22;
QImage Hand::sharedImage23;
QImage Hand::sharedImage24;
QImage Hand::sharedImage25;
QImage Hand::sharedImage26;
QImage Hand::sharedImage27;
QImage Hand::sharedImage28;
QImage Hand::sharedImage29;
QImage Hand::sharedImage30;
QImage Hand::sharedImage31;
QImage Hand::sharedImage32;
QImage Hand::sharedImage33;
QImage Hand::sharedImage34;
QImage Hand::sharedImage35;
QImage Hand::sharedImage36;
QImage Hand::sharedImage37;
QImage Hand::sharedImage38;
QImage Hand::sharedImage39;
QImage Hand::sharedImage40;
QImage Hand::sharedImage41;
QImage Hand::sharedImage42;
QImage Hand::sharedImage43;
QImage Hand::sharedImage44;
QImage Hand::sharedImage45;
QImage Hand::sharedImage46;
QImage Hand::sharedImage47;
QImage Hand::sharedImage48;
QImage Hand::sharedImage49;
QImage Hand::sharedImage50;
QImage Hand::sharedImage51;
QImage Hand::sharedImage52;


FileDownloader::FileDownloader(QUrl imageUrl, QObject *parent) :
    QObject(parent)
{
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
                this, SLOT (fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
    m_DownloadedData = pReply->readAll();
    pReply->deleteLater();
    emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
    return m_DownloadedData;
}


QUrl Menu::loadSharedCard(int card)
{
    QByteArray backData = rpc::sharedBack.toUtf8();
    QByteArray faceData = rpc::sharedFace.toUtf8();
    QByteArray backText = QByteArray::fromHex(backData);
    QByteArray faceText = QByteArray::fromHex(faceData);
    QString back = QString::fromLatin1(backText.data());
    QString face = QString::fromLatin1(faceText.data());
    QString suffix;


    if(card > 0){
        switch (card){
        case 1: suffix = "card1.png"; break;
        case 2: suffix = "card2.png"; break;
        case 3: suffix = "card3.png"; break;
        case 4: suffix = "card4.png"; break;
        case 5: suffix = "card5.png"; break;
        case 6: suffix = "card6.png"; break;
        case 7: suffix = "card7.png"; break;
        case 8: suffix = "card8.png"; break;
        case 9: suffix = "card9.png"; break;
        case 10: suffix = "card10.png"; break;
        case 11: suffix = "card11.png"; break;
        case 12: suffix = "card12.png"; break;
        case 13: suffix = "card13.png"; break;
        case 14: suffix = "card14.png"; break;
        case 15: suffix = "card15.png"; break;
        case 16: suffix = "card16.png"; break;
        case 17: suffix = "card17.png"; break;
        case 18: suffix = "card18.png"; break;
        case 19: suffix = "card19.png"; break;
        case 20: suffix = "card20.png"; break;
        case 21: suffix = "card21.png"; break;
        case 22: suffix = "card22.png"; break;
        case 23: suffix = "card23.png"; break;
        case 24: suffix = "card24.png"; break;
        case 25: suffix = "card25.png"; break;
        case 26: suffix = "card26.png"; break;
        case 27: suffix = "card27.png"; break;
        case 28: suffix = "card28.png"; break;
        case 29: suffix = "card29.png"; break;
        case 30: suffix = "card30.png"; break;
        case 31: suffix = "card31.png"; break;
        case 32: suffix = "card32.png"; break;
        case 33: suffix = "card33.png"; break;
        case 34: suffix = "card34.png"; break;
        case 35: suffix = "card35.png"; break;
        case 36: suffix = "card36.png"; break;
        case 37: suffix = "card37.png"; break;
        case 38: suffix = "card38.png"; break;
        case 39: suffix = "card39.png"; break;
        case 40: suffix = "card40.png"; break;
        case 41: suffix = "card41.png"; break;
        case 42: suffix = "card42.png"; break;
        case 43: suffix = "card43.png"; break;
        case 44: suffix = "card44.png"; break;
        case 45: suffix = "card45.png"; break;
        case 46: suffix = "card46.png"; break;
        case 47: suffix = "card47.png"; break;
        case 48: suffix = "card48.png"; break;
        case 49: suffix = "card49.png"; break;
        case 50: suffix = "card50.png"; break;
        case 51: suffix = "card51.png"; break;
        case 52: suffix = "card52.png"; break;
        }

        QUrl imageUrl(face+suffix);

        return imageUrl;
    }else {
        QUrl imageUrl(back);

        return imageUrl;
    }

}


void Menu::loadFullDeck()
{
    Menu::loading = true;
    loadShared0(loadSharedCard(0));
    loadDelay(90);
    loadShared1(loadSharedCard(1));
    loadDelay(90);
    loadShared2(loadSharedCard(2));
    loadDelay(90);
    loadShared3(loadSharedCard(3));
    loadDelay(90);
    loadShared4(loadSharedCard(4));
    loadDelay(90);
    loadShared5(loadSharedCard(5));
    loadDelay(90);
    loadShared6(loadSharedCard(6));
    loadDelay(90);
    loadShared7(loadSharedCard(7));
    loadDelay(90);
    loadShared8(loadSharedCard(8));
    loadDelay(90);
    loadShared9(loadSharedCard(9));
    loadDelay(90);
    loadShared10(loadSharedCard(10));
    loadDelay(90);
    loadShared11(loadSharedCard(11));
    loadDelay(90);
    loadShared12(loadSharedCard(12));
    loadDelay(90);
    loadShared13(loadSharedCard(13));
    loadDelay(90);
    loadShared14(loadSharedCard(14));
    loadDelay(90);
    loadShared15(loadSharedCard(15));
    loadDelay(90);
    loadShared16(loadSharedCard(16));
    loadDelay(90);
    loadShared17(loadSharedCard(17));
    loadDelay(90);
    loadShared18(loadSharedCard(18));
    loadDelay(90);
    loadShared19(loadSharedCard(19));
    loadDelay(90);
    loadShared20(loadSharedCard(20));
    loadDelay(90);
    loadShared21(loadSharedCard(21));
    loadDelay(90);
    loadShared22(loadSharedCard(22));
    loadDelay(90);
    loadShared23(loadSharedCard(23));
    loadDelay(90);
    loadShared24(loadSharedCard(24));
    loadDelay(90);
    loadShared25(loadSharedCard(25));
    loadDelay(90);
    loadShared26(loadSharedCard(26));
    loadDelay(90);
    loadShared27(loadSharedCard(27));
    loadDelay(90);
    loadShared28(loadSharedCard(28));
    loadDelay(90);
    loadShared29(loadSharedCard(29));
    loadDelay(90);
    loadShared30(loadSharedCard(30));
    loadDelay(90);
    loadShared31(loadSharedCard(31));
    loadDelay(90);
    loadShared32(loadSharedCard(32));
    loadDelay(90);
    loadShared33(loadSharedCard(33));
    loadDelay(90);
    loadShared34(loadSharedCard(34));
    loadDelay(90);
    loadShared35(loadSharedCard(35));
    loadDelay(90);
    loadShared36(loadSharedCard(36));
    loadDelay(90);
    loadShared37(loadSharedCard(37));
    loadDelay(90);
    loadShared38(loadSharedCard(38));
    loadDelay(90);
    loadShared39(loadSharedCard(39));
    loadDelay(90);
    loadShared40(loadSharedCard(40));
    loadDelay(90);
    loadShared41(loadSharedCard(41));
    loadDelay(90);
    loadShared42(loadSharedCard(42));
    loadDelay(90);
    loadShared43(loadSharedCard(43));
    loadDelay(90);
    loadShared44(loadSharedCard(44));
    loadDelay(90);
    loadShared45(loadSharedCard(45));
    loadDelay(90);
    loadShared46(loadSharedCard(46));
    loadDelay(90);
    loadShared47(loadSharedCard(47));
    loadDelay(90);
    loadShared48(loadSharedCard(48));
    loadDelay(90);
    loadShared49(loadSharedCard(49));
    loadDelay(90);
    loadShared50(loadSharedCard(50));
    loadDelay(90);
    loadShared51(loadSharedCard(51));
    loadDelay(90);
    loadShared52(loadSharedCard(52));
    loadDelay(90);
}


void Menu::loadShared0(QUrl url)
{
    s0_ImgCtrl = new FileDownloader(url, this);
    connect(s0_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage0()));
}


void Menu::loadShared1(QUrl url)
{
    s1_ImgCtrl = new FileDownloader(url, this);
    connect(s1_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage1()));
}


void Menu::loadShared2(QUrl url)
{
    s2_ImgCtrl = new FileDownloader(url, this);
    connect(s2_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage2()));
}


void Menu::loadShared3(QUrl url)
{
    s3_ImgCtrl = new FileDownloader(url, this);
    connect(s3_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage3()));
}


void Menu::loadShared4(QUrl url)
{
    s4_ImgCtrl = new FileDownloader(url, this);
    connect(s4_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage4()));
}


void Menu::loadShared5(QUrl url)
{
    s5_ImgCtrl = new FileDownloader(url, this);
    connect(s5_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage5()));
}


void Menu::loadShared6(QUrl url)
{
    s6_ImgCtrl = new FileDownloader(url, this);
    connect(s6_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage6()));
}


void Menu::loadShared7(QUrl url)
{
    s7_ImgCtrl = new FileDownloader(url, this);
    connect(s7_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage7()));
}


void Menu::loadShared8(QUrl url)
{
    s8_ImgCtrl = new FileDownloader(url, this);
    connect(s8_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage8()));
}


void Menu::loadShared9(QUrl url)
{
    s9_ImgCtrl = new FileDownloader(url, this);
    connect(s9_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage9()));
}


void Menu::loadShared10(QUrl url)
{
    s10_ImgCtrl = new FileDownloader(url, this);
    connect(s10_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage10()));
}


void Menu::loadShared11(QUrl url)
{
    s11_ImgCtrl = new FileDownloader(url, this);
    connect(s11_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage11()));
}


void Menu::loadShared12(QUrl url)
{
    s12_ImgCtrl = new FileDownloader(url, this);
    connect(s12_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage12()));
}


void Menu::loadShared13(QUrl url)
{
    s13_ImgCtrl = new FileDownloader(url, this);
    connect(s13_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage13()));
}


void Menu::loadShared14(QUrl url)
{
    s14_ImgCtrl = new FileDownloader(url, this);
    connect(s14_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage14()));
}


void Menu::loadShared15(QUrl url)
{
    s15_ImgCtrl = new FileDownloader(url, this);
    connect(s15_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage15()));
}


void Menu::loadShared16(QUrl url)
{
    s16_ImgCtrl = new FileDownloader(url, this);
    connect(s16_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage16()));
}


void Menu::loadShared17(QUrl url)
{
    s17_ImgCtrl = new FileDownloader(url, this);
    connect(s17_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage17()));
}


void Menu::loadShared18(QUrl url)
{
    s18_ImgCtrl = new FileDownloader(url, this);
    connect(s18_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage18()));
}


void Menu::loadShared19(QUrl url)
{
    s19_ImgCtrl = new FileDownloader(url, this);
    connect(s19_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage19()));
}


void Menu::loadShared20(QUrl url)
{
    s20_ImgCtrl = new FileDownloader(url, this);
    connect(s20_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage20()));
}


void Menu::loadShared21(QUrl url)
{
    s21_ImgCtrl = new FileDownloader(url, this);
    connect(s21_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage21()));
}


void Menu::loadShared22(QUrl url)
{
    s22_ImgCtrl = new FileDownloader(url, this);
    connect(s22_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage22()));
}


void Menu::loadShared23(QUrl url)
{
    s23_ImgCtrl = new FileDownloader(url, this);
    connect(s23_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage23()));
}


void Menu::loadShared24(QUrl url)
{
    s24_ImgCtrl = new FileDownloader(url, this);
    connect(s24_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage24()));
}


void Menu::loadShared25(QUrl url)
{
    s25_ImgCtrl = new FileDownloader(url, this);
    connect(s25_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage25()));
}


void Menu::loadShared26(QUrl url)
{
    s26_ImgCtrl = new FileDownloader(url, this);
    connect(s26_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage26()));
}


void Menu::loadShared27(QUrl url)
{
    s27_ImgCtrl = new FileDownloader(url, this);
    connect(s27_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage27()));
}


void Menu::loadShared28(QUrl url)
{
    s28_ImgCtrl = new FileDownloader(url, this);
    connect(s28_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage28()));
}


void Menu::loadShared29(QUrl url)
{
    s29_ImgCtrl = new FileDownloader(url, this);
    connect(s29_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage29()));
}


void Menu::loadShared30(QUrl url)
{
    s30_ImgCtrl = new FileDownloader(url, this);
    connect(s30_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage30()));
}


void Menu::loadShared31(QUrl url)
{
    s31_ImgCtrl = new FileDownloader(url, this);
    connect(s31_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage31()));
}


void Menu::loadShared32(QUrl url)
{
    s32_ImgCtrl = new FileDownloader(url, this);
    connect(s32_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage32()));
}


void Menu::loadShared33(QUrl url)
{
    s33_ImgCtrl = new FileDownloader(url, this);
    connect(s33_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage33()));
}


void Menu::loadShared34(QUrl url)
{
    s34_ImgCtrl = new FileDownloader(url, this);
    connect(s34_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage34()));
}


void Menu::loadShared35(QUrl url)
{
    s35_ImgCtrl = new FileDownloader(url, this);
    connect(s35_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage35()));
}


void Menu::loadShared36(QUrl url)
{
    s36_ImgCtrl = new FileDownloader(url, this);
    connect(s36_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage36()));
}


void Menu::loadShared37(QUrl url)
{
    s37_ImgCtrl = new FileDownloader(url, this);
    connect(s37_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage37()));
}


void Menu::loadShared38(QUrl url)
{
    s38_ImgCtrl = new FileDownloader(url, this);
    connect(s38_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage38()));
}


void Menu::loadShared39(QUrl url)
{
    s39_ImgCtrl = new FileDownloader(url, this);
    connect(s39_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage39()));
}


void Menu::loadShared40(QUrl url)
{
    s40_ImgCtrl = new FileDownloader(url, this);
    connect(s40_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage40()));
}


void Menu::loadShared41(QUrl url)
{
    s41_ImgCtrl = new FileDownloader(url, this);
    connect(s41_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage41()));
}


void Menu::loadShared42(QUrl url)
{
    s42_ImgCtrl = new FileDownloader(url, this);
    connect(s42_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage42()));
}


void Menu::loadShared43(QUrl url)
{
    s43_ImgCtrl = new FileDownloader(url, this);
    connect(s43_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage43()));
}


void Menu::loadShared44(QUrl url)
{
    s44_ImgCtrl = new FileDownloader(url, this);
    connect(s44_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage44()));
}


void Menu::loadShared45(QUrl url)
{
    s45_ImgCtrl = new FileDownloader(url, this);
    connect(s45_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage45()));
}


void Menu::loadShared46(QUrl url)
{
    s46_ImgCtrl = new FileDownloader(url, this);
    connect(s46_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage46()));
}


void Menu::loadShared47(QUrl url)
{
    s47_ImgCtrl = new FileDownloader(url, this);
    connect(s47_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage47()));
}


void Menu::loadShared48(QUrl url)
{
    s48_ImgCtrl = new FileDownloader(url, this);
    connect(s48_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage48()));
}


void Menu::loadShared49(QUrl url)
{
    s49_ImgCtrl = new FileDownloader(url, this);
    connect(s49_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage49()));
}


void Menu::loadShared50(QUrl url)
{
    s50_ImgCtrl = new FileDownloader(url, this);
    connect(s50_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage50()));
}


void Menu::loadShared51(QUrl url)
{
    s51_ImgCtrl = new FileDownloader(url, this);
    connect(s51_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage51()));
}


void Menu::loadShared52(QUrl url)
{
    s52_ImgCtrl = new FileDownloader(url, this);
    connect(s52_ImgCtrl, SIGNAL (downloaded()), this, SLOT (loadSharedImage52()));
}


void Menu::loadSharedImage0()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 0 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage0.loadFromData(s0_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage1()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 1 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage1.loadFromData(s1_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage2()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 2 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage2.loadFromData(s2_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage3()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 3 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage3.loadFromData(s3_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage4()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 4 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage4.loadFromData(s4_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage5()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 5 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage5.loadFromData(s5_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage6()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 6 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage6.loadFromData(s6_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage7()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 7 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage7.loadFromData(s7_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage8()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 8 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage8.loadFromData(s8_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage9()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 9 ♡♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage9.loadFromData(s9_ImgCtrl->downloadedData());
}

void Menu::loadSharedImage10()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 10 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage10.loadFromData(s10_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage11()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 11 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage11.loadFromData(s11_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage12()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 12 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage12.loadFromData(s12_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage13()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 13 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage13.loadFromData(s13_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage14()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 14 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage14.loadFromData(s14_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage15()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 15 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage15.loadFromData(s15_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage16()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 16 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage16.loadFromData(s16_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage17()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 17 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage17.loadFromData(s17_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage18()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 18 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage18.loadFromData(s18_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage19()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 19 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage19.loadFromData(s19_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage20()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 20 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage20.loadFromData(s20_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage21()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 21 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage21.loadFromData(s21_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage22()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 22 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage22.loadFromData(s22_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage23()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 23 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage23.loadFromData(s23_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage24()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 24 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage24.loadFromData(s24_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage25()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 25 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage25.loadFromData(s25_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage26()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 26 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage26.loadFromData(s26_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage27()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 27 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage27.loadFromData(s27_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage28()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 28 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage28.loadFromData(s28_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage29()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 29 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage29.loadFromData(s29_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage30()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 30 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage30.loadFromData(s30_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage31()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 31 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage31.loadFromData(s31_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage32()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 32 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage32.loadFromData(s32_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage33()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 33 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage33.loadFromData(s33_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage34()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 34 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage34.loadFromData(s34_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage35()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 35 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage35.loadFromData(s35_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage36()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 36 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage36.loadFromData(s36_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage37()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 37 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage37.loadFromData(s37_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage38()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 38 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage38.loadFromData(s38_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage39()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 39 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage39.loadFromData(s39_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage40()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 40 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage40.loadFromData(s40_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage41()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 41 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage41.loadFromData(s41_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage42()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 42 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage42.loadFromData(s42_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage43()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 43 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage43.loadFromData(s43_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage44()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 44 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage44.loadFromData(s44_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage45()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 45 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage45.loadFromData(s45_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage46()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 46 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage46.loadFromData(s46_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage47()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 47 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage47.loadFromData(s47_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage48()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 48 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage48.loadFromData(s48_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage49()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 49 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage49.loadFromData(s49_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage50()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 50 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage50.loadFromData(s50_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage51()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 51 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage51.loadFromData(s51_ImgCtrl->downloadedData());
}


void Menu::loadSharedImage52()
{
    qInfo() << ("\033[36m♤♡♧♢♧♡♤ Loading Card 52 ♤♡♧♢♧♡♤\033[0m");
    Hand::sharedImage52.loadFromData(s52_ImgCtrl->downloadedData());
}
