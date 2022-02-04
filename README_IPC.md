# IPC using pipes

This branch experiments executing builtins inside a fork.

The forks will communicate with the parent using a dedicated pipe.

Data will be sent using simple keyvalue pairs, all the communication is exclusively used to mutate the state of the parent
process.

## Builtin IPC Transaction

* 4 types of messages, 4 types of actions
  * ENV_ADD, adds to the env vars
  * ENV_DEL, removes from env
  * CHDIR, changes dir of parent process
  * RET_STATUS, finishs data transfer

As soon a forked buiitin runs the parent listens for communication and processes
all the mutations needed.

At the end of the transaction the builtin is expected to send a RET_STATUS message
which ends the read cycle. If this not is done undefined behaviour or errors might occur.