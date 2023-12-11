
void delay(int d)
{
	while (d--)
		;
}

int main()
{
	unsigned int *pReg;

	/* 使能 GPIOB */
	pReg = (unsigned int *)(0x40021000 + 0x18);
	*pReg |= (1 << 3);

	/* 设置 GPIOB0 为输出引脚 */
	pReg = (unsigned int *)(0x40010C00 + 0x00);
	*pReg |= (1 << 0);

	pReg = (unsigned int *)(0x40010C00 + 0x0C);

	while (1) {
		/* 设置 GPIOB0 输出 1 */
		*pReg |= (1 << 0);

		delay(1000000);

		/* 设置 GPIOB0 输出 0 */
		*pReg &= ~(1 << 0);

		delay(1000000);
	}

	return 0;
}
