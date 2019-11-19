#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define ElementType int

int compare(void *a, void *b)
{
	return *(ElementType*)a - *(ElementType*)b;
}

// 问题的本质: 基于 left 的小于 target 的最大值 和 大于 target 的最小值
ElementType ThreeSumClosest(ElementType nums[], size_t length, ElementType target)
{
	ElementType mingap = INT_MAX;

	for (size_t i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	// Step 1. 先排序
	qsort(nums, length, sizeof(ElementType), compare);


	for (size_t i = 0; i < length; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");

	// Step 2. 左右夹逼 | 用无符号数小心数值越界
	// 此处夹逼需要小心的考虑 ①这是一个已经排序的且2个结点确定 =======> 递增的值，表明这是一个抛物线
	for (int left = 0; left < length - 2; ++left) {
		// 去重
		/*while (left > 0 && left < length - 2 && nums[left] == nums[left - 1])
			++left;*/
		
		int mid   = left + 1;
		int right = length - 1;

		while (mid < right) {
			ElementType sum = nums[left] + nums[mid] + nums[right];

			ElementType gap = abs(sum - target);

			if (gap < mingap)
				mingap = gap;

			// 思考: 一个递增的序列
			// 你看哈: 
			//		IF sum < target THEN mid越大,基于此left,right的gap越小
			//		IF sum >= target THEN 这个一瞬间,gap是所有的基于现在left mid中大于target的gap最小的
			if (sum < target) {
				++mid;
			}
			else {
				--right;
			}
		}
	}

	return mingap;
}

int main()
{
	ElementType nums[] = { -1,2,1,-4 };

	printf("Hello %d", ThreeSumClosest(nums, sizeof(nums) / sizeof(ElementType), 1));
}