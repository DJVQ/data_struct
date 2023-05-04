#include "head.h"

//单例
class single_hungry {//饿汉模式
    public: 
        static single_hungry* get_instance() {
            static single_hungry ins;
            return &ins;
        }
    private:
        single_hungry() = default;
        ~single_hungry() = default;
        single_hungry(const single_hungry &) = delete;
        single_hungry& operator=(const single_hungry &other) = delete;
};

class single_unhungry {//懒汉模式
    public: 
        static single_unhungry* get_instance() {
            if(ins == nullptr) {
                m_tex.lock();
                if(ins == nullptr) 
                    ins = new single_unhungry();
                m_tex.unlock();      
            }
            return ins;
        }
    private:
        static single_unhungry* ins;
        static std::mutex m_tex;
        single_unhungry() = default;
        ~single_unhungry() = default;
        single_unhungry(const single_hungry &) = delete;
        single_unhungry& operator=(const single_hungry &other) = delete;
};

//简单工厂
class product{
    public:
        product() = default;
        virtual void show() = 0;
};
class product_a : public product{
    public:
        product_a() = default;
        ~product_a() = default;
        void show() {cout<<"product_a_show"<<endl;}
};
class product_b : public product{
    public:
        product_b() = default;
        ~product_b() = default;
        void show() {cout<<"product_b_show"<<endl;}
};
class simple_factory{
    public:
        simple_factory() = default;
        
        product* product(const string product_name) {
            if(product_name == "a")
                return new product_a();
            else if(product_name == "b")
                return new product_b();
            return nullptr;
        }
};

//抽象工厂
class factory{
    public:
        virtual product* create_product() = 0;
};
class factory_a : public factory{
    public:
        product* create_product(){
            return new product_a();
        }
};
class factory_b : public factory{
    public:
        product* create_product(){
            return new product_b();
        }
};

//观察者
class subject;
class observer{
    protected:
        string name;
        subject* sub;
        
    public:
        observer(string name, subject* sbj){
            this->name = name;
            this->sub = sub;
        }
        virtual void update() = 0;
};
class man_observer : public observer{
    public:
        man_observer(string name, subject* sbj) : observer(name, sbj){}
        void update();
};
class women_observer : public observer{
    public:
        women_observer(string name, subject* sbj) : observer(name, sbj){}
        void update();
};
class subject{
    protected:
        list<observer*> observers;
    public:
        string action;
        virtual void attach(observer*) = 0;
        virtual void detach(observer*) = 0;
        virtual void notify() = 0;
};
class baby : public subject{
    void attach(observer* observer){
        observers.push_back(observer);
    }
    void detach(observer* observer_in){
        list<observer*>::iterator iter;
        for(iter = observers.begin(); iter != observers.end(); ++iter) {
            if(*iter == observer_in){
                observers.erase(iter);
                return;
            }
        }
    }
    void notify() {
        list<observer*>::iterator iter;
        for(iter = observers.begin(); iter != observers.end(); ++iter) {
            (*iter)->update();
        }
    }
};
void man_observer::update(){
    cout<<"收到消息："<<sub->action<<endl;
    if(sub->action == "the man care") {
        cout<<"the man will do somthing"<<endl;
    }
}
void women_observer::update(){
    cout<<"收到消息："<<sub->action<<endl;
    if(sub->action == "the women care") {
        cout<<"the women will do somthing"<<endl;
    }
}