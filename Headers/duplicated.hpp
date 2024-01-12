#include <vector>
#include <string>
using namespace std;

class dupli
{
    public:
    int dg_in, dg_out, nm_up;
    int slf_cntrl;
    double weights;
    bool isolated;
    vector <int> nghbrs;
    vector <int> Connected;
    vector <int> updte_list;
    
    dupli() {

    }

    ~dupli(){   
        updte_list.clear();
        Connected.clear();
        nghbrs.clear();
    }


};