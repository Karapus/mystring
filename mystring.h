#ifndef MYSTRING
#define MYSTRING
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

	char& operator [] (size_t i);

	friend int compare (const MyString& fst, const MyString& scd);
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

	friend void swap(MyString& a, MyString& b);

	std::string name();
	size_t size();
	size_t capacity();
	const char* data();
	size_t reserve(size_t capacity);
	bool empty();
	char *c_str();
	void clear();
	void push_back(char c);
	char pop_back();
	void shrink_to_fit();
};

#endif
