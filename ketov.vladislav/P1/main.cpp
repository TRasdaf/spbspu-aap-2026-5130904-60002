#include <iostream>
#include <limits>

const int code0 = 0;
const int code1 = 1;
const int code2 = 2;

namespace ketov {

  class Counter {
  private:
    size_t len_ = 0;

  public:
    void operator()(int)
    {
      ++len_;
    }

    size_t operator()() const
    {
      return len_;
    }
  };

  class SubMax {
  private:
    int max1_ = std::numeric_limits< int >::min();
    int max2_ = std::numeric_limits< int >::min();
    Counter counter_;

  public:
    void operator()(int n)
    {
      counter_(n);
      if (n > max1_) {
        max2_ = max1_;
        max1_ = n;
      } else if (n > max2_ && n < max1_) {
        max2_ = n;
      }
    }

    int operator()() const
    {
      if (counter_() < 2) {
        throw std::invalid_argument("Should be 2 or more arguments");
      }
      return max2_;
    }
  };

  class SumDup {
  private:
    int last1_ = 0;
    int last2_ = 0;
    Counter counter_;
    int matches_ = 0;

  public:
    void operator()(int n)
    {
      int cnt = counter_();
      counter_(n);

      if (cnt == 0) {
        last2_ = n;
      } else if (cnt == 1) {
        last1_ = n;
      } else {
        if (n == last1_ + last2_) {
          matches_++;
        }
        last2_ = last1_;
        last1_ = n;
      }
    }

    int operator()() const
    {
      if (counter_() < 3) {
        throw std::invalid_argument("Should be 3 or more arguments");
      }
      return matches_;
    }
  };

} // namespace ketov

int main()
{
  ketov::SubMax subMax;
  ketov::SumDup sumDup;
  int value = 0;

  while (std::cin >> value) {
    if (value == 0) {
      break;
    }
    subMax(value);
    sumDup(value);
  }

  if (!std::cin) {
    std::cerr << "not a number\n";
    return code1;
  }

  try {
    std::cout << subMax() << "\n";
    std::cout << sumDup();
  } catch (std::invalid_argument &e) {
    std::cerr << e.what() << std::endl;
    return code2;
  }

  return code0;
}
