# IPC using pipes

This branch experiments executing builtins inside a fork.

The forks will communicate with the parent using a dedicated pipe.

Data will be sent using simple keyvalue pairs, all the communication is exclusively used to mutate the state of the parent
process.