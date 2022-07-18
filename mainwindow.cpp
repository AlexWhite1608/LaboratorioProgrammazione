#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO: Implementare connessione al db con il DatabaseManager

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Crezione del contextMenu
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT ( createContextMenu(QPoint) )
            );

    //Setting delegate
    delegate = new ItemDelegatePaint(this);
    ui->tableView->setItemDelegate(delegate);

    //Richiesta di aggiunta del prodotto al carrello
    connect(this, SIGNAL( requestAddCartDelegate(QModelIndex) ),
            delegate, SLOT( paintRow(QModelIndex) ));

    //Si richiama per impostare il valore attuale dei prodotti nel carrello
    onRefreshRequested();

    //Setting label per numero prodotti nel carrello
    connect(delegate, SIGNAL( refreshCartLabel() ),
            this, SLOT( onRefreshRequested() ));

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
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

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
    delete delegate;
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

/* Costruisce il contextMenu */
void MainWindow::createContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    QMenu *menu = new QMenu(this);

    //Aggiunge azione addToCart tramite lambda
    if(index.column() == 1){
        QAction *aggiungiAlCarrello = menu->addAction("Aggiungi al carrello");
        connect(aggiungiAlCarrello, &QAction::triggered,
                this, [this, pos]{ addToCartDelegate(pos); });

    //Aggiunge azione removeProduct tramite lambda
    QAction *rimuoviProdotto = menu->addAction("Rimuovi prodotto");
    connect(rimuoviProdotto, &QAction::triggered,
            this, [this, pos]{ removeProduct(pos); });


    //TODO: L'azione appare soltanto se il prodotto è nel carrello!

    //Aggiunge azione removeProductCart tramite lambda
    QAction *rimuoviProdottoCarrello = menu->addAction("Rimuovi dal carrello");
    connect(rimuoviProdottoCarrello, &QAction::triggered,
            this, [this, pos]{ removeProductCart(pos); });
    }

    menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

/* Elimina il prodotto selezionato tramite contextMenu */
void MainWindow::removeProduct(const QPoint &pos)
{
    //TODO: Quando si rimuove definitivamente il prodotto occorre rimuoverlo anche dal carrello!

    QModelIndex index = ui->tableView->indexAt(pos);

    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    QSqlQuery *qry = new QSqlQuery(myDB);

    qry->prepare("DELETE FROM Lista WHERE Id = ?");
    qry->addBindValue(index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt());  //Ricava ID
    qry->exec();

    //Elimina il prodotto anche dal carrello
    qry->prepare("DELETE FROM Carrello WHERE Id = ?");
    qry->addBindValue(index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt());  //Ricava ID
    qry->exec();

    myDB.close();
    delete qry;

    MainWindow::loadDatabase();
}

/* Rimozione del prodotto selezionato dal carrello andando ad aggiornare il DB */
void MainWindow::removeProductCart(const QPoint &pos)
{
    QModelIndex index = ui->tableView->indexAt(pos);

    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    //Controlla che il prodotto sia effettivamente nel carrello
    QSqlQuery *checkQry = new QSqlQuery(myDB);

    checkQry->prepare("SELECT FROM Carrello WHERE Id = ?");
    checkQry->addBindValue(index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt());  //Ricava ID

    if(!checkQry->isValid()){
        qDebug() << "Prodotto non è nel carrello!";
        return;
    }

    QSqlQuery *qry = new QSqlQuery(myDB);

    qry->prepare("DELETE FROM Carrello WHERE Id = ?");
    qry->addBindValue(index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt());  //Ricava ID
    qry->exec();

    myDB.close();

    onRefreshRequested();
}

/* Sposta il prodotto selezionato dalla lista al carrello */
void MainWindow::addToCartDelegate(const QPoint &pos)
{

    QModelIndex productIndex = ui->tableView->indexAt(pos);

    emit requestAddCartDelegate(productIndex);

}

/* Gestisce la label che indica quanti elementi ci sono nel carrello */
void MainWindow::onRefreshRequested()
{
    //FIXME: quando si elimina un prodotto dalla lista si deve modificare il counter!

    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");
    int count = 0;

    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    QSqlQuery qry(myDB);
    qry.prepare("SELECT * FROM Carrello");
    qry.exec();

    while(qry.next())
        count++;

    myDB.close();

    ui->labelCarrello->setText("Carrello: " + QString::number(count));
}

CustomProxyModel *MainWindow::getMyProxy() const
{
    return myProxy;
}

QSqlQueryModel *MainWindow::getDbModel() const
{
    return dbModel;
}


