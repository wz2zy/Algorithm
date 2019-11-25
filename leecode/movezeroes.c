#include <stdio.h>

#define ElementType int

int removeElement(ElementType* nums, int numsSize, ElementType val)
{
	if (numsSize == 0)
		return 0;

	int insert_pos = 0;
	for (int i = 0; i < numsSize; ++i) {
		if (nums[i] != val) 
		{
			nums[insert_pos] = nums[i];
			++insert_pos;
		}
	}

	return insert_pos;
}

int main()
{
	ElementType nums[] = { 3,2,2,3 };
	ElementType val = 3;

	int newlength = removeElement(nums, sizeof(nums) / sizeof(ElementType), val);

	for (int i = 0; i < newlength; ++i) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}