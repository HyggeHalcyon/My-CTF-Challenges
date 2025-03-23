#!/bin/bash

gcc -fstack-protector-all -pie main.c -o chall
docker build -t pwn_medium_off-off-highway .
docker run --privileged --name=pwn_medium_off-off-highway --rm -p7003:1337 -d -it pwn_medium_off-off-highway