#include "IntSet.h"

IntSet::IntSet(int* _values, int _count)
{
	if (_values == nullptr)
		values = new int[_count];
	else
		count = _count;
}
IntSet::~IntSet()
{
	delete[] values;
}

int IntSet::getCount() const
{
	return count;
}
IntSet IntSet::makeSet() const
{
	IntSet intset;
	set<int> set;
	for (int i = 0; i < count; i++)
	{
		set.insert(values[i]);
	}
	intset.count = (int)set.size();
	intset.values = new int[intset.count];
	int i = 0;
	for (auto value : set)
	{
		intset.values[i++] = value;
	}
	return intset;
}

istream& operator>>(istream& is, IntSet& _set)
{
	int n;
	cout << "nhap so phan tu cua set: ";
	is >> n;
	set<int> set_;
	cout << "nhap cac phan tu: ";
	for (int i = 0; i < n; i++)
	{
		int temp;
		is >> temp;
		set_.insert(temp);
	}
	_set.count = (int)set_.size();
	delete[] _set.values;
	_set.values = new int[_set.count];
	int j = 0;
	for (auto value : set_)
	{
		_set.values[j] = value;
		j++;
	}
	return is;
}
ostream& operator<<(ostream& os, const IntSet& _set)
{
	for (int i = 0; i < _set.count - 1; i++)
	{
		os << _set.values[i] << " ";
	}
	os << _set.values[_set.count - 1];
	return os;
}
int& IntSet::operator[](int index)
{
	if (index >= count || index < 0)
		cout << "index out of bound";
	exit(0);
	return values[index];
}

IntSet IntSet::operator+(const IntSet& _set)
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
		_union.values[i] = value;
		i++;
	}
	return _union;
}
IntSet IntSet::operator-(const IntSet& _set)
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
		_subtract.values[i] = value;
		i++;
	}
	return _subtract;
}
bool IntSet::operator==(const IntSet& _set)
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