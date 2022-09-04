#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H
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

#include "QObject"
#include "QByteArray"
#include "QNetworkAccessManager"
#include "QNetworkRequest"
#include "QNetworkReply"


class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);
    virtual ~FileDownloader();
    QByteArray downloadedData() const;


signals:
    void downloaded();


private slots:
    void fileDownloaded(QNetworkReply* pReply);


private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
};

#endif // FILEDOWNLOADER_H
