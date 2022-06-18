#include "itemdelegatepaint.h"
#include <QAbstractItemModel>

ItemDelegatePaint::ItemDelegatePaint()
{
}

/* Colora la riga selezionata */
void ItemDelegatePaint::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(paintRequest &&
       index.row() == productIndex.row() &&
       index.column() == productIndex.column()) {

        painter->fillRect(option.rect, QColor(0,255,0)); //Colore verde

        if( option.state & QStyle::State_Selected ) //Per la selezione
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        QStyledItemDelegate::paint(painter, option, productIndex);
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
    productIndex = pos;
}
