#include <iostream>
#include <math.h>
using namespace std;

struct DiemSo {
    double Toan, Van, Ly, Hoa;
    double DTB;
};

struct Student {
    int MaHocSinh;
    string HoTen;
    DiemSo DiemSo;
};

void NhapThongTinHocSinh(Student &A) {
    cout << "Nhap Ma Hoc Sinh: ";
    cin >> A.MaHocSinh;

    cout << "Nhap Ho Ten: ";
    cin.ignore();
    getline(cin, A.HoTen);

    cout << "Nhap diem Toan: ";
    cin >> A.DiemSo.Toan;
    cout << "Nhap diem Van: ";
    cin >> A.DiemSo.Van;
    cout << "Nhap diem Ly: ";
    cin >> A.DiemSo.Ly;
    cout << "Nhap diem Hoa: ";
    cin >> A.DiemSo.Hoa;
    A.DiemSo.DTB = round((A.DiemSo.Toan + A.DiemSo.Van + A.DiemSo.Ly + A.DiemSo.Hoa) / 4 * 100) / 100;
}
void XuatThongTinHocSinh(Student &A) {
    cout << "Ma Hoc Sinh: " << A.MaHocSinh << endl;
    cout << "Ho Ten: " << A.HoTen << endl;
    cout << "Diem Trung Binh: " << A.DiemSo.DTB << endl;
}

int main() {

    Student A;
    NhapThongTinHocSinh(A);
    XuatThongTinHocSinh(A);
    return 0;
}