#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "rpc.h"
#include "menu.h"

using std::string;
bool Hand::hasBet;
bool Hand::endSignal;


void MainWindow::delay()            /// Delay for block time
{
    QTime dieTime = QTime::currentTime().addSecs(30);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int MainWindow::fetchScData(void)       /// Get SC variables & control buttons
{
    CURL *curlFetch;        /// Set up cUrl
    CURLcode res;
    string fetchReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *fdCh = dStr.c_str ();

    loginInfo();        /// Get logn info
    const char *loginCh = rpc::rpcLogin.c_str ();

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
      curl_easy_setopt(curlFetch, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlFetch, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlFetch, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlFetch, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlFetch, CURLOPT_WRITEDATA, &fetchReadBuffer);

      res = curl_easy_perform(curlFetch);   /// Preform cUrl and clean up
      curl_easy_cleanup(curlFetch);

      QByteArray brw = fetchReadBuffer.c_str();      /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(brw);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonObject cbBalances = cbResults["balances"].toObject();
      QJsonValue seats = cbStringKeys.value("Seats at Table:");
      QJsonValue ante = cbStringKeys.value("Ante:");
      QJsonValue turn = cbStringKeys.value("Player:");
      QJsonValue draw = cbStringKeys.value("Draw");
      QJsonValue end = cbStringKeys.value("End");
      QJsonValue pot = cbBalances.value("0000000000000000000000000000000000000000000000000000000000000000");
      QJsonValue wager = cbStringKeys.value("Wager:");
      QJsonValue raised = cbStringKeys.value("Raised:");
      QJsonValue bet = cbStringKeys.value("Bet");

      ui->turnReadOut->setStyleSheet( "QTextBrowser{ background-color: rgb(85, 88, 93, 90); };" );
      ui->groupBoxP1->setStyleSheet( "QGroupBox{ border: 2px solid gray; border-radius: 5px; };" );
      ui->betSpinBox->setMinimum(ante.toDouble()/100000);
      ui->anteIsDSB->setValue(ante.toDouble()/100000);

      if(pot.toInt() == 0) /// Reset local player bet bool and blank display after hand ends
      {
          Hand::hasBet = false;
          blankDisplay();
      }

      if(Hand::hasBet == true)  /// Sets minimum bet to wager or raised depending on local bet bool
      {
          ui->betSpinBox->setMinimum(raised.toDouble()/100000);
      }else {
          ui->betSpinBox->setMinimum(wager.toDouble()/100000);
      }

      if(ui->playerId->value() == 1)  /// Owner table button control
      {
          ui->ownerPushButton->setEnabled(true);
          ui->playersComboBox->setEnabled(true);
          ui->payoutPushButton->setEnabled(true);
          ui->winnerComboBox->setEnabled(true);
          ui->shuffleButton->setEnabled(true);
          ui->entryPushButton->setEnabled(false);
      }

      if(ui->playerId->value()  > 1)  /// Player table button control
      {
          ui->ownerPushButton->setEnabled(false);
          ui->playersComboBox->setEnabled(false);
          ui->anteSpinBox->setEnabled(false);
          ui->winnerComboBox->setEnabled(false);
          ui->payoutPushButton->setEnabled(false);
          ui->shuffleButton->setEnabled(false);
          ui->entryPushButton->setEnabled(false);
      }

      if(seats == turn)   /// When full table, owner can start game
      {
          ui->entryPushButton->setEnabled(false);
          ui->dsbTurn->setValue(1);
          ui->dsbSeats->setValue(seats.toDouble());
          ui->dsbPot->setValue(pot.toDouble()/100000);

      }else {
          ui->dsbTurn->setValue(turn.toDouble()+1);
          ui->dsbSeats->setValue(seats.toDouble());
          ui->dsbPot->setValue(pot.toDouble()/100000);
      }





      if(ui->dsbTurn->value() == ui->playerId->value())   /// Local players turn button control
      {

          ui->dealHandPushButton->setEnabled(true);

          if(bet.toInt() >= 1)   /// Sets buttons when in bet
          {
              ui->dealHandPushButton->setEnabled(false);
              ui->checkButton->setText("Check");
              ui->checkButton->setEnabled(true);
              ui->betButton->setText("Bet");
              ui->betButton->setEnabled(true);

          }else {
              ui->betButton->setEnabled(false);
          }

          if(draw.toInt() == 1)   /// Local player draw button control
          {
              ui->drawPushButton->setEnabled(true);
              ui->drawComboBox->setEnabled(true);
              ui->dealHandPushButton->setEnabled(false);
          }else{

              ui->drawPushButton->setEnabled(false);
              ui->drawComboBox->setEnabled(false);
          }

          if(wager.toInt() > 0) /// Sets buttons when wager in play
          {
              ui->dealHandPushButton->setEnabled(false);
              ui->checkButton->setText("Fold");
              ui->checkButton->setEnabled(true);
              ui->betButton->setText("Call/Raise");
              ui->betButton->setEnabled(true);
              ui->drawPushButton->setEnabled(false);
              QString w = QString::number(wager.toDouble()/100000);
              ui->turnReadOut->setStyleSheet( "QTextBrowser{ background-color: rgb(56, 47, 165); };" );
              ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); };" );
              ui->turnReadOut->setText("Bet is "+w);
              ui->turnReadOut->insertPlainText("Your Turn    ");

          }else {
              ui->turnReadOut->setText("Your Turn");
              ui->turnReadOut->setStyleSheet( "QTextBrowser{ background-color: rgb(56, 47, 165); };" );
              ui->groupBoxP1->setStyleSheet( "QGroupBox{ border-color: rgb(56, 47, 165); };" );
          }

          if(raised.toDouble() > 0)  /// Sets button when raised in play
          {
              QString w = QString::number(wager.toDouble()/100000);
              QString r = QString::number(raised.toDouble()/100000);
              ui->betButton->setText("Call");
              ui->turnReadOut->setText("     Raised "+r);
              ui->turnReadOut->insertPlainText("Your Turn    ");
              ui->turnReadOut->insertPlainText("Bet is "+w);

          }

      }else {
          ui->dealHandPushButton->setEnabled(false);
          ui->checkButton->setEnabled(false);
          ui->betButton->setEnabled(false);
          ui->drawPushButton->setEnabled(false);
          QString p = QString::number(ui->dsbTurn->value());
          ui->turnReadOut->setText("Player "+p+"'s Turn");

      }

      if(end.toInt() == 1)   /// End game, show all hands
      {
          fetchResultsData();
          ui->betButton->setEnabled(false);
          ui->drawPushButton->setEnabled(false);
          ui->drawComboBox->setEnabled(false);
          ui->dealHandPushButton->setEnabled(false);
          ui->turnReadOut->setText("Hand Over, payout");
      }

      if(Hand::endSignal == true)  /// Local end signal, all players have folded
      {
          ui->turnReadOut->setText("Players have all folded, payout");
          ui->betButton->setEnabled(false);
          ui->drawPushButton->setEnabled(false);
          ui->drawComboBox->setEnabled(false);
          ui->dealHandPushButton->setEnabled(false);
      }

    }
    return 0;
}


