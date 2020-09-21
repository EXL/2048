# There is no compiler optimization flags because of these bugs:
#
# https://github.com/SerenityOS/serenity/issues/2580
# https://github.com/SerenityOS/serenity/issues/2597
#
# Please use ports for host compiler optimizations.

CC = gcc
CXX = g++

PROGRAM = 2048-Serenity
OBJS = ../src/2048.o main.o
CFLAGS = -I../src/
CXXFLAGS = -I../src/ -fno-rtti
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
