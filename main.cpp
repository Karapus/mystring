#include "mystring.h"
#include <iostream>

#define $(statement) printf("(%03d) >>>> %s\n", __LINE__, #statement); statement; putchar('\n');
int main()
{
	MyString str1("a", "str1");
	MyString str2("b", "str2");
	MyString str3((str1 + str2 + str2 + str1), "str3");

	$(str1 = str2 + str1)

	std::cout << str1;
	std::cout << str2;
	std::cout << str3;

	return 0;
}
