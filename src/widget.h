#ifndef WIDGET_H
#define WIDGET_H

#include <fonctions.h>
#include <QtWidgets>

#include "Widgets/addentrywidget.h"
#include "Widgets/tulpawidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QVBoxLayout *mainLayout;

    QTabWidget *tabWidget;

    AddEntryWidget *addEntryWidget;
    AddTulpaWidget *addTulpaWidget;
    TulpaWidget *tulpaWidget;

};

#endif // WIDGET_H
