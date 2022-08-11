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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "menu.h"
#include "rpc/rpc.h"
#include "hands/handranks.h"



int MainWindow::playerEntry()      /// Player registry (sit down at table)
{
    CURL *curlPlayerEntry;          /// Set up cUrl
    CURLcode res;
    string playerEntryReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayerEntry\"}, {\"name\":\"address\",\"datatype\":\"S\",\"value\":\""+rpc::IdHash+"\" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString(); /// Player address from menu
    const char *dealCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();  /// Player login from menu

    curlPlayerEntry = curl_easy_init();

    if(curlPlayerEntry) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlPlayerEntry, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_URL, dealCh);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlPlayerEntry, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlPlayerEntry, CURLOPT_WRITEDATA, &playerEntryReadBuffer);

      res = curl_easy_perform(curlPlayerEntry);             /// Preform cUrl and clean up
      curl_easy_cleanup(curlPlayerEntry);

      QByteArray br = playerEntryReadBuffer.c_str();        /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue entryTxid = cbResults.value("txid");

      if(entryTxid.isString()){
          ui->logTextBrowser->setText("Player Entry TXID: "+entryTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->txLogTextBrowser->append("TXID: "+entryTxid.toString()+"\n");
          ui->entryPushButton->setEnabled(false);
          ui->winnerComboBox->setEnabled(false);
          MainWindow::skipCount = 3;
      }else {

          ui->logTextBrowser->setText("Error No Entry TXID");      /// No TXID was recieved
          MainWindow::skipCount = 5;
      }

    }
    return 0;
}


int MainWindow::playerLeave()      /// Player leave table
{
    CURL *curlplayerLeave;
    CURLcode res;
    string playerLeaveReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString checkOutId = QString::number(ui->playerId->value());
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayerLeave\"}, {\"name\":\"id\",\"datatype\":\"U\",\"value\":"+checkOutId+" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *dealCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlplayerLeave = curl_easy_init();

    if(curlplayerLeave) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlplayerLeave, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlplayerLeave, CURLOPT_URL, dealCh);
      curl_easy_setopt(curlplayerLeave, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlplayerLeave, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlplayerLeave, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlplayerLeave, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlplayerLeave, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlplayerLeave, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlplayerLeave, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlplayerLeave, CURLOPT_WRITEDATA, &playerLeaveReadBuffer);

      res = curl_easy_perform(curlplayerLeave);
      curl_easy_cleanup(curlplayerLeave);

      QByteArray br = playerLeaveReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue leaveTxid = cbResults.value("txid");

      if(leaveTxid.isString()){
          ui->logTextBrowser->setText("Player Leave TXID: "+leaveTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+leaveTxid.toString()+"\n");
          ui->entryPushButton->setEnabled(false);
          ui->winnerComboBox->setEnabled(false);
          if(ui->playerId->value() != 1){
            ui->playerId->setValue(0);
          }

      }else {
          ui->logTextBrowser->setText("Error No Leave TXID");
          MainWindow::skipCount = 5;
      }

    }
    return 0;
}


void MainWindow::generateKey()    /// Generates player client key
{
    srand(time(0));
    QString key = QString::number(rand() % 999999999999);
    rpc::clientKey = QString(QCryptographicHash::hash((key.toUtf8()),QCryptographicHash::Sha256).toHex());

    QFile keyFile(".handKey");
    keyFile.open(QIODevice::ReadWrite);

    if(keyFile.exists()) {
        keyFile.resize(0);
        keyFile.write(rpc::clientKey.toStdString().c_str());
    }
}


int MainWindow::dealHand()      /// Ante and deals player a hand
{
    generateKey();
    CURL *curlDealHand;
    CURLcode res;
    string dealReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString whichBlind = "0";
    QString anteAmount;

    if(rpc::pot == 0){
        anteAmount = QString::number(rpc::ante+rpc::smallBlind);
        whichBlind = QString::number(1);

    }else if (rpc::pot == rpc::smallBlind || rpc::pot == rpc::ante+rpc::smallBlind){
        anteAmount = QString::number(ui->anteIsDSB->value()*100000+rpc::bigBlind);
        whichBlind = whichBlind = QString::number(2);

    }else {
        anteAmount = QString::number(ui->anteIsDSB->value()*100000);
    }

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"amount\":500 , \"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\", \"burn\":"+anteAmount+"}] , \"fees\":600 , \"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"DealHand\"}, {\"name\":\"pcSeed\",\"datatype\":\"H\",\"value\":\""+rpc::clientKey+"\"}, {\"name\":\"blinds\",\"datatype\":\"U\",\"value\":"+whichBlind+"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *dealCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlDealHand = curl_easy_init();

    if(curlDealHand) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlDealHand, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlDealHand, CURLOPT_URL, dealCh);
      curl_easy_setopt(curlDealHand, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlDealHand, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlDealHand, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlDealHand, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlDealHand, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDealHand, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDealHand, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDealHand, CURLOPT_WRITEDATA, &dealReadBuffer);

      res = curl_easy_perform(curlDealHand);
      curl_easy_cleanup(curlDealHand);

      QByteArray br = dealReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue dealTxid = cbResults.value("txid");

      if(dealTxid.isString()){
          ui->logTextBrowser->setText("Deal Five Cards TXID: "+dealTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+dealTxid.toString()+"\n");
          Hand::keyIsPub = false;
      }else {

          ui->logTextBrowser->setText("Error No Deal Five Cards TXID");
          MainWindow::skipCount = 5;
      }

    }
    return 0;
}


