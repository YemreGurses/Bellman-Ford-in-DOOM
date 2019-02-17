#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Corridor
    {
    	int first_room;
    	int second_room;
    	int cost;
    };

struct Ammoroom
    {
    	int room_number;
    	int ammo_amount;
    };

struct PathwithDistance
	{
		int path_cost;
		vector<int> path;
		int type;
		vector<int> dir;
	};

int ammo; 
int total_rooms;
int chamber_room_number;
int scientistkey_room_number;
int scientist_room_number;

int numberof_oddperiod_locked;
vector<int> oddperiod_rooms;

int numberof_evenperiod_locked;
vector<int> evenperiod_rooms;

int corridor_number;
vector<Corridor> corridors;

int ammo_room_number;
vector<Ammoroom> ammorooms;


vector<int> oddflag;
vector<int> evenflag;

int oddpath_distance, evenpath_distance;

vector<PathwithDistance> pathes;




void readInput(){
	ifstream in("input.inp");

	string str;
 	int i = 0;
 	int iter_corrider = 0;
 	int iter_ammo_room = 0;
	while(getline(in, str)) {
	    // cout << str << endl;
	    if(i==0){
	    	ammo = stoi(str);
	    }
	    else if(i==1){
	    	total_rooms = stoi(str);
	    }
	    else if(i==2){
	    	chamber_room_number = stoi(str);
	    }
	    else if(i==3){
	    	scientistkey_room_number = stoi(str);
	    }
	    else if(i==4){
	    	scientist_room_number = stoi(str);
	    }
	    else if(i==5){
	    	string tmp;
	    	stringstream s(str);
	    	int j = 0;
	    	while(getline(s, tmp, ' ')){
	    		if(j==0){
	    			numberof_oddperiod_locked = stoi(tmp);
	    			j++;
	    		}
	    		else{
	    			oddperiod_rooms.push_back(stoi(tmp));
	    		}
	    	}
	    }
	    else if(i==6){
	    	string tmp;
	    	stringstream s(str);
	    	int j = 0;
	    	while(getline(s, tmp, ' ')){
	    		if(j==0){
	    			numberof_evenperiod_locked = stoi(tmp);
	    			j++;
	    		}
	    		else{
	    			evenperiod_rooms.push_back(stoi(tmp));
	    		}
	    	}

	    }
	    else if(i==7){
	    	corridor_number = stoi(str)*2;
	    }
	    else if(i==8){

	    	string tmp;
	    	stringstream s(str);
	    	int j = 0;
	    	Corridor corr;
	    	Corridor corr2;
	    	while(getline(s, tmp, ' ')){
	    		if(j == 0){
	    			corr.first_room = stoi(tmp);
	    			corr2.second_room = stoi(tmp);
	    			j++;
	    		}
	    		else if(j == 1){
	    			corr.second_room = stoi(tmp);
	    			corr2.first_room = stoi(tmp);
	    			j++;
	    		}
	    		else{
	    			corr.cost = stoi(tmp);
	    			corr2.cost = stoi(tmp);
	    			j++;	
	    		}
	    	}
			corridors.push_back(corr);
			corridors.push_back(corr2);
	    	iter_corrider++;
	    	if(iter_corrider == corridor_number/2){
	    		i++;
	    		continue;
	    	}
	    	continue;
	    }
	    else if(i==9){
	    	ammo_room_number = stoi(str);
	    }
	    else if(i==10){
	    	string tmp;
	    	stringstream s(str);
	    	int j = 0;
	    	Ammoroom ammo_room;
	    	while(getline(s, tmp, ' ')){
	    		if(j == 0){
	    			ammo_room.room_number = stoi(tmp);
	    			j++;
	    		}
	    		else if(j == 1){
	    			ammo_room.ammo_amount = stoi(tmp);
	    			j++;
	    		}
	    	}
			ammorooms.push_back(ammo_room);
	    	iter_ammo_room++;
	    	if(iter_ammo_room == ammo_room_number){
	    		i++;
	    		continue;
	    	}
	    	continue;	    	
	    }
	    i++;
	}
	in.close();
}

