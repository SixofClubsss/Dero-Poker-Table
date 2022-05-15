#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"
#include "menu.h"

using std::string;
string rpc::rpcLogin;


void MainWindow::loginInfo()   /// Used to get wallet login info for wallet functions
{
    QString userInfo = ui->userInput->text()+":";
    QString passInfo = ui->passwordInput->text();
    string userStr = userInfo.toStdString();
    string passStr = passInfo.toStdString();
    rpc::rpcLogin = userStr+passStr;
}


int MainWindow::checkWallet(void)  /// Echo blockchain to confirm wallet is connected
{
    CURL *curlWalletCheck;      /// Set up cUrl
    CURLcode res;
    string readBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Echo\",\"params\":[\"Hello\", \"World\", \"!\"]}";

    QString walletAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = walletAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();            /// Get login info
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlWalletCheck = curl_easy_init();

    if(curlWalletCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlWalletCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlWalletCheck, CURLOPT_URL, pCh);
      curl_easy_setopt(curlWalletCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlWalletCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlWalletCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curlWalletCheck);
      curl_easy_cleanup(curlWalletCheck);           ///Preform cUrl and clean up

      QByteArray br = readBuffer.c_str();           /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonValue okCheck = cbObj["result"];

      std::cout << readBuffer << std::endl;

      if(okCheck == "WALLET Hello World !")
      {
          ui->walletConnectedBox->setChecked(true);      /// Wallet connected
          ui->logTextBrowser->setText("Wallet Connected");
          std::cout << "Wallet Connected" << std::endl;
      }else {

          ui->walletConnectedBox->setChecked(false);
          ui->logTextBrowser->setText("Wallet Not Connected");
          std::cout << "Wallet Not Connected" << std::endl;      /// Wallet NOT connected
      }

    }
    return 0;
}


