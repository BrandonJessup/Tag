#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QSqlRecord>

#include "filetuple.h"
#include "tagtuple.h"

class Database
{
public:
    static Database* getInstance();

    void addFile(const QString& name, const QString& path, const QString& type);
    void removeFile(const int& id);
    QList<FileTuple> getAllFiles();
    void addTagToFile(const QString& tag, const int& fileId);
    void addTag(const QString& tag);
    QList<TagTuple> getTagsOfFile(const int& fileId);

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
    int getIdOfTag(const QString& tag);
    void removeTagsFromFile(const int& id);
};

#endif // DATABASE_H
