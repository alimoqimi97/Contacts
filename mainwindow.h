#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "addorremove.h"
#include "searchwindow.h"
#include "editwindow.h"
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QIcon>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

    QWidget * mainwidget;
    QGridLayout * mainlayout;

    QPushButton * Quit;
    QPushButton * FullScrean;
    QPushButton * NormalScreen;
    QPushButton * addorremove;
    QPushButton * Edit;
    QPushButton * Search;
    QPushButton * See;

    QCheckBox * SeeAllContacts;
    QCheckBox * SeeAllGroups;
    QCheckBox * SeeAllMembersOfGroup;

    QLineEdit * SearchLine;

    //          windows         //
    AddOrRemove * arw;
    SearchWindow * search_window;
    EditWindow  *  editwindow;
    //          -------         //

    QTableWidget * mytable;

    void  InsertContactsInTable(QList<Contact> &mycontacts);

    void  CreateCheckBoxes();
    void  ConnectCheckBoxes();

    void  createButton();
    void  ConnectButtons();
    void  SetButtonsInLayout();

    void  CreateLineEdit();

    void  GetAllMembersOfAGroup(QString groupname,QList<Contact> & SGC);

    QStringList  getAllGroupsName();

    void  SetAMemberGroupInMyTable(QString gn,QStringList & ci,int i);
    void  DownloadANDSetGroupsInTable();
    int   getNumberOfCategorizedMembers();

    ~MainWindow();

signals:

public slots:
    void  OpenAddRemoveWindow();
    void  OpenSearchWindow();
    void  OpenEditWindow();

    void  ShowAllContacts();
    void  ShowAllMembersOfGroup();

    void  InsertGroupsInTable();

    void  CheckForSee();

};

#endif // MAINWINDOW_H
