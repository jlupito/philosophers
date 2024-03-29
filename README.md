# philosophers

  This is the philosopohers project for School 42.
  
  ![Screenshot from 2023-11-22 12-21-16](https://github.com/jlupito/philosophers/assets/113239012/b0fe5ed4-cd99-42db-859d-996cdc3b6543)

This project is a C implementation to resolve the famous philosophers problem:
- One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep, and only do one thing at a time.
- There are also forks on the table. There are as many forks as philosophers.
- A philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
  start sleeping. Once awake, they start thinking again. The simulation stops when
  a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.

The program takes 4 or 5 arguments: number of philosophers, time before starving,
time required to eat, time required to sleep and number of meals to complete (non-compulsory argument).

*The idea of the project is to learn about concurrent programming and get
familiar with threads and mutexes, and the concepts of data races and deadlocks.
Semaphores are only covered in the bonus part, which is not included here.*
