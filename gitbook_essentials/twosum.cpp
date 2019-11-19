#include <iostream>
#include <vector>
#include <unordered_map>

template <typename T>
std::vector<std::pair<size_t, size_t>> GetTwoNumAddUpEqualTheTarget(std::vector<T>& nums, T target)
{
	std::unordered_map<T, size_t> hashmap;
	std::vector<std::pair<size_t, size_t>> result;
	
	for (size_t i = 0; i < nums.size(); ++i) {
		hashmap[nums[i]] = i;
	}

	// 使用[]会有问题哦，这个地方使用at,使用try.catch来捕获这个元素
	//for (auto keyval : hashmap) {
	//	try
	//	{
	//		if (hashmap.at(target - keyval.first)) {
	//			result.push_back(std::make_pair(keyval.second, hashmap[target - keyval.first]));
	//			// result.push_back({ keyval.second, hashmap[target - keyval.first] });
	//			hashmap.erase(target - keyval.first);
	//		}
	//	}
	//	catch (std::out_of_range)
	//	{
	//		std::cout << keyval.first << "continue..." << std::endl;
	//	}
	//}

	// 此处使用 count() 来处理
	//for (auto keyval : hashmap) {
	//	if (hashmap.count(target - keyval.first)) {
	//		result.push_back(std::make_pair(keyval.second, hashmap[target - keyval.first]));
	//		// result.push_back({ keyval.second, hashmap[target - keyval.first] });
	//		hashmap.erase(target - keyval.first);
	//	}
	//}


	// 此处使用 find() 来处理
	for (auto keyval : hashmap) {
		auto iter = hashmap.find(target - keyval.first);

		if (iter != hashmap.end() && keyval.first < target - keyval.first) {
			result.push_back(std::make_pair(keyval.second, hashmap[target - keyval.first]));
			// result.push_back({ keyval.second, hashmap[target - keyval.first] });
			hashmap.erase(iter);
		}
	}

	return result;
}

int main(void)
{
	std::vector<int> nums { 2,7,11,15 };

	auto result = GetTwoNumAddUpEqualTheTarget(nums, 9);

	for (auto res : result) {
		std::cout << res.first << ", " << res.second << "| " << nums[res.first] << "," << nums[res.second] << std::endl;
	}

	return 0;
}