#ifndef QTULPASTATISTICS_H
#define QTULPASTATISTICS_H

#include "../ressources.h"
#include "../Objects/tulpa.h"

#include <QtWidgets>

class QTulpaStatistics : public QWidget
{
    Q_OBJECT
public:
    QTulpaStatistics(QWidget *parent = 0);
    QTulpaStatistics(Tulpa *tulpa, QWidget *parent = 0);
    void loadUI();
    void loadTulpa(Tulpa* tulpa);
    void setupModel();

signals:

public slots:

private:
    QTableView *view;
    QStandardItemModel *model;

    QString strings[ACTION_END_LIST];
    int sessions[ACTION_END_LIST];
};

#endif // QTULPASTATISTICS_H
