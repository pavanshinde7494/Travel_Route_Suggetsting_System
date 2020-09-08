#include <iostream>
#include <bits/stdc++.h>
#include <string>
#define MAX 9999
using namespace std;

class Password
{
  private:
    string str="p";
  public:
    bool check()
    {
      string s;
      cin>>s;
      return s==str;
    }
    void changePassword()
    {
      string s;
      cout<<"\nEnter New Password: ";
      cin>>s;
      str=s;
    }
    friend bool confirm(Password&);
};

bool confirm(Password &p)
{
  string s;
  cout<<"\nEnter Password: ";
  cin>>s;
  if(s==p.str)
    return true;
  return false;
}

class Graph
{
private:
  int adj[10][10];  
public:
  void setting_values()
  {
    for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)
        adj[i][j]=MAX;
    }
    adj[0][1]=adj[1][0]=21;
    adj[0][2]=adj[2][0]=145;
    adj[0][8]=adj[8][0]=141;

    adj[1][9]=adj[9][1]=314;

    adj[2][3]=adj[3][2]=110;
    adj[2][7]=adj[7][2]=120;
    adj[2][8]=adj[8][2]=206;

    adj[3][4]=adj[4][3]=120;
    adj[3][5]=adj[5][3]=121;
    adj[3][7]=adj[7][3]=190;
    adj[3][9]=adj[9][3]=175;

    adj[4][5]=adj[5][4]=45;
    adj[4][9]=adj[9][4]=131;

    adj[5][6]=adj[6][5]=185;
    adj[5][7]=adj[7][5]=274;

    adj[6][7]=adj[7][6]=218;

    adj[7][8]=adj[8][7]=155;

    adj[0][0]=0;
    adj[1][1]=0;
    adj[2][2]=0;
    adj[3][3]=0;
    adj[4][4]=0;
    adj[5][5]=0;
    adj[6][6]=0;
    adj[7][7]=0;
    adj[8][8]=0;
    adj[9][9]=0;
  }
  Graph()
  {
    memset(adj,0,sizeof(adj));
  }
  void cityList() 
  {
    cout<<"\nList of Cites :\n";
    cout<<"1.Thane\n2.Mumbai\n3.Pune\n4.Satara\n5.Kolhapur\n6.Sangli\n7.Solapur\n8.Nagar\n9.Nashik\n10.Ratnagiri\n";
  }
  void cityName(int i)
  {
    switch(i)
    {
      case 1:
        cout<<"     Thane";break;
      case 2:
        cout<<"    Mumbai";break;
      case 3:
        cout<<"      Pune";break;
      case 4:
        cout<<"    Satara";break;
      case 5:
        cout<<"  Kolhapur";break;
      case 6:
        cout<<"    Sangli";break;
      case 7:
        cout<<"   Solapur";break;
      case 8:
        cout<<"     Nagar";break;
      case 9:
        cout<<"    Nashik";break;
      case 10:
        cout<<" Ratnagiri";break;
    }
  }
  void display()
  {
    printf("          ");
    printf("     Thane");
    printf("    Mumbai");
    printf("      Pune");
    printf("    Satara");
    printf("  Kolhapur");
    printf("    Sangli");
    printf("   Solapur");
    printf("     Nagar");
    printf("    Nashik");;
    printf(" Ratnagiri");
    cout<<"\n";
    int i=10;
    cout<<"          ";
    while(i--)
    {
      cout<<"==========";
    }
    cout<<"\n";
    for(int i=0;i<10;i++)
    {
      cityName(i+1);
      for(int j=0;j<10;j++)
      {
        if(adj[i][j]==MAX)
          cout<<"       ---";
        else
          printf("%10d",adj[i][j]);
      }
      cout<<"\n";
    }
  }
  void all_possible_routes_from_city()
  {
    cityList();
    int opt=0;
    while(1)
    {
      cout<<"\nSelect City :";
      cin>>opt;
      if(opt>=1&&opt<=10)
        break;
      cout<<"\nInvalid Input";
    }
    printf("    Source     Destination   Distance(km)\n");
    printf("=========================================");
    for(int i=0;i<10;i++)
    {
      if(i!=opt-1&&(!(adj[opt-1][i]>=MAX)))
      {
        cout<<"\n";cityName(opt);cout<<"->";
        cityName(i+1);
        printf("%13d",adj[opt-1][i]);
      }
    }
  }
  void dijstra(int src,vector<pair<int,vector<int>>>&dis)
  {
    dis[src].first=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push(make_pair(0,src));
    while(!pq.empty())
    {
      int u=pq.top().second;
      for(int i=0;i<10;i++)
      {
        if(i!=u)
        {
          int d=dis[u].first+adj[u][i];
          if(d<dis[i].first)
          {
            dis[i].first=d;
            dis[i].second=dis[pq.top().second].second;
            dis[i].second.push_back(pq.top().second);
            pq.push(make_pair(d,i));
          }
        }
      }
      pq.pop();
    }
  }
  void minPath()
  {
    cityList();
    vector<pair<int,vector<int>>>dis(10);
    for(int i=0;i<10;i++)
    {
      dis[i].first=INT_MAX;
      dis[i].second={};
    }
    int src;
    cout<<"\nSource :";
    while(1)
    {
      cin>>src;
      if(src>=1&&src<=10)
        break;
      cout<<"\nInvalid Input.\nTry Again\nSource:";
    }
    dijstra(src-1,dis);
    for(int i=0;i<10;i++)
    {
      if((i+1)!=src)
        dis[i].second.push_back(i);
    }
    cout<<"\n";
    cout<<"    Source";
    cout<<"          Dest";
    cout<<"     Min Dist(Km)";
    cout<<"  Path";cout<<"\n";
    int i=11;
    while(i--)
    {
      cout<<"==========";
    }
    cout<<"\n";
    for(int i=0;i<10;i++)
    {
      if((i+1)!=src)
      {
        cityName(src);cout<<"  ->";
        cityName(i+1);
        if(dis[i].first!=MAX)
        {
            printf("%11d   ",dis[i].first);
            for(int j=0;j<dis[i].second.size();j++)
            {
              cout<<" ";
              cityName(dis[i].second[j]+1);
              cout<<"->";
            }
        }
        else{
            printf("        ---        No Path");
        }
        cout<<"\n";
      }
    }
  }
  void minPathSrc_dest()
  {
    int src,dest;
    cityList();
    vector<pair<int,vector<int>>>dis(10);
    for(int i=0;i<10;i++)
    {
      dis[i].first=INT_MAX;
      dis[i].second={};
    }
    cout<<"\nSource :";
    while(1)
    {
      cin>>src;
      if(src>=1&&src<=10)
        break;
      cout<<"\nInvalid Input.\nTry Again\nSource: ";
    }
    cout<<"\nDestination :";
    while(1)
    {
      cin>>dest;
      if(dest>=1&&dest<=10)
        break;
      cout<<"\nInvalid Input.\nTry Again\nDestination: ";
    }
    cout<<"\n";
    dijstra(src-1,dis);
    cout<<"\n";
    cout<<"    Source";
    cout<<"          Dest";
    cout<<"     Min Dist(Km)";
    cout<<"  Path";cout<<"\n";
    int i=9;
    while(i--)
    {
      cout<<"==========";
    }
    cout<<"\n";  
    cityName(src);cout<<"  ->";
    cityName(dest);
    if(dis[dest-1].first!=MAX)
    {
      printf("%11d   ",dis[dest-1].first);
      dis[dest-1].second.push_back(dest-1);
      for(int j=0;j<dis[dest-1].second.size();j++)
      {
        cout<<" ";
        cityName(dis[dest-1].second[j]+1);
        cout<<"->";
      }
    }
    else
    {
      printf("        ---        No Path");
    }
  }
  void minPathSrc_inter_dest()
  {
    int src,dest,inter;
    cityList();
    cout<<"\nSourec: ";
    cin>>src;
    cout<<"\nIntermedite: ";
    cin>>inter;
    cout<<"\nDestination: ";
    cin>>dest;
    cout<<"\n";
    cout<<"    Source";
    cout<<"         Inter";
    cout<<"          Dest";
    cout<<"     Min Dist(Km)";
    cout<<"  Path";cout<<"\n";
    int i=10;
    while(i--)
    {
      cout<<"==========";
    }
    cout<<"\n";  
    cityName(src);cout<<"  ->";
    cityName(inter);cout<<"  ->";
    cityName(dest);
    vector<pair<int, vector<int> > >dis(10);
    for(int i=0;i<10;i++)
    {
      dis[i].first=INT_MAX;
      dis[i].second={};
    }
    dijstra(src-1, dis);
    int dist=0;
    dist+=dis[inter-1].first;
    if(dist<=MAX)
    {
      vector<pair<int, vector<int> > >dis1(10);
      for(int i=0;i<10;i++)
      {
        dis1[i].first=INT_MAX;
        dis1[i].second={};
      }
      dijstra(inter-1,dis1);
      dist+=dis1[dest-1].first;
      if(dist<=MAX)
      {
        printf("%11d   ",dist);
        dis[inter-1].second.push_back(inter-1);
        for(int j=0;j<dis[inter-1].second.size();j++)
        { 
          cout<<" ";
          cityName(dis[inter-1].second[j]+1);
          cout<<"->";
        }
        dis1[dest-1].second.push_back(dest-1);
        for(int j=1;j<dis1[dest-1].second.size();j++)
        {
          cout<<" ";
          cityName(dis1[dest-1].second[j]+1);
          cout<<"->";
        }
      }
      else{
        printf("        ---        No Path");
      }
    }
    else{
      printf("        ---        No Path");
    }
  }
  void under_cons()
  {
    cityList();
    int src,dest;
    cout<<"\nSource: ";
    cin>>src;
    cout<<"\nDestination: ";
    cin>>dest;
    adj[src-1][dest-1]=MAX;
    adj[dest-1][src-1]=MAX;
  }
  void newly_cons()
  {
    cityList();
    int src,dest,distance;
    cout<<"\nSource: ";
    cin>>src;
    cout<<"\nDestination: ";
    cin>>dest;
    cout<<"\nDistance: ";
    cin>>distance;
    adj[src-1][dest-1]=distance;
    adj[src-1][dest-1]=distance;
  }
};


