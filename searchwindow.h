#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include "contact.h"
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>

class SearchWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SearchWindow(QWidget *parent = 0);

    QGridLayout * mslayout;
    QWidget * mswidget;

    QPushButton * CloseButton;

    QLineEdit * search_line1;

    //          checkboxes          //
    QCheckBox * SearchByFirstName;
    QCheckBox * SearchByLastName;
    QCheckBox * SearchByPhoneNumber;
    QCheckBox * SearchAGroupByName;
    //          ----------          //

    QTableWidget * SearchTable;

    void  CreateSearchTable();

    void  CreateCheckBox();

    void  setCheckBoxesInLayout();

    void  CreateButtons();
    void  SetButtonsInlayout();
    void  ConnectButtons();

    bool  ReadFromFile(QList<Contact> & AllContacts);

    void  CreateLayout();

    void  FindContactByStartOfFirstName(QList<Contact> & searchlist,QString  myname);
    void  FindConactByStartOfLastName(QList<Contact> & sl,QString myname);
    void  FindContactByStartOfPhoneNumber(QList<Contact> & sl,QString myNumber);

    void  InsertInTable(QList<Contact> & mycontacts);

    QStringList  getAllGroupsName();

    QList<QString>  FindRelatedGroupName();
    void  ConnectCheckBoxes();
    void  InsertRalatedGroupsNameInTable(QList<QString> & RGN);

    void  RefindList();

signals:

public slots:

    void  RefreshList();
};

#endif // SEARCHWINDOW_H
