#include "progressdialog.h"

ProgressDialog::ProgressDialog(QWidget* parent, const QString& text, const int& maximum) : QProgressDialog(parent)
{
    setLabelText(text);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    setWindowModality(Qt::WindowModal);
    setCancelButton(nullptr);
    setMaximum(maximum);
    setMinimumDuration(0);
}

void ProgressDialog::setValueToMaximum()
{
    setValue(maximum());
}
