#include "addorremove.h"

AddOrRemove::AddOrRemove(QWidget *parent) :
    QMainWindow(parent)
{
    this->InsertLayouts();
    this->InsertInfoReceiversTools();
    this->CreateARButtons();

    this->CreateWarning();
    this->CreateSuccessMessage();
}

void AddOrRemove::CreateLineEdits()
{
    this->firstnameLine = new QLineEdit(this);
    this->lastnameLine = new QLineEdit(this);
    this->PhoneNumberLine = new QLineEdit(this);
    this->GroupNameLine = new QLineEdit(this);
}

void AddOrRemove::CreateLabels()
{
    this->firstnamelabel = new QLabel("FirstName:",this);
    this->lastnamelabel = new QLabel("LastName:",this);
    this->phonenumberlabel = new QLabel("PhoneNumber:",this);
    this->groupnamelabel = new QLabel("GroupName(optional):",this);
}

void AddOrRemove::CreateWarning()
{
    this->warning = new QMessageBox;

    warning->setText("Please add your contact in book first.");
    this->warning->setIcon(QMessageBox ::Information);
    warning->setInformativeText("Your Cotact doesn't exists in TelephoneBook");
    warning->addButton(QMessageBox ::Close);
    warning->setStandardButtons(QMessageBox ::Ok );
    warning->setDefaultButton(QMessageBox ::Ok);
}

void AddOrRemove::ShowWarning()
{
    this->warning->show();
}

void AddOrRemove::CreateSuccessMessage()
{
    this->SuccessMessage = new QMessageBox(this);
}

void AddOrRemove::SetDataForRemovetMessage()
{
    this->SuccessMessage->setText("Removing Contact");
    this->SuccessMessage->setInformativeText("The contact removed successfully.!!");
    this->SuccessMessage->setStandardButtons(QMessageBox ::Ok);
    this->SuccessMessage->setIcon(QMessageBox ::Information);
    this->SuccessMessage->setDefaultButton(QMessageBox ::Ok);
    this->SuccessMessage->show();
}

void AddOrRemove::SetDataForAddMessage()
{
    this->SuccessMessage->setText("Good");
    this->SuccessMessage->setInformativeText("The Contact Added Successfully!");
    this->SuccessMessage->setIcon(QMessageBox ::Information);
    this->SuccessMessage->setStandardButtons(QMessageBox ::Ok);
    this->SuccessMessage->setDefaultButton(QMessageBox ::Ok);
    this->SuccessMessage->show();
}

void AddOrRemove::RepeatitiveContactMessage()
{
    this->SuccessMessage->setText("Repeatitive Contact");
    this->SuccessMessage->setInformativeText("Your Entered Contact already exists...");
    this->SuccessMessage->setIcon(QMessageBox ::Information);
    this->SuccessMessage->setStandardButtons(QMessageBox ::Ok);
    this->SuccessMessage->show();
}

void AddOrRemove::InsertInfoReceiversTools()
{
    this->CreateLineEdits();
    this->CreateLabels();

    this->arform->addRow(firstnamelabel,firstnameLine);
    this->arform->addRow(lastnamelabel,lastnameLine);
    this->arform->addRow(phonenumberlabel,PhoneNumberLine);
    this->arform->addRow(groupnamelabel,GroupNameLine);
}

bool AddOrRemove::SearchContact(Contact &c)
{
    QFile  file("AllContacts.txt");
    QString  temp,contactinfo;
    QTextStream  readfile(&file);
    //    Contact  c1;
    //    QStringList  cinfo;

    file.open(QIODevice ::ReadOnly);


    contactinfo = c.getFirstname() + ',' + c.getLastName() + ',' + c.getPhoneNumber();

    while(true)
    {
        temp = readfile.readLine();

        if(temp.isEmpty())
        {
            return false;
        }

        if(temp == contactinfo)
        {
            return true;
        }
    }



    //    while(true)
    //    {
    //        temp = readfile.readLine();

    //        if(temp.isEmpty())
    //        {
    //            break;
    //        }

    //        cinfo = temp.split(',');
    //        c1.setFirstName(cinfo.at(0));
    //        c1.setLastName(cinfo.at(1));
    //        c1.setPhoneNumber(cinfo.at(2));

    //        if(c1 == c)
    //        {
    //            return true;
    //        }
    //    }

    file.close();

    return false;
}

