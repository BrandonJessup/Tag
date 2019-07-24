#include "filetuple.h"

FileTuple::FileTuple()
{
    name = new QString;
    path = new QString;
    type = new QString;
}

FileTuple::FileTuple(const QString& name, const QString& path, const QString& type)
{
    this->name = new QString(name);
    this->path = new QString(path);
    this->type = new QString(type);
}

FileTuple::~FileTuple()
{
    if (name != nullptr) delete name;
    if (path != nullptr) delete path;
    if (type != nullptr) delete type;
}

void FileTuple::setName(const QString& name)
{
    *(this->name) = name;
}

void FileTuple::setPath(const QString& path)
{
    *(this->path) = path;
}

void FileTuple::setType(const QString& type)
{
    *(this->type) = type;
}

QString FileTuple::getName()
{
    return *name;
}

QString FileTuple::getPath()
{
    return *path;
}

QString FileTuple::getType()
{
    return *type;
}
