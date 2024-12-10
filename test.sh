#!/usr/bin/bash
sudo make && sudo make install && g++ main.cpp -o test.out -lbrawlermaker -lcsv && ./test.out $@
