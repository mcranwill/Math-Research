#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <string>
#include <vector>
#include <tr1/unordered_map>

using namespace std;
using tr1::unordered_map;

struct edgePacket{
    int nodeConnected;
    float weight;
};
struct nodeInfo {
    int id;
    int id_received;
    string lbl;
    vector<edgePacket> a;
};

class Graph
{
public:
    /* constructor */
    Graph();

    /* add a node with the given ID
     *
     * @param id id of the node being added
     * @param lbl label for the node being added
     * @return 1 on success, 0 on error or if the node with id already exists
     */
    int add_node(int id, const string& lbl);

    /* add an edge between two nodes
     *
     * @param u id of the source node
     * @param v id of the destination node
     * @return 1 on success, 0 otherwise
     */
    int add_edge(int u, int v);

    /* get a vector of all nodes
     */
    vector<int> nodes();

    /* get the neighbors of a node
     *
     * @param n the node
     * @return a vector of nodes adjacent to n
     */
    vector<int> neighbors(int n);

    /* get the neighbors of a node
     *
     * @param n the node
     * @return the degree of node n
     */
    int degree(int n);

    void PrintStats(int u);
    /* get the label of a node
     *
     * @param n a node id
     * @return the label of node n or empty string if node n does not exist
     */
    string &operator[](int n);

    /* get the weight of an edge
     *
     * @param u id of the source node
     * @param v id of the destination node
     * @return the weight of the edge between node u and node v
     */
    float edge_weight(int u, int v);

private:
    vector<nodeInfo> table;
    int curId;


//int findID(int gml_id);
    /* helper function that when every node in Q has be visited
     *
     * @param nodes vector of nodes, node is visited if id is -1
     * @return true if all ids are -1 false otherwise
     */
	bool isFinished(const vector<nodeInfo> &nodes);

    /* helper function that will find the next node in the path
     *
     * @param dest the destination node (internal id)
     * @param paths the previous vector from dijkstra's algoithm
     * @return internal index of the next node in the path
     */
	int findNextNode(int dest, const vector<nodeInfo> &paths);

    /* helper function that finds the node in Q with the smallest distance in dist
     *
     * @param Q vector of nodes
     * @param dist vector of distances to the nodes in Q (indexed by id)
     * @return returns the node with the smallest distance in dist that is also in Q
     */
	nodeInfo findSmallest(vector<nodeInfo> Q, vector<float> dist);

     /* helper function that collects info from a node
	 *
	 * @param id id of the node
	 * @param label node label
	 * @param list a pointer to the GML_LIST that is the node
	 * @return 1 on success 0 otherwise
	 */
//int getNode(long &id, string &label, struct GML_pair* list);

	/* helper function that collects info from an edge
	 *
	 * @param u id of the source
	 * @param v id of the destination
	 * @param weight the weight of the edge
	 * @param list a pointer to the GML_LIST that is the edge
	 * @return 1 on success 0 otherwise
     */
//int getEdge(long &u, long &v, float &weight, struct GML_pair* list);

	/*helper function that returns the internal ID of a given gml_id
	 *
	 * @param gml_id the id from the gml file
	 * @return internal id on success or -1 if not found
	 */
};
#endif /* _GRAPH_H_ */
