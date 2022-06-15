#ifndef CONFIRM_H
#define CONFIRM_H
/// dReam Tables Five Card Draw Poker
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
    void setFonts();
    void getTableText();
    void newTableText();
    void listTableText();
    void delistTableText();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Confirm *ui;
};

#endif // CONFIRM_H
