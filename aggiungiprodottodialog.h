#ifndef AGGIUNGIPRODOTTODIALOG_H
#define AGGIUNGIPRODOTTODIALOG_H

#include <QDialog>

namespace Ui {
class AggiungiProdottoDialog;
}

class AggiungiProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AggiungiProdottoDialog(QWidget *parent = nullptr);
    ~AggiungiProdottoDialog();

private:
    Ui::AggiungiProdottoDialog *ui;
};

#endif // AGGIUNGIPRODOTTODIALOG_H
