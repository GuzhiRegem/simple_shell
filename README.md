
<<<<<<< HEAD
Project - Simple Shell

Everything you need to know to start coding your own shell
=======

# simple-shell was created focusing on Linux command line interpreter.



Our shell is gonna be a huge loop where a prompt will be printed depending de mo
de, if interactive or non interactive, and is going to
get some input from the user and the is gonna parse it and try to do something w
ith it.

Input will be taken using the function getline() and will be tokanized with the
function str_to args. If it is builtin, that we createad our selves for exapmle
cd command.
simple_shell will do a similar job with the enviroment variable PATH= concatenat
ing the parsed enviroment.

It will start in interactive mode to print the promt and wait for the user to en
ter some input and our program will parse the string into tokens and will return
a pointer to the first position of a string and for the next call will move the
ptr one place in the variable out writtnig the current working directoy followed
by prompt.
Using getline() variable characters will add the value of the buffer terminating
with 0, that in ASCCI table represent a null byte.

Before forking the process will check the status and if existe the file or if ac
cess is allowed it. if not error message will pop up.
Use execve() to substitute the code running with the new proccess code called.
A copy of the proccess is created using an other sys call; fork() so two program
s will run simultaneosly with differents ID numbers.
To complete the excecution we use wait() until the child is over. so the propmt
will show up again, with the main loop of our shell still running.
i.e.
\
void execute(char *command, char **arguments, char **env)
 {
        int pid, exit_status;

        pid = fork();
        if (pid == 0)
        {
                execve(command, arguments, env);
                exit(0);
        }
        else
                wait(&exit_status);
}