int MainWindow::bet()      /// Place bet also for call and raise
{
    CURL *curlBet;
    CURLcode res;
    string betReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString dAmount = QString::number(ui->betSpinBox->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\", \"burn\":"+dAmount+"}] , \"fees\":300 , \"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *bCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlBet = curl_easy_init();

    if(curlBet) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlBet, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlBet, CURLOPT_URL, bCh);
      curl_easy_setopt(curlBet, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlBet, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlBet, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlBet, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlBet, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlBet, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlBet, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlBet, CURLOPT_WRITEDATA, &betReadBuffer);

      res = curl_easy_perform(curlBet);
      curl_easy_cleanup(curlBet);

      QByteArray br = betReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue betTxid = cbResults.value("txid");

      if(betTxid.isString()){
          ui->logTextBrowser->setText("Bet TXID: "+betTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+betTxid.toString()+"\n");
          Hand::hasBet = true;
      }else {

          ui->logTextBrowser->setText("Error No Bet TXID");
          MainWindow::skipCount = 5;
      }

    }
    return 0;
}


int MainWindow::check()      /// Check also used to fold on bet
{
    CURL *curlCheck;
    CURLcode res;
    string checkFoldReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\", \"burn\": 0}] , \"fees\":300 , \"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *cfCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlCheck = curl_easy_init();

    if(curlCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlCheck, CURLOPT_URL, cfCh);
      curl_easy_setopt(curlCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlCheck, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlCheck, CURLOPT_WRITEDATA, &checkFoldReadBuffer);

      res = curl_easy_perform(curlCheck);
      curl_easy_cleanup(curlCheck);

      QByteArray br = checkFoldReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue checkTxid = cbResults.value("txid");

      if(checkTxid.isString()){
          ui->logTextBrowser->setText("Check/Fold TXID: "+checkTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+checkTxid.toString()+"\n");
      }else {

          ui->logTextBrowser->setText("Error No Check/Fold TXID");
          MainWindow::skipCount = 5;
       }

    }
    return 0;
}


int MainWindow::winner()     /// Owner sends payout to winner
{
    CURL *curlWinner;
    CURLcode res;
    string winnerReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString winner = ui->winnerComboBox->currentText();
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}], \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Winner\"},{\"name\":\"whoWon\",\"datatype\":\"S\",\"value\":\""+winner+"\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlWinner = curl_easy_init();

    if(curlWinner) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlWinner, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlWinner, CURLOPT_URL, pCh);
      curl_easy_setopt(curlWinner, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlWinner, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlWinner, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlWinner, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlWinner, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlWinner, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlWinner, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlWinner, CURLOPT_WRITEDATA, &winnerReadBuffer);

      res = curl_easy_perform(curlWinner);
      curl_easy_cleanup(curlWinner);

      QByteArray br = winnerReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            ui->logTextBrowser->setText("Winner TXID: "+txid.toString());
            ui->txLogTextBrowser->append("TXID: "+txid.toString()+"\n");
            blankDisplay();
        }else {

            ui->logTextBrowser->setText("Error No Winner TXID");
            MainWindow::skipCount = 5;
        }

    }
    return 0;
}


int MainWindow::autopayWinner(QString whoWon)     /// Owner sends payout to winner
{
    CURL *curlAutopayWinner;
    CURLcode res;
    string afWinnerReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}], \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Winner\"},{\"name\":\"whoWon\",\"datatype\":\"S\",\"value\":\""+whoWon+"\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlAutopayWinner = curl_easy_init();

    if(curlAutopayWinner) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlAutopayWinner, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_URL, pCh);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlAutopayWinner, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlAutopayWinner, CURLOPT_WRITEDATA, &afWinnerReadBuffer);

      res = curl_easy_perform(curlAutopayWinner);
      curl_easy_cleanup(curlAutopayWinner);

      QByteArray br = afWinnerReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            ui->logTextBrowser->setText("Winner TXID: "+txid.toString());
            ui->txLogTextBrowser->append("TXID: "+txid.toString()+"\n");
        }else {

            ui->logTextBrowser->setText("Error Couldn't Pay Winner");
            MainWindow::skipCount = 5;
        }

    }
    return 0;
}


