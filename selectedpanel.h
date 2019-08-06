#ifndef SELECTEDPANEL_H
#define SELECTEDPANEL_H

#include "selected.h"
#include "subtagpanelbase.h"

class SelectedPanel : public SubTagPanelBase
{
    Q_OBJECT

public:
    explicit SelectedPanel(QWidget *parent = nullptr);

    void setSelectedFile(const int& file);
    void refreshTagList() override;
    void addTag() override;

private:
    int selectedFile;

    bool tagIsValid(const QString& tag);
    bool hasNonWhitespaceCharacter(const QString& tag);
    QString removeExcessWhitespace(QString tag);
    void relaySignals();

signals:

public slots:
    void removeTagFromSelectedFile(int id);
};

#endif // SELECTEDPANEL_H
