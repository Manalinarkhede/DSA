#include<iostream>
#include<string>
using namespace std;
class office {
    public:
    int n;
    int adj[10][10];
    string office[10];

    void input() {
        cout<<"Enter the no. of offices: ";
        cin>>n;
        for(int i=0; i<n; i++) {
            cout<<"Enter the name of office "<<i<<":";
            cin>>office[i];
        }
        cout<<"Enter the charges to connect the offices: ";
        for(int i=0; i<n; i++) {
            cout<<"From "<<office[i]<<endl;
            for(int j=0; j<n; j++) {
                if(i==j) {
                    adj[i][j]=0;
                    continue;
                }
                cout<<"To "<<office[j]<<":";
                cin>>adj[i][j];
                adj[j][i]=adj[i][j];
            }
        }
    }

    void display() {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                cout<<adj[i][j];
            }
            cout << endl;
        }
    }

    void prims() {
        int visit[n];
        int minCost=0;
        int count= n-1; //edges
        int minIndex=0;
        int cost=0; //total cost

        for(int i=0; i<n; i++) {
            visit[i]=0; //all offices->unvisited
        }

        visit[0]=1; //first office
        cout<<"Shortest path using prims algorithm\n :";
        cout<<office[0]<<"->";

        while(count--) {
            minCost=999;
            for(int i=0; i<n; i++) {
                for(int j=0; j<n; j++) {
                    if(visit[i]==1 && visit[j]==0 && adj[i][j]<minCost && adj[i][j] !=0) {
                        minCost=adj[i][j];
                        minIndex=j;
                    }
                }
            }
            visit[minIndex]=1;
            cout<<office[minIndex]<<"->";
            cost=cost+minCost;
        }
        cout << "END" << endl;
        cout << "Minimum Cost to Connect All Offices (MST Cost): " << cost << endl;
    
    }

};

int main() {
    office obj;
    obj.input();
    obj.display();
    obj.prims();
    return 0;
}