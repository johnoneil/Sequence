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
//#include "And.hpp"

class AndSequence;

class Sequence
{
public:
  friend class AndSequence;

  Sequence(const ServiceablePtr& seq);
	Sequence(const Sequence& other);

	Sequence& Then(const ServiceablePtr& sequence);
	Sequence& Then(const Sequence& sequence);

  virtual Sequence And(const ServiceablePtr& seq);
  virtual Sequence And(const Sequence& seq);

	Sequence operator=(const ServiceablePtr& seq);
	Sequence operator=(const Sequence& other);

	bool Update(const float dt);
  bool IsComplete(void)const;

protected:
  virtual bool DoUpdate(const float dt);
	ServiceablePtr m_sequence;
};

/*
class SequenceAndWrapper: public Serviceable, public Sequence
{
public:
  SequenceAndWrapper(const Sequence& seq);
  SequenceAndWrapper(const ServiceablePtr& seq);

  SequenceAndWrapper& And(const Sequence& seq);
  SequenceAndWrapper& And(const ServiceablePtr& seq);
};

SequenceAndWrapper And(const Sequence& seq);

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
*/
#endif

