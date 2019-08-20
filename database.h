#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QList>
#include <QSqlRecord>
#include <QDebug>

#include "filetuple.h"
#include "tagtuple.h"
#include "tagnamenotfoundexception.h"

class Database
{
public:
    static Database* getInstance();

    int addFile(const QString& name, const QString& path, const QString& type);
    void removeFile(const int& id);
    QList<FileTuple> getAllFiles();
    QList<FileTuple> getFilesThatMatchTags(QList<int> tagIds, QList<int> excludeTagIds);
    void addTagToFile(const QString& tag, const int& fileId);
    void addTag(const QString& tag);
    QList<TagTuple> getTagsOfFile(const int& fileId);
    void removeTagFromFile(const int& tagId, const int& fileId);
    int getIdOfTag(const QString& tag);
    QList<TagTuple> getTuplesOfTags(QList<int> tagIds);
    QStringList getAllTagNames();
    QStringList getAllTagNamesExcludingSpecial();
    bool filePathExists(const QString& path);
    bool isSpecialTag(const QString& tag);

    void debug_outputContentsOfTagTable();

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
    void addSpecialTags();
    void createFileTagTableIfDoesntExist();

    int getIdOfType(const QString& type);
    void removeTagsFromFile(const int& id);
    void removeUnusedTags();
    void giveFileInitialSpecialTags(const int& fileId);
    void applyUntaggedIfAppropriate(const int& fileId);
    void removeUntaggedIfAppropriate(const int& fileId);
    bool fileHasNonSpecialTags(const int& fileId);
};

#endif // DATABASE_H
