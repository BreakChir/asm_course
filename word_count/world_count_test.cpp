#include "word_count.cpp"
#include <cstring>
#include <ctime>

size_t pass_cnt = 0;
size_t test_cnt = 0;

void test_own(char *str, char *s) {
    size_t n = strlen(str);
    if (count_SSE(str, n) == word_count(str, n)) {
        printf("test_%s: OK\n", s);
        ++pass_cnt;
    } else {
        printf("test_%s: FAIL\n", s);
    }
}

void start_own() {
    char str1[] = "                                                            1 2 111 1 1 1 1 1  "
            "1111111111111111111111111111111111111111111111111111111                  3 4 5 6 7 8 9 0"
            "                                            ";
    char str2[] = "1";
    char str3[] = "";
    char str4[] = "sfgs gdsd gfsdsadfadf adsfdjfsd sdsfsdmf sdfdma asaasasas asasasas asasasa sass            a   ";
    char str5[] = " 111 234 22 12dsf aaa        sa fdgfa ad     aaaa       a a a            asas as  aaa a a   a a a";
    char str6[] = "1111 25 234 1223441";
    char str7[] = " ad d d12 312frweefsdfs sdf ";
    char str8[] = "11111dsdfgsj;dfsasfgs%235&*$!#1111%%@$dg111111g1ds1s11hh11g1da11a1111111111111111111111111111111";
    char str9[] = " f b a d e f 1 2 r & a ? & | % 1 2 3 4 5 6 7 8 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 8 7 6 g g g g";
    char str10[] = "               aaaaaaaaaaaaaaaaaa               ";

    test_own(str1, (char *) "big_str");
    test_own(str2, (char *) "one_symbol");
    test_own(str3, (char *) "empty");
    test_own(str4, (char *) "space_end");
    test_own(str5, (char *) "space_start");
    test_own(str6, (char *) "without_space");
    test_own(str7, (char *) "space_start_end");
    test_own(str8, (char *) "one_big_word");
    test_own(str9, (char *) "space_even");
    test_own(str10, (char *) "one_long_word");
    test_own(str10 + 1, (char *) "with_shift");

    test_cnt += 11;
}

void test_random(int ran, int num) {
    srand(ran);
    size_t n = 123;
    auto *str = new char[n];
    for (size_t i = 0; i < n; ++i) {
        int a = rand() % 80;
        if (a % 2 == 0) {
            str[i] = ' ';
        } else {
            str[i] = (char) (rand() % 80 + 38);
        }
    }

    if (count_SSE(str, n) == word_count(str, n)) {
        printf("random_test_%d: OK\n", num);
        ++pass_cnt;
    } else {
        printf("random_test_%d: FAIL\n", num);
    }

    delete[] str;
}

void start_random() {
    srand(time(0));
    size_t cnt = 100;
    for (int i = 0; i < cnt; ++i) {
        test_random(rand() + 12341252, i + 1);
    }
    test_cnt += cnt;
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

void run_tests() {
    start_own();
    start_random();
}

int main() {
    run_tests();
    print_result(pass_cnt, test_cnt);
}