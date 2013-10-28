/*
vim: set ts=2 expandtab:

file: And.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Sunday, Oct 28th, 2015

  "And" rendezvous of a series of parallel tasks
  
*/
#ifndef __AND_HPP__
#define __AND_HPP__
#include "Serviceable.hpp"
#include "Sequence.hpp"
#include <list>


Sequence Both(const Sequence& seq);

class AndSequence : public Serviceable
{
public:
  AndSequence(const Sequence& seq);
  AndSequence(const ServiceablePtr& seq);

  ServiceablePtr And(const ServiceablePtr& seq);
  //ServiceablePtr And(const Sequence& seq);

private:
	void DoService(const float dt);

private:
  std::list< ServiceablePtr > m_tasks;

};

#endif
