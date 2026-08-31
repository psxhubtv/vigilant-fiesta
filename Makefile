# PSL1GHT/PS3 homebrew Makefile (minimal scaffold)
# This is a placeholder Makefile. Replace the BUILD commands with your PSL1GHT
# toolchain commands or a cross-compiler invocation you use.

APP = vigilant_fiesta
SRC = src/main.c
OBJ = $(SRC:.c=.o)

all: build

build:
	@echo "Building $(APP) - placeholder"
	@echo "Replace this with your PSL1GHT build pipeline (pdx, psl1ght-toolchain, or cross-compiler)."
	@echo "Example: psl1ght-makefile or ps3sdk/build commands"

clean:
	rm -f $(OBJ) $(APP) *.elf

.PHONY: all build clean
