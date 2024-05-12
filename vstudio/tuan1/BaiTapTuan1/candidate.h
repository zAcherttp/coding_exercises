#pragma once
#include <string>
struct date {
    int day;
    int month;
    int year;
};
struct score {
    float Toan;
    float Van;
    float Anh;
};
class candidate {
private:
    int Ma;
    std::string HoTen;
    date NgaySinh;
    score Diem;

public:
    candidate();
    ~candidate();

    void Nhap();
    void const Xuat();

    int const getMaHocSinh();

    float const getScoreSum();

    float const getMathScore();
    float const getMathScore();
    float const getMathScore();

    void const printName();
    void const printBirthDate();
};
