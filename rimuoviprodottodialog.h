#ifndef RIMUOVIPRODOTTODIALOG_H
#define RIMUOVIPRODOTTODIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include "readFile.h"
#include "dbmanager.h"
#include <QMessageBox>

namespace Ui {
class RimuoviProdottoDialog;
}

class RimuoviProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RimuoviProdottoDialog(QWidget *parent = nullptr);
    ~RimuoviProdottoDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::RimuoviProdottoDialog *ui;
};

#endif // RIMUOVIPRODOTTODIALOG_H
