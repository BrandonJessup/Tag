#include "tagadderdialog.h"

TagAdderDialog::TagAdderDialog()
{
    createLayout();
    createTextField();
    createCompleter();
    createTagList();
    createButtonLayout();
    createButtons();
    updateAndLockSize();
    relaySignals();
}

void TagAdderDialog::createLayout()
{
    layout = new QVBoxLayout;
    this->setLayout(layout);
}

void TagAdderDialog::createTextField()
{
    textField = new QLineEdit;
    textField->setPlaceholderText("Enter tag");
    layout->addWidget(textField);
}

void TagAdderDialog::createCompleter()
{
    completer = new QCompleter(tagDictionary);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::InlineCompletion);
    textField->setCompleter(completer);
    initializeTagDictionary();
}

void TagAdderDialog::createTagList()
{
    tagList = new TagList(QSize(250, 100));
    layout->addWidget(tagList);
}

void TagAdderDialog::initializeTagDictionary() {
    Database* database = Database::getInstance();

    tagDictionary = database->getAllTagNames();
    QStringListModel* model = new QStringListModel(tagDictionary);
    completer->setModel(model);
}

void TagAdderDialog::createButtonLayout()
{
    buttonLayout = new QHBoxLayout;
    layout->addLayout(buttonLayout);
}

void TagAdderDialog::createButtons()
{
    cancelButton = new QPushButton("Cancel");
    buttonLayout->addWidget(cancelButton);
    cancelButton->setAutoDefault(false);
    connect(cancelButton, SIGNAL (clicked()), this, SLOT (reject()));

    buttonLayout->addStretch();

    addTagsButton = new QPushButton("Add Tags");
    buttonLayout->addWidget(addTagsButton);
    addTagsButton->setAutoDefault(false);
    connect(addTagsButton, SIGNAL (clicked()), this, SLOT (accept()));
}

void TagAdderDialog::relaySignals()
{
    connect(textField, SIGNAL (returnPressed()), this, SLOT (addTag()));
    connect(tagList, SIGNAL (tagToBeRemoved(QString)), this, SLOT (removeTag(QString)));
    connect(tagList, SIGNAL (tagClicked(QString)), this, SLOT (removeTag(QString)));
}

void TagAdderDialog::updateAndLockSize()
{
    this->setFixedSize(this->sizeHint());
}

void TagAdderDialog::addTag()
{
    QString tag = textField->text();
    textField->clear();
    if (tagIsValid(tag)) {
        tag = cleanUp(tag);
        if (!tagsToAdd.contains(tag)) {
            tagsToAdd.append(tag);
            refreshTagList();
        }
    }
}

void TagAdderDialog::removeTag(QString tagName)
{
    tagsToAdd.removeOne(tagName);
    refreshTagList();
}

bool TagAdderDialog::tagIsValid(const QString& tag)
{
    bool isValid = true;
    isValid &= !tag.isEmpty();
    isValid &= hasNonWhitespaceCharacter(tag);

    return isValid;
}

bool TagAdderDialog::hasNonWhitespaceCharacter(const QString& tag)
{
    for (int i = 0; i < tag.length(); ++i) {
        if (!tag[i].isSpace()) {
            return true;
        }
    }
    return false;
}

QString TagAdderDialog::cleanUp(QString tag)
{
    tag = tag.simplified();
    tag = tag.toLower();
    return tag;
}

void TagAdderDialog::refreshTagList()
{
    tagList->clear();
    std::sort(tagsToAdd.begin(), tagsToAdd.end());
    for (QString tag : tagsToAdd) {
        TagTuple tuple(0, tag);
        tagList->addTag(tuple);
    }
}

QStringList TagAdderDialog::getTagsToAdd()
{
    return tagsToAdd;
}

void TagAdderDialog::insertWidgetInLayout(int index, QWidget* widget)
{
    layout->insertWidget(index, widget);
}

void TagAdderDialog::setTagListSize(const QSize& size)
{
    tagList->setFixedSize(size);
}

void TagAdderDialog::setCancelButtonText(const QString& text)
{
    cancelButton->setText(text);
}
