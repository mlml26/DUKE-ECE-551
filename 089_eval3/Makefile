SOURCES=function.cpp  page.cpp  book.cpp  cyoa-step2.cpp 
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++11

cyoa-step2: $(OBJS)
	g++ $(CPPFLAGS) -o cyoa-step2 $(OBJS)
%.o: %.cpp function.h  page.h  book.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm cyoa-step2 *~ *.o

