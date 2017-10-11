/*
 * ActorGraph.h
 * Author: Jiahao Wang and Jiahao Wang
 * Date:   06-06-17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <queue>
#include "ActorNode.h"
#include "MovieNode.h"
#include <unordered_map>

// Maybe include some data structures here

using namespace std;

class ActorNodePtrComp{
public:
	bool operator()(ActorNode*& lhs, ActorNode*& rhs) const {
		return *lhs < *rhs;
	}
};

class MovieNodePtrComp{
public:
	bool operator()(MovieNode*& lhs, MovieNode*& rhs) const{
		return *lhs < *rhs;
	}
};



class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
		


public:
		
		/****IMPLEMENT A DESTROYER*****/



    ActorGraph(void);
    ~ActorGraph();
		unordered_map<std::string, ActorNode *> actorMap;
		unordered_map<std::string, MovieNode *> movieMap;

		//see which nodes are already checked
		vector<ActorNode *> checkedNodes;  

		//will reinsert nodes back into priority queue
		vector<MovieNode *> poppedMovies;

		priority_queue<MovieNode *, vector<MovieNode *>, MovieNodePtrComp> movieQueue;
		
    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges, bool actorConnection);
  
	  ActorNode * bfsPath(string first, string end);

		ActorNode * dijkstraPath(string first, string end);

		void reset();

		void printPath(ActorNode * end, ofstream &output);

		//returns year that first connection was made with bfs
		void bfsActorconnection(vector<tuple <string, string, int>> &triple);

		//after end of search, will add everything from popped movies back in
		void resetPriorityQueue();
};


#endif // ACTORGRAPH_H
