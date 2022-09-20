#ifndef VIEWDECK_H
#define VIEWDECK_H
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

#include "hands/handranks.h"
#include "QDialog"

namespace Ui {
class ViewDeck;
}

class ViewDeck : public QDialog
{
    Q_OBJECT

public:
    explicit ViewDeck(QWidget *parent = nullptr);
    ~ViewDeck();
    void setViewTheme();

private:
    Ui::ViewDeck *ui;
};

#endif // VIEWDECK_H
