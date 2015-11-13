#ifndef QGUIDELISTEDITOR_H
#define QGUIDELISTEDITOR_H

#include <QtWidgets>

#include "../fonctions_json.h"
#include "../ressources.h"
#include "../constantes.h"

class QGuideListEditor : public QWidget
{
    Q_OBJECT
public:
    explicit QGuideListEditor(QWidget *parent = 0);

signals:

public slots:
    void add();

private:
    std::string file_path;
    Json::Value root;

    QComboBox *comboBoxType;
    QLineEdit *lineEditName;
    QLineEdit *lineEditUrl;

    QPushButton *pushButtonAdd;
};

#endif // QGUIDELISTEDITOR_H
