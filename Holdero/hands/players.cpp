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

#include "hands/handranks.h"
#include "rpc/rpc.h"
#include "ui_handranks.h"
#include "mainwindow.h"
#include "QDebug"


void MainWindow::getCommunity()  /// Gets ciommunity cards
{
    communityCard[0] = rpc::flopCard1;
    communityCard[1] = rpc::flopCard2;
    communityCard[2] = rpc::flopCard3;
    communityCard[3] = rpc::turnCard;
    communityCard[4] = rpc::riverCard;

    getArray(communityCard[0]);
    cc1[0] = arrSplit[0];
    cc1[1] = arrSplit[1];

    getArray(communityCard[1]);
    cc2[0] = arrSplit[0];
    cc2[1] = arrSplit[1];

    getArray(communityCard[2]);
    cc3[0] = arrSplit[0];
    cc3[1] = arrSplit[1];

    getArray(communityCard[3]);
    cc4[0] = arrSplit[0];
    cc4[1] = arrSplit[1];

    getArray(communityCard[4]);
    cc5[0] = arrSplit[0];
    cc5[1] = arrSplit[1];
}


int MainWindow::getPlayer1() /// Gets player hand and hand rank
{
    int player1HandRaw[] = {keyCard(rpc::hashOneone, 1), keyCard(rpc::hashOnetwo, 1)};
    p1Rank = 100;
    p1HighPair = 0;
    getArray(player1HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player1HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p1HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p1SuitsArr);

    std::sort(p1HighCardArr, p1HighCardArr + 5);
    p1HighPair = getHighPair(p1HighCardArr);
    p1HighTrip = getHighTrip(p1HighCardArr);

    return Rank;
}


int MainWindow::getPlayer2()
{
    int player2HandRaw[] = {keyCard(rpc::hashTwoone, 2), keyCard(rpc::hashTwotwo, 2)};
    p2Rank = 100;
    p2HighPair = 0;
    getArray(player2HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player2HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p2HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p2SuitsArr);

    std::sort(p2HighCardArr, p2HighCardArr + 5);
    p2HighPair = getHighPair(p2HighCardArr);
    p2HighTrip = getHighTrip(p2HighCardArr);

    return Rank;
}


int MainWindow::getPlayer3()
{
    int player3HandRaw[] = {keyCard(rpc::hashThreeone, 3), keyCard(rpc::hashThreetwo, 3)};
    p3Rank = 100;
    p3HighPair = 0;
    getArray(player3HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player3HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p3HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p3SuitsArr);

    std::sort(p3HighCardArr, p3HighCardArr + 5);
    p3HighPair = getHighPair(p3HighCardArr);
    p3HighTrip = getHighTrip(p3HighCardArr);

    return Rank;
}


int MainWindow::getPlayer4()
{
    int player4HandRaw[] = {keyCard(rpc::hashFourone, 4), keyCard(rpc::hashFourtwo, 4)};
    p4Rank = 100;
    p4HighPair = 0;
    getArray(player4HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player4HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p4HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p4SuitsArr);

    std::sort(p4HighCardArr, p4HighCardArr + 5);
    p4HighPair = getHighPair(p4HighCardArr);
    p4HighTrip = getHighTrip(p4HighCardArr);

    return Rank;
}


int MainWindow::getPlayer5()
{
    int player5HandRaw[] = {keyCard(rpc::hashFiveone, 5), keyCard(rpc::hashFivetwo, 5)};
    p5Rank = 100;
    p5HighPair = 0;
    getArray(player5HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player5HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p5HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p5SuitsArr);

    std::sort(p5HighCardArr, p5HighCardArr + 5);
    p5HighPair = getHighPair(p5HighCardArr);
    p5HighTrip = getHighTrip(p5HighCardArr);

    return Rank;
}


int MainWindow::getPlayer6()
{
    int player6HandRaw[] = {keyCard(rpc::hashSixone, 6), keyCard(rpc::hashSixtwo, 6)};
    p6Rank = 100;
    p6HighPair = 0;
    getArray(player6HandRaw[0]);
    suitSplit1[0] = arrSplit[0];
    suitSplit1[1] = arrSplit[1];

    getArray(player6HandRaw[1]);
    suitSplit2[0] = arrSplit[0];
    suitSplit2[1] = arrSplit[1];

    int Rank = compareThese();
    std::copy(fHighCardArr, fHighCardArr + 5, p6HighCardArr);
    ///std::copy(fSuitsArr, fSuitsArr + 5, p6SuitsArr);

    std::sort(p6HighCardArr, p6HighCardArr + 5);
    p6HighPair = getHighPair(p6HighCardArr);
    p6HighTrip = getHighTrip(p6HighCardArr);

    return Rank;
}


