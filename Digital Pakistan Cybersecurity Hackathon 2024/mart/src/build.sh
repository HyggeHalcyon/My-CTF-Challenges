#!/bin/bash

gcc -fstack-protector-all -pie -Wl,-z,relro,-z,now main.c -o chall
docker build -t pwn_easy_mart .
docker run --privileged --name=pwn_easy_mart --rm -p7005:1337 -d -it pwn_easy_mart