 #include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

#define FAIL "****************** TEST FAILED *********************\n\n"

int	main(void)
{
	int		a;
	int		b;
	char	*s;

	// x tests
	printf("x tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%x", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%x %x %x %x", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x %x %x %x",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// X tests
	printf("X tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%X", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%X %X %X %X", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X %X %X %X",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// c tests
	printf("c tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c", '0' - 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'
			- 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf("%c ", '0' + 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'
			+ 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %c %c %c ", '1', '2',
			'3'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c %c %c ",
			'1', '2', '3'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// d & i tests
	printf("d & i tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %d ", -99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", -99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", 100));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", 100));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d ", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %d %i %d %i", INT_MAX, INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d %i %d %i", INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
{	// p tests
	printf("p tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)-1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)-1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)15));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)15));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf("p tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %p ", NULL));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			NULL));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)LONG_MIN, (void *)LONG_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)LONG_MIN, (void *)LONG_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)INT_MIN, (void *)INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)INT_MIN, (void *)INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)ULONG_MAX, (void *)-ULONG_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)ULONG_MAX, (void *)-ULONG_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// s tests
	s = "this is a longer test string to test printf";
	printf("s tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%s", ""));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%s", ""));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %s %s ", "", "-"));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %s %s ", "",
			"-"));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %s %s %s %s %s", "\
			- ", "", "4", "", s));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %s %s %s %s\
			%s", " - ", "", "4", "", s));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// u tests
	printf("u tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %u ", -100));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			-100));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	printf(" printf out\n%d printf length\n", a = printf(" %u ", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
	// mix tests
	printf("mix tests\n");
	printf(" printf out\n%d printf length\n",
		a = printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%c%%", 'A', "42", 42, 42, 42, 42, 42, 'B', "-42", -42, -42, -42,\
			-42, 42, 'C', "0", 0, 0, 0, 0, 42, 0));
	printf(" ft_printf out\n%d ft_printf length\n",
		b = ft_printf("%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%%\
			%c%%", 'A', "42", 42, 42, 42, 42, 42, 'B', "-42", -42, -42, -42,\
			-42, 42, 'C', "0", 0, 0, 0, 0, 42, 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
}
}