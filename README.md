# Underling
-----

### A naive implementation of the `at` command.
-----

Accepts one option, `-d`, telling the process to daemonize (run in the background unaided).

Usage is as follows:
`underling [-d] <time in seconds> <command>`

Depending on how your shell parses commands, command should, or should not be quoted.

For Bash V5, quotes are needed around the command.

For now, the timescale parser is non-existent.
It may be added in the future.

Given a command (daemonized or not), the process will execute the command given in the context of the current working directory after the time specified in seconds.
