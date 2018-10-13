#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->mainwidget = new QWidget;
    this->mainlayout = new QGridLayout;

    this->mainwidget->setLayout(mainlayout);
    this->setCentralWidget(mainwidget);

    //          Table view          //
    this->mytable = new QTableWidget();
    //          ----------          //



    this->createButton();
    this->CreateCheckBoxes();

    this->CreateLineEdit();

    this->mainlayout->addWidget(this->mytable,2,2,1,1);
}


void MainWindow::InsertContactsInTable(QList<Contact> & mycontacts)
{
    int i = 0;

    //      setting up the table in the mainwindow      //
    this->mytable->setRowCount(mycontacts.size());
    this->mytable->setColumnCount(3);

    this->mytable->setHorizontalHeaderItem(0,new QTableWidgetItem("FirstName"));
    this->mytable->setHorizontalHeaderItem(1,new QTableWidgetItem("LastName"));
    this->mytable->setHorizontalHeaderItem(2,new QTableWidgetItem("PhoneNumber"));
    //      -------------------------------------      //

    this->mytable->setEditTriggers(QAbstractItemView ::NoEditTriggers);

    for(Contact c : mycontacts)
    {
        mytable->setItem(i,0,new QTableWidgetItem(c.getFirstname()));
        mytable->setItem(i,1,new QTableWidgetItem(c.getLastName()));
        mytable->setItem(i,2,new QTableWidgetItem(c.getPhoneNumber()));
        i++;
    }

    mytable->resizeRowsToContents();
    mytable->resizeColumnsToContents();
}


void MainWindow::CreateCheckBoxes()
{
    this->SeeAllGroups = new QCheckBox("SeeAllGroups",this);
    this->SeeAllContacts = new QCheckBox("See All Contacts",this);
    this->SeeAllMembersOfGroup = new QCheckBox("SeeAllMembersOfGroup",this);

    this->mainlayout->addWidget(SeeAllContacts,1,0,1,1);
    this->mainlayout->addWidget(SeeAllGroups,2,0,1,1);
    this->mainlayout->addWidget(SeeAllMembersOfGroup,3,0,1,1);
    this->ConnectCheckBoxes();

}

void MainWindow::ConnectCheckBoxes()
{
    this->connect(SeeAllContacts,SIGNAL(stateChanged(int)),this,SLOT(CheckForSee()));
    this->connect(SeeAllGroups,SIGNAL(stateChanged(int)),this,SLOT(CheckForSee()));
    this->connect(SeeAllMembersOfGroup,SIGNAL(stateChanged(int)),this,SLOT(CheckForSee()));

}

void MainWindow::OpenAddRemoveWindow()
{
    this->arw = new AddOrRemove(this);

    this->setWindowTitle("Add + Remove Window");
    arw->resize(500,250);
    arw->show();
}

void MainWindow::OpenSearchWindow()
{
    this->search_window = new SearchWindow(this);

    this->search_window->setWindowTitle("SearchWindow");
    this->search_window->resize(500,400);
    this->search_window->show();
}

void MainWindow::OpenEditWindow()
{
    this->editwindow = new EditWindow(this);

    editwindow->setWindowTitle("EditWindow");
    editwindow->resize(500,250);
    editwindow->show();
}

void MainWindow::ShowAllContacts()
{
    QList<Contact>  clist;

    this->arw->LoadContactFromFile(clist);
    this->InsertContactsInTable(clist);
}

void MainWindow::ShowAllMembersOfGroup()
{
    QString  gn = this->SearchLine->text();
    QList<Contact>  sgc;

    this->GetAllMembersOfAGroup(gn,sgc);
    this->InsertContactsInTable(sgc);
}

void MainWindow::InsertGroupsInTable()
{
    this->mytable->setColumnCount(4);
    this->mytable->setRowCount(this->getNumberOfCategorizedMembers());

    this->mytable->setHorizontalHeaderItem(0,new QTableWidgetItem("GroupName"));
    this->mytable->setHorizontalHeaderItem(1,new QTableWidgetItem("FirstName"));
    this->mytable->setHorizontalHeaderItem(2,new QTableWidgetItem("LastName"));
    this->mytable->setHorizontalHeaderItem(3,new QTableWidgetItem("PhoneNumber"));

    this->DownloadANDSetGroupsInTable();

    this->mytable->resizeRowsToContents();
    this->mytable->resizeColumnsToContents();
}

void MainWindow::CheckForSee()
{
    if(this->SeeAllContacts->isChecked())
    {
        this->connect(See,SIGNAL(pressed()),this,SLOT(ShowAllContacts()));
    }
    else if(this->SeeAllGroups->isChecked())
    {
        this->connect(See,SIGNAL(pressed()),this,SLOT(InsertGroupsInTable()));
    }
    else if(this->SeeAllMembersOfGroup->isChecked())
    {
        this->connect(See,SIGNAL(pressed()),this,SLOT(ShowAllMembersOfGroup()));
    }
}

void MainWindow::createButton()
{
    this->Quit = new QPushButton("Quit",this);
    this->FullScrean = new QPushButton("FullScreen",this);
    this->NormalScreen = new QPushButton("NormalScreen",this);
    this->addorremove = new QPushButton("Add Or Remove",this);
    this->Edit = new QPushButton("Edit",this);
    this->Search = new QPushButton("Search Contact",this);
    this->See = new QPushButton("See",this);

    this->SetButtonsInLayout();
    this->ConnectButtons();
}

