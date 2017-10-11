#include <string>
#include <vector>
#include <stack>
#include <unordered_map>


using namespace std;
class Twitter{
private:
	class User{
	public:
		string name;
		vector<User *> retweets;
		bool visited;
		bool flipped;

		User(string user) :name(user) {
			visited = false;
		}
	};

	int totalGroups = 0;

	std::stack<User *> vertices;

public:
	Twitter(void);
	
	unordered_map<std::string, User *> userMap;		

	void loadGraph(const char* in_filename);

	void DFS(std::stack<User *> &finished);

	void DFSvisit(User *username, std::stack<User *> &finished);

	void flip();
	
	int getGroups();
};
