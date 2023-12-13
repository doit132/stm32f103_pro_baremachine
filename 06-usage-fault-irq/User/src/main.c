
#include "uart.h"
#include "string.h"
#include "exception.h"

char g_Char = 'A';
const char g_Char2 = 'B';
int g_A[3] = {0, 0};
char g_B[9];

void delay(volatile int d)
{
	while (d--)
		;
}

// 函数定义，用于触发硬件故障
void trigger_hard_fault(void)
{
	volatile unsigned int *ptr = (volatile unsigned int *)0x00000000;

	// 通过访问一个空指针来触发硬件故障
	*ptr = 0xDEADBEEF;
}

// 函数定义，用于触发UsageFault
void trigger_usage_fault(void)
{
	// 执行一个不合法的指令，例如未定义的指令
	__asm("UDF #1");
}

int main()
{
	char c;
	void (*funcptr)(const char *s, unsigned int val);

	static int s_C[16] = {0, 0};

	funcptr = put_s_hex;

	uart_init();
	UsageFaultInit();

	// trigger_hard_fault();
	trigger_usage_fault();
        
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

	extern int _svector;
	extern int _sdata;
	put_s_hex("_svector: ", (unsigned int)&_svector);
	put_s_hex("_sdata: ", (unsigned int)&_sdata);

	while (1) {
		c = getchar();
		putchar(c);
		putchar(c + 1);
	}

	return 0;
}
