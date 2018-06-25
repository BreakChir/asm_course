#include <cstdlib>
#include <ctime>
#include "memcpy.cpp"

size_t pass_cnt = 0;
size_t test_cnt = 0;

void test_copy1() {
    char s1[] = "123456";
    char s2[10];
    bool ok = true;

    copy1(s1, s2, sizeof s1);
    for (int i = 0; i < sizeof s1; ++i) {
        if (s1[i] != s2[i]) {
            ok = false;
            break;
        }
    }

    if (ok) {
        ++pass_cnt;
        printf("test_copy1: OK\n");
    } else {
        printf("test_copy1: FAIL\n");
    }
}

void test_copy8() {
    char s1[11] = "0123456789";
    char s2[20];
    bool ok = true;

    copy8(s2, s1, sizeof s1);
    for (int i = 0; i < sizeof s1; ++i) {
        if (s2[i] != s1[i]) {
            ok = false;
            break;
        }
    }

    if (ok) {
        ++pass_cnt;
        printf("test_copy8: OK\n");
    } else {
        printf("test_copy8: FAIL\n");
    }
}

void test_copy16() {
    srand(time(0));
    size_t size = 12345678;
    auto *s1 = new char[size];
    auto *s2 = new char[size];
    for (int i = 0; i < size; ++i) {
        s1[i] = char(rand() % 10 + 'a');
    }
    bool ok = true;

    copy16(s1, s2, size);
    for (int i = 0; i < size; ++i) {
        if (s1[i] != s2[i]) {
            ok = false;
            break;
        }
    }

    if (ok) {
        ++pass_cnt;
        printf("test_copy16: OK\n");
    } else {
        printf("test_copy16: FAIL\n");
    }

    delete[] s1;
    delete[] s2;
}

void test_copy16_align() {
    srand(time(0));
    int size = 12345;
    auto *s1 = new char[size];
    auto *s2 = new char[size];
    for (int i = 0; i < size; ++i) {
        s1[i] = char(rand() % 10 + 'a');
    }
    auto shift = size_t(rand() % 10) + 1;
    bool ok = true;

    copy16_align(s1 + shift, s2, size - shift);
    for (size_t i = shift; i < size; ++i) {
        if (s1[i] != s2[i - shift]) {
            ok = false;
            break;

        }
    }

    if (ok) {
        ++pass_cnt;
        printf("test_copy16_align: OK\n");
    } else {
        printf("test_copy16_align: FAIL\n");
    }

    delete[] s1;
    delete[] s2;
}

void run_tests() {
    test_copy1();
    test_copy8();
    size_t cnt = 10;
    for (int i = 0; i < cnt; i++) {
        test_copy16();
        test_copy16_align();
    }
    test_cnt += 2 * 10 + 2;
}

void print_result(size_t passed, size_t test_cnt) {
    printf("Tests are passed: %d/%d\n", (int) passed, (int) test_cnt);
    printf("Result: ");
    if (passed == test_cnt) {
        printf("OK\n");
    } else {
        printf("FAIL\n");
    }
}

int main() {
    run_tests();
    print_result(pass_cnt, test_cnt);
    return 0;
}
