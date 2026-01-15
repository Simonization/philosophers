# Philosophers Project - Correction Checklist

## 1. Error Handling & Norm

### 1.1 Code Quality
- [ ] Project is coded in C following the Norm
- [ ] No norm errors (run `norminette`)
- [ ] No crashes during execution
- [ ] No undefined behavior

### 1.2 Memory Management
- [ ] No memory leaks (test with `valgrind --leak-check=full`)
- [ ] All heap allocations are properly freed before program ends
- [ ] Test with `valgrind`, `leaks`, or `e_fence`

### 1.3 Data Races
- [ ] No data races (test with `valgrind --tool=helgrind`)
- [ ] No data races (test with `valgrind --tool=drd`)
- [ ] All shared variables are properly protected by mutexes

---

## 2. Global Variables

### 2.1 Shared Resources
- [ ] **CRITICAL**: No global variables used to manage shared resources among philosophers
- [ ] If global variables exist for shared resources, evaluation STOPS here

---

## 3. Code Architecture

### 3.1 Thread Management
- [ ] One thread per philosopher (verify in `philosopher.c`)
- [ ] Threads are properly created with `pthread_create`
- [ ] Threads are properly joined with `pthread_join`

### 3.2 Fork Management
- [ ] One fork per philosopher (n philosophers = n forks)
- [ ] Each fork has its own mutex
- [ ] Mutex is used to check the fork value and/or change it
- [ ] Forks are properly locked before eating
- [ ] Forks are properly unlocked after eating

### 3.3 Output Synchronization
- [ ] Outputs are never mixed up
- [ ] Print mutex is used to protect console output
- [ ] Timestamp and message are printed atomically

### 3.4 Death Detection
- [ ] Check how death of a philosopher is verified
- [ ] Verify there is a mutex to prevent a philosopher from dying and starting to eat at the same time
- [ ] Death is detected within acceptable time margin (< 10ms delay)

### 3.5 Resource Cleanup
- [ ] Check if mutex existence is verified before destroying it
- [ ] All mutexes are properly destroyed at the end
- [ ] Memory cleanup happens even on error paths

---

## 4. Edge Cases

### 4.1 Single Philosopher
- [ ] Single philosopher case is handled correctly
- [ ] Philosopher takes one fork and waits (cannot eat with one fork)
- [ ] Philosopher dies after `time_to_die` milliseconds

### 4.2 Timing Issues
- [ ] Verify usleep before routine is long enough for philosophers to split into groups
- [ ] Even/odd staggering is implemented correctly
- [ ] No race condition at simulation start

---

## 5. Functional Tests

### 5.1 Test Constraints
- [ ] Do not test with more than 200 philosophers
- [ ] Do not test with time_to_die, time_to_eat, or time_to_sleep < 60ms

### 5.2 Basic Death Tests

| Test | Command | Expected Result |
|------|---------|-----------------|
| 5.2.1 | `./philo 1 800 200 200` | Philosopher should NOT eat, should die |
| 5.2.2 | `./philo 4 310 200 100` | One philosopher should die |

### 5.3 Survival Tests

| Test | Command | Expected Result |
|------|---------|-----------------|
| 5.3.1 | `./philo 5 800 200 200` | No philosopher should die |
| 5.3.2 | `./philo 4 410 200 200` | No philosopher should die |

### 5.4 Meal Goal Test

| Test | Command | Expected Result |
|------|---------|-----------------|
| 5.4.1 | `./philo 5 800 200 200 7` | No philosopher should die, simulation stops when each has eaten at least 7 times |

### 5.5 Two Philosophers Test
- [ ] Test with 2 philosophers
- [ ] Death delay must not exceed 10ms
- [ ] Example: `./philo 2 310 200 100` - verify death timing accuracy

### 5.6 Custom Tests
- [ ] Philosophers die at the right time (not too early, not too late)
- [ ] Philosophers don't "steal" forks (no deadlock)
- [ ] Simulation ends cleanly

---

## 6. Valgrind Tests

### 6.1 Memory Leaks
```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200 7
```
- [ ] No memory leaks reported
- [ ] All allocated blocks freed

### 6.2 Helgrind (Data Races)
```bash
valgrind --tool=helgrind ./philo 5 800 200 200 7
```
- [ ] No data races detected
- [ ] No lock order violations

### 6.3 DRD (Data Races Alternative)
```bash
valgrind --tool=drd ./philo 5 800 200 200 7
```
- [ ] No conflicting accesses reported

---

## 7. Code Review Points

### 7.1 Files to Examine
- [ ] `philo.h` - Data structures and prototypes
- [ ] `main.c` - Argument parsing and entry point
- [ ] `init.c` - Mutex and philosopher initialization
- [ ] `philosopher.c` - Thread creation and routine
- [ ] `actions.c` - Fork taking, eating, releasing
- [ ] `monitor.c` - Death detection and logging
- [ ] `time.c` - Time management
- [ ] `utils.c` - Cleanup and utilities

### 7.2 Key Code Sections to Verify
- [ ] Fork assignment logic (circular arrangement)
- [ ] Deadlock prevention mechanism (fork ordering)
- [ ] Death check timing precision
- [ ] Meal counter synchronization
- [ ] Simulation end flag protection

---

## Summary

| Category | Status |
|----------|--------|
| Error Handling | [ ] Pass |
| Global Variables | [ ] Pass |
| Code Architecture | [ ] Pass |
| Edge Cases | [ ] Pass |
| Functional Tests | [ ] Pass |
| Valgrind Tests | [ ] Pass |
| Code Review | [ ] Pass |

**Final Grade:** ____

---

## Notes

_Space for observations during correction:_

