#include "string.h"
#include "exception.h"

void HardFault_Handler(void)
{
	puts("HardFault_Handler\r\n");
	// 注意当中断触发会, 必须在中断处理程序中进行软件触发, 让其知道中断执行完了,
	// 否则会不断的执行中断处理程序
	while (1) {
	}
}

void SVC_Handler(void)
{
	puts("SVC_Handler\n\r");
}

void UsageFault_Handler(unsigned int *stack)
{
	SCB_Type *SCB = (SCB_Type *)SCB_BASE_ADDR;
	puts("UsageFault_Handler\n\r");
	// 注意当中断触发会, 必须在中断处理程序中进行软件触发 (清除中断状态寄存器中的值),
	// 让其知道中断执行完了, 否则会不断的执行中断处理程序

	// clear usage fault
	SCB->CFSR = SCB->CFSR;

	// set pc to next instruction
	// 因为栈中现在存放的就是导致中断发生的指令地址, 如果不设置让pc指向下一条指令的地址,
	// 那么会导致中断结束后, 再次进入中断, stack 是传入的 sp 栈指针, stack[6]
	// 就是硬件自动保存的触发使用异常的指令所在的地址, 让这个地址 + 4 让 pc 指向下一条指令
	// 当触发使用异常的时候, 先执行汇编语言中的 UsageFault_Handler_asm 函数,
	// 因为对于中断函数传参来说, 还是汇编更简单直接, UsageFault_Handler_asm 函数会跳到 C
	// 定义的这个函数执行
	// 注意: 这里需要设置 pc 是因为这个异常就是存放的触发中断的指令地址,
	// 而像 svchandler 这样的异常则不是如此, 所以不需要设置 pc, 所以只需要记住有的中断请求,
	// 需要手动清除中断标志位, 有的则不需要, 而且有的中断在栈中存放的是下一条指令的地址,
	// 所以也不需要重新设置栈中的下一条指令地址
	stack[6] += 4;
}

void UsageFaultInit(void)
{
	SCB_Type *SCB = (SCB_Type *)SCB_BASE_ADDR;
	SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk);
}
