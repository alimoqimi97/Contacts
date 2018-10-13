#include "editwindow.h"

EditWindow::EditWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->mainwidget = new QWidget;
    this->mainlayout = new QGridLayout;


    this->CreateHorizontalLayout();
    this->CreateCheckBoxes();
    this->CreateFormLayouts();
    this->CreateButtons();
    this->CreateLabels();
    this->CreateEditLines();
    this->CreateCompletedEditMessage();

    this->mainwidget->setLayout(mainlayout);
    this->setCentralWidget(mainwidget);
}

void EditWindow::CreateCompletedEditMessage()
{
    this->CompletedEditMessage = new QMessageBox(this);

    this->CompletedEditMessage->setText("Successfull Edition");
    this->CompletedEditMessage->setInformativeText("The Contact Edited successfully");
    this->CompletedEditMessage->setStandardButtons(QMessageBox ::Ok);
    this->CompletedEditMessage->setDefaultButton(QMessageBox ::Ok);
    this->CompletedEditMessage->setIcon(QMessageBox ::Information);
}

void EditWindow::ShowCompletedEditMessage()
{
    this->CompletedEditMessage->show();
}

void EditWindow::CreateCheckBoxes()
{
    this->EditContact = new QCheckBox("EditContact",this);
    this->EditGroupName = new QCheckBox("EditGroupName",this);
    this->SetCheckBoxesInlayout();
    this->ConnectCheckBoxes();
}

void EditWindow::SetCheckBoxesInlayout()
{
    this->CheckBoxeslayout->addWidget(EditContact);
    this->CheckBoxeslayout->addWidget(EditGroupName);
}

void EditWindow::ConnectCheckBoxes()
{
    this->connect(EditContact,SIGNAL(stateChanged(int)),this,SLOT(CheckForEdit()));
}

void EditWindow::CreateHorizontalLayout()
{
    this->CheckBoxeslayout = new QHBoxLayout;
    this->ButtonsLayout = new QHBoxLayout;

    this->mainlayout->addLayout(CheckBoxeslayout,1,0,1,1);
    this->mainlayout->addLayout(ButtonsLayout,2,0,1,1);
}

void EditWindow::CreateFormLayouts()
{
    this->CurrentInfoForm = new QFormLayout;
    this->NewInfoForm = new QFormLayout;
    this->SetFormLayoutsInMainLayout();
}

void EditWindow::SetFormLayoutsInMainLayout()
{
    this->mainlayout->addLayout(CurrentInfoForm,0,0,1,1);
    this->mainlayout->addLayout(NewInfoForm,0,1,1,1);
}

void EditWindow::CreateButtons()
{
    this->Edit = new QPushButton("Edit",this);
    this->Back = new QPushButton("Back",this);
    this->SetButtonsInLayout();
    this->ConnectButtons();
}

void EditWindow::SetButtonsInLayout()
{
    this->ButtonsLayout->addWidget(Edit,1);
    this->ButtonsLayout->addWidget(Back,1);
}

void EditWindow::ConnectButtons()
{
    this->connect(Back,SIGNAL(pressed()),this,SLOT(close()));
}

void EditWindow::CreateLabels()
{
    this->CurrentFirstName = new QLabel("CurrentFirstName:",this);
    this->CurrentLastName = new QLabel("CurrentLastName:",this);
    this->CurrentPhoneNum = new QLabel("CurrentPhoneNumber:",this);
    this->CurrentGroupName = new QLabel("CurrentGroupName:",this);
    this->NewFirstname = new QLabel("NewFirstName:",this);
    this->NewLastName = new QLabel("NewLastName:",this);
    this->NewPhoneNum = new QLabel("NewPhoneNum:",this);
    this->NewGroupName = new QLabel("NewGroupName:",this);

}

void EditWindow::CreateEditLines()
{
    this->CurrentFirstNameLine = new QLineEdit(this);
    this->CurrentLastNameLine = new QLineEdit(this);
    this->CurrentPhoneNumLine = new QLineEdit(this);
    this->CurrentGroupNameLine = new QLineEdit(this);
    this->NewFirstNameLine = new QLineEdit(this);
    this->NewLastNameLine = new QLineEdit(this);
    this->NewPhoneNumLine = new QLineEdit(this);
    this->NewGroupNameLine = new QLineEdit(this);

    this->SetLinesAndLabelsInLayout();
}

void EditWindow::SetLinesAndLabelsInLayout()
{
    this->CurrentInfoForm->addRow(CurrentFirstName,CurrentFirstNameLine);
    this->CurrentInfoForm->addRow(CurrentLastName,CurrentLastNameLine);
    this->CurrentInfoForm->addRow(CurrentPhoneNum,CurrentPhoneNumLine);
    this->CurrentInfoForm->addRow(CurrentGroupName,CurrentGroupNameLine);

    this->NewInfoForm->addRow(NewFirstname,NewFirstNameLine);
    this->NewInfoForm->addRow(NewLastName,NewLastNameLine);
    this->NewInfoForm->addRow(NewPhoneNum,NewPhoneNumLine);
    this->NewInfoForm->addRow(NewGroupName,NewGroupNameLine);
}

bool EditWindow::EditContactInBook(Contact &curC, Contact &NewC, QList<Contact> &ac)
{
    if(!ac.contains(curC))
    {
        return false;
    }

    ac.removeOne(curC);
    ac.push_back(NewC);
    return true;
}

bool EditWindow::EditContactInGroups(Contact &curC, Contact &NewC, QMap<QString, QList<Contact> > &gl, QString gn)
{
    if(!gl[gn].contains(curC))
    {
        return false;
    }

    if(gl[gn].removeOne(curC))
    {
        gl[gn].push_back(NewC);
        return true;
    }

    return false;
}

