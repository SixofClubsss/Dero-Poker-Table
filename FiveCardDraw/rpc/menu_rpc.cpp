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
#include "menu.h"
#include "ui_menu.h"
#include "rpc/rpc.h"

bool Menu::daemonConnected;
bool Menu::walletConnected;
bool Menu::dReams;


void Menu::loginInfo()   /// Used to get wallet login info for wallet functions
{
    Menu::userInfo = ui->userpassInput->text();
    string userpassStr = Menu::userInfo.toStdString();
    rpc::rpcLogin = userpassStr;
}


void Menu::delay()            /// Delay to ensure mulitple calls get in different blocks
{
    QTime dieTime= QTime::currentTime().addSecs(36);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


int Menu::checkDaemon()       /// Check connection to daemon
{
    CURL *curlDaemonCheck;   /// Set up cUrl
    CURLcode res;
    string daemonReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":false}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();   /// Player dameon address from menu
    const char *dCh = dStr.c_str();

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
      curl_easy_setopt(curlDaemonCheck, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlDaemonCheck, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for windows SSL disable*
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDaemonCheck, CURLOPT_WRITEDATA, &daemonReadBuffer);

      res = curl_easy_perform(curlDaemonCheck);              /// Preform cUrl and clean up
      curl_easy_cleanup(curlDaemonCheck);

      QByteArray br = daemonReadBuffer.c_str();             /// Get cUrl results into QByteArray
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue okCheck = cbResults["status"];

      if(okCheck == "OK"){
          ui->daemonConnectedBox->setChecked(true);
          ui->menuTextBrowser->setText("Daemon Connected");     /// Connected message
          ui->findTablesButton->setEnabled(true);
          Menu::daemonConnected = true;
      }else {
          ui->daemonConnectedBox->setChecked(false);   
          ui->menuTextBrowser->setText("Daemon Not Connected"); /// Not connected
          ui->findTablesButton->setEnabled(false);
      }

    }
    return 0;

}


int Menu::checkWallet()  /// Echo blockchain to confirm wallet is connected
{
    CURL *curlWalletCheck;
    CURLcode res;
    string readBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\":\"2.0\",\"id\":\"1\",\"method\":\"Echo\",\"params\":[\"Hello\", \"World\", \"!\"]}";

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

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
      curl_easy_setopt(curlWalletCheck, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlWalletCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlWalletCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlWalletCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlWalletCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlWalletCheck, CURLOPT_WRITEDATA, &readBuffer);
      res = curl_easy_perform(curlWalletCheck);
      curl_easy_cleanup(curlWalletCheck);

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonValue okCheck = cbObj["result"];

      if(okCheck == "WALLET Hello World !"){
          ui->walletConnectedBox->setChecked(true);
          ui->menuTextBrowser->insertPlainText("Wallet Connected\n");
          Menu::walletConnected = true;

          QFile lockedFile("contract/FiveCard.enc");
          lockedFile.open(QIODevice::ReadOnly);

              if(lockedFile.exists()){
                  ui->getTableButton->setEnabled(true);
              }

          QFile contractFile("contract/FiveCard.bas");
          contractFile.open(QIODevice::ReadOnly);

              if(contractFile.exists()){            /// Set unlock & new table buttons
                  ui->getTableButton->setEnabled(false);
                  ui->newTableButton->setEnabled(true);
              }else {
                  ui->newTableButton->setEnabled(false);
              }

      }else {
          ui->walletConnectedBox->setChecked(false);
          ui->menuTextBrowser->setText("Wallet Not Connected");
          ui->getTableButton->setEnabled(false);
      }

    }
    return 0;
}


