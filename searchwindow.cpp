#include "searchwindow.h"

SearchWindow::SearchWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->mswidget = new QWidget;
    this->search_line1 = new QLineEdit(this);
    this->CreateLayout();
    this->CreateButtons();
    this->CreateCheckBox();
    this->CreateSearchTable();

    this->mslayout->addWidget(search_line1,1,1,1,1);

    this->setCentralWidget(mswidget);
}

void SearchWindow::CreateSearchTable()
{
    this->SearchTable = new QTableWidget(this);
    this->mslayout->addWidget(SearchTable,2,1,1,1);
}

void SearchWindow::CreateCheckBox()
{
    this->SearchByFirstName = new QCheckBox("Searh By FirstName",this);
    this->SearchByLastName = new QCheckBox("Search By LastName",this);
    this->SearchByPhoneNumber = new QCheckBox("Search By PhoneNumber",this);
    this->SearchAGroupByName = new QCheckBox("SearchAGroupByName",this);

    this->setCheckBoxesInLayout();
    this->ConnectCheckBoxes();
}

void SearchWindow::setCheckBoxesInLayout()
{
    this->mslayout->addWidget(SearchByFirstName,1,0,1,1);
    this->mslayout->addWidget(SearchByLastName,2,0,1,1);
    this->mslayout->addWidget(SearchByPhoneNumber,3,0,1,1);
    this->mslayout->addWidget(SearchAGroupByName,4,0,1,1);
}

void SearchWindow::CreateButtons()
{
    this->CloseButton = new QPushButton("Close",this);
    this->SetButtonsInlayout();
    this->ConnectButtons();
}

void SearchWindow::SetButtonsInlayout()
{
    this->mslayout->addWidget(CloseButton,0,0,1,1);
}

void SearchWindow::ConnectButtons()
{
    this->connect(CloseButton,SIGNAL(pressed()),this,SLOT(close()));
}

bool SearchWindow::ReadFromFile(QList<Contact> &AllContacts)
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

        AllContacts.push_back(c);
    }

    file.close();

    return true;
}

void SearchWindow::CreateLayout()
{
    this->mslayout = new QGridLayout;
    this->mswidget->setLayout(mslayout);
}

void SearchWindow::FindContactByStartOfFirstName(QList<Contact> &searchlist, QString myname)
{
    QList<Contact>  allcontacts;
    QList<Contact> ::iterator  litr;

    this->ReadFromFile(allcontacts);

    if(allcontacts.isEmpty())
    {
        return;
    }

    for(litr = allcontacts.begin() ; litr != allcontacts.end() ; litr++)
    {
        QString  fn = litr->getFirstname().toLower();

        if(fn.startsWith(myname.toLower()))
        {
            searchlist.push_back(*litr);
        }
    }

}

void SearchWindow::FindConactByStartOfLastName(QList<Contact> &sl, QString myname)
{
    QList<Contact>  allcontacts;
    QList<Contact> ::iterator  litr;

    this->ReadFromFile(allcontacts);

    if(allcontacts.isEmpty())
    {
        return;
    }

    for(litr = allcontacts.begin() ; litr != allcontacts.end() ; litr++)
    {
        QString ln = litr->getLastName().toLower();

        if(ln.startsWith(myname.toLower()))
        {
            sl.push_back(*litr);
        }

//        if(litr->getLastName().startsWith(myname))
//        {
//            sl.push_back(*litr);
//        }
    }
}

void SearchWindow::FindContactByStartOfPhoneNumber(QList<Contact> &sl, QString myNumber)
{
    QList<Contact>  allcontacts;
    QList<Contact> ::iterator  litr;

    this->ReadFromFile(allcontacts);

    if(allcontacts.isEmpty())
    {
        return;
    }

    for(litr = allcontacts.begin() ; litr != allcontacts.end() ; litr++)
    {
        if(litr->getPhoneNumber().startsWith(myNumber))
        {
            sl.push_back(*litr);
        }
    }
}