void MainWindow::showGameKey(void)       /// Shows game key
    {
        CURL *curlShowGameKey;
        CURLcode res;
        string keyReadBuffer;
        char error[CURL_ERROR_SIZE];

        QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
        string addThis = parts.toStdString();
        const char *postthis = addThis.c_str();

        QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
        string dStr = daemonAddress.toStdString();
        const char *kCh = dStr.c_str ();

        loginInfo();
        const char *loginCh = rpc::rpcLogin.c_str ();

        curlShowGameKey = curl_easy_init();

        if(curlShowGameKey) {
          struct curl_slist *headers = NULL;
          /// Add request headers
          headers = curl_slist_append(headers, "Accept: application/json");
          headers = curl_slist_append(headers, "Content-Type: application/json");
          headers = curl_slist_append(headers, "charset: utf-8");
          /// cUrl options
          curl_easy_setopt(curlShowGameKey, CURLOPT_HTTPHEADER, headers);
          curl_easy_setopt(curlShowGameKey, CURLOPT_URL, kCh);
          curl_easy_setopt(curlShowGameKey, CURLOPT_VERBOSE, 1L);
          curl_easy_setopt(curlShowGameKey, CURLOPT_ERRORBUFFER, error);
          curl_easy_setopt(curlShowGameKey, CURLOPT_USERPWD, loginCh);
          curl_easy_setopt(curlShowGameKey, CURLOPT_POSTFIELDS, postthis);
          curl_easy_setopt(curlShowGameKey, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
          curl_easy_setopt(curlShowGameKey, CURLOPT_WRITEFUNCTION, WriteCallback);
          curl_easy_setopt(curlShowGameKey, CURLOPT_WRITEDATA, &keyReadBuffer);

          res = curl_easy_perform(curlShowGameKey);
          curl_easy_cleanup(curlShowGameKey);

          QByteArray br = keyReadBuffer.c_str();
          QJsonDocument cbDoc = QJsonDocument::fromJson(br);
          QJsonObject cbObj = cbDoc.object();
          QJsonObject cbResults = cbObj["result"].toObject();
          QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
          QJsonValue gameKey = cbStringKeys.value("GameKey:");

          std::cout << keyReadBuffer << std::endl;
          ui->gameKeyLineEdit->setText(gameKey.toString());

    }
}


int MainWindow::checkDaemon(void)       /// Check connection to daemon
{
    CURL *curlDaemonCheck;
    CURLcode res;
    string daemonReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":false}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlDaemonCheck = curl_easy_init();

    if(curlDaemonCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlDaemonCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_URL, dCh);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEDATA, &daemonReadBuffer);

      res = curl_easy_perform(curlDaemonCheck);
      curl_easy_cleanup(curlDaemonCheck);

      QByteArray br = daemonReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue okCheck = cbResults["status"];

      std::cout << daemonReadBuffer << std::endl;

      if(okCheck == "OK")
      {
          ui->daemonConnectedBox->setChecked(true);
          ui->logTextBrowser->setText("Daemon Connected");
          std::cout << "Daemon Connected" << std::endl;     /// Connected message

      }else {

          ui->daemonConnectedBox->setChecked(false);
          ui->logTextBrowser->setText("Daemon Not Connected");
          std::cout << "Daemon Not Connected" << std::endl;  /// Not connected
      }

    }
    return 0;

}


