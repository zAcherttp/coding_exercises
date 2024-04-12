#include <iostream>
#include <set>
using namespace std;
class IntSet
{
private:
	int *values;
	int count;

public:
	IntSet(int *_values = nullptr, int _count = 0)
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
	~IntSet()
	{
		delete[] values;
	}

	int getCount() const
	{
		return count;
	}
	IntSet makeSet() const
	{
		IntSet intset;
		set<int> uniques;
		for (int i = 0; i < count; i++)
		{
			uniques.insert(values[i]);
		}
		intset.count = (int)uniques.size();
		intset.values = new int[intset.count];
		int i = 0;
		for (auto value : uniques)
		{
			intset.values[i++] = value;
		}
		return intset;
	}
	friend istream &operator>>(istream &is, IntSet &_set)
	{
		set<int> set_;

		for (int i = 0; i < _set.count; i++)
		{
			set_.insert(_set.values[i]);
		}

		int n;
		cout << "nhap them so phan tu cua set: ";
		is >> n;
		cout << "nhap cac phan tu: ";

		for (int i = 0; i < n; i++)
		{
			int temp;
			is >> temp;
			set_.insert(temp);
		}

		delete[] _set.values;
		_set.count = static_cast<int>(set_.size());
		_set.values = new int[_set.count];

		int i = 0;
		for (auto value : set_)
		{
			_set.values[i] = value;
			i++;
		}
		return is;
	}
	friend ostream &operator<<(ostream &os, const IntSet &_set)
	{
		for (int i = 0; i < _set.count - 1; i++)
		{
			os << _set.values[i] << " ";
		}
		os << _set.values[_set.count - 1];
		return os;
	}

	int &operator[](int index)
	{
		if (index >= count || index < 0)
			cout << "index out of bound";
		exit(0);
		return values[index];
	}
	IntSet operator+(const IntSet &_set)
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
	IntSet operator-(const IntSet &_set)
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
	bool operator==(const IntSet &_set)
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
};

int main()
{
	int *list = new int[3];
	list[0] = 1;
	list[1] = 2;
	list[2] = 2;
	IntSet s1, s2(list, 3), s3;
	cin >> s1 >> s2;
	s3 = s1 + s2;
	s3 = s1 - s2;
	cout << "cout << s3: ";
	cout << s3;
	cout << "cout << s3[0]: ";
	cout << s3[0];
	cout << "cout << (s1 == s2): ";
	cout << (s1 == s2);
	return 0;
}