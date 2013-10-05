
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <list>
using boost::shared_ptr;
using boost::make_shared;
using std::cout;
using std::endl;

/*class ISequence
{
public:
	virtual ~ISequence(){};
	shared_ptr< ISequence > Then( shared_ptr< ISequence > sp) = 0;
	shared_ptr< ISequence > And( shared_ptr< ISequence > sp ) = 0;
	shared_ptr< ISequence > Service( const float dt) = 0;
};*/

class Sequence;
typedef shared_ptr< Sequence > SequencePtr;

class Sequence : public boost::enable_shared_from_this< Sequence >
{
public:
	Sequence():m_updated(false){};
	virtual ~Sequence(){};
	enum Status
	{	
		Complete = true,
		NotComplete = false
	};
	SequencePtr Then( SequencePtr sp)
	{
		//TODO: prevent circular/doubled referenes.
		//these may cause infinite loops.
		cout<<"Sequence::Then"<<endl;
		if(sp && !m_series)
		{
			cout<<"final"<<endl;
			(m_series = sp);
		}else if(sp && m_series){
			cout<<"Nest"<<endl;
			m_series->Then(sp);
		}
		return shared_from_this();
	};
	SequencePtr While( SequencePtr sp)
	{
		//TODO: prevent circular/doubled references.
		//these may cause infinite loops
		cout<<"Sequence::While"<<endl;
		if(sp && !m_parallel)
		{
			cout<<"final"<<endl;
			(m_parallel = sp);
		}else if (sp && m_parallel){
			cout<<"Nest"<<endl;
			m_parallel->While(sp);

		}
		return shared_from_this();
	};

	SequencePtr Service(const float dt)
	{
		cout<<"shared_ptr<Sequence>::Service"<<endl;
		if(!m_updated)
		{
			BeforeFirstUpdate();
			m_updated = true;
		}
		UpdateParallelTasks(dt);
		Sequence::Status completionStatus = DoService(dt);
		if( completionStatus == Complete )
		{
			AfterCompletion();
			//this task is complete. Pass parallel tasks to first child in series
			if(m_parallel)
			{
				if(m_series)
				{
					m_series->While(m_parallel);
				}else{
					return m_parallel;
				}
			}
			return m_series;	
		}else{
			return shared_from_this();
		}
	}
private:
	bool m_updated;
	//NVI implementation
	virtual Sequence::Status DoService(const float dt)
	{
		return Complete;
	};
	virtual void BeforeFirstUpdate(void)
	{
		cout<<"Sequence::BeforeFirstUpdate()"<<endl;
	};
	virtual void AfterCompletion(void)
	{
		cout<<"Sequence::AfterCompletion()"<<endl;
	};
	void UpdateParallelTasks(const float dt)
	{
		cout<<"Service::UpdateParallelTasks"<<endl;
		if(m_parallel)
		{
			m_parallel = m_parallel->Service(dt);
		}
	}
	SequencePtr m_series;
	SequencePtr m_parallel;
};

class Pause : public Sequence
{
public:
	~Pause()
	{
		cout<<"~Pause()"<<endl;
	}
	static SequencePtr Seconds(const float time)
	{
		cout<<"Pause::Seconds"<<endl;
		return make_shared< Pause >(time);
	}
private:
	int m_counter;
	virtual Sequence::Status DoService(const float dt)
	{
		cout<<"Pause::DoService counter:"<<m_counter<<endl;
		++m_counter;
		if(m_counter > 4)
		{
			return Sequence::Complete;
		}else{
			return Sequence::NotComplete;
		}
		
		
	};
public:
	Pause(const float time)
	:m_counter(0)
	{
		cout<<"Pause::Pause()"<<endl;
	};
};

class SequenceHead
{
public:
	bool Update(const float dt)
	{
		m_sequence = m_sequence->Service(1.0f);
		return m_sequence;
	}
	SequenceHead& Then(SequencePtr sequence)
	{
		if(m_sequence)
		{
			m_sequence->Then(sequence);
		}else{
			m_sequence = sequence;
		}
		return *this;
	};
	SequenceHead& Then(const SequenceHead& sequence)
	{
		if(&sequence!=this)
		{
			Then(sequence.m_sequence);
		}
		return *this;
	}
	SequenceHead& First(SequencePtr sp)
	{
		return Then(sp);
	};
	SequenceHead& While(SequencePtr sp)
	{
		if(m_sequence)
		{
			m_sequence->While(sp);
		}else{
			m_sequence = sp;
		}
		return *this;	
	};
	SequenceHead operator=(const SequencePtr& seq)
	{
		//No matter its current state, this assigns the given
		//sequence as the primary sequence this is the head of
		m_sequence = seq;
	};
	SequenceHead operator=(const SequenceHead& other)
	{
		if(&other!=this)
		{
			m_sequence = other.m_sequence;
		}
		return *this;
		
	};
	SequenceHead(const SequencePtr& seq)
		:m_sequence(seq)
	{

	};
	SequenceHead(const SequenceHead& other)
		:m_sequence(other.m_sequence)	
	{

	};
	
private:
	SequencePtr m_sequence;
};



SequenceHead Wait(const float timeToWait)
{
	return SequenceHead(make_shared< Pause >(timeToWait));
};

int main(int argc, char* argv[])
{
	/*
	SequenceHead seq;
	seq.First(Wait(10.0f))
		.Then(Wait(10.0f))
		.Then(Wait(10.0f))
		.While(Wait(10.0f));//WhileSimultaneously, AndSimultaneously, (parallel task, no rendezvous)
	*/
	SequenceHead seq = Wait(10.0f).Then(Wait(10.0f)).Then(Wait(10.0f));
	SequenceHead s2 = Wait(10.0f).Then(Wait(10.0f));
	seq.Then(s2);

	seq = s2;

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
