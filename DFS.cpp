#include <iostream>
#include <vector>
#include <map>
#include <windows.h>
#include <thread>
#include <cstdlib>
using namespace std;

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

vector <vector<char>> m = {
    {'.','W','.','.','.','.','.','.','.'},
    {'.','.','.','W','.','W','.','W','.'},
    {'.','.','.','W','W','W','.','.','.'},
    {'.','.','.','.','.','W','.','W','.'},
    {'W','.','.','W','W','.','.','.','.'},
    {'.','W','.','.','W','.','.','W','.'},
    {'.','.','.','W','.','.','.','.','.'},
    {'W','.','.','W','.','W','.','.','.'},
    {'.','.','.','W','.','W','.','W','.'},
};
map <pair<int, int>, bool> explored; //stores coordinates already explored

string color(string a) { //color character a 
    if (a == "*")return "\x1B[33m*\33[0m"; //yellow character and trail
    if (a == "W")return "\x1B[31mW\033[0m"; //red walls
    return "\x1B[92m" + a + "\033[0m"; //cyan ground and finish point
}
void InitialiseTerminal() {
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) { 
             string c = ""; c += m[i][j];
             cout << color(c)<<" "; 
        }
        cout << "\n\n";
    }
}
void setCursorPosition(const int row, const int col)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(hOut, coord);
}
bool DFS(int row, int col) { //called as DFS(0,0)
    //path.push_back({row,col});
        //output(); 
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
    setCursorPosition(row*2, col*2);
    std::cout << color("*");
    vector <int> dr = { 1,0,-1,0 }; // translation horizontally
    vector <int> dc = { 0,1,0,-1 }; //translation vertically

    //if destination reached, return 1
    if (row == m.size() - 1 && col == m[row].size() - 1) {return 1; }
    int rr, cc;
    for (int i = 0;i < 4;i++) {
        rr = row + dr[i]; cc = col + dc[i];
        if (rr > -1 && rr <m.size() && cc>-1 && cc < m[m.size() - 1].size() && m[rr][cc] != 'W' && explored[{rr, cc}] == 0) {
            explored[{row, col}] = 1; //update list of explored coordinates
            if (DFS(rr, cc) == 1){return 1;}
        }
    }
    return 0;
}

int main() { 
    system("cls");
    InitialiseTerminal(); //output maze
    DFS(0,0);
    cout<<"\n";
}
