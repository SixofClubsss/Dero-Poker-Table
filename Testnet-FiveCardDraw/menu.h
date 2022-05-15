#ifndef MENU_H
#define MENU_H

#include "QDialog"
#include "rpc.h"


namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    static QString contractAddress;
    int checkContract(void);

private slots:
    void on_contractButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
