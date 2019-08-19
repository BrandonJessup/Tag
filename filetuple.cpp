#include "filetuple.h"

FileTuple::FileTuple()
{
    id = -1;
    name = "";
    path = "";
    type = "";
}

FileTuple::FileTuple(const int& id, const QString& name, const QString& path, const QString& type)
{
    this->id = id;
    this->name = name;
    this->path = path;
    this->type = type;
}

void FileTuple::setId(const int& id)
{
    this->id = id;
}

void FileTuple::setName(const QString& name)
{
    this->name = name;
}

void FileTuple::setPath(const QString& path)
{
    this->path = path;
}

void FileTuple::setType(const QString& type)
{
    this->type = type;
}

int FileTuple::getId() const
{
    return id;
}

QString FileTuple::getName() const
{
    return name;
}

QString FileTuple::getPath() const
{
    return path;
}

QString FileTuple::getType() const
{
    return type;
}