void MainWindow::verifyGameKey(void)       /// Checks game key and set player Id
{
    CURL *curlKeyCheck;
    CURLcode res;
    string cKeyReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *ckCh = dStr.c_str ();

    loginInfo();
    const char *loginCh = rpc::rpcLogin.c_str ();

    curlKeyCheck = curl_easy_init();

    if(curlKeyCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlKeyCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlKeyCheck, CURLOPT_URL, ckCh);
      curl_easy_setopt(curlKeyCheck, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlKeyCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlKeyCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlKeyCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlKeyCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlKeyCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlKeyCheck, CURLOPT_WRITEDATA, &cKeyReadBuffer);

      res = curl_easy_perform(curlKeyCheck);
      curl_easy_cleanup(curlKeyCheck);

      QByteArray br = cKeyReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue gameKey = cbStringKeys.value("GameKey:");
      QJsonValue turn = cbStringKeys.value("Player:");

      QString gameKeyInput = ui->gameKeyLineEdit->text();

      if(gameKeyInput == gameKey.toString()){  /// If game key is valid

        std::cout << cKeyReadBuffer << std::endl;

        ui->entryPushButton->setEnabled(false);
        ui->gameKeyPushButton->setEnabled(false);
        if(ui->playerId->value() == 0){
        ui->playerId->setValue(turn.toDouble());    /// Set playerId
        }else
            return;
      }else

        ui->gameKeyLineEdit->setText("Invalid Game Key");
    }
}


int MainWindow::fetchHandData(void)  /// Gets and displays local player cards & get fold status
{
    CURL *curlHandData;
    CURLcode res;
    string handReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis2 = addThis.c_str();

    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *fhdCh = dStr.c_str ();

    curlHandData = curl_easy_init();

    if(curlHandData) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlHandData, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlHandData, CURLOPT_URL, fhdCh);
      curl_easy_setopt(curlHandData, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlHandData, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlHandData, CURLOPT_POSTFIELDS, postthis2);
      curl_easy_setopt(curlHandData, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis2));
      curl_easy_setopt(curlHandData, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlHandData, CURLOPT_WRITEDATA, &handReadBuffer);

      res = curl_easy_perform(curlHandData);
      curl_easy_cleanup(curlHandData);

      QByteArray br = handReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue seats = cbStringKeys.value("Seats at Table:");
      QJsonValue p1Fold = cbStringKeys.value("0F");
      QJsonValue p2Fold = cbStringKeys.value("1F");
      QJsonValue p3Fold = cbStringKeys.value("2F");
      QJsonValue p4Fold = cbStringKeys.value("3F");
      QJsonValue p5Fold = cbStringKeys.value("4F");

      if(p1Fold.toInt() == 1)  /// Sets fold check boxes
      {
          ui->p1CheckBox->setChecked(true);
      }else {
         ui->p1CheckBox->setChecked(false);
      }

      if(p2Fold.toInt() == 1)
      {
          ui->p2CheckBox->setChecked(true);
      }else {
          ui->p2CheckBox->setChecked(false);
      }

      if(p3Fold.toInt() == 1)
      {
          ui->p3CheckBox->setChecked(true);
      }else {
          ui->p3CheckBox->setChecked(false);
      }

      if(p4Fold.toInt() == 1)
      {
          ui->p4CheckBox->setChecked(true);
      }else {
          ui->p4CheckBox->setChecked(false);
      }

      if(p5Fold.toInt() == 1)
      {
          ui->p5CheckBox->setChecked(true);
      }else {
          ui->p5CheckBox->setChecked(false);
      }


      int checkPlayerId = ui->playerId->value();
      QString handId = QString::number(checkPlayerId);


      if(p1Fold.toInt() == 1 && checkPlayerId == 1)   /// Blank display when folded
      {
          blankDisplay();
      }

      if(p2Fold.toInt() == 1 && checkPlayerId == 2)
      {
          blankDisplay();
      }

      if(p3Fold.toInt() == 1 && checkPlayerId == 3)
      {
          blankDisplay();
      }

      if(p4Fold.toInt() == 1 && checkPlayerId == 4)
      {
          blankDisplay();
      }

      if(p5Fold.toInt() == 1 && checkPlayerId == 5)
      {
          blankDisplay();
      }

      int endCheck = p1Fold.toInt()+p2Fold.toInt()+p3Fold.toInt()+p4Fold.toInt()+p5Fold.toInt();
      int end = seats.toInt()-1;

      if(endCheck == end)   /// Local end signal
      {
        Hand::endSignal = true;
      }else {

        Hand::endSignal = false;
      }
            /// Display local cards
            QJsonValue card1 = cbStringKeys.value("Player"+handId.toUtf8()+"card1");
            QJsonValue card2 = cbStringKeys.value("Player"+handId.toUtf8()+"card2");
            QJsonValue card3 = cbStringKeys.value("Player"+handId.toUtf8()+"card3");
            QJsonValue card4 = cbStringKeys.value("Player"+handId.toUtf8()+"card4");
            QJsonValue card5 = cbStringKeys.value("Player"+handId.toUtf8()+"card5");

            int one = card1.toInt();
            int two = card2.toInt();
            int three = card3.toInt();
            int four = card4.toInt();
            int five = card5.toInt();

            displayCardOne(one);
            displayCardTwo(two);
            displayCardThree(three);
            displayCardFour(four);
            displayCardFive(five);
    }

    return 0;
}


