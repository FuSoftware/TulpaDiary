#ifndef TULPAWIDGET_H
#define TULPAWIDGET_H

#include <QWidget>
#include <QtWidgets>

#include <QDir>

#include <iostream>

#include "Objects/tulpa.h"

#include "addtulpawidget.h"

#include "qtulpastatistics.h"

enum TulpaInfo
{
    TULPA_BIRTH,
    TULPA_FIRST_WORD,
    TULPA_END_LIST
};

class TulpaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TulpaWidget(QWidget *parent = 0);
    ~TulpaWidget();

    void loadTulpas();
    void loadInfos();
    void loadPersonality();
    void loadSessions();

    void clearLayout(QLayout *layout);
signals:
    void tulpa_list_changed();
    void show_session(unsigned int id);

public slots:
    void loadTulpa(QString name);
    void addTulpa();
    void editTulpa();
    void reload();
    void showSession(QModelIndex index);

private:
    Tulpa *tulpa;

    QVBoxLayout *mainlayout;

    QComboBox *comboBoxTulpa;

    QGroupBox *groupBoxInfos;
    QLabel *labelsInfo[TULPA_END_LIST];

    QStringList personalityList;
    QListView *personalityView;
    QStringListModel *personalityModel;

    QStringList sessionsList;
    QListView *sessionsView;
    QStringListModel *sessionsModel;

    QList<QLabel*> labelsPersonality;
    QList<QLabel*> labelsSessions;

    QTulpaStatistics *stats;
};

#endif // TULPAWIDGET_H
