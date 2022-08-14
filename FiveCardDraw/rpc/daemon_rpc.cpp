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
#include "rpc/rpc.h"
#include "menu.h"


int rpc::getBalance()  /// Gets players dero balance
{
    CURL *curlBalanceCheck;
    CURLcode res;
    string balanceReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\": \"1\",\"method\": \"GetBalance\"}";

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlBalanceCheck = curl_easy_init();

    if(curlBalanceCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlBalanceCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_URL, pCh);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlBalanceCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlBalanceCheck, CURLOPT_WRITEDATA, &balanceReadBuffer);
      res = curl_easy_perform(curlBalanceCheck);
      curl_easy_cleanup(curlBalanceCheck);

      QByteArray br = balanceReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue Balance_jv = cbResults.value("balance");

      rpc::balance = Balance_jv.toDouble();

    }
    return 0;
}


int rpc::getHeight()  /// Gets current block height
{
    CURL *curlHeightCheck;
    CURLcode res;
    string heightReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\": \"1\",\"method\": \"DERO.GetHeight\"}";

    string dStr = rpc::daemonAddress.toStdString();
    const char *fhCh = dStr.c_str();

    curlHeightCheck = curl_easy_init();

    if(curlHeightCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlHeightCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlHeightCheck, CURLOPT_URL, fhCh);
      curl_easy_setopt(curlHeightCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlHeightCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlHeightCheck, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlHeightCheck, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for windows SSL disable*
      curl_easy_setopt(curlHeightCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlHeightCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlHeightCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlHeightCheck, CURLOPT_WRITEDATA, &heightReadBuffer);
      res = curl_easy_perform(curlHeightCheck);
      curl_easy_cleanup(curlHeightCheck);

      QByteArray br = heightReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue Height_jv = cbResults.value("height");

      rpc::blockHeight = Height_jv.toDouble();

    }
    return 0;
}

