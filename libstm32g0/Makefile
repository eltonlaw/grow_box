LIB=libstm32g0.a

CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
CFLAGS=-mcpu=cortex-m0plus -mthumb -g -O0
CFLAGS=-mcpu=cortex-m0plus -mthumb -g3 -O0
CFLAGS+=-I../STM32CubeG0/Drivers/CMSIS/Device/ST/STM32G0xx/Include
CFLAGS+=-I../STM32CubeG0/Drivers/CMSIS/Include
CFLAGS+=-I../libstm32g0/include
CFLAGS+=-DSTM32G070xx

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)

all: stm32g070rbt.a

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIB): $(OBJS)
	$(AR) cr $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIB)
