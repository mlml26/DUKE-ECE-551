CFLAGS=-std=gnu++11 -pedantic -Wall -Werror -ggdb3
PROGS=cyoa-step1 cyoa-step2
OBJS=$(patsubst %,%.o,$(PROGS)) function.o page.o book.o
all: $(PROGS)
cyoa-step%: cyoa-step%.o function.o page.o book.o
	g++ -o $@ $^
%.o: %.cpp
	g++ $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f *~ $(PROGS) $(OBJS)

function.o: function.h
page.o: page.h
book.o: book.h

