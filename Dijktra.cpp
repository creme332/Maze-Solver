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
    {START,'W','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','.','.','.','W','.','.','.','.','.','W','W','.','.','W','.','W','.','.','.'},
    {'.','W','.','.','.','.','.','.','W','.','.','W','.','.','W','.','.','.','.','.','.','.','.'},
    {'.','W','.','W','W','W','W','W','.','.','.','.','.','.','.','.','.','.','.','W','.','.','.'},
    {'.','.','.','W','.','W','.','.','W','.','.','.','W','.','.','.','.','.','.','.','.','.','.'},
    {'W','.','.','W','.','W','W','.','W','.','W','W','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','W','.','.','.','.','.','.','W','.','.','.','.','W','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','.','W','.','.','W','.','.','.','.','.','.','.','.','.','.','.'},
    {'.','W','.','.','W','.','W','.','W','.','W','.','W','W','.','.','.','W','.','.','.','.',DESTINATION},
    
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
            if(m[i][j] == START){cout << Color(START);}
            else{
                if(m[i][j] == DESTINATION){cout << Color(DESTINATION);}
                else{cout << Color(m[i][j]);}
            }
        }
        cout << "\n";
    }
}

int Dijktra() {
    map <pair<int, int>, int> distance = { {{0,0},0} };//shortest distance to each node from start
    multimap <int, pair<int, int>> nextnode = { {0,{0,0}} };
    map <pair<int, int>, pair<int, int>> parentnode = { {{0, 0}, {-1,-1}} }; //parent node of a node.

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
            if (x < m.size() && y < m[m.size()-1].size() && m[x][y] != WALL) {
                int d = distance[current] + 1;

                if (distance.count({ x,y })!= 0) { // if key exists => it already has a previous min distance
                    if (d < distance[{x, y}]) { //new minimum distance found
                        distance[{x, y}] = d;
                        nextnode.insert({d, { x,y } }); //must update distance for other connected nodes 
                        parentnode[{x,y}]={current.first,current.second};
                    }
                }
                else { //this is the first time we are seeing node (x,y)
                    setCursorPosition(x,y); cout<<Color(PATH);std::this_thread::sleep_for(std::chrono::milliseconds(25));
                    distance[{x, y}] = d;
                    nextnode.insert({ d, { x,y } });
                    parentnode[{x,y}]={current.first,current.second};
                } 
            }
        }
    }
    int x0, y0;
    x = m.size() - 1; y = m[m.size()-1].size() - 1; //set (x,y) to destination coordinates
    while (x != -1) {
        shortestpath.push_front({x,y});
        x0 = x; y0 = y;
        x = parentnode[{x0, y0}].first;
        y = parentnode[{x0, y0}].second;
    }
    return distance[{m.size() - 1, m[m.size()-1].size() - 1}];
}
void OutputShortestPath() { 
    for (auto n : shortestpath) { //output each node along shortest path
        setCursorPosition(n.first,n.second);
        cout<<Color(SHORTESTPATH);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main(){
    system("cls");
    hidecursor();

    InitialiseTerminal();
    Dijktra(); //returns shortest distance in terms of number of steps required
    OutputShortestPath();
    
    setCursorPosition(m.size()+20,m[m.size()-1].size()+20);
}