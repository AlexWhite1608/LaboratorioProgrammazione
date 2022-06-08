#ifndef RIMUOVIPRODOTTODIALOG_H
#define RIMUOVIPRODOTTODIALOG_H

#include <QDialog>

namespace Ui {
class RimuoviProdottoDialog;
}

class RimuoviProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RimuoviProdottoDialog(QWidget *parent = nullptr);
    ~RimuoviProdottoDialog();

private:
    Ui::RimuoviProdottoDialog *ui;
};

#endif // RIMUOVIPRODOTTODIALOG_H