void AddOrRemove::CreateARButtons()
{
    this->CLOSE = new QPushButton("Close",this);
    this->ADDButton = new QPushButton("ADD",this);
    this->REMOVEButton = new QPushButton("Remove",this);

    this->InsertButtonsInLayout();
    this->ConnectButtons();

}

void AddOrRemove::ConnectButtons()
{
    this->connect(CLOSE,SIGNAL(pressed()),this,SLOT(close()));
    this->connect(ADDButton,SIGNAL(pressed()),this,SLOT(AddContactToBook()));
    this->connect(REMOVEButton,SIGNAL(pressed()),this,SLOT(DeleteContact()));
}

void AddOrRemove::InsertButtonsInLayout()
{
    this->argrid->addWidget(CLOSE,0,0,1,1);
    this->argrid->addWidget(ADDButton,2,0,1,1);
    this->argrid->addWidget(REMOVEButton,2,1,1,1);
}

void AddOrRemove::InsertLayouts()
{
    this->arwidget = new QWidget;
    this->argrid = new QGridLayout;
    this->arform = new QFormLayout;

    this->argrid->addLayout(arform,1,0,1,1);
    this->arwidget->setLayout(argrid);
    this->setCentralWidget(arwidget);
}

bool AddOrRemove::LoadContactFromFile(QList<Contact> &clist)
{
    QString temp;
    QStringList  tmplist;
    QFile   file("AllContacts.txt");
    QTextStream  Read(&file);
    Contact  c1;

    file.open(QIODevice ::ReadOnly);

    while(true)
    {
        temp = Read.readLine();

        if(temp.isEmpty())
        {
            return false;
        }
        tmplist = temp.split(',');
        c1.setFirstName(tmplist.at(0));
        c1.setLastName(tmplist.at(1));
        c1.setPhoneNumber(tmplist.at(2));
        clist.push_back(c1);
    }
    file.close();

    return true;
}

bool AddOrRemove::SaveContactsInFile(QList<Contact> &clist)
{
    ofstream  write("AllContacts.txt",ios :: out);
    QList<Contact> ::iterator  litr;

    if(!write)
    {
        return false;
    }
    if(clist.empty())
    {
        return false;
    }

    for(litr = clist.begin() ; litr != clist.end() ; litr++)
    {
        write << *litr;
    }

    return true;
}

void AddOrRemove::SaveContactWithGroupsInFile(QString groupname)
{
    ofstream  writefile("Groups.txt",ios :: out | ios :: app);
    Contact  cont1;

    groupname.append(':');

    writefile << groupname.toStdString() << endl;

    cont1.setFirstName(this->firstnameLine->text());
    cont1.setLastName(this->lastnameLine->text());
    cont1.setPhoneNumber(this->PhoneNumberLine->text());

    writefile << cont1 ;

    writefile << "------------------------------" << endl;

    writefile.close();
}

QStringList AddOrRemove::getAllGroupsName()
{
    QFile  file("Groups.txt");
    QTextStream  Read(&file);
    QStringList  groupname;
    QString   temp;

    file.open(QIODevice ::ReadOnly);

    while(true)
    {
        temp = Read.readLine();

        if(temp.isNull())
        {
            break;
        }
        if(temp.contains(':'))
        {
            if(!groupname.contains(temp))
            {
                groupname.push_back(temp);
            }
        }
    }

    file.close();

    return  groupname;

}

