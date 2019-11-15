#include <iostream>
#include <set>
#include <iterator>

// Longest Consecutive Sequence

#define ElementType int

size_t GetLongestConsecutiveSequence(ElementType nums[], size_t length)
{
	if (length <= 1)
		return length;
	
	std::set<ElementType> set;

	for (size_t i = 0; i < length; ++i) {
		set.insert(nums[i]);
	}

	size_t lengthest = 0;

	for (ElementType num : set) {
		size_t length = 1;

		for (ElementType preNum = num - 1; set.find(preNum) != set.end(); --preNum) {
			// 向前找
			set.erase(preNum);
			++length;
		}

		for (ElementType nextNum = num + 1; set.find(nextNum) != set.end(); ++nextNum) {
			// 向后找
			set.erase(nextNum);
			++length;
		}

		lengthest = lengthest >= length ? lengthest : length;
	}

	return lengthest;
}

void main(void)
{
	size_t length = 0;

	// ElementType nums[] = { 1,1,1,2,2,3 };
	// ElementType nums[] = { 1,1,1,2,2,3,4,4,4,4,5,5,5,6,7,7,7,8,8,8,9,9 };
	ElementType nums[] = { 100,4,200,1,3,2 };

	size_t lengthest = GetLongestConsecutiveSequence(nums, sizeof(nums) / sizeof(ElementType));

	printf("lengthest = %d", lengthest);
}