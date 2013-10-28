
#include "Sequence.hpp"
#include "Pause.hpp"
#include "And.hpp"

int main(int argc, char* argv[])
{
	Sequence seq1 = Both(Pause(10.0f).Then(Pause(3.0f)) ).And(Pause(20.0f)).And(Pause(30.0f));
	Sequence seq = seq1.Then(Pause(3.0f));


	//Button press with blink and timeout
	//Sequence getButtonPress = Either(GetButtonPress(BUTTON_ID).Or(Blink(LIGHT_ID,1.0f).Or(Timeout(30.0f));
	//Sequence buttonPressScreen = MUI_Show(BUTTON_SCREEN_INTRO).Then(getButtonPress).Then(MUI_Show(BUTTON_SCREEN_OUTRO));
	

	while(seq.Update(1.0f))
	{
		
	}
	return 0;
}