int MainWindow::fetchResultsData(void)  /// Gets all players cards and shows to all players
{
    CURL *curlResult;
    CURLcode res;
    string resultReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString daemonAddress =  ui->daemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *rCh = dStr.c_str ();

    curlResult = curl_easy_init();

    if(curlResult) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlResult, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlResult, CURLOPT_URL, rCh);
      curl_easy_setopt(curlResult, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlResult, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlResult, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlResult, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlResult, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlResult, CURLOPT_WRITEDATA, &resultReadBuffer);

      res = curl_easy_perform(curlResult);
      curl_easy_cleanup(curlResult);

      QByteArray br = resultReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue seats = cbStringKeys.value("Seats at Table:");
      QJsonValue p1Fold = cbStringKeys.value("0F");
      QJsonValue p2Fold = cbStringKeys.value("1F");
      QJsonValue p3Fold = cbStringKeys.value("2F");
      QJsonValue p4Fold = cbStringKeys.value("3F");
      QJsonValue p5Fold = cbStringKeys.value("4F");
      QJsonValue playerNumber = cbStringKeys.value("Player:");


            QJsonValue onecard1 = cbStringKeys.value("Player1card1");
            QJsonValue onecard2 = cbStringKeys.value("Player1card2");
            QJsonValue onecard3 = cbStringKeys.value("Player1card3");
            QJsonValue onecard4 = cbStringKeys.value("Player1card4");
            QJsonValue onecard5 = cbStringKeys.value("Player1card5");

            QJsonValue twocard1 = cbStringKeys.value("Player2card1");
            QJsonValue twocard2 = cbStringKeys.value("Player2card2");
            QJsonValue twocard3 = cbStringKeys.value("Player2card3");
            QJsonValue twocard4 = cbStringKeys.value("Player2card4");
            QJsonValue twocard5 = cbStringKeys.value("Player2card5");

            QJsonValue threecard1 = cbStringKeys.value("Player3card1");
            QJsonValue threecard2 = cbStringKeys.value("Player3card2");
            QJsonValue threecard3 = cbStringKeys.value("Player3card3");
            QJsonValue threecard4 = cbStringKeys.value("Player3card4");
            QJsonValue threecard5 = cbStringKeys.value("Player3card5");

            QJsonValue fourcard1 = cbStringKeys.value("Player4card1");
            QJsonValue fourcard2 = cbStringKeys.value("Player4card2");
            QJsonValue fourcard3 = cbStringKeys.value("Player4card3");
            QJsonValue fourcard4 = cbStringKeys.value("Player4card4");
            QJsonValue fourcard5 = cbStringKeys.value("Player4card5");

            QJsonValue fivecard1 = cbStringKeys.value("Player5card1");
            QJsonValue fivecard2 = cbStringKeys.value("Player5card2");
            QJsonValue fivecard3 = cbStringKeys.value("Player5card3");
            QJsonValue fivecard4 = cbStringKeys.value("Player5card4");
            QJsonValue fivecard5 = cbStringKeys.value("Player5card5");

            int oneone = onecard1.toInt();
            int onetwo = onecard2.toInt();
            int onethree = onecard3.toInt();
            int onefour = onecard4.toInt();
            int onefive = onecard5.toInt();

            int twoone = twocard1.toInt();
            int twotwo = twocard2.toInt();
            int twothree = twocard3.toInt();
            int twofour = twocard4.toInt();
            int twofive = twocard5.toInt();

            int threeone = threecard1.toInt();
            int threetwo = threecard2.toInt();
            int threethree = threecard3.toInt();
            int threefour = threecard4.toInt();
            int threefive = threecard5.toInt();

            int fourone = fourcard1.toInt();
            int fourtwo = fourcard2.toInt();
            int fourthree = fourcard3.toInt();
            int fourfour = fourcard4.toInt();
            int fourfive = fourcard5.toInt();

            int fiveone = fivecard1.toInt();
            int fivetwo = fivecard2.toInt();
            int fivethree = fivecard3.toInt();
            int fivefour = fivecard4.toInt();
            int fivefive = fivecard5.toInt();

            if(Hand::endSignal == false)
            {
                switch (seats.toInt()){

                case 2:
                    ui->logTextBrowser->setText("Player1 Has: "+findCards(oneone)+" "+findCards(onetwo)+" "+findCards(onethree)+" "+findCards(onefour)+" "+findCards(onefive));
                    ui->logTextBrowser->append("Player2 Has:"+findCards(twoone)+" "+findCards(twotwo)+" "+findCards(twothree)+" "+findCards(twofour)+" "+findCards(twofive));
                    break;

                case 3:
                    ui->logTextBrowser->setText("Player1 Has: "+findCards(oneone)+" "+findCards(onetwo)+" "+findCards(onethree)+" "+findCards(onefour)+" "+findCards(onefive));
                    ui->logTextBrowser->append("Player2 Has:"+findCards(twoone)+" "+findCards(twotwo)+" "+findCards(twothree)+" "+findCards(twofour)+" "+findCards(twofive));
                    ui->logTextBrowser->append("Player3 Has:"+findCards(threeone)+" "+findCards(threetwo)+" "+findCards(threethree)+" "+findCards(threefour)+" "+findCards(threefive));
                    break;

                case 4:
                    ui->logTextBrowser->setText("Player1 Has: "+findCards(oneone)+" "+findCards(onetwo)+" "+findCards(onethree)+" "+findCards(onefour)+" "+findCards(onefive));
                    ui->logTextBrowser->append("Player2 Has:"+findCards(twoone)+" "+findCards(twotwo)+" "+findCards(twothree)+" "+findCards(twofour)+" "+findCards(twofive));
                    ui->logTextBrowser->append("Player3 Has:"+findCards(threeone)+" "+findCards(threetwo)+" "+findCards(threethree)+" "+findCards(threefour)+" "+findCards(threefive));
                    ui->logTextBrowser->append("Player4 Has:"+findCards(fourone)+" "+findCards(fourtwo)+" "+findCards(fourthree)+" "+findCards(fourfour)+" "+findCards(fourfive));
                    break;

                case 5:
                    ui->logTextBrowser->setText("Player1 Has: "+findCards(oneone)+" "+findCards(onetwo)+" "+findCards(onethree)+" "+findCards(onefour)+" "+findCards(onefive));
                    ui->logTextBrowser->append("Player2 Has:"+findCards(twoone)+" "+findCards(twotwo)+" "+findCards(twothree)+" "+findCards(twofour)+" "+findCards(twofive));
                    ui->logTextBrowser->append("Player3 Has:"+findCards(threeone)+" "+findCards(threetwo)+" "+findCards(threethree)+" "+findCards(threefour)+" "+findCards(threefive));
                    ui->logTextBrowser->append("Player4 Has:"+findCards(fourone)+" "+findCards(fourtwo)+" "+findCards(fourthree)+" "+findCards(fourfour)+" "+findCards(fourfive));
                    ui->logTextBrowser->append("Player5 Has:"+findCards(fiveone)+" "+findCards(fivetwo)+" "+findCards(fivethree)+" "+findCards(fivefour)+" "+findCards(fivefive));
                    break;

                }

           }
    }
    return 0;
}


