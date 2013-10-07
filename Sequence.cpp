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
#include "Both.hpp"
#include <iostream>
using std::cout;
using std::endl;

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


Sequence& Sequence::While(const ServiceablePtr& sp)
{
	if(m_sequence)
	{
		m_sequence->While(sp);
	}else{
		m_sequence = sp;
	}
	return *this;	
}

Sequence& Sequence::While(const Sequence& sequence)
{
	if(&sequence!=this)
	{
		While(sequence.m_sequence);
	}
	return *this;
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

//Sequence Sequence::operator=(const BothTask& both)
//{
//  m_sequence = both;
//}

bool Sequence::Update(const float dt)
{
	m_sequence = m_sequence->Service(dt);
	return m_sequence;
}

RendezvousSequence::RendezvousSequence(const Sequence& seq)
  :Sequence(seq)
{
  cout<<"RendezvousSequence const from seq"<<endl;
}
RendezvousSequence::RendezvousSequence(const ServiceablePtr& seq)
  :Sequence(seq)
{
  cout<<"RendezvousSequence const from ServiceablePtr"<<endl;
}

RendezvousSequence& RendezvousSequence::And(const ServiceablePtr& seq)
{
  cout<<"RendezvousSequence const from seq ServiceablePtr&"<<endl;
  return *this;
}
RendezvousSequence& RendezvousSequence::And(const Sequence& seq)
{
  cout<<"RendezvousSequence::And Sequence&"<<endl;
  //attempt to upcast current ServiceablePtr to a BothTask
  //shared_ptr< BothTask > bothseq = dynamic_cast< shared_ptr< BothTask > >(m_sequence);
  shared_ptr< BothTask > bothseq = boost::dynamic_pointer_cast< BothTask >(m_sequence);
  if(bothseq)
  {
    bothseq->And(seq.m_sequence);
  }
  return *this;

}

