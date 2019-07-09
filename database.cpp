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
    createFileTableIfDoesntExist();
    createTagTableIfDoesntExist();
    createFileTagTableIfDoesntExist();
}

void Database::createFileTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists File ("
                    "   FileId integer primary key autoincrement,"
                    "   Name varchar(255) not null,"
                    "   Extension varchar(255) not null,"
                    "   FilePath varchar(255) not null"
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
