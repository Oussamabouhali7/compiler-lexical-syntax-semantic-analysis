# Compiler — Lexical, Syntax, and Semantic Analysis

## 📌 Overview

This project implements the main analysis phases of a compiler: **lexical analysis, syntax analysis, and semantic analysis**. It processes source code step by step to identify tokens, validate grammatical structure, and detect semantic errors.

## 🔍 Compiler Phases

### 1. Lexical Analysis

The lexical analyzer scans the source code and converts it into a sequence of tokens.

It identifies elements such as:

* Keywords
* Identifiers
* Constants
* Operators
* Separators
* Literals

It also detects invalid or unknown tokens.

### 2. Syntax Analysis

The syntax analyzer verifies whether the sequence of tokens follows the grammar rules of the language.

It is responsible for:

* Parsing the token stream
* Checking grammatical rules
* Detecting syntax errors
* Building the corresponding parse structure

### 3. Semantic Analysis

The semantic analyzer verifies the meaning and consistency of the source code.

It handles checks such as:

* Variable declarations
* Type compatibility
* Scope rules
* Identifier usage
* Assignment validity
* Semantic errors

## 🏗️ Architecture

```
          text
      Source Code
           │
           ▼
┌─────────────────────┐
│ Lexical Analysis    │
│ Tokenization        │
└──────────┬──────────┘
           │ Tokens
           ▼
┌─────────────────────┐
│ Syntax Analysis     │
│ Parsing             │
└──────────┬──────────┘
           │ Parse Structure
           ▼
┌─────────────────────┐
│ Semantic Analysis   │
│ Validation          │
└──────────┬──────────┘
           │
           ▼
      Valid Program
      or Error Report
```

## 🛠️ Technologies

* Lexical Analysis
* Syntax Analysis
* Semantic Analysis
* Parsing
* Context-Free Grammars
* Symbol Tables
* Compiler Design Concepts

## 📂 Project Structure

```text
├── lexical/
│   └── lexical analysis files
├── syntax/
│   └── syntax analysis files
├── semantic/
│   └── semantic analysis files
├── examples/
│   └── test source codes
└── README.md
```

> The actual structure may vary depending on the implementation.

## 🚀 Getting Started

### Clone the repository

```bash
git clone https://github.com/your-username/compiler-lexical-syntax-semantic-analysis.git
cd compiler-lexical-syntax-semantic-analysis
```

### Run the project

Use the appropriate command for your implementation to compile and execute the analyzer.

```bash
# Example
python main.py
```

## 🧪 Testing

The project can be tested using source-code examples containing:

* Valid programs
* Lexical errors
* Syntax errors
* Semantic errors
* Type inconsistencies
* Invalid declarations or identifier usage

## 🎓 Academic Context

This project was developed as part of a **Compiler Design / Compilation** course and focuses on understanding the fundamental stages involved in the compilation process.



⭐ Feel free to explore the project and its implementation of the different compiler analysis phases.