bool EditWindow::LoadAllContactsFromFile(QList<Contact> &ac)
{
    QFile  file("AllContacts.txt");
    QTextStream  Readfile(&file);
    QString  temp;
    QStringList  tmplist;

    file.open(QIODevice ::ReadOnly);

    while(true)
    {
        Contact  c;

        temp = Readfile.readLine();

        if(temp.isEmpty())
        {
            return false;
        }

        tmplist = temp.split(',');

        c.setFirstName(tmplist.at(0));
        c.setLastName(tmplist.at(1));
        c.setPhoneNumber(tmplist.at(2));

        ac.push_back(c);
    }

    file.close();

    return true;
}

bool EditWindow::SaveAllContactsInFile(QList<Contact> &ac)
{
    ofstream  writefile("AllContacts.txt", ios :: out);
    QList<Contact> ::iterator  litr;

    if(!writefile)
    {
        return false;
    }
    if(ac.empty())
    {
        return false;
    }

    for(litr = ac.begin() ; litr != ac.end() ; litr++)
    {
        writefile << *litr;
    }

    return true;
}

QStringList EditWindow::getAllGroupsName()
{
    QFile  gfile("Groups.txt");
    QTextStream   Readfile(&gfile);
    QStringList   groupsnames;
    QString  temp;

    gfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        temp = Readfile.readLine();
        if(temp.isNull())
        {
            break;
        }
        if(temp.contains(':'))
        {
            if(!groupsnames.contains(temp))
            {
                groupsnames.push_back(temp);
            }
        }

    }
    gfile.close();

    return  groupsnames;
}

bool EditWindow::LoadGroupsFromFile(QMap<QString, QList<Contact> > &gl)
{
    QFile  file("Groups.txt");
    QTextStream  Read(&file);
    QStringList  groupsname = this->getAllGroupsName();
    QStringList  ContactInfo;
    QString   key;
    Contact   c;


    if(groupsname.empty())
    {
        return false;
    }

    for(int i = 0 ; i < groupsname.size() ; i++)
    {
        QString  temp;
        QList<Contact>  l;

        key = groupsname.at(i);

        file.open(QIODevice ::ReadOnly);

        while(true)
        {
            temp = Read.readLine();

            if(temp.isEmpty())
            {
                break;
            }

            if(temp == key)
            {
                while(true)
                {
                    temp = Read.readLine();

                    if(temp == "------------------------------")
                    {
                        break;
                    }

                    ContactInfo = temp.split(',');
                    c.setFirstName(ContactInfo.at(0));
                    c.setLastName(ContactInfo.at(1));
                    c.setPhoneNumber(ContactInfo.at(2));
                    l.push_back(c);
                }
                //                    GroupsList[key] = l;
                gl[key] = l;
            }
        }
        file.close();
    }
    return true;
}

bool EditWindow::SaveGroupsInFile(QMap<QString,QList<Contact>> &gl)
{
    ofstream  writefile("Groups.txt", ios :: out);
    QMap<QString,QList<Contact>> ::iterator  mitr;

    if(gl.empty())
    {
        return false;
    }

    for(mitr = gl.begin() ; mitr != gl.end() ; mitr++)
    {
        QList<Contact> ::iterator  litr;

        for(litr = mitr.value().begin() ; litr != mitr.value().end() ; litr++)
        {
            writefile << mitr.key().toStdString() << endl;
            writefile << *litr ;
            writefile << "------------------------------" << endl;
        }
    }
    writefile.close();

    return true;
}

QString EditWindow::GetContactGroupName(Contact &target)
{
    QFile  gfile("Groups.txt");
    QTextStream  Readfile(&gfile);
    QString  temp = target.getFirstname() + ',' + target.getLastName() + ',' + target.getPhoneNumber();
    QString  rtmp,groupname;

    gfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        rtmp = Readfile.readLine();

        if(rtmp.isEmpty())
        {
            break;
        }

        if(rtmp.contains(':'))
        {
            groupname = rtmp;
            continue;
        }

        if(rtmp == temp)
        {
            break;
        }
    }

    gfile.close();

    return groupname;
}

void EditWindow::EditContactFromBook(Contact &curc, Contact &newc)
{
    QList<Contact>  allcontacts;

    this->LoadAllContactsFromFile(allcontacts);
    this->EditContactInBook(curc,newc,allcontacts);
    this->SaveAllContactsInFile(allcontacts);
}

void EditWindow::EditContactFromGroup(Contact &curc, Contact &newc, QString groupname)
{
    QMap<QString,QList<Contact>>  groupslist;

    if(groupname.isEmpty())
    {
        return;
    }

    this->LoadGroupsFromFile(groupslist);
    this->EditContactInGroups(curc,newc,groupslist,groupname);
    this->SaveGroupsInFile(groupslist);
}

void EditWindow::EdittingMission()
{
    Contact  CurrentContact,NewContact;
    QString  GN ;

    GN.append(':');

    CurrentContact.setFirstName(this->CurrentFirstNameLine->text());
    CurrentContact.setLastName(this->CurrentLastNameLine->text());
    CurrentContact.setPhoneNumber(this->CurrentPhoneNumLine->text());

    GN = this->GetContactGroupName(CurrentContact);

    NewContact.setFirstName(this->NewFirstNameLine->text());
    NewContact.setLastName(this->NewLastNameLine->text());
    NewContact.setPhoneNumber(this->NewPhoneNumLine->text());

    this->EditContactFromBook(CurrentContact,NewContact);
    this->EditContactFromGroup(CurrentContact,NewContact,GN);
    this->ShowCompletedEditMessage();
}

void EditWindow::CheckForEdit()
{
    if(this->EditContact->isChecked())
    {
        this->connect(Edit,SIGNAL(pressed()),this,SLOT(EdittingMission()));
    }
}
