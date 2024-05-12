#include "candidate.h"
#include <iostream>
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
    candidate() {
        this->Ma = 0;
        this->HoTen = "";

        this->NgaySinh.day = 1;
        this->NgaySinh.month = 1;
        this->NgaySinh.year = 1;

        this->Diem.Toan = 0.0;
        this->Diem.Van = 0.0;
        this->Diem.Anh = 0.0;
    }

    ~candidate() {
        delete this;
    }

    void Nhap() {
        std::cout << "nhap ma hoc sinh: ";
        std::cin >> this->Ma;

        std::cout << "nhap ho ten: ";
        std::cin.ignore();
        getline(std::cin, this->HoTen);

        std::cout << "nhap ngay thang nam sinh (dd mm yyyy): ";
        std::cin >> this->NgaySinh.day >> this->NgaySinh.month >> this->NgaySinh.year;

        std::cout << "nhap diem Toan: ";
        std::cin >> this->Diem.Toan;
        std::cout << "nhap diem Van: ";
        std::cin >> this->Diem.Van;
        std::cout << "nhap diem Anh: ";
        std::cin >> this->Diem.Anh;
    }
    void const Xuat() {
        std::cout << this->Ma;
        std::cout << this->HoTen;
        std::cout << this->NgaySinh.day << "/" << this->NgaySinh.month << "/" << this->NgaySinh.year;
        std::cout << "diem Toan: ";
        std::cout << this->Diem.Toan;
        std::cout << ", diem Van: ";
        std::cout << this->Diem.Van;
        std::cout << ", diem Anh: ";
        std::cout << this->Diem.Anh;
    }

    int const getMaHocSinh() {
        return this->Ma;
    }

    float const getScoreSum() {
        return this->Diem.Toan + this->Diem.Van + this->Diem.Anh;
    }
    float const getMathScore() {
        return this->Diem.Toan;
    }
    float const getLiteratureScore() {
        return this->Diem.Van;
    }
    float const getEnglishScore() {
        return this->Diem.Anh;
    }

    void const printName() {
        std::cout << this->HoTen;
    }
    void const printBirthDate() {
        std::cout << this->NgaySinh.day << "/" << this->NgaySinh.month << "/" << this->NgaySinh.year;
    }
};