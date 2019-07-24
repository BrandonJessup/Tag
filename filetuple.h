#ifndef FILETUPLE_H
#define FILETUPLE_H

#include <QString>

class FileTuple
{
public:
    FileTuple();
    FileTuple(const int& id, const QString& name, const QString& path, const QString& type);
    FileTuple(const FileTuple& fileTuple);

    ~FileTuple();

    void setId(const int& id);
    void setName(const QString& name);
    void setPath(const QString& path);
    void setType(const QString& type);
    int getId() const;
    QString getName() const;
    QString getPath() const;
    QString getType() const;

private:
    int* id;
    QString* name;
    QString* path;
    QString* type;
};

#endif // FILETUPLE_H
