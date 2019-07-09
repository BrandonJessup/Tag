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
    QSqlDatabase connection = QSqlDatabase::addDatabase(type);

    // Database name must be set outside of the addDatabase method,
    // otherwise it will not be set as the default connection.
    const QString fileName = "data";
    connection.setDatabaseName(fileName);

    connection.open();
}

void Database::createTablesIfTheyDontExist()
{
    createTypeTableIfDoesntExist();
    createFileTableIfDoesntExist();
    createTagTableIfDoesntExist();
    createFileTagTableIfDoesntExist();
}

void Database::createTypeTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists Type ("
                    "   TypeId integer primary key autoincrement,"
                    "   Name varchar(255) not null"
                    ")");
    query.exec();
}

void Database::createFileTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists File ("
                    "   FileId integer primary key autoincrement,"
                    "   TypeId integer not null,"
                    "   Name varchar(255) not null,"
                    "   FilePath varchar(255) not null"
                    "   foreign key(TypeId) references Type(TypeId),"
                    ")");
    query.exec();
}

void Database::createTagTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists Tag ("
                    "   TagId integer primary key autoincrement,"
                    "   Name varchar(255) not null"
                    ")");
    query.exec();
}

void Database::createFileTagTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists FileTag ("
                    "   FileId integer not null,"
                    "   TagId integer not null,"
                    "   foreign key(FileId) references File(FileId),"
                    "   foreign key(TagId) references Tag(TagId),"
                    "   primary key(FileId, TagId)"
                    ")");
    query.exec();
}
