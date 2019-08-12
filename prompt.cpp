#include "prompt.h"

Prompt::Prompt()
{
    // Do nothing.
}

void Prompt::show(const QString& message)
{
    QMessageBox prompt;
    prompt.setText(message);
    prompt.exec();
}
