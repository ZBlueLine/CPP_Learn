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
    Tuple<Types...> tail(){return *this;}
};

void test()
{
    Tuple<int, double, double> myt(99, 0.3, 8.3242);
    cout<<myt.tail().Head;  //0.3
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

int main()
{
    //jj01::test01();
    //jj02::test02();
    //jjinsert::testtinsert();
    //jjstradapt::teststream();
    //jjinadapt::testin();
    jjhash::test();
    //jjtuple::test();
    //jjtraits::test();
    //jjconst::tese();
    
    return 0;
}