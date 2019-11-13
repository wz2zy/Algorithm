#include <stdio.h>

#define ElementType int

size_t RemoveDuplicatesFromSortedArray(ElementType elems[], size_t length)
{
	size_t afterremovelength = 0;

	for (size_t i = 1; i < length; ++i) {
		if (elems[i] != elems[afterremovelength]) {
			elems[++afterremovelength] = elems[i];
		}
	}

	return afterremovelength;
}

// 上个版本并没有返回真正的长度,修改一个版本
size_t RemoveDuplicatesFromSortedArrayV2(ElementType elems[], size_t length)
{
	size_t afterremovelength = 1;

	for (size_t i = 1; i < length; ++i) {
		if (elems[i] != elems[afterremovelength - 1]) {
			elems[afterremovelength++] = elems[i];
		}
	}

	return afterremovelength;
}

// 这个版本其实写的不太好看
size_t RemoveDuplicatesFromSortedArrayV3(ElementType elems[], size_t length)
{
	size_t cursor = 0;
	size_t afterremovelength = 1;

	for (size_t i = 1; i < length; ++i) {
		if (elems[i] != elems[cursor]) {
			elems[++cursor] = elems[i];
			++afterremovelength;
		}
	}

	return afterremovelength;
}

// 标准版本
size_t removeduplicates(ElementType elems[], size_t length)
{
	if (length == 0)
		return 0;

	size_t index = 1;
	for (int i = 1; i < length; ++i) {
		if (elems[i] != elems[index - 1])
			elems[index++] = elems[i];
	}

	return index;
}

void main(void)
{
	size_t length = 0;
	// ElementType elems[] = { 1,1,2 };
	ElementType elems[] = { 1,1,2,3,3,3,3,3,3,4,5,5,6,7,8,9,9,9,9,9,9 };

	for (size_t i = 0; i < sizeof(elems) / sizeof(ElementType); ++i) {
		printf("%d ", elems[i]);
	}
	printf("\n");

	length = removeduplicates(elems, sizeof(elems) / sizeof(ElementType));

	for (size_t i = 0; i < length; ++i) {
		printf("%d ", elems[i]);
	}
	printf("\n");
}