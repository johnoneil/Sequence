/*
vim: set ts=2 expandtab:

file: Both.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for "and" operation on tasks.
  All must complete for container to complete.
  
*/

#include "Both.hpp"
#include <iostream>

using std::cout;
using std::endl;

//Sequence Both(const ServiceablePtr& seq)
//{
//  return Sequence(make_shared< BothTask >(seq));
//}
RendezvousSequence Both(const Sequence& seq)
{
  cout<<"Both global method."<<endl;
  return RendezvousSequence(make_shared< BothTask >(seq));
}

BothTask::BothTask(const Sequence& seq)
{
  cout<<"BothTask from seq"<<endl;
  m_tasks.push_back(seq.m_sequence);
}
BothTask::BothTask(const ServiceablePtr& seq)
{
  cout<<"BothTask from serviceable prt"<<endl;
  m_tasks.push_back(seq);
}
/*BothTask::BothTask(const BothTask& other)
{
  std::list< ServiceablePtr >::const_iterator iTask =other.m_tasks.begin();
  for(;iTask!=other.m_tasks.end();++iTask)
  {
    m_tasks.push_back(*iTask);
  }
}*/
void BothTask::DoService(const float dt)
{
  std::list< ServiceablePtr >::iterator iTask =m_tasks.begin();
  bool complete = true;
  for(;iTask!=m_tasks.end();++iTask)
  {
    if(*iTask)
    {
      *iTask = (*iTask)->Service(dt);
    }
    if(*iTask)
    {
      complete = false;
    }
  }
  if(complete)
  {
    Done();
  }
  
}

//BothTask& BothTask::And(const Sequence& seq)
//{
//  m_tasks.push_back(seq.m_sequence);
//}
BothTask& BothTask::And(const ServiceablePtr& seq)
{
  cout<<"And..."<<endl;
  m_tasks.push_back(seq);
  return *this;
}

