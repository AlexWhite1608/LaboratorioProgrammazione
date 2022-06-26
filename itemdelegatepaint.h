#ifndef ITEMDELEGATEPAINT_H
#define ITEMDELEGATEPAINT_H

#include <QStyledItemDelegate>
#include <QObject>
#include <QPainter>
#include <QDebug>

class ItemDelegatePaint : public QStyledItemDelegate
{
    Q_OBJECT
public:
    ItemDelegatePaint(QObject *parent = nullptr);

public slots:
    void paintRow(const QModelIndex pos);

private slots:
    void addProductToCartDB(QModelIndex index);

signals:
    void requestAddProductToCartDB(QModelIndex index) const;

    void refreshCartLabel() const;

protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    bool paintRequest = false;
    QVector<QModelIndex> indexVector;
};

#endif // ITEMDELEGATEPAINT_H
