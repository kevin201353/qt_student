#include "myqueue.h"

MyQueue::MyQueue()
{

}

MyQueue::~MyQueue()
{

}

void MyQueue::GetQueMsg(QueMsg *queMsg)
{
     QMutexLocker locker(&m_mutex);
     if (queMsg != NULL)
     {
        QueMsg msg = m_queue.dequeue();
        strcpy(queMsg->Data, msg.Data);
     }
}

void MyQueue::AddQueMsg(QueMsg queMsg)
{
     QMutexLocker locker(&m_mutex);
     m_queue.enqueue(queMsg);
}
