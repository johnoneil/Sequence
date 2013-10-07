/*
vim: set ts=2 expandtab:

file: Either.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for serviceable sequence of tasks.
  
*/
#ifndef __EITHER_HPP__
#define __EITHER_HPP__
#include "Serviceable.hpp"
#include "Sequence.hpp"
#include <list>

class EitherTask;

//Sequence Either(const ServiceablePtr& seq);
OrSequence Either(const Sequence& seq);
//EitherTask Either(const Sequence& seq);
//EitherTask Either(const ServiceablePtr& seq);

class EitherTask: public Serviceable
{
public:
  friend class OrTask;

  EitherTask(const Sequence& seq);
  EitherTask(const ServiceablePtr& seq);
  //EitherTask(const EitherTask&);
  void DoService(const float dt);
  void AfterCompletion(void);

  //EitherTask& And(const Sequence& seq);
  EitherTask& Or(const ServiceablePtr& seq);
private:
  std::list< ServiceablePtr > m_tasks;
private:
  EitherTask();
  EitherTask operator=(const EitherTask&);
};

#endif
