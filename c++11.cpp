#include <iostream>

#include <cmath>

using namespace std;

namespace Temp
{

void print()
{
    cout<<"null"<<endl;
}

template<typename T, typename... Types>
void print(const T& a, const Types&... args)
{
    cout<<a<<' ';
    cout<<"many args"<<endl;
    print(args...);
}

template<typename... Types>
void print(const Types&... args)
{
    cout<<"1 arg"<<endl;
}

void test()
{
    print("dfkgjsgsdg", 985646);
}

}

namespace initlist
{

class P
{
public:
    P(int a, int b)
    {
        cout<<"()"<<a<<' '<<b<<endl;
    }
    P(initializer_list<int> inis)
    {
        cout<<"list"<<endl;
        for(auto &c : inis)
            cout<<c<<' ';
        cout<<endl;
    }

};


void test()
{
    P p(1, 2);
    P p2{3, 4, 5};
    P p3{4, 5};
}

}


namespace myexpl
{

class Foo { 
protected:
    int a;
    Foo() = default;
    Foo(int, int){} 
};
class Bar : public Foo
{ 
public:
    using Foo::a;
    void show()
    {
        cout<<a<<endl;
    }
    Bar(initializer_list<int>){
        cout<<"initlist"<<endl;
    }
    explicit Bar(int, int, int){} 
    explicit Bar(int, int){} 
    explicit Bar(int){} 
    
};
void test()
{
    // Foo f1(1, 1); // ok
    // Foo f2 {1, 1}; // ok
    // Foo f3 = {1, 1}; // ok
    Bar b1{1, 2, 3};
    b1.a = 5;
    b1.show();
    // Bar b1(1, 1); // ok
    Bar b2{1, 2, 3, 4, 5, 6, 7}; // ok
    // Bar b3 ({1, 1}); // NOT OKAY
    // Bar b4 = {1, 1, 5}; // NOT OKAY
}

}

namespace jjusing
{

#include <iostream>
struct B {
    virtual void f(int) { std::cout << "B::f\n"; }
    void g(char)        { std::cout << "B::g\n"; }
    void h(int)         { std::cout << "B::h\n"; }
 protected:
    int m; // B::m is protected
    typedef int value_type;
};
 
struct D : B {
    using B::m; // D::m is public
    //using B::value_type; // D::value_type is public
 
    //using B::f;
    void f(int) { std::cout << "D::f\n"; } // D::f(int) overrides B::f(int)
    //using B::g;
    void g(int) { std::cout << "D::g\n"; } // both g(int) and g(char) are visible
                                           // as members of D
    using B::h;
    void h(int) { std::cout << "D::h\n"; } // D::h(int) hides B::h(int)
};
void test()
{
    D d;
    B& b = d;
 
//    b.m = 2; // error, B::m is protected
    d.m = 1; // protected B::m is accessible as public D::m
    b.f(1); // calls derived f()
    d.f(1); // calls derived f()
    d.g(1); // calls derived g(int)
    d.g('a'); // calls base g(char)
    b.h(1); // calls base h()
    d.h(1); // calls derived h()
}
}

#include <set>
namespace lambda
{


template<typename T>
struct myless{
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};

auto cmp = [](const int& l, const int& r){
    return l<r;
};

struct cmp1{
    bool operator()(const int& l, const int& r)
    {
        return l < r;
    }
};

void test () 
{
    std::set<int, cmp1> a;
    for(int i = 0; i < 10; ++i)
    {
        a.insert(i);
    }
    for(auto &c: a)
        cout<<c<<endl;
}

}

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

namespace jjsmart
{

struct Base
{
    Base() { std::cout << "  Base::Base()\n"; }
    // ע�⣺�˴������������� OK
    ~Base() { std::cout << "  Base::~Base()\n"; }
};
 
struct Derived: public Base
{
    Derived() { std::cout << "  Derived::Derived()\n"; }
    ~Derived() { std::cout << "  Derived::~Derived()\n"; }
};
 
void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // �̰߳�ȫ����Ȼ���������� use_count
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "local pointer in a thread:\n"
                  << "  lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << '\n';
    }
}
 
void test()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();
    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    std::thread t1(thr, p), t2(thr, p), t3(thr, p);
    p.reset(); // �� main �ͷ�����Ȩ
    std::cout << "Shared ownership between 3 threads and released\n"
              << "ownership from main:\n"
              << "  p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << '\n';
    t1.join(); t2.join(); t3.join();
    std::cout << "All threads completed, the last one deleted Derived\n";
}

}


