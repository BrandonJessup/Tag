#include "database.h"

Database* Database::instance = nullptr;

Database* Database::getInstance()
{
    if (instance == nullptr) {
        instance = new Database;
    }
    return instance;
}

void Database::addFile(const QString& name, const QString& path, const QString& type)
{
    // TODO
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
    createAndPopulateTypeTableIfDoesntExist();
    createFileTableIfDoesntExist();
    createTagTableIfDoesntExist();
    createFileTagTableIfDoesntExist();
}

void Database::createAndPopulateTypeTableIfDoesntExist()
{
    createTypeTableIfDoesntExist();
    populateTypeTable();
}

void Database::createTypeTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists Type ("
                    "   TypeId integer primary key autoincrement,"
                    "   Name varchar(255) unique not null"
                    ")");
    query.exec();
}

void Database::populateTypeTable()
{
    // If rows already exist in the table they will not be re-added
    // due to the unique constraint on the Name column.
    QSqlQuery query;
    query.exec("insert into Type (name) values('image')");
    query.exec("insert into Type (name) values('video')");
    query.exec("insert into Type (name) values('folder')");
    query.exec("insert into Type (name) values('other')");
}

void Database::createFileTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists File ("
                    "   FileId integer primary key autoincrement,"
                    "   TypeId integer not null,"
                    "   Name varchar(255) not null,"
                    "   Path varchar(255) not null"
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
