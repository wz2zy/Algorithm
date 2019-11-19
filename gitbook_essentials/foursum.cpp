#include <iostream>
#include <vector>
#include <algorithm>

#define ElementType int

std::vector<std::vector<ElementType>> FourSum(std::vector<ElementType>& nums, int target) {
	std::vector<std::vector<int>> result;

	if (nums.size() < 4)
		return result;

	std::sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size() - 3; ++i) {
		if (i > 0 && nums[i] == nums[i - 1])
			continue;

		for (int j = i + 1; j < nums.size() - 2; ++j) {
			if (j > i + 1 && nums[j] == nums[j - 1])
				continue;

			int k = j + 1;
			int l = nums.size() - 1;

			while (k < l) {
				const int sum = nums[i] + nums[j] + nums[k] + nums[l];
				if (sum < target) {
					++k;
					while (nums[k] == nums[k - 1] && k < l) {
						++k;
					}
				}
				else if (sum > target) {
					--l;
					while (nums[l] == nums[l+1] && k < l) {
						--l;
					}
				}
				else {
					result.push_back({ nums[i], nums[j], nums[k], nums[l] });
					++k;
					--l;
					while (nums[k] == nums[k - 1] && k < l) {
						++k;
					}
					while (nums[j] == nums[j+1] && k < l) {
						--j;
					}
				}
			}
		}
	}
}

int main(void)
{

}