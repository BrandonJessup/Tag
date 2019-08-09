#include "tagnamenotfoundexception.h"

TagNameNotFoundException::TagNameNotFoundException(const QString& message)
{
    this->message = message;
}

QString TagNameNotFoundException::getMessage() const
{
    return message;
}