void menu(Graph &g,Password &p)
{
  while(1)
  {
    cout<<"\n\nMenu:\n";
    cout<<"============================================================";
    cout<<"\n1.All possible Routes\n2.All possible Routes from Particular city\n3.Minimum Path from a Particular Source to all other Destinations\n4.Minimum Path from Source to Destination\n5.Minimum Path from Source to Destination via Intermediate\n6.Update Routes \n7.Change Password\n0.Exit";
    int opt;
    cout<<"\nSelect Option:";
    cin>>opt;
    switch(opt)
    {
      case 1:
        g.display();break;
      case 2:
        g.all_possible_routes_from_city();break;
      case 3:
        g.minPath();break;
      case 4:
        g.minPathSrc_dest();break;
      case 5:
        g.minPathSrc_inter_dest();break;
      case 6:
        if(confirm(p))
        {
          int opt;
          while(1)
          {
            cout<<"\nMenu:\n1.Update Underonstruction Road\n2.Update Newly created road\n0.Back";
            cout<<"\nChoose Option: ";
            cin>>opt; 
            if(opt==1||opt==2||opt==0)
            {
              break;
            }
            cout<<"\nInvalid Input";
          }
          switch(opt)
          {
            case 1:
              g.under_cons();break;
            case 2:
              g.newly_cons();break;
          } 
        }
        else
          cout<<"\nTry Again";
        break;
      case 7:
        cout<<"\nEnter Old Password: ";
        if(p.check())
        {
          p.changePassword();
        }
        else
          cout<<"\nTry Again";
        break;
    }
    if(opt<0||opt>7)
    {
      cout<<"\nInvalid Input";
      continue;
    }
    else if(opt==0)
    {
      cout<<"\nEnd of Program";
      break;
    }
    char ch;
    cout<<"\nPress E to Erase Data: ";
    cin>>ch;
    if(ch=='E'||ch=='e')
      system("cls");
  }
}
void Varification(Graph &g) {
  int chances=3;
  Password p;
  while(chances--)
  {
    cout<<"\nEnter Password:";
    if(p.check())
    {
      cout<<"\nCorrect Password";
      menu(g,p);
      return;
    }
    else
      cout<<"\nInvalid Password\nYou have "<<chances<<" chances left\n";
  }
  cout<<"\nOops!End of program";
  return;
}
int main()
{
  Graph g;
  g.setting_values();
  Varification(g);
  return 0;
}












