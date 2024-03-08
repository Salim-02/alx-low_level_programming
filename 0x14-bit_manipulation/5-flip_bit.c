#include "main.h"

/**
 * flip_bits - Counts the number of bits to flip to get from one number to another
 * @n: first number
 * @m: second number
 *
 * Return: Number of bits to flip
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int exclusive = n ^ m;
	unsigned int countbit = 0;

	while (exclusive)
	{
		countbit += exclusive & 1;
		exclusive >>= 1;
	}

	return (countbit);
}
