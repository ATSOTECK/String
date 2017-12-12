//
//  StringList.hpp
//  SkylerString
//
//  Created by Skyler on 12/11/17.
//  Copyright © 2017 counterpoint. All rights reserved.
//

#ifndef StringList_hpp
#define StringList_hpp

#include <stdio.h>
#include <vector>

#include "SkylerString.hpp"

class StringList {
public:
    StringList();
    StringList(const String &str);
    StringList(const StringList &other);

    bool contains(const String &str) const;
    int indexOf(const String &str) const;

    int indexOfFirst(const String &str);
    int indexOfLast(const String &str);

    int removeDuplicates();

    String join(const String &seperator) const;
    String join(char seperator) const;

    String getRandom() const;

    StringList replaceInStrings(const String &before, const String &after, bool cs = true) const;

    size_t count() const;
    size_t count(const String &str) const;

    String at(int i) const;

    void clear();

    bool beginsWith(const String &str) const;
    bool endsWith(const String &str) const;

    void erase(int pos);
    void erase(int start, int stop);
    void eraseAll();

    void removeFirst();
    void removeLast();
    bool removeOne(const String &str); //Removes the first instant of str and returns true if it did.

    String takeAt(int i); //Returns string at i and removes it.
    String takeFirst();
    String takeLast();

    void replace(int i, const String &str);

    String first() const;
    String last() const;

    bool isEmpty() const;

    void insert(int i, const String &s);

    void move(int from, int to);

    void append(const String &str);
    void prepend(const String &str);

    void swap(StringList &other); //Swaps the two lists.
    void swap(int i, int j);

    std::vector<String> toStdVector() const;

private:
    std::vector<String> data;
};

#endif /* StringList_hpp */
