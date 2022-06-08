#ifndef AGGIUNGIPRODOTTODIALOG_H
#define AGGIUNGIPRODOTTODIALOG_H

#include <QDialog>
#include "readFile.h"
#include "dbmanager.h"

namespace Ui {
class AggiungiProdottoDialog;
}

class AggiungiProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AggiungiProdottoDialog(QWidget *parent = nullptr);
    ~AggiungiProdottoDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AggiungiProdottoDialog *ui;
};

#endif // AGGIUNGIPRODOTTODIALOG_H