void MainWindow::blankDisplay()  /// Shows null cards when not playing
{
    ui->localPlayerCard1->setPixmap(QPixmap(":/images/card53.png"));
    ui->localPlayerCard2->setPixmap(QPixmap(":/images/card53.png"));
    ui->localPlayerCard3->setPixmap(QPixmap(":/images/card53.png"));
    ui->localPlayerCard4->setPixmap(QPixmap(":/images/card53.png"));
    ui->localPlayerCard5->setPixmap(QPixmap(":/images/card53.png"));
}


QString MainWindow::findCards(int card) /// To show all hand results at end
{
    QString cardEquiv;
    switch (card){
    case 1: cardEquiv = "🂡"; break;
    case 2: cardEquiv = "🂢"; break;
    case 3: cardEquiv = "🂣"; break;
    case 4: cardEquiv = "🂤"; break;
    case 5: cardEquiv = "🂥"; break;
    case 6: cardEquiv = "🂦"; break;
    case 7: cardEquiv = "🂧"; break;
    case 8: cardEquiv = "🂨"; break;
    case 9: cardEquiv = "🂩"; break;
    case 10: cardEquiv = "🂪"; break;
    case 11: cardEquiv = "🂫"; break;
    case 12: cardEquiv = "🂭"; break;
    case 13: cardEquiv = "🂮"; break;
    case 14: cardEquiv = "🂱"; break;
    case 15: cardEquiv = "🂲"; break;
    case 16: cardEquiv = "🂳"; break;
    case 17: cardEquiv = "🂴"; break;
    case 18: cardEquiv = "🂵"; break;
    case 19: cardEquiv = "🂶"; break;
    case 20: cardEquiv = "🂷"; break;
    case 21: cardEquiv = "🂸"; break;
    case 22: cardEquiv = "🂹"; break;
    case 23: cardEquiv = "🂺"; break;
    case 24: cardEquiv = "🂻"; break;
    case 25: cardEquiv = "🂽"; break;
    case 26: cardEquiv = "🂾"; break;
    case 27: cardEquiv = "🃑"; break;
    case 28: cardEquiv = "🃒"; break;
    case 29: cardEquiv = "🃓"; break;
    case 30: cardEquiv = "🃔"; break;
    case 31: cardEquiv = "🃕"; break;
    case 32: cardEquiv = "🃖"; break;
    case 33: cardEquiv = "🃗"; break;
    case 34: cardEquiv = "🃘"; break;
    case 35: cardEquiv = "🃙"; break;
    case 36: cardEquiv = "🃚"; break;
    case 37: cardEquiv = "🃛"; break;
    case 38: cardEquiv = "🃝"; break;
    case 39: cardEquiv = "🃞"; break;
    case 40: cardEquiv = "🃁"; break;
    case 41: cardEquiv = "🃂"; break;
    case 42: cardEquiv = "🃃"; break;
    case 43: cardEquiv = "🃄"; break;
    case 44: cardEquiv = "🃅"; break;
    case 45: cardEquiv = "🃆"; break;
    case 46: cardEquiv = "🃇"; break;
    case 47: cardEquiv = "🃈"; break;
    case 48: cardEquiv = "🃉"; break;
    case 49: cardEquiv = "🃊"; break;
    case 50: cardEquiv = "🃋"; break;
    case 51: cardEquiv = "🃍"; break;
    case 52: cardEquiv = "🃎"; break;
    }
    return cardEquiv;
}


