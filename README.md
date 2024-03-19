## Minishell
This project is a simple shell that can execute commands, implement some builtins and manage the environment variables.

## Table of Contents
- [Minishell](#minishell)
- [Table of Contents](#table-of-contents)
- [General Informations](#general-informations)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)

## General Informations

Minishell is a custom shell program that allows users to interact with their Unix-based operating systems through a command-line interface. It provides a set of features similar to those found in popular shells like Bash, including command execution, file redirection, piping, environment variable expansion, and built-in commands.

## Installation

To install Minishell, you will need to have the following dependencies installed on your system:
- make
- gcc
- readline

Once you have these dependencies installed, you can clone the repository and run the following commands to build the program:

```bash
git clone
cd minishell
make
```

## Usage

To run Minishell, simply execute the following command in your terminal:

```bash
./minishell
```

Once the program is running, you can enter commands and interact with the shell as you would with any other command-line interface.

## Features

Minishell provides a number of features that allow users to interact with their operating systems in a variety of ways. Some of the key features include:

- Command execution: Minishell can execute commands entered by the user, including built-in commands and external programs.
- File redirection: Minishell supports input and output redirection, allowing users to read from and write to files as part of their commands.
- Piping: Minishell supports piping, allowing users to chain multiple commands together and pass the output of one command as the input to another.
- Environment variable expansion: Minishell supports environment variable expansion, allowing users to reference environment variables in their commands.
- Built-in commands: Minishell provides a number of built-in commands, including `cd`, `echo`, `env`, `exit`, `pwd`, `export`, and `unset`, which allow users to perform common tasks without needing to invoke external programs.

## Acknowledgements

- The Minishell project was inspired by the Bash shell and Unix shell scripting.
- Special thanks to the 1337 coding school for providing the inspiration and resources for this project.
- We would like to acknowledge [Anas Raji Afoua][https://github.com/AnasUnno] for their valuable contributions to this project and for their collaboration in building Minishell.
