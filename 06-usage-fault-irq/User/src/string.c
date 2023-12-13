#include "uart.h"

/**
 * @brief 写入字符串
 *
 * @param s 字符串
 * @return int 成功返回 0
 */
int puts(const char *s)
{
	while (*s) {
		putchar(*s);
		s++;
	}
	return 0;
}

void puthex(unsigned int val)
{
	/* 0x76543210 */
	int i, j;

	puts("0x");
	for (i = 7; i >= 0; i--) {
		j = (val >> (i * 4)) & 0xf;
		if ((j >= 0) && (j <= 9))
			putchar('0' + j);
		else
			putchar('A' + j - 0xA);
	}
}

void put_s_hex(const char *s, unsigned int val)
{
	puts(s);
	puthex(val);
	puts("\r\n");
}

/**
 * @brief 复制 src 地址 len 长度的数据到 dest 地址处
 *
 * @param dest 目标地址
 * @param src 源地址
 * @param len 数据长度
 */
void memcpy(void *dest, void *src, unsigned int len)
{
	unsigned char *pcDest = dest;
	unsigned char *pcSrc = src;

	while (len--) {
		*pcDest = *pcSrc;
		pcSrc++;
		pcDest++;
	}
}

/**
 * @brief 设置从目的地址开始 len 长度的数据为 val
 *
 * @param dest 目的地址
 * @param val 要设置的数据
 * @param len 要设置的数据长度
 */
void memset(void *dest, unsigned char val, unsigned int len)
{
	unsigned char *pcDest = dest;

	while (len--) {
		*pcDest = val;
		pcDest++;
	}
}
