#include "src/head/sort.h"
#include "src/head/tree.h"
#include "src/head/dp.h"
#include "src/head/design_patten.h"
 
int main()
{
    shared_ptr<car> car_ = make_shared<car>();
    car_->move();
    cout<<"__________________"<<endl;
    shared_ptr<robot> robot_ = make_shared<robot>(car_);
    robot_->move();
    robot_->say();

}