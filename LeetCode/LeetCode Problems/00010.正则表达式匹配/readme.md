#### [10.正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching)

给你一个字符串 `s` 和一个字符规律 `p`，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

**'.' 匹配任意单个字符**
**'*' 匹配零个或多个前面的那一个元素**
所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 . 和 *。



示例 1:

**输入:**
`s = "aa"`
`p = "a"`
**输出**: false
**解释**: "a" 无法匹配 "aa" 整个字符串。



示例 2:

**输入:**
`s = "aa"`
`p = "a*"`
**输出:** true
**解释:** 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。



示例 3:

**输入:**
`s = "ab"`
`p = ".*"`
**输出:** true
**解释:** ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。



示例 4:

**输入:**
`s = "aab"`
`p = "c*a*b"`
**输出:** true
**解释:** 因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。



示例 5:

**输入:**
`s = "mississippi"`
`p = "mis*is*p*."`
**输出:** false



### 思路

​		如果p字符串中没有正则表达式则是简单的字符串匹配，但是加入了两条正则规则，第一条规则为p中含有`'.'`，这条规则还是很好匹配，因为'.'可以匹配任何字符，关键是第二条规则`'*'`，`'*'`表示前面一个字符出现0次或者多次，所以我们需要将`'*'`和它前一个字符当做一个**整体考虑**。

​		如果采用暴力法，每次在p中遇到`某个字符`+`'*'`，将它们作为整体依次尝试`'*'`之前的字符出现0次，1次，2次...，的情况去匹配s串，这样过于复杂。动态规划可以解决很多字符串的问题，如最长公共子序列等，尝试使用动态规划求解。

​		定义状态`dp[i][j]` 表示：s的前i个字符与p的前j个字符是否匹配，`dp[i][j]`为1表示**存在一种匹配方案**，为0表示不匹配。

​		**状态计算**：

- 对于普通字符（小写英文字符）如果$s[i] == p[j]$，并且$dp[i-1][j-1] == 1$，则$dp[i][j] = 1$。

- 如果$p[j] == '.'$，并且$dp[i-1][j-1] == 1$，则$dp[i][j] = 1$。

综合以上两种情况可以将代码写成如下

 ```cpp
  if (i > 0 && p[j] != '*')
  	dp[i][j] = (s[i] == p[j] || dp[i-1][j-1]) && dp[i - 1][j - 1];
	//或者：dp[i][j] = match(s, i, p, j) && dp[i - 1][j - 1]; match见后面说明
 ```

-   如果$p[j] == '\*'$，按照暴力算法的思路，我们需要枚举'*'和其前面的字符出现0次，1次，2次...的情况去匹配s串，所以
  - 当`'*'`和它前面的字符出现0次时：$dp[i][j] = dp[i][j-2]$
  
  - 当`'*'`和它前面的字符出现1次时：$dp[i][j] = (s[i] == p[j-1] || p[j-1] == '.')  and\  dp[i-1][j-2]$
  
  - 当`'*'`和它前面的字符出现2次时：$dp[i][j] = (s[i] == p[j-1] || p[j-1] == '.') \ and\  (s[i-1] == p[j-1] || p[j-1] == '.')\ and\ dp[i-2][j-2]$
  
  - 为了简化表达设：$match(s[i], p[j-1])=(s[i] == p[j-1] || p[j-1] == '.')$，其含义为`s[i]`和`p[j]`相等或者`p[j-1]`为`'.'`，表示`s[i]`和`p[j-1]`匹配。
  
  - 当然`'*'`和它前面的字符还有出现3次，4次...等各种状态，但是现在已经根据上面的推导可以总结规律了，记一下公式为**公式1**：
  $$
   dp[i][j] = dp[i][j-2] \ \ || \ \ dp[i-1][j-2] \ and\  match(s[i],p[j-1])\ \ || \ \ dp[i-2][j-2] \ and\  match(s[i],p[j-1]) \ and\  match(s[i-1],p[j-1])
  $$

- 将上面公式中`i`替换成`i-1`得**公式2**：
  $$
  dp[i-1][j] = dp[i-1][j-2] \ \ || \ \ dp[i-2][j-2] \ and\  match(s[i-1],p[j-1])\ \ || \ \ dp[i-3][j-2] \ and\  match(s[i-1],p[j-1]) \ and\  match(s[i-2],p[j-1])
  $$
  可以发现将公式2**左右两边同时**$\ and\ match(s[i],p[j-1])$，则**等于公式1第2项起后面的部分**

- 所以**最终的公式为**：$dp[i][j] = dp[i][j-2]\ \ ||\ \  dp[i-1][j]\ \  \ and\  \ \ match(s[i],p[j-1])$

代码如下：

```cpp
if (p[j] == '*')
	dp[i][j] = dp[i][j-2] || f[i-1][j] && match(s[i], p[j-1]);//注意判断下标大于0
```



​		最后起始状态为$dp[0][0] = 1$表示两个空串可以匹配。代码如下，细节见注释

```cpp
class Solution {
public:
    bool match(string& s, int i, string& p, int j) {
        if (s[i] == p[j]) return true;
        if (p[j] == '.') return true;
        return false;
    }
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        s = ' ' + s;//前面加上空字符串，因为如果p开头就出现:某个字符+'*'则可以匹配空字符
        p = ' ' + p;
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = 1;//空字符串可以匹配

        for (int i = 0; i <= m; i++) {
            for (int j = 1; j <= n; j++) {//j从1开始，因为任何字符串都不可能和空字符串匹配
                if (j + 1 <= n && p[j + 1] == '*') continue;//*必须和它前一个字母一起使用
                if (i > 0 && p[j] != '*') {//普通字符或者p[j] == '.'
                    dp[i][j] = match(s, i, p, j) && dp[i - 1][j - 1];//s[i] == p[j] && dp[i-1][j-1]
                } else if (p[j] == '*') {
                    dp[i][j] = j-2 >= 0 && dp[i][j-2] || i-1 >= 0 && dp[i-1][j] && match(s, i, p, j - 1);
                }
            }
        }
        return dp[m][n];
    }
};
```

