CC = g++
CFLAGS = -c -g
LDFLAGS = -lbrawlermaker -lcsv
TARGET_LIB = libbrawlermaker.a
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib
BIN_DIR = /usr/bin
TARGET_BIN = bm
CXXFLAGS = -O2 -Wall -std=c++17

all: $(TARGET_LIB) $(TARGET_BIN)

brawlermaker.o: brawlermaker.cpp
	$(CC) $(CFLAGS) brawlermaker.cpp -o brawlermaker.o

$(TARGET_LIB): brawlermaker.o
	ar rcs $(TARGET_LIB) brawlermaker.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.o

$(TARGET_BIN): main.o $(TARGET_LIB)
	$(CC) main.o -o $(TARGET_BIN) $(LDFLAGS)

install: all
	cp brawlermaker.h brawler.h $(INCLUDE_DIR)/
	cp $(TARGET_LIB) $(LIB_DIR)/
	cp $(TARGET_BIN) $(BIN_DIR)/

clean:
	rm -f *.o $(TARGET_LIB) $(TARGET_BIN)

win:
	$(CC) $(CXXFLAGS) brawlermaker.cpp main.cpp csv.cpp -o bm.exe