
# What’s a Design Pattern?
Design patterns are customizable solutions for recurring software design problems, differing from algorithms as they are high-level concepts needing adaptation for specific contexts.

# What Does the Pattern Consist Of?
Patterns include sections like Intent (problem and solution), Motivation (context of the problem), Structure (relationships between components), and Code Example (practical implementation).

- Intent:
Describes the problem and solution.

- Motivation:
Explains the context and nature of the problem.

- Structure:
Illustrates the relationships between components.

- Code Example:
Provides a practical example in a popular programming language.

## Classification of Patterns
Design patterns vary in complexity and applicability, categorized into Creational, Structural, and Behavioral patterns, each addressing different aspects of software design

- Creational Patterns:
Focus on object creation for flexibility and reuse.

- Structural Patterns:
Detail assembly of objects and classes into flexible structures.

- Behavioral Patterns:
Address communication and responsibility assignment between objects.

## Who Invented Patterns?
The concept of design patterns originated from Christopher Alexander's work in urban design and was popularized for programming by the "Gang of Four" in their book, "Design Patterns: Elements of Reusable Object-Oriented Software."


## Features of Good Design

- Code Reuse
Code reuse is a vital strategy for reducing development costs and accelerating time-to-market. Although the concept of reusing existing code is appealing, challenges arise when trying to adapt existing code for new contexts due to:

- Tight coupling between components.
- Dependencies on concrete classes rather than interfaces.
- Hardcoded operations.


## Single Responsibility Principle

A class should have just one reason to change, focusing on a single part of the software's functionality, fully encapsulated within the class.

The main goal of this principle is to reduce complexity. Simplicity is sufficient for smaller programs, but challenges arise as programs grow, leading to larger classes that are difficult to navigate, understand, and maintain.

To apply the principle effectively, separate the reporting functionality into its own class, isolating behaviors and enhancing maintainability


## Open/Closed Principle

### Open/Closed Principle
Classes should be open for extension but closed for modification to prevent breaking existing code when adding new features.

### Definition of Open
A class is open if it can be extended through subclasses as long as the programming language allows it.

### Definition of Closed
A class is closed when it is fully defined with a stable interface that won't change in the future.

### Key Point:
The Open/Closed Principle promotes extensibility while minimizing risk in existing code.


## Liskov Substitution Principle

### Liskov Substitution Principle(LSP)
Objects of a subclass should be replaceable with objects of the superclass without alteringcorrectness.LSP Rule: You should be able to swap Vehicle for Bicycle without the program failing. If it fails, you have violated LSP.

### Parameter Types Compatibility
Subclass method parameters should match or be more abstract than the superclass parameters.


## Interface Segregation Principle


## Dependency Inversion Principle
Aims to improve software design by separating concerns between high-level and low-level classes.

### High-level Classes: Contain complex business logic and coordinate actions with low-level
### Low-level Classes: Handle basic operations like disk access or database management.


Low-level classes are often developed first, creating high-level classes that overly depend on low-level implementations.


1. Define Interfaces: Create interfaces for low-level operations in business terminology.
2. Depend on Interfaces: High-level classes should use these interfaces instead of concrete low-level classes.
3. Implementation by Low-level Classes: Low-level classes implement defined interfaces, reversing the dependency direction.



# Factory Method
The Factory Method is a creational design pattern that provides an interface for creating objects in a superclass while allowing subclasses to decide the exact types of objects that will be created.


# Abstract Factory

# Builder

# Prototype

# Singleton
The Singleton is a creational design pattern that ensures a class has only one instance while providing a global access point to that instance.
