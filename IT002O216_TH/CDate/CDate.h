////// CDate.h
#include <chrono>
#include <iostream>

using namespace std;

class CDate {
private:
    tm Date;

public:
    CDate(int _ngay, int _thang, int _nam);
    ~CDate();

    friend ostream &operator<<(ostream &os, const CDate &date);
    friend istream &operator>>(istream &is, CDate &date);

    CDate operator+(const int day);
    CDate operator-(const int day);
};

////// CDate.cpp
CDate::CDate(int _ngay = 1, int _thang = 1, int _nam = 1900) {
    Date.tm_sec = 0;
    Date.tm_min = 0;
    Date.tm_hour = 0;
    Date.tm_mday = _ngay;
    Date.tm_mon = _thang - 1;
    Date.tm_year = _nam - 1900;
}

CDate::~CDate() {}

ostream &operator<<(ostream &os, const CDate &_d) {
    os << _d.Date.tm_mday << '/' << _d.Date.tm_mon + 1 << '/' << _d.Date.tm_year + 1900;
    return os;
}

istream &operator>>(istream &is, CDate &_d) {
    int _ngay, _thang, _nam;
    is >> _ngay >> _thang >> _nam;
    _d.Date.tm_mday = _ngay;
    _d.Date.tm_mon = _thang - 1;
    _d.Date.tm_year = _nam - 1900;
    time_t epochTime = mktime(&_d.Date);
    _d.Date = *localtime(&epochTime);
    return is;
}

CDate CDate::operator+(const int day) {
    time_t epochTime = mktime(&this->Date);
    epochTime += 86400 * day;
    tm *localTime = localtime(&epochTime);
    return CDate(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

CDate CDate::operator-(const int day) {
    time_t epochTime = mktime(&this->Date);
    epochTime -= 86400 * day;
    tm *localTime = localtime(&epochTime);
    return CDate(localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

////// main.cpp
int main() {
    CDate test;
    cin >> test;
    cout << test << '\n';
    cout << test + 1 << '\n';
    cout << test + 2 << '\n';
    cout << test + 3 << '\n';
    return 0;
}