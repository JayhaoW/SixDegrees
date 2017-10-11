/*
 * pathfinder.cpp
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <sstream>

#include "ActorGraph.h"
#include "ActorNode.h"
#include "MovieNode.h"

using namespace std;

int main(int argc, char * argv[]){
	const char* movie_file = argv[1];
	string weighted = argv[2];
	string test_pair = argv[3];
	string output_file = argv[4];

	
	ofstream output;
	output.open(output_file);

	ActorGraph *graph = new ActorGraph();


	//loads from file accordingly
	//if fail, return -1 for error
	if( !(graph -> loadFromFile( movie_file, weighted == "w", false)) ){
			return -1;
	}

	//opens test pair
	std::ifstream infile(test_pair);
	string line;
	string actor1;
	string actor2;
	
	std::getline(infile, line);


	//reads line by line
	output << "(actor)--[movie#@year]-->(actor)--..." << endl;
	while(std::getline(infile, line) ){
		//gets name of first actor
		actor1 = line.substr(0, line.find('\t') );
		
		//gets name of second actor
		actor2 = line.substr(actor1.length() + 1, line.length());
		
		ActorNode * found;
		if(weighted == "u"){
			found = graph -> bfsPath(actor1, actor2);
		}
		else if( weighted == "w"){
			found = graph -> dijkstraPath(actor1, actor2);	
		}
		if(found == nullptr){
			return -1;
		}
		else if(found->getName() == "NOLINK"){
			cout << "NO LINK FOUND" << endl;
			return -1;
		}

		graph->printPath(found, output);
		output << endl;
		graph->reset();
	}
	delete graph;
	infile.close();
	output.close();
}
