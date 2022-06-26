#include "itemdelegatepaint.h"
#include <QAbstractItemModel>
#include <QApplication>

//FIXME: Quando si aggiunge/toglie un prodotto dal database e vi è qualche cella colorata di verde, questa torna normale

ItemDelegatePaint::ItemDelegatePaint(QObject *parent)
{
}

/* Colora la riga selezionata */
void ItemDelegatePaint::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if(paintRequest && indexVector.contains(index)) {
        foreach(QModelIndex i, indexVector){    //Per poter colorare più righe
            if(index == i){     //Garantisce che non si vada a sovrascrivere il prodotto

                painter->fillRect(option.rect, QColor(0,255,0));

                if( option.state & QStyle::State_Selected )
                {
                    painter->fillRect(option.rect, option.palette.highlight());
                }

                QStyledItemDelegate::paint(painter, option, i);

                //TODO: aggiornare il contatore di quanti elementi sono nel carrello (signal). Impostare paintRequest = false per rimozione dal carrello

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
    paintRequest = true;
    indexVector.append(pos);
}
