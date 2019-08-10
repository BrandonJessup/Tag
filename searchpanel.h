#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QStackedLayout>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>

#include "tagnamenotfoundexception.h"
#include "database.h"
#include "taglist.h"

class SearchPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPanel(QWidget *parent = nullptr);

    void refreshTagList();

private:
    QList<int> activeSearchTags;
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* groupBoxLayout;
    QBoxLayout* searchFieldLayout;
    QLineEdit* textField;
    TagList* tagList;

    void createOuterLayout();
    void createGroupBox(const QString& title);
    void createGroupBoxLayout();
    void createSearchFieldLayout();
    void createTextField();
    void createTagList();
    void relaySignals();

    void showPrompt(const QString& message);
    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void populateTagList(QList<TagTuple> tags);

signals:
    void activeSearchTagsChanged(QList<int> tagIds);

public slots:
    void addTag();
    void removeTagFromSearch(int tagId);
    void toggleTagInSearch(int tagId);
};

#endif // SEARCHPANEL_H