void MainWindow::displayCardOne(int card) /// Displays local card one
{
    switch (card){
    case 1: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card1.png")); break;
    case 2: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card2.png")); break;
    case 3: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card3.png")); break;
    case 4: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card4.png")); break;
    case 5: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card5.png")); break;
    case 6: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card6.png"));; break;
    case 7: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card7.png")); break;
    case 8: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card8.png")); break;
    case 9: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card9.png")); break;
    case 10: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card10.png")); break;
    case 11: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card11.png")); break;
    case 12: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card12.png")); break;
    case 13: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card13.png")); break;
    case 14: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card14.png")); break;
    case 15: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card15.png")); break;
    case 16: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card16.png")); break;
    case 17: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card17.png")); break;
    case 18: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card18.png")); break;
    case 19: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card19.png")); break;
    case 20: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card20.png")); break;
    case 21: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card21.png")); break;
    case 22: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card22.png")); break;
    case 23: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card23.png")); break;
    case 24: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card24.png")); break;
    case 25: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card25.png")); break;
    case 26: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card26.png")); break;
    case 27: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card27.png")); break;
    case 28: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card28.png")); break;
    case 29: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card29.png")); break;
    case 30: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card30.png")); break;
    case 31: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card31.png")); break;
    case 32: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card32.png")); break;
    case 33: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card33.png")); break;
    case 34: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card34.png")); break;
    case 35: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card35.png")); break;
    case 36: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card36.png")); break;
    case 37: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card37.png")); break;
    case 38: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card38.png")); break;
    case 39: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card39.png")); break;
    case 40: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card40.png")); break;
    case 41: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card41.png")); break;
    case 42: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card42.png")); break;
    case 43: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card43.png")); break;
    case 44: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card44.png")); break;
    case 45: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card45.png")); break;
    case 46: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card46.png")); break;
    case 47: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card47.png")); break;
    case 48: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card48.png")); break;
    case 49: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card49.png")); break;
    case 50: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card50.png")); break;
    case 51: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card51.png")); break;
    case 52: ui->localPlayerCard1->setPixmap(QPixmap(":/images/card52.png")); break;
    }

}


