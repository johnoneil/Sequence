/*
vim: set ts=2 expandtab:

file: Either.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for "or" operation on tasks.
  
*/

#include "Either.hpp"
#include <iostream>

using std::cout;
using std::endl;

//Sequence Either(const ServiceablePtr& seq)
//{
//  return Sequence(make_shared< EitherTask >(seq));
//}
OrSequence Either(const Sequence& seq)
{
  cout<<"Either global method."<<endl;
  return RendezvousSequence(make_shared< EitherTask >(seq));
}

EitherTask::EitherTask(const Sequence& seq)
{
  cout<<"EitherTask from seq"<<endl;
  m_tasks.push_back(seq.m_sequence);
}
EitherTask::EitherTask(const ServiceablePtr& seq)
{
  cout<<"EitherTask from serviceable prt"<<endl;
  m_tasks.push_back(seq);
}
/*EitherTask::EitherTask(const EitherTask& other)
{
  std::list< ServiceablePtr >::const_iterator iTask =other.m_tasks.begin();
  for(;iTask!=other.m_tasks.end();++iTask)
  {
    m_tasks.push_back(*iTask);
  }
}*/
void EitherTask::DoService(const float dt)
{
  std::list< ServiceablePtr >::iterator iTask =m_tasks.begin();
  bool complete = false;
  for(;iTask!=m_tasks.end();++iTask)
  {
    if(*iTask)
    {
      *iTask = (*iTask)->Service(dt);
    }
    if(!(*iTask))
    {
      complete = true;
    }
  }
  if(complete)
  {
    Done();
  }
}

void EitherTask::AfterCompletion(void)
{
  //If we still have open references to other tasks, cancel them
  std::list< ServiceablePtr >::iterator iTask =m_tasks.begin();
  for(;iTask!=m_tasks.end();++iTask)
  {
    if(*iTask)
    {
      (*iTask)->Cancel();
    }
  }
  m_tasks.clear();
  
}

//EitherTask& EitherTask::And(const Sequence& seq)
//{
//  m_tasks.push_back(seq.m_sequence);
//}
EitherTask& EitherTask::Or(const ServiceablePtr& seq)
{
  cout<<"Or..."<<endl;
  m_tasks.push_back(seq);
  return *this;
}

