
#include "motion_factory.h"

namespace util {

void MotionFactory::Create(MotionConfig config) {

	queued_motions_.push_back(Motion(config));

}

void MotionFactory::Run(void) {
	
	auto item = queued_motions_.begin();

	while(item != queued_motions_.end()) {

		if(item->Step()) {

			item = queued_motions_.erase(item);

		} else {

			++item;

		}

	}

}

bool MotionFactory::Motion::Step(void) {

	auto now = Clock::now();
	auto progress = std::chrono::duration_cast<MotionDuration>(now - start_).count();
	auto expired = progress > config_.duration;

	if(!expired) {

		auto delta = CalculateEase(

			config_.ease,

			(float)progress / config_.duration
		
		);

		config_.callback(delta);
 
	} else {

		if(config_.finish_callback)

			config_.finish_callback();

	}

	return expired;
	
}

static float EaseLinear(float t) {
	return t;
}

static float EaseInQuad(float t) {
	return t * t;
}

static float EaseOutQuad(float t) {
	return t * (2.0f - t);
}

static float EaseInOutQuad(float t) {
	return (t < 0.5f) ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
}

static float EaseOutCubic(float t) { 

	t = t - 1.0f;
	return t * t * t + 1.0f; 
}

static float EaseInOutCubic(float t) { 
	return (t < 0.5f) ? 4.0f * t * t * t : (t - 1.0f) * (2.0f * t - 2.0f) * (2.0f * t - 2.0f) + 1.0f; 
}

static float EaseInQuart(float t) { 
	return t * t * t * t; 
}

static float EaseOutQuart(float t) { 

	t = t - 1.0f;
	return 1.0f - t * t * t * t; 
}

static float EaseInOutQuart(float t) { 

	if(t < 0.5f) {
		return 8.0f * t * t * t * t;

	} else {
		t = t - 1.0f;
		return 1.0f - 8.0f * t * t * t * t;

	}
}

static float EaseInQuint(float t) { 
	return t * t * t * t * t; 
}

static float EaseOutQuint(float t) { 

	t = t - 1.0f;
	return 1.0f + t * t * t * t * t; 
}

static float EaseInOutQuint(float t) { 

	if(t < 0.5f) {
		return 16.0f * t * t * t * t * t;

	} else {
		t = t - 1.0f;
		return 1.0f + 16.0f * t * t * t * t * t;

	}
}

static float EaseInSin(float t) {
	return 1.0f + sinf(M_PI / 2.0f * t - M_PI / 2.0f);
}

static float EaseOutSin(float t) {
	return sinf(M_PI / 2.0f * t);
}

static float EaseInOutSin(float t) {
	return (1.0f + sinf(M_PI * t - M_PI / 2.0f)) / 2.0f;
}

static float EaseInElastic(float t) { 
	return (0.04f - 0.04f / t) * sinf(25.0f * t) + 1.0f;
}

static float EaseOutElastic(float t) {
	return 0.04f * t / (t) * sinf(25.0f * t); 
}

static float EaseInOutElastic(float t) { 
	return (t -= 0.5f) < 0.0f ? (0.01f + 0.01f / t) * sinf(50.0f * t) : (0.02f - 0.01f / t) * sinf(50.0f * t) + 1.0f;
}

float MotionFactory::Motion::CalculateEase(MotionEaseKey key, float progress) {

	switch(key) {

		case kMotionEaseInQuad:
			return EaseInQuad(progress);

		case kMotionEaseOutQuad:
			return EaseOutQuad(progress);

		case kMotionEaseInOutQuad:
			return EaseInOutQuad(progress);

		case kMotionEaseOutCubic:
			return EaseOutCubic(progress);

		case kMotionEaseInOutCubic:
			return EaseInOutCubic(progress);

		case kMotionEaseInQuart:
			return EaseInQuart(progress);

		case kMotionEaseOutQuart:
			return EaseOutQuart(progress);

		case kMotionEaseInOutQuart:
			return EaseInOutQuart(progress);

		case kMotionEaseInQuint:
			return EaseInQuint(progress);

		case kMotionEaseOutQuint:
			return EaseOutQuint(progress);

		case kMotionEaseInOutQuint:
			return EaseInOutQuint(progress);

		case kMotionEaseInSin:
			return EaseInSin(progress);

		case kMotionEaseOutSin:
			return EaseOutSin(progress);

		case kMotionEaseInOutSin:
			return EaseInOutSin(progress);

		case kMotionEaseInElastic:
			return EaseInElastic(progress);

		case kMotionEaseOutElastic:
			return EaseOutElastic(progress);

		case kMotionEaseInOutElastic:
			return EaseInOutElastic(progress);

		default:
			return EaseLinear(progress);
	}

}

} // namespace util