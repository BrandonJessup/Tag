#include "filetuple.h"

FileTuple::FileTuple()
{
    id = new int;
    name = new QString;
    path = new QString;
    type = new QString;
}

FileTuple::FileTuple(const int& id, const QString& name, const QString& path, const QString& type)
{
    this->id = new int(id);
    this->name = new QString(name);
    this->path = new QString(path);
    this->type = new QString(type);
}

FileTuple::FileTuple(const FileTuple& fileTuple)
{
    this->id = new int(fileTuple.getId());
    this->name = new QString(fileTuple.getName());
    this->path = new QString(fileTuple.getPath());
    this->type = new QString(fileTuple.getType());
}

FileTuple::~FileTuple()
{
    if (id != nullptr) delete id;
    if (name != nullptr) delete name;
    if (path != nullptr) delete path;
    if (type != nullptr) delete type;
}

void FileTuple::setId(const int& id)
{
    *(this->id) = id;
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

int FileTuple::getId() const
{
    return *id;
}

QString FileTuple::getName() const
{
    return *name;
}

QString FileTuple::getPath() const
{
    return *path;
}

QString FileTuple::getType() const
{
    return *type;
}
