#include "mystring.h"

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

char& MyString::operator [] (size_t i)
{
	return data_[i];
}

int compare(const MyString& fst, const MyString& scd)
{
	return strncmp(fst.data_, scd.data_, fst.size_ < scd.size_ ? fst.size_ : scd.size_);
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
		delete[] data_;
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
	os << str.name_ << " = \"";
	for (size_t i = 0; i < str.size_; i++)
		os << str.data_[i];
	os << "\"" << std::endl;
	return os;
}

std::istream& operator >> (std::istream& is, MyString& str)
{
	int c = '\n';
	str.clear();
	while ((c = is.get()) != '\n' && (c != EOF))
		str.push_back(c);
	str.shrink_to_fit();
	return is;
}

void swap(MyString& a, MyString& b)
{
	std::swap(a.size_, b.size_);
	std::swap(a.capacity_, b.capacity_);
	std::swap(a.data_, b.data_);
	/*char tmp[sizeof(MyString)] = {}
	memcpy(&tmp,	&a,	sizeof(MyString));
	memcpy(&a,	&b,	sizeof(MyString));
	memcpy(&b,	&tmp,	sizeof(MyString));*/
}

std::string MyString::name()
{
	return name_;
}

size_t  MyString::size()
{
	return size_;
}

size_t  MyString::capacity()
{
	return capacity_;
}

const char*  MyString::data()
{
	return data_;
}

bool  MyString::empty()
{
	return size_ == 0;
}

void  MyString::clear()
{
	size_ = 0;
}

void  MyString::push_back(char c)
{
	if (size_ == capacity_)
		reserve(2 * capacity_ + 1);
	data_[size_++] = c;
}

char  MyString::pop_back()
{
	if (size_)
		return data_[--size_];
	return '\0';
}