int Menu::checkContract()       /// Check if table is valid
{
    CURL *curlContract;
    CURLcode res;
    string contractReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *dCh = dStr.c_str();

    curlContract = curl_easy_init();

    if(curlContract) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlContract, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlContract, CURLOPT_URL, dCh);
      curl_easy_setopt(curlContract, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlContract, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlContract, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlContract, CURLOPT_POSTFIELDS, postthis);
      /// curl_easy_setopt(curlContract, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for windows SSL disable*
      curl_easy_setopt(curlContract, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlContract, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlContract, CURLOPT_WRITEDATA, &contractReadBuffer);

      res = curl_easy_perform(curlContract);
      curl_easy_cleanup(curlContract);

      QByteArray br = contractReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue tableOwner = cbStringKeys.value("owner:");
      QJsonValue tableOwnerId = cbStringKeys.value("Player1 ID:");
      QJsonValue cardsInDeck = cbStringKeys.value("Deck Count:");

      if(tableOwner.isString() && cardsInDeck.toInt() >= 1){                /// Checks if table has valid "owner:" key
          ui->contractCheckBox->setChecked(true);
          ui->menuTextBrowser->setText("Connected to Contract "+Menu::contractAddress);
          QFile contractFile("contract/FiveCard.bas");
          contractFile.open(QIODevice::ReadOnly);
          if(contractFile.exists()){
              if(contractFile.size() > 18000){
                ui->ownerGroupBox->setEnabled(true);
              }
          }

      }else {
          ui->contractCheckBox->setChecked(false);
          ui->menuTextBrowser->setText("Contract is Not Valid");
          ui->ownerGroupBox->setEnabled(false);
      }

      if(tableOwnerId == rpc::IdHash ){             /// If user is owner of table
          ui->cleanTableButton->setEnabled(true);
          ui->menuTextBrowser->setText("You Own Table "+Menu::contractAddress+"\n");
          ui->autoPayRButton->setEnabled(true);
          ui->listTableButton->setEnabled(true);
          ui->delistTableButton->setEnabled(true);
      }else {
          ui->cleanTableButton->setEnabled(false);
          ui->autoPayRButton->setEnabled(true);
          ui->listTableButton->setEnabled(false);
          ui->delistTableButton->setEnabled(false);
      }

    }
    return 0;

}


int Menu::checkAddress()  /// Gets player wallet address and hashes to get player ID
{
    CURL *curlAddressCheck;
    CURLcode res;
    string checkAddressReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\": \"2.0\",\"id\": \"1\",\"method\": \"GetAddress\"}";

    string pStr = rpc::playerAddress.toStdString();
    const char *pCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlAddressCheck = curl_easy_init();

    if(curlAddressCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlAddressCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlAddressCheck, CURLOPT_URL, pCh);
      curl_easy_setopt(curlAddressCheck, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlAddressCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlAddressCheck, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlAddressCheck, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlAddressCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlAddressCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlAddressCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlAddressCheck, CURLOPT_WRITEDATA, &checkAddressReadBuffer);

      res = curl_easy_perform(curlAddressCheck);
      curl_easy_cleanup(curlAddressCheck);

      QByteArray br = checkAddressReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue address = cbResults.value("address");

      if(address.isString()){                   /// Stores address hash to verify player Id
          rpc::IdHash = QString(QCryptographicHash::hash((address.toString().toUtf8()),QCryptographicHash::Sha256).toHex());
          ui->menuTextBrowser->setText("Your Player ID is: "+rpc::IdHash);
      }

    }
    return 0;
}


int Menu::setTable()      /// Owner set table player limit and ante
{
    CURL *curlSetTable;
    CURLcode res;
    string setTableReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString playerLimit = QString::number(ui->playersComboBox->currentIndex());
    QString anteAmount = QString::number(ui->anteSpinBox->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}] , \"fees\":500 , \"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"SetTable\"},{\"name\":\"seats\",\"datatype\":\"U\",\"value\":"+playerLimit+" },{\"name\":\"ante\",\"datatype\":\"U\",\"value\":"+anteAmount+" }, {\"name\":\"address\",\"datatype\":\"H\",\"value\":\""+rpc::IdHash+"\" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

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
      curl_easy_setopt(curlSetTable, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlSetTable, CURLOPT_CONNECTTIMEOUT, 4L);
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

      if(setTableTxid.isString()){
          ui->menuTextBrowser->setText("Set Table TXID: "+setTableTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No Set Table TXID");
      }

    }
    return 0;
}


int Menu::cleanTable()      /// Clean table function to withdraw any funds at table and shuffle deck, requires a seats at table to be present to execute
{
    CURL *curlCleanTable;
    CURLcode res;
    string cleanTableReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString playerLimit = QString::number(ui->playersComboBox->currentIndex());
    QString amount = QString::number(ui->anteSpinBox->value()*100000);
    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\": [{\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\"}], \"fees\":500 ,\"scid\":\""+Menu::contractAddress+"\", \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"CleanTable\"},{\"name\":\"amount\",\"datatype\":\"U\",\"value\":"+amount+" }] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlCleanTable = curl_easy_init();

    if(curlCleanTable) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlCleanTable, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlCleanTable, CURLOPT_URL, stCh);
      curl_easy_setopt(curlCleanTable, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlCleanTable, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlCleanTable, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlCleanTable, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlCleanTable, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlCleanTable, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlCleanTable, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlCleanTable, CURLOPT_WRITEDATA, &cleanTableReadBuffer);

      res = curl_easy_perform(curlCleanTable);
      curl_easy_cleanup(curlCleanTable);

      QByteArray br = cleanTableReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue cleanTableTxid = cbResults.value("txid");

      if(cleanTableTxid.isString()){
          ui->menuTextBrowser->setText("Clean Table TXID: "+cleanTableTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No Clean Table TXID");
      }

    }
    return 0;
}


