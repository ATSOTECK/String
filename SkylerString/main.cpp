//
//  main.cpp
//  SkylerString
//
//  Created by Skyler on 11/26/17.
//  Copyright © 2017 counterpoint. All rights reserved.
//

#include <iostream>

#include "SkylerString.hpp"
#include "StringList.hpp"

#define TEST(x) std::cerr << "L" <<  __LINE__ << " Test: " << x << " : "
#define ln() std::cerr << std::endl

namespace {
    int tests = 0;
    int passes = 0;
    int fails = 0;
}

bool pass() {
    std::cerr << ". PASS" << std::endl;
    ++passes;
    return true;
}

bool fail() {
    std::cerr << ". FAIL" << std::endl;
    ++fails;
    return false;
}

template <typename T>
bool expect(T e, T g) {
    ++tests;
    bool result = e == g;
    
    std::cerr << "Expect \"" << e << "\", got \"" << g << "\"";
    if (result) {
        return pass();
    } else {
        return fail();
    }
}

bool expect(const String &e, const String &g) {
    ++tests;
    bool result = e == g;
    
    std::cerr << "Expect \"" << e << "\", got \"" << g << "\"";
    if (result) {
        return pass();
    } else {
        return fail();
    }
}

void setTest() {
    std::cerr << "Begin setTest()" << std::endl;
    int currentFails = fails;
    
    String str = "hello";
    TEST("str = \"hello\""); expect("hello", str);
    
    std::string s1 = "world";
    std::cerr << "s1 = " << s1 << std::endl;
    str = s1;
    TEST("str = s1"); expect("world", str);
    
    char *s2 = new char[4];
    strcpy(s2, "foo");
    std::cerr << "s2 = " << s2 << std::endl;
    str = s2;
    TEST("str = s2"); expect("foo", str);
    
    String s3 = "bar";
    std::cerr << "s3 = " << s3 << std::endl;
    str = s3;
    TEST("str = s3"); expect("bar", str);

    str = 'h';
    TEST("str = 'h'"); expect("h", str);

    str = '\0';
    TEST("str = '\\0'"); expect("", str);

    str = "";
    TEST("str = \"\""); expect("", str);

    s1 = "";
    str = s1;
    std::cerr << "s1 = " << s1 << std::endl;
    TEST("str = s1"); expect("", str);
    
    strcpy(s2, "");
    std::cerr << "s2 = " << s2 << std::endl;
    str = s2;
    TEST("str = s2"); expect("", str);
    
    s3 = "";
    std::cerr << "s3 = " << s3 << std::endl;
    str = s3;
    TEST("str = s3"); expect("", str);
    
    delete[] s2;
    s2 = NULL;
    
    if (currentFails != fails) {
        std::cerr << "setTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "setTest() PASSED" << std::endl << std::endl;
    }
}

void equalityTest() {
    std::cerr << "Begin equalityTest()" << std::endl;
    int currentFails = fails;
    
    String s1 = "123";
    String s2 = "123";
    
    std::cerr << "s1 = " << s1 << std::endl;
    TEST("s1 == \"123\""); expect(true,  s1 == "123");
    TEST("s1 != \"123\""); expect(false, s1 != "123");
    
    TEST("s1 == \"321\""); expect(false, s1 == "321");
    TEST("s1 != \"321\""); expect(true,  s1 != "321");
    
    std::cerr << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
    TEST("s1 == s2"); expect(true,  s1 == s2);
    TEST("s1 != s2"); expect(false, s1 != s2);
    
    s2 = "321";
    std::cerr << "s1 = " << s1 << ", s2 = " << s2 << std::endl;
    TEST("s1 == s2"); expect(false, s1 == s2);
    TEST("s1 != s2"); expect(true,  s1 != s2);
    
    char *s3 = new char[4];
    strcpy(s3, "123");
    
    std::cerr << "s1 = " << s1 << ", s3 = " << s3 << std::endl;
    TEST("s1 == s3"); expect(true,  s1 == s3);
    TEST("s1 != s3"); expect(false, s1 != s3);
    
    strcpy(s3, "321");
    
    std::cerr << "s1 = " << s1 << ", s3 = " << s3 << std::endl;
    TEST("s1 == s3"); expect(false, s1 == s3);
    TEST("s1 != s3"); expect(true,  s1 != s3);
    
    delete[] s3;
    s3 = NULL;
    
    if (currentFails != fails) {
        std::cerr << "equalityTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "equalityTest() PASSED" << std::endl << std::endl;
    }
}

