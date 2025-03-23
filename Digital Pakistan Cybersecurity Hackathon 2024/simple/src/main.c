#include <stdio.h>
#include <stdlib.h>
#define FLAG_SIZE 0x200

void init() {
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);
}

void read_flag(char *buf) {
    FILE *f = fopen("flag.txt", "r");
    if (f == NULL) {
        puts("flag.txt not found");
        exit(1);
    }

    fgets(buf, FLAG_SIZE, f);
}

int main(int argc, char *argv[]) {
    char flag[FLAG_SIZE];
    char input[0x10];

    init();
    read_flag(flag);
    for(int i = 0; i < 4; i++) {
        printf("say what?");
        fgets(input, 0x10, stdin);
        printf(input);
    }
    puts("welp, that's it, hope you got what you're looking for");

    return 0;
}