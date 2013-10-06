/*
vim: set ts=2 expandtab:

file: Sequence.hpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com
DATE: Saturday, Oct 5th 2013

  Wrapper for serviceable sequence of tasks.
  
*/
#ifndef __PAUSE_HPP__
#define __PAUSE_HPP__
#include "Serviceable.hpp"
#include "Sequence.hpp"

Sequence Pause(const float time);

class PauseTask: public Serviceable
{
public:
  PauseTask(const float timeSeconds);
  void DoService(const float dt);
private:
  const float m_timeToRun;
  float m_timeRun;
private:
  PauseTask();
  PauseTask(const PauseTask&);
  PauseTask operator=(const PauseTask&);
};

#endif
