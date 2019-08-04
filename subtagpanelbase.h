#ifndef SUBTAGPANELBASE_H
#define SUBTAGPANELBASE_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

#include "taglist.h"

// Because SearchPanel and SelectedPanel share a lot of functionality,
// code they code share has been moved to this class for ease of
// maintenence.
class SubTagPanelBase : public QWidget
{
    Q_OBJECT

public:
    explicit SubTagPanelBase(QWidget *parent = nullptr);

protected:
    void setGroupLabel(const QString& label);
    void setTextFieldPlaceholder(const QString& placeHolder);

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

signals:

public slots:
};

#endif // SUBTAGPANELBASE_H
