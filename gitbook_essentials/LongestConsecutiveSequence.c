#include <stdio.h>
#include <stdbool.h>

#define ElementType int

#define BITSPERWORD 32
#define SHIFT		5
#define MASK		0x1F
#define N			10000000

unsigned int bitmap[1 + N / BITSPERWORD] = { 0 };

void set_bit(unsigned long bit) {
	bitmap[bit >> SHIFT] |=  (1 << (bit & MASK));
}

void clr_bit(unsigned long bit) {
	bitmap[bit >> SHIFT] &= ~(1 << (bit & MASK));
}

bool get_bit(unsigned long bit) {
	return bitmap[bit >> SHIFT] & (1 << (bit & MASK));
}

size_t GetLongestConsecutiveSequence(ElementType nums[], size_t length)
{
	if (length <= 1)
		return length;

	for (size_t i = 0; i < length; ++i) {
		set_bit(nums[i]);
	}

	// 验证写入是否正确
	//for (size_t bit = 0; bit < N; ++bit) {
	//	if (get_bit(bit)) {
	//		printf("%dst bit is been setted...\n", bit);
	//	}
	//}

	size_t curlength = 1;
	size_t maxlength = 0;
	for (size_t bit = 1; bit < N; ++bit) {
		if (get_bit(bit) && get_bit(bit - 1)) {
			++curlength;
		}
		else
		{
			if (curlength > maxlength)
				maxlength = curlength;

			curlength = 1;
		}
	}

	return maxlength;
}

void main(void)
{
	ElementType nums[] = { 100, 4, 200, 1, 3, 2 };

	size_t length = GetLongestConsecutiveSequence(nums, sizeof(nums) / sizeof(ElementType));

	printf("Max consecutive sequence is %d\n", length);
}