#ifndef SEARCHPANEL_H
#define SEARCHPANEL_H

#include <QWidget>
#include <QStackedLayout>
#include <QGroupBox>
#include <QBoxLayout>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QComboBox>
#include <QCompleter>
#include <QStringListModel>

#include <algorithm>

#include "tagnamenotfoundexception.h"
#include "database.h"
#include "taglist.h"
#include "tagcolor.h"
#include "prompt.h"

class SearchPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SearchPanel(QWidget *parent = nullptr);

    void refreshTagList();

    enum DropDownIndex {
        INCLUDE = 0,
        EXCLUDE
    };

private:
    QList<int> activeSearchTags;
    QList<int> activeExcludeTags;
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* groupBoxLayout;
    QBoxLayout* searchFieldLayout;
    QLineEdit* textField;
    QStringList tagDictionary;
    QCompleter* completer;
    TagList* tagList;
    QComboBox* excludeDropDown;

    void createOuterLayout();
    void createGroupBox(const QString& title);
    void createGroupBoxLayout();
    void createSearchFieldLayout();
    void createTextField();
    void createCompleter();
    void createExcludeDropDown();
    void createTagList();
    void relaySignals();

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void populateTagList(QList<TagTuple> tags, QList<TagTuple> excludeTags);
    void colorTagsRed(QList<TagTuple>& tags);

signals:
    void activeSearchTagsChanged(QList<int> tagIds, QList<int> excludeTagIds);

public slots:
    void addTag();
    void removeTagFromSearch(int tagId);
    void toggleTagInSearch(int tagId);
    void updateTagDictionary();
};

#endif // SEARCHPANEL_H
