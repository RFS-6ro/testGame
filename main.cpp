#include <iostream>

///<summary>
///function to translate and print value from 10 to 2 number system
///</summary>
void trans_to_binary(int32_t value)
{
	if (abs(value) < INT32_MAX)
	{
		for (unsigned int bite = 1U << 31; bite; bite >>= 1)
			putchar('0' + !!(value & bite));
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	int i;
	while (1)
	{
		std::cin >> i;
		trans_to_binary(i);
	}
	return 0;
}
