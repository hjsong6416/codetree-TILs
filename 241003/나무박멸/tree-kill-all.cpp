#include <iostream>
using namespace std;

int n;
int m;
int k;
int c;
int map[20][20];
int re_map[20][20];
int calc_map[20][20];
int dead[20][20];

int dy[4] = {1,0,-1,0};
int dx[4] = {0,1,0,-1};

int dy1[4] = {1,1,-1,-1};
int dx1[4] = {1,-1, -1, 1};
int dead_count;

void dump_map() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << calc_map[i][j] << " ";
        }
        cout << "\n";
    }
}

bool is_range(int y, int x) {
    if (y >= 0 && y < n && x >= 0 && x < n) {
        return true;
    } else {
        return false;
    }
}

void tree_set_dead() {
    int max_tree = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (calc_map[i][j] > max_tree) {
                max_tree = calc_map[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dead[i][j] > 0) {
                dead[i][j]--;
            }
        }
    }
    dead_count += max_tree;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            
            if (calc_map[i][j] == max_tree) {
                int ny = 0;
                int nx = 0;
                map[i][j] = 0;
                for (int p = 0; p < 4; p++) {
                    for (int q = 1; q <= k; q++) {
                        ny = i + q * dy1[p];
                        nx = j + q * dx1[p];
                        if (is_range(ny, nx)) {
                            if (map[ny][nx] > 0) {
                                map[ny][nx] = 0;
                                dead[ny][nx] = c;
                            } else {
                                dead[ny][nx] = c;
                                break;
                            }
                        }
                    }
                }
                return;
            }
        }
    }
    
}

void tree_calc_dead() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] > 0) {
                int d_count = 0;
                int ny = 0;
                int nx = 0;
                for (int p = 0; p < 4; p++) {
                    for (int q = 1; q <= k; q++) {
                        ny = i + q * dy1[p];
                        nx = j + q * dx1[p];
                        if (is_range(ny, nx)) {
                            if (map[ny][nx] > 0) {
                                d_count += map[ny][nx];
                            } else {
                                break;
                            }
                        }
                    }
                }
                calc_map[i][j] = map[i][j] + d_count;
            }
        }
    }
}

void tree_dup() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            re_map[i][j] = map[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int t_count = 0;
            int ny;
            int nx;
            if (map[i][j] > 0) {
                for(int k = 0; k < 4; k++) {
                    ny = i + dy[k];
                    nx = j + dx[k];
                    if(is_range(ny, nx)) {
                        if (map[ny][nx] == 0 && dead[i][j] == 0) {
                            t_count++;
                        }
                    }
                }
                for(int k = 0; k < 4; k++) {
                    ny = i + dy[k];
                    nx = j + dx[k];
                    if(is_range(ny, nx)) {
                        if (map[ny][nx] == 0 && dead[i][j] == 0) {
                            re_map[ny][nx] += (map[i][j] / t_count);
                        }
                    }
                }

            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            map[i][j] = re_map[i][j];
        }
    }
}


void tree_grow() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int t_count = 0;
            int ny;
            int nx;
            if (map[i][j] > 0) {
                for(int k = 0; k < 4; k++) {
                    ny = i + dy[k];
                    nx = j + dx[k];
                    if(is_range(ny, nx)) {
                        if (map[ny][nx] > 0) {
                            t_count++;
                        }
                    }
                }
                map[i][j] += t_count;
            }
        }
    }
}

void parse_input() {
    cin >> n >> m >> k >> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> map[i][j];
        }
    }
}

int main() {
    parse_input();
    for (int i = 1; i <= m; i++) {
        tree_grow();
        //dump_map();
        tree_dup();
        //dump_map();
        tree_calc_dead();
        //dump_map();
        tree_set_dead();

        for (int u = 0; u < n; u++) {
            for (int j = 0; j < n; j++) {
                calc_map[u][j] = 0;
            }
        }
    }
    cout << dead_count;

    return 0;
}