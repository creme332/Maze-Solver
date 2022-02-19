#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

vector <vector<char>> m = {
    {'.','W','.','.','.','W','.','.','.'},
    {'.','.','.','W','.','W','.','W','.'},
    {'.','.','.','W','W','W','.','.','.'},
    {'.','W','.','.','.','W','.','W','.'},
    {'W','.','.','W','W','.','.','.','.'},
    {'.','W','.','.','W','.','.','W','.'},
    {'.','.','.','W','.','.','W','.','.'},
    {'W','.','.','.','.','W','.','.','.'},
    {'.','.','.','W','.','.','.','W','.'},
};

map <pair<int, int>, bool> explored; //stores coordinates already explored

string color(string a) { //color character a 
    if (a == "o")return "\x1B[33m0\033[0m"; //yellow character and trail
    if (a == "t")return "\x1B[33mo\033[0m"; //yellow trail
    if (a == "W")return "\x1B[31mW\033[0m"; //red walls
    return "\x1B[92m" + a + "\033[0m"; //cyan ground and finish point
}
void output(int r, int c) {
    //(r,c) current position
    for (int k = 0;k < 10000000;k++);
    system("CLS");

    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) { 
            if (i == r && j == c) { cout << color("o") << "   "; }
            else { string c = ""; c += m[i][j]; cout << color(c) << "   "; }
        }
        cout << "\n";
        cout << "\n";
    }
}

bool DFS(int row, int col) { //called as DFS(0,0)
    output(row, col); //output current position
    vector <int> dr = { 1,0,-1,0 }; // translation horizontally
    vector <int> dc = { 0,1,0,-1 }; //translation vertically

    //if destination reached, return 1
    if (row == m.size() - 1 && col == m[row].size() - 1) { return 1; }
    int rr, cc;
    for (int i = 0;i < 4;i++) {
        rr = row + dr[i]; cc = col + dc[i];
        if (rr > -1 && rr <m.size() && cc>-1 && cc < m[m.size() - 1].size() && m[rr][cc] != 'W' && explored[{rr, cc}] == 0) {
            explored[{row, col}] = 1; //update list of explored coordinates
            if (path(rr, cc) == 1)return 1;
        }
    }
    return 0;
}

int main() { 
    cout<<DFS();
}
