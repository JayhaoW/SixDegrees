#include <fstream>
#include <sstream>


#include "Twitter.h"


using namespace std;
void Twitter::loadGraph(const char* in_filename){
	ifstream infile;
	infile.open(in_filename);

	bool have_header = false;

	while(infile){
		string s;

		if( !(getline(infile, s)) ) break;

		if(!have_header){
			have_header = true;
			continue;
		}

		istringstream ss( s );
		vector<string> record;

		while(ss){
			string next;

			if(!getline(ss, next, '\t')) break;

			record.push_back(next);
		}

		if(record.size() != 2){
			continue;
		}

		string name1(record[0]);
		string name2(record[1]);
	
		User * user1;
		try{
			user1 = userMap.at(name1);
		}
		catch(const std::out_of_range &e){
			user1 = new User(name1);
			userMap.insert(make_pair(name1, user1));
			vertices.push(user1);
		}

		User * user2;
		try{
			user2 = userMap.at(name2);
		}
		catch(const std::out_of_range &e){
			user2 = new User(name2);
			userMap.insert(make_pair(name2, user2));
			vertices.push(user2);
		}

		user1->retweets.push_back(user2);
	
	}
}

void Twitter::DFS(std::stack<User *> &finished){
	User * user;
	while(!(vertices.empty())){
		user = vertices.top();	
		vertices.pop();
		if(user -> visited == false){
			
			DFSvisit(user, finished);			
		}
	}	
}

void Twitter::DFSvisit(User *username, std::stack<User *> &finished){
	username->visited = true;
	User * currUser;
	for(int x = 0; x < (int) username->retweets.size(); x++){
		currUser= (username->retweets)[x];
		if(currUser->visited == false){
			DFSvisit(currUser, finished);
		}
	}
	finished.push(username);
}

int Twitter::getGroups(){
	return totalGroups;
}

void Twitter::flip(){
	User * currUser;
	for(auto it = userMap.begin(); it != userMap.end(); it++){
		currUser = (*it).second;
		User * nextUser;
		for(int x = 0; x < (int)currUser->retweets.size(); x++){
			nextUser = currUser->retweets[x];
			
			if(nextUser->flipped == true){
				continue;
			}
			
			bool exists = false;
			for(int y = 0; y < (int) nextUser->retweets.size(); y ++){
				if(currUser == nextUser->retweets[y]){
					exists = true;
					break;
				}
			}
			if(exists == false){
				nextUser->retweets.push_back(currUser);
				currUser->retweets.erase(currUser->retweets.begin() + x);
			}
		}
		currUser->flipped = true;
	}
}
