#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    outputInfo(L_VERBOSE,"Generating Widget");
    checkFolder(TULPA_FOLDER);
    checkFolder(SESSION_FOLDER);

    mainLayout = new QVBoxLayout;

    tabWidget = new QTabWidget(this);

    addEntryWidget = new AddEntryWidget(this);

    tulpaWidget = new TulpaWidget(this);

    tabWidget->addTab(addEntryWidget,"Add Session");
    tabWidget->addTab(tulpaWidget,"Tulpas");

    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

    connect(tulpaWidget,SIGNAL(tulpa_list_changed()),this,SLOT(reload()));
    connect(tulpaWidget,SIGNAL(show_session(int)),addEntryWidget,SLOT(load_session(int)));
    connect(tulpaWidget,SIGNAL(show_session(int)),this,SLOT(load_session(int)));

    connect(tabWidget,SIGNAL(currentChanged(int)),this,SLOT(refresh_tab(int)));

}

Widget::~Widget()
{

}

void Widget::reload()
{
    addEntryWidget->loadTulpas();
    tulpaWidget->reload();
}

void Widget::load_session(int i)
{
    this->tabWidget->setCurrentIndex(0);
}

void Widget::refresh_tab(int i)
{
    switch(i)
    {
    case 0:
        break;
    case ID_TULPAS:
        tulpaWidget->reload();
        break;
    }
}
