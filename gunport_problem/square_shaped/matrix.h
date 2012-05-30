#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string>
#include <vector>

using namespace std;

struct packet_info {
    int id;
    string color;
};

class Matrix
{
public:
    //Constructor
    Matrix();

    //Add a node to the matrix
    int add_node(int r,int c,string color);
    vector<int> neighbors(int id);
    void increase_size(int r, int c, bool is_row);
    void print_matrix();
    void print_stats();

private:

    vector<vector<packet_info> > matrix;

    int curId;

};

#endif /* _MATRIX_H_ */
