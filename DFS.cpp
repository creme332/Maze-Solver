#include <iostream>
#include <vector>
#include <map>
#include <windows.h>
#include <thread>
#include <cstdlib>
#define WALL 'W'
#define EMPTY '.'
#define PATH 'o'
#define START 's'
#define DESTINATION 'f'
using namespace std;

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

vector <vector<char>> m = {
    {'.','W','.','.','.','.','.','.','.','W','.','W','.','.',DESTINATION,'.','.','W','.','W','.','.','.'},
    {'.','.','.','.','.','.','.','W','.','.','.','.','.','W','W','.','.','W','.','W','.','.','.'},
    {'.','W','.','.','.','.','.','.','W','.','.','W','.','.','W','.','.','.','.','.','.','.','.'},
    {'.','W','.','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','W','.','.','.'},
    {'.','.','.','W','.','W','.','.','W','.','.','.','W','.','.','.','.','.','.','.','.','.','.'},
    {'W','.','.','W','.','W','W','.','W','.','W','W','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','W','.','.','.','.','.','.','W','.','.','.','.','W','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','.','W','.','.','W','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','W','.','.','W','.','W','.','W','.','W','.','W','W','.','.','.','W','.','.','.','.','.'},
    
};
map <pair<int, int>, bool> explored; //stores coordinates already explored

string Color(char c) { // color a character in terminal
    if (c == WALL) return  "\033[48;5;196m\033[38;5;232m \033[0m"; //red block for wall 
    if (c == PATH || c == START) return  "\033[48;5;14m\033[38;5;232m \033[0m";  //blue block for path 
    if (c == DESTINATION) return  "\033[48;5;34m\033[38;5;232m \033[0m"; //green block for destination
    if (c == EMPTY) return  "\033[48;5;15m\033[38;5;232m \033[0m"; //white block for empty space
    return "INVALID";
}
void InitialiseTerminal() {
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) { 
            if(m[i][j] == START){cout << Color(START);}
            else{
                if(m[i][j] == DESTINATION){cout << Color(DESTINATION);}
                else{cout << Color(m[i][j]);}
            }
        }
        cout << "\n";
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
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    setCursorPosition(row, col);
    std::cout << Color(PATH);
    vector <int> dr = { 1,0,-1,0 }; // translation horizontally
    vector <int> dc = { 0,1,0,-1 }; //translation vertically

    //if destination reached, return 1
    if (m[row][col] == DESTINATION) {return 1;}
    int rr, cc;
    for (int i = 0;i < 4;i++) {
        rr = row + dr[i]; cc = col + dc[i];
        if (rr > -1 && rr <m.size() && cc>-1 && cc < m[m.size() - 1].size() && m[rr][cc] != WALL && explored[{rr, cc}] == 0) {
            explored[{row, col}] = 1; //update list of explored coordinates
            if (DFS(rr, cc) == 1){return 1;}
        }
    }
    return 0;
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main() { 
    system("cls");
    hidecursor();

    int x=8,y=8 ; //start position
    m[x][y]=START;
    InitialiseTerminal(); //output maze
    DFS(x,y);
    
    setCursorPosition(m.size()+100,m[m.size()-1].size()+100);
    cout<<"\n";
}
