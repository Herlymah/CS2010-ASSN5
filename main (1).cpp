/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

template <class T>
using ELEM = std::vector<T>;

template <class T>
using VEC = std::vector<ELEM<T>>;

template <class T>
using action_t = T (*) (int);

template <class T>
using pred_t = bool (*) (T);

template <class T>
using map_t = T (*) (T,T);

int f(int x) { 
    return x * x;
}

bool g(int x) {
    return x > 0;
}

int h(int x) { 
    return x > 0 ? 1 : 0; 
}

template <class T>
T k(T a, T b) { 
    return a + b; 
}

template <class T>
void printElem(const ELEM<T> &v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i < v.size() - 1) std::cout << ", ";
    }
    std::cout << "]";
}

template <class T>
void initVec(VEC<T> &v, ELEM<T> &&cons) {
    v.clear();
    v.push_back(std::move(cons));
}

template <class T>
void printVec(const VEC<T>& v) {
    std::cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j) {
            //std::cout << "(";
            std::cout << v[i][j];
            if (j < v[i].size() - 1) std::cout << " ";
        }
        //std::cout << ")";
        if (i < v.size() - 1) std::cout << ", ";
        
    }
    std::cout << "]\n";
}

template <class T>
VEC<T> generate(int N, action_t<T> f) {
    VEC<T> result;
    for (int i = 0; i < N; ++i) {
        result.push_back(ELEM<T>{f(i)});
    }
    return result;
}

template<class T>
VEC<T> zip(const VEC<T>& v, const VEC<T>& w) {
    VEC<T> result;
    size_t min_size = std::min(v.size(), w.size());
    
    for (size_t i = 0; i < min_size; ++i) {
        size_t inner_min_size = std::min(v[i].size(), w[i].size());
        for (size_t j = 0; j < inner_min_size; ++j){
        result.push_back (ELEM<T>{v[i][j], w[i][j]});    
        
        // ELEM<T> zipped;
        // for (size_t j = 0; j < v[i].size() && j < w[i].size(); ++j) {
        //     zipped.push_back(v[i][j]);
        //     zipped.push_back(w[i][j]);
        // }
        // result.push_back(zipped);
    }
    }
    return result;
}

template<class T>
VEC<T> filter(const VEC<T> &v, pred_t<T> f) {
    VEC<T> result;
    for (const auto &elem : v) {
        ELEM<T> filtered_elem;
        bool include_elem = false;
        for (const auto &item : elem) {
            if (f(item)) {
                filtered_elem.push_back(item);
                include_elem = true;
            }
        }
        if (include_elem) {
            result.push_back(filtered_elem);
        }
    }
    return result;
}

template<class T>
VEC<T> map(const VEC<T> &v, action_t<T> f) {
    VEC<T> result;
    for (const auto &elem : v) {
        ELEM<T> mapped;
        for (const auto &e : elem) {
            mapped.push_back(f(e));
        }
        result.push_back(mapped);
    }
    return result;
}

template<class T>
ELEM<T> reduce(const VEC<T> &v, map_t<T> f, ELEM<T> ident) {
    ELEM<T> result = ident;
    for (const auto &elem : v) {
        for (const auto &e : elem) {
            result[0] = f(result[0], e);
        }
    }
    return result;
}

int main() {
    VEC<int> v;
    initVec(v, ELEM<int>{1,2,3,4});
    
    VEC<int> w;
    initVec(w, ELEM<int>{-1,3,-3,4});
    
    printVec(v);
    std::cout << std::string(10,'*') << std::endl;
    
    printVec(w);
    std::cout << std::string(10,'*') << std::endl;
    
    VEC<int> z = zip(v,w);
    printVec(z);
    std::cout << std::string(10,'*') << std::endl;
    
    VEC<int> x = zip(z,z);
    printVec(x);
    std::cout << std::string(10,'*') << std::endl;
    
    VEC<int> a = generate(10, f);
    printVec(a);
    
    VEC<int> y = filter(w, g);
    printVec(y);
    
    VEC<int> u = map(w, h);
    printVec(u);
    
    ELEM<int> e = reduce(u, k<int>, ELEM<int>{0});
    printElem(e);
    std::cout << std::endl << std::string(10,'$') << std::endl;
    
    VEC<std::string> ws;
    initVec(ws, ELEM<std::string>{"hello","there","franco","carlacci"});
    printVec(ws);
    
    ELEM<std::string> es = reduce(ws, k<std::string>, ELEM<std::string>{""});
    printElem(es);
    
    VEC<char> wc;
    initVec(wc, ELEM<char>{'a','b','c','d'});
    std::cout << std::endl << std::string(10,'$') << std::endl;
    printVec(wc);
    
    ELEM<char> ec = reduce(wc, k<char>, ELEM<char>{'\0'});
    std::cout << std::endl << std::string(10,'$') << std::endl;
    printElem(ec);

    return 0;
}