#include "NhanVienSX.h"

NhanVienSX::NhanVienSX(int _bs, int _p) : base_salary(_bs), product_num(_p)
{
    setSalary();
}
void NhanVienSX::setSalary()
{
    salary = base_salary + product_num * 5000;
}
void NhanVienSX::setBaseSalary(int _bs)
{
    base_salary = _bs;
    setSalary();
}
void NhanVienSX::setProductNum(int _p)
{
    product_num = _p;
    setSalary();
}