void MainWindow::ConnectButtons()
{
    this->connect(Quit,SIGNAL(pressed()),this,SLOT(close()));
    this->connect(FullScrean,SIGNAL(clicked()),this,SLOT(showFullScreen()));
    this->connect(NormalScreen,SIGNAL(clicked()),this,SLOT(showNormal()));
    this->connect(addorremove,SIGNAL(clicked()),this,SLOT(OpenAddRemoveWindow()));
    this->connect(this->Search,SIGNAL(pressed()),this,SLOT(OpenSearchWindow()));
    this->connect(Edit,SIGNAL(pressed()),this,SLOT(OpenEditWindow()));
}

void MainWindow::SetButtonsInLayout()
{
    this->mainlayout->addWidget(Quit,0,0,1,1);
    this->mainlayout->addWidget(FullScrean,0,1,1,1);
    this->mainlayout->addWidget(NormalScreen,0,2,1,1);
    this->mainlayout->addWidget(Edit,5,1,1,1);
    this->mainlayout->addWidget(addorremove,5,0,1,1);
    this->mainlayout->addWidget(Search,5,2,1,1);
    this->mainlayout->addWidget(See,4,0,1,1);
}

void MainWindow::CreateLineEdit()
{
    this->SearchLine = new QLineEdit(this);
    this->mainlayout->addWidget(SearchLine,1,2,1,1);

}

void MainWindow::GetAllMembersOfAGroup(QString groupname, QList<Contact> &SGC)
{
    QFile  gfile("Groups.txt");
    QTextStream  download(&gfile);
    QString  tmp,fgn;
    Contact  tmpcnt;
    QStringList  cInfo;

    gfile.open(QIODevice ::ReadOnly);

    groupname.append(':');

    while(true)
    {
        tmp = download.readLine();

        if(tmp.isEmpty())
        {
            return;
        }

//        if(tmp.contains(':'))
//        {
//            fgn = tmp;
//        }

        if(tmp == groupname)
        {
            tmp = download.readLine();
            cInfo = tmp.split(',');
            tmpcnt.setFirstName(cInfo[0]);
            tmpcnt.setLastName(cInfo[1]);
            tmpcnt.setPhoneNumber(cInfo[2]);
            SGC.push_back(tmpcnt);
        }
    }

    gfile.close();
}

//QStringList MainWindow::getAllGroupsName()
//{
//    QFile  file("Groups.txt");
//    QTextStream  Read(&file);
//    QStringList  groupname;
//    QString   temp;

//    file.open(QIODevice ::ReadOnly);

//    while(!temp.isEmpty())
//    {
//        temp = Read.readLine();

//        if(temp.isNull())
//        {
//            break;
//        }
//        if(temp.contains(':'))
//        {
//            groupname.push_back(temp);
//        }
//    }
//    file.close();
//    return  groupname;
//}

void MainWindow::SetAMemberGroupInMyTable(QString gn, QStringList &ci, int i)
{
    this->mytable->setItem(i,0,new QTableWidgetItem(gn));
    this->mytable->setItem(i,1,new QTableWidgetItem(ci.at(0)));
    this->mytable->setItem(i,2,new QTableWidgetItem(ci[1]));
    this->mytable->setItem(i,3,new QTableWidgetItem(ci[2]));
}

void MainWindow::DownloadANDSetGroupsInTable()
{
    QString  groupname,temp;
    QFile  groupsfile("Groups.txt");
    QTextStream  Readfile(&groupsfile);
    QStringList  contactinfo;
    int i = 0;

    groupsfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        temp = Readfile.readLine();

        if(temp.isEmpty())
        {
            return;
        }

        if(temp.contains(':'))
        {
            groupname = temp;
            continue;
        }

        if(temp == "------------------------------")
        {
            continue;
        }

        contactinfo = temp.split(',');
        this->SetAMemberGroupInMyTable(groupname,contactinfo,i);
        i++;

    }
    groupsfile.close();
}

int MainWindow::getNumberOfCategorizedMembers()
{
    QFile  gfile("Groups.txt");
    QTextStream  Readfile(&gfile);
    QString  tmp;
    int  number = 0;

    gfile.open(QIODevice ::ReadOnly);

    while(true)
    {
        tmp = Readfile.readLine();

        if(tmp.isEmpty())
        {
            break;
        }
        if(tmp.contains(':'))
        {
            continue;
        }
        if(tmp == "------------------------------")
        {
            continue;
        }

        ++number;
    }

    gfile.close();

    return number;
}


//void MainWindow::CheckForSeeAllMembers()
//{
//    if(this->SeeAllContacts->isChecked())
//    {
//        this->connect(this->See,SIGNAL(pressed()),this,SLOT(ShowAllContacts()));
//    }
//    else
//    {
//        this->connect(this->See,SIGNAL(pressed()),mytable,SLOT(clear()));
//    }
//}

//void MainWindow::CheckForSeeAllGroups()
//{
//    if(this->SeeAllGroups->isChecked())
//    {
//        this->connect(See,SIGNAL(pressed()),this,SLOT(InsertGroupsInTable()));
//    }
//    else
//    {
//        this->connect(See,SIGNAL(pressed()),mytable,SLOT(clear()));
//    }
//}

MainWindow::~MainWindow()
{

}
