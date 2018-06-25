#include <cstdio>

static void copy1(const char *src, const char *dst, size_t size) {
    if (size > 0) {
        asm volatile(
        "loop_1:\n"
                "mov (%0), %%al\n"
                "mov %%al, (%1)\n"
                "inc %0\n"
                "inc %1\n"
                "dec %2\n"
                "jnz loop_1\n"
        :"+r"(src), "+r"(dst), "+r"(size)
        :
        :"cc", "memory", "al"
        );
    }
}

static void copy8(char *src, char *dst, size_t size) {
    if (size > 0) {
        size_t blocks_cnt = size / 8;
        size_t mod = size % 8;
        if (blocks_cnt > 0) {
            asm volatile(
            "loop_8:\n"
                    "mov (%0), %%rax\n"
                    "mov %%rax, (%1)\n"
                    "add $8, %0\n"
                    "add $8, %1\n"
                    "dec %2\n"
                    "jnz loop_8\n"
            :"+r"(src), "+r"(dst), "+r"(blocks_cnt)
            :
            :"cc", "memory", "rax"
            );
        }
        if (mod > 0) {
            copy1(src, dst, mod);
        }
    }
}

static void copy16(char *src, char *dst, size_t size) {
    if (size > 0) {
        size_t blocks_cnt = size / 16;
        size_t mod = size % 16;
        if (blocks_cnt > 0) {
            asm (
            "loop_16:\n"
                    "movdqu (%0), %%xmm0\n"
                    "movdqu %%xmm0, (%1)\n"
                    "add $16, %0\n"
                    "add $16, %1\n"
                    "dec %2\n"
                    "jnz loop_16\n"
            :"+r"(src), "+r"(dst), "+r"(blocks_cnt)
            :
            :"cc", "memory", "xmm0"
            );
        }
        if (mod > 0) {
            copy8(src, dst, mod);
        }
    }
}

static void copy16_align(char *src, char *dst, size_t size) {
    if (size > 0) {
        auto off = 16 - (size_t) src % 16;
        copy8(src, dst, off);
        copy16(src + off, dst + off, size - off);
    }
}

