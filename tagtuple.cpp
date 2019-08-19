#include "tagtuple.h"

TagTuple::TagTuple()
{
    id = -1;
    name = "";
    color = TagColor::GREEN;
}

TagTuple::TagTuple(const int& id, const QString& name, const TagColor& color)
{
    this->id = id;
    this->name = name;
    this->color = color;
}

void TagTuple::setId(const int& id)
{
    this->id = id;
}

void TagTuple::setName(const QString& name)
{
    this->name = name;
}

void TagTuple::setColor(const TagColor& color)
{
    this->color = color;
}

int TagTuple::getId() const
{
    return id;
}

QString TagTuple::getName() const
{
    return name;
}

TagColor TagTuple::getColor() const
{
    return color;
}

bool TagTuple::alphabeticalSort(const TagTuple& t1, const TagTuple& t2)
{
    return t1.getName() < t2.getName();
}
