#include <iostream>
using namespace std;

int n;
int m;
int d;  //방향
int p;  //이동

int map[15][15];
int med[15][15];
int rule[100][2]; // 0: 방향, 1: 이동 칸
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx1[4] = {-1, 1, 1, -1};
int dy1[4] = {-1, -1, 1, 1};


void dump() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << map[i][j] << " ";
            
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "\n";
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            cout << med[i][j] << " ";
            
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "\n";

}

void cut_tree_n_add_med() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] >= 2) {
                if (med[i][j] != -1) {
                    map[i][j] -= 2;
                    med[i][j] = 1;
                }
            }
            if (med[i][j] == -1) {
                med[i][j] = 0;
            }
        }
    }
}

void insert_med() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (med[i][j] == 2) {
                map[i][j]++;
                //med[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (med[i][j] == 2) {
                int count = 0;
                int ny = 0;
                int nx = 0;
                for (int k = 0; k < 4; k++) {
                    ny = i + dy1[k];
                    nx = j + dx1[k];
                    if (ny >= 0 && ny <= n-1 && nx >=0 && nx <= n-1) {
                        if (map[ny][nx] >= 1) {
                            count++;
                        }
                    } else {
                        continue;
                    }
                }
                map[i][j] += count;
                med[i][j] = -1;
            }
        }
    }

}

void move_med(int seq) {
    int nx;
    int ny;
    d = rule[seq-1][0];
    p = rule[seq-1][1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (med[i][j] == 1) {
                
                ny = i + p * dy[d-1];
                nx = j + p * dx[d-1];
                if ((0 <= nx) && (nx <= n-1)) {
                    //
                } else {
                    
                    nx = nx % n; 
                }
                if ((0 <= ny) && (ny <= n-1)) {
                    //
                } else {
                    ny = ny % n; 
                }
                med[i][j] = 0;
                med[ny][nx] = 2;
            }
        }
    }
    
}

void first_set_med() {
    med[n-1][0] = 1;
    med[n-1][1] = 1;
    med[n-2][0] = 1;
    med[n-2][1] = 1;
}

void parse_input() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> rule[i][0] >> rule[i][1];
    }
}


int main() {
    int result = 0;
    parse_input();
    first_set_med();
    //dump();
    for (int i = 1; i <= m; i++) {
        move_med(i);
        //dump();
        insert_med();
        //dump();
        cut_tree_n_add_med();
        //dump();
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result += map[i][j];
        }
    }
    cout << result;
    return 0;
}