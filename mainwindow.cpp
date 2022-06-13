#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO: Implementare connessione al db con il DatabaseManager

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Setting impostazioni proxy model
    myProxy->setHeaderData(1, Qt::Horizontal, "Nome");
    myProxy->setHeaderData(2, Qt::Horizontal, "Cateogoria");
    myProxy->setHeaderData(3, Qt::Horizontal, "Quantità");
    myProxy->setHeaderData(4, Qt::Horizontal, "Prezzo");


    //Proprietà righe/colonne TableView
    ui->tableView->hideColumn(0);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    ui->tableView->resizeColumnToContents(1);

    //Stylesheet
    ui->tableView->setStyleSheet(
                "QTableView::item:selected { background:#54698D; }"
                "QHeaderView::section { color: white; background-color: #54698D; }"
                );

    //Setting completer
    completer = new QCompleter(dbModel, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionColumn(1);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    ui->lineEditFilter->setCompleter(completer);

    //Select iniziale per visualizzare il db
    loadDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myProxy;
    delete dbModel;
    delete completer;
}

/* Ricarica il database per aggiornare la view */
void MainWindow::loadDatabase()
{
    //Connessione al DB
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    if(!db.open())
        qDebug() << "Errore apertura database: " << db.lastError();

    //Select che mostra intero database
    QSqlQuery *initQuery = new QSqlQuery(db);
    initQuery->prepare("SELECT * FROM Lista");
    if(!initQuery->exec())
        qDebug() << "Errore nella query: " << initQuery->lastError();

    //Imposta il modello per la TableView
    dbModel->setQuery(*initQuery);
    myProxy->setSourceModel(dbModel);
    ui->tableView->setModel(myProxy);
    ui->tableView->hideColumn(0);
    ui->tableView->verticalHeader()->setVisible(false);
}

/* Form per aggiungere un nuovo prodotto nella lista */
void MainWindow::on_actionAggiungi_prodotto_triggered()
{
    AggiungiProdottoDialog mDialog(this);
    mDialog.setModal(true);
    mDialog.exec();

    //Ricarica il database dopo la query
    MainWindow::loadDatabase();
}

/* Form per rimuovere un prodotto */
void MainWindow::on_actionRimuovi_prodotto_triggered()
{
    RimuoviProdottoDialog mDialog(this);
    mDialog.setModal(true);
    mDialog.exec();

    //Ricarica il database dopo la query
    MainWindow::loadDatabase();
}

/* Filtra i prodotti in base alla ricerca */
void MainWindow::on_lineEditFilter_textChanged(const QString &arg1)
{
    myProxy->setFilterFixedString(arg1);
    ui->lineEditFilter->completer()->complete();
    completer->setCompletionColumn(ui->comboBox->currentIndex() + 1);
}

/* Cambia il criterio di ricerca */
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index == 3)
        index = -1;
    myProxy->setFilterKeyColumn(index+1);
}

CustomProxyModel *MainWindow::getMyProxy() const
{
    return myProxy;
}

QSqlQueryModel *MainWindow::getDbModel() const
{
    return dbModel;
}
