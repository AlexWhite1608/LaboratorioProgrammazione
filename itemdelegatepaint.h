#ifndef ITEMDELEGATEPAINT_H
#define ITEMDELEGATEPAINT_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QPainter>

class ItemDelegatePaint : public QStyledItemDelegate
{
public:
    ItemDelegatePaint();

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // ITEMDELEGATEPAINT_H
