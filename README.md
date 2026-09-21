*This project has been created as part of the 42 curriculum by gortiz-j.*

# Codexion
## Master the race for resources before the deadline masters you

## Description
Codexion is a multithreaded simulation inspired by the classic resource-allocation problem found in operating systems and real-time scheduling. The project models several coders competing to acquire shared dongles in order to complete compile, debug, and refactor tasks before their burnout deadline is reached.

The simulation is built around independent worker threads, a monitor, and a scheduler that decides which waiting coder should access a resource next. The core challenge is not only to execute tasks correctly, but to do so safely under concurrency, without causing deadlocks, starvation, inconsistent logs, or race conditions on shared state.

Each coder thread performs a sequence of actions in a loop: they request a resource, wait until it becomes available, use it for a limited time, release it, and continue until their required number of successful compiles is reached or the simulation ends due to burnout or forced stop. The monitor continuously checks whether any coder has exceeded their allowed inactivity period and, if so, signals the shutdown condition.

## Features
- Concurrent coder threads competing for shared dongles
- Scheduler-based access control using FIFO or EDF logic
- Time-aware resource cooldown handling
- Burnout detection and simulation shutdown
- Serialized logging for thread-safe event reporting
- Condition-based waiting and wake-up coordination

## Instructions
### Requirements
- A Unix-like environment with GCC/Clang
- POSIX threads support (`pthread`)
- Make

### Compilation
From the project root, run:

```bash
make
```

This builds the executable named `codex`.

### Execution
The program expects the following arguments:

```bash
./codex <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

Example:

```bash
./codex 4 5000 1000 800 700 5 2000 fifo
```

Where:
- `number_of_coders`: total number of coder threads
- `time_to_burnout`: maximum time before a coder is considered burned out
- `time_to_compile`, `time_to_debug`, `time_to_refactor`: task durations
- `number_of_compiles_required`: target completion count per coder
- `dongle_cooldown`: minimum gap between two consecutive uses of the same dongle
- `scheduler`: either `fifo` or `edf`

### Cleaning up
To remove object files and rebuild from scratch:

```bash
make clean
make fclean
make re
```

## Blocking cases handled
This project addresses the main concurrency hazards that typically arise in resource-sharing simulations.

### 1. Deadlock prevention and Coffman conditions
The implementation avoids deadlocks by ensuring that a coder cannot hold a dongle while waiting on a second conflicting resource in a circular pattern. In practice, each resource is guarded by a single mutex and only one coder can own it at a time. A thread that cannot immediately acquire the dongle does not keep the resource locked while waiting; instead, it waits on a condition variable and re-checks the state when awakened.

This prevents the classic Coffman conditions:
- mutual exclusion is enforced by per-dongle mutexes
- hold-and-wait is minimized because a thread does not claim ownership while spinning in a blocked state
- no preemption is respected by the resource model, but ownership is released cleanly when the task ends
- circular wait is avoided because there is only one shared resource class per dongle and access is serialized through the queue

### 2. Starvation prevention
Starvation is mitigated through the scheduling queue attached to each dongle. Waiting coders are inserted in priority order and only the eldest or highest-priority eligible request is allowed to proceed next. This ensures that a thread cannot be perpetually bypassed by newer requests while still preserving fairness.

### 3. Cooldown handling
After a dongle is released, a cooldown period is enforced before another coder can claim it. This avoids excessive re-use and prevents a thread from repeatedly taking the same resource in a tight loop without a real fairness gap. The code checks the stored `last_release_time` before granting ownership.

### 4. Precise burnout detection
The monitor periodically evaluates each coder's timestamp of the most recent compile start. If the elapsed time exceeds the configured burnout threshold, the simulation is stopped and all waiting threads are woken up. This prevents hidden deadlocks where sleeping threads would otherwise remain stuck indefinitely.

### 5. Log serialization
All logging operations are guarded by a mutex, so multiple threads cannot interleave output on stdout. The log mechanism prints a timestamped event with a consistent format, ensuring that the execution trace remains readable and race-free.

## Thread synchronization mechanisms
The implementation relies on standard POSIX primitives and a condition-based waiting pattern to coordinate access to shared resources.

### `pthread_mutex_t`
Each shared structure that may be accessed by multiple threads is protected by a mutex:
- each dongle has a dedicated mutex guarding the ownership state and waiting queue
- the global simulation stop flag is protected by `sim->stop_mutex`
- the coder timestamp state is protected by `coder->timestamp_mutex`
- the logging system uses a dedicated mutex to serialize output

This prevents races when multiple coders read or update the same resource metadata at the same time.

### `pthread_cond_t`
Each dongle exposes a condition variable used as a wait/notify mechanism. A coder that cannot proceed blocks on the resource condition and wakes only after a release event or simulation shutdown. The release path calls `pthread_cond_broadcast`, which awakens all waiters so they can re-evaluate eligibility. This is the key synchronization mechanism that avoids busy waiting and prevents inconsistent ownership checks.

The project uses a small custom wait-notify pattern built on top of the condition variable: a thread locks the dongle mutex, checks whether it can proceed, and if not, waits until the condition is signaled. When the resource is released or the monitor triggers shutdown, the condition is broadcast and all waiting coders re-check the state under the same mutex. This guarantees that no thread observes stale ownership information.

### Shared-resource coordination example
When a coder tries to take a dongle:
1. it locks the dongle mutex
2. it inserts its request into the dongle queue
3. it releases the mutex and waits for the condition to be signaled
4. it re-checks ownership, the cooldown, and queue order under the same mutex
5. only when the resource is free and the request is at the head of the queue does it become the owner

When a coder releases a dongle:
1. it locks the same dongle mutex
2. it sets `owner_id` to `-1`
3. it updates `last_release_time`
4. it broadcasts the condition so waiting coders can retry
5. it unlocks the mutex

This approach prevents races between the queue, the owner field, and the cooldown timestamps.

## Resources
### Classic references
- POSIX Threads (pthreads): https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthreads.html
- Operating Systems: Three Easy Pieces by Remzi H. Arpaci-Dusseau and Andrea C. Arpaci-Dusseau
- The Little Book of Semaphores by Allen B. Downey
- Real-time scheduling documentation on EDF and FIFO algorithms
- Articles and notes on deadlock, starvation, and condition-variable synchronization in concurrent systems

### AI usage
AI tools were used to help reason about the concurrency model, validate the deadlock/starvation strategy, and draft the documentation structure for this repository. In particular, AI was useful for:
- analyzing the wait/notify logic around `pthread_cond_t`
- reviewing edge cases related to burnout detection and cooldown handling
- clarifying the explanation of Coffman conditions and fairness guarantees
- structuring the README and technical narrative in English

AI support was used to improve correctness and clarity of the design notes and documentation, not to replace the underlying implementation work.

## Project summary
Codexion turns a scheduling and concurrency problem into a practical multithreaded simulation. The challenge is to manage shared resources under time pressure, protect them from race conditions, and keep all actors coordinated without creating blocking bugs. The final result is a small but realistic system that demonstrates how mutexes, condition variables, planner logic, and monitor supervision work together in a concurrent environment.
