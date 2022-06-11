#ifndef RIMUOVIPRODOTTODIALOG_H
#define RIMUOVIPRODOTTODIALOG_H

#include <QDialog>
#include <QDebug>
#include <QFile>
#include "readFile.h"
#include "dbmanager.h"
#include <QMessageBox>
#include <QCompleter>

namespace Ui {
class RimuoviProdottoDialog;
}

class RimuoviProdottoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RimuoviProdottoDialog(QSqlQueryModel *model, QSortFilterProxyModel *proxy, QWidget *parent = nullptr);
    ~RimuoviProdottoDialog();

private slots:
    void on_buttonBox_accepted();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::RimuoviProdottoDialog *ui;
    QSqlQueryModel *dbModelDelete;
    QSortFilterProxyModel *proxyDelete;
    QCompleter *completerDelete;
};

#endif // RIMUOVIPRODOTTODIALOG_H
