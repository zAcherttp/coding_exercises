#pragma once
#include <iostream>

using namespace std;

class NhanVien
{
public:
    string name;
    string birth_date;
    int salary;
public:
    NhanVien(string _n = "", string _bd = "", int _s = 0) : name(_n), birth_date(_bd), salary(_s) {} 
    int getSalary() const;
    void setSalary();
    friend istream &operator>>(istream &is, NhanVien &nv);
    friend ostream &operator<<(ostream &os, NhanVien &nv);
};