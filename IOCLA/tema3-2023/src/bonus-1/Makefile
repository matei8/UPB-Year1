include ../Makefile.common

CHECKFILE = check-x64
ASMFILE = bonus_x64
ASFLAGS = -felf64
CFLAGS = -fno-pie -no-pie -g
LDFLAGS = -fno-pie -no-pie -g
DEPS = $(CHECKFILE).o $(ASMFILE).o

all: checker

build: checker

$(CHECKFILE).o: $(CHECKFILE).c

$(ASMFILE).o: $(ASMFILE).asm

checker: $(DEPS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm *.o checker
