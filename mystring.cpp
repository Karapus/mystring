#include <string>
#include <string.h>
#include <iostream>

const size_t DATA_CAP = 100;

struct MyString
{
	public:
	size_t size_ = 0;
	size_t capacity_ = DATA_CAP;
	std::string name_;
	char data_[DATA_CAP] = {};
	//MyString();

	MyString(const char *str, 	std::string name = "noname");
	MyString(const MyString& that, 	std::string name = "noname");
	MyString(MyString&& that, 	std::string name = "noname");

	~MyString();

	MyString&	operator = 	(const MyString& that);

	MyString&	operator +=	(const MyString& other) ;
	MyString&	operator +=	(MyString&& other);
	friend MyString	operator +	(const MyString& fst,	const MyString& snd);
	friend MyString	operator +	(const MyString& fst,	MyString&& snd);
	friend MyString	operator +	(MyString&& fst,	const MyString& snd);
	friend MyString	operator +	(MyString&& fst,	MyString&& snd);
};
//using namespace MyString;

MyString::MyString(const char *str, std::string name) :
	size_(strlen(str)),
	name_(name)
{
	memcpy(data_, str, size_);
}

MyString::MyString(const MyString& that, std::string name) :
	size_(that.size_),
	name_("(" + name + " as copy of " + that.name_ + ")")
{
	memcpy(data_, that.data_, strlen(that.data_));
}

MyString::MyString(MyString&& that, std::string name) :
	size_(that.size_),
	name_("(" + name + " is moved " + that.name_ + ")")
{
	memcpy(data_, that.data_, strlen(that.data_));
}

MyString::~MyString()
{
}

MyString& MyString::operator += (const MyString& other)
{
	strcat(data_, other.data_);
	name_ = "(" + name_ + " += " + other.name_ + ")";
	return *this;
}

MyString& MyString::operator += (MyString&& other)
{
	strcat(data_, other.data_);
	name_ = "(" + name_ + " += " + other.name_ + ")";
	return *this;
}

MyString operator + (const MyString& fst, const MyString& snd)
{
	std::cout << "1 type of + names:" << fst.name_ << " " << snd.name_ << '\n';
	MyString res(fst);
	res += snd;
	return res;
}

MyString operator + (const MyString& fst, MyString&& snd)
{
	std::cout << "2 type of + names:" << fst.name_ << " " << snd.name_ << '\n';
	MyString res(fst);
	res += (MyString&&) snd;
	return res;
}

MyString operator + (MyString&& fst, const MyString& snd)
{
	std::cout << "3 type of + names:" << fst.name_ << " " << snd.name_ << '\n';
	MyString res((MyString&&)fst);
	res += snd;
	return res;
}

MyString operator + (MyString&& fst, MyString&& snd)
{
	std::cout << "4 type of + names:" << fst.name_ << " " << snd.name_ << '\n';
	MyString res((MyString&&)fst);
	res += (MyString&&) snd;
	return res;
}
