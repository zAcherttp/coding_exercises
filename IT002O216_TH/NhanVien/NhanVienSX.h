#pragma once
#include "NhanVien.h"
class NhanVienSX :
    public NhanVien
{
public:
    int base_salary;
    int product_num;
    NhanVienSX(int _bs = 0, int _p = 0);
    void setSalary();
    void setBaseSalary(int _bs);
    void setProductNum(int _p);
};

