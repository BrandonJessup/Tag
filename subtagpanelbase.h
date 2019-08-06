#ifndef SUBTAGPANELBASE_H
#define SUBTAGPANELBASE_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

#include "userrole.h"
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

    virtual void refreshTagList() = 0;

protected:
    TagList* tagList;

    void setGroupLabel(const QString& label);
    void setTextFieldPlaceholder(const QString& placeHolder);
    QString getTextFieldContent();
    void clearTextField();

    void populateTagList(QList<TagTuple> tags);

private:
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* innerLayout;
    QLineEdit* textField;

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
