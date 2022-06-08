#include "rimuoviprodottodialog.h"
#include "ui_rimuoviprodottodialog.h"

RimuoviProdottoDialog::RimuoviProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RimuoviProdottoDialog)
{
    ui->setupUi(this);
}

RimuoviProdottoDialog::~RimuoviProdottoDialog()
{
    delete ui;
}
