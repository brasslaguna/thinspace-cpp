
#ifndef UTIL_MOTION_H_
#define UTIL_MOTION_H_

#include <vector>
#include <functional>
#include <chrono>
#include <cmath>
#include <memory>

namespace util {

	enum MotionEaseKey {
		
		kMotionEaseLinear,
		kMotionEaseInQuad,
		kMotionEaseOutQuad,
		kMotionEaseInOutQuad,
		kMotionEaseOutCubic,
		kMotionEaseInOutCubic,
		kMotionEaseInQuart,
		kMotionEaseOutQuart,
		kMotionEaseInOutQuart,
		kMotionEaseInQuint,
		kMotionEaseOutQuint,
		kMotionEaseInOutQuint,
		kMotionEaseInSin,
		kMotionEaseOutSin,
		kMotionEaseInOutSin,
		kMotionEaseInElastic,
		kMotionEaseOutElastic,
		kMotionEaseInOutElastic
	};

	typedef std::chrono::high_resolution_clock Clock;
	typedef Clock::time_point TimePoint;
	typedef std::chrono::duration<float> MotionDuration;

	typedef struct {

		MotionEaseKey ease;
		float duration;
		std::function<void (float delta)> callback;
		std::function<void (void)> finish_callback;

	} MotionConfig;

	class MotionFactory {

		public:

			void Create(MotionConfig config);
			void Run(void);

		private:

			class Motion {

				public:

					Motion(MotionConfig config) :
						config_(config) {

							start_ = Clock::now();

						}

						bool Step();

				private:
					
					float CalculateEase(MotionEaseKey key, float progress);
					MotionConfig config_;
					TimePoint start_;

			};

			std::vector<Motion> queued_motions_;

	};

	typedef std::shared_ptr<MotionFactory> MotionFactoryPtr;

}

#endif // UTIL_MOTION_H_