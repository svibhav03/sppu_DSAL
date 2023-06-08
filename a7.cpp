#include<iostream>
using namespace std;
class Edge{
public:
int src;
int des;
int weight;
};
class Graph{
    int nv;
    int ed;
    int **adjmat;
    public:
    Graph(int v,int d){
        nv=v;
        ed=d;
        adjmat=new int*[nv];
        for(int i=0;i<nv;i++){
            adjmat[i]=new int[nv];
        }
    }
    void initialize(){
        for(int i=0;i<nv;i++){

            for(int j=0;j<nv;j++){
                adjmat[i][j]=0;
            }

        }
        for(int i=0;i<ed;i++){
            int src,des,cs;
            cout<<"Enter Source:";
            cin>>src;
            cout<<"Enter Destination:";
            cin>>des;
            cout<<"Enter Cost:";
            cin>>cs;
            adjmat[src][des]=cs;
            adjmat[des][src]=cs;
        }
    }
    void prism(int start){
        int rich[nv];
        int unrich[nv];
        int result[nv][nv];
        for(int i=0;i<nv;i++){
            for (int j = 0; j < nv; j++)
            {
                result[i][j]=0;
            }

        }
        for(int i=0;i<nv;i++){
            rich[i]=0;
            unrich[i]=1;
        }
        int edge=0;
        int weight=0;
        rich[start]=1;
        unrich[start]=0;
        cout<<"Path:"<<"\t"<<"Cost"<<endl;
        while(edge<nv-1){
            int s=100000;
            int flag=0;
            int a=0;
            int b=0;
            for(int i=0;i<nv;i++){
            if(rich[i]==1){
                for(int j=0;j<nv;j++){
                    if(unrich[j]==1){

                        if(s>adjmat[i][j] && adjmat[i][j]!=0){
                            flag=1;
                            a=i;
                            b=j;
                            s=adjmat[i][j];
                        }
                    }
                }
            }
            }

            if(flag==1){
                rich[b]=1;
                unrich[b]=0;
                weight+=s;
                edge+=1;
                result[a][b]=s;

            }
        }
        for (int i = 0; i < nv; i++)
        {
            for (int j = 0; j < nv; j++)
            {
                if(result[i][j]!=0){
                    cout<<i<<"-"<<j<<"\t"<<result[i][j]<<endl;
                }
            }

        }
        cout<<"______________"<<endl;
        cout<<"Minimum Path:"<<weight<<endl;
    }
    void kruskal(int start){
    Edge *re=new Edge[ed];
    int vis[nv][nv];
    for(int i=0;i<nv;i++){
       for (int j = 0; j < nv; j++)
       {
            vis[i][j]=0;
       }

    }
    for(int x=0;x<ed;x++){
    int mn=1000000;
    int a;
    int b;
    for(int i=0;i<nv;i++){
    for(int j=0;j<nv;j++){
    if(vis[i][j]==0 && adjmat[i][j]<mn && adjmat[i][j]!=0 && vis[j][i]==0){
    a=i;
    b=j;
    mn=adjmat[i][j];
    }
    }
    }
    //cout<<mn<<endl;
    vis[a][b]=1;
    re[x].src=a;
    re[x].des=b;
    re[x].weight=mn;
    }
    int vi[nv];
    for(int i=0;i<nv;i++){
    vi[i]=0;
    }
    int result[nv][nv];
    for(int i=0;i<nv;i++){
       for (int j = 0; j < nv; j++)
       {
          result[i][j]=0;
       }

    }
    for(int x=0;x<ed;x++){
    cout<<re[x].src<<" "<<re[x].des<<" "<<re[x].weight<<endl;
    }
    for(int i=0;i<ed;i++){
    if(vi[re[i].src]==0 || vi[re[i].des]==0){
    result[re[i].src][re[i].des]=re[i].weight;
    vi[re[i].src]=1;
    vi[re[i].des]=1;

    }
    }
    int weight=0;
    for (int i = 0; i < nv; i++)
    {
      for (int j = 0; j < nv; j++)
      {
           if(result[i][j]!=0){
            weight+=result[i][j];
               cout<<i<<"-"<<j<<"\t"<<result[i][j]<<endl;
           }
      }

    }
    cout<<"______________"<<endl;
    cout<<"Minimum Path:"<<weight<<endl;
    }
    void display(){
        cout<<"Graph is as Follows:"<<endl;
        for(int i=0;i<nv;i++){
            cout<<i<<"=> ";
            for(int j=0;j<nv;j++){
                cout<<adjmat[i][j]<<" ";
            }
            cout<<endl;
        }

    }
};

int main(){
    int nv,ed;
    cout<<"Enter NUmber of Vertices:";
    cin>>nv;
    cout<<"Enter NUmber of Edges:";
    cin>>ed;
    Graph g(nv,ed);
    g.initialize();
    g.display();
    g.kruskal(0);
    return 0;
}
