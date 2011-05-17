/*
 * Copyright (c) 2011, Rohit Grover
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither Rohit Grover, nor Aurokruti, nor the names of Aurokruti's
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef VARIOUS_PARA_CONTAINERS
#define VARIOUS_PARA_CONTAINERS

#include <cassert>
#include "containerDirective.h"

class Set : public ContainerDirective
{
public:

    Set(void)
        : ContainerDirective(SET)
        {
        }

    ~Set(void)
        {
        }

    void setAuthor(string name)
        {
            author = name;
        }

    string getAuthor(void) const
        {
            return author;
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
    string author;
};

class Book : public ContainerDirective
{
public:

    Book(void) : ContainerDirective(BOOK) {
    }

    ~Book(void) {
    }

    void setAuthor(string name)
        {
            author = name;
        }

    string getAuthor(void) const
        {
            return author;
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
    string author;
};


class Part : public ContainerDirective
{
public:

    Part(void) : ContainerDirective(PART)
        {
        }

    ~Part(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

class Preface : public ContainerDirective
{
public:

    Preface(void) : ContainerDirective(PREFACE)
        {
        }

    ~Preface(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

class Chapter : public ContainerDirective
{
public:

    Chapter(void) : ContainerDirective(CHAPTER)
        {
        }

    ~Chapter(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};


class Section : public ContainerDirective
{
public:

    Section(void) : ContainerDirective(SECTION)
        {
        }

    ~Section(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};


class Section1 : public ContainerDirective
{
public:

    Section1(void) : ContainerDirective(SECTION1)
        {
        }

    ~Section1(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

class Section2 : public ContainerDirective
{
public:

    Section2(void) : ContainerDirective(SECTION2)
        {
        }

    ~Section2(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

class Section3 : public ContainerDirective
{
public:

    Section3(void) : ContainerDirective(SECTION3)
        {
        }

    ~Section3(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

class Section4 : public ContainerDirective
{
public:

    Section4(void) : ContainerDirective(SECTION3)
        {
        }

    ~Section4(void)
        {
        }

    void setAuthor(string name)
        {
            assert(0);
        }

    string getAuthor(void) const
        {
            assert(0);
        }

    void emit(outputMode_t mode, unsigned int &indentation);
    void emitBegin(void);
    void emitEnd(void) const;

private:
};

#endif /* VARIOUS_PARA_CONTAINERS */
