/*
IDA* algorithm on column jump game
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


int N;
vvi start,goal;
vector<transition> trans_vec;

int nodesss(vvi current){
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

pair<vvi,transition> get_left(vvi &current, int i, int j){
	int color1,color2,k,tantative_g;
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
	int color1,color2,k,tantative_g;
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
	int color1,color2,k,tantative_g;
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
	int color1,color2,k,tantative_g;
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





int Search(vvi state,int g,int bound){
	expanded_nodes++;
	int f=g+heuristic_cost(state);

	if(f>bound) return f;
	if(nodesss(state)==1)
		return 0;
	int min=INT_MAX;

	vector< pair<vvi,transition> > ngh;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			if(state[i][j]==0){
				pair<vvi,transition> element;
				element=get_left(state,i,j);
				if(element.second.init.first!=-1)
					ngh.push_back(element);
				
				element=get_right(state,i,j);
				if(element.second.init.first!=-1)
					ngh.push_back(element);
				
				element=get_top(state,i,j);
				if(element.second.init.first!=-1)
					ngh.push_back(element);

				element=get_bottom(state,i,j);
				if(element.second.init.first!=-1)
					ngh.push_back(element);
			}

	tr(ngh,it){		
		vvi neighbour=(*it).first;
		int t=Search(neighbour,g+1,bound);
		if(t==0){
			trans_vec.push_back((*it).second);
			return 0;
		}
		else if(t<min)
			min=t;
	}
	return min;
}

int IDA_star(){

	int bound=heuristic_cost(start);
	while(1){

		int t=Search(start,0,bound);
		if(t==0)
			return 0;
		else if (t==INT_MAX)
			return 1;
		bound=t;
	}
}


void printpath(){

	for(int i=trans_vec.size()-1;i>=0;i--)
		cout<<"("<<trans_vec[i].init.first + 1<<","<<trans_vec[i].init.second + 1<<")"<<"-->"<<"("<<trans_vec[i].end.first+1<<","<<trans_vec[i].end.second+1<<")"<<endl;

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

	IDA_star();
	cout<<"\nNodes expanded "<<expanded_nodes<<endl<<endl;
	printpath();


}