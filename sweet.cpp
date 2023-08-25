/*
 * Author: ZJS
 * Language: C++
 */

#include <iostream>
#include <random>
#include <ctime>
#include <cstring>
#include <queue>

using namespace std;


int mp[50][50];
bool vis[50][50];
int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1}, dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};

int sweet_num, map_x, map_y;

//map_x * map_y的地图
// 地雷数 = sweet_num

bool out_of_map(int x, int y) {
	return !(x >= 1 && x <= map_x && y >= 1 && y <= map_y);
}

void print_map() {
	for (int i = 1; i <= map_x; i++) {
		for (int j = 1; j <= map_y; j++) {
			if (!vis[i][j]) cout << 'x';
			else if (mp[i][j] == -1) cout << '*'; // 未揭开的地雷
			else if (mp[i][j] == 0) cout << ' '; // 周围没雷
			else cout << mp[i][j];
			cout << ' ';
		}
		cout << '\n';
	}
}

int sum = 0;

void work(int x, int y) {
	queue<pair<int, int> > q;
	q.push(make_pair(x, y));
	while (!q.empty()) {
		int ox = q.front().first, oy = q.front().second;
		q.pop();
		for (int i = 0; i < 8; i++) {
			int xx = ox + dx[i], yy = oy + dy[i];
			if (vis[xx][yy] || out_of_map(xx, yy)) continue;
			vis[xx][yy] = 1;
			sum++;
			if (mp[xx][yy] == 0) {
				q.push(make_pair(xx, yy));
			}
		}
	}
}

void print_last_map() {
	for (int i = 1; i <= map_x; i++) {
		for (int j = 1; j <= map_y; j++) {
			if (mp[i][j] == -1) cout << '*';
			else if (mp[i][j] == 0) cout << ' ';
			else cout << mp[i][j];
			cout << ' ';
		}
		cout << '\n';
	}
}

int main() {
	cout << "Hi! Welcome to play my C++ game Sweep!" << '\n';
	cout << "Now, before the game strating, you have the right to decide the number of sweets and the size of map, please enter three numbers above:" << '\n';
	while (1) {
		cout << "The number of sweets (from 5 to 30): ";
		cin >> sweet_num;
		if (!(sweet_num >= 5 && sweet_num <= 30))
			cout << "The sweet_num isn't illegal! Please re-enter another one!" << '\n';
		else break;
	}
	cout << '\n';
	while (1) {
		cout << "The size of map (both length and width are from 5 to 30): ";
		cin >> map_x >> map_y;
		if (!(map_x >= 5 && map_x <= 30 && map_y >= 5 && map_y <= 30)) 
			cout << "The size isn't illegal! Please re-enter another one!" << '\n';
		else break;
	}
	cout << '\n' << "GAME START!" << '\n';
	system("pause");
	system("cls");
	srand(unsigned(time(NULL)));
	memset(mp, 0, sizeof mp);
	for (int i = 1; i <= sweet_num; i++) {
		int x, y;
		do {
			x = rand() % map_x, y = rand() % map_y;
		} while (out_of_map(x, y) || mp[x][y] == -1);
		mp[x][y] = -1;
	}
	for (int i = 1; i <= map_x; i++) {
		for (int j = 1; j <= map_y; j++) {
			if (mp[i][j] != -1) continue;
			for (int k = 0; k < 8; k++) {
				int xx = i + dx[k], yy = j + dy[k];
				if (!out_of_map(xx, yy) && mp[xx][yy] != -1) {
					mp[xx][yy]++;
				}
			}
		}
	}
	while (1) {
		system("cls");
		print_map();
		cout << "Your latest point is " << sum << '\n';
		cout << "Please 2 numbers from 1 to 10 as your choosing coordinate:" << '\n';
		int x, y;
		cin >> x >> y;
		if (out_of_map(x, y)) {
			cout << "The coordinate isn't illegal! Please re-enter!" << '\n';
			system("pause");
			continue;
		}
		if (vis[x][y]) {
			cout << "This coordinate has been chosen! Please re-enter another one!" << '\n';
			system("pause");
			continue;
		}
		if (mp[x][y] == -1) {
			cout << "Here is a mine! Sorry to say that you lose!" << '\n';
			cout << "Your last point sum is " << sum << '\n';
			cout << '\n' << "Press any key to continue to check the whole true map..." << '\n';
			system("pause");
			system("cls");
			print_last_map();
			exit(0);
		}
		sum++;
		vis[x][y] = 1;
		if (mp[x][y] == 0) work(x, y);
		if (sum >= map_x * map_y - sweet_num) {
			system("cls");
			print_map();
			cout << "Your latest point is " << sum << '\n';
			cout << "You win!!!" << '\n';
			cout << '\n' << "Press any key to continue to check the whole true map..." << '\n';
			system("pause");
			system("cls");
			print_last_map();
			exit(0);
		}
	}
	return 0;
}
