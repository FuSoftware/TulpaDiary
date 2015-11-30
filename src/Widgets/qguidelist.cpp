#include "qguidelist.h"

QGuideList::QGuideList(QWidget *parent) : QWidget(parent)
{
    this->parent = parent;

    file_path = std::string(DATA_FOLDER) + std::string("guidelist.json");
    int res = 0;

    if(!fexists(file_path.c_str()))
    {
         res = downloadFile(URL_GUIDELIST,file_path.c_str(),true);
    }

    if(res == 0)
    {
        this->root = loadJSONFile(file_path.c_str());
        loadUI();
    }
    else
    {
        QMessageBox::critical(this,"Error",QString("Couldn't load the guidelist : QNetwork error ") + QString::number(res));
        this->close();
    }
}

void QGuideList::loadUI()
{
    mainlayout = new QVBoxLayout;
    guideType = new QComboBox(this);
    QString title;

    /*Load category*/
    for(unsigned int i=0;i<G_END_LIST;i++)
    {
        /*Guide category*/
        title = guide_types[i].toLower();
        title[0] = title[0].toUpper();

        guideType->addItem(title);
    }

    widget = new QWidget(this);
    mainlayout->addWidget(guideType);
    mainlayout->addWidget(widget);

    connect(guideType,SIGNAL(currentIndexChanged(int)),this,SLOT(generateGuideList(int)));
    generateGuideList(0);

    this->setLayout(mainlayout);
}

void QGuideList::generateGuideList(int index)
{
    mainlayout->removeWidget(widget);
    delete widget;
    widget = new QWidget(this);

    QVBoxLayout *groupBoxLayout;
    QLabel *label;
    QString text;
    groupBoxLayout = new QVBoxLayout;

    int category_size = root[index].size();

    for(int j=0;j<category_size;j++)
    {
        text = QString("<a href=\"") +  QString(root[index][j]["url"].asCString()) + QString("\">") + QString(QString(root[index][j]["name"].asCString())) + QString("</a>");
        label = new QLabel(text,this);
        label->setTextFormat(Qt::RichText);
        label->setTextInteractionFlags(Qt::TextBrowserInteraction);
        label->setOpenExternalLinks(true);
        groupBoxLayout->addWidget(label);
    }

    widget->setLayout(groupBoxLayout);
    mainlayout->addWidget(widget);
    parent->resize(0,0);

}