void constructorTest() {
    std::cerr << "Begin constructorTest()" << std::endl;
    int currentFails = fails;

    String str = String("123");
    TEST("String(\"123\")"); expect("123", str);

    String s1 = "321";
    str = String(s1);
    TEST("String(s1)"); expect("321", str);

    std::string s2 = "456";
    str = String(s2);
    TEST("String(s2)"); expect("456", str);

    char *s3 = new char[4];
    strcpy(s3, "789");
    str = String(s3);
    TEST("String(s3)"); expect("789", str);

    s1 = "";
    str = String(s1);
    TEST("String(s1)"); expect("", str);

    s2 = "";
    str = String(s2);
    TEST("String(s2)"); expect("", str);

    strcpy(s3, "");
    str = String(s3);
    TEST("String(s3)"); expect("", str);

    char c = 'h';
    str = String(c);
    TEST("String(c)"); expect("h", str);

    c = '\0';
    str = String(c);
    TEST("String(c)"); expect("", str);

    int n = 123;
    str = String(n);
    TEST("String(n)"); expect("123", str);

    n = -123;
    str = String(n);
    TEST("String(n)"); expect("-123", str);

    uint32 u = 123456789;
    str = String(u);
    TEST("String(u)"); expect("123456789", str);

    str = String();
    TEST("String()"); expect("", str);

    delete[] s3;
    s3 = NULL;

    if (currentFails != fails) {
        std::cerr << "constructorTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "constructorTest() PASSED" << std::endl << std::endl;
    }
}

void lengthTest() {
    std::cerr << "Begin lengthTest()" << std::endl;
    int currentFails = fails;

    String str = "123";
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)3, str.length);

    str = "Hello world!";
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)12, str.length);

    str = "";
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)0, str.length);

    str = 'h';
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)1, str.length);

    str = '\0';
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)0, str.length);

    std::string s1 = "Hello world!";
    str = s1;
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)s1.length(), str.length);

    String s2 = "Hey there world!";
    str = s2;
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect(s2.length, str.length);

    char *s3 = new char[4];
    strcpy(s3, "123");
    str = s3;
    std::cerr << "str = " << str << std::endl;
    TEST("str.length"); expect((int64)strlen(s3), str.length);

    if (currentFails != fails) {
        std::cerr << "lengthTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "lengthTest() PASSED" << std::endl << std::endl;
    }
}

void eraseTest() {
    std::cerr << "Begin eraseTest()" << std::endl;
    int currentFails = fails;
    
    String str = "1234567890";
    TEST("str = \"1234567890\""); expect("1234567890", str);
    
    str.erase(0);
    TEST("str.erase(0)"); expect("234567890", str);
    
    str = "1234567890";
    str.erase(0, 3);
    TEST("str.erase(0, 3)"); expect("4567890", str);
    
    str = "1234567890";
    str.erase(3);
    TEST("str.erase(3)"); expect("123567890", str);
    
    str = "1234567890";
    str.erase(3, 3);
    TEST("str.erase(3, 3)"); expect("1237890", str);
    
    if (currentFails != fails) {
        std::cerr << "eraseTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "eraseTest() PASSED" << std::endl << std::endl;
    }
}

