#include <vector>
#include <iostream>
#include "NhanVienSX.h"
#include "NhanVienVP.h"

using namespace std;

int main()
{
    int m; //n;
    vector<NhanVienSX> DSNhanVienSX;
    vector<NhanVienVP> DSNhanVienVP;
    cout << "nhap so nhan vien sx: ";
    cin >> m;
    for (int i{}; i < m; i++)
    {
        int base_salary = 0;
        int product_num = 0;
        NhanVienSX temp;
        cin >> temp;
        cout << "nhap luong co ban: ";
        cin >> base_salary;
        cout << "nhap so san pham: ";
        cin >> product_num;
        temp.setBaseSalary(base_salary);
        temp.setProductNum(product_num);
        DSNhanVienSX.push_back(temp);
    }

    for (int i{}; i < m; i++)
    {
        cout << DSNhanVienSX[i];
    }
}