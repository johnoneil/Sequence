/*
vim: set ts=2 expandtab:

file: Or.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Sunday, Oct 28th, 2015

  "Or" rendezvous of a series of parallel tasks
  
*/
#include "Or.hpp"

OrSequence::OrSequence(const Sequence& seq)
{
	m_tasks.push_back(seq.m_sequence);
};

ServiceablePtr OrSequence::Or(const ServiceablePtr& seq)
{
	m_tasks.push_back(seq);
	return shared_from_this();
};

OrSequence::OrSequence(const ServiceablePtr& seq)
{
	m_tasks.push_back(seq);
}

void OrSequence::DoService(const float dt)
  {
    bool complete = false;
    for(std::list< ServiceablePtr >::iterator itask=m_tasks.begin();
        itask!=m_tasks.end(); ++itask)
    {
      if(*itask)
      {
        (*itask) = (*itask)->Service(dt);
        if(!(*itask))
        {
          complete=true;
        }
      }
    }
    if(complete)
    {
      for(std::list< ServiceablePtr >::iterator itask=m_tasks.begin();
        itask!=m_tasks.end(); ++itask)
      {
        if(*itask)
        {
          (*itask)->Cancel();
        }
      }
      Done();
    }
  };
;

Sequence Either(const Sequence& seq)
{
  return Sequence(make_shared< OrSequence >(seq));
};
