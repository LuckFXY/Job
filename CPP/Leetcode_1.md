
学习网址 https://blog.csdn.net/haolexiao/article/details/53487436
作者 CSDN 哈乐笑
#179. Largest Number 

Given a list of non negative integers, arrange them such that they form the largest number.

**Example 1:**

```
Input: [10,2]
Output: "210"
```

**Example 2:**

```
Input: [3,30,34,5,9]
Output: "9534330"
```

**Note:** The result may be very large, so you need to return a string instead of an integer.

23 放在 2前，但是 21, 放在2后。 345 放在 45后，但是 344 放在 34 前。·····写了一晚上，全错。


上面分类讨论的目的无非是决定a,b 的顺序。所以直接将 a,b 合并为 ab 和 ba 再比较会简单的多。

```
sort(begin(arr), end(arr), [](string &s1, string &s2){ return s1+s2>s2+s1; });
```

```cpp
string largestNumber(vector<int> &num) {
    vector<string> arr;
    for(auto i:num)
        arr.push_back(to_string(i));
    sort(begin(arr), end(arr), [](string &s1, string &s2){ return s1+s2>s2+s1; });
    string res;
    for(auto s:arr)
        res+=s;
    while(res[0]=='0' && res.length()>1)
        res.erase(0,1);
    return  res;
}
```

# 48. Rotate Image 

You are given an *n* x *n* 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

**Note:**

You have to rotate the image [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm), which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

**Example 1:**

```
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
```
上下反转，对角反转，原地右旋90度。



```cpp
void rotate(vector<vector<int>>& matrix) {
        if(!matrix.empty()){
            int m = matrix.size(), n = matrix[0].size();
            int tmp;
            for(int i=0; i<m/2; i++){
                for(int j=0; j<n; j++){
                    tmp = matrixn-1-i;
                    matrixn-1-i = matrixi;
                    matrixi = tmp;
                }
            }
            for(int i=0; i<m; i++){
                for(int j=i+1; j<n; j++){
                    if(i!=j){
                        tmp = matrixi;
                        matrixi = matrixj;
                        matrixj = tmp;
                }
            }
        }
    }
}
```
#  [231.Power of Two](https://leetcode.com/problems/power-of-two/) 

判断一个数是不是2的指数

1. 考虑 负数 和零
2. 一个数的二进制表示中最后一个1在 i 处。这个数减一后 i 处的1被低位借位（最后一位直接为0）而成为零。若以 i 为分界线，n 和 n-1 只有 i 之后的部分不同（包括i），其中 n 在 i 位后全0 ，所以 n & (n-1) i 后全为0，i之前全部相同，只有 i 处 0.   n & (n-1)  的操作相当于 i 位被置零，既最后一个1被置零。
3. 若这个数为2的次幂，二进制表示中只有一个1， n&(n-1) == 0

```
bool isPowerOfTwo(int n) {        
     return n > 0 && !(n&(n-1));    
}
```



# [456.132 Pattern](https://leetcode.com/problems/132-pattern/)  

Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence a**i**, a**j**, a**k** such that **i** < **j** < **k** and a**i** < a**k** < a**j**. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

**Note:** n will be less than 15,000.

**Example 1:**

```
Input: [1, 2, 3, 4]

Output: False

Explanation: There is no 132 pattern in the sequence.
```

**Example 2:**

```
Input: [3, 1, 4, 2]

Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].
```

这道题是让找出是否有符合132这种模式的数 。这是简化版的最长升序问题，现找从后向前找最大值 b , 然后b 左边的最大值为c, 此时只需从 b 左边找一个值 a 满足 a< c 即可。用priority_queue（greater版） 保存 s2 记录b的候选值。一旦新的值 x 大于s2的堆顶，说明出现逆序元素。此时弹出 s2 中小于等于 x 值作为 c 的候选值。由于 c 只需要一个元素，这个元素为b后边 小于 b 的元素中最大值。此时一旦新元素 x < c 说明存在 a<c<b的情况返回true.

```cpp
bool find132pattern(vector<int>& nums) {
    if(nums.size()<3) return false;
    priority_queue<int, vector<int>,greater<int>> s2;
    int c = 0x80000000;
    int cur, n = nums.size();

    for(int i=n-1; i>=0; i--){
        cur = nums[i];
        if(s2.empty() || cur < s2.top()){
            s2.push(cur);
        }
        else{
            while(!s2.empty() && s2.top() <= cur){
                if(s2.top() != cur && s2.top() > c)
                    c = s2.top();
                s2.pop();
            }
            s2.push(cur);
        }
        if(cur < c)
            return true;
    }
    return false;
}
```

# [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/)  

