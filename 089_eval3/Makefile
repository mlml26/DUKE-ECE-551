SOURCES=function.cpp  page.cpp  cyoa-step1.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11

cyoa-step1: $(OBJS)
	g++ $(CPPFLAGS) -o cyoa-step1 $(OBJS)
%.o: %.cpp function.h  page.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm cyoa-step1 *~ *.o

