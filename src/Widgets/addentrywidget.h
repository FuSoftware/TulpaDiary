#ifndef ADDENTRYWIDGET_H
#define ADDENTRYWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include <iostream>
#include "constantes.h"

#include "json/json.h"
#include "fonctions.h"
#include "fonctions_json.h"
#include "../Objects/tulpa.h"

enum Actions
{
    ACTION_ACTIVE_T =0,
    ACTION_ACTIVE_V,
    ACTION_ACTIVE_B,
    ACTIOn_PASSIVE,
    ACTION_MEDITATION,
    ACTION_END_LIST
};

class AddEntryWidget : public QWidget
{
    Q_OBJECT
public:
    AddEntryWidget(QWidget *parent = 0);
    ~AddEntryWidget();

signals:

public slots:
    void save();
    void load(QString index);
    void loadSessions();
    void loadTulpas();

private:

    QComboBox *comboBoxSelectSession;
    //QComboBox *comboBoxDate[3];
    QVBoxLayout *mainLayout;

    QComboBox *comboBoxName;
    QComboBox *comboBoxAction;
    QLineEdit *lineEditTimeSpent;

    QTextEdit *textEditDescription;

    QPushButton *pushButtonSave;

    int fileIDBuffer;
    bool loaded_from_file;
};

#endif // ADDENTRYWIDGET_H
