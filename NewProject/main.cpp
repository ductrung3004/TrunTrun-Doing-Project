#include <iostream>
#include <vector>

using namespace std;
int main() {
        vector <int> nums = {-3,-2,-3};
        int res;
        int n = nums.size();
        int max_sum = INT_MIN;
        int min_sum = INT_MAX;
        int array_sum = 0;

        int tmp_max = 0;
        int tmp_min = 0;

        for (int i = 0; i < n; ++i){
            array_sum +=nums[i] ;
            tmp_max += nums[i];
            max_sum = max_sum < tmp_max ? tmp_max : max_sum;
            tmp_max = 0 < tmp_max ? tmp_max : 0;

            tmp_min += nums[i];
            min_sum = min_sum > tmp_min ? tmp_min : min_sum;
            tmp_min = 0 > tmp_min ? tmp_min : 0;

        }
        cout << max(max_sum,(array_sum - min_sum));
}
