# 42sh

## Objectif

- Write a UNIX bash-like shell

## Downloading
You can clone by copy-paste this command :
```
$> git clone https://github.com/GrandChaman/42sh.git
```

## Compilation

Run `make`command

## Utilisation

/!\ Remember: The project was mainly developed in/for a macOS Sierra environment (10.12.16). The project may not behave as desired under another operating system. /!\

Once the 42h project is compiled you can run it using the `./42sh` command.

## Features
/!\ PRECISION: Official POSIX documentation link: http://pubs.opengroup.org/onlinepubs/9699919799/) /!\

- Editing the command line using the termcaps library.

- The features of the `ctrl + D` and `ctrl + C` key combinations in line editing and process execution.

- Command separator `;`

- Pipe `|`

- The logical operators `&&` and `||`.

- Execution of simple commands with their parameters and PATH management.

- Jobs Control with `jobs`, `fg`, `bg` command and `&`

- Simple scripting shell with bash syntax. Execute your script like `./42sh test.sh`
  - `while`, `do`, `if`, `elif`, `fi`, `done`
  - Increment your variable like `x=$(($x + 1))`

- Error and command return value management with `echo $?` command.

- Advanced redirections: file output aggregation and heredoc `<<`

  - The four redirections `<`, `>`, `<<` (heredoc) and `>>`.
  - File descriptor aggregations, for example to close the error output (`>&` and `<&`).

- Use the up and down arrows to navigate through the command history, line editing possible.

- Cut, copy and/or paste all or part of a line with the following key sequences: 

  - `shift + LEFT/RIGHT  Select text.
  - `alt + C` Copy the selected text.
  - `alt + V` Paste the selected text.
  - `alt + X` Cut selected text.

- Move left and right by "word" with `ctrl + LEFT` and `ctrl + RIGHT`.

- Go directly to the beginning and end of a line with the home and end keys.

- Write and edit a command on several lines. In this case, `alt + UP` and `alt + DOWN` allow you to go from one row to another of the command while remaining on the same column or the column.

- Complete management of quotas and double quotas, even on several lines (excluding expansions).

- Auto-completion with tab key

- Local variable management with set and unset builtins

- Implementation of the following builtins respecting the standards dictated by POSIX:

  - cd
  - echo
  - exit
  - env
  - setenv (export equivalent under bash)
  - set
  - unsetenv
  - unset

- Order history and builtins history and ! with all their options.

## Authors

Frederic Bertoria - https://github.com/fbertoia 

Francis Le-Roy - https://github.com/GrandChaman/42sh 

Hugo Fontaine - https://github.com/Usiten 

Romain Fautier - https://github.com/rfautier
