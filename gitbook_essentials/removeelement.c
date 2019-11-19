#include <stdio.h>

#define ElementType int

size_t RemoveElement(ElementType nums[], size_t length, ElementType value)
{
	size_t ins_pos = 0;

	for (size_t idx_pos = 0; idx_pos < length; ++idx_pos) {
		if (nums[idx_pos] != value) {
			nums[ins_pos++] = nums[idx_pos];
		}
	}

	return ins_pos;
}

int main(void)
{
	ElementType nums[] = { 1,2,3,4,5,6,7,8,1,1,2,1, };

	for (size_t i = 0; i < sizeof(nums) / sizeof(ElementType); ++i) {
		if (nums[i] != 1)
			printf("%d ", nums[i]);
	}
	printf("\n");

	size_t newlength = RemoveElement(nums, sizeof(nums) / sizeof(ElementType), 1);

	for (size_t i = 0; i < newlength; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}