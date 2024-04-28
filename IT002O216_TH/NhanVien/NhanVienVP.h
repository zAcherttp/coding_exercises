#pragma once
#include "NhanVien.h"
class NhanVienVP :
    public NhanVien
{
public:
    int work_days;
    NhanVienVP(int _wd = 0);
    void setSalary();
    void setWorkDays(int _wd);
};

