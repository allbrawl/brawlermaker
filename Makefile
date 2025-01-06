CC = g++
CFLAGS = -c -g -Wall
CXXFLAGS = -O2

TARGET_BIN = bm
BIN_DIR = /usr/bin

SOURCES = main.cpp tui.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET_BIN)

$(TARGET_BIN): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lflatline -lbrawlermaker -lncurses

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

install: $(TARGET_BIN)
	cp $(TARGET_BIN) $(BIN_DIR)/

clean:
	rm -f *.o $(TARGET_BIN)
