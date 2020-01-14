/*
 * queue.h
 *
 *  Created on: Apr 17, 2019
 *      Author: dgv130030
 */

#ifndef QUEUE_H_
#define QUEUE_H_

template <class Type>
class queue;

template <class Type>
class queueEntry
{
    friend class queue<Type>;
    
protected:
    Type                 dataValue;
    queueEntry<Type>     *pNext;
    
    queueEntry(const Type &newData, queueEntry<Type> *newNext = nullptr)
    {
        dataValue = newData;
        pNext = newNext;
    }
    virtual ~queueEntry()
    {
        pNext = nullptr;
    }
    virtual void next(queueEntry<Type> *pNext)
    {
        this->pNext = pNext;
    }
    virtual queueEntry<Type>* next()
    {
        return pNext;
    }
    virtual Type& data()
    {
        return dataValue;
    }
    virtual const Type& data() const
    {
        return dataValue;
    }
};

template <class Type>
class queue
{
    
private:
    queueEntry<Type> *pFront;
    queueEntry<Type> *pEnd;
    std::size_t count;
public:
    queue()
    {
        pFront = nullptr;
        pEnd= nullptr;
        count = 0;
    }
    virtual ~queue()
    {
        
    }
    queue(const queue &other)
    {
        if(other.pFront)
        {
            clear();
            queueEntry<Type>* tempNode = other.pFront;
            while(tempNode)
            {
                push(tempNode->data());
                tempNode= tempNode->next();
            }
            
        }
    }
    const queue& operator=(const queue &other)
    {
        if(other.pFront)
        {
            clear();
            queueEntry<Type>* tempNode = other.pFront;
            while(tempNode)
            {
                push(tempNode->data());
                tempNode= tempNode->next();
            }
            
        }
        return *this;
    }
    const Type& front() const
    {
        return pFront->data();
    }
    Type& front()
    {
        return pFront->data();
    }
    const Type& back() const
    {
        return pEnd->data();
    }
    Type& back()
    {
        return pEnd->data();
    }
    bool empty() const
    {
        return count == 0 ;
    }
    std::size_t size() const
    {
        return count;
    }
    void push(const Type &value)
    {
        queueEntry<Type>* tempNode = nullptr;
        tempNode = new queueEntry<Type>(value,nullptr);
        if(empty())
        {
            pFront = tempNode;
            pEnd = tempNode;
            tempNode->next(nullptr);
        }
        else
        {
            pEnd->next(tempNode);
            pEnd = tempNode;
            tempNode->next(nullptr);
        }
        count++;
    }
    void pop()
    {
        queueEntry<Type>* tempNode = nullptr;
        if(empty())
            return;
        else if (count == 1)
        {
            pEnd = nullptr;
            delete pFront;
            pFront = nullptr;
            count--;
        }
        else
        {
            tempNode = pFront->next();
            delete pFront;
            pFront = tempNode;
            count--;
        }
    }
    void clear()
    {
        queueEntry<Type>* nodePtr = nullptr;
        queueEntry<Type>* nextNode = nullptr;
        nodePtr = pFront;
        while(nodePtr)
        {
            nextNode = nodePtr->next();
            delete nodePtr;
            nodePtr = nextNode;
            count--;
        }
        pFront = nullptr;
        pEnd = nullptr;
    }
    void debug() const;
    void debug(std::ostream &out) const;
    // used by applications using the queue to work with all
    //  of the items in the queue from end to front.
    void traverse(void (*applicationFunction) (const Type &nextItem))
    {
        queueEntry<Type>* nodePtr = nullptr;
        nodePtr = pFront;
        while(nodePtr)
        {
            applicationFunction(nodePtr->data());
            nodePtr = nodePtr->next();
        }
    }
};


template<class Type>
void queue<Type>::debug() const
{
    debug(std::cout);
}

template<class Type>
void queue<Type>::debug(std::ostream &out) const
{
    {
        out << "Number of items in queue: " << count << std::endl;
        out << "Front of queue is entry @" << pFront << std::endl;
        out << "End of queue is entry @" << pEnd << std::endl;
        out << std::endl;
        
        queueEntry<Type> *pNext = pFront;
        
        while (pNext != nullptr)
        {
            out << "@" << pNext << ", next @" << pNext->next() << ", data = " << pNext->data() << std::endl;
            pNext = pNext->next();
        }
    }
}
#endif /* QUEUE_H_ */
