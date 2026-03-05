# Command Line Interpreter

C++ implementation of a command line interpreter (CLI) with support for pipes, I/O redirection, and batch processing, developed as part of an Object-Oriented Programming course.

## Overview

This project implements a simplified but fully functional command line interpreter inspired by Unix shells. The interpreter reads commands interactively from the console, parses them using a lexer-parser pipeline, and executes them with support for input/output redirection, piping between commands, and batch script execution. The architecture is designed with extensibility in mind — new commands can be added by simply creating a new class and registering it in the command factory.

## Features

- **Interactive command prompt** with customizable prompt string
- **Lexical analysis** with full error reporting (highlights invalid character positions)
- **Pipeline support** — chain multiple commands with `|`
- **I/O redirection** — input (`<`), output (`>`), and append (`>>`)
- **Batch processing** — execute command scripts from files, including recursive batch calls
- **Numeric pipeline references** — reference earlier pipeline stages by index
- **Command history** with filtering and re-execution
- **Extensible command architecture** using the Factory and Template Method patterns
- **Visitor-based error handling** with distinct error categories (lexical, syntax, command, file, unknown command)

## Supported Commands

| Command | Description |
|---------|-------------|
| `echo` | Pass-through with options for uppercase (`-u`), lowercase (`-l`), reverse (`-reverse`), repeat (`-rN`), and tab indentation (`-t`) |
| `wc` | Count words (`-w`), characters (`-c`), lines (`-l`), blanks (`-b`), unique words (`-unique`), longest/shortest word (`-max`/`-min`) |
| `tr` | Find and replace text with options for case-insensitive (`-i`), first-only (`-first`), and count mode (`-count`) |
| `head` | Output first N lines (`-nN`) or characters (`-cN`) |
| `tail` | Output last N lines (`-nN`) or characters (`-cN`) |
| `time` | Display current time with options for individual components (`-h`, `-m`, `-s`) |
| `date` | Display current date with options for day (`-d`), month (`-m`), year (`-y`), day of week (`-day`), epoch (`-r`), date difference (`-diff`), and tomorrow/yesterday |
| `touch` | Create an empty file |
| `truncate` | Clear file contents |
| `rm` | Delete a file |
| `copy` | Copy content to a file with optional append mode (`-a`) |
| `batch` | Execute commands from a script file |
| `prompt` | Change the command prompt, with one-time mode (`-t`) |
| `grep` | Search for text in input with invert match (`-v`) |
| `diff` | Compare two files or file against input |
| `sort` | Sort words alphabetically, with descending option (`-d`) |
| `cat` | Concatenate input with optional line numbering (`-n`) |
| `history` | Display command history with filtering and count limit (`-nN`, `-c`) |
| `last` | Re-execute previous commands or cut pipelines by index |
| `count` | Count total or per-command executions from history |
| `find` | Filter lines matching a pattern |
| `menu` | List all available commands |
| `clear` | Clear the terminal screen |
| `exit` | Exit the interpreter |

## Architecture

```
main.cpp
  └── CommandLineInterpreter (implements SystemContext)
        ├── Lexer          — tokenizes input into typed tokens
        ├── Parser         — builds command objects from tokens, splits pipelines
        ├── CommandFactory  — registry-based command creation (Factory Pattern)
        ├── PipelineExecutor — wires I/O between piped commands
        └── ErrorHandler    — visitor for typed exception handling (Visitor Pattern)

Command (abstract base)
  ├── StreamManager — uniform I/O abstraction (console, file, string)
  ├── run()         — template method: setup I/O → execute()
  └── execute()     — pure virtual, overridden by each command
```

### Design Patterns

- **Factory Pattern** — `CommandFactory` uses a registry map of lambda creators to instantiate commands by name, enabling easy extension without modifying existing code.
- **Template Method** — `Command::run()` defines the I/O setup skeleton, while subclasses implement only `execute()` with command-specific logic. In pipelines, `PipelineExecutor` handles I/O setup and calls `execute()` directly.
- **Visitor Pattern** — Exception hierarchy (`InterpreterException` and subclasses) uses double dispatch via `accept(ErrorHandler&)` for type-specific error formatting.
- **Dependency Inversion** — Commands interact with the interpreter through the `SystemContext` abstract interface, avoiding circular dependencies.

### Key Components

- **`Lexer`** — Validates characters, handles quoted strings, and produces typed tokens (WORD, QUOTED_STRING, PIPE, INPUT_REDIRECT, OUTPUT_REDIRECT, APPEND_REDIRECT).
- **`Parser`** — Splits token stream at pipe boundaries, resolves numeric pipeline references, parses each segment into a `Command` with options, arguments, and I/O redirections, and validates pipeline semantics.
- **`StreamManager`** — Provides a uniform `std::istream&` / `std::ostream&` interface regardless of whether the underlying source is stdin/stdout, a file, or an in-memory string. Manages ownership and cleanup of heap-allocated streams.
- **`PipelineExecutor`** — Chains commands by capturing each command's output in a `std::stringstream` and feeding it as the next command's input.

## Project Structure

```
cpp-command-line-interpreter/
├── README.md
├── .gitignore
├── include/          # Header files
│   ├── Command.h
│   ├── CommandFactory.h
│   ├── CommandLineInterpreter.h
│   ├── ErrorHandler.h
│   ├── InterpreterException.h
│   ├── Lexer.h
│   ├── Parser.h
│   ├── PipelineExecutor.h
│   ├── StreamManager.h
│   ├── SystemContext.h
│   ├── Types.h
│   └── ...           # All command headers
└── src/              # Source files
    ├── main.cpp
    ├── Command.cpp
    ├── CommandFactory.cpp
    ├── CommandLineInterpreter.cpp
    ├── Lexer.cpp
    ├── Parser.cpp
    ├── PipelineExecutor.cpp
    ├── StreamManager.cpp
    ├── ErrorHandler.cpp
    └── ...           # All command implementations
```

## Build and Run

Compile and run using a standard C++17 compiler:

```bash
g++ -std=c++17 -Iinclude -o cli src/*.cpp
./cli
```

## Usage Examples

Basic command execution:
```
$ echo "Hello, World!"
Hello, World!
$ wc -w "Lorem ipsum dolor sit amet"
5
```

Piping and redirection:
```
$ time | tr -":" "." | wc -c >output.txt
$ echo "Hello World" | wc -w
2
```

Batch execution:
```
$ batch script.txt
$ batch script.txt >output.txt
```

History and re-execution:
```
$ history
1. echo "hello"
2. wc -w "test string"
$ last
```

## Project Context

This project was developed as part of the Object-Oriented Programming course (2025/2026 academic year) at the Faculty of Electrical Engineering, University of Belgrade. The project covers two phases:

- **Phase 1** — Core commands (`echo`, `time`, `date`, `touch`, `wc`) with argument and option support
- **Phase 2** — Full implementation including all commands, I/O redirection, pipelines, batch processing, and comprehensive error handling

## License

This project is licensed under the MIT License.

## Author

Magdalena Savić
Faculty of Electrical Engineering, University of Belgrade