void SearchWindow::InsertInTable(QList<Contact> &mycontacts)
{
    QList<Contact> ::iterator  clitr;
    int i = 0;

    this->SearchTable->setRowCount(mycontacts.size());
    this->SearchTable->setColumnCount(3);


    this->SearchTable->setHorizontalHeaderItem(0,new QTableWidgetItem("FirstName"));
    this->SearchTable->setHorizontalHeaderItem(1,new QTableWidgetItem("LastName"));
    this->SearchTable->setHorizontalHeaderItem(2,new QTableWidgetItem("PhoneNumber"));

    for(clitr = mycontacts.begin() ; clitr != mycontacts.end() ; clitr++)
    {
        this->SearchTable->setItem(i,0,new QTableWidgetItem(clitr->getFirstname()));
        this->SearchTable->setItem(i,1,new QTableWidgetItem(clitr->getLastName()));
        this->SearchTable->setItem(i,2,new QTableWidgetItem(clitr->getPhoneNumber()));
        i++;
    }

    this->SearchTable->setEditTriggers(QAbstractItemView ::NoEditTriggers);
    this->SearchTable->resizeRowsToContents();
    this->SearchTable->resizeColumnsToContents();
}

QStringList SearchWindow::getAllGroupsName()
{
    QFile  file("Groups.txt");
    QTextStream  Read(&file);
    QStringList  groupname;
    QString   temp;

    file.open(QIODevice ::ReadOnly);
    temp = Read.readLine();
    while(!temp.isEmpty())
    {
        if(temp.isNull())
        {
            break;
        }
        if(temp.contains(':'))
        {
            temp.remove(':');
            groupname.push_back(temp);
        }
        temp = Read.readLine();
    }

    groupname.removeDuplicates();

    file.close();

    return  groupname;

}

void SearchWindow::InsertRalatedGroupsNameInTable(QList<QString> &RGN)
{
    QTableWidgetItem * Gn = new QTableWidgetItem("GroupName");

    if (this->SearchTable == nullptr)
        return;

    this->SearchTable->setRowCount(RGN.size());
    this->SearchTable->setColumnCount(1);

    this->SearchTable->setHorizontalHeaderItem(0,Gn);

    for(int i = 0 ; i < RGN.size() ; i++)
    {
        QTableWidgetItem * RGNi = new QTableWidgetItem(RGN.at(i));

        this->SearchTable->setItem(i,0,RGNi);
    }

    this->SearchTable->resizeRowsToContents();
    this->SearchTable->resizeColumnsToContents();
}

QList<QString> SearchWindow::FindRelatedGroupName()
{
    QList<QString>  cinfo;
    QString  groupname = this->search_line1->text();
    QStringList  GN = this->getAllGroupsName();

    for(int i = 0 ; i < GN.size() ; i++)
    {
        QString gn = GN.at(i).toLower();

        if(gn.startsWith(groupname.toLower()))
        {
            cinfo.push_back(GN.at(i));
        }
    }

    return  cinfo;
}

void SearchWindow::ConnectCheckBoxes()
{
    this->connect(search_line1,SIGNAL(textChanged(QString)),this,SLOT(RefreshList()));
}

void SearchWindow::RefreshList()
{
    QString  info = this->search_line1->text();
    QList<Contact>  SL;

    if(SearchByFirstName->isChecked())
    {
        this->FindContactByStartOfFirstName(SL,info);
    }
    else if(SearchByLastName->isChecked())
    {
        this->FindConactByStartOfLastName(SL,info);
    }
    else if(SearchByPhoneNumber->isChecked())
    {
        this->FindContactByStartOfPhoneNumber(SL,info);
    }
    else if (SearchAGroupByName->isChecked())
    {
        this->RefindList();
        return;
    }

    this->InsertInTable(SL);

}

void SearchWindow::RefindList()
{
    if(this->SearchAGroupByName->isChecked())
    {
        QList<QString>  relatedGroupsName = this->FindRelatedGroupName();
        this->InsertRalatedGroupsNameInTable(relatedGroupsName);
    }
}
