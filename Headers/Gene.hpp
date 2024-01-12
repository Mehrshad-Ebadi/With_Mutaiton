#include <vector>
#include <string>
using namespace std;

class gene
{
    public:
    int dg_in, dg_out, nm_up;
    int slf_cntrl;
    double weights;
    bool isolated;
    vector <int> nghbrs;
    vector <int> Connected;
    vector <int> updte_list;
    
    gene () {

    }

    ~gene (){
        updte_list.clear();
        Connected.clear();
        nghbrs.clear();
    }


};