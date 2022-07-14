#include "util/Clock.h"

#include <chrono>

namespace ccyy {
namespace util {

Clock::Clock()
    : tic_flag(false) { }

void
Clock::tic() {
  from_time = std::chrono::high_resolution_clock::now();
  tic_flag = true;
}

void
Clock::toc() {
  if (not tic_flag) {
    printf("%s: Please call tic() first!\n", __PRETTY_FUNCTION__);
    return;
  }

  end_time = std::chrono::high_resolution_clock::now();
  tic_flag = false;
  printf("%lf seconds passed\n",
      static_cast<double>(
          std::chrono::duration_cast<std::chrono::milliseconds>(getDuration())
              .count() /
          1000.0));
}

std::chrono::duration<long, std::ratio<1, 1000000000>>
Clock::getDuration() {
  return (end_time - from_time);
}

} // namespace util
} // namespace ccyy
