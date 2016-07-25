/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   setstr_compare.cc
 * Author: ashu
 * 
 * Created on July 13, 2016, 6:28 PM
 */

#include "declaration.h"

/**
 * compares both objects of the sets of the string based on the size of set and
 * if equal then contents of the string set.
 */
bool setstr_compare::less(const set_str &lhs, const set_str &rhs) {
    if (lhs.size() < rhs.size())
        return true;
    if (lhs.size() == rhs.size()) {
        for (auto i = lhs.begin(), j = rhs.begin(); i != lhs.end(); ++i, ++j) {
            if (*i < *j)
                return true;
            if (*i > *j)
                return false;
        }
        return false;
    }
    return false;
}

/**
 * Just calls the less function to determine the inequality of the parameter objects.
 */
bool setstr_compare::operator()(const set_str &lhs, const set_str &rhs) const {
    return setstr_compare::less(lhs, rhs);
}
