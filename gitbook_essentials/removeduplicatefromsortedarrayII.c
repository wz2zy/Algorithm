#include <stdio.h>

#define ElementType int

// Time complexity: O(n), Space Complexity: O(1)

size_t RemoveDuplicatesFromSortedArrayII(ElementType elems[], size_t length)
{
	if (length == 0)
		return;

	// 计数
	size_t count = 0;

	size_t afterremovelength = 1;

	for (size_t i = 1; i < length; ++i) {
		if (elems[afterremovelength - 1] != elems[i]) {
			count = 0;
			elems[afterremovelength++] = elems[i];
		}
		else if (count == 0) {
			++count;
			elems[afterremovelength++] = elems[i];
		}
	}

	return afterremovelength;
}

// 在第一个版本的基础上思考
// 1.2个以下元素的数组是否需要考虑
size_t RemoveDuplicatesFromSortedArrayIIV2(ElementType elems[], size_t length)
{
	if (length <= 2)
		return length;

	size_t offset = 2;
	for (size_t i = 2; i < length; ++i) {
		if (elems[offset - 2] != elems[i]) {
			elems[offset++] = elems[i];
		}
	}

	return offset;
}

// 如果精益求精,上面的代码应该还是能精简的
size_t RemoveDuplicates(ElementType elems[], size_t length)
{
	size_t afterremovelength = 0;

	// Find the first elements 和 the last elements
	for (size_t i = 0; i < length; ++i) {
		// if (i > 0 && i < (length - 1) && elems[i - 1] == elems[i] && elems[i + 1] == elems[i])
		// 改进下表达式
		if (i < (length - 1) && elems[i - 1] == elems[i + 1]) 
			// 所有的中间元素
			continue;

		elems[afterremovelength++] = elems[i];
	}

	return afterremovelength;
}

void main(void)
{
	size_t length = 0;

	// ElementType elems[] = { 1,1,1,2,2,3 };
	ElementType elems[] = { 1,1,1,2,2,3,4,4,4,4,5,5,5,6,7,7,7,8,8,8,9,9 };

	for (size_t i = 0; i < sizeof(elems) / sizeof(ElementType); ++i) {
		printf("%d ", elems[i]);
	}
	printf("\n");

	// length = RemoveDuplicatesFromSortedArrayII(elems, sizeof(elems) / sizeof(ElementType));
	// length = RemoveDuplicatesFromSortedArrayIIV2(elems, sizeof(elems) / sizeof(ElementType));
	length = RemoveDuplicates(elems, sizeof(elems) / sizeof(ElementType));

	for (size_t i = 0; i < length; ++i) {
		printf("%d ", elems[i]);
	}
	printf("\n");
}