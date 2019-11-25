#include <stdio.h>
#include <stdlib.h>

#define DEBUG_LEVEL 0

// threeSumClosest.c
#define ABS(a) (((a)>0)?(a):(-(a)))

int compare(void *a, void *b) {
	return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int numsSize, int target) {
	int mingap = INT_MAX;
	int closestvalue = INT_MAX;

	if (numsSize < 3)
		return closestvalue;

	qsort(nums, numsSize, sizeof(int), compare);

#if DEBUG_LEVEL
	for (int i = 0; i < numsSize; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
#endif

	for (int left = 0; left < numsSize - 2; ++left) {
		// 如果是负数,是不是更小了
		//if (target > 0 && nums[left] >= target) {
		//	// ERROR 2 手误
		//	int sum = nums[left] + nums[left + 1] + nums[left + 2];
		//	// if (abs(sum - target) < mingap)
		//	if (ABS(sum - target) < mingap)
		//		closestvalue = sum;

		//	break;
		//}

		int midst = left + 1;
		int right = numsSize - 1;

		while (midst < right) {
			int sum = nums[left] + nums[midst] + nums[right];
			// int gap = abs(sum - target);
			int gap = ABS(sum - target);
			if (gap < mingap) {
				mingap = gap;
				closestvalue = sum;
			}

			// ERROR 1 写成了 gap 的比较
			if (sum < target) {
				// 基于 left,mid 的最大的小于 target 的值
				++midst;

				// 去重
				while (midst < right && nums[midst] == nums[midst - 1])
					++midst;
			}
			else if (sum > target) {
				// 基于 left,mid的准上界
				// 仔细思考
				--right;

				// 去重
				while (midst < right && nums[right] == nums[right + 1])
					--right;
			}
			else {
				// 相等的话,就直接返回了
				return target;
			}
		}
	}

	return closestvalue;
}



int main(void)
{
	// int nums[] = { -1,2,1,-4 };
	// int nums[] = { 0,2,1,-3 };
	// int nums[] = { 1,1,-1,-1,3 };
	int nums[] = { 6, -18, -20, -7, -15, 9, 18, 10, 1, -20, -17, -19, -3, -5, -19, 10, 6, -11, 1, -17, -15, 6, 17, -18, -3, 16, 19, -20, -3, -17, -15, -3, 12, 1, -9, 4, 1, 12, -2, 14, 4, -4, 19, -20, 6, 0, -19, 18, 14, 1, -15, -5, 14, 12, -4, 0, -10, 6, 6, -6, 20, -8, -6, 5, 0, 3, 10, 7, -2, 17, 20, 12, 19, -13, -1, 10, -1, 14, 0, 7, -3, 10, 14, 14, 11, 0, -4, -15, -8, 3, 2, -5, 9, 10, 16, -4, -3, -9, -8, -14, 10, 6, 2, -12, -7, -16, -6, 10 };
	int target = 1;

	printf("The sum that closest to the target is %d\n", threeSumClosest(nums, sizeof(nums) / sizeof(int), -52));
}