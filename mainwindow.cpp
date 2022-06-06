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

    //Setting tableView
    ui->tableView->setModel(dbModel);

    //Query che mostra l'intero DB
    QSqlQuery *initQuery = new QSqlQuery(DBManager::getDb());
    initQuery->prepare("SELECT * FROM Players");
    initQuery->exec();

    //Imposta il modello per la TableView
    MydbModel->setQuery(*initQuery);
    ui->tableView->setModel(myProxy);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete myProxy;
    delete dbModel;

    //Disconnessione dal db
    DBManager::disconnect();
}

