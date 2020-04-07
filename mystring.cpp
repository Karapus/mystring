#include <string>
#include <string.h>
#include <iostream>

struct MyString
{
	private:
	std::string name_;
	size_t capacity_ = 0;
	size_t size_ = 0;
	char *data_ = nullptr;

	public:
	MyString(const char *str, 	std::string name = "noname");
	MyString(const MyString& that, 	std::string name = "noname");
	MyString(MyString&& that, 	std::string name = "noname");

	~MyString();

	MyString& operator = (MyString that);

	MyString& operator += (const MyString& other) ;
	
	friend MyString operator + (MyString fst, const MyString& scd);

	char& operator [] (size_t i)
	{
		return data_[i];
	};

	friend int compare (const MyString& fst, const MyString& scd)
	{
		return strncmp(fst.data_, scd.data_, fst.size_ < scd.size_ ? fst.size_ : scd.size_);
	};
#define CMP_OP(op)								\
	friend bool operator op (const MyString& fst, const MyString& scd)	\
	{									\
		return compare(fst, scd) op 0;					\
	};
	CMP_OP(<)
	CMP_OP(>)
	CMP_OP(==)
	CMP_OP(<=)
	CMP_OP(>=)
#undef CMP_OP

	friend std::ostream& operator << (std::ostream& os, const MyString& str);
	friend std::istream& operator >> (std::istream& is, MyString& str);

	std::string name()
	{
		return name_;
	};
	size_t size()
	{
		return size_;
	};
	size_t capacity()
	{
		return capacity_;
	};
	const char* data()
	{
		return data_;
	};
	friend void swap(MyString& a, MyString& b);
	size_t reserve(size_t capacity);
	bool empty()
	{
		return size_ == 0;
	};
	char *c_str();
	void clear()
	{
		size_ = 0;
	};
	void push_back(char c)
	{
		data_[++size_] = c;	
	};
	char pop_back()
	{
		return data_[size_--];
	};
	void shrink_to_fit();
};

MyString::MyString(const char *str, std::string name) :
	name_(name),
	capacity_(strlen(str)),
	size_(capacity_),
	data_(new char[size_])
{
	memcpy(data_, str, size_);
}

MyString::MyString(const MyString& that, std::string name) :
	name_("(" + name + " as copy of " + that.name_ + ")"),
	capacity_(that.capacity_),
	size_(that.size_),
	data_(new char[that.capacity_])
{
	memcpy(data_, that.data_, size_);
}

MyString::MyString(MyString&& that, std::string name) :
	name_("(" + name + " as move of " + that.name_ + ")"),
	capacity_(that.capacity_),
	size_(that.size_),
	data_(that.data_)
{
	that.data_ = nullptr;
	that.size_ = that.capacity_ = 0;
}

MyString::~MyString()
{
	if (data_)
		delete[] data_;
	data_ = nullptr;
	size_ = capacity_ = 0;
}

MyString& MyString::operator = (MyString that)
{
	swap(*this, that);
	name_ = "(" + name_ + " = " + that.name_ + ")";
	return *this;
}

MyString& MyString::operator += (const MyString& other)
{
	reserve(size_ + other.size_);
	memcpy(data_ + size_, other.data_, other.size_);
	size_ += other.size_;
	name_ = "(" + name_ + " += " + other.name_ + ")";
	return *this;
}

MyString operator + (MyString fst, const MyString& scd)
{
	fst += scd;
	return fst;
}

size_t MyString::reserve(size_t capacity)
{
	if (capacity_ < capacity)
	{
		char *data = new char[capacity];
		memcpy(data, data_, size_);
		capacity_ = capacity;
		delete[] data_;
		data_ = data;
	}
	return capacity_;
}

void MyString::shrink_to_fit()
{
	if (size_ != capacity_)
	{
		char *new_data = new char[size_];
		memcpy(new_data, data_, size_);
		delete data_;
		data_ = new_data;
	}
}

char *MyString::c_str()
{
	char *res = new char[size_ + 1];
	res[size_] = '\0';
	return res;
}

std::ostream& operator << (std::ostream& os, const MyString& str)
{
	for (size_t i = 0; i < str.size_; i++)
		os << str.data_[i];
	return os;
}

std::istream& operator >> (std::istream& is, MyString& str)
{
	int c = '\n';
	while ((c = is.get()) != '\n' && (c != EOF))
	{
		if (str.size_ == str.capacity_)
			str.reserve(2 * str.capacity_);
		str.push_back(c);
	}
	str.shrink_to_fit();
	return is;
}

void swap(MyString& a, MyString& b)
{
	std::swap(a.size_, b.size_);
	std::swap(a.capacity_, b.capacity_);
	std::swap(a.data_, b.data_);
	/*char tmp[sizeof(MyString)] = {};
	memcpy(&tmp,	&a,	sizeof(MyString));
	memcpy(&a,	&b,	sizeof(MyString));
	memcpy(&b,	&tmp,	sizeof(MyString));*/
}
