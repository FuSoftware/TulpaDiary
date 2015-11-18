#ifndef QEDITSESSION_H
#define QEDITSESSION_H

#include <QtWidgets>

#include <iostream>
#include "constantes.h"

#include "json/json.h"
#include "fonctions.h"
#include "fonctions_json.h"
#include "../Objects/tulpa.h"

#include "../ressources.h"
#include "../Objects/session.h"

class QEditSession : public QWidget
{
    Q_OBJECT
public:
    QEditSession(Session *session, bool load = true, QWidget *parent = 0);
    void loadSession();
    void loadTulpas();

signals:

public slots:
    void save();
    void changeDate();
    void changeDateSelected(QDate date);

private:

    Session *session;

    //QComboBox *comboBoxDate[3];
    QVBoxLayout *mainLayout;

    QComboBox *comboBoxName;
    QComboBox *comboBoxAction;
    QPushButton *pushButtonDate;
    QLineEdit *lineEditTimeSpent;

    QTextEdit *textEditDescription;

    QPushButton *pushButtonSave;

    int fileIDBuffer;
    bool loaded_from_file;

    QCalendarWidget *calendar;
};


#endif // QEDITSESSION_H
