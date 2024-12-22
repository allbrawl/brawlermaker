CC = g++
CFLAGS = -c -g
LDFLAGS = -lbrawlermaker
TARGET_LIB = libbrawlermaker.a
INCLUDE_DIR = /usr/include
LIB_DIR = /usr/lib

all: $(TARGET_LIB)

brawlermaker.o: brawlermaker.cpp
	$(CC) $(CFLAGS) brawlermaker.cpp -o brawlermaker.o

$(TARGET_LIB): brawlermaker.o
	ar rcs $(TARGET_LIB) brawlermaker.o

install:
	cp brawlermaker.h brawler.h $(INCLUDE_DIR)/
	cp $(TARGET_LIB) $(LIB_DIR)/

clean:
	rm -f *.o $(TARGET_LIB)