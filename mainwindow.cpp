#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Connessione al DB
    DBManager::connect();

    //Query che mostra l'intero DB
    QSqlQuery *initQuery = new QSqlQuery(DBManager::getDb());
    initQuery->prepare("SELECT * FROM Players");
    if(!initQuery->isValid())
        qDebug() << "Errore nella query" << initQuery->lastError();

    //Imposta il modello per la TableView
    dbModel->setQuery(*initQuery);
    ui->tableView->setModel(dbModel);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete myProxy;
    delete dbModel;

    //Disconnessione dal db
    DBManager::disconnect();
}

