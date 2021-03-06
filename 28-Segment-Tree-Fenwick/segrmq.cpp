#include <iostream>
#define INF 0x3F3F3F3F
using namespace std;

int N;
int seg[100],ms;
int ar[] = {2,5,1,4,9,3};

int build(int s, int e, int i){
    if(s == e){
        seg[i] = ar[s];
        return seg[i];
    }
    int mid = (s+e)/2;
    seg[i] = min(build(s,mid,2*i+1),build(mid+1,e,2*i+2));
    return seg[i];
}

void build(){
    build(0,N-1,0);
}

int query(int s, int e,int i,int l, int r){
    if(s >= l && e <= r){
        return seg[i];
    }
    if(e < l || s > r) return INF;
    int mid = (s+e)/2;
    return min(query(s,mid,2*i+1,l,r),query(mid+1,e,2*i+2,l,r));
}

int query(int l, int r){
    return query(0,N-1,0,l,r);
}

int update(int s, int e, int i, int k, int d){
    if(s <= k && e >= k){
        if(s == e){
            seg[i] = min(seg[i],d);
        } else{
            int mid = (s+e)/2;
            seg[i] = min(update(s,mid,2*i+1,k,d),update(mid+1,e,2*i+2,k,d));
        }
    }
    return seg[i];
}

void update(int k, int d){
    update(0,N-1,0,k,d);
}

void print(){
    for(int i = 0; i < ms; i++){
        cout << seg[i] << ' ';
    }
    cout << endl;
}

void init(){
    ms = N;
    bool p = true;
    while(ms & (ms-1)){
        ms = ms & (ms-1);
        p = false;
    }
    ms<<=1;
    if(!p) ms <<= 1;
    ms--;
}

int main(){
    N = sizeof(ar)/sizeof(ar[0]);   
    init();
    build();
    print();
    std::cout << query(1,3) << std::endl;
    update(3,-1);
    print();
    std::cout << query(1,3) << std::endl;     
    return 0;
}
