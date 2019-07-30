#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QSqlRecord>

#include "filetuple.h"

class Database
{
public:
    static Database* getInstance();

    void addFile(const QString& name, const QString& path, const QString& type);
    void removeFile(const int& id);
    QList<FileTuple> getAllFiles();

protected:
    Database();

private:
    static Database* instance;

    void connect();
    void createTablesIfTheyDontExist();
    void createAndPopulateTypeTableIfDoesntExist();
    void createTypeTableIfDoesntExist();
    void populateTypeTable();
    void createFileTableIfDoesntExist();
    void createTagTableIfDoesntExist();
    void createFileTagTableIfDoesntExist();
    int getIdOfType(const QString& type);
};

#endif // DATABASE_H
