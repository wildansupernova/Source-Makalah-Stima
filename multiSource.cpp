#include <bits/stdc++.h>
#include <chrono>
using namespace std;
typedef pair<int,int> point;
typedef pair<point,int> bf;
typedef vector<int> vi;

int xgerak[4] = {-1,0,0,1};
int ygerak[4] = {0,-1,1,0};


bool isValidP(int n,int m,point p, vector<vi> &peta){
    return p.first>=1 && p.first<=n && p.second>=1 && p.second<=m && peta[p.first][p.second]==-1;
}

bool isValidP2(int n,int m,point p, vector<vi> &peta){
    return p.first>=1 && p.first<=n && p.second>=1 && p.second<=m && peta[p.first][p.second]!=-2;
}


void hasilBFS(vector<vi> &peta,queue<bf> &antrian,int n,int m){
    
    while(!antrian.empty()){
        bf temp = antrian.front();
        antrian.pop();
        if(isValidP(n,m,temp.first,peta)){
            peta[temp.first.first][temp.first.second] = temp.second;
            point utara = {temp.first.first-1,temp.first.second};
            point selatan = {temp.first.first+1,temp.first.second};
            point barat = {temp.first.first,temp.first.second-1};
            point timur = {temp.first.first,temp.first.second+1};        
            antrian.push({utara,temp.second+1});    
            antrian.push({selatan,temp.second+1}); 
            antrian.push({barat,temp.second+1}); 
            antrian.push({timur,temp.second+1}); 
        }
    }
}



int jumlahkan(vector<vi> &peta,int n,int m){
    int sum=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(peta[i][j]!=-2 && peta[i][j]!=-1){
                sum+=peta[i][j];
            }
        }
    }

    return sum;
}



void printVectorPath(vector< point > &path){
    for(int i=0;i < path.size();i++){
        if(i!=0){
            cout<<" -> ";
        } 
        cout<<"("<<path[i].first<<","<<path[i].second<<")";
    }
}

void printShortestPathXY(vector<vi> &peta,int n,int m,int x,int y){
    vector<point> hasil;
    cout<<"("<<x<<","<<y<<") = ";
    hasil.push_back({x,y});
    while(peta[x][y]!=0){
        int minV = INT_MAX;
        point idx;
        for(int i=0;i<4;i++){
            int xbaru = x+ xgerak[i];
            int ybaru = y+ ygerak[i];
            if(isValidP2(n,m,{xbaru,ybaru},peta) &&  peta[xbaru][ybaru]<minV){
                minV = peta[xbaru][ybaru];
                idx = {xbaru,ybaru};
            }
        }
        x = idx.first;
        y=idx.second;
        hasil.push_back({x,y});
    }
    printVectorPath(hasil);
    cout<<"\n";
}


void printAllShortestPath(vector<vi> &peta,int n,int m){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(isValidP2(n,m,{i,j},peta)){
                printShortestPathXY(peta,n,m,i,j);
            }
        }
    }
}

void printAll(vector<vi> &b,int n,int m){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<b[i][j]<<" ";
        }
        cout<<endl;
    }
}




int main(){

    std::chrono::time_point<std::chrono::system_clock> start, end;

    vector<vi> mep;
    mep.push_back({1,2,3});
    int n,m,s;
    cin>>n>>m>>s;
    for(int i = 0;i<n;i++){
        string temp;
        cin>>temp;
        vi hasil;
        hasil.push_back(1);
        for(int i=0;i<m;i++){
            if(temp[i]=='.'){
                hasil.push_back(-1);
            } else{
                hasil.push_back(-2);
            }
        }
        mep.push_back(hasil);
    }
    
    start = std::chrono::system_clock::now();
    queue<bf> antri;
    for(int i=0;i<s;i++){
        int x,y;
        cin>>x>>y;
        antri.push({{x,y},0});
    }
    hasilBFS(mep,antri,n,m);

    end = std::chrono::system_clock::now();
    cout<<"Ukuran Matriks NxM : "<<n<<"x"<<m<<endl;
    cout<<"Ukuran K(jumlah sel tujuan) : "<<s<<endl;
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout<<"Waktu Algoritma : "<<elapsed_seconds.count()<<"s\n";
    cout<<"Jumlah Jarak Terdekat : " <<jumlahkan(mep,n,m)<<endl;
    cout<<endl<<"Hasil Shortest Path"<<endl;
    printAllShortestPath(mep , n , m);
}