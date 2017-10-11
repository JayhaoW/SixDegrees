/*
 * MovieNode.h
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 */
 
#include "MovieNode.h"

void MovieNode::addActor(ActorNode * actor){
	actors.push_back(actor);
}

string MovieNode::getName() const{
	return name;
}

vector<ActorNode*> MovieNode::getActors(){
	return actors;
}

int MovieNode::getYear() const{
	return year;
}

int MovieNode::getWeight(){
	return weight;
}

bool MovieNode::operator<(const MovieNode& other){
	if(year != other.getYear()){
		return year > other.getYear();
	}
	return name < other.getName();
}
