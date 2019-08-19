#include "tagtuple.h"

TagTuple::TagTuple()
{
    id = new int;
    name = new QString;
}

TagTuple::TagTuple(const int& id, const QString& name)
{
    this->id = new int(id);
    this->name = new QString(name);
}

TagTuple::TagTuple(const TagTuple& tagTuple)
{
    this->id = new int(tagTuple.getId());
    this->name = new QString(tagTuple.getName());
}

TagTuple::~TagTuple()
{
    if (id != nullptr) delete id;
    if (name != nullptr) delete name;
}

TagTuple& TagTuple::operator =(const TagTuple& tagTuple)
{
    this->setName(tagTuple.getName());
    this->setId(tagTuple.getId());
    return *this;
}

void TagTuple::setId(const int& id)
{
    *(this->id) = id;
}

void TagTuple::setName(const QString& name)
{
    *(this->name) = name;
}

int TagTuple::getId() const
{
    return *id;
}

QString TagTuple::getName() const
{
    return *name;
}

bool TagTuple::sortByName(const TagTuple& t1, const TagTuple& t2)
{
    return t1.getName() < t2.getName();
}
