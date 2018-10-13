#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include "contact.h"
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

class EditWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent = 0);

    QWidget * mainwidget;
    QGridLayout * mainlayout;
    QFormLayout * CurrentInfoForm, * NewInfoForm;
    QCheckBox  * EditContact, * EditGroupName;
    QHBoxLayout *CheckBoxeslayout, *ButtonsLayout;
    QPushButton *Edit, *Back;

    QLabel  * CurrentFirstName , * CurrentLastName ,
            * CurrentPhoneNum , * CurrentGroupName ,
            * NewFirstname , * NewLastName ,
            * NewPhoneNum  , * NewGroupName ;

    QLineEdit  * CurrentFirstNameLine , * CurrentLastNameLine ,
               * CurrentPhoneNumLine  , * CurrentGroupNameLine ,
               * NewFirstNameLine , * NewLastNameLine ,
               * NewPhoneNumLine  , * NewGroupNameLine ;

    QMessageBox * CompletedEditMessage;

    void  CreateCompletedEditMessage();
    void  ShowCompletedEditMessage();

    void  CreateCheckBoxes();
    void  SetCheckBoxesInlayout();
    void  ConnectCheckBoxes();

    void  CreateHorizontalLayout();

    void  CreateFormLayouts();
    void  SetFormLayoutsInMainLayout();

    void  CreateButtons();

    void  SetButtonsInLayout();
    void  ConnectButtons();

    void  CreateLabels();
    void  CreateEditLines();
    void  SetLinesAndLabelsInLayout();

    bool  EditContactInBook(Contact & curC,Contact & NewC,QList<Contact> & ac);
    bool  EditContactInGroups(Contact & curC,Contact & NewC,QMap<QString,QList<Contact>> & gl,QString gn);

    bool  LoadAllContactsFromFile(QList<Contact> & ac);
    bool  SaveAllContactsInFile(QList<Contact>  & ac);

    QStringList  getAllGroupsName();

    bool  LoadGroupsFromFile(QMap<QString,QList<Contact>>  &  gl);
    bool  SaveGroupsInFile(QMap<QString,QList<Contact>> & gl);

    QString  GetContactGroupName(Contact & target);

    void  EditContactFromBook(Contact & curc,Contact & newc);
    void  EditContactFromGroup(Contact & curc,Contact & newc,QString  groupname);

signals:

public slots:

    void  EdittingMission();
    void  CheckForEdit();
};

#endif // EDITWINDOW_H
