#ifndef WIDGET_H
#define WIDGET_H

#include <fonctions.h>
#include <QtWidgets>

#include "Widgets/addentrywidget.h"
#include "Widgets/tulpawidget.h"
#include "Widgets/qguidelist.h"

enum Indexes{
    ID_SESSIONS = 0,
    ID_TULPAS,
    ID_GUIDES
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void reload();
    void load_session(int i);
    void refresh_tab(int i);

private:
    QVBoxLayout *mainLayout;

    QTabWidget *tabWidget;

    AddEntryWidget *addEntryWidget;
    QGuideList *guideList;

    TulpaWidget *tulpaWidget;

};

#endif // WIDGET_H
