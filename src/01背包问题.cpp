#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
#define MAXN 30		//最多物品数
#define MAXW 100	//最大限制重量
//问题表示
int n, W;	//n个数，W容量
int w[MAXN], v[MAXN];	//物品重量和价值
//求解结果表示
int dp[MAXN][MAXW];
int x[MAXN];
int bestp;		//存放最优解的总价值
//用动态规划法求0/1背包问题
void Knap1()
{
	int i, r;
	for (i = 0; i <= n; i++)	//置边界条件dp[i][0] = 0
		dp[i][0] = 0;
	for (r = 0; r <= W; r++)	//置边界条件dp[0][r] = 0
		dp[0][r] = 0;
	for (i = 1; i <= n; i++) {
		for (r = 1; r <= W; r++) {
			if (r < w[i])
				dp[i][r] = dp[i - 1][r];
			else
				dp[i][r] = max(dp[i - 1][r], dp[i - 1][r - w[i]] + v[i]);
		}
	}
}
void Buildx()		//回推求最优解
{
	int i = n, r = W;
	bestp = 0;
	while (i >= 0) {
		if (dp[i][r] != dp[i - 1][r]) {
			x[i] = 1;
			bestp += v[i];
			r = r - w[i];
		}
		else
			x[i] = 0;
		i--;
	}
}
int main() {
	cout << "输入物品个数n:"; cin >> n;
	cout << "输入最大容量W:"; cin >> W;
	cout << "依次输入每个物品的重量w和价值v，用空格分开：";
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}
	Knap1();
	Buildx();
	printf("最优方案\n");
	printf("选取物品为：");
	for (int i = 1; i <= n; i++)
		if (x[i] == 1)
			printf("%d ", i);
	printf("\n");
	printf("总价值=%d\n", bestp);
	return 0;
}

/*
贪心法
struct NodeType
{
	int w;
	int v;
	int p;				//性价比p=v/w
	bool operator<(const NodeType& s)const
	{
		return p > s.p;
	}
};
NodeType A[MAXN];
int maxv;
int x[MAXN];
void Knap2()						//求解背包问题并返回总价值
{
	maxv = 0;					//maxv初始化为0
	int weight = W;				//背包中能装入的余下重量	
	memset(x, 0, sizeof(x));	//初始化x向量
	int i = 1;
	while (A[i].w <= weight)		//物品i能够全部装入背包时，循环
	{
		x[i] = 1;				//装入物品i
		weight -= A[i].w;		//减少背包中能装入的余下重量
		maxv += A[i].v;			//计算装入物品i后的总价值
		i++;
	}
}
void disp_bestx() {
	int sumw = 0;
	cout << "放入购物车的物品序号为：";
	for (int j = 1; j <= n; j++) {
		if (x[j] == 1) {
			cout << j << " ";
			sumw += A[j].w;
		}
	}
	cout << endl;
	cout << "放入购物车的物品最大价值为：" << maxv << "，总重量为：" << sumw << endl;
}
int main()
{
	cout << "输入物品个数n:"; cin >> n;
	cout << "输入购物车容量W:"; cin >> W;
	cout << "依次输入每个物品的重量w和价值v，用空格分开：" << endl;;
	for (int i = 1; i <= n; i++) {
		cin >> A[i].w >> A[i].v;
	}
	for (int i = 1; i <= n; i++) {
		A[i].p = A[i].v / A[i].w;
	}
	sort(A + 1, A + 1 + n);
	Knap2();
	disp_bestx();
	return 0;
}*/

/*回溯法
//求解0/1背包问题
void Backtrack(int t, int tw, int tv, int op[]) 
{
	if (t > n) {		//找到一个叶子结点
		if (tw <= W && tv > bestp) {		//找到一个满足条件的更优解，保存它
			bestp = tv;
			for (int j = 1; j <= n; j++)
				x[j] = op[j];
		}
	}
	else {			//还没搜寻玩所有物品
		if (tw + w[t] <= W) {		//左孩子结点剪枝：满足条件才放入第i个物品
			op[t] = 1;		//选取第i个物品
			Backtrack(t+1,tw+w[t],tv+v[t],op);
		}
		op[t] = 0;		//不选取第i个物品，回溯
		Backtrack(t + 1, tw, tv, op);
	}
}
void disp_bestx() {
	int i;
	int sumw = 0;
	cout << "放入购物车的物品序号为：";
	for (i = 1; i <= n; i++) {
		if (x[i] == 1) {
			cout << i << " ";
			sumw += w[i];
		}
	}
	cout << endl;
	cout << "放入购物车的物品最大价值为：" << bestp << "，总重量为：" << W << endl;
}
int main() {
	cout << "输入物品个数n:"; cin >> n;
	cout << "输入购物车容量W:"; cin >> W;
	cout << "依次输入每个物品的重量w和价值v，用空格分开：";
	for (int i = 1; i <= n; i++) {
		cin >> w[i] >> v[i];
	}
	int op[MAXN];		//存放临时解
	Backtrack(1, 0, 0, op);
	disp_bestx();
	return 0;
}*/


