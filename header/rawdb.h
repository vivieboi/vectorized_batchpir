#ifndef RAWDB_H
#define RAWDB_H

#include <vector>
#include <span>
#include <cassert>
#include "seal/seal.h"

using namespace std;
using namespace seal;
using namespace std;

class RawDB {
    public:
        RawDB();
        RawDB(size_t rows, size_t cols);
        RawDB(size_t rows, size_t cols, unsigned char init_val);

        /* Overload [] operators -> return a span (representing a row) */
        span<unsigned char> operator[](size_t i);
        std::span<const unsigned char> operator[](size_t i) const;

        vector<unsigned char>& data();
        size_t rows() const;
        size_t cols() const;
        size_t size() const;        // Just returns the # rows

        void set_rows(size_t rows);
        void set_cols(size_t cols);

        void resize(size_t new_rows);
        void clear();
        bool empty();

        // Ideally we don't use these, and can just directly modify the RawDB
        void push_back(vector<unsigned char> row);
        void push_back(span<unsigned char> row);

    private:
        vector<unsigned char> db_;
        size_t rows_;
        size_t cols_;
};



#endif