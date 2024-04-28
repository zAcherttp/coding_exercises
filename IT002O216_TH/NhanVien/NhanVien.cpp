#include "NhanVien.h"
#include <string>
#include <climits>

int NhanVien::getSalary() const
{
    return this->salary;
}

istream& operator>>(istream& is, NhanVien& nv)
{
    cout << "nhap ho ten: ";
    is.ignore();
    getline(is, nv.name);
    cout << "nhap ngay thang nam sinh: ";
    //is.ignore();
    getline(is, nv.birth_date);
    cout << "nhap luong: ";
    is >> nv.salary;
    return is;
}

ostream& operator<<(ostream& os, NhanVien& nv)
{
    os << "ho ten: " << nv.name << '\n';
    os << "ngay sinh: " << nv.birth_date << '\n';
    os << "luong: " << nv.getSalary() << '\n';
    return os;
}