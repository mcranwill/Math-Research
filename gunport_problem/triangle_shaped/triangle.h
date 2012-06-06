#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <string>
#include <vector>

using namespace std;

struct coordinate{
	int row;
	int col;
};
struct nodeInfo{
    int id;
    vector<int> set;
    int orientation;
};

class Triangle
{
public:
    /* constructor */
	Triangle();
	Triangle(int height);
	void create_table(int height);
	void display_depth();
	void print_triangle();

private:
    vector<vector<nodeInfo> > table;
    int curId;

};
#endif /* _TRIANGLE_H_ */
