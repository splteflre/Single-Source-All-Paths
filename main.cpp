#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <sstream>


using namespace std;

/***********************************************************************
ASSUMPTIONS: The following program is done under the assumption that   *
             the input file always follows these input specificaitons: *
                                                                       *
1) The first line will be the string "Name : " followed by the name of *
   a person in the graph                                               *
2) The next line will be the string "Friend : " followed by a list of  *
   friends of the aforementioned person                                *
3) 1) and 2) will repeat for any amount of times or zero times         *
4) No name will occur more than once                                   *
5) A friendship goes both ways, thus making the graph undirected       *
                                                                       *
************************************************************************/

map<string, vector<string> > graph;   //hash tables that maps each person to their friends
map<string, int> discovered;          //hash table that tracks which person is discovered, 0 == not discovered, 1 == discovered
vector<string> paths;                 //all possible paths from start to finish

void find_paths(string node, string finish, string path);
string get_second(string line);
vector<string> get_friends(string friend_str);

int main()
{
    string fd, start, finish, name, friend_line;
    vector<string> friends;
    ifstream file;

    cin >> fd >> start >> finish;

    //open file for reading, since open needs const char* use c_str
    file.open(fd.c_str());
    if(!file){
        cerr << "could not open file";
        exit(1);
    }

    //get friend from file, parse each line and initialize graph
    while(getline(file, name) && getline(file, friend_line)){
        name = get_second(name); //name of person
        friend_line = get_second(friend_line); //line containing list of friend each seperated by a space
        friends = get_friends(friend_line); //vector containing all friends of person

        //check if name is already in the hash table, if it is insert friends at the end
        if(graph.insert(make_pair(name, friends)).second == false){
            graph[name].insert(graph[name].end(), friends.begin(), friends.end());
        }

        //since a friendship goes both ways extend the connection back to form an undirected graph
        for(int i = 0; i < friends.size(); i++){
            // temporary variable to check if friend is already part of hash table
            vector<string> temp;
            temp.push_back(name);

            //if friend is already in hash table, insert name at the end
            if(graph.insert(make_pair(friends[i], temp)).second == false){
                graph[friends[i]].insert(graph[friends[i]].end(), temp.begin(), temp.end());
            }
        }
    }
    file.close();

    //find all paths from start to finish
    find_paths(start, finish, start);

    //print all possible paths
    for(int i = 0; i < paths.size(); i++){
        cout << paths[i] << endl;
    }


    return 0;
}

//parse line to get everything after ': '
string get_second(string line){
    return line.substr(line.find(': ')+3, line.length()-1);
}

//parse the friend string and return all friends in a vector
vector<string> get_friends(string friend_str){
    vector<string> friends;
    stringstream friend_stream (friend_str);
    string name;

    while(getline(friend_stream, name, ' ')){
        friends.push_back(name);
    }
    return friends;
}

//depth first search to find all possible paths from start to finish
void find_paths(string node, string finish, string path){
    if(node == finish){
        paths.push_back(path);
        return;
    }

    discovered[node] = 1; //mark node as discovered

    //iterate through all neighbors
    for(int i = 0; i < graph[node].size(); i++){
        //if node is not discovered recurse on that node
        if(!discovered[graph[node][i]]){
            find_paths(graph[node][i], finish, path+" => " + graph[node][i]);
        }
    }

    //unmark node as discovered so other nodes can reuse it as part of their path
    discovered[node] = 0;

}
