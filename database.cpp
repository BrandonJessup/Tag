#include "database.h"

Database* Database::instance = nullptr;

Database* Database::getInstance()
{
    if (instance == nullptr) {
        instance = new Database;
    }
    return instance;
}

int Database::addFile(const QString& name, const QString& path, const QString& type)
{
    QSqlQuery query;
    query.prepare("insert into File (TypeId, Name, Path) values (:TypeId, :Name, :Path)");
    query.bindValue(":Name", name);
    query.bindValue(":Path", path);
    query.bindValue(":TypeId", getIdOfType(type));
    query.exec();

    query.prepare("select FileId from File where Path = :Path");
    query.bindValue(":Path", path);
    query.exec();

    int idIndex = query.record().indexOf("FileId");
    query.next();

    int fileId = query.record().value(idIndex).toInt();

    giveFileInitialSpecialTags(fileId);

    return fileId;
}

void Database::removeFile(const int& id)
{
    removeTagsFromFile(id);

    QSqlQuery query;
    query.prepare("delete from File where FileId = :FileId");
    query.bindValue(":FileId", id);
    query.exec();
}

void Database::removeTagsFromFile(const int& id)
{
    QSqlQuery query;
    query.prepare("delete from FileTag where FileId = :FileId");
    query.bindValue(":FileId", id);
    query.exec();

    removeUnusedTags();
}

QList<FileTuple> Database::getAllFiles()
{
    QList<FileTuple> files;

    QSqlQuery query("select File.FileId, File.Name, File.Path, Type.Name from File join Type on File.TypeId = Type.TypeId");
    int idIndex = query.record().indexOf("File.FileId");
    int nameIndex = query.record().indexOf("File.Name");
    int pathIndex = query.record().indexOf("File.Path");
    int typeIndex = query.record().indexOf("Type.Name");
    while(query.next()) {
        FileTuple file;
        file.setId(query.value(idIndex).toInt());
        file.setName(query.value(nameIndex).toString());
        file.setPath(query.value(pathIndex).toString());
        file.setType(query.value(typeIndex).toString());
        files.append(file);
    }

    return files;
}

QStringList Database::getAllTagNames()
{
    QStringList tags;

    QSqlQuery query("select Name from Tag");
    int nameIndex = query.record().indexOf("Name");
    while(query.next()) {
        tags << query.value(nameIndex).toString();
    }

    return tags;
}

QStringList Database::getAllTagNamesExcludingSpecial()
{
    QStringList tags;

    QSqlQuery query("select Name from Tag where IsSpecial = 0");
    int nameIndex = query.record().indexOf("Name");
    while(query.next()) {
        tags << query.value(nameIndex).toString();
    }

    return tags;
}


bool Database::filePathExists(const QString& path)
{
    QSqlQuery query;
    query.prepare("select Path from File where Path = :Path");
    query.bindValue(":Path", path);
    query.exec();

    return query.next();
}

