#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QtSql>

/* Gestisce l'interfacciamento con il database */
class DBManager
{
public:
    DBManager();

    static bool connect();

    static bool disconnect();

    static QString lastErrorDB();

    static QSqlDatabase getDb();

    static QString getDbName();

    static QSqlDatabase db;

private:
    static QString dbName;
};

#endif // DBMANAGER_H
