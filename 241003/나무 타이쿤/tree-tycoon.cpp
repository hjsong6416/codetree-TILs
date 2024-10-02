#include <iostream>
using namespace std;

int n;
int m;
int d;  //방향
int p;  //이동

int map[15][15];
int med[15][15];
int med_r[15][15];
int wait_q[15][3];
int rule[100][2]; // 0: 방향, 1: 이동 칸
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dx1[4] = {-1, 1, 1, -1};
int dy1[4] = {-1, -1, 1, 1};

int wait_index = 0;

void dump() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << map[i][j] << " ";
            
        }
        cout << "\n";
    }
    cout << "\n";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
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
                if (med[i][j] == -1) {
                    
                } else {
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
                //med[i][j] = 3;
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
                    if ((ny >= 0) && (ny <= (n-1)) && (nx >=0) && (nx <= (n-1))) {
                        if (map[ny][nx] >= 1) {
                            count++;
                        }
                    } else {
                        continue;
                    }
                }
                wait_q[wait_index][0] = i;
                wait_q[wait_index][1] = j;
                wait_q[wait_index][2] = count;
                wait_index++;

                med[i][j] = -1;
            }
        }
    }
    for (int i = 0; i <= wait_index; i++) {
        map[wait_q[i][0]][wait_q[i][1]] += wait_q[i][2];
        wait_q[i][0] = 0;
        wait_q[i][1] = 0;
        wait_q[i][2] = 0;


    }
    wait_index = 0;
    

}

void move_med(int seq) {
    int nx;
    int ny;
    d = rule[seq-1][0];
    p = rule[seq-1][1];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            med_r[i][j] = 0;    
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (med[i][j] == 1) {
                
                ny = i + p * dy[d-1] + n*p;
                nx = j + p * dx[d-1] + n*p;
            
                nx = nx % n;  
                ny = ny % n; 
                    
                
                med_r[ny][nx] = 2;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            med[i][j] = med_r[i][j];   
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