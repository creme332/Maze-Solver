#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <windows.h>
#include <thread>
#define WALL 'W'
#define EMPTY '.'
#define PATH 'o'
#define DESTINATION 'f'
using namespace std;

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

vector <vector<char>> m = {
    {'.','W','.','.','.','.','.','.','.','W','.','W','.','.',','},
    {'.','W','.','.','.','W','.','W','.',',','.','.','.','W','W'},
    {'.','.','.','W','.','.','.','.','W',',','.','W','.','.','W'},
    {'.','W','.','.','.','.','W','.','.',',','.','.','.','.',','},
    {'.','.','.','W','.','W','.','.','W',',','.','.','W','.',','},
    {'.','.','.','.','.','W','W','.','W',',','W','W','.','.',','},
    {'.','W','.','.','W','.','.','.','W',',','.','.','.','W',','},
    {'.','.','.','.','W','.','.','.','W',',','.','W','.','.',','},
    {'.','W','.','.','W','.','W','.','.',',','W','.','W','W',','},
};
string Color(char c) { // color a character
    int color[] = { 196,220,226,10,39,129 }; //list of colors
    if (c == WALL) return  "\033[48;5;196m\033[38;5;232m \033[0m"; //red block for wall 
    if (c == PATH) return  "\033[48;5;14m\033[38;5;232m \033[0m";  //blue block for path 
    if (c == DESTINATION) return  "\033[48;5;34m\033[38;5;232m \033[0m"; //green block for destination
    return  "\033[48;5;15m\033[38;5;232m \033[0m"; //white block for empty space
}
void InitialiseTerminal() {
    for (int i = 0;i < m.size();i++) {
        for (int j = 0;j < m[i].size();j++) { 
            if(i==m.size()-1 && j ==m[i].size()-1 ){
                cout << Color(DESTINATION); 
            }else{
                cout << Color(m[i][j]); 
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
int main(){
    system("cls");
    cout<<"Hello world";
    cout<<"\n";
}