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

namespace Chain
{

class Sequence
{
public:
  friend class AndSequence;
  friend class OrSequence;

  Sequence(const ServiceablePtr& seq);
  Sequence(const Sequence& other);

  Sequence& Then(const ServiceablePtr& sequence);
  Sequence& Then(const Sequence& sequence);

  virtual Sequence And(const ServiceablePtr& seq);
  virtual Sequence And(const Sequence& seq);

  virtual Sequence Or(const ServiceablePtr& seq);
  virtual Sequence Or(const Sequence& seq);

  Sequence operator=(const ServiceablePtr& seq);
  Sequence operator=(const Sequence& other);

  bool Update(const float dt);
  bool IsComplete(void)const;

protected:
  virtual bool DoUpdate(const float dt);
  ServiceablePtr m_sequence;
};

}

#endif

