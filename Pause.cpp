/*
vim: set ts=2 expandtab:

file: Pause.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Task which does nothing. Just returns
  complete in X seconds.
  
*/
#include "Pause.hpp"
#include "Sequence.hpp"

#include <boost/make_shared.hpp>
#include <iostream>

using boost::shared_ptr;
using boost::make_shared;
using std::cout;
using std::endl;

Sequence Pause(const float time)
{
  return Sequence(make_shared< PauseTask >(time));
}
Sequence Timeout(const float time)
{
  return Pause(time);
}
Sequence Wait(const float time)
{
  return Pause(time);
}

PauseTask::PauseTask(const float timeSeconds)
  :m_timeToRun(timeSeconds)
  ,m_timeRun(0.0f)
{

}

void PauseTask::DoService(const float dt)
{
  m_timeRun+=dt;
  cout<<"PauseTask::DoService "<<m_timeRun<<" of "<<m_timeToRun<<endl;
  if(m_timeRun>=m_timeToRun)
  {
    Done();
  }
}
