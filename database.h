#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>

class Database
{
public:
    static Database* getInstance();

protected:
    Database();

private:
    static Database* instance;

    void connect();
    void createTablesIfTheyDontExist();
    void createTypeTableIfDoesntExist();
    void createFileTableIfDoesntExist();
    void createTagTableIfDoesntExist();
    void createFileTagTableIfDoesntExist();
};

#endif // DATABASE_H
