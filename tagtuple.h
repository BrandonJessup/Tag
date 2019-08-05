#ifndef TAGTUPLE_H
#define TAGTUPLE_H

#include <QString>

class TagTuple
{
public:
    TagTuple();
    TagTuple(const int& id, const QString& name);
    TagTuple(const TagTuple& tagTuple);

    ~TagTuple();

    void setId(const int& id);
    void setName(const QString& name);
    int getId() const;
    QString getName() const;

private:
    int* id;
    QString* name;
};

#endif // TAGTUPLE_H
