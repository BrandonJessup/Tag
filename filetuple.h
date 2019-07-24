#ifndef FILETUPLE_H
#define FILETUPLE_H

#include <QString>

class FileTuple
{
public:
    FileTuple();
    FileTuple(const int& id, const QString& name, const QString& path, const QString& type);

    ~FileTuple();

    void setId(const int& id);
    void setName(const QString& name);
    void setPath(const QString& path);
    void setType(const QString& type);
    int getId();
    QString getName();
    QString getPath();
    QString getType();

private:
    int* id;
    QString* name;
    QString* path;
    QString* type;
};

#endif // FILETUPLE_H
