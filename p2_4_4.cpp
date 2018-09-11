#include <iostream>
using namespace std;
typedef float DATO;
class monitor
{
public:
    DATO xmin,ymin,xmax,ymax;
    DATO ndcx,ndcy;
    DATO user_x,user_y;
    DATO dcx,dcy;   
    monitor(DATO xmin,DATO xmax, DATO ymin, DATO ymax)
    {
        this->xmin=xmin;
        this->xmax=xmax;
        this->ymin=ymin;
        this->ymax=ymax;
    }
    void ndc_to_user()
    {
        user_x=ndcx*(xmax-xmin)+xmin;
        user_y=ndcy*(ymax-ymin)+ymin;
    }
    void user_to_ndc(x,y)
    {
        ndcx=(x-xmin)/(xmax-xmin);
        ndcy=(y-ymin)/(ymax-ymin);
    }
    void inp_to_ndc()
    {
        ndcx=
        ndcy=
    }
    void ndc_to_dc()
    {
        dcx=
        dcy=
    }
};

int main()
{
    return 0;
}