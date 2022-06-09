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

/* Elimina il prodotto selezionato dal db con una query */
void RimuoviProdottoDialog::on_buttonBox_accepted()
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    QSqlQuery qry;
    qry.prepare("DELETE FROM Lista WHERE Nome = ? AND Categoria = ?");

    qry.addBindValue(ui->lineEdit->text());
    qry.addBindValue(ui->comboBox->currentText());

    if(!qry.exec()){
        QMessageBox errorBox1;
        errorBox1.setWindowTitle("Rimuovi prodotto");
        errorBox1.setIcon(QMessageBox::Icon::Critical);
        errorBox1.setText("Errore: non è stato possibile rimuovere il prodotto, verificare che i dati inseriti siano corretti!");
        errorBox1.exec();
    }

    myDB.close();
}
