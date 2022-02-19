#include <iostream>
#include <vector>
#include <map>
#include <deque>

using namespace std;
map <pair<int, int>, bool> explored; //stores coordinates already explored
//maze must be a n x n square. 
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
deque <pair<int, int>> shortestpath; //stores nodes along shortest path

//Goal : Reach (n-1,n-1) from (0,0). Can move in any orthogonal direction

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
void output1() { 
    //animate shortest path for BFS()
    //move character + leave a trail behind.
 
    for (auto n : shortestpath) { //for each node along shortest path

        for (int i = 0;i < m.size();i++) {
            for (int j = 0;j < m[i].size();j++) {
                if (i == n.first && j == n.second) {
                    cout << color("o") << "   ";
                    m[n.first][n.second] = 't'; //trail
                }
                else {
                    string c = ""; c += m[i][j];
                    if (i == m.size() - 1 && j == m[m.size() - 1].size() - 1) {
                        cout << color("f") << "   ";
                    }
                    else {
                        cout << color(c) << "   ";
                    }
                }
            }
            cout << "\n";
            cout << "\n";
        }

        for (int k = 0;k < 100000000;k++); //freeze screen
        system("CLS");

    }

}

bool DFS(int row, int col) {
    output(row, col);
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
                && m[x][y] != 'W')
            {
                NextNode.push_back({ x,y });
                parentnode[{x, y}] = { currentcoord.first,currentcoord.second };
                distance[{x, y}] = distance[currentcoord] + 1;

                if (x == m.size() - 1 && y == m[m.size() - 1].size() - 1) {//shortest path reached
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
    return 0;
}


int main() {
    cout << BFS() << endl; //start at (0,0) and move to (n-1, n-1)
    output1(); //NOTE : maze is permanently modified after this call and cannot be used again.
    
    //cout<<DFS();


}
