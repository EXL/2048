# There is no compiler optimization flags because of these bugs:
#
# https://github.com/SerenityOS/serenity/issues/2580
# https://github.com/SerenityOS/serenity/issues/2597
#
# Please use ports for host compiler optimizations.
#
# Update 26-Sep-2020:
# Why is there a compilation error without `-isystem /usr/include` include option?
# Check this on future versions of Serenity or with the release of a new C++ standard.
#
# Update 27-Sep-2020:
# It's is Toolchain/GCC mistake, see: https://github.com/SerenityOS/serenity/issues/3605

CC = gcc
CXX = g++

PROGRAM = 2048-Serenity
OBJS = ../src/2048.o main.o
CFLAGS = -I../src/
CXXFLAGS = -I../src/ -isystem /usr/include -std=c++20 -fno-rtti
LDFLAGS = -lgui -lgfx -lcore -lipc

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm $(OBJS) $(PROGRAM)

run:
	./$(PROGRAM)
