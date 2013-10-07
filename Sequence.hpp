/*
vim: set ts=2 expandtab:

file: Sequence.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for serviceable sequence of tasks.
  
*/
#ifndef __SEQUENCE_HPP__
#define __SEQUENCE_HPP__
#include "Serviceable.hpp"

class Sequence
{
public:
  friend class BothTask;
  friend class EitherTask;
  friend class RendezvousSequence;
  friend class OrSequence;

  Sequence(const ServiceablePtr& seq);
	Sequence(const Sequence& other);

	Sequence& Then(const ServiceablePtr& sequence);
	Sequence& Then(const Sequence& sequence);
	Sequence& While(const ServiceablePtr& sp);
  Sequence& While(const Sequence& sequence);

	Sequence operator=(const ServiceablePtr& seq);
	Sequence operator=(const Sequence& other);
  //Sequence operator=(const BothTask& both); 

	bool Update(const float dt);

protected:
	ServiceablePtr m_sequence;
};

class RendezvousSequence: public Sequence
{
public:
  RendezvousSequence(const Sequence& seq);
  RendezvousSequence(const ServiceablePtr& seq);

  RendezvousSequence& And(const ServiceablePtr& seq);
  RendezvousSequence& And(const Sequence& seq);
};

class OrSequence: public Sequence
{
public:
  OrSequence(const Sequence& seq);
  OrSequence(const ServiceablePtr& seq);

  OrSequence& Or(const ServiceablePtr& seq);
  OrSequence& Or(const Sequence& seq);
};

#endif