void MainWindow::compare1_2()   /// Compares two players hands
{
    if((p1HighCardArr[4] > p2HighCardArr[4]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] > p2HighCardArr[3]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] > p2HighCardArr[2]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] == p2HighCardArr[2] && p1HighCardArr[1] > p2HighCardArr[1]) ||
       (p1HighCardArr[4] == p2HighCardArr[4] && p1HighCardArr[3] == p2HighCardArr[3] && p1HighCardArr[2] == p2HighCardArr[2] && p1HighCardArr[1] == p2HighCardArr[1] && p1HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare1_3()
{
    if((p1HighCardArr[4] > p3HighCardArr[4]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] > p3HighCardArr[3]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] > p3HighCardArr[2]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] == p3HighCardArr[2] && p1HighCardArr[1] > p3HighCardArr[1]) ||
       (p1HighCardArr[4] == p3HighCardArr[4] && p1HighCardArr[3] == p3HighCardArr[3] && p1HighCardArr[2] == p3HighCardArr[2] && p1HighCardArr[1] == p3HighCardArr[1] && p1HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare1_4()
{
    if((p1HighCardArr[4] > p4HighCardArr[4]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] > p4HighCardArr[3]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] > p4HighCardArr[2]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] == p4HighCardArr[2] && p1HighCardArr[1] > p4HighCardArr[1]) ||
       (p1HighCardArr[4] == p4HighCardArr[4] && p1HighCardArr[3] == p4HighCardArr[3] && p1HighCardArr[2] == p4HighCardArr[2] && p1HighCardArr[1] == p4HighCardArr[1] && p1HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare1_5()
{
    if((p1HighCardArr[4] > p5HighCardArr[4]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] > p5HighCardArr[3]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] > p5HighCardArr[2]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] == p5HighCardArr[2] && p1HighCardArr[1] > p5HighCardArr[1]) ||
       (p1HighCardArr[4] == p5HighCardArr[4] && p1HighCardArr[3] == p5HighCardArr[3] && p1HighCardArr[2] == p5HighCardArr[2] && p1HighCardArr[1] == p5HighCardArr[1] && p1HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare1_6()
{
    if((p1HighCardArr[4] > p6HighCardArr[4]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] > p6HighCardArr[3]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] > p6HighCardArr[2]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] == p6HighCardArr[2] && p1HighCardArr[1] > p6HighCardArr[1]) ||
       (p1HighCardArr[4] == p6HighCardArr[4] && p1HighCardArr[3] == p6HighCardArr[3] && p1HighCardArr[2] == p6HighCardArr[2] && p1HighCardArr[1] == p6HighCardArr[1] && p1HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare2_1()
{
    if((p2HighCardArr[4] > p1HighCardArr[4]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] > p1HighCardArr[3]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] > p1HighCardArr[2]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] == p1HighCardArr[2] && p2HighCardArr[1] > p1HighCardArr[1]) ||
       (p2HighCardArr[4] == p1HighCardArr[4] && p2HighCardArr[3] == p1HighCardArr[3] && p2HighCardArr[2] == p1HighCardArr[2] && p2HighCardArr[1] == p1HighCardArr[1] && p2HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare2_3()
{
    if((p2HighCardArr[4] > p3HighCardArr[4]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] > p3HighCardArr[3]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] > p3HighCardArr[2]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] == p3HighCardArr[2] && p2HighCardArr[1] > p3HighCardArr[1]) ||
       (p2HighCardArr[4] == p3HighCardArr[4] && p2HighCardArr[3] == p3HighCardArr[3] && p2HighCardArr[2] == p3HighCardArr[2] && p2HighCardArr[1] == p3HighCardArr[1] && p2HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare2_4()
{
    if((p2HighCardArr[4] > p4HighCardArr[4]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] > p4HighCardArr[3]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] > p4HighCardArr[2]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] == p4HighCardArr[2] && p2HighCardArr[1] > p4HighCardArr[1]) ||
       (p2HighCardArr[4] == p4HighCardArr[4] && p2HighCardArr[3] == p4HighCardArr[3] && p2HighCardArr[2] == p4HighCardArr[2] && p2HighCardArr[1] == p4HighCardArr[1] && p2HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare2_5()
{
    if((p2HighCardArr[4] > p5HighCardArr[4]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] > p5HighCardArr[3]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] > p5HighCardArr[2]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] == p5HighCardArr[2] && p2HighCardArr[1] > p5HighCardArr[1]) ||
       (p2HighCardArr[4] == p5HighCardArr[4] && p2HighCardArr[3] == p5HighCardArr[3] && p2HighCardArr[2] == p5HighCardArr[2] && p2HighCardArr[1] == p5HighCardArr[1] && p2HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare2_6()
{
    if((p2HighCardArr[4] > p6HighCardArr[4]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] > p6HighCardArr[3]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] > p6HighCardArr[2]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] == p6HighCardArr[2] && p2HighCardArr[1] > p6HighCardArr[1]) ||
       (p2HighCardArr[4] == p6HighCardArr[4] && p2HighCardArr[3] == p6HighCardArr[3] && p2HighCardArr[2] == p6HighCardArr[2] && p2HighCardArr[1] == p6HighCardArr[1] && p2HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare3_1()
{
    if((p3HighCardArr[4] > p1HighCardArr[4]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] > p1HighCardArr[3]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] > p1HighCardArr[2]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] == p1HighCardArr[2] && p3HighCardArr[1] > p1HighCardArr[1]) ||
       (p3HighCardArr[4] == p1HighCardArr[4] && p3HighCardArr[3] == p1HighCardArr[3] && p3HighCardArr[2] == p1HighCardArr[2] && p3HighCardArr[1] == p1HighCardArr[1] && p3HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare3_2()
{
    if((p3HighCardArr[4] > p2HighCardArr[4]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] > p2HighCardArr[3]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] > p2HighCardArr[2]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] == p2HighCardArr[2] && p3HighCardArr[1] > p2HighCardArr[1]) ||
       (p3HighCardArr[4] == p2HighCardArr[4] && p3HighCardArr[3] == p2HighCardArr[3] && p3HighCardArr[2] == p2HighCardArr[2] && p3HighCardArr[1] == p2HighCardArr[1] && p3HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare3_4()
{
    if((p3HighCardArr[4] > p4HighCardArr[4]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] > p4HighCardArr[3]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] > p4HighCardArr[2]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] == p4HighCardArr[2] && p3HighCardArr[1] > p4HighCardArr[1]) ||
       (p3HighCardArr[4] == p4HighCardArr[4] && p3HighCardArr[3] == p4HighCardArr[3] && p3HighCardArr[2] == p4HighCardArr[2] && p3HighCardArr[1] == p4HighCardArr[1] && p3HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare3_5()
{
    if((p3HighCardArr[4] > p5HighCardArr[4]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] > p5HighCardArr[3]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] > p5HighCardArr[2]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] == p5HighCardArr[2] && p3HighCardArr[1] > p5HighCardArr[1]) ||
       (p3HighCardArr[4] == p5HighCardArr[4] && p3HighCardArr[3] == p5HighCardArr[3] && p3HighCardArr[2] == p5HighCardArr[2] && p3HighCardArr[1] == p5HighCardArr[1] && p3HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare3_6()
{
    if((p3HighCardArr[4] > p6HighCardArr[4]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] > p6HighCardArr[3]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] > p6HighCardArr[2]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] == p6HighCardArr[2] && p3HighCardArr[1] > p6HighCardArr[1]) ||
       (p3HighCardArr[4] == p6HighCardArr[4] && p3HighCardArr[3] == p6HighCardArr[3] && p3HighCardArr[2] == p6HighCardArr[2] && p3HighCardArr[1] == p6HighCardArr[1] && p3HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare4_1()
{
    if((p4HighCardArr[4] > p1HighCardArr[4]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] > p1HighCardArr[3]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] > p1HighCardArr[2]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] == p1HighCardArr[2] && p4HighCardArr[1] > p1HighCardArr[1]) ||
       (p4HighCardArr[4] == p1HighCardArr[4] && p4HighCardArr[3] == p1HighCardArr[3] && p4HighCardArr[2] == p1HighCardArr[2] && p4HighCardArr[1] == p1HighCardArr[1] && p4HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare4_2()
{
    if((p4HighCardArr[4] > p2HighCardArr[4]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] > p2HighCardArr[3]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] > p2HighCardArr[2]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] == p2HighCardArr[2] && p4HighCardArr[1] > p2HighCardArr[1]) ||
       (p4HighCardArr[4] == p2HighCardArr[4] && p4HighCardArr[3] == p2HighCardArr[3] && p4HighCardArr[2] == p2HighCardArr[2] && p4HighCardArr[1] == p2HighCardArr[1] && p4HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare4_3()
{
    if((p4HighCardArr[4] > p3HighCardArr[4]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] > p3HighCardArr[3]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] > p3HighCardArr[2]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] == p3HighCardArr[2] && p4HighCardArr[1] > p3HighCardArr[1]) ||
       (p4HighCardArr[4] == p3HighCardArr[4] && p4HighCardArr[3] == p3HighCardArr[3] && p4HighCardArr[2] == p3HighCardArr[2] && p4HighCardArr[1] == p3HighCardArr[1] && p4HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare4_5()
{
    if((p4HighCardArr[4] > p5HighCardArr[4]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] > p5HighCardArr[3]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] > p5HighCardArr[2]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] == p5HighCardArr[2] && p4HighCardArr[1] > p5HighCardArr[1]) ||
       (p4HighCardArr[4] == p5HighCardArr[4] && p4HighCardArr[3] == p5HighCardArr[3] && p4HighCardArr[2] == p5HighCardArr[2] && p4HighCardArr[1] == p5HighCardArr[1] && p4HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::compare4_6()
{
    if((p4HighCardArr[4] > p6HighCardArr[4]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] > p6HighCardArr[3]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] > p6HighCardArr[2]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] == p6HighCardArr[2] && p4HighCardArr[1] > p6HighCardArr[1]) ||
       (p4HighCardArr[4] == p6HighCardArr[4] && p4HighCardArr[3] == p6HighCardArr[3] && p4HighCardArr[2] == p6HighCardArr[2] && p4HighCardArr[1] == p6HighCardArr[1] && p4HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare5_1()
{
    if((p5HighCardArr[4] > p1HighCardArr[4]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] > p1HighCardArr[3]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] > p1HighCardArr[2]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] == p1HighCardArr[2] && p5HighCardArr[1] > p1HighCardArr[1]) ||
       (p5HighCardArr[4] == p1HighCardArr[4] && p5HighCardArr[3] == p1HighCardArr[3] && p5HighCardArr[2] == p1HighCardArr[2] && p5HighCardArr[1] == p1HighCardArr[1] && p5HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare5_2()
{
    if((p5HighCardArr[4] > p2HighCardArr[4]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] > p2HighCardArr[3]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] > p2HighCardArr[2]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] == p2HighCardArr[2] && p5HighCardArr[1] > p2HighCardArr[1]) ||
       (p5HighCardArr[4] == p2HighCardArr[4] && p5HighCardArr[3] == p2HighCardArr[3] && p5HighCardArr[2] == p2HighCardArr[2] && p5HighCardArr[1] == p2HighCardArr[1] && p5HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare5_3()
{
    if((p5HighCardArr[4] > p3HighCardArr[4]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] > p3HighCardArr[3]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] > p3HighCardArr[2]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] == p3HighCardArr[2] && p5HighCardArr[1] > p3HighCardArr[1]) ||
       (p5HighCardArr[4] == p3HighCardArr[4] && p5HighCardArr[3] == p3HighCardArr[3] && p5HighCardArr[2] == p3HighCardArr[2] && p5HighCardArr[1] == p3HighCardArr[1] && p5HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare5_4()
{
    if((p5HighCardArr[4] > p4HighCardArr[4]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] > p4HighCardArr[3]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] > p4HighCardArr[2]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] == p4HighCardArr[2] && p5HighCardArr[1] > p4HighCardArr[1]) ||
       (p5HighCardArr[4] == p4HighCardArr[4] && p5HighCardArr[3] == p4HighCardArr[3] && p5HighCardArr[2] == p4HighCardArr[2] && p5HighCardArr[1] == p4HighCardArr[1] && p5HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare5_6()
{
    if((p5HighCardArr[4] > p6HighCardArr[4]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] > p6HighCardArr[3]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] > p6HighCardArr[2]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] == p6HighCardArr[2] && p5HighCardArr[1] > p6HighCardArr[1]) ||
       (p5HighCardArr[4] == p6HighCardArr[4] && p5HighCardArr[3] == p6HighCardArr[3] && p5HighCardArr[2] == p6HighCardArr[2] && p5HighCardArr[1] == p6HighCardArr[1] && p5HighCardArr[0] > p6HighCardArr[0])){

        less6();
    }

}


