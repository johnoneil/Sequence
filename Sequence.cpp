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
//#include "Both.hpp"
//#include "Either.hpp"
#include "And.hpp"
#include <iostream>
#include <boost/make_shared.hpp>
using std::cout;
using std::endl;

Sequence::Sequence(const ServiceablePtr& seq)
	:m_sequence(seq)
{
  cout<<"Sequence::Sequence ptr"<<endl;
}

Sequence::Sequence(const Sequence& other)
	:m_sequence(other.m_sequence)	
{
  cout<<"Sequence::Sequence seq"<<endl;
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
  shared_ptr<AndSequence> sp=make_shared< AndSequence >(s);
  sp->And(seq);
  return Sequence(sp);
}
Sequence Sequence::And(const Sequence& seq)
{
  ServiceablePtr s=m_sequence;
  shared_ptr<AndSequence> sp=make_shared< AndSequence >(s);
  sp->And(seq.m_sequence);
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
  cout<<"Sequence::DoUpdate"<<endl;
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
/*
SequenceAndWrapper::SequenceAndWrapper(const Sequence& seq)
  :Sequence(seq)
{
  cout<<"SequenceAndWrapper::SequenceAndWrapper seq"<<endl;
}
SequenceAndWrapper::SequenceAndWrapper(const ServiceablePtr& seq)
  :Sequence(seq)
{
  cout<<"SequenceAndWrapper::SequenceAndWrapper ptr"<<endl;
}

SequenceAndWrapper& SequenceAndWrapper::And(const Sequence& seq)
{
  cout<<"SequenceAndWrapper::And seq"<<endl;
  if(m_sequence)
  {
    m_sequence->While(seq.m_sequence);
  }else{
    m_sequence = seq.m_sequence;
  }
  return *this;
}
SequenceAndWrapper& SequenceAndWrapper::And(const ServiceablePtr& seq)
{
 cout<<"SequenceAndWrapper::And ptr"<<endl;
  if(m_sequence)
  {
    m_sequence->While(seq);
  }else{
    m_sequence = seq;
  }
  return *this;
}

SequenceAndWrapper And(const Sequence& seq)
{
  cout<<__FUNCTION__<<endl;
  return SequenceAndWrapper(make_shared< SequenceAndWrapper >(seq));
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

OrSequence::OrSequence(const Sequence& seq)
  :Sequence(seq)
{
  cout<<"OrSequence const from seq"<<endl;
}
OrSequence::OrSequence(const ServiceablePtr& seq)
  :Sequence(seq)
{
  cout<<"OrSequence const from ServiceablePtr"<<endl;
}

OrSequence& OrSequence::Or(const ServiceablePtr& seq)
{
  cout<<"OrSequence const from seq ServiceablePtr&"<<endl;
  return *this;
}
OrSequence& OrSequence::Or(const Sequence& seq)
{
  cout<<"OrSequence::Or Sequence&"<<endl;
  //attempt to upcast current ServiceablePtr to a BothTask
  shared_ptr< EitherTask > eitherseq = boost::dynamic_pointer_cast< EitherTask >(m_sequence);
  if(eitherseq)
  {
    eitherseq->Or(seq.m_sequence);
  }
  return *this;
}
*/
