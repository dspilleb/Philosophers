<h1 align="center">
	📖 Philosophers
</h1>

<p align="center">
	<b><i>I never thought philosophy would be so deadly</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/dspilleb/Philosophers?color=lightblue" />
	<img alt="Number of lines of code" src="https://img.shields.io/tokei/lines/github/dspilleb/Philosophers?color=critical" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/dspilleb/Philosophers?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/dspilleb/Philosophers?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/dspilleb/Philosophers?color=green" />
</p>

## 💡 About the project

> __In this project, you will learn the basics of threading a process.__
>  You will see how to create threads and you will discover mutexes.

  In computer science, the dining philosophers problem is an example problem often used 
  in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.
It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals.
Soon after, Tony Hoare gave the problem its present form.

<a href=‘https://en.wikipedia.org/wiki/Dining_philosophers_problem#/media/File:An_illustration_of_the_dining_philosophers_problem.png’ align="center"><img src=‘https://user-images.githubusercontent.com/59456000/198906008-4135d5d2-de53-4a8b-9c24-744181f04851.png’ width=‘275’ heigth=‘275’></img></a>
<p align=“center”>Illustration of the dining philosophers problem</p>
<br><br>

------------

## 💻 To use the program 
<h3>you must first compile it with the makefile by using the command 'make' in the shell</h3>

```bash
make all
```

<h3>Then the program must be executed as follows: </h3>

```bash
./philo number_philosopher time_to_die time_to_eat time_to_sleep [number_of_time_each_philosophers_must_eat]
```
<br>
<li>number_of_philosophers: The number of philosophers and also the number
of forks.</li>
<li>time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.</li>
<li>time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.</li>
<li>time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.</li>
<li>number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.</li>
