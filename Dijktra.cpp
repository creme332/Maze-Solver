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

int Dijktra() {
    map <pair<int, int>, int> distance = { {{0,0},0} };
    multimap <int, pair<int, int>> nextnode = { {0,{0,0}} };
    //next node to be visited and their corresponding distances. We first access nodes closest to source.
    //multimap sorts by distance and allows duplicate distances.

    int dx[] = { 1,0,-1,0 }; // translation horizontally
    int dy[] = { 0,1,0,-1 }; //translation vertically
    int x, y;//new position

    while (nextnode.size() != 0) {
        pair<int, int> current = nextnode.begin()->second; //coordinates of current node
        nextnode.erase(nextnode.begin()); //dequeue

        for (int i = 0;i < 4;i++) {
            x = current.first + dx[i]; y = current.second + dy[i];
            if (x < m.size() && y < maze.size()) {

                int d = distance[current] + abs(maze[current.first][current.second] - maze[x][y]);

                if (distance.count({ x,y })) { // if key exists => it already has a previous min distance
                    if (d < distance[{x, y}]) { //new minimum distance found
                        distance[{x, y}] = d;
                        nextnode.insert({d, { x,y } }); //must update distance for other connected nodes 
                    }
                }
                else { //this is the first time we are seeing node (x,y)
                    distance[{x, y}] = d;
                    nextnode.insert({ d, { x,y } });
                }
            }
        }
    }

    return distance[{m.size() - 1, m[m.size()-1].size() - 1}];
}
int main(){
    system("cls");
    InitialiseTerminal();
    cout<<"\n";
}