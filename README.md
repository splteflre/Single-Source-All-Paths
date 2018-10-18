# Single-Source-All-Paths
Find all possible paths between two nodes in a graph

Create a graph where each node represents names. Edge is added if they are friends. 
Given two names in the graph, print out how they are connected in all possible ways.

friendslist.txt :
Name : John
Friends : Aron James
Name : Joseph
Friends : James Peter
Name : James
Friends : Peter Mathew
Name : Mathew
Friends : Alex Rex
 
Run the program command line:
./findfriends <path/to/friendslist.txt> john joseph  <= Should print all the possible ways john and joseph are connected through friends.
john => james=>joseph
john => james => peter => joseph
