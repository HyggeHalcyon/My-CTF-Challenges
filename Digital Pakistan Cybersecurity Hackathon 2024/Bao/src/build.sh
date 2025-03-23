#!/bin/bash

gcc -fstack-protector-all -pie -Wl,-z,relro,-z,now main.c -o chall -lseccomp
docker build -t pwn_medium_bao .
docker run --privileged --name=pwn_medium_bao --rm -p7006:1337 -d -it pwn_medium_bao 