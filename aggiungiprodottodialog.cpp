#include "aggiungiprodottodialog.h"
#include "ui_aggiungiprodottodialog.h"

AggiungiProdottoDialog::AggiungiProdottoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AggiungiProdottoDialog)
{
    ui->setupUi(this);

    //Setting ComboBox con categorie estratte da file .txt
    QStringList categorie = readFile("C:/Dev/Qt/LaboratorioProgrammazione/Settings/categorie.txt");
    ui->comboBoxCategoria->addItems(categorie);
}

AggiungiProdottoDialog::~AggiungiProdottoDialog()
{
    delete ui;
}

/* Realizza la query che aggiunge il prodotto nel database */
void AggiungiProdottoDialog::on_buttonBox_accepted()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    if(!db.open())
        qDebug() << "Errore apertura database: " << db.lastError();

    QSqlQuery qry;
    qry.prepare("INSERT INTO Lista (Nome, Categoria, Quantità, Prezzo)"
                "VALUES(?, ?, ?, ?);");

    qry.addBindValue(ui->lineEditNome->text());
    qry.addBindValue(ui->comboBoxCategoria->currentText());
    qry.addBindValue(ui->spinBoxQuantita->value());
    qry.addBindValue(ui->doubleSpinBoxPrezzo->value());

    if(!qry.exec()){
        QMessageBox errorBox1;
        errorBox1.setWindowTitle("Aggiungi prodotto");
        errorBox1.setIcon(QMessageBox::Icon::Critical);
        errorBox1.setText("Errore: non è stato possibile inserire il prodotto, verificare che i dati inseriti siano corretti!");
        errorBox1.exec();
    }

    db.close();
}

