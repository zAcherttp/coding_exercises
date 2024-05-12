#include <iostream>
#include <set>
using namespace std;
class IntSet {
private:
    int *values;
    int count;

public:
    IntSet(int *_values, int _count);
    ~IntSet();

    int getCount() const;

    friend istream &operator>>(istream &is, IntSet &_set);
    friend ostream &operator<<(ostream &os, const IntSet &_set);

    int &operator[](const int index);
    IntSet operator+(const IntSet &_set);
    IntSet operator-(const IntSet &_set);
    bool operator==(const IntSet &_set);
};

IntSet::IntSet(int *_values = nullptr, int _count = 0) {
    if (_values == nullptr || _count == 0) {
        count = 0;
        values = nullptr;
    } else {
        set<int> uniques;
        for (int i = 0; i < _count; i++) {
            uniques.insert(_values[i]);
        }
        count = (int)uniques.size();
        values = new int[count];
        int i = 0;
        for (auto value : uniques) {
            values[i++] = value;
        }
    }
}
IntSet::~IntSet() {
    delete[] values;
}
int IntSet::getCount() const {
    return count;
}
bool IntSet::operator==(const IntSet &_set) {
    if (this->count == _set.count) {
        for (int i = 0; i < _set.count; i++) {
            if (this->values[i] == _set.values[i])
                continue;
            else
                return false;
        }
        return true;
    }
    return false;
}
IntSet IntSet::operator-(const IntSet &_set) {
    IntSet _subtract;
    set<int> __subtract;

    for (int i = 0; i < this->count; i++) {
        __subtract.insert(this->values[i]);
    }

    for (int i = 0; i < _set.count; i++) {
        if (__subtract.find(_set.values[i]) != __subtract.end())
            __subtract.erase(_set.values[i]);
        else
            __subtract.insert(_set.values[i]);
    }

    _subtract.count = (int)__subtract.size();
    _subtract.values = new int[_subtract.count];

    int i = 0;
    for (auto value : __subtract) {
        _subtract.values[i++] = value;
    }
    return _subtract;
}
IntSet IntSet::operator+(const IntSet &_set) {
    IntSet _union;
    set<int> __union;

    for (int i = 0; i < this->count; i++) {
        __union.insert(this->values[i]);
    }

    for (int i = 0; i < _set.count; i++) {
        __union.insert(_set.values[i]);
    }

    _union.count = (int)__union.size();
    _union.values = new int[_union.count];

    int i = 0;
    for (auto value : __union) {
        _union.values[i++] = value;
    }

    return _union;
}
int &IntSet::operator[](const int index) {
    if (index >= count || index < 0) {
        cout << "index out of bound!";
        exit(1);
    }
    return values[index];
}
ostream &operator<<(ostream &os, const IntSet &_set) {
    if (_set.count > 0) {
        for (int i = 0; i < _set.count; i++) {
            os << _set.values[i] << " ";
        }
    } else
        cout << "empty set!";
    return os;
}
istream &operator>>(istream &is, IntSet &_set) {
    set<int> set_;

    cout << "number of unique elements: ";
    int n, temp;
    is >> n;
    cout << "new elements: ";

    for (int i = 0; i < n; i++) {
        is >> temp;
        set_.insert(temp);
    }

    if (_set.values != nullptr) {
        delete[] _set.values;
    }
    _set.values = new int[(int)set_.size()];
    _set.count = (int)set_.size();

    int i = 0;
    for (auto value : set_) {
        _set.values[i++] = value;
    }

    return is;
}

int main() {
    int *values = new int[2];
    values[0] = 1;
    values[1] = 1;
    IntSet s1, s2(values, 2), s3;
    cin >> s2;
    s3 = s1 + s2;
    s3 = s1 - s2;
    cout << s2[0];
    cout << (s1 == s2);
    return 0;
}