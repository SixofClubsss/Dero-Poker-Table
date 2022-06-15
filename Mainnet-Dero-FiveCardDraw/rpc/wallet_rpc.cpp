/// dReam Tables Five Card Draw Poker
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc/rpc.h"
#include "menu.h"


int MainWindow::playerEntry()      /// Player registry (sit down at table)
{
    CURL *curlPlayerEntry;          /// Set up cUrl
    CURLcode res;
    string playerEntryReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayerEntry\"}, {\"name\":\"address\",\"datatype\":\"S\",\"value\":\""+rpc::IdAddress+"\" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString(); /// Player address from menu
    const char *dealCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();  /// Player login from menu

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
      }else {

          ui->logTextBrowser->setText("Error No Entry TXID");      /// No TXID was recieved
          MainWindow::skipCount = 2;
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
    const char *dealCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

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
          ui->winnerComboBox->setEnabled(false);;
          ui->playerId->setValue(0);
      }else {

          ui->logTextBrowser->setText("Error No Leave TXID");
          MainWindow::skipCount = 2;
      }

    }
    return 0;
}


int MainWindow::dealFiveCardHand()      /// Ante and deals player a hand
{
    CURL *curlDealFiveCards;
    CURLcode res;
    string dealReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString anteAmount = QString::number(ui->anteIsDSB->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"amount\":500 , \"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\", \"burn\":"+anteAmount+"}] , \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"DealFiveCardHand\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *dealCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlDealFiveCards = curl_easy_init();

    if(curlDealFiveCards) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlDealFiveCards, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_URL, dealCh);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDealFiveCards, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDealFiveCards, CURLOPT_WRITEDATA, &dealReadBuffer);

      res = curl_easy_perform(curlDealFiveCards);
      curl_easy_cleanup(curlDealFiveCards);

      QByteArray br = dealReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue dealTxid = cbResults.value("txid");

      if(dealTxid.isString()){
          ui->logTextBrowser->setText("Deal Five Cards TXID: "+dealTxid.toString());
          ui->txLogTextBrowser->append("TXID: "+dealTxid.toString()+"\n");
      }else {

          ui->logTextBrowser->setText("Error No Deal Five Cards TXID");
          MainWindow::skipCount = 2;
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
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"sc_dero_deposit\":"+dAmount+" , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *bCh = pStr.c_str ();

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
          MainWindow::skipCount = 2;
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

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"sc_dero_deposit\":0 , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *cfCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

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
          MainWindow::skipCount = 2;
       }

    }
    return 0;
}


int MainWindow::drawCards() /// Get new cards at draw
{
    CURL *curlDrawCards;
    CURLcode res;
    string drawReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString whichCards = QString::number(ui->drawComboBox->currentIndex());
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"amount\":100 , \"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}] , \"fees\":300 ,\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"DrawCards\"},{\"name\":\"whichCard\",\"datatype\":\"U\",\"value\":"+whichCards+" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *dcCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlDrawCards = curl_easy_init();

    if (curlDrawCards) {
        struct curl_slist *headers = NULL;
        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlDrawCards, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlDrawCards, CURLOPT_URL, dcCh);
        curl_easy_setopt(curlDrawCards, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curlDrawCards, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlDrawCards, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlDrawCards, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlDrawCards, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlDrawCards, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlDrawCards, CURLOPT_WRITEDATA, &drawReadBuffer);

        res = curl_easy_perform(curlDrawCards);
        curl_easy_cleanup(curlDrawCards);

        QByteArray br = drawReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue drawTxid = cbResults.value("txid");

        if (drawTxid.isString()){
            ui->logTextBrowser->setText("Draw Card TXID: " + drawTxid.toString());
            ui->txLogTextBrowser->append("TXID: " + drawTxid.toString() + "\n");
            ui->localPlayerCard1->setStyleSheet( "QLabel{ border: 0px; };" );
            ui->localPlayerCard2->setStyleSheet( "QLabel{ border: 0px; };" );
            ui->localPlayerCard3->setStyleSheet( "QLabel{ border: 0px; };" );
            ui->localPlayerCard4->setStyleSheet( "QLabel{ border: 0px; };" );
            ui->localPlayerCard5->setStyleSheet( "QLabel{ border: 0px; };" );
        }else {

            ui->logTextBrowser->setText("Error No Draw Card TXID");
            MainWindow::skipCount = 2;
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
    const char *pCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

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
            MainWindow::skipCount = 6;
        }

    }
    return 0;
}


int MainWindow::allFoldedWinner(QString whoWon)     /// Owner sends payout to winner
{
    CURL *curlAllFoldWinner;
    CURLcode res;
    string afWinnerReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}], \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Winner\"},{\"name\":\"whoWon\",\"datatype\":\"S\",\"value\":\""+whoWon+"\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str ();

    const char *loginCh = rpc::rpcLogin.c_str ();

    curlAllFoldWinner = curl_easy_init();

    if(curlAllFoldWinner) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_URL, pCh);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlAllFoldWinner, CURLOPT_WRITEDATA, &afWinnerReadBuffer);

      res = curl_easy_perform(curlAllFoldWinner);
      curl_easy_cleanup(curlAllFoldWinner);

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
            MainWindow::skipCount = 2;
        }

    }
    return 0;
}

