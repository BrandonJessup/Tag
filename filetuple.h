#ifndef FILETUPLE_H
#define FILETUPLE_H

#include <QString>

class FileTuple
{
public:
    FileTuple();
    FileTuple(const QString& name, const QString& path, const QString& type);

    ~FileTuple();

    void setName(const QString& name);
    void setPath(const QString& path);
    void setType(const QString& type);
    QString getName();
    QString getPath();
    QString getType();

private:
    QString* name;
    QString* path;
    QString* type;
};

#endif // FILETUPLE_H
