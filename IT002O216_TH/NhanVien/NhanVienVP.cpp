#include <NhanVien.h>

class NhanVienVP : public NhanVien
{
public:
    int work_days;
    NhanVienVP(int _wd) : work_days(_wd)
    {
        setSalary();
    }
    void setSalary()
    {
        salary = work_days * 100000;
    }
    void setWorkDays(int _wd)
    {
        work_days = _wd;
        setSalary();
    }
};