int MainWindow::splitWinner()     /// Owner sends split payout to winners
{
    CURL *curlSplit;
    CURLcode res;
    string winnerReadBuffer;
    char error[CURL_ERROR_SIZE];

    int ways = 0;
    QString splitWinners[6] = {"Zero", "Zero", "Zero", "Zero", "Zero", "Zero"};

    if(p1HighCardArr[0] > 0){
        ways = 1;
        splitWinners[0] = "Player1";
    }

    if(p2HighCardArr[0] > 0){
        ++ways;
        splitWinners[1] = "Player2";
    }

    if(p3HighCardArr[0] > 0){
        ++ways;
        splitWinners[2] = "Player3";
    }

    if(p4HighCardArr[0] > 0){
        ++ways;
        splitWinners[3] = "Player4";
    }

    if(p5HighCardArr[0] > 0){
        ++ways;
        splitWinners[4] = "Player5";
    }

    if(p6HighCardArr[0] > 0){
        ++ways;
        splitWinners[5] = "Player6";
    }

    std::sort(splitWinners, splitWinners + 6);
    QString stringWays = QString::number(ways);

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}], \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"SplitWinner\"},"
                     "{\"name\":\"div\",\"datatype\":\"U\",\"value\":"+stringWays+"}, {\"name\":\"split1\",\"datatype\":\"S\",\"value\":\""+splitWinners[0]+"\"}, {\"name\":\"split2\",\"datatype\":\"S\",\"value\":\""+splitWinners[1]+"\"}, {\"name\":\"split3\",\"datatype\":\"S\",\"value\":\""+splitWinners[2]+"\"}, {\"name\":\"split4\",\"datatype\":\"S\",\"value\":\""+splitWinners[3]+"\"}, {\"name\":\"split5\",\"datatype\":\"S\",\"value\":\""+splitWinners[4]+"\"}, {\"name\":\"split6\",\"datatype\":\"S\",\"value\":\""+splitWinners[5]+"\"}]}}";

    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlSplit = curl_easy_init();

    if(curlSplit) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlSplit, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlSplit, CURLOPT_URL, pCh);
      curl_easy_setopt(curlSplit, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlSplit, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlSplit, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlSplit, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlSplit, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlSplit, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlSplit, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlSplit, CURLOPT_WRITEDATA, &winnerReadBuffer);

      res = curl_easy_perform(curlSplit);
      curl_easy_cleanup(curlSplit);

      QByteArray br = winnerReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue txid = cbResults.value("txid");

        if(txid.isString()){
            ui->logTextBrowser->setText("Split Winner TXID: "+txid.toString());
            ui->txLogTextBrowser->append("TXID: "+txid.toString()+"\n");
            blankDisplay();

            if(rpc::end == 1){
                rpc::hashOne ="null";
                rpc::hashTwo = "null";
            }

        }else {

            ui->logTextBrowser->setText("Split Error No Winner TXID");
            MainWindow::skipCount = 5;
        }

    }
    return 0;
}


int MainWindow::revealKey()      /// Stores client key on chain for other players to reveal at end
{
    CURL *curlReveal;
    CURLcode res;
    string dealReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"RevealKey\"},{\"name\":\"pcSeed\",\"datatype\":\"H\",\"value\":\""+rpc::clientKey+"\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *revCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlReveal = curl_easy_init();

    if(curlReveal) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlReveal, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlReveal, CURLOPT_URL, revCh);
      curl_easy_setopt(curlReveal, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlReveal, CURLOPT_CONNECTTIMEOUT, 9L);
      curl_easy_setopt(curlReveal, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlReveal, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlReveal, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlReveal, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlReveal, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlReveal, CURLOPT_WRITEDATA, &dealReadBuffer);

      res = curl_easy_perform(curlReveal);
      curl_easy_cleanup(curlReveal);

      QByteArray br = dealReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue keyTxid = cbResults.value("txid");

      if(keyTxid.isString()){
          ui->logTextBrowser->setText("Reveal TXID: "+keyTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+keyTxid.toString()+"\n");
          Hand::keyIsPub = true;
      }else {

          ui->logTextBrowser->setText("Error No Reveal TXID");
          MainWindow::skipCount = 5;
      }

    }
    return 0;
}

