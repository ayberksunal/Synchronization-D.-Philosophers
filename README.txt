
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
