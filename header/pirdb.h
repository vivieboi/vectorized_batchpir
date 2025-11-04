#ifndef PIRDB_H
#define PIRDB_H

#include <vector>
#include <span>
#include <cassert>
#include "seal/seal.h"

using namespace seal;
using namespace std;

class PirDB {
    public:
        PirDB();
        PirDB(size_t rows, size_t cols);
        PirDB(size_t rows, size_t cols, uint64_t init_val);

        /* Overload [] operators -> return a span (representing a row) */
        span<uint64_t> operator[](size_t i);

        vector<uint64_t>& data();
        size_t rows() const;
        size_t cols() const;
        size_t size() const;

        void set_rows(size_t rows);
        void set_cols(size_t cols);

        void resize(size_t new_rows);
        void clear();
        bool empty();

        void push_back(vector<uint64_t> row);
        void push_back(vector<size_t> row);

    private:
        vector<uint64_t> db_;
        size_t rows_;
        size_t cols_;
};



#endif