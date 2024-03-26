#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

////// de bai.

struct NhanVien
{
    char MaNhanVien[8];
    char HoTen[20];
    char PhongBan[10];
    int LuongCoBan;
    int Thuong;
    int getThucLanh()
    {
        return LuongCoBan + Thuong;
    }
};

////// a.

int tongThucLanh(vector<NhanVien> A)
{
    int n = A.size();
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += A[i].getThucLanh();
    }
    return sum;
}

////// b.

////// c.

int soMucThuongCao(vector<NhanVien> A)
{
    int count = 0;
    int n = A.size();
    for (int i = 0; i < n; i++)
    {
        if (A[i].Thuong > 1200000)
        {
            count++;
        }
    }
    return count;
}

////// d.

bool compareNhanVien(NhanVien &a, NhanVien &b)
{
    if (strcmp(a.PhongBan, b.PhongBan) != 0)
    {
        return strcmp(a.PhongBan, b.PhongBan) < 0; // PhongBan tang dan
    }
    else
    {
        return strcmp(b.MaNhanVien, a.MaNhanVien) > 0; // MaNhanVien giam dan
    }
}

void inDanhSachLuong(vector<NhanVien> A)
{
    sort(A.begin(), A.end(), compareNhanVien);
    for (auto &nv : A)
    {
        std::cout << "Ma NV: " << nv.MaNhanVien << ", Ho Ten: " << nv.HoTen
                  << ", Phong Ban: " << nv.PhongBan << ", Luong Co Ban: " << nv.LuongCoBan
                  << ", Thuong: " << nv.Thuong << ", Thuc Lanh: " << nv.getThucLanh() << std::endl;
    }
}

int main()
{
    vector<NhanVien> nv = {
        {"NV00001", "Nguyen Van A", "Marketing", 10000000, 500000},
        {"NV00002", "Tran Thi B", "IT", 8000000, 300000},
        {"NV00003", "Le Van C", "Sales", 9000000, 700000},
        {"NV00004", "Ho Thi D", "Accountin", 7500000, 250000},
        {"NV00005", "Nguyen Thi E", "HR", 8500000, 400000},
        {"NV00006", "Tran Van F", "Marketing", 11000000, 1000000},
        {"NV00007", "Le Thi G", "IT", 9500000, 800000},
        {"NV00008", "Ho Van H", "Sales", 10500000, 1200000},
        {"NV00009", "Nguyen Thi I", "Accountin", 8000000, 450000},
        {"NV00010", "Tran Van J", "HR", 9000000, 600000},
    };

    // cout << tongThucLanh(nv);
    // cout << soMucThuongCao(nv);
    // inDanhSachLuong(nv);

    return 0;
}