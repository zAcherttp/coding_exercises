#include <iostream>
#include <set>
using namespace std;
class IntSet
{
private:
	int* values;
	int count;

public:
	IntSet(int* _values = nullptr, int _count = 0);
	~IntSet();

	int getCount() const;
	IntSet makeSet() const;
	friend istream& operator>>(istream& is, IntSet& _set);
	friend ostream& operator<<(ostream& os, const IntSet& _set);

	int& operator[](int index);
	IntSet operator+(const IntSet& _set);
	IntSet operator-(const IntSet& _set);
	bool operator==(const IntSet& _set);
};

