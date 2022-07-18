#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "customproxymodel.h"
#include "dbmanager.h"
#include "aggiungiprodottodialog.h"
#include "rimuoviprodottodialog.h"
#include "itemdelegatepaint.h"
#include <QCompleter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    QSqlQueryModel *getDbModel() const;

    CustomProxyModel *getMyProxy() const;

private:
    void loadDatabase();

private slots:
    void on_actionAggiungi_prodotto_triggered();

    void on_actionRimuovi_prodotto_triggered();

    void on_lineEditFilter_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void createContextMenu(const QPoint& pos);

    void removeProduct(const QPoint& pos);

    void removeProductCart(const QPoint& pos);

    void addToCartDelegate(const QPoint& pos);

    void onRefreshRequested();

signals:
    void requestAddCartDelegate(const QModelIndex pos);

private:
    Ui::MainWindow *ui;
    CustomProxyModel *myProxy = new CustomProxyModel();
    QSqlQueryModel *dbModel = new QSqlQueryModel();
    QCompleter *completer = nullptr;
    ItemDelegatePaint *delegate = nullptr;
};
#endif // MAINWINDOW_H