int Menu::getDreams()      /// Gets dReams Tokens
{
    CURL *curlgetDreams;
    CURLcode res;
    string getDreamsReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"transfer\",\"params\":{\"transfers\":[{\"amount\":200000,\"destination\":\"dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn\",\"burn\":10000}],\"scid\":\"8289c6109f41cbe1f6d5f27a419db537bf3bf30a25eff285241a36e1ae3e48a4\", \"ringsize\":2 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"IssueChips\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *gDr = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlgetDreams = curl_easy_init();

    if(curlgetDreams) {
      struct curl_slist *headers = NULL;

      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlgetDreams, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlgetDreams, CURLOPT_URL, gDr);
      curl_easy_setopt(curlgetDreams, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlgetDreams, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlgetDreams, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlgetDreams, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlgetDreams, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlgetDreams, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlgetDreams, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlgetDreams, CURLOPT_WRITEDATA, &getDreamsReadBuffer);

      res = curl_easy_perform(curlgetDreams);
      curl_easy_cleanup(curlgetDreams);

      QByteArray br = getDreamsReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue getDreamsTxid = cbResults.value("txid");

      if(getDreamsTxid.isString()){
            Menu::dReams = true;
      }

    }
    return 0;
}


void Menu::unlockTable()   /// Unlocks contract file for use
{
    checkDaemon();
    checkWallet();

    if(ui->daemonConnectedBox->isChecked() && ui->walletConnectedBox->isChecked() && Menu::mainnet == true){
        QByteArray lockedBytes;
        QFile lockedFile("contract/FiveCard.enc");
        lockedFile.open(QIODevice::ReadWrite);

            if(lockedFile.exists()){
                lockedBytes = lockedFile.readAll();
            }

        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::OFB);
        QString lock = QString::fromLocal8Bit(lockedBytes);
        QString key("07123E1F482356C415F684407A3B8723E10B2CBBC0B8FCD6282C49D37C9C1ABC");
        QString iv("D32DE74C7D993849132F774AE84E66D9");
        QByteArray hashKey = QCryptographicHash::hash(key.toLocal8Bit(), QCryptographicHash::Sha256);
        QByteArray hashIV = QCryptographicHash::hash(iv.toLocal8Bit(), QCryptographicHash::Md5);
        QByteArray decodeText = encryption.decode(lockedBytes, hashKey, hashIV);
        QString decodedString = QString(encryption.removePadding(decodeText));
       if(Menu::dReams == true){
            QFile unlockedFile("contract/FiveCard.bas");
            unlockedFile.open(QIODevice::ReadWrite);
            if(unlockedFile.exists()){
              unlockedFile.write(decodedString.toUtf8());
            }

            unlockedFile.close();
            ///lockedFile.remove();

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

        }

    }

}


void Menu::unixUpload(bool u)
{
    if(u){
        QFile scriptFile("contract/createTable.sh");
        scriptFile.open(QIODevice::ReadWrite);

        if(scriptFile.exists()){
            scriptFile.resize(0);
            QByteArray userPass = rpc::rpcLogin.c_str();
            QByteArray tableOwner = rpc::playerAddress.toUtf8();
            tableOwner.chop(9);
            scriptFile.write("curl -u "+userPass+"  --request POST --data-binary  @contract/FiveCard.bas "+tableOwner+"/install_sc >> contract/Tables.txt");
            scriptFile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
            scriptFile.close();
            system("./contract/createTable.sh");
            ui->menuTextBrowser->setText("Check Tables.txt for Table Id");
        }else {
            ui->menuTextBrowser->setText("Could Not Upload");
        }
    }else {
        ui->menuTextBrowser->setText("No Contract File To Upload");
    }
}


void Menu::windowsUpload(bool u)
{
    if(u){
        QFile scriptFile("createTable.cmd");
        scriptFile.open(QIODevice::ReadWrite);

        if(scriptFile.exists()){
            scriptFile.resize(0);
            QByteArray userPass = rpc::rpcLogin.c_str();
            QByteArray tableOwner = rpc::playerAddress.toUtf8();
            tableOwner.chop(9);
            scriptFile.write("curl -u "+userPass+"  --request POST --data-binary  @FiveCard.bas "+tableOwner+"/install_sc >> Tables.txt");
            scriptFile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
            scriptFile.close();
            system("createTable.cmd");
            ui->menuTextBrowser->setText("Check Tables.txt for Table Id");
        }else {
            ui->menuTextBrowser->setText("Could Not Upload");
        }
    }else {
        ui->menuTextBrowser->setText("No Contract File To Upload");
    }
}


