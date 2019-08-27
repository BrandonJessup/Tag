#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QProgressDialog>
#include <QCoreApplication>

class ProgressDialog : public QProgressDialog
{
public:
    ProgressDialog(QWidget* parent, const QString& text, const int& maximum);

    void setValueToMaximum();
};

#endif // PROGRESSDIALOG_H
