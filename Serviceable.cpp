/*
vim: set ts=2 expandtab:

file: Serviceable.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Base class for serviceable task.
  
*/
#include "Serviceable.hpp"
#include <boost/make_shared.hpp>
#include <iostream>
using boost::shared_ptr;
using boost::make_shared;
using std::cout;
using std::endl;

//TODO: namespace mgmt

Serviceable::Serviceable()
  :m_updated(false)
  ,m_complete(false)
{

}

Serviceable::~Serviceable()
{

}

void Serviceable::Cancel(void)
{
  cout<<"Serviceable::Cancel"<<endl;
  Done();
  AfterCompletion();
}

ServiceablePtr Serviceable::Then(const ServiceablePtr& sp)
{
	//TODO: prevent circular/doubled referenes.
	//these may cause infinite loops.
	cout<<"Serviceable::Then"<<endl;
	if(sp && !m_series)
	{
		cout<<"final"<<endl;
		m_series = sp;
	}else if(sp && m_series){
		cout<<"Nest"<<endl;
		m_series->Then(sp);
	}
	return shared_from_this();
}

ServiceablePtr Serviceable::Service(const float dt)
{
	cout<<"Serviceable::Service"<<endl;
	if(!m_updated)
	{
		BeforeFirstUpdate();
		m_updated = true;
	}

  //If the task is in some way already complete
  //we don't service this class at all
  if(!m_complete)
  {
    DoService(dt);
  }

  //TODO: protect against running completion handler multiple times
  //if this class gets serviced multiple times after completion?
  //it shouldn't happen, but we ought to guarrantee it only runs once.
	if(m_complete)
	{
    //TODO: fire a global event to notify listeners this task has completed?
		AfterCompletion();
		return m_series;	
	}else{
		return shared_from_this();
	}
}

void Serviceable::DoService(const float dt)
{
  //This base implementation just returns completes on first service
  Done();
}
void Serviceable::BeforeFirstUpdate(void)
{
	cout<<"Serviceable::BeforeFirstUpdate()"<<endl;
}
void Serviceable::AfterCompletion(void)
{
	cout<<"Serviceable::AfterCompletion()"<<endl;
}


