#include "itemdelegatepaint.h"

ItemDelegatePaint::ItemDelegatePaint()
{

}

/* Colora la riga selezionata */
void ItemDelegatePaint::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->fillRect(option.rect,QColor(0,255,0)); //Colore verde

    if( option.state & QStyle::State_Selected ) //Per la selezione
    {
        painter->fillRect(option.rect, option.palette.highlight());
    }


    QStyledItemDelegate::paint(painter,option,index);
}
