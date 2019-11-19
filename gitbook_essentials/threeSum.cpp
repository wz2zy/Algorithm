#include <iostream>

#include <set>
#include <tuple>
#include <vector>
#include <iterator>
#include <algorithm>

#define ElementType int

//int main(void)
//{
//	ElementType target = 0;
//	std::vector<ElementType> nums{ -1,0,1,2,-1,-4 };
//
//	// if (nums.size() < 3)
//	//	return 0;
//
//	// 排序前
//	//std::copy(nums.begin(), nums.end(), std::ostream_iterator<ElementType>(std::cout, " "));
//	//std::cout << std::endl;
//	
//	std::sort(nums.begin(), nums.end());
//	// 排序后
//	//std::copy(nums.begin(), nums.end(), std::ostream_iterator<ElementType>(std::cout, " "));
//	//std::cout << std::endl;
//
//	size_t left = 0;
//	size_t right = nums.size() - 1;
//	
//	std::set<std::tuple<ElementType, ElementType, ElementType>> results;
//
//	// while (left < right)
//	while (left < right - 1)
//	{
//		size_t mid = left + 1;
//		ElementType sum = nums[left] + nums[right];
//
//		while (mid < right && sum + nums[mid] < target)
//		{
//			++mid;
//		}
//
//		if (mid >= right || sum + nums[mid] < target)
//		{
//			// 在此轮 left right 基准中
//			// 最大也不够, 此时应该增加 left
//			++left;
//		}
//		else if (sum + nums[mid] > target)
//		{
//			// 在此轮 left right 基准中
//			// 最小的 {left,mid,right}值没有合适的,此时应该减少right
//			--right;
//		}
//		else if (sum + nums[mid] == target)
//		{
//			results.insert(std::make_tuple(left, mid, right));
//			// 问一下自己为什么需要都增加?
//			// 原因一、在三个数的加法中，2个数已经确定，那么第三个数是唯一的，但是结果不需要有duplicate，且数值是已经排序的 ==》同时增加，减少
//			++left;
//			--right; 
//		}
//	}
//
//	 for (auto tp : results)
//	 {
//	 	 std::cout << "(" << nums[std::get<0>(tp)] << "," << nums[std::get<1>(tp)]  << "," << nums[std::get<2>(tp)] << ")" << std::endl;
//	 }
//
//	return 0;
//}

// 这个方法有好处,但是缺点也很明显，就是IF ELSE 判断太对了，一不小心就越界了，答案都没有考虑到这点=。=
// 可能这种方法比我那种也快不了多少
int main(void)
{
	ElementType target = 0;
	std::vector<ElementType> nums{ -1,0,1,2,-1,-4 };

	// if (nums.size() < 3)
	//	return 0;

	// 排序前
	//std::copy(nums.begin(), nums.end(), std::ostream_iterator<ElementType>(std::cout, " "));
	//std::cout << std::endl;

	std::sort(nums.begin(), nums.end());
	// 排序后
	//std::copy(nums.begin(), nums.end(), std::ostream_iterator<ElementType>(std::cout, " "));
	//std::cout << std::endl;

	std::set<std::tuple<ElementType, ElementType, ElementType>> results;

	for (size_t i = 0; i < results.size() - 2; ++i)
	{
		while (i < results.size() - 2 && i > 0 && nums[i] == nums[i - 1]) {
			++i;
		}

		size_t j = i + 1;
		size_t k = nums.size() - 1;

		while (j < k)
		{
			ElementType sum = nums[i] + nums[j] + nums[k];
			if (sum > target) {
				--k;

				while (j < k && nums[k] == nums[k+1]) {
					--k;
				}
			}
			else if (sum < target) {
				++j;

				while (j < k && nums[j] == nums[j - 1]) {
					++j;
				}
			}
			else {
				results.insert(std::make_tuple(i, j, k));
				--k;
				++j;

				while (j < k && nums[k] == nums[k + 1]) {
					--k;
				}

				while (j < k && nums[j] == nums[j - 1]) {
					++j;
				}
			}
		}
	}

	for (auto tp : results)
	{
		std::cout << "(" << nums[std::get<0>(tp)] << "," << nums[std::get<1>(tp)] << "," << nums[std::get<2>(tp)] << ")" << std::endl;
	}

	return 0;
}