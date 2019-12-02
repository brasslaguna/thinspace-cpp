
#ifndef TIMER_H_
#define TIMER_H_

#include <chrono>

namespace util {

constexpr int kFps = 100;

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::time_point TimePoint;
typedef std::chrono::duration<long, std::ratio<1, kFps>> FrameDuration;

class Timer {

	public:

		bool UpdateFrame(void) {

			TimePoint now = Clock::now();

			if(now - time_ >= FrameDuration(1)) {

				time_ = now;

				return true;
			
			} else {

				return false;

			}
			
		};

	private:

		TimePoint time_ = Clock::now();

};

} // namespace util

#endif // TIMER_H_