int Menu::fetchInfo()  /// Fetch blockchain info for contract uploads
{
    CURL *curlFetchInfo;
    CURLcode res;
    string infoReadBuffer;
    char error[CURL_ERROR_SIZE];

    static const char *postthis = "{\"jsonrpc\": \"2.0\",\"id\": \"1\",\"method\": \"DERO.GetInfo\"}";

    string dStr = rpc::daemonAddress.toStdString();
    const char *fdCh = dStr.c_str();

    curlFetchInfo = curl_easy_init();

    if(curlFetchInfo) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlFetchInfo, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlFetchInfo, CURLOPT_URL, fdCh);
      curl_easy_setopt(curlFetchInfo, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlFetchInfo, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlFetchInfo, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlFetchInfo, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlFetchInfo, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlFetchInfo, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlFetchInfo, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlFetchInfo, CURLOPT_WRITEDATA, &infoReadBuffer);
      res = curl_easy_perform(curlFetchInfo);
      curl_easy_cleanup(curlFetchInfo);

      QByteArray br = infoReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue testnetCheck = cbResults.value("testnet");

      if(testnetCheck == false){
          Menu::mainnet = true;
          unlockTable();
      }

    }
    return 0;
}


int Menu::listTable()      /// Owner can list table for public sit an go play
{
    CURL *curlListTable;
    CURLcode res;
    string listTableReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::listingAddress+"\" , \"ringsize\":2 , \"sc_dero_deposit\":10000 , \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ListTable\"} , {\"name\":\"table\",\"datatype\":\"H\",\"value\":\""+Menu::contractAddress+"\"}] }}";

    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlListTable = curl_easy_init();

    if(curlListTable) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlListTable, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlListTable, CURLOPT_URL, stCh);
      curl_easy_setopt(curlListTable, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlListTable, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlListTable, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlListTable, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlListTable, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlListTable, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlListTable, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlListTable, CURLOPT_WRITEDATA, &listTableReadBuffer);

      res = curl_easy_perform(curlListTable);
      curl_easy_cleanup(curlListTable);

      QByteArray br = listTableReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue listTableTxid = cbResults.value("txid");

      if(listTableTxid.isString()){
          ui->menuTextBrowser->setText("List Table TXID: "+listTableTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No List Table TXID");
      }

    }
    return 0;
}


int Menu::delistTable()      /// Owner can remove listing made by current address
{
    CURL *curlDelistTable;
    CURLcode res;
    string listTableReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::listingAddress+"\" , \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"RemoveListing\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlDelistTable = curl_easy_init();

    if(curlDelistTable) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlDelistTable, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlDelistTable, CURLOPT_URL, stCh);
      curl_easy_setopt(curlDelistTable, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlDelistTable, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlDelistTable, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlDelistTable, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlDelistTable, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlDelistTable, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlDelistTable, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlDelistTable, CURLOPT_WRITEDATA, &listTableReadBuffer);

      res = curl_easy_perform(curlDelistTable);
      curl_easy_cleanup(curlDelistTable);

      QByteArray br = listTableReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue delistTableTxid = cbResults.value("txid");

      if(delistTableTxid.isString()){
          ui->menuTextBrowser->setText("Delist Table TXID: "+delistTableTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No Delist Table TXID");
      }

    }
    return 0;
}


int Menu::checkIfListed()       /// Checks if players table is already listed
{
    CURL *curlListedCheck;
    CURLcode res;
    string listedReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::listingAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *fdCh = dStr.c_str();

    curlListedCheck = curl_easy_init();

    if(curlListedCheck) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlListedCheck, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlListedCheck, CURLOPT_URL, fdCh);
      curl_easy_setopt(curlListedCheck, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlListedCheck, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlListedCheck, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlFetchInfo, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlListedCheck, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlListedCheck, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlListedCheck, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlListedCheck, CURLOPT_WRITEDATA, &listedReadBuffer);

      res = curl_easy_perform(curlListedCheck);
      curl_easy_cleanup(curlListedCheck);

      QByteArray fld = listedReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(fld);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue counter = cbStringKeys.value("Counter:");

      int endPoint = counter.toInt();

      for (int i = 0; i < endPoint; i++) {
        QString searchId = QString::number(i);
        QJsonValue table = cbStringKeys.value("Table#"+searchId.toUtf8()+":");
        if(table.toString() == Menu::contractAddress){
            ui->listTableButton->setEnabled(false);
            ui->delistTableButton->setEnabled(true);
        }else {
            ui->listTableButton->setEnabled(true);
            ui->delistTableButton->setEnabled(false);
        }

      }

    }
    return 0;
}