void AddOrRemove::FillGroupsInFile(QMap<QString, QList<Contact> > &GroupsList)
{
    ofstream  writefile("Groups.txt",ios :: out);
    QMap<QString,QList<Contact>> ::iterator  mitr;

    for(mitr = GroupsList.begin() ; mitr != GroupsList.end() ; mitr++)
    {
        QList<Contact> ::iterator  clistItr;

        for(clistItr = mitr.value().begin() ; clistItr != mitr.value().end() ; clistItr++)
        {
            writefile << mitr.key().toStdString() << endl;
            writefile << *clistItr ;
            writefile << "------------------------------" << endl;
        }
    }

    writefile.close();
}

void AddOrRemove::LoadGroupsFromFile(QMap<QString, QList<Contact> > &GroupsList)
{
    QFile  file("Groups.txt");
    QTextStream  Read(&file);
    QStringList  groupsname = this->getAllGroupsName();
    QStringList  ContactInfo;
    QString   key;
    Contact   c;


    if(groupsname.empty())
    {
        return ;
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
                GroupsList[key] = l;
            }
        }
        file.close();
    }
}

bool AddOrRemove::RemoveContactFromBook(Contact &c)
{
    QList<Contact>  RemoveList;

    this->LoadContactFromFile(RemoveList);

    if(!RemoveList.contains(c))
    {
        return false;
    }

    RemoveList.removeOne(c);

    if(this->SaveContactsInFile(RemoveList))
    {
        return true;
    }

    return false;
}

bool AddOrRemove::RemoveContactFromGroup(Contact &c, QString groupname)
{
    QMap<QString,QList<Contact>>  GroupsList;

    this->LoadGroupsFromFile(GroupsList);

    if(GroupsList.isEmpty())
    {
        return false;
    }

    if(!GroupsList.contains(groupname))
    {
        return false;
    }

    GroupsList[groupname].removeOne(c);

    this->FillGroupsInFile(GroupsList);

    return  true;
}

QString AddOrRemove::getContactGroupname(Contact &target)
{
    QFile  gfile("Groups.txt");
    QTextStream  read(&gfile);
    QString  temp = target.getFirstname() + ',' + target.getLastName() + ',' + target.getPhoneNumber();
    QString  rtmp,groupname;

    gfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        rtmp = read.readLine();

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

    return  groupname;
}

bool AddOrRemove::AddContactToBook()
{
    ofstream  write("AllContacts.txt", ios :: out | ios :: app);
    Contact  c;
    bool  searchcontact;

    if(!write)
    {
        return false;
    }

    c.setFirstName(this->firstnameLine->text());
    c.setLastName(this->lastnameLine->text());
    c.setPhoneNumber(this->PhoneNumberLine->text());

    searchcontact = this->SearchContact(c);

    if(this->GroupNameLine->text().isEmpty())
    {
        //          If contact exists in book ; it isn't saved in book again    //
        if(searchcontact)
        {
            this->RepeatitiveContactMessage();
            return false;
        }
        write << c;
    }
    else
    {
        //          If contact doesn't exists in book ; it is not save in groups    //
        if(!searchcontact)
        {
            this->ShowWarning();
            return false;
        }
        this->SaveContactWithGroupsInFile(this->GroupNameLine->text());
    }

    this->SetDataForAddMessage();

    write.close();
    return true;
}

void AddOrRemove::DeleteContact()
{
    Contact  Target;
    QString  gn;

    Target.setFirstName(this->firstnameLine->text());
    Target.setLastName(this->lastnameLine->text());
    Target.setPhoneNumber(this->PhoneNumberLine->text());

    gn = this->getContactGroupname(Target);

    if(this->GroupNameLine->text().isEmpty())
    {
        if(this->RemoveContactFromBook(Target))
        {
            this->SetDataForRemovetMessage();
        }
        this->RemoveContactFromGroup(Target,gn);
        return;
    }

    //          Debugging           //
//    if(empty.isEmpty())
//    {
//        this->RemoveContactFromBook(Target);
//        this->RemoveContactFromGroup(Target,gn);
//        return;
//    }
    //          ---------           //

    this->RemoveContactFromGroup(Target,this->GroupNameLine->text());
}
