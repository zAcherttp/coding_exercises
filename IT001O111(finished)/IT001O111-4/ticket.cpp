#include <iostream>
#include <string>
#include <cmath>

using namespace std;
// hàm kiểm tra 1 chữ số hay 2 chữ số sau đó trả về 10/100
int check(int n)
{
    if (n >= 10)
    {
        return 100;
    }
    else
    {
        return 10;
    }
}

int main()
{
    int t, p, x[4], y[4];
    cin >> p;
    // xếp input vào array 4 chỗ theo lề phải
    int digit;
    for (int i = 0; i < 4; i++)
    {
        digit = p % 10;
        x[i] = digit;
        p /= 10;
    }
    // tính lại giá trị x gán vào xx để đỡ loop tính
    int xx = x[3] * 1000 + x[2] * 100 + x[1] * 10 + x[0];

    int i = 1000;
    while (i <= 10000)
    {
        // gán i chạy vào array 4 chỗ theo lề phải
        int temp = i;
        int seperator;
        for (int k = 0; k < 4; k++)
        {
            seperator = temp % 10;
            y[k] = seperator;
            temp /= 10;
        }
        // so sánh tổng cặp số đầu với sau rồi tính giá trị của ticket
        if ((y[3] + y[2]) > (y[1] + y[0]))
        {
            t = (y[3] + y[2]) * check(y[1] + y[0]) + y[1] + y[0];
        }
        else
        {
            t = (y[1] + y[0]) * check(y[3] + y[2]) + y[3] + y[2];
        }
        if (t == xx)
        {
            break;
        }
        i++;
    }
    // xuất giá trị cần nhập nếu có,nếu không xuất 0
    t = i;
    if (t >= 10000)
    {
        cout << 0;
    }
    else
    {
        cout << i;
    }
    return 0;
}
