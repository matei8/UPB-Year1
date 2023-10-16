include ../Makefile.common

CHECKFILE = check-timegate
ASMFILE = bonus_timegate
DEPS = $(CHECKFILE).o $(ASMFILE).o

all: checker

build: checker

$(CHECKFILE).o: $(CHECKFILE).c

$(ASMFILE).o: $(ASMFILE).asm

checker: $(DEPS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm *.o checker
