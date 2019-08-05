#ifndef SUBTAGPANELBASE_H
#define SUBTAGPANELBASE_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

#include "taglist.h"
#include "database.h"

// Because SearchPanel and SelectedPanel share a lot of functionality,
// code they share has been moved to this class for ease of
// maintenence.
class SubTagPanelBase : public QWidget
{
    Q_OBJECT

public:
    explicit SubTagPanelBase(QWidget *parent = nullptr);

protected:
    void setGroupLabel(const QString& label);
    void setTextFieldPlaceholder(const QString& placeHolder);
    QString getTextFieldContent();
    void clearTextField();

private:
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* innerLayout;
    QLineEdit* textField;
    TagList* tagList;

    void createOuterLayout();
    void createGroupBox();
    void createInnerLayout();
    void createTextField();
    void createTagList();

    void relaySignals();

signals:

public slots:
    virtual void addTag() = 0;
};

#endif // SUBTAGPANELBASE_H
