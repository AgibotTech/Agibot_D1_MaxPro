#!/bin/bash
g++ src/high_level_remote_tcp_client_test.cpp -Lbuild -Iinclude -I/usr/include -lhigh_level_remote_tcp_client -lcrypto -Wl,-rpath=build -o build/high_level_remote_tcp_client_test