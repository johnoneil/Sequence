/*
vim: set ts=2 expandtab:

file: And.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Sunday, Oct 28th, 2015

  "And" rendezvous of a series of parallel tasks
  
*/
#include "And.hpp"

namespace Chain
{

Sequence Both(const Sequence& seq)
{
  return Sequence(make_shared< AndSequence >(seq));
}

AndSequence::AndSequence(const Sequence& seq)
{
	m_tasks.push_back(seq.m_sequence);
}

ServiceablePtr AndSequence::And(const ServiceablePtr& seq)
{
	m_tasks.push_back(seq);
	return shared_from_this();
}

AndSequence::AndSequence(const ServiceablePtr& seq)
{
	m_tasks.push_back(seq);
}

void AndSequence::DoService(const float dt)
{
  bool complete = true;
  for(std::list< ServiceablePtr >::iterator itask=m_tasks.begin();
      itask!=m_tasks.end(); ++itask)
  {
    if(*itask)
    {
      (*itask) = (*itask)->Service(dt);
      complete = false;
    }else{
      
    }
  }
  if(complete){Done();}
}

}
