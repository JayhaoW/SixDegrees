/*
 * MovieNode.h
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#ifndef MOVIENODE_H
#define MOVIENODE_H

#include<string>
#include <vector>
//#include "ActorNode.h"

using namespace std;

class ActorNode;
class MovieNode{
 
private: 
  string name;
  vector<ActorNode *> actors;
	int year;
	int weight;

public:
  MovieNode(string movieName, int date): name(movieName), year(date){
		weight = 1 + (2015 - year);
	}

  // getter for name
  string getName() const;

	int getYear() const;

  // add actor to its cast list
  void addActor(ActorNode * actor);
  
  // return vector of cast list
  vector<ActorNode* > getActors();

	int getWeight();

	bool operator<(const MovieNode& other);
};

#endif
