include ../Makefile.common

CHECKFILE = check-syscall
ASMFILE = bonus_syscall
DEPS = $(CHECKFILE).o $(ASMFILE).o

all: checker

build: checker

$(CHECKFILE).o: $(CHECKFILE).c

$(ASMFILE).o: $(ASMFILE).asm

checker: $(DEPS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm *.o checker
