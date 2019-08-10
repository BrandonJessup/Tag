#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include <QWidget>
#include <QStackedLayout>
#include <QBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

#include "selected.h"
#include "taglist.h"
#include "tagtuple.h"

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
    TagList* tagList;

    void createOuterLayout();
    void createGroupBox(const QString& title);
    void createGroupBoxLayout();
    void createTextField();
    void createTagList();
    void relaySignals();

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString cleanUp(QString tag);
    void populateTagList(QList<TagTuple> tags);

signals:
    void tagClicked(int tagId);

public slots:
    void addTag();
    void removeTagFromSelectedFile(int id);
};

#endif // SELECTEDPANEL_H
