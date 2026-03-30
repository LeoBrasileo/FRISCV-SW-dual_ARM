# FRISCV-SW — Dual-ARM Memory Management System for a RISC-V Processor

Software stack for a dual-core ARM-managed memory subsystem supporting a custom RISC-V soft-core processor implemented on FPGA.

## Overview

This project implements the software infrastructure that runs on two ARM Cortex-A cores (e.g., on a Zynq SoC) to manage the memory subsystem of a RISC-V processor instantiated in programmable logic (PL). Rather than handling memory in HDL alone, the ARM cores take on the role of a memory management layer — handling program loading, memory arbitration, clock generation, and I/O — while the RISC-V core focuses solely on instruction execution.

## Architecture

```
┌──────────────────────────────────────────────────────┐
│                    Zynq SoC                          │
│                                                      │
│   ┌─────────────┐        ┌──────────────────────┐    │
│   │  ARM Core 0 │        │  ARM Core 1          │    │
│   │  (Control / │◄──────►│  (Memory Arbitration │    │
│   │   Loader)   │        │   / I/O)             │    │
│   └──────┬──────┘        └──────────┬───────────┘    │
│          │                          │                │
│   ┌──────▼──────────────────────────▼────────────┐   │
│   │          Programmable Logic (PL)             │   │
│   │                                              │   │
│   │         RISC-V Soft-Core Processor           │   │
│   │                                              │   │
│   └──────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────┘
```

**Core 0** (`friscv_app_core_0`) — Program control: loads RISC-V programs into memory and coordinates system startup and lifecycle.

**Core 1** (`friscv_app_core_1`) — Memory arbitration and I/O: manages concurrent memory access requests and handles peripheral communication.

**Semaphore layer** (`dual_arm_semaphore_example`) — Inter-core synchronization primitives used to prevent race conditions between the two ARM cores.

**Platform memory** (`friscv_platform_memory`) — Shared memory layout and access abstractions used by both cores.

**Software runner** (`software_runner`) — Utility to load and dispatch RISC-V binaries to the processor.

**Hardware** (`hardware`) — FPGA constraints and configuration files for the target board.

## Key Features

- **Dual-core coordination**: ARM Core 0 and Core 1 operate concurrently, each with a distinct role, synchronized via hardware semaphores.
- **Memory arbitration**: arbitration logic ensures conflict-free access to shared RISC-V instruction and data memory.
- **Clock management**: ARM-side clock configuration for the RISC-V core in PL.
- **Hardware-validated**: the full system was tested on physical FPGA hardware, with memory throughput and synchronization behavior evaluated under real operating conditions.

## Repository Structure

```
├── friscv_app_core_0/          # Core 0 application (program control)
├── friscv_app_core_1/          # Core 1 application (memory arbitration)
├── friscv_app_system/          # System-level initialization
├── friscv_platform_memory/     # Shared memory definitions and access layer
├── dual_arm_semaphore_example/ # Inter-core synchronization example
├── software_runner/            # RISC-V program loader utility
└── hardware/                   # FPGA board constraints and config
```
