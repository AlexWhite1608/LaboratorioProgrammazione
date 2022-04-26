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

private:
    static QString dbName;
    static QSqlDatabase db;
};

#endif // DBMANAGER_H
