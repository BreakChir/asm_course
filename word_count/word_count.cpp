#include <cstdio>
#include <nmmintrin.h>

using namespace std;

auto SPACES_MASK = _mm_set1_epi8(' ');
auto ONE_MASK = _mm_set1_epi8((char) 1);

size_t word_count(char const *str, size_t size) {
    if (!size) return 0;
    size_t cnt = 0;
    if (str[0] != ' ') {
        ++cnt;
    }

    for (size_t i = 1; i < size; ++i) {
        if (str[i] != ' ' && str[i - 1] == ' ') {
            ++cnt;
        }
    }
    return cnt;
}

size_t count_SSE(char *str, size_t size) {
    if (size < 48)
        return word_count(str, size);

    size_t mod = 16 - (size_t) str % 16;
    size_t cnt = word_count(str, mod);
    int ans = 0;
    size -= mod;
    size_t i = mod;

    for (; size > 16; i += 16, size -= 16) {
        auto cur_str = _mm_loadu_si128((__m128i *) (str + i));
        auto cur_str_shift = _mm_loadu_si128((__m128i *) (str + i - 1));

        auto spaces = _mm_cmpgt_epi8(cur_str, SPACES_MASK);
        auto spaces_shift = _mm_cmpgt_epi8(cur_str_shift, SPACES_MASK);

        auto xor_words = _mm_xor_si128(spaces, spaces_shift);
        auto end_words = _mm_and_si128(xor_words, ONE_MASK);

        auto parts = reinterpret_cast<unsigned long long *>(&end_words);
        auto part_left = __builtin_popcountll(parts[0]);
        auto part_right = __builtin_popcountll(parts[1]);
        ans += part_left + part_right;
    }

    if (str[mod - 1] != ' ' && str[mod] == ' ') --ans;
    else if (str[mod - 1] != ' ' && str[mod] != ' ') --ans;
    if (ans >= 0) {
        if (ans % 2 == 1 && str[i] == ' ') {
            ++ans;
        }
        ans /= 2;
    }

    ans += cnt;
    ans += word_count(str + i, size);
    return (size_t) ans;
}


