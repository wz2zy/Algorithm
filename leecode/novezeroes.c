#include <stdio.h>

#define ElementType int

// remove Element 的翻版
void moveZeroes(ElementType* nums, int numsSize)
{
	int ins_pos = 0;
	for (int i = 0; i < numsSize; ++i) {
		int elem = nums[i];
		if (elem)
		{
			nums[ins_pos] = elem;
			++ins_pos;
		}
	}

	for (int i = ins_pos; i < numsSize; ++i) {
		nums[i] = 0;
	}
}

int main()
{
	ElementType nums[] = { 0,1,0,3,12 };
	int length = sizeof(nums) / sizeof(ElementType);

	moveZeroes(nums, length);

	for (int i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}