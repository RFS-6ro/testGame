#include <iostream>

///<summary>
///function to translate and print value from 10 to 2 number system
///</summary>
void trans_to_binary(int value)
{
	unsigned int bit_depth = 1;
	unsigned int binary_value = 0;

	while (value > 0) {
		binary_value += bit_depth * (value % 2);
		bit_depth *= 10;
		value /= 2;
	}

	std::cout << binary_value << std::endl;
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