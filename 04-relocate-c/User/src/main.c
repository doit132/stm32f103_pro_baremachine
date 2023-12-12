
#include "uart.h"
#include "string.h"

char g_Char = 'A';
const char g_Char2 = 'B';
int g_A[3] = {0, 0};
char g_B[9];

void delay(volatile int d)
{
	while (d--)
		;
}

void SystemInit(void *loadaddr)
{
	extern int _vector_start;
	extern int __bss_start;
	extern int __bss_end;
	unsigned int len;

	// 代码, 数据重定位
	len = &__bss_start - &_vector_start;
	memcpy(&_vector_start, loadaddr, len);

	// bss clear
	len = &__bss_end - &__bss_start;
	memset(&__bss_start, 0, len);
}

int main()
{
	char c;
	void (*funcptr)(const char *s, unsigned int val);

	static int s_C[16] = {0, 0};

	funcptr = put_s_hex;

	uart_init();

	delay(1);

	putchar('1');
	putchar('0');
	putchar('0');
	putchar('a');
	putchar('s');
	putchar('k');
	putchar('\n');
	putchar('\r');

	funcptr("test for text relocate ", 123);

	put_s_hex("g_Char's addr  = ", (unsigned int)&g_Char);
	put_s_hex("g_Char2's addr = ", (unsigned int)&g_Char2);
	put_s_hex("g_A[0]'s val = ", g_A[0]);
	put_s_hex("g_B[0]'s val = ", g_B[0]);
	put_s_hex("s_C[0]'s val = ", s_C[0]);

	putchar(g_Char);
	putchar(g_Char2);

	while (1) {
		c = getchar();
		putchar(c);
		putchar(c + 1);
	}

	return 0;
}
