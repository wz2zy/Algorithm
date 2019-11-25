#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// 超时
//std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
//	std::vector<std::vector<int>> results;
//	
//	std::sort(nums.begin(), nums.end());
//
//	for (int left = 0; left < nums.size() - 2; ++left) {
//		// 去重
//		if (left > 0 && nums[left] == nums[left - 1])
//			continue;
//
//		for (int mid = left + 1; mid < nums.size() - 1; ++mid) {
//			for (int right = mid + 1; right < nums.size();++right) {
//				int sum = nums[left] + nums[mid] + nums[right];
//
//				if (sum < 0) {
//					++right;
//
//					// 去重
//					while (right < nums.size() && nums[right] == nums[right - 1])
//						++right;
//				}
//				else if (sum > 0) {
//					break;
//				}
//				else {
//					results.push_back({ nums[left], nums[mid], nums[right] });
//					break;
//				}
//			}
//		}
//	}
//
//	return results;
//}

//std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
//{
//	std::vector<std::vector<int>> results;
//
//	if (nums.size() < 3)
//		return results;
//
//	std::sort(nums.begin(), nums.end());
//
//	for (size_t left = 0; left < nums.size() - 2; ++left) {
//		// 去重
//		if (left > 0 && left < nums.size() - 2 && nums[left] == nums[left - 1]) {
//			continue;
//		}
//
//		size_t midst = left + 1;
//		size_t right = nums.size() - 1;
//
//		while (midst < right) {
//			int sum = nums[left] + nums[midst] + nums[right];
//
//			if (sum < 0) {
//				++midst;
//
//				// 去重
//				while (midst < right && nums[midst] == nums[midst - 1]) {
//					++midst;
//				}
//			}
//			else if (sum > 0) {
//				// 这个地方考虑下,首先能到达这个地方,premid + right <= 0
//				// case 1: premid + right < 0 =======> premid + right - 1 < 0
//				// case 2: premid + right == 0 ======> 不能
//
//				--right;
//
//				// 去重
//				while (midst < right && nums[right] == nums[right + 1]) {
//					--right;
//				}
//			}
//			else {
//				results.push_back({ nums[left], nums[midst], nums[right] });
//
//				// 去重
//				++midst;
//				while (midst < right && nums[midst] == nums[midst - 1]) {
//					++midst;
//				}
//
//				// 去重
//				--right;
//				while (midst < right && nums[right] == nums[right + 1]) {
//					--right;
//				}
//			}
//		}
//	}
//
//	return results;
//}

// 精进版本
std::vector<std::vector<int>> threeSum(std::vector<int>& nums)
{
	size_t length = nums.size();
	std::vector<std::vector<int>> results;

	if (length < 3)
		return results;

	std::sort(nums.begin(), nums.end());

	for (size_t left = 0; left < length - 2; ++left) {
		// smallest value > 0 Not possible
		if (nums[left] > 0)
			break;
		
		// 去重
		if (left > 0 && left < length - 2 && nums[left] == nums[left - 1])
			continue;

		// 目前最小数大了 木了
		//if (left < length - 2 && (nums[left] + nums[left + 1] + nums[left + 2]) > 0)
		//	break;

		// 最大数不足
		//if (left < length - 2 && (nums[left] + nums[length - 2] + nums[length - 1]) < 0)
		//	continue;

		size_t midst = left + 1;
		size_t right = length - 1;

		while (midst < right) {
			int sum = nums[left] + nums[midst] + nums[right];

			if (sum < 0) {
				++midst;

				// 去重
				//while (midst < right && nums[midst] == nums[midst - 1]) {
				//	++midst;
				//}
			}
			else if (sum > 0) {
				// 这个地方考虑下,首先能到达这个地方,premid + right <= 0
				// case 1: premid + right < 0 =======> premid + right - 1 < 0
				// case 2: premid + right == 0 ======> 不能

				--right;

				// 去重
				//while (midst < right && nums[right] == nums[right + 1]) {
				//	--right;
				//}
			}
			else {
				results.push_back({ nums[left], nums[midst], nums[right] });

				do {
					++midst;
				} while (midst < right && nums[midst] == nums[midst - 1]);

				do {
					--right;
				} while (midst < right && nums[right] == nums[right + 1]);
			}
		}
	}

	return results;
}

int main()
{
	std::vector<int> nums { -1, 0, 1, 2, -1, -4 };

	std::vector<std::vector<int>> results = threeSum(nums);

	for (size_t i = 0; i < results.size(); ++i) {
		for (size_t j = 0; j < results[i].size(); ++j) {
			std::cout << results[i][j] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}