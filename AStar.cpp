#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <windows.h>
#include <thread>
#define WALL 'W'
#define EMPTY '.'
#define PATH 'o'
#define START 's'
#define DESTINATION 'f'
#define SHORTESTPATH 'p'
using namespace std;

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

vector <vector<char>> m = {
    {'s','W','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','W','.','.','.','.','.','W','W','.','.','W','.','W','.','.','.'},
    {'.','W','.','.','W','.','.','.','.','.','.','W','.','.','W','.','.','.','.','.','.','.','.'},
    {'.','W','.','W','W','W','W','W','W','.','.','.','.','W','.','W','.','.','.','W','.','.','.'},
    {'.','.','.','W','.','W','.','.','W','.','.','.','W','.','.','.','W','.','.','.','.','W','.'},
    {'W','.','.','W','.','W','W','.','W','.','W','W','.','W','.','.','.','W','.','.','W','.','.'},
    {'.','W','.','.','.','.','.','.','W','W','W','W','.','W','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','W','.','.','.','.'},
    {'.','W','.','.','W','.','W','.','.','.','W','W','W','W','.','.','.','W','.','.','.','.','f'},
    
};
deque <pair<int, int>> shortestpath; //stores nodes along shortest path

string Color(char c) { // color a character in terminal
    if (c == WALL) return  "\033[48;5;196m\033[38;5;232m \033[0m"; //red block for wall 
    if (c == SHORTESTPATH) return  "\033[48;5;21m\033[38;5;232m \033[0m"; //dark blue block for shortest path
    if (c == PATH || c == START) return  "\033[48;5;14m\033[38;5;232m \033[0m";  //blue block for path 
    if (c == DESTINATION) return  "\033[48;5;34m\033[38;5;232m \033[0m"; //green block for destination
    if (c == EMPTY) return  "\033[48;5;15m\033[38;5;232m \033[0m"; //white block for empty space
    return "INVALID";
}
void setCursorPosition(const int row, const int col)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(hOut, coord);
}

void InitialiseTerminal() {
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) { 
                cout << Color(m[i][j]); 
        }
        cout << "\n";
    }
    setCursorPosition(0,0); Color(PATH);
}

int Astar() {

}
void OutputShortestPath() { 
    for (auto n : shortestpath) { //output each node along shortest path
        setCursorPosition(n.first,n.second);
        cout<<Color(SHORTESTPATH);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
int main(){
    system("cls");
    InitialiseTerminal();
    Astar();
    OutputShortestPath();
    setCursorPosition(m.size()+20,m[m.size()-1].size()+20);
    cout<<"\n\n\n\nDONE!";
}
