# Advent of Code 2025 — Multi-Language Rotation Challenge

A full Advent of Code 2025 repository built as a deliberate programming training exercise, where each day's problem is solved in a different language through a rotating schedule across:

* C
* C++
* x86-64 Assembly
* Go
* Python
* Haskell

Instead of solving every problem in a single language, this project uses Advent of Code as a structured way to sharpen programming aptitude by repeatedly switching paradigms, abstraction levels, and development styles.

## Project Goal

The purpose of this repository is not just to complete Advent of Code, but to improve adaptability as a programmer.

Each new problem introduces two simultaneous challenges:

1. Solving the algorithmic puzzle itself
2. Solving it within the constraints and idioms of a different language

That constant context switching forces deeper understanding of:

* Algorithms and data structures
* Systems-level thinking
* Memory management
* Functional vs imperative design
* Debugging strategies
* Toolchains and build systems
* Performance tradeoffs
* Language-specific problem solving

The rotation system intentionally prevents over-reliance on the conveniences of any single language.

## Why Rotate Languages?

Most Advent of Code repositories optimize for speed and consistency by staying in one ecosystem.

This project instead treats each puzzle as a learning opportunity.

Switching languages daily forces you to repeatedly adapt your thinking:

* Python emphasizes rapid prototyping and expressive implementation
* C develops awareness of memory, layout, and manual control
* C++ encourages efficient abstraction and performance-conscious design
* Go introduces concurrency-oriented thinking and pragmatic tooling
* Haskell strengthens recursive and functional reasoning
* Assembly pushes understanding down to instruction flow, registers, and CPU-level execution

The goal is not mastering syntax alone, but building flexibility in how problems are approached.

## Repository Structure

```text id="9l2vma"
.
├── day01/
│   ├── solution.py
│   ├── NOTES.md
│   └── input.txt
├── day02/
│   ├── solution.cpp
│   └── ...
...
├── benchmarks/
└── README.md
```

Each day is self-contained and includes:

* The solution for that day's chosen language
* Notes about implementation decisions
* Reflections on language-specific challenges
* Observations about performance or tooling

## Core Learning Areas

### 1. Adapting Between Paradigms

One of the biggest goals of the project is reducing attachment to a single programming style.

Some days require:

* Recursive functional decomposition
* Low-level manual state management
* Concurrent execution models
* Object-oriented structuring
* Procedural optimization

Rotating languages forces repeated exposure to all of them.

### 2. Understanding Abstraction Levels

The contrast between languages becomes especially visible when solving similar categories of problems.

For example:

* Parsing input in Python can take minutes
* Parsing the same input in Assembly can become a substantial engineering task

That difference teaches how much modern languages abstract away — and what those abstractions cost or simplify.

### 3. Strengthening Systems Intuition

Working in C and Assembly regularly builds awareness of:

* Memory layout
* Stack behavior
* Pointer manipulation
* Data movement
* Allocation costs
* Cache-conscious thinking

Even when returning to higher-level languages afterward, that understanding improves overall programming judgment.

### 4. Building Debugging Discipline

Switching ecosystems constantly means adapting to different:

* Compilers
* Error models
* Runtime behavior
* Toolchains
* Debugging workflows

Over time, this develops stronger debugging habits and greater comfort working outside familiar environments.

## Build Philosophy

There is intentionally no unified build system.

Part of the educational value comes from working directly with each language's native tooling:

* `gcc`
* `g++`
* `go run`
* `ghc`
* assembler/linker workflows
* Python execution environments

The goal is to become comfortable inside each ecosystem rather than abstracting them behind one interface.

## What This Project Trains

This repository is ultimately a long-form programming exercise focused on improving:

* General problem-solving ability
* Cross-language fluency
* Algorithmic thinking
* Systems programming intuition
* Adaptability under constraints
* Low-level reasoning
* Debugging skills
* Performance awareness

Advent of Code simply provides the structure; the real objective is deliberate practice through repetition, variation, and exposure to multiple ways of thinking about software.