QList<FileTuple> Database::getFilesThatMatchTags(QList<int> tagIds, QList<int> excludeTagIds)
{
    // TODO: Split up query into multiple methods.

    QList<FileTuple> files;

    QSqlQuery query;
    QString command = "";

    if (!tagIds.isEmpty()) {
        command += "select Frequency.FileId, File.Name, Type.Name, File.Path "
                   "from ("
                        "select FileTag.FileId, count(FileTag.FileId) as Matches "
                        "from FileTag "
                        "where FileTag.TagId in (";
        for (int tagId : tagIds) {
            command.append(":Tag");
            command.append(QString::number(tagId));
            command.append(",");
        }
        if (!tagIds.isEmpty()) {
            command.chop(1);
      }
        command.chop(1);
        command += ") ";
        command += "group by FileId) as Frequency "
                   "join File "
                   "on File.FileId = Frequency.FileId "
                   "join Type "
                   "on File.TypeId = Type.TypeId "
                   "where Frequency.Matches = ";
        command.append(QString::number(tagIds.size()));

        command += " and Frequency.FileId not in ("
                        "select Ignore.FileId "
                        "from ("
                            "select FileId, count(FileId) as Matches "
                            "from FileTag "
                            "where TagId in (";
        for (int tagId : excludeTagIds) {
            command.append(":Tag");
            command.append(QString::number(tagId));
            command.append(",");
        }
        if (!excludeTagIds.isEmpty()) {
            command.chop(1);
        }
        command += ") ";
        command += "group by FileId) as Ignore)";
    }
    else {
        command += "select File.FileId, File.Name, Type.Name, File.Path "
                   "from File "
                   "join Type "
                   "on Type.TypeId = File.TypeId "
                   "where File.FileId not in ("
                        "select Ignore.FileId "
                        "from ("
                            "select FileId, count(FileId) as Matches "
                            "from FileTag "
                            "where TagId in (";
        for (int tagId : excludeTagIds) {
            command.append(":Tag");
            command.append(QString::number(tagId));
            command.append(",");
        }
        if (!excludeTagIds.isEmpty()) {
            command.chop(1);
        }
        command += ") ";
        command += "group by FileId) as Ignore)";
    }

    query.prepare(command);

    for (int i = 0; i < tagIds.size(); ++i) {
        query.bindValue(i, tagIds[i]);
    }
    for (int i = 0; i < excludeTagIds.size(); ++i) {
        query.bindValue(i + tagIds.size(), excludeTagIds[i]);
    }
    query.exec();

    int idIndex = query.record().indexOf("FileId");
    int nameIndex = query.record().indexOf("File.Name");
    int pathIndex = query.record().indexOf("File.Path");
    int typeIndex = query.record().indexOf("Type.Name");

    while(query.next()) {
        FileTuple file;
        file.setId(query.value(idIndex).toInt());
        file.setName(query.value(nameIndex).toString());
        file.setPath(query.value(pathIndex).toString());
        file.setType(query.value(typeIndex).toString());
        files.append(file);
    }

    return files;
}

void Database::addTagToFile(const QString& tag, const int& fileId)
{
    addTag(tag);
    int tagId = getIdOfTag(tag);

    QSqlQuery query;
    query.prepare("insert into FileTag (FileId, TagId) values (:FileId, :TagId)");
    query.bindValue(":FileId", fileId);
    query.bindValue(":TagId", tagId);
    query.exec();

    removeUntaggedIfAppropriate(fileId);
}

void Database::addTag(const QString& tag)
{
    QSqlQuery query;
    query.prepare("insert into Tag (Name) values (:Name)");
    query.bindValue(":Name", tag);
    query.exec();
}

QList<TagTuple> Database::getTagsOfFile(const int& fileId)
{
    QSqlQuery query;

    query.prepare("select Tag.TagId, Tag.Name from Tag "
                  "where Tag.TagId in (select FileTag.TagId from FileTag where FileTag.FileId = :FileId)");
    query.bindValue(":FileId", fileId);
    query.exec();

    int idIndex = query.record().indexOf("Tag.TagId");
    int nameIndex = query.record().indexOf("Tag.Name");

    QList<TagTuple> tags;
    while (query.next()) {
        TagTuple tag;
        tag.setId(query.value(idIndex).toInt());
        tag.setName(query.value(nameIndex).toString());
        tags.append(tag);
    }

    return tags;
}

int Database::getIdOfType(const QString& type) {
    QSqlQuery query;
    query.prepare("select TypeId from Type where Name = :type");
    query.bindValue(":type", type);
    query.exec();
    query.first();
    return query.value(0).toInt();
}

int Database::getIdOfTag(const QString& tag)
{
    QSqlQuery query;
    query.prepare("select TagId from Tag where Name = :Name");
    query.bindValue(":Name", tag);
    query.exec();
    query.first();
    if (query.isValid()) {
        return query.value(0).toInt();
    }
    else {
        throw TagNameNotFoundException("Tag Name " + tag + " not found in database.");
    }
}

bool Database::isSpecialTag(const QString& tag)
{
    QSqlQuery query;
    query.prepare("select IsSpecial from Tag where Name = :Name");
    query.bindValue(":Name", tag);
    query.exec();
    int index = query.record().indexOf("IsSpecial");
    query.first();
    if (query.isValid()) {
        return query.value(index).toBool();
    }
    return false;
}

