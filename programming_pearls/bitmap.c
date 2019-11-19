#include <stdio.h>
#include <math.h>
#include <limits.h>

// 位图

// 位长
#define BITSPERWORD 32
// 数组长度
#define N			1
// MASK
#define MASK		0x1F
// SHIFT
#define SHIFT		5

int bitmap[N] = { 0 };

// 设置标志位
void set_bit(size_t bit) { bitmap[bit >> SHIFT] |= 1 << (bit & MASK); }
// 清除标志位
void clr_bit(size_t bit) { bitmap[bit >> SHIFT] &= ~(1 << (bit & MASK)); }
// 获取标志位
int get_bit(size_t bit) { return bitmap[bit >> SHIFT] & 1 << (bit & MASK); }

int main(void)
{
	int max_value = INT_MIN;
	int nums[] = { 1,2,5,7,9,1,32,35,33,64,128,157 };

	int length = sizeof(nums) / sizeof(int);
	
	// 取出最大值
	for (int i = 0; i < length; ++i) {
		if (nums[i] > max_value)
			max_value = nums[i];
	}

	// 计算需要多少轮
	int round = ceil((double)(max_value) / (BITSPERWORD * N));

	for (int cnt = 0; cnt < round; ++cnt) {
		// [start, end)
		int start = cnt * BITSPERWORD * N;
		int end = (cnt + 1) * BITSPERWORD * N;
		printf("Step %d==============[%d,%d)=========================\n", cnt + 1, start, end);
		for (int i = 0; i < length; ++i) {
			if (nums[i] >= start && nums[i] < end) {
				set_bit(nums[i] - start);
			}
		}

		for (int i = 0; i < BITSPERWORD * N; ++i) {
			if (get_bit(i)) {
				printf("%d been setted...\n", i + start);
			}
			clr_bit(i);
		}
	}
}