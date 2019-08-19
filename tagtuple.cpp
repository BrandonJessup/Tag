#include "tagtuple.h"

TagTuple::TagTuple()
{
    id = -1;
    name = "";
}

TagTuple::TagTuple(const int& id, const QString& name)
{
    this->id = id;
    this->name = name;
}

void TagTuple::setId(const int& id)
{
    this->id = id;
}

void TagTuple::setName(const QString& name)
{
    this->name = name;
}

int TagTuple::getId() const
{
    return id;
}

QString TagTuple::getName() const
{
    return name;
}

bool TagTuple::sortByName(const TagTuple& t1, const TagTuple& t2)
{
    return t1.getName() < t2.getName();
}
