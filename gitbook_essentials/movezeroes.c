#include <stdio.h>

#define ElementType int

void MoveZeroes(ElementType nums[], size_t length)
{
	size_t ins_pos = 0;

	for (size_t i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	for (size_t idx_pos = 0; idx_pos < length; ++idx_pos) {
		if (nums[idx_pos]) {
			nums[ins_pos++] = nums[idx_pos];
		}
	}

	for (; ins_pos < length; ++ins_pos) {
		nums[ins_pos] = 0;
	}

	for (size_t i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

int main(void)
{
	ElementType nums[] = { 0,2,3,0,5,0,0,0,1,2,1,23,5,6,0 };

	MoveZeroes(nums, sizeof(nums) / sizeof(ElementType));
}