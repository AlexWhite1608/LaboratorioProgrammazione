#include "itemdelegatepaint.h"
#include <QAbstractItemModel>

ItemDelegatePaint::ItemDelegatePaint(QObject *parent)
{
}

/* Colora la riga selezionata */
void ItemDelegatePaint::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(paintRequest && indexVector.contains(index)) {
        foreach(QModelIndex i, indexVector){
            painter->fillRect(option.rect, QColor(0,255,0));

            if( option.state & QStyle::State_Selected )
            {
                painter->fillRect(option.rect, option.palette.highlight());
            }

            QStyledItemDelegate::paint(painter, option, i);

        }

        //manda segnale che imposta il paintRequest a false
    }
    else
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
