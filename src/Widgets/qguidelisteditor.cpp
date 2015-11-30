#include "qguidelisteditor.h"

QGuideListEditor::QGuideListEditor(QWidget *parent) : QWidget(parent)
{
    file_path = std::string(DATA_FOLDER) + std::string("guidelist.json");

    comboBoxType = new QComboBox(this);
    for(unsigned int i=0;i<G_END_LIST;i++)
    {
        comboBoxType->addItem(guide_types[i].toLower());
    }

    lineEditName = new QLineEdit(this);
    lineEditUrl = new QLineEdit(this);

    lineEditName->setPlaceholderText("Guide Name");
    lineEditUrl->setPlaceholderText("URL");

    pushButtonAdd = new QPushButton("Add",this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(comboBoxType);
    layout->addWidget(lineEditName);
    layout->addWidget(lineEditUrl);
    layout->addWidget(pushButtonAdd);

    QVBoxLayout *mainlayout = new QVBoxLayout;

    mainlayout->addLayout(layout);

    this->setLayout(mainlayout);

    connect(pushButtonAdd,SIGNAL(clicked()),this,SLOT(add()));
}

void QGuideListEditor::add()
{
    unsigned int index = root[comboBoxType->currentIndex()].size();
    root[comboBoxType->currentIndex()][index]["url"] = lineEditUrl->text().toStdString();
    root[comboBoxType->currentIndex()][index]["name"] = lineEditName->text().toStdString();

    saveJSONFile(root,file_path.c_str());

    lineEditUrl->clear();
    lineEditName->clear();
}

