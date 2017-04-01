#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <vector>
#include <iostream>

#include "lib.h"
#include "generated.h"


using std::vector;
using std::string;
using std::pair;
using std::ostream;
using std::endl;
using std::cout;
using std::cerr;
using std::unique_ptr;
using std::get;
using std::tuple;

using cell::Value;

////////////////////////////////////////////////////////////////////////////////

template<typename T> ostream& operator << (ostream& out, const vector<T>& v) {
    out << "(";
    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];
        if (i != last)
            out << ", ";
    }
    out << ")";
    return out;
}
