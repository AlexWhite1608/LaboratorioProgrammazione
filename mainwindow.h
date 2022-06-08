#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQueryModel>
#include "customproxymodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadDatabase();

private slots:
    void on_actionAggiungi_prodotto_triggered();

private:
    Ui::MainWindow *ui;
    CustomProxyModel *myProxy;
    QSqlQueryModel *dbModel = new QSqlQueryModel();
};
#endif // MAINWINDOW_H
