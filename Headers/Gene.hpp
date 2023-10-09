#include <vector>
#include <string>
using namespace std;

class gene
{
    public:
    int dg_in, dg_out, nm_up;
    int slf_cntrl;
    double weights;
    vector <int> nghbrs;
    vector <int> Connected;
    gene () {

    }

    ~gene (){

    }


};