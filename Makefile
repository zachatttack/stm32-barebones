CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall
LDFLAGS= -nostdlib -T f401.ld -Wl,-Map=final.map
OCDCFG = -f /usr/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/share/openocd/scripts/target/stm32f4x.cfg

all: blink.o stm32_startup.o blink.elf

blink.o: blink.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o: stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

blink.elf: blink.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf

flash: blink.elf
	openocd $(OCDCFG) -c "program blink.elf verify reset exit"

ocd:
	openocd $(OCDCFG)
