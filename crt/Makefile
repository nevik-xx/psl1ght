PSL1GHT_INTERNAL := ..
include $(PSL1GHT_INTERNAL)/rules/internal.mk

CFILES		:= $(wildcard *.c)
SFILES		:= $(wildcard *.S)
CRT0		:= lv2-crt0.o
CRT1		:= crt0.o crt1.o

STUBS		:= $(SFILES:.S=.o) $(CFILES:.c=.o)

all: $(STUBS) $(CRT0)

clean:
	rm -f $(STUBS) $(CRT0)

install: all
	@mkdir -p $(PS3DEV)/host/ppu/ppu/lib
	@cp -f lv2-*.o $(PS3DEV)/host/ppu/ppu/lib/

$(CRT0): $(CRT1)
	ppu-ld -r $(CRT1) -o $(CRT0)

%.o: %.c
	$(CC) -I../include -c $< -o $@

%.o: %.S
	$(CC) -I../include -c $< -o $@

.PHONY: all clean
