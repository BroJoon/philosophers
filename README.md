# :star:Introduce

it's about the operating system
Dining philosophers problem resolved differently using mutexes and semaphores, threads and processes.

![image](https://user-images.githubusercontent.com/52714837/130329785-2225ed62-f43b-49f5-b36f-18aa67bceb3a.png)

### 🎯 Object
Implement Dining philosophers problem in two different way!

#### `philo_one`
philosopher with threads and mutex

- One fork between each philosopher, therefore there will be a fork at the right and at the left of each philosopher.
- To avoid deadlokc, you should protect the forks state with a mutex for each of them.
- Each philosopher should be a thread and do not talk to each other 

#### `philo_bonus`
philosopher with processes and semaphore

- All the forks are in the middle of the table.
- They have no states in memory but the number of available forks is represented by a semaphore.
- Each philosopher should be a process and the main process should not be a philosopher.

### 💻 How to Run
```command
> git clone https://github.com/steveklabnik/dining_philosophers.git
> cd philo or philo_bonus
> make
> ./philo [philo_count] [time_to_die] [time_to_eat] [time_to_sleep] option([must_eat])
> ./philo_bonus [philo_count] [time_to_die] [time_to_eat] [time_to_sleep] option([must_eat])
example > ./philo 5 410 200 200 

