#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>
#include <QBoxLayout>

class ButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBar(QWidget *parent = nullptr);

private:
    QBoxLayout* layout;

    void createLayout();

signals:

public slots:
};

#endif // BUTTONBAR_H
