/*
vim: set ts=2 expandtab:

file: And.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Sunday, Oct 28th, 2015

  "And" rendezvous of a series of parallel tasks
  
*/
#ifndef __OR_HPP__
#define __OR_HPP__
#include "Serviceable.hpp"
#include "Sequence.hpp"
#include <list>

namespace Chain
{

Sequence Either(const Sequence& seq);

class OrSequence : public Serviceable
{
public:
  OrSequence(const Sequence& seq);
  OrSequence(const ServiceablePtr& seq);

  ServiceablePtr Or(const ServiceablePtr& seq);

private:
	void DoService(const float dt);

private:
  std::list< ServiceablePtr > m_tasks;

};

}

#endif
