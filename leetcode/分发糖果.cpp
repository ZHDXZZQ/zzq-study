// 思路： 动态规划+贪心，时间On，空间O1
// 1. 相邻孩子的评分序列只有三种情况：评分相同、评分更高、评分更低
// 2. 如果评分相同，无需考虑糖果个数，直接给1个
// 3. 如果评分是升高的，则比前一个同学的糖果多1个即可
// 4. 如果评分在递减，则直接给1个，如果前面的同学糖果数和该同学的相同，则给前一个同学也分配一个糖果
// 5. 因此我们可以在遍历时看成是多个递增序列 + 递减序列
// 6. 如果处在递增序列之中，只需要考虑比前一个人多一个糖果即可
// 7. 如果处在递减序列之中，则需要考虑给前面所处递减序列的所有同学多给一颗糖果
// 8. 如果递减序列长度超过了前一个递增序列，则递增序列的最后一个同学的糖果也要多分配一个
// 9. 至此，一定满足题目要求

class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();     //孩子数量
        int res = 1;                //第一个孩子恒定给1颗
        int inc_len = 1, dec_len = 0, cur_cnt = 1;      //分别表示当前所在序列前一个递增序列的长度，当前递减序列长度，当前同学的糖果数
        for(int i = 1; i < n; ++ i) {       //从第二个孩子开始遍历，第一个孩子一定只有1颗糖果
            if(ratings[i] >= ratings[i - 1]) {  //如果处在非递减序列之中
                if(dec_len != 0) {      //如果递减序列长度不为0，则说明刚刚从递减序列进入递增序列，且前一个孩子糖果为1个，因此该孩子算作递增序列的第二个孩子
                    inc_len = 1;        //所以初始化置已经有一个孩子在递增序列中
                }
                dec_len = 0;        //递减序列长度置0
                if(ratings[i] == ratings[i - 1]) {      //如果该孩子和前一个孩子分数相同
                    cur_cnt = 1;                //则直接给1个糖果即可
                    inc_len = 0;                //并且置递增序列长度为0，该孩子算作可能的递增序列的第一个孩子
                } else {
                    cur_cnt += 1;   //否则的话严格递增，当前孩子的糖果数只需要比前一个同学多一个
                }
                res += cur_cnt;     //结果加上给当前同学的糖果数
                ++ inc_len;         //递增序列长度 + 1
            } else {                //如果处在递减序列中
                ++ dec_len;         //递减序列长度 + 1
                if(dec_len == inc_len) {    //如果某个孩子进入递减序列后，递增序列长度和递减序列长度相等
                    ++ dec_len;             //把递增序列的最后一个孩子算到递减序列中，因为每再增加一个递减序列的同学，就需要给其多一个糖果
                }
                res += dec_len;     //递减序列的孩子每多1个，就需要给所有递减序列中的孩子都多发一个糖果，包含当前同学
                cur_cnt = 1;        //作为递减序列的当前最后一个同学，只需要给1颗糖果
            }
        }
        return res;
    }
};