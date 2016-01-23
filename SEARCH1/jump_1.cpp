/*
A* algorithm on column jump game
Help is taken from the pseudo code given in wikipedia

*/
#include <bits/stdc++.h>
using namespace std;
#define vvi vector< vector<int> >
#define tr(vec,it) for(__typeof(vec.begin()) it = vec.begin();it!=vec.end();++it)
#define rep(i,a,b) for(__typeof(a) i = (a); i < (b) ; i++)
map<vvi, int> g_score;
map<vvi, int> f_score;
set< vvi > closed;
int expanded_nodes=0;
struct transition
{	
	pair<int,int> init;
	pair<int,int> end;
};

map<vvi, pair<vvi,transition> > came_from; // vvi is reached from pair<vvi> with defined transition
int N;
vvi start,goal;
stack<transition> output;

class comparison
{
 
public:

  bool operator() (const vvi& state1, const vvi& state2) const
  {
  	return f_score[state1]>f_score[state2];
  }
};

priority_queue<vvi, std::vector< vvi >, comparison > open;

void printvector(vvi v){

	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
			cout<<v[i][j]<<" ";
		cout<<endl;
	}
	cout<<"\n\n";
}

int goal_check(vvi current){
	int ret = 0;
	rep(i,0,N){
		rep(j,0,N){
			if(current[i][j])
				ret++;
		}
	}
	return ret;
}

int heuristic_cost(vvi state){

	int count=0;
	set<int> color;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(state[i][j]!=0)
				color.insert(state[i][j]);

	return color.size()-1;
}

void reconstruct_path(vvi current){

	while(current!=start){
	    
		transition t;
		t.init=came_from[current].second.init;
		t.end=came_from[current].second.end;
		//cout<<"("<<t.init.first<<","<<t.init.second<<")"<<"-->"<<"("<<t.end.first<<","<<t.end.second<<")"<<endl;

		output.push(t);
		current=came_from[current].first;
	// 	// if(current==start)
	// 	// 	break;
		
	}
}

pair<vvi,transition> get_left(vvi &current, int i, int j){
	int color1,color2,k,tentative_gscore;
	pair <vvi,transition> element;
	vvi neighbor = current;
	if(j>=2 && current[i][j-1] && current[i][j-2]){
		color1 = current[i][j-1];
		k = j-2;
		while(k>=0 && current[i][k]==color1) k--;
	
		if(k>=0){	
			neighbor[i][k] = 0;
			neighbor[i][j] = current[i][k];
			rep(t,k+1,j) neighbor[i][t] = 0;
			transition trans;
			trans.init=make_pair(i,k);
			trans.end=make_pair(i,j);
			element=make_pair(neighbor,trans);
		}
		else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
		}

	}
	else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
	}
	return element;
}

pair<vvi,transition> get_right(vvi &current, int i, int j){
	int color1,color2,k,tentative_gscore;
	pair <vvi,transition> element;
	vvi neighbor = current;
	if(j<=N-3 && current[i][j+1] && current[i][j+2]){
		color1 = current[i][j+1];
		k = j+2;
		while(k<=N-1 && current[i][k]==color1) k++;
	
		if(k<=N-1){	
			
			neighbor[i][k] = 0;
			neighbor[i][j] = current[i][k];
			rep(t,j+1,k) neighbor[i][t] = 0;
			transition trans;
			trans.init=make_pair(i,k);
			trans.end=make_pair(i,j);
			element=make_pair(neighbor,trans);
		}
		else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
		}

	}
	else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
	}
	return element;
}

pair<vvi,transition> get_top(vvi &current, int i, int j){
	int color1,color2,k,tentative_gscore;
	pair <vvi,transition> element;
	vvi neighbor = current;
	if(i>=2 && current[i-1][j] && current[i-2][j]){
		color1 = current[i-1][j];
		k = i-2;
		while(k>=0 && current[k][j]==color1) k--;
	
		if(k>=0){	
			
			neighbor[k][j] = 0;
			neighbor[i][j] = current[k][j];
			rep(t,k+1,i) neighbor[t][j] = 0;
			transition trans;
			trans.init=make_pair(k,j);
			trans.end=make_pair(i,j);
			element=make_pair(neighbor,trans);
		}
		else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
		}

	}
	else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
	}
	return element;
}

pair<vvi,transition> get_bottom(vvi &current, int i, int j){
	int color1,color2,k,tentative_gscore;
	pair <vvi,transition> element;
	vvi neighbor = current;
	if(i<=N-3 && current[i+1][j] && current[i+2][j]){
		color1 = current[i+1][j];
		k = i+2;
		while(k<=N-1 && current[k][j]==color1) k++;
	
		if(k<=N-1){	
			
			neighbor[k][j] = 0;
			neighbor[i][j] = current[k][j];
			rep(t,i+1,k) neighbor[t][j] = 0;
			transition trans;
			trans.init=make_pair(k,j);
			trans.end=make_pair(i,j);
			element=make_pair(neighbor,trans);
		}
		else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
		}

	}
	else{
			transition trans;
			trans.init=make_pair(-1,-1);
			trans.end=make_pair(-1,-1);
			element=make_pair(neighbor,trans);
	}
	return element;
}

void A_star(){

	open.push(start);
	g_score[start]=0;
	f_score[start]=g_score[start]+heuristic_cost(start);
	std::set< vvi >::iterator it1;
	map <vvi,int>::iterator it2;


	while(!open.empty()){
		
		vvi current=open.top();
		//printvector(current);
		if(goal_check(current)==1){
		     return reconstruct_path(current);
		}
		open.pop();

		closed.insert(current);
		vector< pair<vvi,transition> > ngh;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(current[i][j]==0){
					pair<vvi,transition> element;
					element=get_left(current,i,j);
					if(element.second.init.first!=-1)
						ngh.push_back(element);
					
					element=get_right(current,i,j);
					if(element.second.init.first!=-1)
						ngh.push_back(element);
					
					element=get_top(current,i,j);
					if(element.second.init.first!=-1)
						ngh.push_back(element);

					element=get_bottom(current,i,j);
					if(element.second.init.first!=-1)
						ngh.push_back(element);
				}
		expanded_nodes++;
		tr(ngh,it){		
			vvi neighbour=(*it).first;
			//printvector(neighbour);
			it1=closed.find(neighbour);
			if(it1!=closed.end())
			 	continue;
		    int tentative_gscore=g_score[current]+1;
		   
 			bool inopen = (g_score.find(neighbour)==g_score.end());

			if(inopen || tentative_gscore < g_score[neighbour]){
				
				came_from[neighbour] = make_pair(current,(*it).second);
				g_score[neighbour]= tentative_gscore;
				f_score[neighbour]= g_score[neighbour] + heuristic_cost(neighbour);
				open.push(neighbour);
				
 			}

		}

	}

 }

void printpath(){

	while(!output.empty()){
		transition t=output.top();
		cout<<"("<<t.init.first + 1<<","<<t.init.second + 1<<")"<<"-->"<<"("<<t.end.first+1<<","<<t.end.second+1<<")"<<endl;
		output.pop();
	}

}
int main(){

	
	int m,a;
	cin>>N;
	cin>>m;


	for(int i=0;i<N;i++){
		start.push_back(vector<int>());
		for(int j=0;j<N;j++){
			cin>>a;
			start[i].push_back(a);
		}
	}

	A_star();

	cout<<"\n\nNodes expanded "<<expanded_nodes<<endl;
	printpath();


}