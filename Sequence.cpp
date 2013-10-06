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

Sequence& Sequence::First(const Sequence& sp)
{
	return Then(sp);
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
	m_sequence = m_sequence->Service(dt);
	return m_sequence;
}

