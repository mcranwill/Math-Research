#include "graph.h"
#include "gml_parser.h"
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#ifndef _GRAPH_CPP_
#define _GRAPH_CPP_

#define TEST(num) printf("test %d\n",num); fflush(stdout);

//Constructor
Graph::Graph() {
    curId=0;
}

int Graph::add_node(int id, const string & lbl) {
    nodeInfo temp1;
    temp1.id = curId;
    temp1.id_received = id;
    temp1.lbl = lbl;
    curId++;
    table.push_back(temp1);
    return 1;
}

//Assuming that u and v are the indices of the the two nodes you want to attach with an edge.
int Graph::add_edge(int u, int v) {
    //Find the locations of u and v.
    //If assumption wrong input here.
    //Take the string lbl of each of the nodes and insert it at the end of
	edgePacket temp1;
	temp1.nodeConnected= table[findID(v)].id_received;
	temp1.weight = weight;
	table[findID(u)].a.push_back(temp1);
	temp1.nodeConnected= table[findID(u)].id_received;
	table[findID(v)].a.push_back(temp1);

    return 1;
}

vector<int> Graph::nodes() {
    vector<int> temp;
	int i=0;
	while(i < table.size()){
		temp.push_back(table[i].id_received);
		++i;
	}
	return temp;
}

vector<int> Graph::neighbors(int n) {
    vector<int> temp;
    //get the neighbors of node index n

    //test the case where there are no nodes.
	int i=0;
	while(i< table[findID(n)].a.size()){
		temp.push_back(table[findID(n)].a[i].nodeConnected);
		++i;
	}
	return temp;
}

int Graph::degree(int n) {
    return table[findID(n)].a.size();
}

void Graph::PrintStats(int u) {
	u = findID(u);
    int i=0;
    cout <<"The id assigned is " <<  table[u].id << endl;
    cout <<"The id received is " << table[u].id_received << endl;
    cout <<"the indices and weight of the connecting edges and connected nodes are "<< endl;
    while (i < table[u].a.size()){
        cout << table[u].a[i].nodeConnected << " " << table[u].a[i].weight << endl;
        i++;
    }
}

string& Graph::operator[](int n) {
	int temp = findID(n);
	if(temp == -1)
	{
		printf("id %d does not exist.\n",n);
		exit(1);
	}
	else
	{
		return table[temp].lbl;
	}
}

float Graph::edge_weight(int u, int v) {
    u = findID(u);
    v = findID(v);
    int i=0;
    //Find the correct connection
    while(i < table[u].a.size()){
        if(table[u].a[i].nodeConnected == v){
            return table[u].a[i].weight;
        }
        i++;
    }
    return 0;
}
/*
int Graph::findID(int gml_id) {
	for(int i=0;i<table.size();i++)
	{
		if(table[i].id_received == gml_id)
			return i;
	}
	return -1;
}*/

bool Graph::isFinished(const vector<nodeInfo> &nodes)
{
    for(int i=0;i<nodes.size();i++)
    {
        if(nodes[i].id != -1)
            return false;
    }

    return true;
}

int Graph::findNextNode(int dest, const vector<nodeInfo> &paths) {
    int temp = dest;
    int ret = dest;
    if(paths[temp].id == -1)
        return ret;

    temp = paths[temp].id;
    while(paths[temp].id != -1)
    {
        ret = temp;
        temp = paths[temp].id;
    }

    return ret;
}

nodeInfo Graph::findSmallest(vector<nodeInfo> Q, vector<float> dist) {
    int smallest_id=Q[0].id;
    float smallest=INFINITY;
    for (int cur_id = 0; cur_id < Q.size();cur_id++){
       //test for smallest in dist. if dist[cur_id] < dist[smallest_id]
       if(Q[cur_id].id != -1 && dist[Q[cur_id].id] < smallest){
            smallest_id = cur_id;
            smallest = dist[Q[cur_id].id];
       }
    }
    return Q[smallest_id];
}
/*
int Graph::getNode(long &id, string &label, struct GML_pair* list) {
	struct GML_pair* tmp = list;
	bool foundID = false;
	bool foundlbl = false;

	while(tmp != NULL)
	{
		if(strcmp(tmp->key, "id") == 0)
		{
			// return in error if it is not an int
			if(tmp->kind != GML_INT)
				return 0;
			else
				id = tmp->value.integer;

			foundID = true;
		}
		else if(strcmp(tmp->key, "label") == 0)
		{
			// return in error if label is not a string
			if(tmp->kind != GML_STRING)
				return 0;
			else
				label = tmp->value.string;

			foundlbl = true;
		}

		tmp = tmp->next;
	}

	// return in error if no id is found
	if(!foundID)
		return 0;

	// if no label is found, a blank label is used
	if(!foundlbl)
		label = "";

	// return 1 on success
    return 1;
}*/
/*
int Graph::getEdge(long &u, long &v, float &weight, struct GML_pair* list) {
	struct GML_pair* tmp = list;
	bool foundSrc = false;
	bool foundDest = false;
	bool foundValue = false;

	while(tmp != NULL)
	{
		if(strcmp(tmp->key, "source") == 0)
		{
			// return in error if it is not an int
			if(tmp->kind != GML_INT)
				return 0;
			else
				u = tmp->value.integer;

			foundSrc = true;
		}
		else if(strcmp(tmp->key, "target") == 0)
		{
			// return in error if it is not an int
			if(tmp->kind != GML_INT)
				return 0;
			else
				v = tmp->value.integer;

			foundDest = true;
		}
		else if(strcmp(tmp->key, "value") == 0)
		{
			// return in error if it is not a float or int
			if(tmp->kind == GML_DOUBLE)
				weight = tmp->value.floating;
			else if(tmp->kind == GML_INT)
				weight = tmp->value.integer;
			else
				return 0;

			foundValue = true;
		}

		tmp = tmp->next;
	}

	// return in error if either of the id's are missing
	if(!foundSrc || !foundDest)
		return 0;

	// if no weight is given, set weight to 0
	if(!foundValue)
		weight = 1;

	// return 1 on success
	return 1;
}*/



#endif /*_GRAPH_CPP_*/
