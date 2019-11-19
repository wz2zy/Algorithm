#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define ElementType int

int _do_compare(void *a, void *b)
{
	return *(ElementType*)a - *(ElementType*)b;
}

void FourSum(ElementType nums[], int length, ElementType target)
{
	if (length < 4)
		return;
	
	for (int i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	// 先排序
	qsort(nums, length, sizeof(ElementType), _do_compare);

	for (int i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	for (int left = 0; left < length - 3; ++left) {
		// 去重 [0, length - 3)
		while (left > 0 && left < length - 3 && nums[left] == nums[left - 1]) {
			++left;
		}

		for (int right = length - 1; right > left + 2; --right) {
			// 去重 [3, length - 1)
			while (right > 3 && right < (length - 1) && nums[right] == nums[right + 1]) {
				--right;
			}

			// 此时问题表现为2个数的加法
			int mid_left = left + 1;
			int mid_right = right - 1;

			while (mid_left < mid_right)
			{
				ElementType sum = nums[left] + nums[mid_left] + nums[mid_right] + nums[right];

				if (sum < target) {
					++mid_left;
				}
				else if (sum > target) {
					--mid_right;
				}
				else {
					printf("(%d,%d,%d,%d)\n", nums[left], nums[mid_left], nums[mid_right], nums[right]);
					
					++mid_left;
					--mid_right;
				}
			}
		}
	}
}

int main(void)
{
	ElementType nums[] = { 1,0,-1,0,-2,2 };

	FourSum(nums, sizeof(nums) / sizeof(ElementType), 0);
}