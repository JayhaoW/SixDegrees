/*
 * ActorGraph.h
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#ifndef ACTORNODE_H
#define ACTORNODE_H

#include <vector>
#include <string>
#include "limits.h"
//#include "MovieNode.h"

using namespace std;

class MovieNode;
class ActorNode{


private:
	string name;
	vector<MovieNode *> movies;
	ActorNode *prevActor;
	MovieNode *prevMovie;
	bool check = false;

	
	

public:
	int distance = INT_MAX;
	
	ActorNode(string actorName) : name(actorName), prevActor(nullptr), 
																prevMovie(nullptr){}

	//adds movie to actors vector
	void addMovie(MovieNode* movieName);

	//gets name of actor
	string getName() const;

	//sets pointer to previous node
	void setPrevActor(ActorNode *prev);

	//gets previous node
	ActorNode* getPrevActor();
	
	//set check boolean
	void setCheck(bool checked);

	//get check boolean
	bool getCheck();

	void setPrevMovie( MovieNode *linkedMovie);

	MovieNode* getPrevMovie();

	//returns vector of movies 
	vector<MovieNode *> getMovies();

	~ActorNode();

	bool operator<(const ActorNode& other);
};

#endif 
