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

    TagTuple& operator =(const TagTuple& tagTuple);

    void setId(const int& id);
    void setName(const QString& name);
    int getId() const;
    QString getName() const;

    static bool sortByName(const TagTuple& t1, const TagTuple& t2);

private:
    int* id;
    QString* name;
};

#endif // TAGTUPLE_H
