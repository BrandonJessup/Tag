#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QDebug>

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
};

#endif // DATABASE_H
