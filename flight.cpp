#include<iostream>
#include<string>
using namespace std;

class FlightGraph {
    public:
    string cities[50];
    int adjmat[50][50]={0};
    int visited[50]={0};
    int n;

    void insert() {
        cout<<"Enter the number of cities : ";
        cin>>n;

        for(int i=0; i<n; i++) {
            cout<<"Enter the name of the city" <<i<<": ";
            cin>>cities[i];
        }

        for(int i=0; i<n; i++) {
            for(int j=i+1; j<n; j++) {
                cout<<"Enter flight time between "<<cities[i]<<" and "<<cities[j]<<":";
                cin>>adjmat[i][j];
                adjmat[j][i]=adjmat[i][j];
            }
        }
    }

    void dfs(int city) {
        visited[city]=1;
        cout<<cities[city]<<" ";

        for(int i=0; i<n; i++) {
            if(adjmat[city][i]!=0 && visited[i]==0) {
                dfs(i);
            }
        }
    }

    void display() {
        
        cout<<"Flight times between Cities:\n";
        cout<<"  ";
        for(int i=0; i<n; i++) {
            cout<<cities[i]<<" ";
        }
        cout<<endl;
        
        for(int i=0; i<n; i++) {
            cout<<cities[i]<<" ";
            for(int j=0; j<n; j++) {
                cout<<adjmat[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    bool isConnected() {
        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                return false; 
            }
        }
        return true;
    }

};
int main() {
    FlightGraph graph;

    graph.insert();         
    graph.display();        

    cout << "\nDFS Traversal starting from city 0: ";
    graph.dfs(0);           

    cout << endl;

    if (graph.isConnected()) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is NOT connected." << endl;
    }

    return 0;
}
