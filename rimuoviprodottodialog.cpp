#include "rimuoviprodottodialog.h"
#include "ui_rimuoviprodottodialog.h"

RimuoviProdottoDialog::RimuoviProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RimuoviProdottoDialog)
{
    ui->setupUi(this);

    //Setting ComboBox con categorie estratte da file .txt
    QFile file("C:/Dev/Qt/LaboratorioProgrammazione/Settings/categorie.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Errore apertura file" << file.errorString();
    }

    QTextStream categorie(&file);

    while(!categorie.atEnd()) {
        QString line = categorie.readLine();
        ui->comboBox->addItem(line);
    }

    file.close();
}

RimuoviProdottoDialog::~RimuoviProdottoDialog()
{
    delete ui;
}
