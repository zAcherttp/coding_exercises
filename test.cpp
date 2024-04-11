#include <iostream>
#include <algorithm>
using namespace std;
class IntSet
{
private:
	int *values;
	int count;

public:
	IntSet(int *values = nullptr, int count = 0) {}
	~IntSet() {}

	int* setPtr() {}
	int getCount() {}

	friend istream &operator>>(istream &is, IntSet &set);
	friend ostream &operator<<(ostream &os, const IntSet &set);

	int& operator[](int index);
	IntSet operator+(const IntSet &set);
	IntSet operator-(const IntSet &set);
	bool operator==(const IntSet &set);
};

IntSet::IntSet(int *_values = nullptr, int _count = 0)
{
	if(_values == nullptr)
		values = new int[_count];
	else
		count = _count;
}
IntSet::~IntSet()
{
	delete[] values;
}

int* IntSet::setPtr()
{
	return values;
}
int IntSet::getCount()
{
	return count;
}

istream &operator>>(istream &is, IntSet &set)
{
	int _count;
	is >> _count;
	set.values = new int(_count);
	set.count = _count;
	return is;
}
ostream &operator<<(ostream &os, const IntSet &set)
{
	for(int i = 0; i < set.count - 1; i++)
	{
		os << set.values[i] << " ";
	}
	os << set.values[set.count - 1];
	return os;
}

int& IntSet::operator[](int index)
{
	if(index >= count || index < 0)
		cout << "index out of bound";
		exit(0);
	return values[index];
}

IntSet IntSet::operator+(const IntSet &set)
{
	IntSet _union;
	IntSet _sorted1 = *this;
	IntSet _sorted2 = set;

	sort(_sorted1.values, _sorted1.values + _sorted1.count);
	sort(_sorted2.values, _sorted2.values + _sorted2.count);



	_union.count = this->count + set.count;

}
IntSet IntSet::operator-(const IntSet &set)
{

}
bool IntSet::operator==(const IntSet &set)
{

}

int main()
{
	int* list = new int[3];
	list[0] = 1;
	list[1] = 2;
	list[2] = 2;
	IntSet s1, s2(list, 3), s3;
	cin >> s1 >> s2;
	s3 = s1 + s2;
	s3 = s1 - s2;
	cout << s3;
	cout << s3[0];
	cout << (s1 == s2);
	return 0;
}