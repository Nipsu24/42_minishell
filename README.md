<h1 align="center">minishell</h1>

> Hive Helsinki (School 42) 9th curriculum project (Rank03)

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#Program scope">Program Scope</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#instructions">Instructions</a>
  <span> · </span>
	<a href="#testing">Testing</a>
</h2>

## About
The repository contains a custom shell, replicating the behavioiur of the bash command line shell. It is the first project in the school 42 curriculum
conducted in a team consisting of 2 students. Thus, apart from learning in-depth about the characteristics of the bash language, the logic and setup of
a command line shell and how to structure and develop a complex program written in C (consisting of extensive parsing/lexing, command execution of both
built-in and external commands and comprehensive signal handling), the setup of a joint git repository and agreement on a suitable and efficient working
mode is another pivotal aspect of this project.

## Program Scope

### EXECUTION  
**builtins:**
  - `echo` with option -n
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
   
The implementation orients closely on a bash shell, whereby the following functionalities **are out of scope**:  
`unclosed quotes`, `whildcards *`, `&&`, `||`

## Requirements
-`gcc` compiler
with `<readline.h>` 

## Instructions

### 1. Compiling the program

To compile the minishell, clone the repository, cd into the folder and run:

```
$ make 
```
### 2. Cleaning all binary (.o) and executable files

To delete all files generated with make, run:
```
$ make fclean
```

## Testing
This library has been tested with [minishell_tester] (https://github.com/LucasKuhn/minishell_tester)
