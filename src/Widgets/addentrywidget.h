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

#include "../ressources.h"

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
    void load_session(int id);

private:

    QComboBox *comboBoxSelectSession;
    //QComboBox *comboBoxDate[3];
    QVBoxLayout *mainLayout;

    QComboBox *comboBoxName;
    QComboBox *comboBoxAction;
    QLineEdit *lineEditDate;
    QLineEdit *lineEditTimeSpent;

    QTextEdit *textEditDescription;

    QPushButton *pushButtonSave;

    int fileIDBuffer;
    bool loaded_from_file;
};

#endif // ADDENTRYWIDGET_H
