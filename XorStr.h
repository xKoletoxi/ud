#pragma once

template <int X>
struct Xor {
    static constexpr char encrypt(char c, int i) {
        return c ^ (X + i);
    }

    template <size_t N>
    static void decrypt(char(&data)[N]) {
        for (size_t i = 0; i < N - 1; ++i) {
            data[i] ^= (X + i);
        }
    }

    template <size_t N>
    static constexpr void encryptData(char(&data)[N]) {
        for (size_t i = 0; i < N - 1; ++i) {
            data[i] ^= (X + i);
        }
    }

    template <size_t N>
    static const char* decryptOnce(char(&data)[N]) {
        decrypt(data);
        return data;
    }
};

#define XorStr(s) ([]() { \
    static char data[] = s; \
    Xor<__COUNTER__>::encryptData(data); \
    return Xor<__COUNTER__>::decryptOnce(data); \
}())

