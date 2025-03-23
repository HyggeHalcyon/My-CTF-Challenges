#!/bin/bash

gcc -fno-stack-protector -z execstack -no-pie main.c -o chall
docker build -t pwn_medium_jump .
docker run --privileged --name=pwn_medium_jump --rm -p7001:1337 -d -it pwn_medium_jump