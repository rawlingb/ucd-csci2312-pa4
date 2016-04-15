//
// Created by Brian on 4/1/2016.
//


#include <string>
#include "Exceptions.h"

namespace Gaming {
    void GamingException::setName(std::string name) { __name = name; }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        ex.__print_args(os);
		return os;
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) :
        __exp_width(expWidth), __exp_height(expHeight), __width(width), __height(height) { }

    unsigned DimensionEx::getExpWidth() const { return __exp_width; }

    unsigned DimensionEx::getExpHeight() const { return __exp_height; }

    unsigned DimensionEx::getHeight() const { return __height; }

    unsigned DimensionEx::getWidth() const { return __width; }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width, unsigned height) :
        DimensionEx(minWidth, minHeight, width, height){
        setName("InsufficientDimensionsEx");
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << __name << " Minimum Dimensions Required: " << __exp_height << ", " << __exp_width << std::endl
        << "Got: " << __height << ", " << __width << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height):
        DimensionEx(maxWidth, maxHeight, width, height) {
        setName("OutOfBoundsEx");
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << __name << " Maximum dimensions Allowed: " << __exp_height << ", " << __exp_width << std::endl
        << "Got: " << __height << ", " << __width << std::endl;
    }

    PositionEx::PositionEx(unsigned x, unsigned y) : __x(x), __y(y){ }

    void PositionEx::__print_args(std::ostream &os) const {
        os << __name << " (" << __x << ", " << __y << ")" << std::endl;
    }

    PositionNonemptyEx::PositionNonemptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        setName("PositionNonemptyEx");
    }

    PositionEmptyEx::PositionEmptyEx(unsigned x, unsigned y) : PositionEx(x, y) {
        setName("PositionEmptyEx");
    }

    PosVectorEmptyEx::PosVectorEmptyEx() {
        setName("PosVectorEmptyEx");
    }

    void PosVectorEmptyEx::__print_args(std::ostream &os) const {
        os << __name << std::endl;
    }


}

