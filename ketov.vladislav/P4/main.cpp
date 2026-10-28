#include <cctype>
#include <cstddef>
#include <cstring>
#include <iostream>

const char second[] = "abc_ef";
const int out1 = 1;
const int out0 = 0;
const size_t initial_capacity = 8;
const size_t digits_count = 10;

namespace ketov {

  char *findCommonChars(char *dest, const char *str1, const char *str2)
  {
    size_t idx = 0;
    for (size_t i = 0; i < strlen(str1); i++) {
      for (size_t j = 0; j < strlen(str2); j++) {
        if (str1[i] == str2[j]) {
          dest[idx] = str1[i];
          idx++;
          break;
        }
      }
    }
    dest[idx] = '\0';
    return dest;
  }

  int hasRepeatedDigits(const char *str)
  {
    int counts[digits_count] = {0};
    for (size_t i = 0; str[i] != '\0'; i++) {
      if (std::isdigit(static_cast< unsigned char >(str[i]))) {
        counts[str[i] - '0'] += 1;
        if (counts[str[i] - '0'] > 1) {
          return out1;
        }
      }
    }
    return out0;
  }
}

int main()
{
  try {
    size_t size = 0;
    size_t capacity = initial_capacity;
    char *first = new char[capacity];
    char ch = 0;
    while (std::cin.get(ch) && ch != '\n') {
      if (size + 1 >= capacity) {
        const size_t new_capacity = capacity * 2;
        char *const new_first = new char[new_capacity];
        for (size_t i = 0; i < size; i++) {
          new_first[i] = first[i];
        }
        delete[] first;
        first = new_first;
        capacity = new_capacity;
      }
      first[size] = ch;
      size++;
    }
    if (size == 0) {
      delete[] first;
      std::cerr << "Empty input\n";
      return out1;
    }

    first[size] = '\0';

    char *const dest = new char[std::strlen(first) + 1];
    const char *const res1 = ketov::findCommonChars(dest, first, second);
    const int res2 = ketov::hasRepeatedDigits(first);

    std::cout << res1 << "\n";

    std::cout << res2 << "\n";

    delete[] dest;
    delete[] first;

    return out0;
  } catch (...) {
    std::cerr << "Exception occured" << std::endl;
    return out1;
  }
}