void trimTest() {
    std::cerr << "Begin trimTest()" << std::endl;
    int currentFails = fails;
    
    String str = "   123";
    str.trimLeadingWhitespace();
    TEST("str.trimLeadingWhitespace()"); expect("123", str);
    
    str = "123   ";
    str.trimTrailingWhitespace();
    TEST("str.trimTrailingWhitespace()"); expect("123", str);
    
    str = "   123";
    str.trimWhitespace();
    TEST("str.trimWhitespace()"); expect("123", str);
    
    str = "123   ";
    str.trimWhitespace();
    TEST("str.trimWhitespace()"); expect("123", str);
    
    str = "   123   ";
    str.trimWhitespace();
    TEST("str.trimWhitespace()"); expect("123", str);
    
    str = "123";
    str.trimWhitespace();
    TEST("str.trimWhitespace()"); expect("123", str);
    
    str = "\t123\t   ";
    str.trimWhitespace();
    TEST("str.trimWhitespace()"); expect("123", str);
    
    if (currentFails != fails) {
        std::cerr << "trimTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "trimTest() PASSED" << std::endl << std::endl;
    }
}

void startsWithTest() {
    std::cerr << "Begin startsWithTest()" << std::endl;
    int currentFails = fails;
    
    String str = "hello world";
    std::cerr << "str = " << str << std::endl;
    TEST("str.startsWith(\"h\")");                 expect(true,  str.startsWith("h"));
    TEST("str.startsWith(\"w\")");                 expect(false, str.startsWith("w"));
    TEST("str.startsWith(\"hello\")");             expect(true,  str.startsWith("hello"));
    TEST("str.startsWith(\"yo\")");                expect(false, str.startsWith("yo"));
    TEST("str.startsWith(\"hello world\")");       expect(true,  str.startsWith("hello world"));
    TEST("str.startsWith(\"hello there world\")"); expect(false, str.startsWith("hello there world"));
    
    if (currentFails != fails) {
        std::cerr << "endsWithTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "endsWithTest() PASSED" << std::endl << std::endl;
    }
}

void endsWithTest() {
    std::cerr << "Begin endsWithTest()" << std::endl;
    int currentFails = fails;
    
    String str = "hello world";
    std::cerr << "str = " << str << std::endl;
    TEST("str.endsWith(\"d\")");                 expect(true,  str.endsWith("d"));
    TEST("str.endsWith(\"w\")");                 expect(false, str.endsWith("w"));
    TEST("str.endsWith(\"world\")");             expect(true,  str.endsWith("world"));
    TEST("str.endsWith(\"yo\")");                expect(false, str.endsWith("yo"));
    TEST("str.endsWith(\"hello world\")");       expect(true,  str.endsWith("hello world"));
    TEST("str.endsWith(\"hello there world\")"); expect(false, str.endsWith("hello there world"));
    
    if (currentFails != fails) {
        std::cerr << "startsWithTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "startsWithTest() PASSED" << std::endl << std::endl;
    }
}

void modifyTest() {
    std::cerr << "Begin modifyTest()" << std::endl;
    int currentFails = fails;
    
    String str = "123";
    std::cerr << "str = " << str << std::endl;
    str.append('4');
    TEST("str.append('4')"); expect("1234", str);
    
    str.append("5");
    TEST("str.append(\"5\")"); expect("12345", str);
    
    str.append("6789");
    TEST("str.append(\"6789\")"); expect("123456789", str);
    
    str = "123";
    std::cerr << "str = " << str << std::endl;
    str += '4';
    TEST("str += '4'"); expect("1234", str);
    
    str += "5";
    TEST("str += \"5\""); expect("12345", str);
    
    str += "6789";
    TEST("str += \"6789\""); expect("123456789", str);
    
    str = "123";
    std::cerr << "str = " << str << std::endl;
    char *s1 = new char[4];
    strcpy(s1, "456");
    std::cerr << "s1 = " << s1 << std::endl;
    str += s1;
    TEST("str += s1"); expect("123456", str);
    
    str = "123";
    std::cerr << "str = " << str << std::endl;
    std::string s2 = "456";
    std::cerr << "s2 = " << s2 << std::endl;
    str += s2;
    TEST("str += s2"); expect("123456", str);
    
    str = "123";
    std::cerr << "str = " << str << std::endl;
    String s3 = "456";
    std::cerr << "s3 = " << s3 << std::endl;
    str += s3;
    TEST("str += s3"); expect("123456", str);
    
    
    if (currentFails != fails) {
        std::cerr << "modifyTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "modifyTest() PASSED" << std::endl << std::endl;
    }
}

