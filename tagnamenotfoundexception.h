#ifndef TAGNAMENOTFOUNDEXCEPTION_H
#define TAGNAMENOTFOUNDEXCEPTION_H

#include <QString>

class TagNameNotFoundException
{
public:
    TagNameNotFoundException(const QString& message);

    QString getMessage() const;

private:
    QString message;
};

#endif // TAGNAMENOTFOUNDEXCEPTION_H
