/*
 * stack.h
 *
 *  Created on: Apr 8, 2019
 *      Author: dgv130030
 */

#ifndef STACK_H_
#define STACK_H_

#include <cstddef>
#include <cassert>
#include <iostream>

template <class Type>
class stack;

template <class Type>
class stackEntry
{
    friend class stack<Type>;
protected:
    Type              dataValue;
    stackEntry<Type>* pNext;
    
    stackEntry()
    :dataValue(), pNext(nullptr)
    {
        
    }
    
    stackEntry(Type& value)
    : dataValue(value), pNext(nullptr)
    {
    }
    
    stackEntry(const Type &newData, stackEntry<Type> *newNext = nullptr)
    {
        dataValue = newData;
        pNext = newNext;
    }
   virtual ~stackEntry()
    {
    }
    
    virtual void next(stackEntry<Type> *pNext)
    {
        this->pNext = pNext;
    }
    virtual Type& data()
    {
        return dataValue;
    }
    virtual const Type& data() const
    {
        return dataValue;
    }
    virtual stackEntry<Type>* next()
    {
        return pNext;
    }
    
    
};

template <class Type>
class stack
{
private:
    stackEntry<Type>* pTop;
    std:: size_t count;
public:
    stack()
    {
        pTop = nullptr;
        count = 0;
    }
    stack(const stack &other)
    {
        if(other.pTop)
        {
            stackEntry<Type>* tempNode = other.pTop;
            while(tempNode)
            {
                push(tempNode->data());
                tempNode= tempNode->next();
            }
        }

    }
    const stack& operator=(const stack &other)
    {
        if(other.pTop)
        {
            clear();
            stackEntry<Type>* tempNode = other.pTop;
            while(tempNode)
            {
                push(tempNode->data());
                tempNode= tempNode->next();
            }
        }
        return *this;
    }
    virtual ~stack()
    {
        clear();
        pTop = nullptr;
        
    }
    const Type& top() const
    {
        return pTop->data();
    }
    Type& top()
    {
        return pTop->data();
    }
    bool empty() const
    {
        return count == 0;
    }
    std::size_t size() const
    {
        return count;
    }
    void push(const Type &value)
    {
        stackEntry<Type>* tempNode = nullptr;
        tempNode = new stackEntry<Type>(value, pTop);
        
        if(empty())
        {
            pTop = tempNode;
            tempNode->next(nullptr);
        }
        else
        {
            tempNode->next(pTop);
            pTop = tempNode;
        }
        count++;
    }
    
    void pop()
    {
        stackEntry<Type>* tempNode = nullptr;
        if(empty())
            return;
        else
        {
            tempNode = pTop->next();
            delete pTop;
            pTop = tempNode;
            count--;
        }
    }
    void clear()
    {
        stackEntry<Type>* nodePtr = nullptr;
        stackEntry<Type>* nextNode = nullptr;
        nodePtr = pTop;
        while(nodePtr)
        {
            nextNode = nodePtr->next();
            delete nodePtr;
            nodePtr = nextNode;
            count--;
        }
        pTop = nullptr;
    }
    
    void debug() const;
    void debug(std::ostream &out) const;
};

template <class Type>
void stack<Type>::debug() const
{
    debug(std::cout);
}

template <class Type>
void stack<Type>::debug(std::ostream &out) const
{
    {
        out << "Number of items in stack: " << count << std::endl;
        out << "Top of stack is entry @" << pTop << std::endl;
        
        stackEntry<Type> *pNext = pTop;
        
        while (pNext != nullptr)
        {
            out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
            pNext = pNext->next();
        }
    }
}

#endif /* STACK_H_ */
