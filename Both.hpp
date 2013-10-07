/*
vim: set ts=2 expandtab:

file: Both.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for serviceable sequence of tasks.
  
*/
#ifndef __BOTH_HPP__
#define __BOTH_HPP__
#include "Serviceable.hpp"
#include "Sequence.hpp"
#include <list>

class BothTask;

//Sequence Both(const ServiceablePtr& seq);
RendezvousSequence Both(const Sequence& seq);
//BothTask Both(const Sequence& seq);
//BothTask Both(const ServiceablePtr& seq);

class BothTask: public Serviceable
{
public:
  friend class RendezvousTask;

  BothTask(const Sequence& seq);
  BothTask(const ServiceablePtr& seq);
  //BothTask(const BothTask&);
  void DoService(const float dt);

  //BothTask& And(const Sequence& seq);
  BothTask& And(const ServiceablePtr& seq);
private:
  std::list< ServiceablePtr > m_tasks;
private:
  BothTask();
  BothTask operator=(const BothTask&);
};

#endif
