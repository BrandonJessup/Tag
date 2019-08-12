#ifndef PROMPT_H
#define PROMPT_H

#include <QString>
#include <QMessageBox>

class Prompt
{
public:
    static void show(const QString& message);

protected:
    Prompt();
};

#endif // PROMPT_H
