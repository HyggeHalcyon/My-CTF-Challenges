#include <stdio.h>

void init() {
    setvbuf(stdin, 0, _IONBF, 0);
    setvbuf(stdout, 0, _IONBF, 0);
}

// sub rsp, 0x50
// jmp rsp
// ret 
static const char __attribute__((section (".text"))) code[] = { 0x48, 0x83, 0xEC, 0x50, 0xFF, 0xE4, 0xC3 };

int main(int argc, char *argv[]) {
    char buf[0x40];

    init();
    printf(":mssfrog: >>");
    read(0, buf, 0x40+8+8);

    return 0;
}