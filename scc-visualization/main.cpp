#pragma warning(disable:4996)
#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

const int MAX = 10020;

const string kCOLOR[] = {
    "blueviolet",
    "chocolate",
    "cyan",
    "darkgreen",
    "darkorange",
    "firebrick",
    "lawngreen",
    "gold",
    "maroon",
    "darkkhaki",
    "salmon",
    "dimgrey"
};
// http://graphviz.org/doc/info/colors.html

int V, E;
vector < int > front[MAX], rev[MAX];

int visited[MAX], stk[MAX], top;
vector<vector<int> > sccGroup;

void input() {
	printf("정점의 개수 : ");
	scanf("%d", &V);
	printf("간선의 개수 : ");
	scanf("%d", &E);

	// 그래프 초기화
	printf("두 정점의 번호를 입력\n");
	for (int i = 0; i < E; i++) {
		int f, s;
		printf("남은 입력 횟수 %d번\t : ", E - i);
		scanf("%d%d", &f, &s);
		front[f].push_back(s);
		rev[s].push_back(f);
	}
}


void front_dfs(int node) {
	visited[node] = 1;
	for (auto next : front[node]) {
		if (!visited[next]) {
			front_dfs(next);
		}
	}
	// DFS를 빠져 나올 때 스택에 쌓음
	stk[top++] = node;
}

void rev_dfs(int node) {
	visited[node] = 1;
	// 마지막 그룹에 정점 추가
	sccGroup[sccGroup.size() - 1].push_back(node);
	for (auto next : rev[node]) {
		if (!visited[next]) {
			rev_dfs(next);
		}
	}
}

void solve() {
	// 위상 정렬
	for (int v = 1; v <= V; v++) {
		if (!visited[v]) {
			front_dfs(v);
		}
	}

	// 그룹 묶기
	memset(visited, 0, sizeof(visited));
	while (top) {
		int node = stk[top - 1];
		top--;
		if (!visited[node]) {
			// 빈 그룹 추가
			sccGroup.push_back(vector<int>());
			rev_dfs(node);
		}
	}

	// 문제 요구 조건대로 정렬
	for (auto &vec : sccGroup)
		sort(vec.begin(), vec.end());
	sort(sccGroup.begin(), sccGroup.end());

	printf("\n\n");
	// 출력
	printf("강한 연결 요소의 개수 : %d개\n", sccGroup.size());
	for (auto &vec : sccGroup) {
		static int num = 1;
		printf("[%d 그룹] : ", num++);
		for (auto elem : vec) {
			printf("%2d ", elem);
		}
		printf("\n");
		//puts("-1");
	}
}

int main() {
	input();
	solve();
	
	// 원본 그래프 출력하는 코드
	string input_text = "digraph {\n";
	int colorNumber = 0;
	for (const auto &vec : sccGroup) {
		for (auto elem : vec) {
			input_text += "\t" + to_string(elem)
				+ "[color=" + kCOLOR[colorNumber] + "];\n";
		}
		colorNumber++;
	}
	printf("\n\n");

	printf("정점을 향하는 간선의 방향\n");
	for (int i = 0; i <= E; i++) {
		if (!front[i].empty()) {
			sort(front[i].begin(), front[i].end());
			for (auto t = front[i].begin(); t != front[i].end(); ++t) {
				printf("%2d -> %2d, ", i, *t);
				input_text += "\t" + to_string(i) + "->" + to_string(*t) + ";\n";
			}
			printf("\n");
		}
	}
	input_text += "}";

	ofstream out("../output/graph_file.dot", ios::binary);
	if (out.is_open()) {
		out << input_text;
	}
	out.close();

	system("..\\graphviz-lib\\bin\\neato -Tpng ../output/graph_file.dot -o ../output/graph_print.png");
    system("pause");
	return 0;
}


/*
10
15
1 3
2 1
3 2
4 7
5 4
6 5
6 8
7 3
7 6
8 3
8 7
9 5
10 6
10 8
10 9
*/

/*
교재
10
15
1 2
2 3
3 1
3 8
3 7
8 10
8 6
6 7
7 8
7 4
4 5
5 6
5 9
9 10
6 10


*/


/*
교재
10
15
1 2
1 5
2 3
3 4
4 2
5 2
5 6
6 1
6 7
7 8
8 5
9 1
9 6
9 10
10 7
*/



/*

15
18
1 15
2 3
2 5
2 7
2 14
4 5
5 3
5 6
5 14
7 8
8 9
8 12
8 14
9 10
9 13
10 11
14 15
15 2

*/



/*

15
19
1 15
2 3
2 5
2 7
2 14
4 5
5 3
5 6
5 14
7 8
8 9
8 12
8 14
9 10
9 13
10 11
11 9
14 15
15 2

*/



/*
2017년 11월 27일 오전 12시 07분 테스트 케이스

12
17
2 3
2 5
2 12
4 5
5 6
1 12
1 11
11 4
5 12
5 11
6 4
7 8
9 2
8 6
6 7
2 10
6 10

*/