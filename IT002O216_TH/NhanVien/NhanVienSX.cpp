#include <NhanVien.h>

class NhanVienSX : public NhanVien
{
public:
    int base_salary;
    int product_num;
    NhanVienSX(int _bs, int _p) : base_salary(_bs), product_num(_p)
    {
        setSalary();
    }
    void setSalary()
    {
        salary = base_salary + product_num * 5000;
    }
    void setBaseSalary(int _bs)
    {
        base_salary = _bs;
        setSalary();
    }
    void setProductNum(int _p)
    {
        product_num = _p;
        setSalary();
    }
};