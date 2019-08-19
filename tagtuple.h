#ifndef TAGTUPLE_H
#define TAGTUPLE_H

#include <QString>

#include "tagcolor.h"

class TagTuple
{
public:
    TagTuple();
    TagTuple(const int& id, const QString& name, const TagColor& color = TagColor::GREEN);

    void setId(const int& id);
    void setName(const QString& name);
    void setColor(const TagColor& color);
    int getId() const;
    QString getName() const;
    TagColor getColor() const;

    static bool alphabeticalSort(const TagTuple& t1, const TagTuple& t2);

private:
    int id;
    QString name;
    TagColor color;
};

#endif // TAGTUPLE_H
