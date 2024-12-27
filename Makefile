CC = g++
CFLAGS = -c -g -Wall -std=c++17
CXXFLAGS = -O2 -std=c++17
AR = ar rcs

TARGET_STATIC = libbrawlermaker.a
TARGET_SHARED = libbrawlermaker.so
TARGET_BIN = bm
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib
BIN_DIR = /usr/bin

LIB_SOURCES = brawlermaker.cpp
LIB_OBJECTS = $(LIB_SOURCES:.cpp=.o)

CLI_SOURCES = main.cpp
CLI_OBJECTS = $(CLI_SOURCES:.cpp=.o)

all: $(TARGET_STATIC) $(TARGET_SHARED) $(TARGET_BIN)

$(TARGET_STATIC): $(LIB_OBJECTS)
	$(AR) $@ $^

$(TARGET_SHARED): $(LIB_SOURCES)
	$(CC) -fPIC -c $(LIB_SOURCES)
	$(CC) -shared -o $@ brawlermaker.o

$(TARGET_BIN): $(CLI_OBJECTS) $(TARGET_STATIC)
	$(CC) $(CLI_OBJECTS) -o $@ -L. -lbrawlermaker -lcsv -static

%.o: %.cpp
	$(CC) $(CFLAGS) -fPIC -o $@ $<

install: all
	cp brawlermaker.h brawler.h $(INCLUDE_DIR)/
	cp $(TARGET_STATIC) $(TARGET_SHARED) $(LIB_DIR)/
	cp $(TARGET_BIN) $(BIN_DIR)/

clean:
	rm -f *.o $(TARGET_STATIC) $(TARGET_SHARED) $(TARGET_BIN)
