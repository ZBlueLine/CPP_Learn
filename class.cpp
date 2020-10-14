#include <iostream>
#include <vector>
#include <array>
#include <set>
#include <list>
#include <deque>
#include <ctime>
#include <cmath>
#include <stack>

using namespace std;


int image(int a)
{return a;}

namespace jj01
{
void test01()
{
        stack<string> a;
    clock_t timestart = clock();
    for(int i = 0; i < 10000000; ++i)
    {
        a.push("TestString");
    }
    cout<<"deque: "<<clock()-timestart<<endl;
    timestart = clock();
    stack<string, list<string> > b;
    for(int i = 0; i < 10000000; ++i)
    {
        b.push("TestString");
    }
    cout<<"list: "<<clock()-timestart<<endl;
    
    
    timestart = clock();
    stack<string, set<string> > c;
    for(int i = 0; i < 10000000; ++i)
    {
        c.size();
    }
    cout<<"vector: "<<clock()-timestart<<endl;
}

} // namespace jj01

namespace jj02
{
void test02()
{
    
    _Rb_tree<int, int, _Identity<int>, less<int>> a;
    _Identity<int> v;
    cout<<"_Identity"<<v(4)<<endl;
    a._M_insert_unique(3);
    a._M_insert_equal(3);
    cout<<a.size();
}
}


namespace jj03
{
template<class Arg1, class Arg2>
class testfather
{
private:
    int *p;
public:
    typedef Arg1 argument1_type;
    typedef Arg2 argument2_type;
};

template<class T>
class MAX : public testfather<T, T>
{
public:
    T operator()(const T& a, const T& b)
    {
        return a > b? a:b;
    }
};

template<class T>
T maxmy(T a, T b)
{
    return a > b? a : b;
}

}

#include <functional>
namespace jj04
{
template<class T>
class Division : public binary_function<T, T, T>
{
public:
    T operator()(const T& a, const T& b)
    {
        return a/b;
    }
};

}

namespace jjinsert
{

void testtinsert()
{
    vector<int> a;
    for(int i = 0; i < 5; ++i)
        a.push_back(i*10);
    vector<int> cc{23,3434,635,76};
    copy(cc.begin(), cc.end(),inserter(a, a.begin()));
    for(auto &c:a)
        cout<<c<<endl;
}

}

#include <iterator>
namespace jjstradapt
{

void teststream()
{
    list<string> mystr{"zzy", "no1"};

    ostream_iterator<string> out(std::cout, ", ");
    copy(mystr.begin(), mystr.end(), out);
}


}

