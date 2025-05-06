#include <stdio.h>

int	main(void)
{
	int	return_value;

	unsigned long meow = 111111111111111111;

	char	c = 'a';
	char	*str = "This is a string";
	int		i = -1234;
	unsigned int	u = 1234;
	unsigned int	x = 1234;
	unsigned int	X = 1234;
	void	*p = &meow;

	return_value = printf("Printf:\n"
	"	Char: %c\n"
	"	String: %s\n"
	"	Decimal: %d\n"
	"	Integer: %i\n"
	"	Unsingned Integer: %u\n"
	"	Percent sign: %%\n"
	"	Hexadecimal Lowercase: %x\n"
	"	Hexadecimal Uppercase: %X\n"
	"	Pointer: %p\n"
		, c, str, i, i, u, x, X, p);

	printf("\nReturn Value: %i\n", return_value);
}
