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
#include "rpc.h"

using std::string;
QString rpc::daemonAddressToMain;


QString Menu::contractAddress;

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->ui->checkBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->checkBox->setFocusPolicy(Qt::NoFocus);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_contractButton_clicked()
{
    Menu::contractAddress = ui->contractLineEdit->text();
    checkContract();
    rpc::daemonAddressToMain = ui->menuDaemonRPCinput->text();
}


int Menu::checkContract(void)       /// Check if table is valid
{
    CURL *curlContract;
    CURLcode res;
    string readBuffer;
    char error[CURL_ERROR_SIZE];

    QString parts = "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"getsc\",\"params\":{ \"scid\":\""+Menu::contractAddress+"\" , \"ringsize\":2 , \"code\":false , \"variables\":true}}";
    string addThis = parts.toStdString();
    const char *postthis = addThis.c_str();

    QString daemonAddress =  ui->menuDaemonRPCinput->text()+"/json_rpc";
    string dStr = daemonAddress.toStdString();
    const char *dCh = dStr.c_str ();

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
      curl_easy_setopt(curlContract, CURLOPT_VERBOSE, 1L);
      curl_easy_setopt(curlContract, CURLOPT_ERRORBUFFER, error);
      ///curl_easy_setopt(curlContract, CURLOPT_USERPWD, loginCh);
      curl_easy_setopt(curlContract, CURLOPT_POSTFIELDS, postthis);
      curl_easy_setopt(curlContract, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
      curl_easy_setopt(curlContract, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curlContract, CURLOPT_WRITEDATA, &readBuffer);

      res = curl_easy_perform(curlContract);
      curl_easy_cleanup(curlContract);

      QByteArray br = readBuffer.c_str();
      QJsonDocument cbDoc = QJsonDocument::fromJson(br);
      QJsonObject cbObj = cbDoc.object();
      QJsonObject cbResults = cbObj["result"].toObject();
      QJsonObject cbStringKeys = cbResults["stringkeys"].toObject();
      QJsonValue tableOwner = cbStringKeys.value("owner:");

      if(tableOwner.isString())
      {
          ui->checkBox->setChecked(true);
          std::cout << "Contract is Valid" << std::endl;     /// Connected message

      }else {

          ui->checkBox->setChecked(false);
      }

    }
    return 0;

}




