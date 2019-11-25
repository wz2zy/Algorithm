#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define DEBUG_LEVEL 1

// ERROR.1 为空数组
// ERROR.2 重复数

//std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
//	std::vector<std::vector<int>> results;
//
//	size_t length = nums.size();
//
//	// 好像小于4进不去
//	if (length < 4)
//		return results;
//	
//	std::sort(nums.begin(), nums.end());
//
//#if DEBUG_LEVEL
//	// 测试输出排序后的值
//	std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
//	std::cout << std::endl;
//#endif
//
//	// [left, mid_left, mid_right, right)
//	for (size_t left = 0; left < length - 3; ++left) {
//		// 去重
//		if (left > 0 && left < length - 3 && nums[left] == nums[left - 1])
//			continue;
//
//		for (size_t mid_left = left + 1; mid_left < length - 2; ++mid_left) {			
//			// 去重
//			if (mid_left > left + 1 && mid_left < length - 2 && nums[mid_left] == nums[mid_left - 1])
//				continue;
//			
//			size_t mid_right = mid_left + 1;
//			size_t right = length - 1;
//
//			// offset
//			int diff = target - nums[left] - nums[mid_left];
//
//			while (mid_right < right) {
//				if (nums[mid_right] + nums[right] < diff) {
//					++mid_right;
//					while (mid_right < right && nums[mid_right] == nums[mid_right - 1])
//						++mid_right;
//				}
//				else if (nums[mid_right] + nums[right] > diff) {
//					--right;
//					while (mid_right < right && nums[right] == nums[right + 1])
//						--right;
//				}
//				else {
//					results.push_back({ nums[left],nums[mid_left],nums[mid_right],nums[right] });
//
//					++mid_right;
//					while (mid_right < right && nums[mid_right] == nums[mid_right - 1])
//						++mid_right;
//
//					--right;
//					while (mid_right < right && nums[right] == nums[right + 1])
//						--right;
//				}
//			}
//		}
//	}
//
//	return results;
//}

// 最快的版本
//std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
//	std::vector<std::vector<int>> total;
//
//	int n = nums.size();
//	if (n < 4)
//		return total;
//
//	std::sort(nums.begin(), nums.end());
//
//	for (int i = 0; i < n - 3; ++i) {
//		if (i > 0 && nums[i] == nums[i - 1])
//			continue;
//		
//		if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
//			break;
//
//		if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
//			continue;
//
//		for (int j = i + 1; j < n - 2; ++j) {
//			if (j > i + 1 && nums[j] == nums[j - 1])
//				continue;
//
//			if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
//				break;
//
//			if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
//				continue;
//
//			int left  = j + 1;
//			int right = n - 1;
//
//			while (left < right) {
//				int sum = nums[i] + nums[j] + nums[left] + nums[right];
//				if (sum < target) {
//					do { ++left; } while (left < right && nums[left] == nums[left - 1]);
//				}
//				else if (sum > target) {
//					do { --right; } while (left < right && nums[right] == nums[right + 1]);
//				}
//				else {
//					total.push_back({ nums[i], nums[j], nums[left], nums[right] });
//					do { ++left; } while (left < right && nums[left] == nums[left - 1]);
//					do { --right; } while (left < right && nums[right] == nums[right + 1]);
//				}
//			}
//		}
//	}
//
//	return total;
//}

// 很通用的版本
//void helper(std::vector<int>& nums, int start, int nsum, int target, std::vector<int> &cur, std::vector<std::vector<int>> &rslt)
//{
//	if (start >= nums.size() || nsum * nums[start] > target || nsum * nums.back() < target)
//		return;
//
//	if (nsum > 2) {
//		for (size_t i = start; i < nums.size(); ++i) {
//			cur.push_back(nums[i]);
//			helper(nums, i + 1, nsum - 1, target - nums[start], cur, rslt);
//			cur.pop_back();
//
//			// 去重
//			while (i + 1 < nums.size() && nums[i] == nums[i + 1])
//				++i;
//		}
//	}
//	else {	// nsum should never be smaller than 2
//		int ll = start, rr = nums.size() - 1;
//		while (ll < rr) {
//			int sum = nums[ll] + nums[rr];
//			if (sum < target) {
//				ll++;
//			}
//			else if (sum > target) {
//				--rr;
//			}
//			else {
//				cur.push_back(nums[ll]);
//				cur.push_back(nums[rr]);
//				
//				rslt.push_back(cur);
//
//				cur.pop_back();
//				cur.pop_back();
//
//				do { ++ll; } while (ll < rr && nums[ll] == nums[ll - 1]);
//				do { --rr; } while (ll < rr && nums[rr] == nums[rr + 1]);
//			}
//		}
//	}
//}

void helper(std::vector<int>& nums, int start, int nsum, int target, std::vector<int> &cur, std::vector<std::vector<int>> &rslt)
{
	if (start > nums.size() - nsum)
		return;

	if (nsum * nums[start] > target)
		return;

	if (nsum * nums.back() < target)
		return;

	if (nsum > 2)
	{
		// 是否需要考虑 MaxI 其实没有必要,但是可以少几圈的循环
		for (int i = start; i < nums.size() - nsum + 1; ++i)
		{
			cur.push_back(nums[i]);
			helper(nums, i + 1, nsum - 1, target - nums[i], cur, rslt);
			cur.pop_back();

			// 去重
			while (i < (nums.size() - 1) && nums[i] == nums[i + 1])
				++i;
		}
	}
	else
	{
		// 左右夹逼
		int ll = start;
		int rr = nums.size() - 1;

		while (ll < rr)
		{
			int sum = nums[ll] + nums[rr];
			if (sum < target) {
				++ll;
			}
			else if (sum > target) {
				--rr;
			}
			else {
				cur.push_back(nums[ll]);
				cur.push_back(nums[rr]);
				
				rslt.push_back(cur);

				cur.pop_back();
				cur.pop_back();

				do { ++ll; } while (ll < rr && nums[ll] == nums[ll - 1]);
				do { --rr; } while (ll < rr && nums[rr] == nums[rr + 1]);
			}
		}
	}
}

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target)
{
	std::vector<int> cur;
	std::vector<std::vector<int>> rslt;

	if (nums.size() < 4)
		return rslt;

	std::sort(nums.begin(), nums.end());

#if DEBUG_LEVEL
	std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
#endif

	helper(nums, 0, 4, target, cur, rslt);

	return rslt;
}

int main()
{
	// std::vector<int> nums{};
	// std::vector<int> nums{ 1,0,-1,0,-2,2 };
	// std::vector<int> nums{ -3,-2,-1,0,0,1,2,3 };
	std::vector<int> nums{ 4, -9, -2, -2, -7, 9, 9, 5, 10, -10, 4, 5, 2, -4, -2, 4, -9, 5 };

	// std::vector<std::vector<int>> results = fourSum(nums, 0);
	std::vector<std::vector<int>> results = fourSum(nums, -13);

	for (size_t i = 0; i < results.size(); ++i) {
		std::copy(results[i].begin(), results[i].end(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << std::endl;
	}
}