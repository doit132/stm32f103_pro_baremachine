#include "string.h"

void HardFault_Handler(void)
{
	// 由于使用了串口, 所以使用之前需要初始化, 所以引发硬件中断之前必须初始化串口
	puts("HardFault_Handler\r\n");
	while (1) {
	}
}