void MainWindow::compare6_1()
{
    if((p6HighCardArr[4] > p1HighCardArr[4]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] > p1HighCardArr[3]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] > p1HighCardArr[2]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] == p1HighCardArr[2] && p6HighCardArr[1] > p1HighCardArr[1]) ||
       (p6HighCardArr[4] == p1HighCardArr[4] && p6HighCardArr[3] == p1HighCardArr[3] && p6HighCardArr[2] == p1HighCardArr[2] && p6HighCardArr[1] == p1HighCardArr[1] && p6HighCardArr[0] > p1HighCardArr[0])){

        less1();
    }

}


void MainWindow::compare6_2()
{
    if((p6HighCardArr[4] > p2HighCardArr[4]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] > p2HighCardArr[3]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] > p2HighCardArr[2]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] == p2HighCardArr[2] && p6HighCardArr[1] > p2HighCardArr[1]) ||
       (p6HighCardArr[4] == p2HighCardArr[4] && p6HighCardArr[3] == p2HighCardArr[3] && p6HighCardArr[2] == p2HighCardArr[2] && p6HighCardArr[1] == p2HighCardArr[1] && p6HighCardArr[0] > p2HighCardArr[0])){

        less2();
    }

}


void MainWindow::compare6_3()
{
    if((p6HighCardArr[4] > p3HighCardArr[4]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] > p3HighCardArr[3]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] > p3HighCardArr[2]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] == p3HighCardArr[2] && p6HighCardArr[1] > p3HighCardArr[1]) ||
       (p6HighCardArr[4] == p3HighCardArr[4] && p6HighCardArr[3] == p3HighCardArr[3] && p6HighCardArr[2] == p3HighCardArr[2] && p6HighCardArr[1] == p3HighCardArr[1] && p6HighCardArr[0] > p3HighCardArr[0])){

        less3();
    }

}