int MainWindow::setTable(void)      /// Owner set table player limit and ante
{
    CURL *curlSetTable;
    CURLcode res;
    string setTableReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString playerLimit = QString::number(ui->playersComboBox->currentIndex());
    QString anteAmount = QString::number(ui->anteSpinBox->value()*100000);

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"SetTable\"},{\"name\":\"seats\",\"datatype\":\"U\",\"value\":"+playerLimit+" },{\"name\":\"ante\",\"datatype\":\"U\",\"value\":"+anteAmount+" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *stCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlSetTable = curl_easy_init();

    if(curlSetTable) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlSetTable, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlSetTable, CURLOPT_URL, stCh);
      curl_easy_setopt(curlSetTable, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlSetTable, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlSetTable, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlSetTable, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlSetTable, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlSetTable, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlSetTable, CURLOPT_WRITEDATA, &setTableReadBuffer);

      res = curl_easy_perform(curlSetTable);
      curl_easy_cleanup(curlSetTable);

      QByteArray br = setTableReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue setTableTxid = cbResults.value("txid");

      std::cout << setTableReadBuffer << std::endl;

      if(setTableTxid.isString())
      {
          ui->logTextBrowser->setText("Set Table TXID: "+setTableTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("Waiting for block");
          ui->txLogTextBrowser->append("TXID: "+setTableTxid.toString()+"\n");
          ui->gameKeyPushButton->setEnabled(true);
          ui->entryPushButton->setEnabled(false);

      }else
       {
          ui->logTextBrowser->setText("Error No Set Table TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::playerEntry(void)      /// Player registry (sit down at table)
{
    CURL *curlPlayerEntry;
    CURLcode res;
    string playerEntryReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"PlayerEntry\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *dealCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

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

      res = curl_easy_perform(curlPlayerEntry);
      curl_easy_cleanup(curlPlayerEntry);

      QByteArray br = playerEntryReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue entryTxid = cbResults.value("txid");

      if(entryTxid.isString())
      {
          ui->logTextBrowser->setText("Player Entry TXID: "+entryTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("Waiting for block");
          ui->txLogTextBrowser->append("TXID: "+entryTxid.toString()+"\n");
          ui->entryPushButton->setEnabled(false);
          ui->ownerPushButton->setEnabled(false);
          ui->playersComboBox->setEnabled(false);
          ui->winnerComboBox->setEnabled(false);
          ui->anteSpinBox->setEnabled(false);
          ui->gameKeyPushButton->setEnabled(false);
          fetchScData();

      }else
       {
          ui->logTextBrowser->setText("Error No Entry TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::dealFiveCardHand(void)      /// Ante and deals player a hand
{
    CURL *curlDealFiveCards;
    CURLcode res;
    string getChipsReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString anteAmount = QString::number(ui->anteIsDSB->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"sc_dero_deposit\":"+anteAmount+" , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"DealFiveCardHand\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *dealCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlDealFiveCards, CURLOPT_WRITEDATA, &getChipsReadBuffer);

      res = curl_easy_perform(curlDealFiveCards);
      curl_easy_cleanup(curlDealFiveCards);

      QByteArray br = getChipsReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue dealTxid = cbResults.value("txid");

      if(dealTxid.isString())
      {
          ui->logTextBrowser->setText("Deal Five Cards TXID: "+dealTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("Waiting for block");
          ui->txLogTextBrowser->append("TXID: "+dealTxid.toString()+"\n");

      }else
       {
          ui->logTextBrowser->setText("Error No Deal Five Cards TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::bet(void)      /// Place bet also for call and raise
{
    CURL *curlBet;
    CURLcode res;
    string betReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString dAmount = QString::number(ui->betSpinBox->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"sc_dero_deposit\":"+dAmount+" , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *bCh = pStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

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

      if(betTxid.isString())
      {
          ui->logTextBrowser->setText("Bet TXID: "+betTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("Waiting for block");
          ui->txLogTextBrowser->append("TXID: "+betTxid.toString()+"\n");
          Hand::hasBet = true;

      }else
       {
          ui->logTextBrowser->setText("Error No Bet TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::check(void)      /// Check also used to fold on bet
{
    CURL *curlCheck;
    CURLcode res;
    string checkFolcReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"sc_dero_deposit\":0 , \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Bet\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *cfCh = pStr.c_str ();

    loginInfo();
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
      curl_easy_setopt(curlCheck, CURLOPT_WRITEDATA, &checkFolcReadBuffer);

      res = curl_easy_perform(curlCheck);
      curl_easy_cleanup(curlCheck);

      QByteArray br = checkFolcReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue checkTxid = cbResults.value("txid");

      if(checkTxid.isString())
      {
          ui->logTextBrowser->setText("Check/Fold TXID: "+checkTxid.toString());  /// Displays TXID and adds TXID to session log
          ui->logTextBrowser->append("Waiting for block");
          ui->txLogTextBrowser->append("TXID: "+checkTxid.toString()+"\n");

      }else
       {
          ui->logTextBrowser->setText("Error No Check/Fold TXID");      /// No TXID was recieved
       }

    }
    return 0;
}


int MainWindow::drawCards(void) /// Get new cards at draw
{
    CURL *curlDrawCards;
    CURLcode res;
    string drawReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString whichCards = QString::number(ui->drawComboBox->currentIndex());
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"DrawCards\"},{\"name\":\"whichCard\",\"datatype\":\"U\",\"value\":"+whichCards+" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress = ui->walletRPCinput->text() + "/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *dcCh = pStr.c_str();

    loginInfo();
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

        if (drawTxid.isString())
        {
            ui->logTextBrowser->setText("Draw Card TXID: " + drawTxid.toString()); /// Displays TXID and adds TXID to session log
            ui->logTextBrowser->append("Waiting for block");
            ui->txLogTextBrowser->append("TXID: " + drawTxid.toString() + "\n");
        }
        else
        {
            ui->logTextBrowser->setText("Error No Draw Card TXID"); /// No TXID was recieved
        }
    }
    return 0;
}


int MainWindow::winner(void)     /// Owner sends payout to winner
{
    CURL *curlWinner;
    CURLcode res;
    string winnerReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString winner = ui->winnerComboBox->currentText();
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"amount\":1,\"destination\":\"deto1qy5su0wuw937tlurlwre606kunkr0fgl22f58dg35pfga5nv9wgg7qq3tvyk3\"}], \"fees\":1000 , \"scid\":\""+Menu::contractAddress+"\",\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Winner\"},{\"name\":\"whoWon\",\"datatype\":\"S\",\"value\":\""+winner+"\" }]}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress =  ui->walletRPCinput->text()+"/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *pCh = pStr.c_str ();

    loginInfo();
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

        if(txid.isString())
        {
            ui->logTextBrowser->setText("Winner TXID: "+txid.toString());
            ui->logTextBrowser->append("Waiting for block");
            ui->txLogTextBrowser->append("TXID: "+txid.toString()+"\n");

        }else
         {
            ui->logTextBrowser->setText("Error No Winner TXID");
         }

    }
    return 0;
}


int MainWindow::shuffleDeck(void) /// Trade Testnet Dero for Chips token (Only Chips are accepted for bets)
{
    CURL *curlShuffle;
    CURLcode res;
    string shuffleReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString whichCards = QString::number(ui->drawComboBox->currentIndex());
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"amount\":1,\"destination\":\"deto1qy5su0wuw937tlurlwre606kunkr0fgl22f58dg35pfga5nv9wgg7qq3tvyk3\"}], \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\", \"fees\":5000 ,\"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ShuffleDeck\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString playerAddress = ui->walletRPCinput->text() + "/json_rpc";
    string pStr = playerAddress.toStdString();
    const char *gcCh = pStr.c_str();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str();

    curlShuffle = curl_easy_init();

    if (curlShuffle) {
        struct curl_slist *headers = NULL;
        /// Add request headers
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        /// cUrl options
        curl_easy_setopt(curlShuffle, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curlShuffle, CURLOPT_URL, gcCh);
        curl_easy_setopt(curlShuffle, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curlShuffle, CURLOPT_ERRORBUFFER, error);
        curl_easy_setopt(curlShuffle, CURLOPT_USERPWD, loginCh);
        curl_easy_setopt(curlShuffle, CURLOPT_POSTFIELDS, postthis);
        curl_easy_setopt(curlShuffle, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
        curl_easy_setopt(curlShuffle, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlShuffle, CURLOPT_WRITEDATA, &shuffleReadBuffer);

        res = curl_easy_perform(curlShuffle);
        curl_easy_cleanup(curlShuffle);

        QByteArray br = shuffleReadBuffer.c_str();
        QJsonDocument cbDoc = QJsonDocument::fromJson(br);
        QJsonObject cbObj = cbDoc.object();
        QJsonObject cbResults = cbObj["result"].toObject();
        QJsonValue shuffleTxid = cbResults.value("txid");

        std::cout << shuffleReadBuffer << std::endl;

        if (shuffleTxid.isString())
        {
            ui->logTextBrowser->setText("Shuffle TXID: " + shuffleTxid.toString()); /// Displays TXID and adds TXID to session log
            ui->logTextBrowser->append("Waiting for block");
            ui->txLogTextBrowser->append("TXID: " + shuffleTxid.toString() + "\n");
        }
        else
        {
            ui->logTextBrowser->setText("Error No Shuffle TXID"); /// No TXID was recieved;
        }

    }
    return 0;
}

