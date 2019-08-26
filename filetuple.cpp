#include "filetuple.h"

FileTuple::FileTuple()
{
    id = -1;
    name = "";
    path = "";
    type = "";
    thumbnail = "";
}

FileTuple::FileTuple(const int& id, const QString& name, const QString& path, const QString& type, const QString& thumbnail)
{
    this->id = id;
    this->name = name;
    this->path = path;
    this->type = type;
    this->thumbnail = thumbnail;
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

void FileTuple::setThumbnail(const QString& thumbnail)
{
    this->thumbnail = thumbnail;
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

QString FileTuple::getThumbnail() const
{
    return thumbnail;
}
