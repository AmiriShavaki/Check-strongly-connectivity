#include <iostream>
#include <vector>
#include <cstring> //Using memset

using namespace std;

const int N = 100005;

vector < int > G[N];
int from[N], to[N], cmpCnt = 1, mark[N];
bool mark2[N];

void dfs(int v) {
	mark[v] = cmpCnt;
	for (int i = 0; i < G[v].size(); i++) {
		if (!mark[G[v][i]]) {
			dfs(G[v][i]);
		}
	}
}

bool dfs2(int i, int j) {
	mark2[j] = true;
	bool res = false;
	for (int k = 0; k < G[j].size(); k++) {
		if (G[j][k] == i) {
			return true;
		}
		if (!mark2[G[j][k]]) {
			res |= dfs2(i, G[j][k]);
		}
	}
	return res;
}

void check(int i, int n) {
	for (int j = 0; j < n; j++) {
		if (i == j) {
			continue;
		}
		if (mark[i] == mark[j]) {
			memset(mark2, false, sizeof(mark2));
			if (!dfs2(i, j)) {
				mark[j] = 0;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	int i = 0;
	while (cin >> from[i] >> to[i]) {
		from[i]--;
		to[i]--;
		G[from[i]].push_back(to[i]);
		i++;
	}
	for (int i = 0; i < n; i++) {
		if (!mark[i]) {
			dfs(i);
			check(i, n);
			cmpCnt++;
		}
	}
	cout << cmpCnt - 1;
}
