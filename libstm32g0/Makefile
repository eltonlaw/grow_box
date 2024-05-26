LIB=libstm32g0.a
CC=arm-none-eabi-gcc
AR=arm-none-eabi-ar
CFLAGS=-mcpu=cortex-m0plus -mthumb -g -O0

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)

all: stm32g070rbt.a

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@

$(LIB): $(OBJS)
	$(AR) cr $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIB)