void MainWindow::displayCardTwo(int card)  /// Displays local card two
{
    switch (card){
    case 1: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card1.png")); break;
    case 2: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card2.png")); break;
    case 3: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card3.png")); break;
    case 4: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card4.png")); break;
    case 5: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card5.png")); break;
    case 6: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card6.png"));; break;
    case 7: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card7.png")); break;
    case 8: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card8.png")); break;
    case 9: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card9.png")); break;
    case 10: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card10.png")); break;
    case 11: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card11.png")); break;
    case 12: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card12.png")); break;
    case 13: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card13.png")); break;
    case 14: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card14.png")); break;
    case 15: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card15.png")); break;
    case 16: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card16.png")); break;
    case 17: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card17.png")); break;
    case 18: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card18.png")); break;
    case 19: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card19.png")); break;
    case 20: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card20.png")); break;
    case 21: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card21.png")); break;
    case 22: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card22.png")); break;
    case 23: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card23.png")); break;
    case 24: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card24.png")); break;
    case 25: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card25.png")); break;
    case 26: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card26.png")); break;
    case 27: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card27.png")); break;
    case 28: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card28.png")); break;
    case 29: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card29.png")); break;
    case 30: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card30.png")); break;
    case 31: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card31.png")); break;
    case 32: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card32.png")); break;
    case 33: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card33.png")); break;
    case 34: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card34.png")); break;
    case 35: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card35.png")); break;
    case 36: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card36.png")); break;
    case 37: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card37.png")); break;
    case 38: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card38.png")); break;
    case 39: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card39.png")); break;
    case 40: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card40.png")); break;
    case 41: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card41.png")); break;
    case 42: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card42.png")); break;
    case 43: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card43.png")); break;
    case 44: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card44.png")); break;
    case 45: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card45.png")); break;
    case 46: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card46.png")); break;
    case 47: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card47.png")); break;
    case 48: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card48.png")); break;
    case 49: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card49.png")); break;
    case 50: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card50.png")); break;
    case 51: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card51.png")); break;
    case 52: ui->localPlayerCard2->setPixmap(QPixmap(":/images/card52.png")); break;
    }

}


void MainWindow::displayCardThree(int card)    /// Displays local card three
{
    switch (card){
    case 1: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card1.png")); break;
    case 2: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card2.png")); break;
    case 3: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card3.png")); break;
    case 4: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card4.png")); break;
    case 5: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card5.png")); break;
    case 6: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card6.png"));; break;
    case 7: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card7.png")); break;
    case 8: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card8.png")); break;
    case 9: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card9.png")); break;
    case 10: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card10.png")); break;
    case 11: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card11.png")); break;
    case 12: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card12.png")); break;
    case 13: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card13.png")); break;
    case 14: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card14.png")); break;
    case 15: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card15.png")); break;
    case 16: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card16.png")); break;
    case 17: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card17.png")); break;
    case 18: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card18.png")); break;
    case 19: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card19.png")); break;
    case 20: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card20.png")); break;
    case 21: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card21.png")); break;
    case 22: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card22.png")); break;
    case 23: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card23.png")); break;
    case 24: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card24.png")); break;
    case 25: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card25.png")); break;
    case 26: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card26.png")); break;
    case 27: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card27.png")); break;
    case 28: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card28.png")); break;
    case 29: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card29.png")); break;
    case 30: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card30.png")); break;
    case 31: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card31.png")); break;
    case 32: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card32.png")); break;
    case 33: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card33.png")); break;
    case 34: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card34.png")); break;
    case 35: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card35.png")); break;
    case 36: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card36.png")); break;
    case 37: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card37.png")); break;
    case 38: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card38.png")); break;
    case 39: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card39.png")); break;
    case 40: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card40.png")); break;
    case 41: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card41.png")); break;
    case 42: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card42.png")); break;
    case 43: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card43.png")); break;
    case 44: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card44.png")); break;
    case 45: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card45.png")); break;
    case 46: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card46.png")); break;
    case 47: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card47.png")); break;
    case 48: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card48.png")); break;
    case 49: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card49.png")); break;
    case 50: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card50.png")); break;
    case 51: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card51.png")); break;
    case 52: ui->localPlayerCard3->setPixmap(QPixmap(":/images/card52.png")); break;
    }
}


