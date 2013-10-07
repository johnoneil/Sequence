
#include "Sequence.hpp"
#include "Pause.hpp"
#include "Both.hpp"

int main(int argc, char* argv[])
{
	/*
	SequenceHead seq;
	seq.First(Wait(10.0f))
		.Then(Wait(10.0f))
		.Then(Wait(10.0f))
		.While(Wait(10.0f));//WhileSimultaneously, AndSimultaneously, (parallel task, no rendezvous)
	*/
	//Sequence seq = Pause(10.0f).Then(Pause(10.0f)).Then(Pause(10.0f));
	//Sequence parallel_task = Pause(30.0f);
	//seq.While(parallel_task);
	//Sequence s2 = Pause(10.0f).Then(Pause(10.0f));
	//seq.Then(s2);

	//Three sequences that rendezvous:
	Sequence rendezvous = Both(Pause(10.0f))
				.And(Pause(20.0f))
				.And(Pause(30.0f));

	//Three tasks in series
	Sequence series = Pause(10.0f).Then(Pause(10.0f)).Then(Pause(10.0f));

	//Three tasks in parallel that don't rendezvous
	Sequence parallel = Pause(10.0f).While(Pause(20.0f)).While(Pause(30.0f));

	//Three tasks which rendezvous at first task completion
	//Sequence rendezvous_or = Either(Pause(10.0f))
	//			.Or(Pause(20.0f))
	//			.Or(Pause(20.0f));

	//Put all these sequences in series
	Sequence seq = rendezvous.Then(series).Then(parallel);



	//Sequence seq = Pause(10.0f)
	//		.Then( Both(Pause(10.0f)).And(Pause(20.0f)) )
	//		.Then(Pause(10.0f));
	//seq=s3;

	//seq = s2;

	//seq = First(Wait(10.0f).Then(Wait(10.0f).Then(Wait(10.0f)); --> First as constructor, define head assignment operator

	//seq.First(Wait(10.0f)).Then(Both(Wait(10.0f).And(Wait(10.0f))---> "Both" container, linked by "And"
	//								     Task completes when all parallel tasks complete
	//seq.First(wait(10.0f)).Then.Both(Wait(10.0f)).And(Wait(10.0f))

	//seq.First(Wait(10.0f)).Then.Either(Wait(10.0f)).Or(Wait(10.0f)) -->Either container, linked by "Or"

	//Button press with blink and timeout
	//Sequence getButtonPress = First.Either(GetButtonPress(BUTTON_ID)).Or(Blink(LIGHT_ID,1.0f)).Or(Timeout(30.0f));
	//Sequence buttonPressScreen = First(MUI_Show(BUTTON_SCREEN_INTRO).Then(getButtonPress).Then(MUI_Show(BUTTON_SCREEN_OUTRO));
	
	//SequencePtr sequence = Pause::Seconds(10.0f)
	//	->Then( Pause::Seconds(10.0f)->While(Pause::Seconds(10.0f)) )
	//	->Then( Pause::Seconds(10.0f) );
	//while( sequence = sequence->Service(1.0f) 

	while(seq.Update(1.0f))
	{
		
	}
	return 0;
}
