# Underling
-----

### A naive implementation of the `at` command.
-----

Accepts several options, -d, -h, and -v, they are Daemonize, Help, and Version respectively.

Usage is as follows:
`underling [-dhv] <time in seconds> <command>`

Depending on how your shell parses commands, command should, or should not be quoted.

For Bash V5, quotes are needed around the command.

For now, the timescale parser is non-existent.
It may be added in the future.

Given a command (daemonized or not), the process will execute the command given in the context of the current working directory after the time specified in seconds.

To compile it, `cd` into the cloned git directory, `mkdir build` then `cd build`, finally run `cmake ../` and `make`

Binary will be titled `underling`, use it with `./underling`
