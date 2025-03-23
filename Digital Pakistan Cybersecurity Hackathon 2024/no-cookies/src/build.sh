#!/bin/bash

gcc -pie -fstack-protector-all main.c -o chall
docker build -t pwn_medium_no-cookies .
docker run --privileged --name=pwn_medium_no-cookies --rm -p7004:1337 -d -it pwn_medium_no-cookiess