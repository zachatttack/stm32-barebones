#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (96 * 1024) //96K
#define SRAM_END ((SRAM_START) + (SRAM_SIZE)) //0x20020000U

#define STACK_START SRAM_END

extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;

extern uint32_t _sbss;
extern uint32_t _ebss;

void main(void);

void Reset_Handler(void);
void NMI_Handler(void)            __attribute__((weak, alias ("Default_Handler")));
void HardFault_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void MemManage_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void BusFault_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void UsageFault_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void SVCall_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void DebugMonitor_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void PendSV_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void Systick_Handler(void)      __attribute__((weak, alias ("Default_Handler")));


uint32_t vectors[] __attribute__((section(".isr_vector")))= {
  STACK_START,
  (uint32_t)Reset_Handler,
  (uint32_t)NMI_Handler,
  (uint32_t)MemManage_Handler,
  (uint32_t)BusFault_Handler,
  (uint32_t)UsageFault_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)SVCall_Handler,
  (uint32_t)DebugMonitor_Handler,
  0,
  (uint32_t)PendSV_Handler,
  (uint32_t)Systick_Handler,
  //IRQ to last on in vector table
    

};

void Default_Handler(void)
{
    while(1);
} 

// copy .data to SRAM
// init .bss to zero
// (optional) call init function of std lib
// call main

void Reset_Handler(void)
{
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t *pDst = (uint8_t*)&_sdata; //sram
    uint8_t *pSrc = (uint8_t*)&_etext; //flash

    for(uint32_t i=0; i < size ; i++){
      *pDst++ = *pSrc++;
    }

    size = &_ebss - &_sbss;
    pDst = (uint8_t*)&_sbss;
    for(uint32_t i=0; i < size ; i++){
      *pDst++ = 0;
    }

    main();

}
