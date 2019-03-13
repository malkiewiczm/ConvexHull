MAKEFLAGS += Rr
.PHONY: all clean

all: a.out

a.out: ch.cpp
	g++ -Wall -Wextra -Wpedantic -Wshadow -std=c++11 $<
clean:
	rm -f a.out



