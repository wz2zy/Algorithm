#include <stdio.h>
#include <stdlib.h>

#define ElementType int

// 稍微修改下，仅仅选择相加等于target的值，不返回下标

int compare(const void* a, const void* b)
{
	return *(ElementType*)a - *(ElementType*)b;
}

int main(void)
{
	ElementType target = 9;
	ElementType nums[] = { 2,7,3,6,5,7,11,15,-8,-6 };

	for (size_t i = 0; i < sizeof(nums) / sizeof(ElementType); ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	// 先排序
	qsort(nums, sizeof(nums) / sizeof(ElementType), sizeof(ElementType), compare);

	for (size_t i = 0; i < sizeof(nums) / sizeof(ElementType); ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	size_t i = 0;
	size_t j = sizeof(nums) / sizeof(ElementType) - 1;

	while (i < j)
	{
		ElementType sum = nums[i] + nums[j];

		if (sum == target) {
			printf("%d,%d\n", nums[i], nums[j]);
			// 如果有重复元素,怎么处理
			// ++i;

			if (nums[i] == nums[i + 1]) {
				++i;
			}
			else if (nums[j] == nums[j - 1]) {
				--j;
			}
			else {
				++i;
				--j;
			}
		}
		else if (sum > target) {
			--j;
		}
		else {
			++i;
		}
	}
}