/*
 * DisjointSet.cpp
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#include "DisjointSet.h"
#include <sstream>
#include <fstream>

// file parser
bool DisjointSet::loadFromFile(const char* in_filename){
	ifstream infile(in_filename);

	bool have_header = false;

	//keep reading lines until the end of file is reached
	while(infile){
		string s;

		//get next line
		if(!getline(infile, s)) break;
	

		if(!have_header){
			//skip the header
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector <string > record;

		while(ss){
			string next;

			//get the next string before hitting a tab character and put it in 'next'
			if(!getline(ss, next, '\t')) break;
			record.push_back(next);
		}

		if(record.size() != 3){
			//we should have exactly 3 columns
			continue;
		}

		string actor_name(record[0]);
		string movie_title(record[1]);
		int movie_year = stoi(record[2]);
		
		Actor * node;
		MovieNode * film;
		ActorNode * actorNode;

		try{
			node = actorMap.at(actor_name);			
		}
		catch(const std::out_of_range &e){
			node = new Actor(actor_name);
			actorNode = new ActorNode(actor_name);
			actorMap.insert(std::make_pair(actor_name, node));
			actorNodeMap.insert(std::make_pair(actor_name, actorNode));
		}
		
		try{
			film = movieMap.at(movie_title);
		}
		catch(const std::out_of_range& e){
			film = new MovieNode(movie_title, movie_year);
			movieMap.insert(std::make_pair(movie_title,film));
			movieQueue.push(film);
		}
		film->addActor(actorNode);
	}
	if(!infile.eof()){
		cerr << "Failed to read " << in_filename << "!\n";
		return false;
	}
	infile.close();
	return true;
}

DisjointSet::Actor* DisjointSet::find(string name){
	Actor * currNode;
	try{
		currNode = actorMap.at(name);
	}	
	catch(const std::out_of_range &e){
		cerr << "Actor cannot be found" << endl;
		return nullptr;
	}

	Actor *sentinel = currNode;
	//gets the sentinel node
	while(sentinel->parent != nullptr){
		sentinel = sentinel->parent;
	}

	//if only singular node, then return currNode
	if(sentinel == currNode){
		return sentinel;
	}

	//connects every node in path to sentinel node
	Actor *tempNode;
	while(currNode -> parent != nullptr){
		tempNode = currNode;
		currNode = currNode->parent;
		tempNode->parent = sentinel;
	}
	return sentinel;
	
}

void DisjointSet::unionSet(Actor *node1, Actor *node2){
	//if in same set, return 

	if((find(node1->name)->name) == (find(node2->name)->name)){
		return;
	}
	Actor * one = find(node1->name);
	Actor * two = find(node2->name);
	if((one->size) > (two->size)){
		two->parent = one;
		one->size = (two->size) + (one->size);
	}
	else{
		one->parent = two;
		two->size = ((one->size)+ (two->size));
	}
}

// find the actor connection using disjoint set union find, take in a tuple
// of actor1 name , actor2 name, and year to be edited in this function
void DisjointSet::unionActorconnection(vector<tuple<string,string,int>>&triplet){
	while(! (movieQueue.empty())){
		int movieyear = movieQueue.top()->getYear();
		MovieNode* movie = movieQueue.top();

		// for every movie in this year
		while(movieyear== movieQueue.top()->getYear() && !movieQueue.empty()){
			movie = movieQueue.top();
			movieQueue.pop();
			poppedMovies.push_back(movie);
			vector <ActorNode*> actors = movie->getActors();
			
			// connect the actors with other actors with union find w/ movie cast 
			// list
			for(int i = 1; i < (int)actors.size(); i++){
				this->unionSet(actorMap.at(actors[0]->getName()), 
																	actorMap.at(actors[i]->getName()));
			}
		}
		int count = 0;
		// after adding all the connections check if the actors are connected
		// using find
		for(int i = 0 ; i < (int)triplet.size(); i++){
			
			if(std::get<2>(triplet[i]) != 9999){
				count++;
				continue;	
			}
			string actor1 = std::get<0>(triplet[i]);
			string actor2 = std::get<1>(triplet[i]);
			if(this->find(actor1) == this->find(actor2)){
				std::get<2>(triplet[i]) = movieyear;
			}

		}
		// return function if all the years have been found
		if( count == (int)triplet.size()){
			return;
		}
	}
}

// destructor 
DisjointSet::~DisjointSet(){
	for(auto it = actorMap.begin(); it != actorMap.end(); it++){
		delete (*it).second;
	}
	for(auto it = actorNodeMap.begin(); it != actorNodeMap.end(); it++){
		delete (*it).second;
	}
	for(auto it = movieMap.begin(); it != movieMap.end(); it++){
		delete (*it).second;
	}
}
