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

#include "tagnamenotfoundexception.h"
#include "database.h"
#include "taglist.h"
#include "tagcolor.h"

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
    TagList* tagList;
    QComboBox* excludeDropDown;

    void createOuterLayout();
    void createGroupBox(const QString& title);
    void createGroupBoxLayout();
    void createSearchFieldLayout();
    void createTextField();
    void createExcludeDropDown();
    void createTagList();
    void relaySignals();

    void showPrompt(const QString& message);
    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void populateTagList(QList<TagTuple> tags, QList<TagTuple> excludeTags);

signals:
    void activeSearchTagsChanged(QList<int> tagIds, QList<int> excludeTagIds);

public slots:
    void addTag();
    void removeTagFromSearch(int tagId);
    void toggleTagInSearch(int tagId);
};

#endif // SEARCHPANEL_H
