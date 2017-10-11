/*
 * ActorNode.h
 * Author: Jiahao Wang and Alex Chiu
 * Date:   06-06-17
 *
 */
 


#include "ActorNode.h"

// add movie to the movie vector
void ActorNode::addMovie(MovieNode *  movieName){
	movies.push_back(movieName);
}

// getter for name
string ActorNode::getName() const{
	return name;
}

// set the previous actor
void ActorNode::setPrevActor(ActorNode *prev){
	prevActor = prev;
}

// getter for prev actor
ActorNode* ActorNode::getPrevActor(){
	return prevActor;
}

// setter for checked
void ActorNode::setCheck(bool checked){
	check = checked;
}

// getter for checked
bool ActorNode::getCheck(){
	return check;
}

// setter for prev movie
void ActorNode::setPrevMovie(MovieNode *linkedMovie){
	prevMovie = linkedMovie;
}

// getter for prev movie
MovieNode* ActorNode::getPrevMovie(){
	return prevMovie;
}

// getter for movie vector
vector<MovieNode *> ActorNode::getMovies(){
	return movies;
}

ActorNode::~ActorNode(){
}

// operator < for priority queue
bool ActorNode:: operator<(const ActorNode& other){
	if(distance != other.distance){
		return distance > other.distance;
	}
	return name < other.getName();
}
