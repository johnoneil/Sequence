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
  Sequence(const ServiceablePtr& seq);
	Sequence(const Sequence& other);

	Sequence& Then(const ServiceablePtr& sequence);
	Sequence& Then(const Sequence& sequence);
	Sequence& First(const Sequence& sp);
	Sequence& While(const ServiceablePtr& sp);
	Sequence operator=(const ServiceablePtr& seq);
	Sequence operator=(const Sequence& other);

	bool Update(const float dt);

private:
	ServiceablePtr m_sequence;
};

#endif

