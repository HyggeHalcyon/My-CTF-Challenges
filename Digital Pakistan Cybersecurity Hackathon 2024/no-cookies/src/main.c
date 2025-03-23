#include <stdio.h>  
#include <stdlib.h>
#define MAX_POOL 11
#define BUFFER_PAD 0x10

typedef struct idk {
    long d;
    char s[BUFFER_PAD];
} idk;

void init() {
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);
}

void menu() {
    printf(
        "1. add\n"
        "2. show\n"
        "3. exit\n"
        "> "
    );
}

void vuln() {
    idk pool[MAX_POOL];
    // char pool[240];
    long count = 0;
    long idx = 0;

    long c = 0;
    while(1) {
        menu();
        scanf("%ld%*c", &c);
        switch(c) {
            case 1:
                printf("d > ");
                scanf("%ld%*c", &pool[count].d);
                printf("s > ");
                scanf("%15s", &pool[count].s);
                count++;
                break;
            case 2:
                printf("idx > ");
                scanf("%ld%*c", &idx);
                if (idx < 0 || idx >= count) {
                    puts("no buenos");
                    return;
                }
                printf("d := %ld\ns := %s\n", pool[idx].d, pool[idx].s);
                break;
            case 3:
                exit(0);
                break;
            default:
                puts("invalid choice");
        }
    }

    return;
}

int main(int argc, char *argv[]) {
    init();
    // printf("%s", "link start!\n");
    vuln();

    return 0;
}