/*
 * DisjointSet.h
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 *
 */

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <iostream>
#include <unordered_map>
#include "ActorNode.h"
#include "MovieNode.h"
#include "ActorGraph.h"

using namespace std;

class DisjointSet{
private:

public:

  class Actor{
		public:
			string name;
			Actor * parent;
			int size;

			Actor(string Actorname): name(Actorname), parent(nullptr), size(1){}

	};

  ~DisjointSet();

  vector<MovieNode *> poppedMovies;

	unordered_map<std::string, Actor *> actorMap;

  unordered_map<std::string, ActorNode*> actorNodeMap;
	unordered_map<std::string, MovieNode *> movieMap;
	std::priority_queue<MovieNode *, std::vector<MovieNode *>, 
												MovieNodePtrComp> movieQueue;

	bool loadFromFile(const char* in_filename);
	
	
	Actor* find(string name);

	void unionSet(Actor * node1, Actor *node2);
  
  void unionActorconnection(vector<tuple<string,string,int>>&triplet);
};

#endif