void MainWindow::displayCardFour(int card)   ///  Displays local card four
{
    switch (card){
    case 1: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card1.png")); break;
    case 2: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card2.png")); break;
    case 3: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card3.png")); break;
    case 4: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card4.png")); break;
    case 5: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card5.png")); break;
    case 6: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card6.png"));; break;
    case 7: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card7.png")); break;
    case 8: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card8.png")); break;
    case 9: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card9.png")); break;
    case 10: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card10.png")); break;
    case 11: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card11.png")); break;
    case 12: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card12.png")); break;
    case 13: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card13.png")); break;
    case 14: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card14.png")); break;
    case 15: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card15.png")); break;
    case 16: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card16.png")); break;
    case 17: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card17.png")); break;
    case 18: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card18.png")); break;
    case 19: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card19.png")); break;
    case 20: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card20.png")); break;
    case 21: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card21.png")); break;
    case 22: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card22.png")); break;
    case 23: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card23.png")); break;
    case 24: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card24.png")); break;
    case 25: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card25.png")); break;
    case 26: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card26.png")); break;
    case 27: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card27.png")); break;
    case 28: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card28.png")); break;
    case 29: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card29.png")); break;
    case 30: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card30.png")); break;
    case 31: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card31.png")); break;
    case 32: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card32.png")); break;
    case 33: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card33.png")); break;
    case 34: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card34.png")); break;
    case 35: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card35.png")); break;
    case 36: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card36.png")); break;
    case 37: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card37.png")); break;
    case 38: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card38.png")); break;
    case 39: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card39.png")); break;
    case 40: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card40.png")); break;
    case 41: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card41.png")); break;
    case 42: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card42.png")); break;
    case 43: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card43.png")); break;
    case 44: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card44.png")); break;
    case 45: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card45.png")); break;
    case 46: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card46.png")); break;
    case 47: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card47.png")); break;
    case 48: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card48.png")); break;
    case 49: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card49.png")); break;
    case 50: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card50.png")); break;
    case 51: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card51.png")); break;
    case 52: ui->localPlayerCard4->setPixmap(QPixmap(":/images/card52.png")); break;
    }

}


void MainWindow::displayCardFive(int card)   ///  Displays local card five
{
    switch (card){
    case 1: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card1.png")); break;
    case 2: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card2.png")); break;
    case 3: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card3.png")); break;
    case 4: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card4.png")); break;
    case 5: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card5.png")); break;
    case 6: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card6.png"));; break;
    case 7: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card7.png")); break;
    case 8: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card8.png")); break;
    case 9: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card9.png")); break;
    case 10: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card10.png")); break;
    case 11: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card11.png")); break;
    case 12: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card12.png")); break;
    case 13: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card13.png")); break;
    case 14: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card14.png")); break;
    case 15: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card15.png")); break;
    case 16: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card16.png")); break;
    case 17: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card17.png")); break;
    case 18: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card18.png")); break;
    case 19: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card19.png")); break;
    case 20: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card20.png")); break;
    case 21: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card21.png")); break;
    case 22: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card22.png")); break;
    case 23: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card23.png")); break;
    case 24: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card24.png")); break;
    case 25: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card25.png")); break;
    case 26: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card26.png")); break;
    case 27: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card27.png")); break;
    case 28: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card28.png")); break;
    case 29: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card29.png")); break;
    case 30: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card30.png")); break;
    case 31: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card31.png")); break;
    case 32: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card32.png")); break;
    case 33: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card33.png")); break;
    case 34: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card34.png")); break;
    case 35: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card35.png")); break;
    case 36: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card36.png")); break;
    case 37: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card37.png")); break;
    case 38: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card38.png")); break;
    case 39: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card39.png")); break;
    case 40: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card40.png")); break;
    case 41: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card41.png")); break;
    case 42: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card42.png")); break;
    case 43: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card43.png")); break;
    case 44: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card44.png")); break;
    case 45: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card45.png")); break;
    case 46: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card46.png")); break;
    case 47: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card47.png")); break;
    case 48: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card48.png")); break;
    case 49: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card49.png")); break;
    case 50: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card50.png")); break;
    case 51: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card51.png")); break;
    case 52: ui->localPlayerCard5->setPixmap(QPixmap(":/images/card52.png")); break;
    }

}
