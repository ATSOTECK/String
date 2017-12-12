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

#ifndef __SKYLER_STRINGFUNCTIONS_H__
#define __SKYLER_STRINGFUNCTIONS_H__

#include <stdint.h>

#if defined (__APPLE__) && defined (__MACH__)
#    include "TargetConditionals.h"
#    if TARGET_OS_IPHONE || TARGET_IPHONE_SINULATOR
#		define N_IOS
#	elif TARGET_OS_MAC
#		define N_MAC
#	else
#		error This Apple OS is not supported.
#	endif
#elif defined (WIN32) || defined (_WIN32)
#	define N_WIN
#elif defined (linux) || defined (__linux) || defined (__linux__)
#    define N_LINUX
#elif defined (__FreeBSD__) || defined (__FreeBSD_Kernel__)
#	define N_FREEBSD
#endif

typedef int8_t  int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

#include <iostream>
#include <cstring>
#include <string>

class String;

//char functions
char toLower(char c);
char toUpper(char c);
char swapCase(char c);

bool isNumber(char c);
bool isHexnumber(char c);

bool isAlpha(char c);
bool isAlphanumeric(char c);
bool isUpper(char c);
bool isLower(char c);

bool isWhitespace(char c);

bool isNewline(char c);

//String functions
uint32 strLen(String str);

String toString(uint32 n);

String toUpper(const String &str);
String toLower(const String &str);

void copyStr(char *dest, const char *src, uint64 size, int64 start = 0);

struct String {
    String();
    String(const String &other);
    String(const char *s);
    String(const std::string &s);
    String(char c);
    String(int n);
    String(uint32 n);
    ~String();
    
    void init(uint64 buffSize);
    void resize(uint64 newLength);
    
    void append(char c, uint64 buffSize = 0);
    void append(const String &string, uint64 buffSize = 0);
    
    /*
     void toUpper();
     void toLower();
     */
    
    char *c_str() const;
    std::string toStdString() const;
    
    bool contains(char c, int count = 1) const;
    bool contains(const String &s, int count = 1) const;
    
    bool startsWith(const String &s, bool ignoreWhitespace = false) const;
    bool endsWith(const String &s, bool ignoreWhitespace = false) const;
    
    String stringAfterLast(char c);
    String stringAfterLast(char c, char c1);
    
    String stringAfterFirst(char c);
    String stringAfterFirst(char c, char c1);
    
    String stringBeforeFirst(char c);
    String stringBeforeFirst(char c, char c1);
    
    String stringBeforeLast(char c);
    String stringBeforeLast(char c, char c1);
    
    void erase(size_t pos, size_t count = 1);
    void clear();
    void trimLeadingWhitespace();
    void trimTrailingWhitespace();
    void trimWhitespace();
    
    bool isEmpty() const;
    
    String toUpper() const;
    String toLower() const;
    String swapCase() const;
    String reverse() const;
    
    static String number(int n);
    static String number(float n);
    static String number(double n);
    
    String &setNum(int n);
    String &setNum(float n);
    String &setNum(double n);
    
    int toInt() const;
    float toFloat() const;
    double toDouble() const;
    
    char operator[](int64 index);
    char operator[](int64 index) const;
    
    String &operator=(const String &right);
    String &operator=(const char *s);
    String &operator=(const std::string &s);
    //String &operator=(const char c);
    String operator+(const String &right);
    String operator+(const char *right);
    String operator+=(const String &right);
    String operator+=(char c);
    String operator+=(const char *c);
    String operator+=(std::string s);
    
    operator std::string() const;
    
    char *str;
    int64 length; //length of the string
    int64 size; //size of the space allocated to the string
};

String operator+(char *left, String right);
String operator+(std::string left, String right);

bool operator ==(const String &left, const String &right);
bool operator !=(const String &left, const String &right);

bool operator ==(String left, const char *right);
bool operator !=(String left, const char *right);

std::ostream &operator<<(std::ostream &left, String right);

#endif
