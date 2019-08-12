#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>

#include "selected.h"
#include "taglist.h"
#include "tagtuple.h"
#include "tagcolor.h"

class SelectedPanel : public QWidget
{
    Q_OBJECT

public:
    explicit SelectedPanel(QWidget *parent = nullptr);

    void setSelectedFile(const int& file);
    void refreshTagList();

private:
    int selectedFile;
    QStackedLayout* outerLayout;
    QGroupBox* groupBox;
    QBoxLayout* groupBoxLayout;
    QLineEdit* textField;
    QCompleter* completer;
    TagList* tagList;
    QStringList tagDictionary;

    void createOuterLayout();
    void createGroupBox(const QString& title);
    void createGroupBoxLayout();
    void createTextField();
    void createCompleter();
    void createTagList();
    void relaySignals();

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void populateTagList(QList<TagTuple> tags);

signals:
    void tagClicked(int tagId);
    void databaseTagsChanged();

public slots:
    void addTag();
    void removeTagFromSelectedFile(int id);
    void updateTagDictionary();
};

#endif // SELECTEDPANEL_H
