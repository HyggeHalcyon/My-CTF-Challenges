#!/bin/bash

gcc -fstack-protector-all -pie -Wl,-z,relro,-z,now main.c -o chall
docker build -t pwn_easy_simple .
docker run --privileged --name=pwn_easy_simple --rm -p7002:1337 -d -it pwn_easy_simple