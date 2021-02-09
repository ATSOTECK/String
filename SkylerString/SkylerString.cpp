////////////////////////////////////////////////////////////
//
// Skyler String
// Copyright (C) 2014-2017 Skyler Burwell
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#include "SkylerString.hpp"

#include <cstdio>
#include <cassert>
#include <stdlib.h>

#ifdef N_MAC
void itoa(int value, char *sp, int radix) {
    char tmp[64 + 1]; //TODO:
    char *tp = tmp;
    int i;
    unsigned v;
    int sign;
    int len = 0;
    
    sign = (radix == 10 && value < 0);
    if (sign) {
        v = -value;
    } else {
        v = (unsigned)value;
    }
    
    while (v || tp == tmp) {
        i = v % radix;
        v /= radix;
        if (i < 10) {
            *tp++ = i + '0';
        } else {
            *tp++ = i + 'a' - 10;
        }
    }
    
    if (sign) {
        *sp++ = '-';
    }
    
    while (tp > tmp) {
        *sp++ = *--tp;
        ++len;
    }
    
    sp[len] = '\0';
}

void strupr(char *s) {
    for (; *s; s++) {
        *s = toupper((unsigned char) *s);
    }
}
#endif

void uitoa(unsigned int value, char *sp, int radix) {
    char tmp[64 + 1]; //TODO:
    char *tp = tmp;
    int i;
    unsigned v;
    int len = 0;
    
    v = value;
    
    while (v || tp == tmp) {
        i = v % radix;
        v /= radix;
        if (i < 10) {
            *tp++ = i + '0';
        } else {
            *tp++ = i + 'a' - 10;
        }
    }
    
    while (tp > tmp) {
        *sp++ = *--tp;
        ++len;
    }
    
    sp[len] = '\0';
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c += 32;
    }
    
    return c;
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        c -= 32;
    }
    
    return c;
}

char swapCase(char c) {
    if (!isAlpha(c)) {
        return c;
    }
    
    if (isUpper(c)) {
        return c + 32;
    } else {
        return c - 32;
    }
}

bool isNumber(char c) {
    return (c >= '0' && c <= '9');
}

