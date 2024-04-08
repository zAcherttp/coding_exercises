#include <iostream>
#include <vector>

using namespace std;

class Data
{
public:
    string key;
    int count;
bool operator<(const data &d)
{
    return count == d.count ? (key > d.key) : (count < d.count);
}
};

int main()
{
    int n;
    cin >> n;
    Data DS[n];
    


    return 0;
}