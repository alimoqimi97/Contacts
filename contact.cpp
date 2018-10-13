#include "contact.h"

Contact::Contact()
{
}

Contact ::Contact(QString fn,QString ln,QString pn)
{
    this->FirstName = fn;
    this->LastName = ln;
    this->PhoneNumber = pn;
}

void Contact::setFirstName(QString firstname)
{
    this->FirstName = firstname;
}

QString Contact::getFirstname() const
{
    return  this->FirstName;
}

void Contact::setLastName(QString lastname)
{
    this->LastName = lastname;
}

QString Contact::getLastName() const
{
    return this->LastName;
}

void Contact::setPhoneNumber(QString phonenum)
{
    this->PhoneNumber = phonenum;
}

QString Contact::getPhoneNumber() const
{
    return this->PhoneNumber;
}

void Contact::PrintContact()
{
    cout << this->FirstName.toStdString() << endl;
    cout << this->LastName.toStdString() << endl;
    cout << this->PhoneNumber.toStdString() << endl;
}

void Contact::ReceiveContact()
{
    QString  info;
    QTextStream  qin(stdin);

    cout << "FirstName : ";
    qin >> info;
    this->FirstName = info;

    cout << "LastName : ";
    qin >> info;
    this->LastName = info;

    cout << "PhoneNumber : ";
    qin >> info;
    this->PhoneNumber = info;
}

bool Contact::operator <(Contact &other)
{
    if(this->LastName.toLower() < other.getLastName())
    {
        return true;
    }
    if(this->FirstName.toLower() < other.getFirstname())
    {
        return true;
    }
    if(this->PhoneNumber.toCaseFolded() < other.getPhoneNumber())
    {
        return true;
    }

    return false;
}

bool Contact::operator ==(const Contact &other) const
{
    if(this->FirstName == other.getFirstname())
    {
        if(this->LastName == other.getLastName())
        {
            if(this->PhoneNumber == other.getPhoneNumber())
            {
                return true;
            }
        }
    }

    return false;
}


ostream & operator <<(ostream & out, Contact &c1)
{
    out << c1.getFirstname().toStdString() << ' ';
    out << c1.getLastName().toStdString() << ' ';
    out << c1.getPhoneNumber().toStdString() << endl;

    return out;
}


ofstream & operator <<(ofstream & fout, Contact & c)
{
    fout << c.getFirstname().toStdString() << ',';
    fout << c.getLastName().toStdString() << ',';
    fout << c.getPhoneNumber().toStdString() << endl ;

    return fout;
}




QTextStream &operator >>(QTextStream &qin, Contact &c)
{
    QString  cinfo;

    cout << "FirstName : ";
    qin >> cinfo;
    c.setFirstName(cinfo);

    cout << "LastName : ";
    qin >> cinfo;
    c.setLastName(cinfo);

    cout << "PhoneNumber : ";
    qin >> cinfo;
    c.setPhoneNumber(cinfo);

    return  qin;
}
