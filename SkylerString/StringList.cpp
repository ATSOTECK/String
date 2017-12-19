//
//  StringList.cpp
//  SkylerString
//
//  Created by Skyler on 12/11/17.
//  Copyright © 2017 counterpoint. All rights reserved.
//

#include "StringList.hpp"

StringList::StringList() {
    //
}

StringList::StringList(const String &str) {
    _data.push_back(str);
}

bool StringList::contains(const String &str) const {
    return (std::find(_data.begin(), _data.end(), str) != _data.end());
}

int StringList::indexOf(const String &str) const {
    return (int)(std::find(_data.begin(), _data.end(), str) - _data.begin());
}

int StringList::indexOfFirst(const String &str) {
    return (int)(std::find(_data.begin(), _data.end(), str) - _data.begin());
}

int StringList::indexOfLast(const String &str) {
    return ((int)(_data.rend() - std::find(_data.rbegin(), _data.rend(), str))) - 1;
}

String StringList::join(const String &seperator) const {
    String str = "";
    for (size_t i = 0; i < count(); ++i) {
        if (i == count() - 1) {
            str += _data[i];
        } else {
            str += (_data[i] + seperator);
        }
    }
    
    return str;
}

String StringList::join(char seperator) const {
    String str = "";
    for (size_t i = 0; i < count(); ++i) {
        if (i == count() - 1) {
            str += _data[i];
        } else {
            str += (_data[i] + seperator);
        }
    }
    
    return str;
}

String StringList::getRandom() const {
    return at(rand() % (count() - 1));
}

size_t StringList::count() const {
    return _data.size();
}

String StringList::at(int i) const {
    if (i >= count() || i < 0) {
        return "";
    }

    return _data[i];
}

void StringList::clear() {
    _data.clear();
}

void StringList::erase(int pos) {
    if (pos >= count() || pos < 0) {
        return;
    }

    std::vector<String>::iterator it = _data.begin();
    for (int i = 0; i < pos; ++i) {
        it++;
    }
    
    _data.erase(it);
}

void StringList::erase(int start, int stop) {
    if (start >= count() || start < 0 || stop >= count() || stop < 0 || start > stop) {
        return;
    }

    std::vector<String>::iterator itb = _data.begin();
    for (int i = 0; i < start; ++i) {
        itb++;
    }

    std::vector<String>::iterator ite = _data.begin();
    for (int j = 0; j <= stop; ++j) {
        ite++;
    }
    
    _data.erase(itb, ite);
}

void StringList::eraseAll() {
    _data.clear();
}

void StringList::removeFirst() {
    _data.erase(_data.begin());
}

void StringList::removeLast() {
    _data.erase(_data.end() - 1);
}

bool StringList::removeOne(const String &str) {
    return false;
}

String StringList::takeAt(int i) {
    String str = at(i);
    erase(i);
    return str;
}

String StringList::takeFirst() {
    String str = at(0);
    removeFirst();
    return str;
}

String StringList::takeLast() {
    String str = at((int)count() - 1);
    removeLast();
    return str;
}

void StringList::replace(int i, const String &str) {
    //
}

String StringList::first() const {
    return at(0);
}

String StringList::last() const {
    return at((int)count() - 1);
}

bool StringList::isEmpty() const {
    return (count() == 0);
}

void StringList::insert(int i, const String &str) {
    if (i >= count() || i < 0) {
        return;
    }

    std::vector<String>::iterator it = _data.begin();
    for (int j = 0; j < i; ++j) {
        it++;
    }

    _data.insert(it, str);
}

void StringList::move(int from, int to) {
    //
}

void StringList::append(const String &str) {
    _data.push_back(str);
}

void StringList::prepend(const String &str) {
    insert(0, str);
}

std::vector<String> StringList::toStdVector() const {
    return _data;
}

const String *StringList::data() const {
    return _data.data();
}
