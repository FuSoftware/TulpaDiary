#ifndef QGUIDELIST_H
#define QGUIDELIST_H

#include <QtWidgets>

#include "../constantes.h"
#include "../ressources.h"
#include "../fonctions_json.h"
#include "../fonctions.h"

class QGuideList : public QWidget
{
    Q_OBJECT
public:
    QGuideList(QWidget *parent = 0);
    void loadUI();

signals:

public slots:
    void generateGuideList(int index);

private:
    QWidget *widget;
    QVBoxLayout *mainlayout;
    QComboBox *guideType;

    std::string file_path;
    Json::Value root;
};

#endif // QGUIDELIST_H
