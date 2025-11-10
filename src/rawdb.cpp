#include "rawdb.h"

/* CONSTRUCTORS */
RawDB::RawDB() {
    rows_ = 0;
    cols_ = 0;
}

RawDB::RawDB(size_t rows, size_t cols) {
    rows_ = rows;
    cols_ = cols;
    db_ = vector<unsigned char>(rows * cols);
}

RawDB::RawDB(size_t rows, size_t cols, unsigned char init_val) {
    rows_ = rows;
    cols_ = cols;
    db_ = vector<unsigned char>(rows * cols, init_val);
}

span<unsigned char> RawDB::operator[](size_t i) {
    assert(i < rows_);
    return span<unsigned char>(&db_[i * cols_], cols_);
}

std::span<const unsigned char> RawDB::operator[](size_t i) const {
    assert(i < rows_);
    return span<const unsigned char>(&db_[i * cols_], cols_);
}

vector<unsigned char>& RawDB::data() {
    return db_;
}

size_t RawDB::size() const {
    return rows_;
}

size_t RawDB::rows() const {
    return rows_;
}

size_t RawDB::cols() const {
    return cols_;
}

void RawDB::set_rows(size_t rows) {
    rows_ = rows;
}

void RawDB::set_cols(size_t cols) {
    cols_ = cols;
}

void RawDB::resize(size_t new_rows) {
    // Only adds new rows, doesn't change the # of columns
    db_.resize(new_rows * cols_);
    rows_ = new_rows;
}

void RawDB::clear() {
    db_.clear();        // Makes the database completely empty
    rows_ = 0;
    // cols_ = 0;           // TODO: should we keep the columns the same?
}

bool RawDB::empty() {
    // Only consider a database empty if there are no rows
    return (rows_ == 0);
}

void RawDB::push_back(vector<unsigned char> row) {
    if (cols_ == 0) {
        // This means cols is uninitialized, initialize it now
        cols_ = row.size();
    } else {
        // Cols has already been initialized, make sure we're pushing back something of the right size
        assert(row.size() == cols_);
    }

    for (unsigned char val : row) {
        db_.push_back(val);
    }
    rows_ += 1;
}


void RawDB::push_back(span<unsigned char> row) {
    if (cols_ == 0) {
        // This means cols is uninitialized, initialize it now
        cols_ = row.size();
    } else {
        // Cols has already been initialized, make sure we're pushing back something of the right size
        assert(row.size() == cols_);
    }

    for (unsigned char val : row) {
        db_.push_back(val);
    }
    rows_ += 1;
}
