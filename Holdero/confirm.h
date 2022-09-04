#ifndef CONFIRM_H
#define CONFIRM_H
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

#include "QDialog"


namespace Ui { class Confirm; }

class Confirm : public QDialog
{
    Q_OBJECT

public:
    explicit Confirm(QWidget *parent = nullptr);
    ~Confirm();
    static bool actionConfirmed;
    static int whichText;
    void setConfirmTheme();
    void setFonts(QString);
    void getTableText();
    void newTableText();
    void listTableText();
    void delistTableText();
    void forceStartText();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Confirm *ui;
};

#endif // CONFIRM_H