namespace inherit
{

class Base{
public:
    int a;
    Base(){cout<<a<<endl;}
    Base(const int& A) : a(A)
    {
        cout<<"Base ctor"<<endl;
    }
    virtual int myfunc()
    {
        cout<< "a "<<a<<endl;
        return a;
    }
};

class Derived : public Base
{
public:
    int b;
    Derived() = default;
    Derived(const int& A) : b(A)
    {
        cout<<"Derived ctor"<<endl;
        a = b;
    }
    virtual int myfunc()
    {
        cout<<"b "<<b<<endl;
        return b;
    }
};

void test()
{
    int Min =5,Max = 4;
}

}

namespace newcode01
{

void test()
{
    int a = -1;
    unsigned int b = 2;
    cout<< (int)(a>b?a:b)<<endl;
}

}

namespace jjtype
{
template<typename T>
class foo{
public:
    void tt()
    {
        int a = T::aaa;
        cout<<a<<endl;
    }
};

class ContainsaType{
public:
    class iter{
        int a;
        int b;
    };
    static int aaa;
};

int ContainsaType::aaa = 1000;

void test()
{
    //foo<ContainsaType> a;
    //a.tt();
}

}

namespace smartptr
{
    class B;
    class A {
    public:
        shared_ptr<B> srd;
        ~A()
        {cout<<"A dtor"<<endl;}
        void print()
        {
            cout<<"print"<<endl;
        }

    };

    class B{
    public:
        weak_ptr<A> srd;
        ~B()
        {cout<<"B dtor"<<endl;}
    };

    void test()
    {
        auto_ptr<string> p1 (new string ("I reigned lonely as a cloud.")); 
        auto_ptr<string> p2; 
        p2 = p1; //auto_ptr���ᱨ��.
        cout<<*p2<<endl;
        unique_ptr<string> p3 (new string ("auto"));   //#4
        unique_ptr<string> p4;   //#5
        //p4 = p3;//��ʱ�ᱨ������
        cout<<*p3<<endl;
        p4 = unique_ptr<string>(new string("tmp auto"));
        cout<<*p4<<endl;
        shared_ptr<A> a (new A());
        shared_ptr<B> b (new B()); 
        cout<<a.use_count()<<endl;
        cout<<b.use_count()<<endl;
        a->srd = b;                     //ѭ������
        b->srd = a;
        shared_ptr<A> p = b->srd.lock();
        p->print();
        cout<<a.use_count()<<endl;
        cout<<b.use_count()<<endl;
    }
}

#include <unordered_map>
#include <vector>
#include <map>
#include <list>

namespace internal
{

void test()
{
    vector<int> vec1;
    map<int, int> map1;
    list<int> lis1;
    std::unordered_map<int ,int>
        myrecipe;
    for(int i = 0; i < 10000; ++i)
    {
        vec1.push_back(i);
        map1[i] = i;
        lis1.push_back(i);
        myrecipe.insert (std::make_pair<int,int>(move(i), move(i)));
        //un1.insert(std::make_pair<int ,int>(i, i));
    }
    int max = 0;
    for(int i = 0; i < myrecipe.bucket_count(); ++i)
    {
        max += myrecipe.bucket_size(i);
    }
    bool a = true;
    int c = 10;
    switch(a)
    {
        case true:{
            cout<<"true"<<endl;
            break;
        }
        case false:{
            cout<<"false"<<endl;
            break;
        }
    };
    switch(c)
    {
        case 10:{
            cout<<"10"<<endl;
            break;
        }
        case 1:{
            cout<<"1"<<endl;
            break;
        }
    };
    cout<<"vec1: "<<vec1.capacity()<<endl;
    cout<<"map1: "<<map1.size()<<endl;
    cout<<"lis1: "<<lis1.size()<<endl;
    cout<<"myrecipe: "<<myrecipe.bucket_count()<<' '<<max<<endl;
    
}

}

namespace inherit
{
    class X
    {
    public:
        virtual void f() {}
    };

    class Y : public X
    {
        void f() override {}
    };

}

int main()
{
    //Temp::test();
    //initlist::test();
    //myexpl::test();
    //jjusing::test();
    //lambda::test();
    //jjsmart::test();
    //inherit::test();
    //newcode01::test();
    //jjtype::test();
    //smartptr::test();
    internal::test();
    return 0;
}