#include "rimuoviprodottodialog.h"
#include "ui_rimuoviprodottodialog.h"

RimuoviProdottoDialog::RimuoviProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RimuoviProdottoDialog)
{
    ui->setupUi(this);

    QStringList categorie = readFile("C:/Dev/Qt/LaboratorioProgrammazione/Settings/categorie.txt");
    ui->comboBox->addItems(categorie);
}

RimuoviProdottoDialog::~RimuoviProdottoDialog()
{
    delete ui;
}
