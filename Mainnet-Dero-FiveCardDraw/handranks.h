#ifndef HANDRANKS_H
#define HANDRANKS_H

#include <QDialog>

namespace Ui {
class HandRanks;
}

class HandRanks : public QDialog
{
    Q_OBJECT

public:
    explicit HandRanks(QWidget *parent = nullptr);
    ~HandRanks();
     void setFonts();

private:
    Ui::HandRanks *ui;
};

#endif // HANDRANKS_H
