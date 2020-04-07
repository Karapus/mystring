#include "mystring.cpp"
#include <iostream>

int main()
{
	MyString str1("a", "str1");
	MyString str2("b", "str2");
	MyString str3((str1 + str2 + str2 + str1), "str3");

	str1 = str2 + str1;

	std::cout << str1.name() << " = " << '"' << str1 << '"' << '\n';
	std::cout << str2.name() << " = " << '"' << str2 << '"' << '\n';
	std::cout << str3.name() << " = " << '"' << str3 << '"' << '\n';

	return 0;
}
