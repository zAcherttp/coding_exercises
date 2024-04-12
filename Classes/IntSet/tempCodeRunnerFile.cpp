	friend istream &operator>>(istream &is, IntSet &_set)
	{
		set<int> set_;

		for(int i = 0; i < _set.count; i++)
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

		_set.count = (int)set_.size();
		delete[] _set.values;
		_set.values = new int[_set.count];
		int i = 0;
		for (auto value : set_)
		{
			_set.values[i] = value;
			i++;
		}
		return is;
	}