# Dero-Poker-Table
Ui for Dero Private Poker Table.

![logo_optimized](https://user-images.githubusercontent.com/84689659/165416164-7e63fc07-e2ef-4391-9e6b-ed8eeaa6d2af.png)

Written in C++/Qt. Used Qt 5.12.8 to build the Ui. This app is for playing **private** poker built on **Dero**. The poker table is a _smart contract_, it deals out the cards and takes the Dero bets. The owner of the table sets the ante/limits and seats at the table then invites players to join.

![PokerMenu](https://user-images.githubusercontent.com/84689659/168459412-95a0da71-3464-4095-b286-2937998d597e.png)

## Current Tables
- **Five Card Draw**  -  Up to five players at the table, minimum bet is ante with single no limit raise.

![FiveCardDrawTable](https://user-images.githubusercontent.com/84689659/168459898-428109ec-16d2-4549-821c-edb108a834bb.png)

- More to come...


---
### Donations
- **Dero Address**: dero1qyr8yjnu6cl2c5yqkls0hmxe6rry77kn24nmc5fje6hm9jltyvdd5qq4hn5pn

![DeroDonations](https://user-images.githubusercontent.com/84689659/165414903-44164e7e-4277-44f8-b1fe-8d139f559db1.jpg)

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
git clone https://github.com/SixofClubsss/Dero-Testnet-Baccarat.git
cd Dero-Poker-Table/Testnet-FiveCardDraw
qmake
make
```

**Start app**
```
./Testnet-FiveCardDraw
```

---
