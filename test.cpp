#include <iostream>

using namespace std;

class test
{
public:
    string s;

    test(string _default_arg = "Hello World!") : s(_default_arg) {}

    friend ostream &operator<<(ostream &os, const test &_test)
    {
        os << _test.s;
        return os;
    }
};

// int main()
// {
//     cout << "Hello World!\n";

//     test obj;

//     cout << obj;

//     return 0;
// }

int main(int argc, char* argv[])
{
    std::cout << "Have " << argc << " arguments:\n";
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << "\n";
    }
}