/*
vim: set ts=2 expandtab:

file: Sequence.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for serviceable sequence of tasks.
  
*/
 
#include "Sequence.hpp"
#include "And.hpp"
#include "Or.hpp"
#include <iostream>
#include <boost/make_shared.hpp>
using std::cout;
using std::endl;

using namespace Chain;

Sequence::Sequence(const ServiceablePtr& seq)
	:m_sequence(seq)
{

}

Sequence::Sequence(const Sequence& other)
	:m_sequence(other.m_sequence)	
{

}

Sequence& Sequence::Then(const ServiceablePtr& sequence)
{
	if(m_sequence)
	{
		m_sequence->Then(sequence);
	}else{
		m_sequence = sequence;
	}
	return *this;
}

Sequence& Sequence::Then(const Sequence& sequence)
{
	if(&sequence!=this)
	{
		Then(sequence.m_sequence);
	}
	return *this;
}

Sequence Sequence::And(const ServiceablePtr& seq)
{

  ServiceablePtr s=m_sequence;
  shared_ptr< AndSequence > sp=make_shared< AndSequence >(s);
  sp->And(seq);
  return Sequence(sp);
}
Sequence Sequence::And(const Sequence& seq)
{
  ServiceablePtr s=m_sequence;
  shared_ptr< AndSequence > sp=make_shared< AndSequence >(s);
  sp->And(seq.m_sequence);
  return Sequence(sp);
}

Sequence Sequence::Or(const ServiceablePtr& seq)
{

  ServiceablePtr s=m_sequence;
  shared_ptr< OrSequence > sp=make_shared< OrSequence >(s);
  sp->Or(seq);
  return Sequence(sp);
}
Sequence Sequence::Or(const Sequence& seq)
{
  ServiceablePtr s=m_sequence;
  shared_ptr< OrSequence > sp=make_shared< OrSequence >(s);
  sp->Or(seq.m_sequence);
  return Sequence(sp);
}

Sequence Sequence::operator=(const ServiceablePtr& seq)
{
	//No matter its current state, this assigns the given
	//sequence as the primary sequence this is the head of
	m_sequence = seq;
}

Sequence Sequence::operator=(const Sequence& other)
{
	if(&other!=this)
	{
		m_sequence = other.m_sequence;
	}
	return *this;
}


bool Sequence::Update(const float dt)
{
  return DoUpdate(dt);
}

bool Sequence::DoUpdate(const float dt)
{

  while(m_sequence)
  {
    ServiceablePtr currentSeq = m_sequence->Service(dt);
    if(currentSeq==m_sequence)
    {
      break;
    }else{
      m_sequence = currentSeq;
    }
  }
	return m_sequence;
}

bool Sequence::IsComplete(void)const
{
  return m_sequence;
}