namespace jjinadapt
{

void testin()
{
    string value;
    istream_iterator<string> eos;
    istream_iterator<string> inn(std::cin);
    cout<<"???"<<endl;
    while(inn!=eos)
    {
        
        value = *inn;
        cout<<value<<endl;
        ++inn;
    }
}

}
#include<unordered_set>
namespace jjhash
{

class Myhash{
public:
    template<typename T>
    static
    inline size_t hash_combine(size_t& seed, const T& val)
    {
        seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    template<typename T>
    static
    inline size_t hash_val(size_t& seed, const T& val)
    {
        hash_combine(seed, val);
    }

    template<typename... Type>
    static
    inline size_t hash_val(const Type&... args)
    {
        size_t seed = 0;
        hash_val(seed, args...);
        return seed;
    }

    template<typename T, typename... Type>
    static
    inline void hash_val(size_t &seed, const T& val, const Type&... args)
    {
        hash_combine(seed, val);
        hash_val(seed, args...);
    }
};

class myclass{
public:
    string a;
    int b;
    char c;
    long long d;
};

struct myclassCmp
{
    bool operator()(const myclass& lhs, const myclass& rhs) const{
        return lhs.b == rhs.b;
    }
};

class myhash{
public:
    std::size_t operator()(const myclass& c)const
    {
        return Myhash::hash_val(c.a, c.b, c.c, c.d);
    }
};

void test()
{
    myclass a;
    a.a = "dsfkajsd";
    a.b = 345355;
    a.c = 'd';
    a.d = 43895798254375;
    
    std::unordered_set<myclass, myhash, myclassCmp> myset;
    for(int i = 0; i < 100; ++i)
    {
        myclass tmp = a;
        tmp.b = i;
        myset.insert(tmp);
    }
    unsigned n = myset.bucket_count();
    for (unsigned i=0; i<n; ++i) 
    {
        std::cout << "bucket #" << i << " contains:";
        for (auto it = myset.begin(i); it!=myset.end(i); ++it)
        std::cout << " " << it->b;
        std::cout << "\n";
    }
    return;
}

}

// namespace std
// {

// template<>
// struct hash<jjhash::myclass>
// {
//     size_t operator()(const jjhash::myclass& s)const
//     {
//         return jjhash::Myhash::hash_val(s.a, s.b, s.c, s.d);
//     }
// };

// }

#include <tuple>
namespace jjtuple
{

template<typename... Values>class Tuple;

template<>class Tuple<>{};

template<typename T, typename... Types>
class Tuple<T, Types...> : private Tuple<Types...>
{
public:
    T Head;
    Tuple(){}
    Tuple(T hd, Types... args)
    :Head(hd), Tuple<Types...>(args...){}
    auto head()->decltype(Head) {return Head;}
    Tuple<Types...> tail(){return *this;}
}; 

void test()
{
    Tuple<int, double, double> myt(99, 0.3, 8.3242);
    cout<<myt.tail().head();  //0.3
}

}


#include <type_traits>
namespace jjtraits
{

class A 
{
    int b;
    char c;
    long long d; 
};

void test()
{
    cout<<"is void"<<is_void<jjhash::myclass>::value<<endl;
    cout<<"is integral"<<is_integral<jjhash::myclass>::value<<endl;
    cout<<"is class"<<is_class<jjhash::myclass>::value<<endl;
    cout<<"is pod"<<std::is_pod<jjhash::myclass>::value<<endl; 
    cout<<"is pod"<<std::is_pod<A>::value<<endl; 
    //cout<<__is_pod(jjhash::myclass)<<endl;
}

}

namespace jjconst
{

template<typename T>
class removeconst
{
public:
    typedef T type;
};

template<typename T>
class removeconst<const T>
{
public:
    typedef T type;
};

template<typename T>
struct is_int_helper
: public false_type
{};

template<>
struct is_int_helper<int>
: public true_type
{};

template<typename T>
struct is_int
: public is_int_helper<typename removeconst<T>::type>::type
{};

void tese()
{
    int const a = 4;
    cout<<is_int<const int>::value<<endl;
}

}

//内存管理部分测试



#include <windows.h>

namespace jjnd
{

class Allocator
{
private:
    struct obj{
        struct obj* next;
    };
public:
    void* allocate(size_t);
    void  deallocate(void*, size_t);
private:
    obj* freeStore = nullptr;
    const int CHUNK = 5;
};

void* Allocator::allocate(size_t size)
{
    obj* p;
    if(!freeStore)
    {
        size_t chunk = CHUNK * size;
        freeStore = p = reinterpret_cast<obj*>(new char[chunk]);
        for(int i = 0; i < (CHUNK-1); ++i)
        {   
            // cout<<"freeStore: "<<&freeStore->next<<endl;
            cout<<"freeStore->next: "<<freeStore->next<<endl;
            p->next = (obj*)((char*)p+size);
            // cout<<"freeStore: "<<&freeStore->next<<endl;
            cout<<"freeStore->next: "<<freeStore->next<<endl;
            // cout<<"pnext: "<<p->next<<endl;
            p = p->next;
            cout<<"p->next"<<p<<endl;
            //freeStore = freeStore->next;
            // cout<<"p: "<<p<<endl;
            cout<<"freeStore: "<<freeStore->next<<endl;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

class Foo{
public:
    int a;
    static Allocator myalloc;
    Foo(const int& i)
    : a(i){}
    void* operator new(size_t size)
    {return myalloc.allocate(size);}
    void operator delete(void *p, size_t size)
    {return myalloc.deallocate(p, size);}
};
Allocator Foo::myalloc;

void Allocator::deallocate(void* p, size_t size)
{
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}

class A
{
public:
    int id;
    A():id(0){cout<<"default ctor.this="<<this<<" id="<<id<<endl;}
    A(const int& i) : id(i){cout<<"ctor.this="<<this<<" id="<<id<<endl;}
    ~A(){cout<<"dtor.this="<<this<<" id="<<id<<endl;}

};

class Screen{
public:
    struct Screendata{
        int i;
    };
    union{
        Screendata data;
        Screen *next;
    };
    Screen(int x){data.i = x;};
    int get(){return data.i;}
    void* operator new(size_t);
    void operator delete(void*, size_t);
private:
    static Screen *freeStore;
    static const int screenChunk;
};
Screen* Screen::freeStore;
const int Screen::screenChunk = 24;

void* Screen::operator new(size_t size)
{
    Screen *p;
    if(!freeStore)
    {
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen*>(new char[chunk]);
        for(int i = 0; p != &freeStore[screenChunk-1]; ++p, ++i)
        {
            p->next = p + 1;
        }
        cout<<endl;
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void *p, size_t)
{
    (static_cast<Screen*>(p))->next = freeStore;
    freeStore = static_cast<Screen*>(p);
}

void test()
{
    // const int n = 3;
    // Screen *p[n];
    // for(int i = 0; i < n; ++i)
    //     p[i] = new Screen(i);
    // for(int i = 0; i < n; ++i)
    //     cout<<p[i]<<endl;
    Foo *a[10];
    
    //cout<<a[0]->a<<endl;
    for(int i = 0; i < 10; ++i)
        a[i] = new Foo(i);
    for(int i = 0; i < 10; ++i)
        cout<<a[i]<<endl;
}

}


//#include<ext/pool_allocator.h>

namespace jjhand
{

typedef void(*fun)();

void NoMoreMemory()
{
    cerr<<"out of memory";
    abort();
}
void NoMoreMemory2()
{
    cerr<<"out of memory222";
    abort();
}

void test()
{
    fun myfun;
    set_new_handler(NoMoreMemory);
    myfun = set_new_handler(NoMoreMemory2);
    set_new_handler(myfun);
    int *p = new int[10000000000000000000000];
    cout<<"??"<<endl;
    return;
}

}

int main()
{
    //jj01::test01();
    jj02::test02();
    //jjinsert::testtinsert();
    //jjstradapt::teststream();
    //jjinadapt::testin();
    //jjhash::test();
    //jjtuple::test();
    //jjtraits::test();
    //jjconst::tese();
    //jjnd::test();
    //jjhand::test();
    return 0;
}