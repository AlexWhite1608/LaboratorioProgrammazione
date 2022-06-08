#include "dbmanager.h"

QString DBManager::dbName = "C:/Dev/Qt/LaboratorioProgrammazione/DatabaseSpesa.db";
QSqlDatabase DBManager::db;

bool DBManager::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    db.open();

    if(!db.isOpen()){
        lastErrorDB();
        return false;
    }

    return true;
}

bool DBManager::disconnect()
{
    if(db.isOpen())
        db.close();

    return true;
}

QString DBManager::lastErrorDB()
{
    return DBManager::db.lastError().text();
}

QSqlDatabase DBManager::getDb()
{
    return db;
}

QString DBManager::getDbName()
{
    return dbName;
}
