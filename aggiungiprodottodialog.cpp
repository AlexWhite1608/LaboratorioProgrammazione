#include "aggiungiprodottodialog.h"
#include "ui_aggiungiprodottodialog.h"
#include "dbmanager.h"

AggiungiProdottoDialog::AggiungiProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AggiungiProdottoDialog)
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
//        QStringList fields = line.split(";");
        ui->comboBoxCategoria->addItem(line);
    }

    file.close();
}

AggiungiProdottoDialog::~AggiungiProdottoDialog()
{
    delete ui;
}

/* Realizza la query che aggiunge il prodotto nel database */
void AggiungiProdottoDialog::on_buttonBox_accepted()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Dev/Qt/LaboratorioProgrammazione/DatabaseSpesa.db");
    if(!db.open())
        qDebug() << "Errore apertura database: " << db.lastError();

    QSqlQuery qry;
    qry.prepare("INSERT INTO Lista (Nome, Categoria, Quantità, Prezzo)"
                "VALUES(?, ?, ?, ?);");

    qry.addBindValue(ui->lineEditNome->text());
    qry.addBindValue(ui->comboBoxCategoria->currentText());
    qry.addBindValue(ui->spinBoxQuantita->value());
    qry.addBindValue(ui->doubleSpinBoxPrezzo->value());
    qry.exec();

    db.close();
}