void MainWindow::compare6_4()
{
    if((p6HighCardArr[4] > p4HighCardArr[4]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] > p4HighCardArr[3]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] > p4HighCardArr[2]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] == p4HighCardArr[2] && p6HighCardArr[1] > p4HighCardArr[1]) ||
       (p6HighCardArr[4] == p4HighCardArr[4] && p6HighCardArr[3] == p4HighCardArr[3] && p6HighCardArr[2] == p4HighCardArr[2] && p6HighCardArr[1] == p4HighCardArr[1] && p6HighCardArr[0] > p4HighCardArr[0])){

        less4();
    }

}


void MainWindow::compare6_5()
{
    if((p6HighCardArr[4] > p5HighCardArr[4]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] > p5HighCardArr[3]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] > p5HighCardArr[2]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] == p5HighCardArr[2] && p6HighCardArr[1] > p5HighCardArr[1]) ||
       (p6HighCardArr[4] == p5HighCardArr[4] && p6HighCardArr[3] == p5HighCardArr[3] && p6HighCardArr[2] == p5HighCardArr[2] && p6HighCardArr[1] == p5HighCardArr[1] && p6HighCardArr[0] > p5HighCardArr[0])){

        less5();
    }

}


void MainWindow::less6()    /// Stip hand
{
    p6HighCardArr[0] = 0;
    p6HighCardArr[1] = 0;
    p6HighCardArr[2] = 0;
    p6HighCardArr[3] = 0;
    p6HighCardArr[4] = 0;
    p6HighPair = 0;
}


