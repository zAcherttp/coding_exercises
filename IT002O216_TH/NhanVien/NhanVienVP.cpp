#include "NhanVienVP.h"

NhanVienVP::NhanVienVP(int _wd) : work_days(_wd)
{
    setSalary();
}
void NhanVienVP::setSalary()
{
    salary = work_days * 100000;
}
void NhanVienVP::setWorkDays(int _wd)
{
    work_days = _wd;
    setSalary();
}
