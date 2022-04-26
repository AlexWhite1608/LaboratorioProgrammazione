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

    //Setting header del proxy
    myProxy->setHeaderData(1, Qt::Horizontal, "Prodotto");
    myProxy->setHeaderData(2, Qt::Horizontal, "Categoria");
    myProxy->setHeaderData(3, Qt::Horizontal, "Quantità");
    myProxy->setHeaderData(4, Qt::Horizontal, "Prezzo");

    //Setting tableView
    ui->tableView->setModel(myProxy);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnToContents(1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->sortByColumn(1, Qt::SortOrder::AscendingOrder);
    ui->tableView->resizeColumnToContents(1);
}

MainWindow::~MainWindow()
{
    delete ui;

    //Disconnessione dal db
    DBManager::disconnect();
}