void MainWindow::less5()
{
    p5HighCardArr[0] = 0;
    p5HighCardArr[1] = 0;
    p5HighCardArr[2] = 0;
    p5HighCardArr[3] = 0;
    p5HighCardArr[4] = 0;
    p5HighPair = 0;
}


void MainWindow::less4()
{
    p4HighCardArr[0] = 0;
    p4HighCardArr[1] = 0;
    p4HighCardArr[2] = 0;
    p4HighCardArr[3] = 0;
    p4HighCardArr[4] = 0;
    p4HighPair = 0;
}


void MainWindow::less3()
{
    p3HighCardArr[0] = 0;
    p3HighCardArr[1] = 0;
    p3HighCardArr[2] = 0;
    p3HighCardArr[3] = 0;
    p3HighCardArr[4] = 0;
    p3HighPair = 0;
}


void MainWindow::less2()
{
    p2HighCardArr[0] = 0;
    p2HighCardArr[1] = 0;
    p2HighCardArr[2] = 0;
    p2HighCardArr[3] = 0;
    p2HighCardArr[4] = 0;
    p2HighPair = 0;
}


void MainWindow::less1()
{
    p1HighCardArr[0] = 0;
    p1HighCardArr[1] = 0;
    p1HighCardArr[2] = 0;
    p1HighCardArr[3] = 0;
    p1HighCardArr[4] = 0;
    p1HighPair = 0;
}


