#include <NhanVien.h>

int NhanVien::getSalary() const
{
    return this->salary;
}

istream &operator>>(istream &is, NhanVien &nv)
{
    cout << "nhap ho ten: ";
    getline(is, nv.name);
    is.ignore();
    cout << "nhap ngay thang nam sinh: ";
    getline(is, nv.birth_date);
    is.ignore();
    cout << "nhap luong: ";
    is >> nv.salary;
}

ostream &operator<<(ostream &os, NhanVien &nv)
{
    os << "ho ten: " << nv.name << '\n';
    os << "ngay sinh: " << nv.birth_date << '\n';
    os << "luong: " << nv.getSalary() << '\n';
}