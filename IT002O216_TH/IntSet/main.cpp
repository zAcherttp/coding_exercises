#include <iostream>
#include <set>
using namespace std;
class IntSet
{
private:
	int *values;
	int count;

public:
	IntSet(int *_values = nullptr, int _count = 0);
	~IntSet();

	int getCount() const;

	friend istream &operator>>(istream &is, IntSet &_set);
	friend ostream &operator<<(ostream &os, const IntSet &_set);

	int &operator[](int index);
	IntSet operator+(const IntSet &_set);
	IntSet operator-(const IntSet &_set);
	bool operator==(const IntSet &_set);
};

IntSet::IntSet(int *_values, int _count)
{
	if (_values == nullptr)
		count = 0;
	else
	{
		set<int> uniques;
		for (int i = 0; i < _count; i++)
		{
			uniques.insert(_values[i]);
		}
		count = (int)uniques.size();
		values = new int[count];
		int i = 0;
		for (auto value : uniques)
		{
			values[i++] = value;
		}
	}
}
IntSet::~IntSet()
{
	delete[] values;
}
int IntSet::getCount() const
{
	return count;
}
bool IntSet::operator==(const IntSet &_set)
{
	if (this->count == _set.count)
	{
		for (int i = 0; i < _set.count; i++)
		{
			if (this->values[i] == _set.values[i])
				continue;
			else
				return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}
IntSet IntSet::operator-(const IntSet &_set)
{
	IntSet _subtract;
	set<int> __subtract;
	for (int i = 0; i < this->count; i++)
	{
		__subtract.insert(this->values[i]);
	}
	for (int i = 0; i < _set.count; i++)
	{
		if (__subtract.find(_set.values[i]) != __subtract.end())
			__subtract.erase(_set.values[i]);
		else
			__subtract.insert(_set.values[i]);
	}
	_subtract.count = (int)__subtract.size();
	_subtract.values = new int[_subtract.count];
	int i = 0;
	for (auto value : __subtract)
	{
		_subtract.values[i++] = value;
	}
	return _subtract;
}
IntSet IntSet::operator+(const IntSet &_set)
{
	IntSet _union;
	set<int> __union;
	for (int i = 0; i < this->count; i++)
	{
		__union.insert(this->values[i]);
	}
	for (int i = 0; i < _set.count; i++)
	{
		__union.insert(_set.values[i]);
	}
	_union.count = (int)__union.size();
	_union.values = new int[_union.count];
	int i = 0;
	for (auto value : __union)
	{
		_union.values[i++] = value;
	}
	return _union;
}
int &IntSet::operator[](int index)
{
	if (index >= count || index < 0)
		cout << "index out of bound!";
	exit(0);
	return values[index];
}
ostream &operator<<(ostream &os, const IntSet &_set)
{
	if (_set.count > 0)
	{
		for (int i = 0; i < _set.count - 1; i++)
		{
			os << _set.values[i] << " ";
		}
		os << _set.values[_set.count - 1];
	}
	else
		cout << "empty set!";
	return os;
}
istream &operator>>(istream &is, IntSet &_set)
{
	set<int> set_;
	cout << "checkpoint 0" << '\n';
	if (_set.count > 0)
	{
		for (int i = 0; i < _set.count; i++)
		{
			set_.insert(_set.values[i]);
		}
	}
	cout << "checkpoint 1" << '\n';
	int n;
	cout << "number of new unique elements: ";
	is >> n;
	cout << "new elements: ";

	cout << "checkpoint 2" << '\n';

	for (int i = 0; i < n; i++)
	{
		int temp;
		is >> temp;
		set_.insert(temp);
	}
	cout << "checkpoint 3" << '\n';
	delete[] _set.values;
	_set.count = static_cast<int>(set_.size());
	_set.values = new int[_set.count];
	cout << "checkpoint 4" << '\n';
	int i = 0;
	for (auto value : set_)
	{
		_set.values[i] = value;
		i++;
	}
	cout << "checkpoint 5" << '\n';
	return is;
}

int main()
{
	int *list = new int[3];
	list[0] = 1;
	list[1] = 2;
	list[2] = 2;
	IntSet set0(list, 3), set1;
	cout << set0 << '\n';
	cin >> set0;
	cout << set0 << '\n';
	cout << "set1 size: " << set1.getCount() << '\n';
	cout << "set1 elements: " << set1 << '\n';
	cin >> set1;
	cout << set1 << '\n';
	// IntSet s1, s2(list, 3), s3;
	// cin >> s1 >> s2;
	// s3 = s1 + s2;
	// s3 = s1 - s2;
	// cout << "cout << s3: ";
	// cout << s3;
	// cout << "cout << s3[0]: ";
	// cout << s3[0];
	// cout << "cout << (s1 == s2): ";
	// cout << (s1 == s2);
	return 0;
}