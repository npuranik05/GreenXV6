# GreenXV6 — Kernel-Level Environmental Monitoring

A kernel-level extension to the xv6 teaching operating system that simulates a campus-wide network of air quality sensors, pollution mitigation, and per-process energy accounting. The project models environmental monitoring as an OS problem and demonstrates custom syscall design, kernel synchronization with spinlocks, and scheduler modification.

Built on top of MIT's xv6, this project adds an entirely new kernel subsystem plus a set of user-space programs that interact with it.

## 🚀 Features

### Core Features

- **Zone-Based Pollution Tracking**: 5 independent campus zones (0–4), each tracking its own pollution level inside a spinlock-protected kernel structure
- **Custom Syscalls**: New system calls for associating processes with zones, reporting pollution, querying zone state, and triggering mitigation
- **Sensor Processes**: User-space sensor programs that attach to a zone and generate pollution data
- **Mitigator Processes**: Cleanup processes that reduce zone pollution by 50 units per cleaning cycle
- **Pollution Monitor**: A live monitor program that displays pollution levels across all zones and flags zones exceeding 100 units with `[CRITICAL]` status

### Kernel-Level Features

- **Scheduler Throttling**: The scheduler throttles processes running in polluted zones to slow further pollution generation
- **Mitigator Bypass**: Mitigator processes are protected from throttling so cleanup can always run, even in critical zones
- **Per-Process Energy Accounting**: Energy usage tracked per process during context switches via the timer interrupt
- **Spinlock Synchronization**: Concurrent-safe zone state shared across processes and interrupt context

## 🛠️ Tech Stack

- **C** (kernel and user programs)
- **x86 Assembly** (xv6 boot and trap code)
- **xv6** (MIT's teaching operating system)
- **QEMU** (PC hardware emulation)
- **GNU Make / GCC toolchain**

## 📋 Prerequisites

- x86 ELF toolchain (native on Linux, or a cross-compiler like `i386-jos-elf-` on macOS/Windows — see https://pdos.csail.mit.edu/6.828/)
- QEMU PC simulator
- GNU Make

## 🏃‍♂️ Getting Started

### Build

```bash
# On an x86 ELF machine (Linux)
make

# On non-x86 or non-ELF machines (macOS, Windows)
make TOOLPREFIX=i386-jos-elf-
```

### Run

```bash
make qemu
```

### Using the Environmental Features

```bash
# 1. Start the monitor to view pollution levels
$ monitor

# 2. In other shell instances, start sensors for different zones
$ sensor 0      # Zone 0 sensor
$ sensor 1      # Zone 1 sensor

# 3. Start mitigators to manage pollution
$ mitigator 0   # Zone 0 mitigator
$ mitigator 1   # Zone 1 mitigator

# 4. Test the energy accounting system
$ energy_test

# 5. Test the environment syscalls
$ env_test
```

## 🏗️ Architecture Overview

The system uses a simple model:

- 5 campus zones (0–4) track independent pollution levels in a shared kernel structure
- Processes associate with a zone to either generate pollution (sensors) or clean it (mitigators)
- The scheduler throttles processes in heavily polluted zones, while mitigators bypass throttling to guarantee cleanup
- Energy accounting happens during context switches, driven by the timer interrupt
- Zones exceeding 100 pollution units are flagged as critical; mitigation reduces pollution by 50 units per pass

## 🐛 Challenges I Faced & How I Solved Them

### 1. Kernel Synchronization
Zone state is touched by multiple processes and interrupt handlers at once. Protecting the shared zone-tracking structure with spinlocks without introducing deadlocks in interrupt context took careful ordering of lock acquisition.

### 2. Scheduler Modification
Modifying xv6's round-robin scheduler to throttle polluting processes without starving them entirely — and carving out an exemption path so mitigators always get CPU time in critical zones.

### 3. Syscall Plumbing
Wiring new syscalls through xv6's full syscall path (user-space stubs, syscall table, dispatch, kernel handlers) while keeping argument validation safe against bad user pointers.

### 4. Energy Accounting in Interrupt Context
Hooking per-process energy tracking into the timer interrupt and context switch path without adding measurable overhead or corrupting process state.

### 5. Debugging in QEMU
No debugger comforts of user-space development — kernel panics and triple faults meant relying on print-based debugging and reasoning carefully about concurrency.

## 🎯 What I Learned

- How syscalls actually work end-to-end, from user-space stub to kernel handler
- Kernel synchronization primitives and why spinlocks (not sleep locks) are needed in interrupt context
- How schedulers make decisions and how to modify scheduling policy safely
- Interrupt handling and what can (and can't) safely happen inside an interrupt
- Reading and extending a real, minimal UNIX-like kernel codebase
- Low-level debugging without standard tooling

## 🔧 Development Notes

- Pollution threshold for `[CRITICAL]` status is 100 units
- Each mitigation pass reduces zone pollution by 50 units
- Zone state lives entirely in kernel memory — no persistence across reboots
- Energy accounting runs on every context switch via the timer interrupt

## 📝 Future Improvements

- Configurable pollution thresholds and mitigation rates
- More zones with dynamic zone creation
- Priority-based scheduling tiers instead of binary throttle/bypass
- Historical pollution logging to disk
- Inter-zone pollution spread simulation

## 🙏 Acknowledgments

This project is based on xv6, which is inspired by John Lions's *Commentary on UNIX 6th Edition*. See https://pdos.csail.mit.edu/6.828/ for additional resources.

Original xv6 code is Copyright 2006–2018 Frans Kaashoek, Robert Morris, and Russ Cox.

Developed as a group project for SE 3313B (Operating Systems).

---

*Built with ❤️ during my third year of Software Engineering*
