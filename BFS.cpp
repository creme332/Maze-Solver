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
#define SHORTESTPATH 'p'
#define DESTINATION 'f'
using namespace std;

//Goal : Reach DESTINATION from (0,0). Can move in any orthogonal direction.

vector <vector<char>> m = {
    {'.','W','.','.','.','.','.','.','.','W','.','W','.','.','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','W','.','.','.','.','.','W','W','.','.','W','.','W','.','.','.'},
    {'.','W','.','.','W','.','.','.','.','.','.','W','.','.','W','.','.','.',DESTINATION,'.','.','.','.'},
    {'.','W','.','.','W','W','W','W','W','.','.','.','.','W','.','W','.','.','.','W','.','.','.'},
    {'.','.','.','.','.','W','.','.','W','.','.','.','W','.','.','.','W','.','.','.','.','W','.'},
    {'W','.','.','.','.','W','W','.','W','.','W','W','.','W','.','.','.','W','.','.','W','.','.'},
    {'.','.','.','.','.','.','.','.','W','W','W','W','.','W','.','.','.','W','.','W','.','.','.'},
    {'.','.','.','.','W','.','.','.','.','.','.','.','.','.','.','.','.','.','W','.','.','.','.'},
    {'.','W','.','.','W','.','W','.','.','.','W','W','W','W','.','.','.','W','.','.','.','.','.'},
    
};
deque <pair<int, int>> shortestpath; //stores nodes along shortest path

void setCursorPosition(const int row, const int col){
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(hOut, coord);
}
string Color(char c) { // color a character
    if (c == WALL) return  "\033[48;5;196m\033[38;5;232m \033[0m"; //red block for wall 
    if (c == PATH || c == START) return  "\033[48;5;14m\033[38;5;232m \033[0m";  //blue block for explored path 
    if (c == SHORTESTPATH) return  "\033[48;5;21m\033[38;5;232m \033[0m";  //dark blue block for shortest path 
    if (c == DESTINATION) return  "\033[48;5;34m\033[38;5;232m \033[0m"; //green block for finish point
    if (c == EMPTY) return "\033[48;5;15m\033[38;5;232m \033[0m"; //white block for empty space
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
void OutputShortestPath() { 
    for (auto n : shortestpath) { //output each node along shortest path
        setCursorPosition(n.first,n.second);
        cout<<Color(SHORTESTPATH);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int BFS() {// find shortest path using BFS
    map <pair<int, int>, int> distance = { {{0, 0},0} }; //minimum distance from start (in terms of number of moves required)
    deque <pair<int, int>> NextNode = { {0, 0} }; //head of queue is the next node to be checked
    map <pair<int, int>, pair<int, int>> parentnode = { {{0, 0}, {-1,-1}} }; //parent node of a node.

    vector <int> dx = { 1,0,-1,0 }; // translation horizontally
    vector <int> dy = { 0,1,0,-1 }; //translation vertically
    int x, y; // new coordinates after moving 

    while (NextNode.size() != 0) {
        pair<int, int> currentcoord = NextNode.front();
        NextNode.pop_front();

        for (int i = 0;i < 4;i++) {
            x = currentcoord.first + dx[i];
            y = currentcoord.second + dy[i];

            if (x > -1 && x < m.size() && y > -1
                && y < m[m.size() - 1].size() && parentnode.count({ x,y }) == 0
                && m[x][y] != WALL)
            {
                setCursorPosition(x,y); cout<<Color(PATH);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));

                NextNode.push_back({ x,y });
                parentnode[{x, y}] = { currentcoord.first,currentcoord.second };
                distance[{x, y}] = distance[currentcoord] + 1;

                if (m[x][y] == DESTINATION) {//destination & shortest path reached
                    int ans = distance[{x, y}];
                    int x0, y0;
                    while (x != -1) {
                        shortestpath.push_front({ x, y });
                        x0 = x; y0 = y;
                        x = parentnode[{x0, y0}].first;
                        y = parentnode[{x0, y0}].second;
                    }
                    return ans;
                }

            }

        }
    }
    return -1;
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

    InitialiseTerminal();
    BFS(); //BFS also outputs number of steps required to reach destination 
    OutputShortestPath(); 

    setCursorPosition(m.size(),m[m.size()-1].size());
    cout<<"\n";

}
