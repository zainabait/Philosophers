

<h1 align="center">Philosophers_42_1337 </h1>
<p align="center">
  <a href="https://github.com//zainabait/Philosophers">
    <img src="https://raw.githubusercontent.com/zainabait/1337_badges/refs/heads/master/philosophersm.png" alt="42 Badge">
  </a>
</p>


---

## Overview

This project explores **multithreading** by implementing the classic **Dining Philosophers problem**, a common synchronization problem in computer science.

You will learn how to:

* Create and manage **threads**
* Use **mutexes** to prevent **race conditions** and ensure safe access to shared resources

---

## 🧠 The Problem

* A number of philosophers sit at a round table with one **fork between each pair**.
* Philosophers alternate between **thinking**, **eating**, and **sleeping**.
* To eat, a philosopher must **hold two forks** (left and right).
* Forks are shared between neighbors, so coordination is required to avoid deadlocks and starvation.

---

## 🧵 Core Concepts

### Threads

Each philosopher is represented by a **thread** running concurrently. A separate **monitor thread** watches for deaths or completion.

### Mutexes

Each fork is protected by a **mutex** to ensure mutual exclusion. Philosophers must acquire both forks (mutexes) before eating, and release them afterward.

### Race Conditions

A **race condition** happens when multiple threads access and modify shared data without synchronization, leading to unpredictable behavior.
This is avoided using mutexes to serialize critical sections.

---

## 📦 Program Flow

1. **Input Validation**
   The program accepts 4 or 5 arguments:
   `number_of_philos time_to_die time_to_eat time_to_sleep [meals_required]`

2. **Initialization**
   Structures are used to hold program state and philosopher data. Mutexes for forks and other synchronization elements are initialized.

3. **Thread Creation**

   * One thread per philosopher
   * One monitor thread to detect death or meal completion

4. **Routine Loop**
   Each philosopher:

   * Picks up forks (mutexes)
   * Eats
   * Sleeps
   * Thinks

5. **Monitoring**
   The monitor checks:

   * If any philosopher has died
   * If all philosophers have eaten the required number of times

6. **Cleanup**
   All mutexes are destroyed at the end.

---

## ✅ Bonus

For the bonus part, you may use **semaphores** instead of mutexes to explore alternative synchronization methods.

---


### I hope this README was helpful and gives you a clear overview of the project. 😊

