/*
 * ActorGraph.cpp
 * Author: Jiahao Wang and Alex Chiu
 * Date:  06/06/17
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <sstream>
#include "ActorGraph.h"


using namespace std;

ActorGraph::ActorGraph(void) {}

bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges, bool actorConnection) {
    // Initialize the file stream
    ifstream infile(in_filename);

    bool have_header = false;
  
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;
    
        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;
      
            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }
    
        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
    
        // we have an actor/movie relationship, now what?
    		
				ActorNode *actor;
				MovieNode *film;

				//checks if actor node is already created
				//tries to get actor with key
				try{
					actor = actorMap.at(actor_name);
				}
				//catches out of range exception if it does not exist
				catch(const std::out_of_range& e){
					//cout << actor_name << endl;
					actor = new ActorNode(actor_name);
					actorMap.insert(std::make_pair(actor_name, actor));
				}
				
				//title of movie and key are the same
				string movie = movie_title.append("#@");
				movie.append(record[2]);

				//tries to get movie with key
				try{
					film = movieMap.at(movie);
				}
				//catches out of range exception if it does not exist
				catch(const std::out_of_range& e){
					//cout << movie << endl;
					film = new MovieNode(movie, movie_year); 
					movieMap.insert(std::make_pair(movie, film));
					
					//adds movie to priority queue (based on year)
					movieQueue.push(film);
				}

				//add films to actors vector
				//adds actor to film vector
				//if false, don't update actors movies
				if(actorConnection == false){
					actor->addMovie(film);
				}
				film->addActor(actor);
				

				//for actor connection, add another input boolean variable
				//if true, load graph normally
				//if false, don't update actor's movies 
				//also, create a priority queue to store movies based on year it was created
				//pop off movies of a certain year and try to find path,
				//keep popping off movies from certain years until path is found, then print

		
		}

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();

    return true;
		
		}

// Find connection between first actor and end actor and return pointer to end actorNode
// if no connection found return node with "NOLINK"
ActorNode* ActorGraph::bfsPath(string first, string end){	

	ActorNode *currNode;
	
	//tries to get actor node
	try{
		currNode = actorMap.at(first);
	}
	//catches error if node does not exist
	//sets end pointer to nullptr
	catch(const std::out_of_range& e){
		std::cout<<"Actor Name Does Not Exist In List" << endl;
		return nullptr;
	}

	currNode -> setCheck(true);
	
	//intializes a queue a actor nodes
	std::queue<ActorNode *> actorQueue;
	actorQueue.push(currNode);

	// keep a list of checked node so we can reset the node for each bfs
	checkedNodes.push_back(currNode);

	while(! (actorQueue.empty()) ){
		currNode = actorQueue.front();
		actorQueue.pop();

		vector<MovieNode *> actorMovies = currNode->getMovies();
	
		//goes through list of movies actor has been in
		for(int x = 0; x < (int) actorMovies.size(); x++){
			
			MovieNode * currMovie = actorMovies[x];

			vector<ActorNode *> actorsInMovie = currMovie -> getActors();
		
			//goes through list of actors in movie
			for(int y = 0; y < (int) actorsInMovie.size(); y ++){
			
				ActorNode * nextActor = actorsInMovie[y];

				//checks if actors in node has already been checked
				//if it is, continue to next actor
				if(nextActor->getCheck()){
					continue;
				}
				
				// set prev actor, distance, checked
				nextActor -> distance = currNode -> distance + 1;
				nextActor -> setPrevActor(currNode);
				nextActor -> setCheck(true);
				actorQueue.push(nextActor);
				nextActor -> setPrevMovie(currMovie);
				checkedNodes.push_back(nextActor);
				
				//if actor matches end actor
				//return
				if(end == nextActor->getName()){
					return nextActor;
				}
			}
		}
	}

	ActorNode * noLink = new ActorNode("NOLINK");
	return noLink;
}

//resets the checkedNodes
void ActorGraph::reset(){
	ActorNode * checked;
	for(int x = 0; x < (int) checkedNodes.size(); x++){
		checked = checkedNodes[x];
		checked->setPrevActor(nullptr);
		checked->setPrevMovie(nullptr);
		checked->setCheck(false);
		checked->distance = INT_MAX;
	}
}

//prints the path 
void ActorGraph::printPath(ActorNode * end, ofstream &output){
	vector<string> print;

	ActorNode * currNode = end;
	



	//concatenates string together to create format
	std::stringstream ss0;
	ss0 << "(" << currNode -> getName() << ")";
	//cout << currNode-> getName() << endl;

	print.push_back(ss0.str());

	//follows path and prints the movie and actors
	while((currNode -> getPrevActor()) != nullptr){
		std::stringstream ss;
		ss << "[" << currNode->getPrevMovie() -> getName() << "]" << "-->";
		//cout << currNode->getPrevMovie() -> getName() << endl;
		print.push_back(ss.str());

		std::stringstream stream;
		currNode = currNode -> getPrevActor();
		stream << "(" << (currNode -> getName()) << ")" << "--";
		print.push_back(stream.str());
	}

	//itereates through the vector and prints in reverse order
	for(int i = print.size() - 1; i >= 0; i--){
		output << print[i];
	}
}

// find connection between first actor and end actor using dijkstra and return a pointer
// to the end actor;
ActorNode * ActorGraph::dijkstraPath(string first, string end){

	ActorNode * start;
	ActorNode * found;

	// see if actors are in the hashmap
	try{
		start = actorMap.at(first);
		found = actorMap.at(end);
	}
	catch(const std::out_of_range& e){
		std::cout<<"Actor Name Does Not Exist In List" << endl;
		return nullptr;
	}

	// queue for dijkstra
	std::priority_queue<ActorNode *, std::vector<ActorNode *>, ActorNodePtrComp> queue;

	start->distance = 0;
	queue.push(start);

	ActorNode * curr;

	//keeps popping from queue
	while( !(queue.empty()) ){
		curr = queue.top();
		queue.pop();
		checkedNodes.push_back(curr);

		//if check is not true
		if( !(curr->getCheck()) ){
			curr->setCheck(true);

			//gets list of movies from popped node
			//and traverses it
			vector<MovieNode *> listOfMovies = curr->getMovies();
			for(int x = 0; x < (int) listOfMovies.size(); x++){
				vector<ActorNode *> listOfActors = listOfMovies[x]->getActors();
				ActorNode * nextActor;
				
				//gets weighted path to next Actor
				int addedWeight = curr->distance + (listOfMovies[x]->getWeight() );
				
				//traverses through list of actors
				for(int y = 0; y < (int) listOfActors.size(); y ++){
					nextActor = listOfActors[y];

					//if new shorter path to next Actor is found, update info
					if(addedWeight < nextActor->distance){
						nextActor->distance = addedWeight;
						nextActor->setPrevActor(curr);
						nextActor->setPrevMovie(listOfMovies[x]);
						queue.push(nextActor);
					}
				}
			}
		}
	}

	return found;
}

// find actor connection using bfs after adding movies from each year
// accepts a vector of tuple containing actor1, actor2, and year of their first
// connection year of their first connection field is initally 9999, 
// it is to be changed in this method
void ActorGraph::bfsActorconnection(vector<tuple<string,string,int>>&triplet ){

	while( !(movieQueue.empty()) ){
		int movieyear = movieQueue.top() -> getYear();
		MovieNode* movie = movieQueue.top();
		
		//add all movies from this year		
		while(movieyear== movieQueue.top()->getYear() && !movieQueue.empty()){
			movie = movieQueue.top();
			movieQueue.pop();
			poppedMovies.push_back(movie);
			vector <ActorNode*> actors = movie->getActors();
			// add movie to each of actor's movie list
			for(int i = 0; i < (int)(actors.size()); i++){
				actors[i]->addMovie(movie);		
			}
		}
		int count = 0;
		// for each actor use bfs to check if there's a connection after 
		// the movies of the year are added
		for(int i = 0; i < (int)triplet.size(); i++){
			if(std::get<2>(triplet[i]) != 9999){
				count++;
				continue;
			}
			string actor1 = std::get<0>(triplet[i]);
			string actor2 = std::get<1>(triplet[i]);
			ActorNode* actor = this->bfsPath(actor1, actor2);
			// change the year connected field if there's a connection between the
			// two actors
			if((actor != nullptr )&& (actor->getName() != "NOLINK")){
				std::get<2>(triplet[i]) = movieyear;
			}
			this->reset();
		}
		// if all the actors's connected years are found, end function
		if(count ==(int)triplet.size()){
			return;
		}
	}	
	
}

// reset the priority queue of movies of different years
void ActorGraph::resetPriorityQueue(){
	for(int x = 0; x < (int)poppedMovies.size(); x++){
		movieQueue.push(poppedMovies[x]);
	}
	poppedMovies.clear();
}

// destructor 
ActorGraph::~ActorGraph(){
	for(auto it = actorMap.begin(); it != actorMap.end(); it++){
		delete (*it).second;
	}
	for(auto it = movieMap.begin(); it != movieMap.end(); it++){
		delete (*it).second;
	}
}