void printPath(int oddparent[], int evenparent[], int odddistance[], int evendistance[], int source, int dest){
	int i=dest;
	int temp;
	int yon=0;
	int flag = 1;
	vector<int> myoddpath;
	vector<int> dir;
	dir.push_back(source+1);
	dir.push_back(dest+1);
	// cout << "Last t is odd" << endl;
	while(flag){ //last t is odd case
		myoddpath.push_back(i+1);
		if(yon==0){
			temp = i;
			i = evenparent[i];
			yon = 1;
			if(i==-1) flag = 0;
		}
		else if(yon==1){
			temp = i;
			i = oddparent[i];
			yon = 0;
			if(i==-1) flag = 0;
		}
	}
	if(temp == source){
		oddpath_distance = odddistance[dest];
		reverse(myoddpath.begin(), myoddpath.end());
		PathwithDistance temp_oddpath = {oddpath_distance, myoddpath, 1, dir};
		pathes.push_back(temp_oddpath);
	}
	else{
		oddpath_distance = INT_MAX;
		oddpath_distance = odddistance[dest];
		reverse(myoddpath.begin(), myoddpath.end());
		PathwithDistance temp_oddpath = {oddpath_distance, myoddpath, 1, dir};
		pathes.push_back(temp_oddpath);		
	}


	flag = 1;
	i=dest;
	yon=0;
	vector<int> myevenpath;
	// cout << "Last t is even" << endl;
	while(flag){ //last t is even case
		// cout << i+1 << endl;
		myevenpath.push_back(i+1);
		if(yon==0){
			temp = i;
			i = oddparent[i];
			yon = 1;
			if(i==-1) flag = 0;
		}
		else if(yon==1){
			temp = i;
			i = evenparent[i];
			yon = 0;
			if(i==-1) flag = 0;
		}
	}
	if(temp == source){
		evenpath_distance = evendistance[dest];
		reverse(myevenpath.begin(), myevenpath.end());
		PathwithDistance temp_evenpath = {evenpath_distance, myevenpath, 0, dir};
		pathes.push_back(temp_evenpath);
	}
	else{
		evenpath_distance = INT_MAX;
		reverse(myevenpath.begin(), myevenpath.end());
		PathwithDistance temp_evenpath = {evenpath_distance, myevenpath, 0, dir};
		pathes.push_back(temp_evenpath);		
	}

}

void shortestPath(int odddistance[], int evendistance[], int oddparent[], int evenparent[], int source, int dest, int even_or_odd){
    // Step 1: Initialize distances from src to all other vertices 
    // as INFINITE 
    for (int i = 0; i < total_rooms; i++){ 
        odddistance[i] = INT_MAX; 
        evendistance[i] = INT_MAX; 
    	oddparent[i] = -1;
    	evenparent[i] = -1;
    }
    if(even_or_odd == 1){
    	odddistance[source] = 0; 
    }
    else{
    	evendistance[source] = 0;
    }

    for (int i = 0; i < total_rooms-1; i++) 
    { 
        for (int j = 0; j < corridors.size(); j++) 
        { 
            int u = corridors[j].first_room-1;
            int v = corridors[j].second_room-1;
            int weight = corridors[j].cost;
            if (odddistance[u] != INT_MAX && odddistance[u] + weight < evendistance[v] && evenflag[v] == 1) //u odd - v even
            { 
  			  	evendistance[v] = odddistance[u] + weight;
				oddparent[v] = u; 
            }
            if (evendistance[u] != INT_MAX && evendistance[u] + weight < odddistance[v] && oddflag[v] == 1) //u even - v odd
            {           	
                odddistance[v] = evendistance[u] + weight;
                evenparent[v] = u; 
            }
        } 
    }


    printPath(oddparent, evenparent, odddistance, evendistance, source, dest);
   
} 

