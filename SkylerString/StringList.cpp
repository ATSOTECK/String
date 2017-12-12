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
    data.push_back(str);
}

bool StringList::contains(const String &str) const {
    return (std::find(data.begin(), data.end(), str) != data.end());
}

int StringList::indexOf(const String &str) const {
    return (int)(std::find(data.begin(), data.end(), str) - data.begin());
}

int StringList::indexOfFirst(const String &str) {
    return (int)(std::find(data.begin(), data.end(), str) - data.begin());
}

int StringList::indexOfLast(const String &str) {
    return ((int)(data.rend() - std::find(data.rbegin(), data.rend(), str))) - 1;
}

void StringList::append(const String &str) {
    data.push_back(str);
}
