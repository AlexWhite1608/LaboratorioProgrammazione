#include "rimuoviprodottodialog.h"
#include "ui_rimuoviprodottodialog.h"

RimuoviProdottoDialog::RimuoviProdottoDialog(QSqlQueryModel *model, QSortFilterProxyModel *proxy, QWidget *parent) :
    dbModelDelete(model),
    proxyDelete(proxy),
    QDialog(parent),
    ui(new Ui::RimuoviProdottoDialog)
{
    ui->setupUi(this);

    QStringList categorie = readFile("C:/Dev/Qt/LaboratorioProgrammazione/Settings/categorie.txt");
    ui->comboBox->addItems(categorie);

    //Apertura DB
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    //Crea la query iniziale
    QSqlQuery *initQuery = new QSqlQuery(myDB);
    initQuery->prepare("SELECT * FROM Lista");
    initQuery->exec();
    dbModelDelete->setQuery(*initQuery);

    //Impostazione del Completer
    completerDelete = new QCompleter(dbModelDelete, this);
    completerDelete->setCompletionMode(QCompleter::InlineCompletion);
    completerDelete->setCaseSensitivity(Qt::CaseInsensitive);
    completerDelete->setCompletionColumn(1);
    ui->lineEdit->setCompleter(completerDelete);

    delete initQuery;

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

/* Ricerca il prodotto in base a cosa si scrive nella LineEdit */
void RimuoviProdottoDialog::on_lineEdit_textChanged(const QString &arg1)
{
    proxyDelete->setFilterFixedString(arg1);
    ui->lineEdit->completer()->complete();
}
