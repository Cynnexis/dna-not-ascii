#include "util.hpp"

unsigned long epochMs() {
	struct timespec spec;
	clock_gettime(CLOCK_REALTIME, &spec);
	return spec.tv_sec * 1000L + (spec.tv_nsec / 1.0e6);
}
