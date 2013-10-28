Sequence
========

Code experiments in the area of sequencing events using boost C++11 functionality.
The only type of event implemented here is a pause, but the model for pause can be expanded to include any single blocking task.

Using
=====

Use the code as follows:

Create a sequence
```
Sequence seq1 = Pause(10.0f);
```

Link sequences in series by the 'Then' method
```
Sequence seq1 = Pause(10.0f);
Sequence seq2 = Pause(10.0f);
Sequence seq = seq1.Then(seq2).Then(Pause(10.0f));
```

You can run tasks in parallel by using the 'And' method. This creates a sequence which completes when all subtasks within complete. Thus is it the logical and of parallel task completion.
```
Sequence seq1 = Both(Pause(10.0f)).And(Pause(20.0f));
```

You can also run tasks in parallel, but complete the sequence by the logical 'Or' of all subtask completion. In other words,the sequence will complete when the first subtask completes.
Subtasks which havne't yet run their course when the parent sequence completes will have a 'Cancel' event delivered to them.
```
Sequence seq1 = Either(Pause(10.0f)).Or(Pause(20.0f));
```

Once a sequence has been created it can be (destructively) run by servicing it:
```
Sequence myseq = Both(Pause(10.0f).Then(Pause(20.0f))).Then(Either(Pause(10.0f).Or(Pause(20.0f)));
//Run sequence to completion
while(seq.Update(1.0f)){}
```
