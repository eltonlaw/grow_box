CC=arm-none-eabi-gcc
CFLAGS=-mcpu=cortex-m0plus -mthumb -g -O0
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
CFLAGS+=-I./STM32CubeG0/Drivers/CMSIS/Include
CFLAGS+=-I./src
LDFLAGS=-Tlinker_script.ld -nostartfiles
OBJCOPY=arm-none-eabi-objcopy

SRC = $(wildcard src/*.c)

all: main.bin

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.elf: $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f *.elf *.bin

flash: main.bin
	STM32_Programmer_CLI -c port=SWD -w main.bin 0x8000000 -rst
