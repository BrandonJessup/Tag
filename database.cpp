#include "database.h"

Database* Database::instance = nullptr;

Database* Database::getInstance()
{
    if (instance == nullptr) {
        instance = new Database;
    }
    return instance;
}

Database::Database()
{
    connect();
    createTablesIfTheyDontExist();
}

// Connects to database, creating it if it doesn't already exist.
void Database::connect()
{
    const QString type = "QSQLITE";
    const QString fileName = "data";
    QSqlDatabase::addDatabase(type, fileName);
}

void Database::createTablesIfTheyDontExist()
{
    // TODO: Create File, Tag, and FileTag tables if they don't already exist.
}
