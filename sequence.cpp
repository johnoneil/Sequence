
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
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
		
		
	}
	//friend boost::shared_ptr< Sequence< Pause > > boost::make_shared<>(const float);
public:
	Pause(const float time)
	:m_counter(0)
	{
		cout<<"Pause::Pause()"<<endl;
	};
};

int main(int argc, char* argv[])
{
	SequencePtr sequence = Pause::Seconds(10.0f)
		->Then( Pause::Seconds(10.0f)->While(Pause::Seconds(10.0f)) )
		->Then( Pause::Seconds(10.0f) );
	while( sequence = sequence->Service(1.0f) )
	{
		
	}
	return 0;
}
