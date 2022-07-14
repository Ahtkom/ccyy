#ifndef CCYY_UTIL_CLOCK
#define CCYY_UTIL_CLOCK

#include "util/IllegalArgumentException.h"

#include <chrono>
#include <iostream>
#include <string>
#include <type_traits>

namespace ccyy {
namespace util {

// For time counting.
class Clock
{
public:
  using time_point = std::chrono::system_clock::time_point;

  Clock();

  ~Clock() = default;

  // Start time counting.
  void tic();

  // End time counting and show the duration from start time.
  void toc();

  // Template overload of toc for different timespan.
  template <typename duration,
      typename = std::void_t<typename duration::period, typename duration::rep>>
  void toc();

private:
  std::chrono::duration<long, std::ratio<1, 1000000000>> getDuration();

private:
  time_point from_time, end_time;

  bool tic_flag;
};

template <typename duration, typename>
void
Clock::toc() {
  if (not tic_flag) {
    printf("%s: Please call tic() first!\n", __PRETTY_FUNCTION__);
    return;
  }

  end_time = std::chrono::high_resolution_clock::now();
  tic_flag = false;

  auto num = duration::period::num;
  auto den = duration::period::den;

  std::string repr = "%ld";
  if (num == 1) {
    switch (den) {
    case 1:
      repr += " seconds ";
      break;
    case 1000:
      repr += " milliseconds ";
      break;
    case 1000000:
      repr += " microseconds ";
      break;
    case 1000000000:
      repr += " nanoseconds ";
      break;
    }
  } else if (num == 60) {
    repr += " minutes ";
  } else if (num == 3600) {
    repr += " hours ";
  }
  repr += "passed\n";

  printf(repr.c_str(),
      static_cast<std::size_t>(
          std::chrono::duration_cast<duration>(getDuration()).count()));
}

} // namespace util
} // namespace ccyy

#endif // CCYY_UTIL_CLOCK