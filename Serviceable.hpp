/*
vim: set ts=2 expandtab:

file: Serviceable.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Base class for serviceable task
  
*/
#ifndef __SERVICEABLE_HPP__
#define __SERVICEABLE_HPP__
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

using boost::shared_ptr;
using boost::make_shared;

class Serviceable;
typedef shared_ptr< Serviceable > ServiceablePtr;

class Serviceable : public boost::enable_shared_from_this< Serviceable >
{
public:
	Serviceable();
  //Serviceable(const Serviceable&);
	virtual ~Serviceable();

  //Add a serviceable task in series (run when this completes)
	ServiceablePtr Then(const ServiceablePtr& sp);
  //Add a serviceable task in parallel (run as this runs. May complete before or after)
	ServiceablePtr While(const ServiceablePtr& sp);

  //Basic service implementation. Returned pointer is the current "head" of
  //the chain of serviced tasks. Meant to be called in the form:
  //ServiceablePtr seq;
  //while( seq = seq.Service(dt))
	ServiceablePtr Service(const float dt);

  void Cancel(void);

protected:
  inline void Done(void){m_complete=true;};

private:
	//NVI implementation
  //These are the primary interfaces that task implementations
  //need define.
	virtual void DoService(const float dt);
	virtual void BeforeFirstUpdate(void);
	virtual void AfterCompletion(void);

  //Helpers
	void UpdateParallelTasks(const float dt);

  bool m_updated;
  bool m_complete;
	ServiceablePtr m_series;
	ServiceablePtr m_parallel;
private:
  
  Serviceable operator=(const Serviceable&);
};

#endif
