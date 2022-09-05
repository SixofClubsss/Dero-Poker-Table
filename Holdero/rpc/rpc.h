#ifndef RPC_H
#define RPC_H
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

#include "string"
#include "curl/curl.h"
#include "QTime"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonValue"
#include "QJsonArray"
#include "QString"
#include "QObject"
#include "QDebug"
#include "QThread"

using std::string;


static size_t
WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


class rpc
{

public:
    static bool inGame;
    static bool paidOut;
    static bool assetConfirmed;
    static double blockHeight;
    static double clickedHeight;
    static std::string rpcLogin;
    static QString salt;
    static QString playerAddress;
    static QString daemonAddress;
    static QString IdHash;
    static int seats;
    static int count;
    static double ante;
    static double bigBlind;
    static double smallBlind;
    static double turn;
    static double balance;
    static QString oneId;
    static QString twoId;
    static QString threeId;
    static QString fourId;
    static QString fiveId;
    static QString sixId;
    static double dealer;
    static int draw;
    static int end;
    static double pot;
    static double wager;
    static double raised;
    static int bet;
    static int IV;
    static int p1Fold;
    static int p2Fold;
    static int p3Fold;
    static int p4Fold;
    static int p5Fold;
    static int p6Fold;
    static int p1Out;
    static int p2Out;
    static int p3Out;
    static int p4Out;
    static int p5Out;
    static int p6Out;
    static int checkPlayerId;
    static int full;
    static int open;

    static int flopBool;
    static int turnBool;
    static int riverBool;
    static int revealBool;

    static QString contractSeed;
    static QString clientKey;

    static QString hashOneone;
    static QString hashOnetwo;

    static QString hashTwoone;
    static QString hashTwotwo;

    static QString hashThreeone;
    static QString hashThreetwo;

    static QString hashFourone ;
    static QString hashFourtwo ;

    static QString hashFiveone ;
    static QString hashFivetwo ;

    static QString hashSixone;
    static QString hashSixtwo;

    static int flopCard1;
    static int flopCard2;
    static int flopCard3;
    static int riverCard;
    static int turnCard;

    static QString key1;
    static QString key2;
    static QString key3;
    static QString key4;
    static QString key5;
    static QString key6;

    static QString hashOne;
    static QString hashTwo;

    static QString sharedFace;
    static QString sharedBack;

    int getBalance();
    int getHeight();
    int fetchScData();
    int getDreams();
    int verifyNFAcreator(QString);
    int verifyAsset(QString);

};


class Worker : public QObject
{
    Q_OBJECT

public:
    static QThread workThread;

private slots:
    void onTimeout()
    {
        rpc rpcData;
        rpcData.getHeight();
        rpcData.fetchScData();
        rpcData.getBalance();
    }

};

#endif // RPC_H
