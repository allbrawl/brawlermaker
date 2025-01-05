#!/usr/bin/bash
sudo make && sudo make install && g++ main.cpp tui.cpp -o test.out -lbrawlermaker -lcsv -lncurses && ./test.out $@
