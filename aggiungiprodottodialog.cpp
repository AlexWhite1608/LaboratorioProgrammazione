#include "aggiungiprodottodialog.h"
#include "ui_aggiungiprodottodialog.h"

AggiungiProdottoDialog::AggiungiProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AggiungiProdottoDialog)
{
    ui->setupUi(this);
}

AggiungiProdottoDialog::~AggiungiProdottoDialog()
{
    delete ui;
}
