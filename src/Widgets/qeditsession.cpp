#include "qeditsession.h"

QEditSession::QEditSession(Session *session, bool load, QWidget *parent) : QWidget(parent)
{
    outputInfo(L_DEBUG,"Loading Session Editor");
    this->session = session;

    mainLayout = new QVBoxLayout;

    /*-----*/
    outputInfo(L_DEBUG,"Loading Tulpas");

    comboBoxName = new QComboBox(this);
    comboBoxAction = new QComboBox(this);

    loadTulpas();

    lineEditTimeSpent = new QLineEdit(this);
    textEditDescription = new QTextEdit(this);
    textEditWriting = new QTextEdit(this);
    pushButtonSave = new QPushButton("Save",this);
    pushButtonDate = new QPushButton("Edit date",this);


    for(int i=0;i<ACTION_END_LIST;i++)
    {
        comboBoxAction->addItem(actions_string[i]);
    }

    QGroupBox   *groupBox[OBJECT_NUMBER];
    QVBoxLayout *layout[OBJECT_NUMBER];

    for(int i=1; i<OBJECT_NUMBER;i++)
    {
        groupBox[i] = new QGroupBox(titles[i],this);
        layout[i] = new QVBoxLayout;
        groupBox[i]->setLayout(layout[i]);

        switch(i)
        {
        case 1:
            layout[i]->addWidget(comboBoxName);
            break;
        case 2:
            layout[i]->addWidget(comboBoxAction);
            break;
        case 3:
            layout[i]->addWidget(pushButtonDate);
            break;
        case 4:
            layout[i]->addWidget(lineEditTimeSpent);
            break;
        case 5:
            layout[i]->addWidget(textEditDescription);
            break;
        case 6:
            layout[i]->addWidget(textEditWriting);
            break;
        }

        mainLayout->addWidget(groupBox[i]);
    }
    mainLayout->addWidget(pushButtonSave);
    setLayout(mainLayout);

    connect(pushButtonSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(pushButtonDate,SIGNAL(clicked()),this,SLOT(changeDate()));

    calendar = new QCalendarWidget(0);
    connect(calendar,SIGNAL(activated(QDate)),this,SLOT(changeDateSelected(QDate)));

    if(load)
    {
        loadSession();
    }
}

void QEditSession::loadSession()
{
    comboBoxName->setCurrentText(session->getTulpaName().c_str());
    comboBoxAction->setCurrentIndex(session->getTypeId());
    lineEditTimeSpent->setText(QString::number(session->getDuration()));
    textEditDescription->setText(session->getDescription().c_str());
}

void QEditSession::loadTulpas()
{
    comboBoxName->clear();

    QDir tulpadir(TULPA_FOLDER);
    tulpadir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QString buffer;
    int entry_size = tulpadir.entryList().size();

    for(int i=0;i<entry_size;i++)
    {
        if(!tulpadir.entryInfoList().at(i).baseName().isEmpty())
        {
            buffer = tulpadir.entryInfoList().at(i).baseName();
            buffer[0] = buffer[0].toUpper();
            comboBoxName->addItem(buffer);

            outputInfo(L_DEBUG,"Loaded Tulpa " + buffer.toStdString());
        }
    }
    comboBoxName->addItem("No Tulpa");
}


void QEditSession::save()
{
    session->setTypeID(comboBoxAction->currentIndex());
    session->setTulpaName(comboBoxName->currentText().toStdString());
    session->setDuration(lineEditTimeSpent->text().toInt());
    session->setDescription(textEditDescription->toPlainText().toStdString());

    session->save();
    emit saved();
    emit finished();
    this->close();
}

void QEditSession::changeDate()
{
    QMessageBox::warning(this,"Warning","This feature is highly unstable since it will move the current file.\nYour session may duplicate between the old and new folder, but not always.");
    calendar->show();
}

void QEditSession::changeDateSelected(QDate date)
{
    calendar->close();

    session->setDate(date.toString(DATE_TYPE).toStdString());

    QString path = QString(QString(session->getFilePath().c_str()));
    QFile file(path);

    QString new_path = QString(SESSION_FOLDER) + date.toString(DATE_TYPE) + QString("/") + QString::number(session->getId()) + QString(".json");

    session->setFilePath(new_path.toStdString());
    session->save();
    file.rename(new_path);
}