int main()
{
	readInput();
	int i,j;

	int oddparent[total_rooms];
	int evenparent[total_rooms];
	int odddist[total_rooms];
	int evendist[total_rooms];


	vector<int> locked_rooms;


    std::sort(oddperiod_rooms.begin(), oddperiod_rooms.end());
    std::sort(evenperiod_rooms.begin(), evenperiod_rooms.end());
 
    std::set_intersection(oddperiod_rooms.begin(), oddperiod_rooms.end(), 
    					  evenperiod_rooms.begin(), evenperiod_rooms.end(), 
    					  std::back_inserter(locked_rooms));

    for(int a=0; a<locked_rooms.size(); a++){ //removing always locked doors
    	for(int b=0; b<corridors.size(); b++){
    		if(locked_rooms[a] == corridors[b].first_room || locked_rooms[a] == corridors[b].second_room){
    			corridors.erase(corridors.begin()+b);
    			b--;
    		}
    	}
    }

    for(int i = 0; i < total_rooms; i++){  //creating vectors for locked rooms
    	oddflag.push_back(1);
    	evenflag.push_back(1);
    }

    for(int i = 0; i < numberof_oddperiod_locked; i++){ //setting the flags for odd locked rooms
    	oddflag[oddperiod_rooms[i]-1] = 0;
    }
    for(int i = 0; i < numberof_evenperiod_locked; i++){ //setting the flags for even locked rooms
    	evenflag[evenperiod_rooms[i]-1] = 0;
    }
    



	if(ammo_room_number==0){
		shortestPath(odddist, evendist, oddparent, evenparent, 0, scientistkey_room_number-1, 1);//start with odd

		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 0);

		int final_cost[8] = {INT_MAX};
		final_cost[0] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost;
		final_cost[1] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost;
		final_cost[2] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost;
		final_cost[3] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost;

		final_cost[4] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost;
		final_cost[5] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost;
		final_cost[6] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost;
		final_cost[7] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost;

		for(int i = 0; i<8; i++){ //prevent overflow
		    if(final_cost[i] < -1000){
		    	final_cost[i] = INT_MAX;
		    }
		    
		} 


		int temp = INT_MAX;
		int shortest_index;
		for(int iter = 0; iter < 8; iter++){
			if(final_cost[iter] < temp){
				temp = final_cost[iter];
				shortest_index = iter;
			}
		}


		vector<int> final_path;
		for(int i = 0; i<pathes[shortest_index/4].path.size()-1; i++){
		    final_path.push_back(pathes[shortest_index/4].path[i]);
		    // cout << pathes[shortest_index/4].path[i] << " ";
		}

		for(int i = 0; i<pathes[shortest_index/2 + 2].path.size()-1; i++){
			final_path.push_back(pathes[shortest_index/2 + 2].path[i]);
		    // cout << pathes[shortest_index/2 + 2].path[i] << " ";
		}

		for(int i = 0; i<pathes[(shortest_index%4) + 6].path.size(); i++){
		    final_path.push_back(pathes[(shortest_index%4) + 6].path[i]);
		    // cout << pathes[(shortest_index%4) + 6].path[i] << " ";
		}
		vector<int> bos{ 0 , 0 };
		PathwithDistance path = {final_cost[shortest_index], final_path, 1, bos};

		
		ofstream outfile ("output.out");

		outfile << ammo - path.path_cost << endl;
		outfile << path.path.size() << endl;
		for(int i = 0; i<path.path.size(); i++){
			outfile << path.path[i] << " ";
		}
		outfile << endl;

		outfile.close();		

	}
	else if(ammo_room_number==1 || ammo_room_number==2){
		//NO AMMO CASE
		shortestPath(odddist, evendist, oddparent, evenparent, 0, scientistkey_room_number-1, 1);//start with odd

		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 0);

		int final_cost[8] = {INT_MAX};
		final_cost[0] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost;
		final_cost[1] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost;
		final_cost[2] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost;
		final_cost[3] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost;

		final_cost[4] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost;
		final_cost[5] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost;
		final_cost[6] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost;
		final_cost[7] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost;

		for(int i = 0; i<8; i++){ //prevent overflow
		    if(final_cost[i] < -1000){
		    	final_cost[i] = INT_MAX;
		    }		    
		} 
		int temp = INT_MAX;
		int shortest_index;
		for(int iter = 0; iter < 8; iter++){
			if(final_cost[iter] < temp){
				temp = final_cost[iter];
				shortest_index = iter;
			}
		}

		vector<int> final_path;
		for(int i = 0; i<pathes[shortest_index/4].path.size()-1; i++){
		    final_path.push_back(pathes[shortest_index/4].path[i]);
		    // cout << pathes[shortest_index/4].path[i] << " ";
		}

		for(int i = 0; i<pathes[shortest_index/2 + 2].path.size()-1; i++){
			final_path.push_back(pathes[shortest_index/2 + 2].path[i]);
		    // cout << pathes[shortest_index/2 + 2].path[i] << " ";
		}

		for(int i = 0; i<pathes[(shortest_index%4) + 6].path.size(); i++){
		    final_path.push_back(pathes[(shortest_index%4) + 6].path[i]);
		    // cout << pathes[(shortest_index%4) + 6].path[i] << " ";
		}
		vector<int> bos{ 0 , 0 };
		PathwithDistance path1 = {final_cost[shortest_index], final_path, 1, bos};
		final_path.clear();
		pathes.clear();



		//AMMO BETWEEN 0 AND K CASE
		shortestPath(odddist, evendist, oddparent, evenparent, 0, ammorooms[0].room_number-1, 1);//ammo		

		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, scientistkey_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, scientistkey_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 0);

		int final_cost1a[16] = {INT_MAX};
		final_cost1a[0] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1a[1] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1a[2] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1a[3] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1a[4] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1a[5] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1a[6] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1a[7] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		final_cost1a[8] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1a[9] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1a[10] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1a[11] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1a[12] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1a[13] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1a[14] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1a[15] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		for(int i = 0; i<16; i++){ //prevent overflow
		    if(final_cost1a[i] < -1000){
		    	final_cost1a[i] = INT_MAX;
		    }		   
		} 
		temp = INT_MAX;
		// int shortest_index;
		for(int iter = 0; iter < 16; iter++){
			if(final_cost1a[iter] < temp){
				temp = final_cost1a[iter];
				shortest_index = iter;
			}
		}


		// cout << shortest_index/8 << endl;
		// cout << shortest_index/4 + 2 << endl;
		// cout << ((shortest_index/2)%4) + 6 << endl;
		// cout << (shortest_index%4) + 10 << endl;

		for(int i = 0; i<pathes[shortest_index/8].path.size()-1; i++){
		    final_path.push_back(pathes[shortest_index/8].path[i]);
		    // cout << pathes[shortest_index/8].path[i] << " ";
		}

		for(int i = 0; i<pathes[shortest_index/4 + 2].path.size()-1; i++){
		   	final_path.push_back(pathes[shortest_index/4 + 2].path[i]);
		   	// cout << pathes[shortest_index/4 + 2].path[i] << " ";
		}

		for(int i = 0; i<pathes[((shortest_index/2)%4) + 6].path.size()-1; i++){
		   	final_path.push_back(pathes[((shortest_index/2)%4) + 6].path[i]);
		   	// cout << pathes[((shortest_index/2)%4) + 6].path[i] << " ";
		}
		for(int i = 0; i<pathes[(shortest_index%4) + 10].path.size(); i++){
		   	final_path.push_back(pathes[(shortest_index%4) + 10].path[i]);
		   	// cout << pathes[(shortest_index%4) + 10].path[i] << " ";
		}
		
		PathwithDistance path2 = {final_cost1a[shortest_index]-ammorooms[0].ammo_amount, final_path, 1, bos};
		final_path.clear();
		pathes.clear();


		//AMMO BETWEEN K AND S CASE

		shortestPath(odddist, evendist, oddparent, evenparent, 0, scientistkey_room_number-1, 1);

		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, ammorooms[0].room_number-1, 1); //ammo		
		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, ammorooms[0].room_number-1, 0); //ammo		

		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, scientist_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, scientist_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, chamber_room_number-1, 0);

		int final_cost1b[16] = {INT_MAX};
		final_cost1b[0] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1b[1] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1b[2] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1b[3] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1b[4] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1b[5] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1b[6] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1b[7] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		final_cost1b[8] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1b[9] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1b[10] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1b[11] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1b[12] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1b[13] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1b[14] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1b[15] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		for(int i = 0; i<16; i++){ //prevent overflow
		    if(final_cost1b[i] < -1000){
		    	final_cost1b[i] = INT_MAX;
		    }		   
		} 
		temp = INT_MAX;
		// int shortest_index;
		for(int iter = 0; iter < 16; iter++){
			if(final_cost1b[iter] < temp){
				temp = final_cost1b[iter];
				shortest_index = iter;
			}
		}



		for(int i = 0; i<pathes[shortest_index/8].path.size()-1; i++){
		    final_path.push_back(pathes[shortest_index/8].path[i]);
		    // cout << pathes[shortest_index/8].path[i] << " ";
		}

		for(int i = 0; i<pathes[shortest_index/4 + 2].path.size()-1; i++){
		   	final_path.push_back(pathes[shortest_index/4 + 2].path[i]);
		   	// cout << pathes[shortest_index/2 + 2].path[i] << " ";
		}

		for(int i = 0; i<pathes[((shortest_index/2)%4) + 6].path.size()-1; i++){
		   	final_path.push_back(pathes[((shortest_index/2)%4) + 6].path[i]);
		   	// cout << pathes[((shortest_index/2)%4) + 6].path[i] << " ";
		}
		for(int i = 0; i<pathes[(shortest_index%4) + 10].path.size(); i++){
		   	final_path.push_back(pathes[(shortest_index%4) + 10].path[i]);
		   	// cout << pathes[(shortest_index%4) + 10].path[i] << " ";
		}
		
		PathwithDistance path3 = {final_cost1b[shortest_index]-ammorooms[0].ammo_amount, final_path, 1, bos};
		final_path.clear();
		pathes.clear();

		//AMMO BETWEEN S AND C CASE

		shortestPath(odddist, evendist, oddparent, evenparent, 0, scientistkey_room_number-1, 1);	

		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, scientistkey_room_number-1, scientist_room_number-1, 0);

		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, ammorooms[0].room_number-1, 1); //ammo		
		shortestPath(odddist, evendist, oddparent, evenparent, scientist_room_number-1, ammorooms[0].room_number-1, 0); //ammo	

		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, chamber_room_number-1, 1);
		shortestPath(odddist, evendist, oddparent, evenparent, ammorooms[0].room_number-1, chamber_room_number-1, 0);

		int final_cost1c[16] = {INT_MAX};
		final_cost1c[0] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1c[1] = pathes[0].path_cost + pathes[2].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1c[2] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1c[3] = pathes[0].path_cost + pathes[2].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1c[4] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1c[5] = pathes[0].path_cost + pathes[3].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1c[6] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1c[7] = pathes[0].path_cost + pathes[3].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		final_cost1c[8] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[10].path_cost;
		final_cost1c[9] = pathes[1].path_cost + pathes[4].path_cost + pathes[6].path_cost + pathes[11].path_cost;
		final_cost1c[10] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[12].path_cost;
		final_cost1c[11] = pathes[1].path_cost + pathes[4].path_cost + pathes[7].path_cost + pathes[13].path_cost;
		final_cost1c[12] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[10].path_cost;
		final_cost1c[13] = pathes[1].path_cost + pathes[5].path_cost + pathes[8].path_cost + pathes[11].path_cost;
		final_cost1c[14] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[12].path_cost;
		final_cost1c[15] = pathes[1].path_cost + pathes[5].path_cost + pathes[9].path_cost + pathes[13].path_cost;

		for(int i = 0; i<16; i++){ //prevent overflow
		    if(final_cost1c[i] < -1000){
		    	final_cost1c[i] = INT_MAX;
		    }		   
		} 
		temp = INT_MAX;
		// int shortest_index;
		for(int iter = 0; iter < 16; iter++){
			if(final_cost1c[iter] < temp){
				temp = final_cost1c[iter];
				shortest_index = iter;
			}
		}



		for(int i = 0; i<pathes[shortest_index/8].path.size()-1; i++){
		    final_path.push_back(pathes[shortest_index/8].path[i]);
		    // cout << pathes[shortest_index/8].path[i] << " ";
		}

		for(int i = 0; i<pathes[shortest_index/4 + 2].path.size()-1; i++){
		   	final_path.push_back(pathes[shortest_index/4 + 2].path[i]);
		   	// cout << pathes[shortest_index/2 + 2].path[i] << " ";
		}

		for(int i = 0; i<pathes[((shortest_index/2)%4) + 6].path.size()-1; i++){
		   	final_path.push_back(pathes[((shortest_index/2)%4) + 6].path[i]);
		   	// cout << pathes[((shortest_index/2)%4) + 6].path[i] << " ";
		}
		for(int i = 0; i<pathes[(shortest_index%4) + 10].path.size(); i++){
		   	final_path.push_back(pathes[(shortest_index%4) + 10].path[i]);
		   	// cout << pathes[(shortest_index%4) + 10].path[i] << " ";
		}
			
		PathwithDistance path4 = {final_cost1c[shortest_index]-ammorooms[0].ammo_amount, final_path, 1, bos};
		final_path.clear();
		pathes.clear();


		//CHOSING THE BEST PATH


		vector<PathwithDistance> leastcostpathes;
		leastcostpathes.push_back(path1);
		leastcostpathes.push_back(path2);
		leastcostpathes.push_back(path3);
		leastcostpathes.push_back(path4);


		int outputpath;
		int min_cost = INT_MAX;
		for(int i = 0; i<leastcostpathes.size(); i++){
			if(leastcostpathes[i].path_cost < min_cost){
				min_cost = leastcostpathes[i].path_cost;
				outputpath = i;
			}
		}

		ofstream outfile ("output.out");
		
		outfile << ammo - leastcostpathes[outputpath].path_cost << endl;
		outfile << leastcostpathes[outputpath].path.size() << endl;
		for(int i = 0; i<leastcostpathes[outputpath].path.size(); i++){
			outfile << leastcostpathes[outputpath].path[i] << " ";
		}
		outfile << endl;
		
		outfile.close();



	}





	return 0;
}