#ifndef ADDORREMOVE_H
#define ADDORREMOVE_H

#include "contact.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QWidget>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <iostream>
using namespace std;

class AddOrRemove : public QMainWindow
{
    Q_OBJECT
public:
    explicit AddOrRemove(QWidget *parent = 0);

    //          Layouts         //
    QWidget * arwidget;
    QGridLayout * argrid;
    QFormLayout * arform;
    //          --------        //

    QMessageBox  *  warning;
    QMessageBox  *  SuccessMessage;


    //          Buttons         //
    QPushButton * CLOSE;
    QPushButton * ADDButton;
    QPushButton * REMOVEButton;
    //          -------         //


    //          labels          //
    QLabel * firstnamelabel;
    QLabel * lastnamelabel;
    QLabel * phonenumberlabel;
    QLabel * groupnamelabel;
    //          -------         //

    //          LineEdits       //
    QLineEdit * firstnameLine;
    QLineEdit * lastnameLine;
    QLineEdit * PhoneNumberLine;
    QLineEdit * GroupNameLine;
    //          ----------      //

    //          public functions        //
    void  CreateLineEdits();

    void  CreateLabels();

    //              QMessageBox methods     //
    void  CreateWarning();
    void  ShowWarning();

    void  CreateSuccessMessage();
    void  SetDataForRemovetMessage();
    void  SetDataForAddMessage();
    void  RepeatitiveContactMessage();
    //              ------------------      //

    void  InsertInfoReceiversTools();

    bool  SearchContact(Contact & c);

    void  CreateARButtons();
    void  ConnectButtons();
    void  InsertButtonsInLayout();

    void  InsertLayouts();

    bool  LoadContactFromFile(QList<Contact> &clist);
    bool  SaveContactsInFile(QList<Contact> &clist);

    void  SaveContactWithGroupsInFile(QString  groupname);

    QStringList  getAllGroupsName();

    void  FillGroupsInFile(QMap<QString,QList<Contact>> & GroupsList);
    void  LoadGroupsFromFile(QMap<QString,QList<Contact>> & GroupsList);

    bool  RemoveContactFromBook(Contact & c);

    bool  RemoveContactFromGroup(Contact & c, QString groupname) ;

    QString  getContactGroupname(Contact & target);
    //                  -------------------------------                     //

signals:

public slots:

    bool  AddContactToBook();
    void  DeleteContact();

};

#endif // ADDORREMOVE_H
