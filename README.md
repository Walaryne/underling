# Underling
-----

### A naive implementation of the `at` command.
-----

Accepts several options, -d, -h, -t, and -v, they are Daemonize, Help, Dump Time, and Version respectively.

Dump Time allows you to see how far in the future the command will be executed in seconds.
This is displayed as a double (rounded if need be).

Daemonize simply means it will run unattended, free of the calling shell.
(You can close the prompt after the command is run, for instance.)

Options for time duration are -Y (Years), -M (Months, 30 days), -D (Days), -H (Hours), -m (Minutes), -S (Seconds).
At least one of these options must be specified with a number in order for execution to occur. A number must be affixed with these options after a space. The number may be in the form of 0 or 0.0.

Usage is as follows:
`underling [-dhvtYMDHmS] <command>`

Depending on how your shell parses commands, command should, or should not be quoted.

For Bash V5, quotes are needed around the command.

The timescale parser has been implemented!
Use of the duration options allows for this.
You may combine any of them together, and you can even use doubles (0.0 notation) to specify duration!

Given a command (daemonized or not), the process will execute the command given in the context of the current working directory after the time specified using the various options for specifying durations.

To compile it, `cd` into the cloned git directory, `mkdir build` then `cd build`, finally run `cmake ../` and `make`

Binary will be titled `underling`, use it with `./underling`
