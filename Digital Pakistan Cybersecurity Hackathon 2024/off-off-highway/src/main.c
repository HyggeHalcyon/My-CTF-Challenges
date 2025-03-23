#include <stdio.h>  
#include <stdlib.h>
#include <time.h>
#define MAX_LANES 10
#define NAME_LENGTH 0x10

typedef struct highway {
    long lanes;
    char name[NAME_LENGTH];    
} highway;
highway pool[MAX_LANES];
int used = 0;

void init() {
    srand(time(NULL));
    setvbuf(stdout, 0, _IONBF, 0);
    setvbuf(stdin, 0, _IONBF, 0);
}

void menu() {
    printf(
        "1. add new highway\n"
        "2. add more lanes\n"
        "3. exit\n"
        "> "
    );
}

void new_highway(){
    long idx;

    printf("where do you want the highway to be put at?\n> ");
    scanf("%ld%*c", &idx);

    if (idx > MAX_LANES) {
        printf("sorry can't do that sir\n");
        return;
    }

    printf("what is the name of the highway?\n> ");
    fgets(pool[idx].name, NAME_LENGTH, stdin);

    if (used == 0) {
        printf("how many lanes do you want?\n> ");
        scanf("%ld%*c", &pool[idx].lanes);
        used = 1;
    } else {
        pool[idx].lanes = rand() % 100;
    }

    puts("just to wrap up, here's what you gave us:");
    printf("name: %s\n", pool[idx].name);
    printf("lanes: %ld\n", pool[idx].lanes);

    return;
}

void moar_lanes() {
    int idx;
    long to_add;

    printf("which highway do you want to add more lanes to?\n> ");
    scanf("%d%*c", &idx);

    if (idx > MAX_LANES) {
        printf("sorry can't do that sir\n");
        return;
    }

    printf("how many more lanes do you want to add?\n> ");
    scanf("%ld%*c", &to_add);

    pool[idx].lanes += to_add;

    return;
}

int main(int argc, char *argv[]) {
    init();

    int c = 0;
    while(1) {
        menu();
        scanf("%d%*c", &c);
        switch(c) {
            case 1:
                new_highway();
                break;
            case 2:
                moar_lanes();
                break;
            case 3:
                exit(0);
                break;
            default:
                puts("invalid choice");
        }
    }

    return 0;
}