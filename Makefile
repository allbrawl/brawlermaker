CC = g++
CFLAGS = -c -g -Wall
CXXFLAGS = -O2

TARGET_BIN = bm
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

LIBS = -lbrawlermaker -lflatline -lncurses

all: $(TARGET_BIN)

$(TARGET_BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o $(TARGET_BIN)
