# Dero-Poker-Table
Ui for Dero Private Poker Table.
![dReamTablesFooter](https://user-images.githubusercontent.com/84689659/170848755-d2cb4933-df2b-46f9-80e6-4349621871a3.png)
Written in C++/Qt. Used Qt 5.12.8 to build the Ui. These apps are for playing dReam Tables **private** poker, built on [**Dero**](https://dero.io). The poker table is a _smart contract_, it deals out the cards and takes the Dero bets. The owner of the table sets the ante/limits and seats at the table then invites players to join.


![dReamTablesFiveCardMenu](https://user-images.githubusercontent.com/84689659/177437584-f17156f8-e125-4424-acf4-46bb6a268405.png)

## Current Tables
- **Five Card Draw**  
  - Up to six players at the table, minimum bet is ante with single no limit raise.
  - Sit & Go play.
  - Public listing contract and search function for public tables.
  - Auto table generate function in app.
  - Automated or manual payouts. 
  - In game [Non-Fungible-Assets](https://github.com/civilware/artificer-nfa-standard) for customization.
  
![FiveCardTableMain](https://user-images.githubusercontent.com/84689659/185278305-71c68b5a-1326-4c8d-afc0-24d083a61342.png)

---
- **Holdero** (*Texas Hold'em*)
  - Up to six players at the table.
  - Can use blinds, antes or a combination of both.
  - Sit & Go play.
  - Public listing contract and search function for public tables.
  - Auto table generate function in app.
  - Automated or manual payouts.
  - In game [Non-Fungible-Assets](https://github.com/civilware/artificer-nfa-standard) for customization.
  
![HolderoMain](https://user-images.githubusercontent.com/84689659/185277836-a32fccb5-e737-402b-b87b-f8a2378fcfd3.png)

More updates to come...

---
### Donations
- **Dero Address**: dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn

![DeroDonations](https://user-images.githubusercontent.com/84689659/165414903-44164e7e-4277-44f8-b1fe-8d139f559db1.jpg)

---

View the latest [release](https://github.com/SixofClubsss/Dero-Poker-Table/releases) or build from source. 

## Build

- ### Linux

**Install dependencies**
```
sudo apt update
sudo apt install build-essential qt5-qmake curl libcurl4-openssl-dev
sudo apt install --no-install-recommends qtbase5-dev qttools5-dev libqt5svg5-dev
```

**Download repo & build**
```
git clone https://github.com/SixofClubsss/Dero-Poker-Table.git
cd Dero-Poker-Table/Mainnet-Dero-FiveCardDraw
qmake
make
```

**Start app**
```
./Dero-FiveCardDraw
```
To build testnet version `cd Dero-Poker-Table/Testnet-FiveCardDraw` then `qmake` & `make`

---

### Licensing

dReam Tables Dero Poker Tables are free open source games.     
The source code is published under the [GNU GPL V3 License.](https://github.com/SixofClubsss/Dero-Poker-Table/blob/main/Licenses/LICENSE)     
Copyright 2022 dReam Tables       
Refer to the [copywrite.md](https://github.com/SixofClubsss/Dero-Poker-Table/blob/main/Licenses/copyright.md) file for artwork licensing. 
