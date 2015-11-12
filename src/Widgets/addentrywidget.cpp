#include "addentrywidget.h"

AddEntryWidget::AddEntryWidget(QWidget *parent) : QWidget(parent)
{
    outputInfo(L_DEBUG,"Loading Sessions Widget");


    loaded_from_file = false;

    mainLayout = new QVBoxLayout;

    /*-----*/
    outputInfo(L_DEBUG,"Loading Sessions");

    comboBoxSelectSession = new QComboBox(this);

    loadSessions();

    /*-----*/
    outputInfo(L_DEBUG,"Loading Tulpas");

    comboBoxName = new QComboBox(this);
    comboBoxAction = new QComboBox(this);

    loadTulpas();

    lineEditTimeSpent = new QLineEdit(this);
    lineEditDate = new QLineEdit(this);
    textEditDescription = new QTextEdit(this);
    pushButtonSave = new QPushButton("Save",this);


    for(int i=0;i<ACTION_END_LIST;i++)
    {
        comboBoxAction->addItem(actions_string[i]);
    }

    QGroupBox   *groupBox[OBJECT_NUMBER];
    QVBoxLayout *layout[OBJECT_NUMBER];

    for(int i=0; i<OBJECT_NUMBER;i++)
    {
        groupBox[i] = new QGroupBox(titles[i],this);
        layout[i] = new QVBoxLayout;
        groupBox[i]->setLayout(layout[i]);

        switch(i)
        {
        case 0:
            layout[i]->addWidget(comboBoxSelectSession);
            break;
        case 1:
            layout[i]->addWidget(comboBoxName);
            break;
        case 2:
            layout[i]->addWidget(comboBoxAction);
            break;
        case 3:
            layout[i]->addWidget(lineEditDate);
            break;
        case 4:
            layout[i]->addWidget(lineEditTimeSpent);
            break;
        case 5:
            layout[i]->addWidget(textEditDescription);
            break;
        }

        mainLayout->addWidget(groupBox[i]);
    }
    mainLayout->addWidget(pushButtonSave);
    setLayout(mainLayout);

    connect(pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(comboBoxSelectSession,SIGNAL(currentIndexChanged(QString)),this,SLOT(load(QString)));

    load(comboBoxSelectSession->currentText());
}

AddEntryWidget::~AddEntryWidget()
{

}

void AddEntryWidget::load_session(int id)
{
    int index = comboBoxSelectSession->findText(QString::number(id));
    comboBoxSelectSession->setCurrentIndex(index);
}

void AddEntryWidget::loadSessions()
{
    QDir sessiondir(SESSION_FOLDER);
    QString buffer;
    sessiondir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    comboBoxSelectSession->clear();

    for(int i=0;i<sessiondir.entryInfoList().size();i++)
    {
        buffer = sessiondir.entryInfoList().at(i).baseName();
        comboBoxSelectSession->addItem(buffer);
    }

    comboBoxSelectSession->addItem("New Session");
}

void AddEntryWidget::loadTulpas()
{
    comboBoxName->clear();

    QDir tulpadir(TULPA_FOLDER);
    tulpadir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QString buffer;
    int entry_size = tulpadir.entryList().size();

    for(int i=0;i<entry_size;i++)
    {
        if (tulpadir.entryInfoList().at(i).baseName().isEmpty())
        {

        }
        else
        {
            buffer = tulpadir.entryInfoList().at(i).baseName();
            buffer[0] = buffer[0].toUpper();
            comboBoxName->addItem(buffer);

            outputInfo(L_DEBUG,"Loaded Tulpa " + buffer.toStdString());
        }

    }

    comboBoxName->addItem("No Tulpa");
}

void AddEntryWidget::save()
{
    QDir sessionDir(SESSION_FOLDER);
    sessionDir.setFilter(QDir::Files);
    std::string filePath;
    std::string fileIDBuffer;

    int index = comboBoxSelectSession->currentIndex();

    if(index < comboBoxSelectSession->count())
    {
        loaded_from_file = true;
    }
    else
    {
        loaded_from_file = false;
    }

    fileIDBuffer = intToString(index);

    Json::Value root;

    Session session(atoi(fileIDBuffer.c_str()),
                    comboBoxName->currentText().toStdString(),
                    comboBoxAction->currentText().toStdString(),
                    comboBoxAction->currentIndex(),
                    textEditDescription->toPlainText().toStdString(),
                    lineEditTimeSpent->text().toInt(),
                    lineEditDate->text().toStdString());

    /*Add entry to tulpa*/
    if(comboBoxName->currentIndex() < comboBoxName->count()-1)
    {
        int i=0;

        Tulpa tulpa(comboBoxName->currentText().toStdString());

        std::vector<int> v = tulpa.getSessionsIds();
        int id = atoi(fileIDBuffer.c_str());

        if(std::find(v.begin(), v.end(), id) != v.end())
        {
          //elem exists in the vector
        }
        else
        {
            tulpa.addSessions(session);
        }

        tulpa.save();
    }

    loadSessions();
    loadTulpas();

    comboBoxSelectSession->setCurrentIndex(index);
}

void AddEntryWidget::load(QString index)
{
    if(comboBoxSelectSession->currentIndex() < comboBoxSelectSession->count()-1)
    {
        std::string filePath = std::string(SESSION_FOLDER) + index.toStdString() + std::string(".json");
        Json::Value root = loadJSONFile(filePath.c_str());

        textEditDescription->setText(root["description"].asCString());
        lineEditTimeSpent->setText(QString::number(root["duration"].asInt()));
        fileIDBuffer = root["id"].asInt();
        comboBoxAction->setCurrentIndex(root["id_action"].asInt());
        comboBoxName->setCurrentText(root["tulpa_name"].asCString());
        lineEditDate->setText(QString(root["time"].asString().c_str()));
        loaded_from_file = true;
    }
    else
    {
        textEditDescription->setText("Enter a description");
        lineEditTimeSpent->setText("Enter the spent time");
        comboBoxAction->setCurrentText("Enter the session type");
        comboBoxName->setCurrentText("Choose your Tulpa");
        lineEditDate->setText("Enter the date");
        loaded_from_file = false;
    }
}