bool isHexnumber(char c) {
    return (isNumber(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

bool isAlpha(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isAlphanumeric(char c) {
    return (isAlpha(c) || isNumber(c));
}

bool isUpper(char c) {
    return (c >= 'A' && c <= 'Z');
}

bool islower(char c) {
    return (c >= 'a' && c <= 'z');
}

bool isWhitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

bool isNewline(char c) {
    return (c == '\n' /*|| c == '\r\n'*/);
}

///////////////////////////////////////////////////////////////////////////////

uint32 strLen(const String &str) {
    uint32 len = 0;
    while (str.str[len++] != '\0') {}
    
    return len;
}

uint32 numDigits(uint32 n) {
    uint32 num = 0;
    for (uint32 i = 10; i < UINT32_MAX; i *= 10) {
        ++num;
        if (n < i) {
            return num;
        }
    }
    
    return num;
}

String toString(uint32 n) {
    uint32 len = numDigits(n);
    
    String s;
    s.init(len);
    s.length = len;
    
    sprintf(s.str, "%d", n);
    
    return s;
}

String toUpper(const String &str) {
    return str.toUpper();
}

String toLower(const String &str) {
    return str.toLower();
}

void copyStr(char *dest, const char *src, uint64 size, int64 start) {
    for (uint64 i = start; i < size + start; ++i) {
        dest[i - start] = src[i];
    }
}

///////////////////////////////////////////////////////////////////////////////

String::String() :
    str(null),
    length(0),
    size(0)
{
    //
}

String::String(const String &other) :
    str(null),
    length(0),
    size(0)
{
    *this = other;
}

String::String(const char *s) :
    str(null),
    length(0),
    size(0)
{
    *this = s;
}

String::String(const std::string &s) :
    str(null),
    length(0),
    size(0)
{
    *this = s;
}

String::String(char c) :
    str(null),
    length(0),
    size(0)
{
    if (c == '\0') {
        length = 0;
    } else {
        length = 1;
    }
    
    init(1);
    str[0] = c;
    str[1] = '\0';
}

String::String(int n) :
    str(null),
    length(0),
    size(0)
{
    char *tmp = new char[128];
    itoa(n, tmp, 10);
    *this = (const char*)tmp;
}

String::String(uint32 n) :
    str(null),
    length(0),
    size(0)
{
    char *tmp = new char[128];
    memset(tmp, 0, 128);
    uitoa(n, tmp, 10);
    *this = (const char*)tmp;
}

String::~String() {
    if (str) {
        str = null;
        free(str);
    }
    
    length = 0;
    size = 0;
}

void String::init(uint64 buffSize) {
    if (str) {
        delete[] str;
        str = null;
    }
    
    size = buffSize + 1;
    str = new char[size];
    str[size] = 0;
}

void String::resize(uint64 newLength) {
    if (size == 0) {
        if (newLength == 0) {
            return;
        }
        
        size = newLength + 1;
        str = new char[size];
        memset(str, 0, size); //Remove garbage that may be in the string.
    } else {
        if (newLength != 0 && size < newLength + 1) {
            size = newLength + 1;
            
            char *newStr = new char[size];
            
            if (length != 0) {
                copyStr(newStr, str, length);
            } else {
                memset(newStr, 0, size);
            }
            
            delete[] str;
            str = newStr;
        }
    }
    
    str[newLength] = 0;
    length = newLength;
}

void String::append(char c, uint64 buffSize) {
    uint64 oldLength = length;
    
    if (buffSize > 1) {
        resize(length + buffSize);
        length = oldLength + 1;
    } else {
        resize(length + 1);
    }
    
    str[oldLength] = c;
    str[oldLength + 1] = '\0';
}

void String::append(const String &string, uint64 buffSize) {
    uint64 oldLength = length;
    
    if (buffSize > 1) {
        resize(length + buffSize);
    }
    
    length = oldLength;
    length += string.length;
    *this += string;
}
/*
 void String::toUpper() {
	for (uint32 i = 0; i < length; ++i) {
 str[i] = ::toUpper(str[i]);
	}
 }
 
 void String::toLower() {
	for (uint32 i = 0; i < length; ++i) {
 str[i] = ::toLower(str[i]);
	}
 }
 */
char *String::c_str() const {
    char *s = new char[length + 1];
    strcpy(s, str); //TODO(Skyler): Depreciated.
    return s;
}

std::string String::toStdString() const {
    return std::string(str);
}

bool String::contains(char c, int count) const {
    int found = 0;
    
    for (int64 i = 0; i < length; ++i) {
        if (str[i] == c) {
            if (++found == count) {
                return true;
            }
        }
    }
    
    return false;
}

bool String::contains(const String &s, int count) const {
    return false;
}

bool String::startsWith(const String &s, bool ignoreWhitespace) const {
    if (s.length == 1) {
        return str[0] == s.str[0];
    }
    
    String tmp = s;
    
    if (ignoreWhitespace) {
        tmp.trimLeadingWhitespace();
    }
    
    if (tmp.length > length) {
        return false;
    }
    
    String start;
    
    for (int64 i = 0; i <= tmp.length - 1; ++i) {
        start += str[i];
    }
    
    return start == tmp;
}

bool String::endsWith(const String &s, bool ignoreWhitespace) const {
    if (s.length == 1) {
        return str[length - 1] == s.str[0];
    }
    
    String tmp = s;
    
    if (ignoreWhitespace) {
        tmp.trimTrailingWhitespace();
    }
    
    if (tmp.length > length) {
        return false;
    }
    
    String end;
    
    for (int64 i = length - tmp.length; i < length; ++i) {
        end += str[i];
    }
    
    return end == tmp;
}

String String::stringAfterLast(char c) const {
    String ret = "";
    String tmp;
    
    for (int64 i = length; i >= 0; --i) {
        if (str[i] == c) {
            ret = tmp.reverse();
            break;
        }
        
        tmp += str[i];
    }
    
    return ret;
}

String String::stringAfterLast(char c, char c1) const {
    String ret = "";
    String tmp;
    
    for (int64 i = length; i >= 0; --i) {
        if (str[i] == c || str[i] == c1) {
            ret = tmp.reverse();
            break;
        }
        
        tmp += str[i];
    }
    
    return ret;
}

String String::stringAfterFirst(char c) const {
    String tmp;
    bool found = false;
    
    int64 i;
    for (i = 0; i < length; ++i) {
        if (str[i] == c) {
            found = true;
            break;
        }
    }
    
    for (int64 j = length;  j > i; --j) {
        tmp += str[j];
    }
    
    if (found) {
        return tmp.reverse();
    } else {
        return "";
    }
}

String String::stringAfterFirst(char c, char c1) const {
    String tmp;
    bool found = false;
    
    int64 i;
    for (i = 0; i < length; ++i) {
        if (str[i] == c || str[i] == c1) {
            found = true;
            break;
        }
    }
    
    for (int64 j = length;  j > i; --j) {
        tmp += str[j];
    }
    
    if (found) {
        return tmp.reverse();
    } else {
        return "";
    }
}

String String::stringBeforeFirst(char c) const {
    String ret = "";
    String tmp;
    
    for (int64 i = 0; i < length; ++i) {
        if (str[i] == c) {
            ret = tmp;
            break;
        }
        
        tmp += str[i];
    }
    
    return ret;
}

String String::stringBeforeFirst(char c, char c1) const {
    String ret = "";
    String tmp;
    
    for (int64 i = 0; i < length; ++i) {
        if (str[i] == c || str[i] == c1) {
            ret = tmp;
            break;
        }
        
        tmp += str[i];
    }
    
    return ret;
}

String String::stringBeforeLast(char c) const {
    String tmp;
    bool found = false;
    int64 last = -1;
    
    for (int64 i = 0; i < length; ++i) {
        if (str[i] == c) {
            last = i;
            found = true;
        }
    }
    
    for (int64 j = 0; j < last; ++j) {
        tmp += str[j];
    }
    
    if (found) {
        return tmp;
    } else {
        return "";
    }
}

String String::stringBeforeLast(char c, char c1) const {
    String tmp;
    bool found = false;
    int64 last = -1;
    
    for (int64 i = 0; i < length; ++i) {
        if (str[i] == c || str[i] == c1) {
            last = i;
            found = true;
        }
    }
    
    for (int64 j = 0; j < last; ++j) {
        tmp += str[j];
    }
    
    if (found) {
        return tmp;
    } else {
        return "";
    }
}

void String::erase(size_t pos, size_t count) {
    if (length == 0 || count == 0) {
        return;
    }
    
    std::string tmp = str;
    tmp.erase(pos, count);
    *this = tmp;
    
    //return; //ffs
    /*
    if (pos == 0) {
        char *tmp = new char[size - count];
        copyStr(tmp, str, size - count, pos + count);
        *this = tmp;
        delete[] tmp;
    } else {
        char *part1 = new char[pos + 1];
        copyStr(part1, str, pos);
        
        char *part2 = new char[size - (pos + count)];
        copyStr(part2, str, size - (pos + count), pos + count);
        
        char *tmp = new char[size - count];
        strcat(tmp, part1);
        strcat(tmp, part2);
        
        *this = tmp;
        
        delete[] part1;
        delete[] part2;
        delete[] tmp;
    }
    */
}

void String::clear() {
    init(0);
    length = 0;
}

void String::trimLeadingWhitespace() {
    while (isWhitespace(str[0])) {
        erase(0);
    }
}

void String::trimTrailingWhitespace() {
    while (isWhitespace(str[length - 1])) {
        erase(length - 1);
    }
}

void String::trimWhitespace() {
    trimLeadingWhitespace();
    trimTrailingWhitespace();
}

bool String::isEmpty() const {
    return (length == 0);
}

String String::toUpper() const {
    String ret = *this;
    for (int64 i = 0; i < ret.length; ++i) {
        ret.str[i] = ::toUpper(ret.str[i]);
    }
    
    return ret;
}

String String::toLower() const {
    String ret = *this;
    for (int64 i = 0; i < ret.length; ++i) {
        ret.str[i] = ::toLower(ret.str[i]);
    }
    
    return ret;
}

String String::swapCase() const {
    String ret = *this;
    for (int64 i = 0; i < ret.length; ++i) {
        ret.str[i] = ::swapCase(ret.str[i]);
    }
    
    return ret;
}

String String::reverse() const {
    if (length == 1) {
        return *this;
    }
    
    String ret = "";
    
    for (int64 i = length - 1; i >= 0; --i) {
        ret += str[i];
    }
    
    return ret;
}

String String::number(int n) {
    return String(std::to_string(n));
}

String String::number(float n) {
    return String(std::to_string(n));
}

String String::number(double n) {
    return String(std::to_string(n));
}

String &String::setNum(int n) {
    *this = number(n);
    return *this;
}

String &String::setNum(float n) {
    *this = number(n);
    return *this;
}

String &String::setNum(double n) {
    *this = number(n);
    return *this;
}

int String::toInt() const {
    return atoi(str);
}

float String::toFloat() const {
    return (float)atof(str);
}

double String::toDouble() const {
    return atof(str);
}

char &String::operator[](int64 index) {
    if (str == null) {
        assert(false); //TODO(Skyler): Handle this better.
    }

    if (index > length || index < 0) {
        return str[length];
    }
    
    return str[index];
}

char String::operator[](int64 index) const {
    if (str == null || index > length || index < 0) {
        return '\0';
    }
    
    return str[index];
}

String &String::operator=(const String &right) {
    if (this == &right) {
        return *this;
    }

    if (right.length == 0) {
        resize(1);
        length = 0;
        str[0] = '\0';
    } else {
        resize(right.length);
        copyStr(str, right.str, length);
    }
    
    return *this;
}

String &String::operator=(const char *s) {
    if (s == null) {
        length = 0;
    } else {
        length = strlen(s);
    }

    if (length == 0) {
        resize(1);
        length = 0;
        str[0] = '\0';
    } else {
        resize(length);
        copyStr(str, s, length);
    }
    
    return *this;
}

String &String::operator=(const std::string &s) {
    length = s.length();

    if (length == 0) {
        resize(1);
        length = 0;
        str[0] = '\0';
    } else {
        resize(length);
        copyStr(str, s.c_str(), length);
    }
    
    return *this;
}

/*
 String &String::operator=(const char c) {
 length = 1;
 size = 1;
 set = true;
 
 str = new char[1];
 str[0] = c;
 
 return *this;
 }
 */

//TODO: FIX!

String String::operator+(const String &right) const {
    String s;
    s += *this;
    s += right;
    
    return s;
}

String String::operator+(const char *right) const {
    String s;
    s += *this;
    s += right;
    
    return s;
}

String String::operator+=(const String &right) {
    if (size < length + right.length) {
        resize(length + right.length + 1);
    } else {
        length += right.length;
    }
    
    strcat(str, right.str);
    
    return *this;
}

String String::operator+=(char c) {
    append(c);
    
    return *this;
}

String String::operator+=(const char *c) {
    uint64 len = strlen(c);
    
    if (size < length + len) {
        resize(length + len + 1);
    } else {
        length += len;
    }
    
    strcat(str, c);
    
    return *this;
}

String String::operator+=(std::string s) {
    *this += s.c_str();
    
    return *this;
}

String operator+(char *left, const String &right) {
    String s;
    s += left;
    s += right;
    
    return s;
}

String operator+(const std::string &left, const String &right) {
    String s;
    s += left.c_str();
    s += right;
    
    return s;
}

bool operator==(const String &left, const String &right) {
    return (strcmp(left.str, right.str) == 0);
}

bool operator!=(const String &left, const String &right) {
    return (strcmp(left.str, right.str) != 0);
}

bool operator ==(const String &left, const char *right) {
    return (strcmp(left.str, right) == 0);
}

bool operator !=(const String &left, const char *right) {
    return (strcmp(left.str, right) != 0);
}

String::operator std::string() const {
    return toStdString();
}

std::ostream &operator<<(std::ostream &left, const String &right) {
    if (!right.str) {
        left << "";
        return left;
    }
    
    left << right.str;
    return left;
}
