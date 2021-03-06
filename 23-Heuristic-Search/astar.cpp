#include <iostream>
#include <queue>
#include <stack>
#include <math.h>
#define ROW 9
#define COL 10
using namespace std;

int adj[ROW][COL] =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
int dx[8] = { 0,-1,0,1,1,-1,-1, 1};
int dy[8] = {-1, 0,1,0,1,-1, 1,-1};


struct node{
    int f;
    int g;
    int i,j;
    node(int i = 0, int j = 0,int f = 0,int g = 0){  
        this->f = f;
        this->i = i;
        this->j = j;
        this->g = g;
    }
    bool operator < (const node &o)const{
        return f > o.f;
    }
};

int manhattan(int i, int j, node dest){
    return abs(dest.i - i) + abs(dest.j - j);
}

int diagonal(int i, int j, node dest){
    return max(abs(i - dest.i),abs(j - dest.j));
}

int euclidean(int i, int j, node dest){
    double d = sqrt((i - dest.i) * (i - dest.i) + (j - dest.j) * (j - dest.j));
    return int(d);
}
void pathtrace(node point[ROW][COL],node &dest){
        node n = dest;
        stack<node> s;
        while(n.i != point[n.i][n.j].i || n.j != point[n.i][n.j].j){
            s.push(n);
            n = point[n.i][n.j];
        }
        s.push(n);
        while(!s.empty()){
            n = s.top(); 
            s.pop();
            std::cout << '(' << n.i << ',' <<n.j << ")\t"; 
        }
}

bool isvalid(int x, int y){
    return !(x < 0 || y < 0 || x >= ROW || y >= COL);
}

void astar(node &src, node &dest){
    bool visited[ROW][COL];
    node point[ROW][COL];
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            visited[i][j] = false;
            point[i][j].f = INT_MAX;
        }
    }


    std::priority_queue<node> q; 
    q.push(src);
    point[src.i][src.j] = src;
    while(!q.empty()){
        node n = q.top();
        std::cout << "processing " << n.i << ' ' << n.j << std::endl;  
        q.pop(); 
        visited[n.i][n.j] = true;
        if(n.i == dest.i && n.j == dest.j){
            std::cout << "Found dest\n";
            pathtrace(point,dest);
            return;
        }
        for(int i = 0; i < 8; i++){
            int x = n.i+dx[i];
            int y = n.j+dy[i];
            if(isvalid(x,y) && adj[x][y] == 1 && !visited[x][y]){
                int newg = point[n.i][n.j].g+1;
                int newf = newg + euclidean(x, y,dest);
                //int newf = newg + manhattan(x, y,dest);
                //int newf = newg + diagonal(x, y,dest);
                if(newf < point[x][y].f){
                    point[x][y] = n;
                    point[x][y].g = newg;
                    q.push(node(x,y,newf)); 
                }
            }
        }  
    }
    std::cout << "Not found\n";
}

int main(){
    node src(8,0);
    node dest(0,0);
    astar(src,dest);
    return 0;
}
