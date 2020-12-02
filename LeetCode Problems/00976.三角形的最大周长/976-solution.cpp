//标签：排序，贪心，数学

//首先时间复杂度提示，只能使用时间复杂度为nlogn的算法，联想到排序
//首先由三角形的构成规则：任意两边之和大于第三边，设三条边分别是a, b, c，则应该有
//a + b > c; a + c > b; b + c > a
//又因为要让我们求最大的周长，我们所选择的边长应该尽可能的大，所以首先，我们先对边长从大到小排序
//选择数组前三条边分别为a, b, c，且有a > b > c, 如果不能构成三角形，则至少违背了以下三条规则中的一条
//a + b < c; a + c < b; b + c < a; 又因为我们选择的边长一定保证a > b > c;故前两条规则一定满足，
//所以只需要考虑是否违背b + c < a，如果未违背这条规则，则答案即为a + b + c; 如果违背了这条规则，则
//只能减小a来使得规则满足，又因为a, b, c在数组中是连续的一段，故a减小后，不能重复使用边，故b, c也应该减小

//所以本题的解法为：【从大到小对变长排序，枚举连续的三条边a, b, c; 检查是否满足规则b + c > a；满足则返回边长，
//否则a减小，继续枚举】

//时间复杂度O(nlogn)，空间复杂度O(logn)
class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        int n = A.size();
        sort(A.begin(), A.end(), [](int a, int b) {//时间复杂度O(nlogn)
            return a > b;
        });
        for (int i = 0; i <= n - 3; i++) {//时间复杂度O(n)
            int a = A[i], b = A[i + 1], c = A[i + 2];
            if (b + c > a) return a + b + c;
        }
        return 0;
    }
};