int Menu::fetchListingScData()       /// Fetch Public table listings and displays
{
    CURL *curlListingFetch;
    CURLcode res;
    string fetchListingReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::listingAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string dStr = rpc::daemonAddress.toStdString();
    const char *fdCh = dStr.c_str();

    curlListingFetch = curl_easy_init();

    if(curlListingFetch) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlListingFetch, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlListingFetch, CURLOPT_URL, fdCh);
      curl_easy_setopt(curlListingFetch, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlListingFetch, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlListingFetch, CURLOPT_ERRORBUFFER, error);
      /// curl_easy_setopt(curlFetchInfo, CURLOPT_SSL_VERIFYPEER, 0);   *Remove comment for widnows SSL disable*
      curl_easy_setopt(curlListingFetch, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlListingFetch, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlListingFetch, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlListingFetch, CURLOPT_WRITEDATA, &fetchListingReadBuffer);

      res = curl_easy_perform(curlListingFetch);
      curl_easy_cleanup(curlListingFetch);

      QByteArray fld = fetchListingReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(fld);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue counter = cbStringKeys.value("Counter:");

      int endPoint = counter.toInt();

      for (int i = 0; i < endPoint; i++) {
        QString searchId = QString::number(i);
        QJsonValue table = cbStringKeys.value("Table#"+searchId.toUtf8()+":");
        if(table.isString()){
            ui->menuTextBrowser->append(table.toString()+"\n");
        }

      }

    }
    return 0;
}


int Menu::forceStart()      /// Owner can start the game with empty seats
{
    CURL *curlforceStart;
    CURLcode res;
    string forceReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"ForceStart\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlforceStart = curl_easy_init();

    if(curlforceStart) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlforceStart, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlforceStart, CURLOPT_URL, stCh);
      curl_easy_setopt(curlforceStart, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlforceStart, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlforceStart, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlforceStart, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlforceStart, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlforceStart, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlforceStart, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlforceStart, CURLOPT_WRITEDATA, &forceReadBuffer);

      res = curl_easy_perform(curlforceStart);
      curl_easy_cleanup(curlforceStart);

      QByteArray br = forceReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue forceStartTxid = cbResults.value("txid");

      if(forceStartTxid.isString()){
          ui->menuTextBrowser->setText("Game Start TXID: "+forceStartTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No Start Table TXID");
      }

    }
    return 0;
}


int Menu::ownerShare()      /// Owner can start the game with empty seats
{
    CURL *curlShare;
    CURLcode res;
    string forceReadBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"scinvoke\",\"params\":{\"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2, \"sc_rpc\":[{\"name\":\"entrypoint\",\"datatype\":\"S\",\"value\":\"Deck\"}, {\"name\":\"face\",\"datatype\":\"S\",\"value\":\""+MainWindow::faceUrl+"\"}, {\"name\":\"back\",\"datatype\":\"S\",\"value\":\""+MainWindow::backUrl+"\"}] }}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    string pStr = rpc::playerAddress.toStdString();
    const char *stCh = pStr.c_str();

    const char *loginCh = rpc::rpcLogin.c_str();

    curlShare = curl_easy_init();

    if(curlShare) {
      struct curl_slist *headers = NULL;
      /// Add request headers
      headers = curl_slist_append(headers, "Accept: application/json");
      headers = curl_slist_append(headers, "Content-Type: application/json");
      headers = curl_slist_append(headers, "charset: utf-8");
      /// cUrl options
      curl_easy_setopt(curlShare, CURLOPT_HTTPHEADER, headers);
      curl_easy_setopt(curlShare, CURLOPT_URL, stCh);
      curl_easy_setopt(curlShare, CURLOPT_VERBOSE, 0L);
      curl_easy_setopt(curlShare, CURLOPT_CONNECTTIMEOUT, 4L);
      curl_easy_setopt(curlShare, CURLOPT_ERRORBUFFER, error);
      curl_easy_setopt(curlShare, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlShare, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlShare, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlShare, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlShare, CURLOPT_WRITEDATA, &forceReadBuffer);

      res = curl_easy_perform(curlShare);
      curl_easy_cleanup(curlShare);

      QByteArray br = forceReadBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonValue forceStartTxid = cbResults.value("txid");

      if(forceStartTxid.isString()){
          ui->menuTextBrowser->setText("Share Deck TXID: "+forceStartTxid.toString());
      }else {
          ui->menuTextBrowser->setText("Error No Share TXID");
      }

    }
    return 0;
}

