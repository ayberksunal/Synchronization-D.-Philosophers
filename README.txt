WHAT IS THE PROBLEM?

The dining philosophers problem is: how do you make sure every philosopher gets to eat? In the problem, there are 5 different philosophers who are seated around a circular table. Every philosophers behaves is in this way: Either he wants to think, or he wants to eat. There is a chopstick places between each pair of philosophers which both can use.
  A philosopher have to use two of them these chopsticks to eat spaghetti. A philoso- pher can only pick up one chopstick at one time. When a philosopher finishes eating, they replaced their chopsticks to the table and they return thinking again. The problem is chopsticks are not enough for all philoso- phers to eat at the same time but each of them have to eat for a time.


HOW DO WE SOLVE?
Philosophers are numerated from 0 to 4 and they share a circular table. In this table philoso- phers who are even numbered get the right chopstick firstly and then get the left chopstick. If the philosopher number is odd numbered, he gets the left chopstick firstly and then get the right chopstick. To run this methodology, I get help from the pthears(mutex). I created 5 threads for chopsticks and philosophers and I controlled the turn with these threads with locking and opening.

IF philosopher number even RIGHT => LEFT
ELSE
LEFT => RIGHT

1. Allow only 4 philosophers to sit simultaneously
2. Asymmetric solution
  a) Odd philosopher picks left fork followed by right 
  b) Even philosopher does vice versa
3. Pass a token
4. Allow philosopher to pick fork only if both available
