#include "addtulpawidget.h"

AddTulpaWidget::AddTulpaWidget(QWidget *parent) : AddTulpaWidget("", parent)
{

}

AddTulpaWidget::AddTulpaWidget(QString name, QWidget *parent): QWidget(parent)
{
    this->path = path;
    loadUI();

    if(!name.isEmpty())
    {
        loadTulpa(name);
    }
}

void AddTulpaWidget::loadTulpa(QString name)
{
    tulpa.loadByName(name.toStdString());

    this->lineEdits.at(LINE_EDIT_NAME)->setText(QString(tulpa.getName().c_str()));
    this->lineEdits.at(LINE_EDIT_BIRTH)->setText(QString(intToDate(tulpa.getBirthTime()).c_str()));
    this->lineEdits.at(LINE_EDIT_FIRST_WORD)->setText(QString::number(tulpa.getFirstWordTime()));

    for(int i=0;i<tulpa.getPersonalityTraits().size();i++)
    {
        personalityTraits << QString(tulpa.getPersonalityTrait(i).c_str());
    }

    loadPersonality(personalityTraits);
}

void AddTulpaWidget::loadUI()
{
    mainLayout = new QVBoxLayout;

    /*Main data*/
    for(int i=0;i<LAYOUT_END_LIST;i++)
    {
        labels.push_back(new QLabel(label_names[i],this));
        lineEdits.push_back(new QLineEdit(this));
        layouts.push_back(new QHBoxLayout);

        layouts.at(i)->addWidget(labels.at(i));
        layouts.at(i)->addWidget(lineEdits.at(i));

        mainLayout->addLayout(layouts.at(i));
    }

    /*Personality*/
    QHBoxLayout *layoutBottom = new QHBoxLayout;
    QVBoxLayout *layoutBottomButtons = new QVBoxLayout;
    QPushButton *pBEditPersonality = new QPushButton("Add",this);
    QPushButton *pBCleanPersonality = new QPushButton("Clean",this);

    model = new QStringListModel(personalityTraits);
    view = new QListView;
    view->setModel(model);

    layoutBottomButtons->addWidget(pBEditPersonality);
    layoutBottomButtons->addWidget(pBCleanPersonality);

    layoutBottom->addWidget(view);
    layoutBottom->addLayout(layoutBottomButtons);
    mainLayout->addLayout(layoutBottom);

    /*Save*/
    QPushButton *pushButtonSave = new QPushButton("Save",this);
    mainLayout->addWidget(pushButtonSave);

    connect(pBEditPersonality,SIGNAL(clicked()),this,SLOT(setPersonality()));
    connect(pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(pBCleanPersonality,SIGNAL(clicked()),this,SLOT(refreshPersonality()));

    setLayout(mainLayout);
}

void AddTulpaWidget::save()
{
    Json::Value root;

    tulpa.setName(lineEdits.at(LINE_EDIT_NAME)->text().toStdString());
    tulpa.setBirthTime(lineEdits.at(LINE_EDIT_BIRTH)->text().toInt());
    tulpa.setFirstWordTime(lineEdits.at(LINE_EDIT_FIRST_WORD)->text().toInt());

    std::vector<std::string> personality;

    for(int i=0;i<personalityTraits.size();i++)
    {
        personality.push_back(personalityTraits.at(i).toStdString());
    }

    tulpa.setPersonalityTraits(personality);

    emit finished();
    this->close();
}


void AddTulpaWidget::refreshPersonality()
{
    QMessageBox msgBox(QMessageBox::Question,"Clean Personality", "Do you want to clean empty entries ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Cancel,"Clear All");

    int reponse = msgBox.exec();

    if (reponse == QMessageBox::Yes)
    {

        QStringList buffer = model->stringList();
        personalityTraits.clear();
        int size = buffer.size();

        for(int i=0;i<size;i++)
        {
            if(buffer.at(i).isEmpty())
            {

            }
            else
            {
                personalityTraits.push_back(buffer.at(i));
            }
        }

        model->setStringList(personalityTraits);
    }
    else if(reponse == QMessageBox::Cancel)
    {
        personalityTraits = model->stringList();
        personalityTraits.clear();
        model->setStringList(personalityTraits);
    }

}

void AddTulpaWidget::setPersonality()
{
    QString personality_s = QInputDialog::getText(this, "Personality", "Please input a new personality trait");
    personalityTraits.push_back(personality_s);
    model->setStringList(personalityTraits);
}

void AddTulpaWidget::loadPersonality(QStringList personality)
{
    model->setStringList(personality);
}

QStringList AddTulpaWidget::parsePersonality(QString string)
{
    QStringList output;
    QString buffer = "";
    QChar c;

    for(int i=0;i<string.size();i++)
    {
        c = string.at(i);
        if(c == QLatin1Char(','))
        {
            output.push_back(buffer);
            buffer.clear();
        }
        else
        {
            buffer.push_back(c);
        }
    }
    output.push_back(buffer);
    return output;
}
