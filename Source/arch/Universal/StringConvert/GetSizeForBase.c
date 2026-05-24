#include <stddef.h>
#include <StringConvert.h>

size_t GetSizeForBase(int Integer, int Division) {
	size_t SafeSize = 0;
	while (Integer > 0) {
		SafeSize++;
		Integer /= Division;
	}
	return SafeSize;
}