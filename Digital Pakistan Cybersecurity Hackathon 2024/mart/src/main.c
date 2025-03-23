#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define FLAGSIZE_MAX 0x40

void win(){
  char flag[FLAGSIZE_MAX];
  FILE *fd;

  fd = fopen("flag.txt", "r");
  if (fd == NULL){
    printf("%s%s", 
          "flag.txt not found, please create a flag.txt\n",
          "if this happened on remote server please contact admin");
    exit(1);
  }
  fgets(flag, FLAGSIZE_MAX, fd);
  printf(flag);
}

void setup(){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
}

void menu(){
  puts("what do you want to buy?");
  puts("(1) girlfriend Rp.99");
  puts("(2) friend Rp.1");
  puts("(3) perfect GPA Rp.666");
}

int main(){
  setup();
  int money = 1337;
  long c = 0;
  long n = 0;

  puts("welcome to ***mart!!!\n");
  while(1){
    if(money <= 0 || money > 1337){
      puts("uhh what just happened?");
    }

    printf("money: %d\n", money);
    menu();
    scanf("%d", &c);

    switch(c){
      case 1:
        puts("how much?");
        scanf("%d", &n);
        money -= n * 99;
        puts("got yourself a girlfriend <3\n");
        break;
      case 2:
        puts("how much?");
        scanf("%d", &n);
        money -= n * 1;
        puts("got yourself a new friend\n");
        break;
      case 3:
        puts("how much?");
        scanf("%d", &n);
        money -= n * 666;
        puts("got a perfect GPA for yourself\n");
        break;
      case 69:
        if(money <= 999999999){
          puts("to poor for that\n");
        } else{
          win();
          exit(1);
        }
        break;
      default:
        puts("sorry, i dont think we sell that here\n");
    }

    c = 0;
    n = 0;
  }

  return 0;
}