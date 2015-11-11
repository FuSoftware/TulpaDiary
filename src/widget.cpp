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

}

Widget::~Widget()
{

}

void Widget::reload()
{
    addEntryWidget->loadTulpas();
    tulpaWidget->reload();
}
