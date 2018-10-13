#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <QString>
#include <QTextStream>
#include <QList>
#include <QMap>
#include <QFile>
#include <QStringList>
#include <fstream>
using namespace std;


class Contact
{
private:
    QString  FirstName;
    QString  LastName;
    QString  PhoneNumber;


public:
    Contact();
    Contact(QString fn,QString ln,QString pn);

    void setFirstName(QString  firstname);
    QString  getFirstname() const;

    void setLastName(QString lastname);
    QString  getLastName() const;

    void  setPhoneNumber(QString phonenum);
    QString  getPhoneNumber() const;

    void PrintContact();
    void  ReceiveContact();

    bool operator < (Contact & other);
    bool operator == (const Contact & other) const;

};

ostream & operator << (ostream & out , Contact & c1);
ofstream & operator << (ofstream & fout , Contact & c);

QTextStream & operator >> (QTextStream & qin,Contact & c);


#endif // CONTACT_H
