#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> point;
typedef pair<point,int> bf;
int xgerak[4] = {-1,0,0,1};
int ygerak[4] = {0,-1,1,0};
bool isValidP(int n,int m,point p, vector<string> &peta){
    return p.first>=1 && p.first<=n && p.second>=1 && p.second<=m && peta[p.first][p.second]=='.';
}
vector< vector<int> > bfs(vector<string> &peta,point p){
    int n = peta.size()-1;
    int m = peta[1].length()-1;

    vector<int> temp(m+1,-1);
    vector< vector<int> > nilai;
    for(int i=0;i<=n;i++){
        nilai.push_back(temp);
    }
    queue<bf> bef;
    bef.push({p,0});
    nilai[p.first][p.second] = 0 ; 

    while(!bef.empty()){
        bf temp = bef.front();
        bef.pop();
//        nilai[temp.first.first][temp.first.second] = temp.second;
        point utara = {temp.first.first-1,temp.first.second};
        point selatan = {temp.first.first+1,temp.first.second};
        point barat = {temp.first.first,temp.first.second-1};
        point timur = {temp.first.first,temp.first.second+1};

        if(isValidP(n,m,utara,peta)&& nilai[utara.first][utara.second]==-1)  {
            bef.push({utara,temp.second+1});
            nilai[utara.first][utara.second] = temp.second+1;

        }
        if(isValidP(n,m,selatan,peta)&& nilai[selatan.first][selatan.second]==-1)   {
            bef.push({selatan,temp.second+1});
            nilai[selatan.first][selatan.second] = temp.second+1;

        }
        if(isValidP(n,m,barat,peta)&& nilai[barat.first][barat.second]==-1)  {
            bef.push({barat,temp.second+1});
            nilai[barat.first][barat.second] = temp.second+1;

        } 
        if(isValidP(n,m,timur,peta)&& nilai[timur.first][timur.second]==-1)   {
            bef.push({timur,temp.second+1});
            nilai[timur.first][timur.second] = temp.second+1;

        }
    }
    //cout<<"blomb";



    return nilai;
}


void bfs2(vector<string> &peta,point p,vector< vector<int> > &hasil){
    int n = peta.size()-1;
    int m = peta[1].length()-1;

    vector<int> temp(m+1,-1);
    vector< vector<int> > nilai;
    for(int i=0;i<=n;i++){
        nilai.push_back(temp);
    }
    queue<bf> bef;
    bef.push({p,0});
    nilai[p.first][p.second] = 0 ; 
    while(!bef.empty()){
        bf temp = bef.front();
        bef.pop();
//        nilai[temp.first.first][temp.first.second] = temp.second;
        point utara = {temp.first.first-1,temp.first.second};
        point selatan = {temp.first.first+1,temp.first.second};
        point barat = {temp.first.first,temp.first.second-1};
        point timur = {temp.first.first,temp.first.second+1};

        if(isValidP(n,m,utara,peta)&& nilai[utara.first][utara.second]==-1){
            bef.push({utara,temp.second+1});
            nilai[utara.first][utara.second] = temp.second+1;
        }
            
        if(isValidP(n,m,selatan,peta)&& nilai[selatan.first][selatan.second]==-1)   {
            bef.push({selatan,temp.second+1});
            nilai[selatan.first][selatan.second] = temp.second+1;

        }
        if(isValidP(n,m,barat,peta)&& nilai[barat.first][barat.second]==-1)   {
            bef.push({barat,temp.second+1});
            nilai[barat.first][barat.second] = temp.second+1;

        }
        if(isValidP(n,m,timur,peta)&& nilai[timur.first][timur.second]==-1)   {
            bef.push({timur,temp.second+1});
            nilai[timur.first][timur.second] = temp.second+1;

        }
    }
    //cout<<"blomb";

    int sum=0;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(hasil[i][j]!=-1){
                //cout<<nilai[i][j]<<endl;
                //sum+=nilai[i][j];
                if(nilai[i][j]< hasil[i][j])
                	hasil[i][j] = nilai[i][j];
           

            }
            //cout<<nilai[i][j]<<" ";
        }
        //cout<<endl;
    }

    //return nilai;
}


void cariKecil(vector< vector<int> > &hasil,vector< vector<int> >&temp){
    int sum=0;
    int n = hasil.size()-1;
    int m = hasil[1].size()-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(hasil[i][j]!=-1){
                //cout<<nilai[i][j]<<endl;
                //sum+=nilai[i][j];
                if(temp[i][j]< hasil[i][j])
                	hasil[i][j] = temp[i][j];
           

            }
            //cout<<nilai[i][j]<<" ";
        }
        //cout<<endl;
    }	
}

int summin(vector< vector<int> > &hasil){
    int sum=0;
    int n = hasil.size()-1;
    int m = hasil[1].size()-1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(hasil[i][j]!=-1){
                //cout<<nilai[i][j]<<endl;
                sum+=hasil[i][j];

            }
            //cout<<nilai[i][j]<<" ";
        }
        //cout<<endl;
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

void printShortestPathXY(vector<string> &peta, vector< vector<int> > &hasilAngka,int n,int m,int x,int y){
    vector<point> hasil;
    cout<<"("<<x<<","<<y<<") = ";
    hasil.push_back({x,y});
    while(hasilAngka[x][y]!=0){
        int minV = INT_MAX;
        point idx;
        for(int i=0;i<4;i++){
            int xbaru = x+ xgerak[i];
            int ybaru = y+ ygerak[i];
            if(isValidP(n,m,{xbaru,ybaru},peta) &&  hasilAngka[xbaru][ybaru]<minV){
                minV = hasilAngka[xbaru][ybaru];
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


void printAllShortestPath(vector<string> &peta, vector< vector<int> > &hasil ,int n,int m){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(isValidP(n,m,{i,j},peta)){
                printShortestPathXY(peta,hasil,n,m,i,j);
            }
        }
    }
}


int main(){
    int n,m,k;
    std::chrono::time_point<std::chrono::system_clock> start, end;

    cin>>n>>m>>k;
    vector<string> peta;
    peta.push_back("a");
    for(int i=1;i<=n;i++){
        string temp;
        cin>>temp;
        peta.push_back("a"+temp);
    }

    //vector<point> colP;
    start = std::chrono::system_clock::now();

    vector< vector<int> > hasil ;
    for(int i=0;i<k;i++){
        int x;
        int y;
        cin>>x>>y;
        if(i==0){
        	hasil = bfs(peta,{x,y});
        } else{
        	//vector< vector<int> > temp = bfs(peta,{x,y});
            bfs2(peta,{x,y},hasil);
        }
        //colP.push_back({x,y});

    }
    
    
    end = std::chrono::system_clock::now();
    cout<<"Ukuran Matriks NxM : "<<n<<"x"<<m<<endl;
    cout<<"Ukuran K(jumlah sel tujuan) : "<<k<<endl;
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout<<"Waktu Algoritma : "<<elapsed_seconds.count()<<"s\n";
    cout<<"Jumlah Jarak Terdekat : " <<summin(hasil)<<endl;
    cout<<endl<<"Hasil Shortest Path"<<endl;
    printAllShortestPath(peta,hasil , n , m);
}