int rpc::fetchScData()       /// Get SC variables
{
    CURL *curlFetch;        /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *fdCh = dStr.c_str();

    curlFetch = curl_easy_init();

    if(curlFetch) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlFetch, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlFetch, CURLOPT_URL, fdCh);
      curl_easy_setopt(curlFetch, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlFetch, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlFetch, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlFetch, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for windows SSL disable*
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlFetch, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlFetch, CURLOPT_WRITEDATA, &fetchReadBuffer);

      res = curl_easy_perform(curlFetch);               /// Preform cUrl and clean up
      curl_easy_cleanup(curlFetch);

      QByteArray brw = fetchReadBuffer.c_str();          /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(brw);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonObject cbBalances = cbResults["balances"].toObject();
      QJsonValue Seats_jv = cbStringKeys.value("Seats at Table:");
      QJsonValue Ante_jv = cbStringKeys.value("Ante:");
      QJsonValue Turn_jv = cbStringKeys.value("Player:");
      QJsonValue OneId_jv = cbStringKeys.value("Player1 ID:");
      QJsonValue TwoId_jv = cbStringKeys.value("Player2 ID:");
      QJsonValue ThreeId_jv = cbStringKeys.value("Player3 ID:");
      QJsonValue FourId_jv = cbStringKeys.value("Player4 ID:");
      QJsonValue FiveId_jv = cbStringKeys.value("Player5 ID:");
      QJsonValue SixId_jv = cbStringKeys.value("Player6 ID:");
      QJsonValue Dealer_jv = cbStringKeys.value("Dealer:");
      QJsonValue Draw_jv = cbStringKeys.value("Draw");
      QJsonValue End_jv = cbStringKeys.value("End");
      QJsonValue Pot_jv = cbBalances.value("0000000000000000000000000000000000000000000000000000000000000000");
      QJsonValue Wager_jv = cbStringKeys.value("Wager:");
      QJsonValue Raised_jv = cbStringKeys.value("Raised:");
      QJsonValue Bet_jv = cbStringKeys.value("Bet");
      QJsonValue Full_jv = cbStringKeys.value("Full");
      QJsonValue Open_jv = cbStringKeys.value("Open");

      QJsonValue IV_jv = cbStringKeys.value("IV");
      QJsonValue OBF_jv = cbStringKeys.value("OBF");
      QJsonValue P1Fold_jv = cbStringKeys.value("0F");
      QJsonValue P2Fold_jv = cbStringKeys.value("1F");
      QJsonValue P3Fold_jv = cbStringKeys.value("2F");
      QJsonValue P4Fold_jv = cbStringKeys.value("3F");
      QJsonValue P5Fold_jv = cbStringKeys.value("4F");
      QJsonValue P6Fold_jv = cbStringKeys.value("5F");
      QJsonValue P1Out_jv = cbStringKeys.value("0SO");
      QJsonValue P2Out_jv = cbStringKeys.value("1SO");
      QJsonValue P3Out_jv = cbStringKeys.value("2SO");
      QJsonValue P4Out_jv = cbStringKeys.value("3SO");
      QJsonValue P5Out_jv = cbStringKeys.value("4SO");
      QJsonValue P6Out_jv = cbStringKeys.value("5SO");

      QJsonValue ContractSeed_jv = cbStringKeys.value("HandSeed");
      QJsonValue RevealBool_jv = cbStringKeys.value("Reveal");

      QJsonValue onecard1_jv = cbStringKeys.value("Player1card1");
      QJsonValue onecard2_jv = cbStringKeys.value("Player1card2");
      QJsonValue onecard3_jv = cbStringKeys.value("Player1card3");
      QJsonValue onecard4_jv = cbStringKeys.value("Player1card4");
      QJsonValue onecard5_jv = cbStringKeys.value("Player1card5");

      QJsonValue twocard1_jv = cbStringKeys.value("Player2card1");
      QJsonValue twocard2_jv = cbStringKeys.value("Player2card2");
      QJsonValue twocard3_jv = cbStringKeys.value("Player2card3");
      QJsonValue twocard4_jv = cbStringKeys.value("Player2card4");
      QJsonValue twocard5_jv = cbStringKeys.value("Player2card5");

      QJsonValue threecard1_jv = cbStringKeys.value("Player3card1");
      QJsonValue threecard2_jv = cbStringKeys.value("Player3card2");
      QJsonValue threecard3_jv = cbStringKeys.value("Player3card3");
      QJsonValue threecard4_jv = cbStringKeys.value("Player3card4");
      QJsonValue threecard5_jv = cbStringKeys.value("Player3card5");

      QJsonValue fourcard1_jv = cbStringKeys.value("Player4card1");
      QJsonValue fourcard2_jv = cbStringKeys.value("Player4card2");
      QJsonValue fourcard3_jv = cbStringKeys.value("Player4card3");
      QJsonValue fourcard4_jv = cbStringKeys.value("Player4card4");
      QJsonValue fourcard5_jv = cbStringKeys.value("Player4card5");

      QJsonValue fivecard1_jv = cbStringKeys.value("Player5card1");
      QJsonValue fivecard2_jv = cbStringKeys.value("Player5card2");
      QJsonValue fivecard3_jv = cbStringKeys.value("Player5card3");
      QJsonValue fivecard4_jv = cbStringKeys.value("Player5card4");
      QJsonValue fivecard5_jv = cbStringKeys.value("Player5card5");

      QJsonValue sixcard1_jv = cbStringKeys.value("Player6card1");
      QJsonValue sixcard2_jv = cbStringKeys.value("Player6card2");
      QJsonValue sixcard3_jv = cbStringKeys.value("Player6card3");
      QJsonValue sixcard4_jv = cbStringKeys.value("Player6card4");
      QJsonValue sixcard5_jv = cbStringKeys.value("Player6card5");

      QJsonValue Key1_jv = cbStringKeys.value("Player1Key");
      QJsonValue Key2_jv = cbStringKeys.value("Player2Key");
      QJsonValue Key3_jv = cbStringKeys.value("Player3Key");
      QJsonValue Key4_jv = cbStringKeys.value("Player4Key");
      QJsonValue Key5_jv = cbStringKeys.value("Player5Key");
      QJsonValue Key6_jv = cbStringKeys.value("Player6Key");

      rpc::seats = Seats_jv.toInt();
      rpc::ante = Ante_jv.toDouble();
      rpc::turn = Turn_jv.toDouble();
      rpc::oneId = OneId_jv.toString();
      rpc::twoId = TwoId_jv.toString();
      rpc::threeId = ThreeId_jv.toString();
      rpc::fourId = FourId_jv.toString();
      rpc::fiveId = FiveId_jv.toString();
      rpc::sixId = SixId_jv.toString();
      rpc::dealer = Dealer_jv.toDouble();
      rpc::draw = Draw_jv.toInt();
      rpc::end = End_jv.toInt();
      rpc::pot = Pot_jv.toDouble();
      rpc::wager = Wager_jv.toDouble();
      rpc::raised = Raised_jv.toDouble();
      rpc::bet = Bet_jv.toInt();

      rpc::IV = IV_jv.toInt();
      rpc::OBF = OBF_jv.toInt();
      rpc::p1Fold = P1Fold_jv.toInt();
      rpc::p2Fold = P2Fold_jv.toInt();
      rpc::p3Fold = P3Fold_jv.toInt();
      rpc::p4Fold = P4Fold_jv.toInt();
      rpc::p5Fold = P5Fold_jv.toInt();
      rpc::p6Fold = P6Fold_jv.toInt();
      rpc::p1Out = P1Out_jv.toInt();
      rpc::p2Out = P2Out_jv.toInt();
      rpc::p3Out = P3Out_jv.toInt();
      rpc::p4Out = P4Out_jv.toInt();
      rpc::p5Out = P5Out_jv.toInt();
      rpc::p6Out = P6Out_jv.toInt();
      rpc::full = Full_jv.toInt();
      rpc::open = Open_jv.toInt();

      rpc::contractSeed = ContractSeed_jv.toString();
      rpc::revealBool = RevealBool_jv.toInt();

      rpc::hashOneone = onecard1_jv.toString();
      rpc::hashOnetwo = onecard2_jv.toString();
      rpc::hashOnethree = onecard3_jv.toString();
      rpc::hashOnefour = onecard4_jv.toString();
      rpc::hashOnefive = onecard5_jv.toString();

      rpc::hashTwoone = twocard1_jv.toString();
      rpc::hashTwotwo = twocard2_jv.toString();
      rpc::hashTwothree = twocard3_jv.toString();
      rpc::hashTwofour = twocard4_jv.toString();
      rpc::hashTwofive = twocard5_jv.toString();

      rpc::hashThreeone = threecard1_jv.toString();
      rpc::hashThreetwo = threecard2_jv.toString();
      rpc::hashThreethree = threecard3_jv.toString();
      rpc::hashThreefour = threecard4_jv.toString();
      rpc::hashThreefive = threecard5_jv.toString();

      rpc::hashFourone = fourcard1_jv.toString();
      rpc::hashFourtwo = fourcard2_jv.toString();
      rpc::hashFourthree = fourcard3_jv.toString();
      rpc::hashFourfour = fourcard4_jv.toString();
      rpc::hashFourfive = fourcard5_jv.toString();

      rpc::hashFiveone = fivecard1_jv.toString();
      rpc::hashFivetwo = fivecard2_jv.toString();
      rpc::hashFivethree = fivecard3_jv.toString();
      rpc::hashFivefour = fivecard4_jv.toString();
      rpc::hashFivefive = fivecard5_jv.toString();

      rpc::hashSixone = sixcard1_jv.toString();
      rpc::hashSixtwo = sixcard2_jv.toString();
      rpc::hashSixthree = sixcard3_jv.toString();
      rpc::hashSixfour = sixcard4_jv.toString();
      rpc::hashSixfive = sixcard5_jv.toString();

      rpc::salt = rpc::OBF;
      QString handId = QString::number(rpc::checkPlayerId);

      QJsonValue card1 = cbStringKeys.value("Player"+handId.toUtf8()+"card1");
      QJsonValue card2 = cbStringKeys.value("Player"+handId.toUtf8()+"card2");
      QJsonValue card3 = cbStringKeys.value("Player"+handId.toUtf8()+"card3");
      QJsonValue card4 = cbStringKeys.value("Player"+handId.toUtf8()+"card4");
      QJsonValue card5 = cbStringKeys.value("Player"+handId.toUtf8()+"card5");

      rpc::hashOne = card1.toString();
      rpc::hashTwo = card2.toString();
      rpc::hashThree = card3.toString();
      rpc::hashFour = card4.toString();
      rpc::hashFive = card5.toString();

      rpc::key1 = Key1_jv.toString();
      rpc::key2 = Key2_jv.toString();
      rpc::key3 = Key3_jv.toString();
      rpc::key4 = Key4_jv.toString();
      rpc::key5 = Key5_jv.toString();
      rpc::key6 = Key6_jv.toString();

      rpc::inGame = true;

    }
    return 0;
}
