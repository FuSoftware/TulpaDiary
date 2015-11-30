#include "qtulpastatistics.h"

QTulpaStatistics::QTulpaStatistics(QWidget *parent) : QWidget(parent)
{
    loadUI();
}

QTulpaStatistics::QTulpaStatistics(Tulpa *tulpa, QWidget *parent) : QWidget(parent)
{
    loadUI();
    loadTulpa(tulpa);
}

void QTulpaStatistics::loadUI()
{
    QVBoxLayout *layout = new QVBoxLayout;

    view = new QTableView(this);
    model =  new QStandardItemModel(this);

    view->setModel(model);
    view->setWordWrap(true);
    layout->addWidget(view);

    setLayout(layout);
}

void QTulpaStatistics::loadTulpa(Tulpa* tulpa)
{
    int time[ACTION_END_LIST] = {0};

    int d,h,m;

    /*Clear counts*/
    for(unsigned int i=0;i<ACTION_END_LIST;i++)
    {
        sessions[i] = 0;
    }

    /*Load durations*/
    for(unsigned int i=0;i<tulpa->getSessions().size();i++)
    {
        time[tulpa->getSessions().at(i).getTypeId()] += tulpa->getSessions().at(i).getDuration();
        sessions[i]++ ;
    }

    /*Generate Strings*/
    for(unsigned int i=0;i<ACTION_END_LIST;i++)
    {
        strings[i].clear();
        /*Days*/
        if(time[i] > 1440)
        {
            d = time[i]/1440;
            time[i] %= 1440;
            strings[i] += QString::number(d);
            strings[i] += QString(" days ");
        }

        /*Hours*/
        if(time[i] > 60)
        {
            h = time[i]/60;
            time[i] %= 60;
            strings[i] += QString::number(h);
            strings[i] += QString(" hours ");
        }

        /*Minutes*/
        if(time[i] > 0)
        {
            m = time[i];
            strings[i] += QString::number(m);
            strings[i] += QString(" minutes ");
        }
    }

    setupModel();
}

void QTulpaStatistics::setupModel()
{
    QStringList labels;
    labels << "Type" << "Duration" << "Sessions";

    model->clear();

    model->setHorizontalHeaderLabels(labels);

    for(unsigned int i=0;i<ACTION_END_LIST;i++)
    {
         model->setItem(i,0,new QStandardItem(actions_string[i])); //Type
         model->setItem(i,1,new QStandardItem(strings[i])); //Duration
         model->setItem(i,2,new QStandardItem(QString::number(sessions[i]))); //Sessions
    }

    view->resizeColumnsToContents();
}
