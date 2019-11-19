#include <stdio.h>

#define ElementType char

// [left, right)
void _do_rotate(ElementType nums[], int left, int right)
{
	--right;

	while (left < right) {
		ElementType temp;
		temp = nums[right];
		nums[right--] = nums[left];
		nums[left++] = temp;
	}
}

void rotate(ElementType nums[], int length, int rotatebit)
{
	// 分成两段,先分别输出
	printf("Step one:====================================================\n");
	for (int i = 0; i < rotatebit; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
	_do_rotate(nums, 0, rotatebit);
	for (int i = 0; i < rotatebit; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
	printf("Step two:====================================================\n");
	for (int i = rotatebit; i < length; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
	_do_rotate(nums, rotatebit, length);
	for (int i = rotatebit; i < length; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
	printf("Step three:====================================================\n");
	for (int i = 0; i < length; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
	_do_rotate(nums, 0, length);
	for (int i = 0; i < length; ++i) {
		printf("%c ", nums[i]);
	}
	printf("\n");
}

int main(void)
{
	ElementType array[] = { 'a','b','c','d','e','f','g','h' };
	rotate(array, sizeof(array) / sizeof(ElementType), 3);
}