分析：

如果能分成两个和相等的集合，sum(nums)一定是偶数。设每一组的和为 S

设置一个长度为 S+1的数组dp，用于下标保存可能的和， 0表示初始状态，1表示该下标为可能的和。

每遇见一个数字，都让这个数字与dp 中不为零的位置的下标相加得到新的可能的和，并在dp对应位置标记。

一旦dp中位置S被标记，则nums可以被分为两个和相同的子集合。

```cpp
bool canPartition(vector<int>& nums) {
        long tmp, sum=0;
        for(int num: nums){
            sum += num;
        }
        if(sum & 1 == 1) return false;
        sum /=2;

        vector<bool> dp(sum+1);
        dp[0]=true;
        for(int num: nums){
            cout<<num<<endl;
            //dp[num] = true;
            for(int i=sum; i>=0; i-- ){
                if(dp[i]){
                    tmp = i + num;
                    if(tmp == sum)
                        return true;
                    else if(tmp < sum)
                        dp[tmp] = true;
                    
                }

            }
        }
        return false;
    }
```



# [410. Split Array Largest Sum](https://leetcode.com/problems/split-array-largest-sum/)  

Given an array which consists of non-negative integers and an integer *m*, you can split the array into *m* non-empty continuous subarrays. Write an algorithm to minimize the largest sum among these *m* subarrays.

**Note:**
If *n* is the length of array, assume the following constraints are satisfied:

- 1 ≤ *n* ≤ 1000
- 1 ≤ *m* ≤ min(50, *n*)

**Examples:**

```
Input:
nums = [7,2,5,10,8]
m = 2

Output:
18

Explanation:
There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8],
where the largest sum among the two subarrays is only 18.
```

分析

leetcode [dax1ng](https://leetcode.com/dax1ng) 二分搜索的思路

1. 答案一定在max(nums) 与 sum(nums) 之间. left = max(nums), right = sum(nums)

2. 二分搜索

      mid = (left + right) >> 1

3. 贪心算法

   1. 由于分割后的子序列连续，所以只需要从左到右扫描就可以了
   2. 尝试将序列分割为m组，并且每一组的和都小于等于 mid
      1. 组数小于m。 mid太大了 缩小一点
      2. 组数等于m， 为了最小化mid ,尝试缩小它
      3. 组数大于m, mid 太小了，放大一点。

4. 注意事项（边界条件累死人）

   1. 由于每组之和小于等于mid , 且组数等于m，所以当找到符合条件的mid时，此时执行缩小m，既将right右移，由于mid可能是答案，所以 right左移到 mid 就行，而不是常见的 mid-1

      这就相当于 100 50 25 每次搜索范围是左边的闭区间。

   2. 当 left = k, right=k+1时候。

      1. 若答案为k 则 mid = k, right左移至k while结束
      2. 若答案为k+1， 则 mid = k, left 右移至 mid+1, 既 k+1 结束

```cpp
bool valid(const vector<int>& nums, const int target, int m){
    int sum=0;
    for(int num : nums){
        sum += num;
        if(sum > target){
            sum = num;
            m -=1;
            if(m<1)
                return false;
        }

    }
    return true;
}

int splitArray(vector<int>& nums, int m) {
    int total=0, max_one=0;

    for(int i=0;i<nums.size(); i++){
        total += nums[i];
        max_one = nums[i] > max_one ? nums[i] : max_one;
    }
    if(m==1)
        return total;
    int left = max_one, right = total;
    int mid = (left + right) >>1;
    int v;
    while(left < right){
        mid = (left + right) >>1;
        if(valid(nums, mid, m))
            right = mid;
        else
            left = mid + 1;
    }
    return left;
}
```

## 大神的动态规划

```cpp
dp[i][count][sum] = max{ dp[i-1][count-1][sum-a[i]] , dp[i-1][count][sum] }; 
```

# 合并重复区间

```
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
typedef vector<Interval>::iterator iter_type;

static bool compare(const Interval &src, const Interval &dst){
    return src.end > dst.end;
}
int eraseOverlapIntervals(vector<Interval>& intervals) {
    if(intervals.size() == 0)
        return 0;
    sort(intervals.begin(), intervals.end(), compare);
    vector<iter_type> iter_vec;
    int big = intervals.front().end + 1;
    Interval* last = new Interval(big, big);
    for(auto it = intervals.begin(); it != intervals.end(); it++){
        if( (*it).end <= (*last).start ){
            iter_vec.emplace_back(it);
            last = &(*it);
        }
        else if((*it).start > (*last).start){
            (*last).start =(*it).start;
        }
    }

    return intervals.size() - iter_vec.size();
}
```

