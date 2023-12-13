#include "string.h"

void SystemInit(void *loadaddr)
{
	extern int __bss_start__;
	extern int __bss_end__;
	extern int _stext;
	extern int _edata;
	unsigned int len;

	// 代码, 数据重定位
	len = &_edata - &_stext;
	memcpy(&_stext, loadaddr, len);

	// bss clear
	len = &__bss_end__ - &__bss_start__;
	memset(&__bss_start__, 0, len);
}
