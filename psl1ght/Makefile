# PSL1GHT Makefile (PS3 target)
# Replace the placeholders below with your PSL1GHT/PS3 SDK toolchain paths.
# This file is a scaffold to help you integrate with PSL1GHT. It will NOT work
# until you set the correct toolchain variables for your environment.

# Example usage:
#   make -f psl1ght/Makefile all

PSL1GHT_PATH ?= /path/to/psl1ght
CROSS_COMPILE ?= $(PSL1GHT_PATH)/bin/ppu-lv2-
CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy

TARGET = vigilant_fiesta.elf
SRCS = ../src/ps3/ps3_main.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -O2 -Wall -I$(PSL1GHT_PATH)/include
LDFLAGS = -L$(PSL1GHT_PATH)/lib -lpsl1ght -lppu -lfs

all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Compiling PS3 target (placeholder - configure PSL1GHT_PATH first)"
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
