#include "aggiungiprodottodialog.h"
#include "ui_aggiungiprodottodialog.h"
#include "dbmanager.h"

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

/* Realizza la query che aggiunge il prodotto nel database */
void AggiungiProdottoDialog::on_buttonBox_accepted()
{
    DBManager::connect();

    QSqlQuery qry;
    qry.prepare("INSERT INTO Lista (Nome, Categoria, Quantità, Prezzo)"
                "VALUES(?, ?, ?, ?)");

    qry.addBindValue(ui->lineEditNome->text());
    qry.addBindValue(ui->comboBoxCategoria->currentText());
    qry.addBindValue(ui->spinBoxQuantita->value());
    qry.addBindValue(ui->doubleSpinBoxPrezzo->value());

    if(!qry.isValid())
        qDebug() << "Errore esecuzione query aggiunta prodotto: " << qry.lastError();

    DBManager::disconnect();
}

