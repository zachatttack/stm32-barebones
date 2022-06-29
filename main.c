#include <stdint.h>

#define RCC_BASE	(struct rcc *) 0x40023800

#define GPIOA_BASE	(struct gpio *) 0x40020000
#define GPIOB_BASE	(struct gpio *) 0x40020400
#define GPIOC_BASE	(struct gpio *) 0x40020800

struct rcc {
	volatile uint32_t cr;	/* 0 - control reg */
	volatile uint32_t pll;	/* 4 - pll config */
	volatile uint32_t conf;	/* 8 - clock config */
	volatile uint32_t cir;	/* c - clock interrupt */
	volatile uint32_t ahb1_r;	/* 10 - AHB1 peripheral reset */
	volatile uint32_t ahb2_r;	/* 14 - AHB2 peripheral reset */
	int __pad1[2];
	volatile uint32_t apb1_r;	/* 20 - APB1 peripheral reset */
	volatile uint32_t apb2_r;	/* 24 - APB2 peripheral reset */
	int __pad2[2];
	volatile uint32_t ahb1_e;	/* 30 - AHB1 peripheral enable */
	volatile uint32_t ahb2_e;	/* 34 - AHB2 peripheral enable */
	int __pad3[2];
	volatile uint32_t apb1_e;	/* 40 - APB1 peripheral enable */
	volatile uint32_t apb2_e;	/* 44 - APB2 peripheral enable */
	int __pad4[2];
	volatile uint32_t ahb1_elp;	/* 50 - AHB1 peripheral enable in low power */
	volatile uint32_t ahb2_elp;	/* 54 - AHB2 peripheral enable in low power */
	int __pad5[2];
	volatile uint32_t apb1_elp;	/* 60 - APB1 peripheral enable in low power */
	volatile uint32_t apb2_elp;	/* 64 - APB2 peripheral enable in low power */
	int __pad6[2];
	volatile uint32_t bdcr;	/* 70 */
	volatile uint32_t csr;	/* 74 */
	int __pad7[2];
	volatile uint32_t sscgr;	/* 80 */
	volatile uint32_t plli2s;	/* 84 */
	int __pad8;
	volatile uint32_t dccr;	/* 8c */
};

struct gpio {
	volatile uint32_t mode;	/* 0x00 */
	volatile uint32_t otype;	/* 0x04 */
	volatile uint32_t ospeed;	/* 0x08 */
	volatile uint32_t pupd;	/* 0x0c */
	volatile uint32_t idata;	/* 0x10 */
	volatile uint32_t odata;	/* 0x14 */
	volatile uint32_t bsrr;	/* 0x18 */
	volatile uint32_t lock;	/* 0x1c */
	volatile uint32_t afl;	/* 0x20 */
	volatile uint32_t afh;	/* 0x24 */
};

struct gpio *pGpio;

void gpio_init()
{
	pGpio = GPIOC_BASE;
	struct rcc *rp = RCC_BASE;

  rp->ahb1_e |= (1 << 2);

  int bit = 13;
  int shift = bit *2;

	pGpio->mode &= ~(3<<shift);
	pGpio->mode |= (1<<shift);
	pGpio->otype &= ~(1<<bit);
}

void delay ( void )
{
	// volatile int count = 1000 * FAST;
	volatile unsigned int count = 1000 * 800;

	while ( count-- )
	    ;
}


void main(void)
{
	pGpio = GPIOC_BASE;
 
  gpio_init();

  while(1){
    pGpio->bsrr |= (1<<13);
    delay();
    pGpio->bsrr |= 1<<(13+16);
  }

}
