#include "IntSet.h"

IntSet::IntSet(int *_values, int _count) {
    count = 0;
    values = nullptr;
    for (int i = 0; i < _count; i++) {
        if(!this->contains(_values[i])) {
            values = (int *)realloc(values, ++count * sizeof(int));
            values[count - 1] = _values[i];
        }
    }
    sort(values, values + count);
}
IntSet::IntSet(const IntSet &_set) : count(_set.count) {
    values = new int[count];
    copy(_set.values, _set.values + count, values);
}
IntSet::~IntSet() {
    delete[] values;
}
int IntSet::getCount() const {
    return count;
}
bool IntSet::contains(int &element) const {
    return find(values, values + count, element) != values + count;
}
void IntSet::clear() {
    delete[] values;
    values = nullptr;
    count = 0;
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
IntSet &IntSet::operator=(const IntSet &_set) {
    if (this != &_set) {
        this->clear();
        count = _set.count;
        values = new int[count];
        copy(_set.values, _set.values + count, values);
    }
    return *this;
}
IntSet IntSet::operator-(const IntSet &_set) {
    IntSet result;

    for (int i = 0; i < this->count; i++) {
        if (!_set.contains(this->values[i])) {
            result.values = (int *)realloc(result.values, ++result.count * sizeof(int));
            result.values[result.count - 1] = _set.values[i];
        }
    }

    for (int i = 0; i < _set.count; i++) {
        if (!this->contains(_set.values[i])) {
            result.values = (int *)realloc(result.values, ++result.count * sizeof(int));
            result.values[result.count - 1] = _set.values[i];
        }
    }

    sort(result.values, result.values + result.count);

    return result;
}

IntSet IntSet::operator+(const IntSet &_set) {
    IntSet result = *this;

    for (int i = 0; i < _set.count; i++) {
        if (!result.contains(_set.values[i])) {
            result.values = (int *)realloc(result.values, ++result.count * sizeof(int));
            result.values[result.count - 1] = _set.values[i];
        }
    }

    sort(result.values, result.values + result.count);

    return result;
}
int &IntSet::operator[](int index) {
    if (index >= count || index < 0) {
        throw out_of_range("index out of bounds!");
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
    _set.clear();

    int n;
    cout << "number of unique elements: ";
    is >> n;

    for (int i = 0; i < n; ++i) {
        int temp;
        cout << "element: ";
        is >> temp;

        if (!_set.contains(temp)) {
            _set.values = (int *)realloc(_set.values, ++_set.count * sizeof(int));
            _set.values[_set.count - 1] = temp;
            cout << temp << " added!\n";
        } else {
            cout << "duplicate element!, skipping\n";
        }
    }

    return is;
}