void numbersTest() {
    std::cerr << "Begin numbersTest()" << std::endl;
    int currentFails = fails;

    String str = String::number(10);
    TEST("str = String::number(10)"); expect("10", str);

    str = String::number(10.3f);
    TEST("str = String::number(10.3f)"); expect("10.3", str);

    str = String::number((double)10.3);
    TEST("str = String::number((double)10.3)"); expect("10.3", str);

    str.setNum(12);
    TEST("str.setNum(12)"); expect("12", str);

    str.setNum(12.2f);
    TEST("str.setNum(12.2f)"); expect("12.2", str);

    str.setNum((double)12.3);
    TEST("str.setNum((double)12.3)"); expect("12.3", str);

    str = "12.3";
    std::cerr << "str = " << str << std::endl;
    
    int i = str.toInt();
    TEST("int i = str.toInt()"); expect(12, i);

    float f = str.toFloat();
    TEST("float f = str.toFloat()"); expect(12.3f, f);

    double d = str.toDouble();
    TEST("double d = str.toDouble()"); expect(12.3, d);

    if (currentFails != fails) {
        std::cerr << "numbersTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "numbersTest() PASSED" << std::endl << std::endl;
    }
}

void indexTest() {
    std::cerr << "Begin indexTest()" << std::endl;
    int currentFails = fails;

    String str = "123hello world456";
    std::cerr << "str = " << str << std::endl;

    TEST("str[0]"); expect('1', str[0]);
    TEST("str[16]"); expect('6', str[16]);
    TEST("str[8]"); expect(' ', str[8]);
    TEST("str[80]"); expect('\0', str[80]);
    TEST("str[-8]"); expect('\0', str[-8]);

    if (currentFails != fails) {
        std::cerr << "indexTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "indexTest() PASSED" << std::endl << std::endl;
    }
}

void beforeAfterTest() {
    std::cerr << "Begin beforeAfterTest()" << std::endl;
    int currentFails = fails;

    String str = "what even is this";
    std::cerr << "str = " << str << std::endl;

    TEST("str.stringAfterLast('e')"); expect("n is this", str.stringAfterLast('e'));
    TEST("str.stringAfterLast('q', t')"); expect("his", str.stringAfterLast('q', 't'));
    TEST("str.stringAfterLast('t', q')"); expect("his", str.stringAfterLast('t', 'q'));

    TEST("str.stringAfterFirst('e')"); expect("ven is this", str.stringAfterFirst('e'));
    TEST("str.stringAfterFirst('q', t')"); expect(" even is this", str.stringAfterFirst('q', 't'));
    TEST("str.stringAfterFirst('t', q')"); expect(" even is this", str.stringAfterFirst('t', 'q'));

    TEST("str.stringBeforeFirst('e')"); expect("what ", str.stringBeforeFirst('e'));
    TEST("str.stringBeforeFirst('q', t')"); expect("wha", str.stringBeforeFirst('q', 't'));
    TEST("str.stringBeforeFirst('t', q')"); expect("wha", str.stringBeforeFirst('t', 'q'));

    TEST("str.stringBeforeLast('e')"); expect("what ev", str.stringBeforeLast('e'));
    TEST("str.stringBeforeLast('q', t')"); expect("what even is ", str.stringBeforeLast('q', 't'));
    TEST("str.stringBeforeLast('t', q')"); expect("what even is ", str.stringBeforeLast('t', 'q'));

    if (currentFails != fails) {
        std::cerr << "beforeAfterTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "beforeAfterTest() PASSED" << std::endl << std::endl;
    }
}

