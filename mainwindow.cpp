#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TODO: Implementare connessione al db con il DatabaseManager

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
    ui->tableView->setModel(dbModel);

    //Proprietà TableView
    ui->tableView->hideColumn(0);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    ui->tableView->resizeColumnToContents(1);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete myProxy;
    delete dbModel;

    //Disconnessione dal db
    DBManager::disconnect();
}

