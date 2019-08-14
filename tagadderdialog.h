#ifndef TAGADDERDIALOG_H
#define TAGADDERDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QCompleter>
#include <QStringListModel>

#include "taglist.h"

class TagAdderDialog : public QDialog
{
    Q_OBJECT

public:
    TagAdderDialog();

    QStringList getTagsToAdd();

private:
    QStringList tagsToAdd;
    QStringList tagDictionary;
    QBoxLayout* layout;
    QLineEdit* textField;
    QCompleter* completer;
    TagList* tagList;
    QBoxLayout* buttonLayout;
    QPushButton* cancelButton;
    QPushButton* addTagsButton;

    void createLayout();
    void createTextField();
    void createCompleter();
    void initializeTagDictionary();
    void createTagList();
    void createButtonLayout();
    void createButtons();
    void relaySignals();

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void refreshTagList();

protected:
    void insertWidgetInLayout(int index, QWidget* widget);
    void setTagListSize(const QSize& size);
    void setCancelButtonText(const QString& text);

public slots:
    void addTag();
    void removeTag(QString tagName);
};

#endif // TAGADDERDIALOG_H