void caseTest() {
    std::cerr << "Begin caseTest()" << std::endl;
    int currentFails = fails;

    String str = "What up loser";
    std::cerr << "str = " << str << std::endl;

    TEST("str.toUpper()"); expect("WHAT UP LOSER", str.toUpper());
    TEST("str.toLower()"); expect("what up loser", str.toLower());

    str = "WhAt Up LoSeR";
    std::cerr << "str = " << str << std::endl;

    TEST("str.swapCase()"); expect("wHaT uP lOsEr", str.swapCase());

    if (currentFails != fails) {
        std::cerr << "caseTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "caseTest() PASSED" << std::endl << std::endl;
    }
}

void miscTest() {
    std::cerr << "Begin miscTest()" << std::endl;
    int currentFails = fails;

    String str = "123";
    std::cerr << "str = " << str << std::endl;

    TEST("str.isEmpty()"); expect(false, str.isEmpty());

    str = "";
    std::cerr << "str = " << str << std::endl;
    TEST("str.isEmpty()"); expect(true, str.isEmpty());

    str = "123456";
    std::cerr << "str = " << str << std::endl;
    TEST("str.reverse()"); expect("654321", str.reverse());

    if (currentFails != fails) {
        std::cerr << "miscTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "miscTest() PASSED" << std::endl << std::endl;
    }
}

void convertTest() {
    std::cerr << "Begin convertTest()" << std::endl;
    int currentFails = fails;

    String str = "Hello world!";
    std::cerr << "str = " << str << std::endl;

    char *chr = new char[str.length];
    strcpy(chr, str.str);
    TEST("strcpy(chr, str.str)"); expect("Hello world!", chr);

    strcpy(chr, "123");
    std::cerr << "chr = " << chr << std::endl;
    strcpy(chr, str.c_str());
    TEST("strcpy(chr, str.c_str())"); expect("Hello world!", chr);

    std::string stdstr;
    stdstr = str.toStdString();
    TEST("stdstr = str.toStdString()"); expect("Hello world!", stdstr);

    stdstr = "123";
    std::cerr << "stdstr = " << chr << std::endl;
    stdstr = str.toStdString();
    TEST("stdstr = str.toStdString()"); expect("Hello world!", stdstr);

    if (currentFails != fails) {
        std::cerr << "convertTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "convertTest() PASSED" << std::endl << std::endl;
    }
}

