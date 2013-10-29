Sequence
========

Code experiments in the area of sequencing events using boost C++11 functionality.
The only type of event implemented here is a pause, but the model for pause can be expanded to include any single blocking task.

Using
=====

Use the code as follows:

Access the classes by including the single Chain.hpp header.
```
#include <Chain.hpp>
```

Manage classes within 'Chain' namespace
```
using namespace Chain;
```

At run time, to create a sequence of events, instantiate the Chain::Sequence class via some appropriate factory.
```
Sequence seq1 = Pause(10.0f);
```

Link sequences in series by the 'Then' method. In 'series' means that that the first must complete before the second is started.
```
Sequence seq1 = Pause(10.0f);
Sequence seq2 = Pause(10.0f);
Sequence seq = seq1.Then(seq2).Then(Pause(10.0f));
```

You can run sequences in parallel by using the 'And' method. This creates a larger sequence container which completes when all parallel sequences within complete. Thus is it the logical AND of parallel sequence completion.
```
Sequence seq1 = Both(Pause(10.0f)).And(Pause(20.0f));
```

You can also run sequences in parallel with the logical 'Or' of all parallel sequence completion. In other words,the sequence will complete when the first parallel sequence completes.
Parallel sequences which havne't yet run their course when one of their siblings complete will have a 'Cancel' event delivered to them.
```
Sequence seq1 = Either(Pause(10.0f)).Or(Pause(20.0f));
```

Once a sequence has been created it can be (destructively) run by servicing it:
```
Sequence myseq = Both(Pause(10.0f).Then(Pause(20.0f))).Then(Either(Pause(10.0f).Or(Pause(20.0f)));
//Run sequence to completion
while(myseq.Update(1.0f)){}
```
At other times, the completion of a sequence can be polled by just using the Sequence::IsComplete() method.
```
const bool completion_status = myseq.IsComplete();
```
