/*
 * actorconnections.cpp
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <sstream>

#include "ActorGraph.h"
#include "ActorNode.h"
#include "MovieNode.h"
#include "DisjointSet.h"
#include "util.h"

using namespace std;
int main(int argc, char *argv[]){
	char* movie_cast = argv[1];
	string pair_file = argv[2];
	string outputFile = argv[3];
	string search;

	if(argc == 5 ){
		search = argv[4];
	}
	if(search != "bfs"){
		search = "ufind";
	}
	std::ifstream infile(pair_file);
	string line;
	string actor1;
	string actor2;

	std::getline(infile, line);
	vector<tuple<string,string, int>> triplet;
	
	Timer time;

	// get each actor pairs and push into vector
	while( std::getline(infile, line) ){
		actor1 = line.substr( 0, line.find('\t') );
		actor2 = line.substr( actor1.length() + 1, line.length() );
		triplet.push_back(make_tuple(actor1, actor2, 9999));
	}

	
	time.begin_timer();
	// load graph if option is set to bfs
	if(search == "bfs"){
		ActorGraph *graph = new ActorGraph();
	
		//loads from file with actorconnection being true
		//actor nodes are not going to be connected
		if( !(graph -> loadFromFile(movie_cast, false, true) ) ){
			return -1;
		}
		// call bfs connection on triplet vector
		graph->bfsActorconnection(triplet);
		delete graph;
	}
	// load set if option is set to ufind 
	else{
		DisjointSet * set = new DisjointSet();
		if( !(set -> loadFromFile(movie_cast))){
			return -1;
		}
		// call disjoint set connection on triplet vector
		set->unionActorconnection(triplet);
		delete set;
	}
	long totalTime = time.end_timer();
	
	cout << "Total Time for connection is " << totalTime << endl;
	
	// print out results
	ofstream output;
	output.open(outputFile);
	output << "Actor1" << '\t' << "Actor2" << '\t' << "Year" << endl;
	for(int x = 0; x < (int) triplet.size(); x++){
		output << get<0>(triplet[x]) << '\t' << get<1>(triplet[x]) << '\t';
		output << get<2>(triplet[x]) << endl;
	}
}
