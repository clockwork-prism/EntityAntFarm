#pragma once
#include <vector>
#include <array>
#include <stdexcept> 
#include <string>

template <typename T>
class Array2D {
private:
    std::vector<T> _data;

    size_t _get_index(size_t r, size_t c) const { 
        if (r >= _shape[0] || c >= _shape[1]) {
            throw std::out_of_range(
                "Indeces r: " + std::to_string(r) + " and c: " + std::to_string(c) + 
                " out of range for matrix of shape " + std::to_string(_shape[0]) +
                " rows by " + std::to_string(_shape[1]) + " columns."
            );
        }
        return _shape[1] * r + c;
    }
    std::array<size_t, 2> _shape;

public:
    const std::array<size_t, 2>& shape() const { return this->_shape; }

    Array2D(size_t nRows, size_t nCols)
        : _data(nRows * nCols), _shape{ nRows, nCols } {}

    Array2D(size_t nRows, size_t nCols, T val)
        : _data(nRows* nCols, val), _shape{ nRows, nCols } {}

    Array2D(size_t nRows, size_t nCols, std::vector<T> val) : _shape{ nRows, nCols }, _data( val.size() ) {
        if (val.size() != nRows * nCols)
            throw std::runtime_error("Size of vector must be equal to rows * cols");
        _data = val;
    }

    T& at(size_t r, size_t c) { return _data.at(_get_index(r, c)); }
    const T& cat(size_t r, size_t c) const { return _data.at(_get_index(r, c)); }
    auto begin() { return _data.begin(); }
    auto end() { return _data.end(); }
    auto cbegin() const { return _data.cbegin(); }
    auto cend() const { return _data.cend(); }
    size_t size() const noexcept { return _data.size(); }
    std::array<size_t, 2> const unravel_index(size_t idx) {
        T _ = _data.at(idx);
        return { idx / shape[0], (idx % shape[0]) };
    }
};
