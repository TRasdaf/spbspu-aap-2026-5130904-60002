#include <cstring>
#include <iostream>

const char second[] = "abc_ef";
const int out1 = 1;
const int out0 = 0;

namespace ketov {

  char *findCommonChars(char *dest, const char *str1, const char *str2)
  {
    int idx = 0;
    for (int i = 0; i < strlen(str1); i++) {
      for (int j = 0; j < strlen(str2); j++) {
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
    int counts[10] = {0};
    for (int i = 0; str[i] != '\0'; i++) {
      if (std::isdigit(str[i])) {
        counts[str[i] - '0'] += 1;
        if (counts[str[i] - '0'] > 1) {
          return out1;
        }
      }
    }
    return out0;
  }

} // namespace ketov

int main()
{
  try {
    int size = 0;
    int capacity = 8;
    char *first = new char[capacity];
    char ch = 0;
    while (std::cin.get(ch) && ch != '\n') {
      if (size + 1 >= capacity) {
        int newCapacity = capacity * 2;
        char *newFirst = new char[newCapacity];
        for (int i = 0; i < size; i++) {
          newFirst[i] = first[i];
        }
        delete[] first;
        first = newFirst;
        capacity = newCapacity;
      }
      first[size] = ch;
      size++;
    }
    first[size] = '\0';

    char *dest = new char[std::strlen(first) + 1];
    char *res1 = ketov::findCommonChars(dest, first, second);
    int res2 = ketov::hasRepeatedDigits(first);

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