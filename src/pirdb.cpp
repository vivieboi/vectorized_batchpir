#include "pirdb.h"

#include "pirdb.h"

PirDB::PirDB() {
    rows_ = 0;
    cols_ = 0;
}

PirDB::PirDB(size_t rows, size_t cols) {
    rows_ = rows;
    cols_ = cols;
    db_ = vector<uint64_t>(rows * cols);
}

PirDB::PirDB(size_t rows, size_t cols, uint64_t init_val) {
    rows_ = rows;
    cols_ = cols;
    db_ = vector<uint64_t>(rows * cols, init_val);
}

span<uint64_t> PirDB::operator[](size_t i) {
    assert(i < rows_);
    return span<uint64_t>(&db_[i * cols_], cols_);
}

vector<uint64_t>& PirDB::data() {
    return db_;
}

size_t PirDB::size() const {
    return rows_;
}

size_t PirDB::rows() const {
    return rows_;
}

size_t PirDB::cols() const {
    return cols_;
}

void PirDB::set_rows(size_t rows) {
    rows_ = rows;
}

void PirDB::set_cols(size_t cols) {
    cols_ = cols;
}

void PirDB::resize(size_t new_rows) {
    // Only adds new rows, doesn't change the # of columns
    db_.resize(new_rows * cols_);
    rows_ = new_rows;
}

void PirDB::clear() {
    db_.clear();        // Makes the database completely empty
    rows_ = 0;
    // cols_ = 0;          // TODO: Maybe columns should still stay?
}

bool PirDB::empty() {
    // Only consider a database empty if there are no rows
    return (rows_ == 0);
}

void PirDB::push_back(vector<uint64_t> row) {
    if (cols_ == 0) {
        // This means cols is uninitialized, initialize it now
        cols_ = row.size();
    } else {
        // Cols has already been initialized, make sure we're pushing back something of the right size
        assert(row.size() == cols_);
    }

    for (uint64_t val : row) {
        db_.push_back(val);
    }
    rows_ += 1;
}

void PirDB::push_back(vector<size_t> row) {
    if (cols_ == 0) {
        // This means cols is uninitialized, initialize it now
        cols_ = row.size();
    } else {
        // Cols has already been initialized, make sure we're pushing back something of the right size
        assert(row.size() == cols_);
    }

    for (size_t val : row) {
        db_.push_back(val);
    }
    rows_ += 1;
}