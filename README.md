# Input/Output and file system management
## Command List
1. **cd**.
2. **cp**.
3. **pwd**.
4. **cat**.
5. **ls**.
6. **exit**.
7. **touch**.
8. **grep**. 
9. **man**.
10. **mv**.

## System calls
1. **open**
2. **read**
3. **write**
4. **close**
5. **link**
6. **unlink**
7. **stat**
8. **readdir**
9. lseek
10. **chmod**

## C library functions
1. **opendir**
2. **closedir**

# Process management
## System calls
1. **fork**
2. **wait**

## C library functions
• execlp or **execvp**

1. There should be an option to concatenate commands with pipes.
2. **Each of the commands created should work on their own, they should be independent
programs.**
3. The users should have the option to list the last movements done (last commands used).
4. **All possible error should be handled and users should be informed about the reason of the
error. For example:
▪ $ ls añsldk
ls: cannot access añsldk: No such file or directory**
5. **Every command should have a man page with its specification.(not completed)**
6. The code should work on the course server (dif-linuxserver.ehu.es).
