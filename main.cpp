/*
vim: set ts=2 expandtab:

file: main.cpp
Desc:
Author: John O'Neil
Email: oneil.john@gmail.com

  Simple example using multimedia sequence classes for:
  building simple sequences (A then B then C)
  Rendezvous by completion of all tasks in parallel (A and B and C)
  Rendezvous by first completion of tasks in parallel (A or B or C)
  
*/
#include "Sequence.hpp"
#include "Pause.hpp"
#include "And.hpp"
#include "Or.hpp"

int main(int argc, char* argv[])
{
	Sequence seq1 = Both(Pause(10.0f).Then(Pause(3.0f)) ).And(Pause(20.0f)).And(Pause(30.0f));
	Sequence seq2 = Either(Pause(10.0f).Then(Pause(3.0f))).Or(Pause(20.0f)).Or(Pause(30.0f));
	Sequence seq = seq1.Then(seq2).Then(Pause(5.0f));


	//Button press with blink and timeout
	//Sequence getButtonPress = Either(GetButtonPress(BUTTON_ID).Or(Blink(LIGHT_ID,1.0f).Or(Timeout(30.0f));
	//Sequence buttonPressScreen = MUI_Show(BUTTON_SCREEN_INTRO).Then(getButtonPress).Then(MUI_Show(BUTTON_SCREEN_OUTRO));
	

	while(seq.Update(1.0f))
	{
		
	}
	return 0;
}
