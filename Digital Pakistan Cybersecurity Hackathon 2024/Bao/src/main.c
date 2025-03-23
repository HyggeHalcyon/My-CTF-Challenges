#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/mman.h> 
#include <linux/filter.h>
#include <seccomp.h>
#include <syscall.h>
#include <string.h>

// __asm__(
//         "xor rax, rax;"
//         "xor rbx, rbx;"
//         "xor rcx, rcx;"
//         "xor rdx, rdx;"
//         "xor rsi, rsi;"
//         "xor rdi, rdi;"
//         "xor rbp, rbp;"
//         "xor r9, r9;"
//         "xor r10, r10;"
//         "xor r11, r11;"
//         "xor r12, r12;"
//         "xor r13, r13;"
//         "xor r14, r14;"
//         "xor r15, r15;"
//         "xor rbp, rbp;"
//         "xor rsp, rsp;"
//     );
char prefix[] = { 0x48, 0x31, 0xC0, 0x48, 0x31, 0xDB, 0x48, 0x31, 0xC9, 0x48, 0x31, 0xD2, 0x48, 0x31, 0xF6, 0x48, 0x31, 0xFF, 0x48, 0x31, 0xED, 0x4D, 0x31, 0xC9, 0x4D, 0x31, 0xD2, 0x4D, 0x31, 0xDB, 0x4D, 0x31, 0xE4, 0x4D, 0x31, 0xED, 0x4D, 0x31, 0xF6, 0x4D, 0x31, 0xFF, 0x48, 0x31, 0xED, 0x48, 0x31, 0xE4 };
void *code = 0; 

void setup_seccomp() {
    scmp_filter_ctx ctx;
	ctx = seccomp_init(SCMP_ACT_KILL);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, __NR_preadv2, 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, __NR_openat, 0);
    seccomp_rule_add(ctx, SCMP_ACT_ALLOW, __NR_writev, 0);
	seccomp_load(ctx);
}

void run_code() {
    ((void(*)())code)();
}

int main(int argc, char *argv[]) {
    setvbuf(stdout, NULL, _IONBF, 0);
    code = mmap(0, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (code == MAP_FAILED) {
        perror("mmap");
        return 1;
    }
    puts("shellcode: ");
    read(0, code+sizeof(prefix), 0x1000);
    memcpy(code, prefix, sizeof(prefix));
    mprotect(code, 0x1000, PROT_READ | PROT_EXEC);
    
    setup_seccomp();
    run_code();

    return 0;
}