void Database::removeTagFromFile(const int& tagId, const int& fileId)
{
    QSqlQuery query;
    query.prepare("delete from FileTag where FileId = :FileId and TagId = :TagId");
    query.bindValue(":FileId", fileId);
    query.bindValue(":TagId", tagId);
    query.exec();

    removeUnusedTags();
    applyUntaggedIfAppropriate(fileId);
}

QList<TagTuple> Database::getTuplesOfTags(QList<int> tagIds)
{
    QList<TagTuple> tuples;

    if (!tagIds.isEmpty()) {
        QSqlQuery query;
        QString command = "select TagId, Name from Tag where TagId in (";
        for (int i = 0; i < tagIds.size(); ++i) {
            command.append(":Tag");
            command.append(QString::number(i));
            command.append(",");
        }
        command.chop(1);
        command += ")";
        query.prepare(command);

        for (int i = 0; i < tagIds.size(); ++i) {
            query.bindValue(i, tagIds[i]);
        }
        query.exec();

        int idIndex = query.record().indexOf("Tag.TagId");
        int nameIndex = query.record().indexOf("Tag.Name");

        while (query.next()) {
            TagTuple tag;
            tag.setId(query.value(idIndex).toInt());
            tag.setName(query.value(nameIndex).toString());
            tuples.append(tag);
        }
    }

    return tuples;
}

// This method should be called any time a tag is removed from a
// file.
void Database::removeUnusedTags()
{
    QSqlQuery query("delete from Tag where TagId not in (select TagId from FileTag) and IsSpecial = 0");
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
    addSpecialTags();
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
                    "   Path varchar(255) unique not null,"
                    "   foreign key(TypeId) references Type(TypeId)"
                    ")");
}

void Database::createTagTableIfDoesntExist()
{
    QSqlQuery query("create table if not exists Tag ("
                    "   TagId integer primary key autoincrement,"
                    "   Name varchar(255) unique not null,"
                    "   IsSpecial integer(1) default 0"
                    ")");
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
}

void Database::addSpecialTags()
{
    QSqlQuery query;
    query.exec("insert into Tag (Name, IsSpecial) values('untagged', 1)");
}

void Database::debug_outputContentsOfTagTable()
{
    QSqlQuery query("select TagId, Name, IsSpecial from Tag");
    int idIndex = query.record().indexOf("TagId");
    int nameIndex = query.record().indexOf("Name");
    int isSpecialIndex = query.record().indexOf("IsSpecial");
    while(query.next()) {
        qDebug() << query.value(idIndex).toString() << query.value(nameIndex).toString() << query.value(isSpecialIndex).toBool();
    }
}

void Database::giveFileInitialSpecialTags(const int& fileId)
{
    applyUntaggedIfAppropriate(fileId);
}

void Database::applyUntaggedIfAppropriate(const int& fileId)
{
    if (!fileHasNonSpecialTags(fileId)) {
        addTagToFile("untagged", fileId);
    }
}

void Database::removeUntaggedIfAppropriate(const int& fileId)
{
    if (fileHasNonSpecialTags(fileId)) {
        removeTagFromFile(getIdOfTag("untagged"), fileId);
    }
}

bool Database::fileHasNonSpecialTags(const int& fileId)
{
    QStringList tags;

    QSqlQuery query;
    query.prepare("select FileTag.TagId, FileTag.FileId, Tag.IsSpecial from FileTag "
                  "join Tag on FileTag.TagId = Tag.TagId "
                  "where Tag.IsSpecial = 0 and FileTag.FileId = :FileId");
    query.bindValue(":FileId", fileId);
    query.exec();

    return query.next();
}

bool Database::fileHasTag(const int& fileId, const QString& tag)
{
    QStringList tags;

    QSqlQuery query;
    query.prepare("select FileTag.TagId, FileTag.FileId from FileTag "
                  "join Tag on FileTag.TagId = Tag.TagId "
                  "where FileTag.FileId = :FileId and Tag.Name = :Tag");
    query.bindValue(":FileId", fileId);
    query.bindValue(":Tag", tag);
    query.exec();

    return query.next();
}
