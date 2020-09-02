# Unix shell 
--------
_A program that simulates behavior of Linux shell zsh._

_Developed as study assignment in the Ucode school._

## Description:
```
The program is a Unix shell that can be used as an interactive login shell and as a command interpreter for shell scripting.
Ush has comand line editing, builtin spelling correction, programmable command completion, shell functions (with autoloading), 
a history mechanism, and a host of other features.
```

## Features:

**1.** Execution of external commands (bin files).\
**2.** Execution of builtins.\
**3.** Meta-circular interpreter.\
**4.** Interpretation of complex grammar of input line including command\
separator ( ; ), pipeline ( | ), command substitution, redirections.\
**5.** Expansions of tilda (~).\
**6.** Variables ( $name, ${name}).\
**7.** Escape working accordingly in no quote, quote, double quote expressions.\
**8.** Ctrl+C, Ctrl+D, Ctrl+Z.\
**9.** Command history.\
**10.** Backspace key while inputting line.\


## Usage:
```
1. git clone https://github.com/vladyslav-n/ush.git
2. make
3. ./ush
```

## Builtins-table:
| Builtin  | Description |
|:-:|:-:|
|**cd**| Change the working directory |
|**pwd**| Wites the full pathname of the current working directory |
|**chdir**| Change the working directory|
|**unset**| Remove variable or function names from enviroment |
|**export**| Set the export attribute for variables to enviroment|
|**fg**| Run jobs in the foreground |
|**jobs**| Print currently running jobs and their status |
|**which**| Locate a command and display its pathname or alias |
|**echo**| Write arguments to standard output |
|**env**| Set the environment for command invocation |
|**exit**| Cause the shell to exit |
|**true**| Stop shell with exit status 0 |
|**false**| Stop shell with non-zero exit status |
         

## Developers:

[Vladyslav Nazarenko](https://github.com/vladyslav-n)

[Olha Lytvynenko](https://github.com/hlgltvnnk)

[Ilya Minakov](https://github.com/i-minakov)
