#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TODO: Implementare connessione al db con il DatabaseManager

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

    //Select iniziale per visualizzare il db
    loadDatabase();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete myProxy;
    delete dbModel;
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

void MainWindow::on_actionRimuovi_prodotto_triggered()
{
    RimuoviProdottoDialog mDialog(this);
    mDialog.setModal(true);
    mDialog.exec();

    //Ricarica il database dopo la query
    MainWindow::loadDatabase();
}
