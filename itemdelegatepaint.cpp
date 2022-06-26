#include "itemdelegatepaint.h"
#include <QAbstractItemModel>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>

//FIXME: Quando si ricarica il database e vi è qualche cella colorata di verde, questa torna normale

ItemDelegatePaint::ItemDelegatePaint(QObject *parent)
{
    connect(this, SIGNAL( requestAddProductToCartDB(QModelIndex) ),
            this, SLOT( addProductToCartDB(QModelIndex) ));

    //Legge dalla tabella Carrello tutti i prodotti che sono nel carrello per poi colorare le righe corrispondenti
}

/* Colora la riga selezionata */
void ItemDelegatePaint::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //FIXME: non serve più guardare se l'index è presente in indexVector, ma di controlla se è presente in Carrello!

    if(paintRequest && indexVector.contains(index)) {
        foreach(QModelIndex i, indexVector){    //Per poter colorare più righe
            if(index == i){     //Garantisce che non si vada a sovrascrivere il prodotto

                painter->fillRect(option.rect, QColor(0,255,0));

                if( option.state & QStyle::State_Selected )
                {
                    painter->fillRect(option.rect, option.palette.highlight());
                }

                QStyledItemDelegate::paint(painter, option, i);

                emit refreshCartLabel();
            }
        }
    }

    else    //Colorazione standard di tutte le righe

    {
        painter->fillRect(option.rect, QColor(223, 241, 255));

        if( option.state & QStyle::State_Selected )
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        QStyledItemDelegate::paint(painter, option, index);
    }

}

/* Slot richiamato dal contextMenu della tableView quando si inserisce un prodotto nel carrello */
void ItemDelegatePaint::paintRow(const QModelIndex pos)
{
    paintRequest = true;    //FIXME: Serve?
    indexVector.append(pos);

    emit requestAddProductToCartDB(pos);

}

/* Inserisce prodotto corrispondente all'index all'interno della tabella Carrello */
void ItemDelegatePaint::addProductToCartDB(QModelIndex index)
{
    QSqlDatabase myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(QCoreApplication::applicationDirPath() + "/DatabaseSpesa.db");
    myDB.open();

    QSqlQuery *qry = new QSqlQuery(myDB);

    qry->prepare("INSERT INTO Carrello (ID) "
                 "VALUES(?);");

    qry->addBindValue(index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt());  //Ricava ID

    qry->exec();

    myDB.close();
}