void stringListTest() {
    std::cerr << "Begin stringListTest()" << std::endl;
    int currentFails = fails;

    StringList list;
    list.append("hello");
    list.append("there");
    list.append("beautiful");
    list.append("world");//3
    list.append("what");
    list.append("we");
    list.append("live");
    list.append("in");
    list.append("world");//8
    list.append("what");
    list.append("we");
    list.append("live");
    list.append("in");//12
    
    int i = list.indexOf("world");
    TEST("list.indexOf(\"world\")"); expect(3, i);
    //std::cerr << i << std::endl;
    i = list.indexOfFirst("world");
    TEST("list.indexOfFirst(\"world\")"); expect(3, i);
    //std::cerr << i << std::endl;
    i = list.indexOfLast("world");
    TEST("list.indexOfLast(\"world\")"); expect(8, i);
    //std::cerr << i << std::endl;

    TEST("list.count() == 13"); expect((size_t)13, list.count());
    TEST("list.clear()");
    list.clear();
    TEST("list.count() == 0"); expect((size_t)0, list.count());

    list.append("hi");
    list.append("ho");
    list.append("he");

    String join = list.join(", ");
    TEST("list.join(\", \")"); expect("hi, ho, he", join);

    String joinc = list.join('|');
    TEST("list.join('|')"); expect("hi|ho|he", joinc);

    String at = list.at(1);
    TEST("list.at(1)"); expect("ho", at);
    at = list.at(-1);
    TEST("list.at(-1)"); expect("", at);
    at = list.at(12);
    TEST("list.at(12)"); expect("", at);

    list.erase(1);
    TEST("list.erase(1)");
    joinc = list.join('|');
    expect("hi|he", joinc);

    list.erase(-1);
    TEST("list.erase(-1)");
    joinc = list.join('|');
    expect("hi|he", joinc);

    list.erase(12);
    TEST("list.erase(12)");
    joinc = list.join('|');
    expect("hi|he", joinc);

    list.clear();
    list.append("hi");
    list.append("ho");
    list.append("he");//<
    list.append("ni");//<
    list.append("no");//<
    list.append("ne");

    list.erase(2, 4);
    TEST("list.erase(2, 4)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.erase(-1, 4);
    TEST("list.erase(-1, 4)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.erase(2, -4);
    TEST("list.erase(2, -4)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.erase(4, 2);
    TEST("list.erase(4, 2)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.erase(2, 40);
    TEST("list.erase(2, 40)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.erase(20, 4);
    TEST("list.erase(20, 4)");
    joinc = list.join('|');
    expect("hi|ho|ne", joinc);

    list.removeFirst();
    TEST("list.removeFirst()"); expect("ho", list.at(0));
    TEST("list.count() == 2"); expect((size_t)2, list.count());
    list.removeLast();
    TEST("list.removeLast()"); expect("ho", list.at(list.count() - 1));
    TEST("list.count() == 1"); expect((size_t)1, list.count());

    list.clear();
    list.append("hi");
    list.append("ho");
    list.append("he");
    
    String ta = list.takeAt(1);
    TEST("list.takeAt(1)"); expect("ho", ta);
    TEST("list.count()"); expect((size_t)2, list.count());

    list.clear();
    list.append("hi");
    list.append("ho");
    list.append("he");
    
    String tf = list.takeFirst();
    TEST("list.takeFirst()"); expect("hi", tf);
    TEST("list.count()"); expect((size_t)2, list.count());

    list.clear();
    list.append("hi");
    list.append("ho");
    list.append("he");

    String tl = list.takeLast();
    TEST("list.takeLast()"); expect("he", tl);
    TEST("list.count()"); expect((size_t)2, list.count());

    TEST("list.first()"); expect("hi", list.first());
    TEST("list.last()"); expect("ho", list.last());

    TEST("list.IsEmpty()"); expect(false, list.isEmpty());
    list.eraseAll();
    TEST("list.IsEmpty()"); expect(true, list.isEmpty());

    list.append("hi");
    list.append("ho");
    list.append("he");

    list.insert(1, "yo");
    TEST("list.at(1)"); expect("yo", list.at(1));
    TEST("list.count()"); expect((size_t)4, list.count());

    list.insert(-1, "bo");
    TEST("list.count()"); expect((size_t)4, list.count());

    list.insert(4, "bo");
    TEST("list.count()"); expect((size_t)4, list.count());

    list.prepend("lo");
    TEST("list.first()"); expect("lo", list.first());
    TEST("list.count()"); expect((size_t)5, list.count());

    for (int i = 0; i < 10; ++i) {
        std::cerr << list.getRandom() << " ";
    }
    ln();
    
    if (currentFails != fails) {
        std::cerr << "stringListTest() FAILED" << std::endl << std::endl;
    } else {
        std::cerr << "stringListTest() PASSED" << std::endl << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));

    setTest();
    equalityTest();
    constructorTest();
    lengthTest();
    eraseTest();
    trimTest();
    startsWithTest();
    endsWithTest();
    modifyTest();
    numbersTest();
    indexTest();
    beforeAfterTest();
    caseTest();
    miscTest();
    convertTest();
    
    //std::cerr << std::endl;
    std::cerr << "===========RESULTS===========" << std::endl;
    std::cerr << tests << " tests run." << std::endl;
    std::cerr << passes << "/" << tests << " passed." << std::endl;
    std::cerr << fails << "/" << tests << " failed." << std::endl;
    std::cerr << "=============================" << std::endl;
    std::cerr << std::endl;
    
    tests = 0;
    passes = 0;
    fails = 0;

    stringListTest();

    //std::cerr << std::endl;
    std::cerr << "===========RESULTS===========" << std::endl;
    std::cerr << tests << " tests run." << std::endl;
    std::cerr << passes << "/" << tests << " passed." << std::endl;
    std::cerr << fails << "/" << tests << " failed." << std::endl;
    std::cerr << "=============================" << std::endl;
    
    return 0;
}
