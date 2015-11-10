#ifndef EDITTULPAWIDGET_H
#define EDITTULPAWIDGET_H

#include <QtWidgets>
#include "../fonctions_json.h"
#include "../Objects/tulpa.h"

enum Layouts{
    LAYOUT_NAME = 0,
    LAYOUT_BIRTH,
    LAYOUT_FIRST_WORD,
    LAYOUT_END_LIST
};

enum Labels{
    LABEL_NAME = 0,
    LABEL_BIRTH,
    LABEL_FIRST_WORD,
};

enum LineEdits{
    LINE_EDIT_NAME = 0,
    LINE_EDIT_BIRTH,
    LINE_EDIT_FIRST_WORD,
};

const QString label_names[3] = {"Name","Birth","First Word"};

class AddTulpaWidget : public QWidget
{
    Q_OBJECT
public:
    AddTulpaWidget(QWidget *parent = 0);
    AddTulpaWidget(QString name, QWidget *parent = 0);
    void loadTulpa(QString name);
    void loadUI();
    void loadPersonality(QStringList personality);
    QStringList parsePersonality(QString string);

signals:
    void finished();

public slots:
    void setPersonality();
    void save();
    void refreshPersonality();

private:
    Tulpa tulpa;

    QStringList personalityTraits;

    QString path;

    QList<QLineEdit*> lineEdits;
    QList<QLabel*> labels;
    QList<QHBoxLayout*> layouts;

    QList<QLabel*> labelsPersonality;

    QVBoxLayout *mainLayout;

    QStringListModel *model;
    QListView *view;

    Json::Value root;
};

#endif // ADDTULPAWIDGET_H
