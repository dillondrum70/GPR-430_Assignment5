# Programming Assignment 5 -- TCP Sorting Server

The purpose of this assignment is to help you practice writing TCP
server code. You will create a server which will receive connections
from clients and sort numbers for them, like the server in the first
networking assignment did.

As always, to begin this assignment:
- Create a new repository from this template repository.
- Make your new repository private and owned by the CC-GPR-430
  organization.
- You can check to ensure that your assignment is working as expected
  by observing the workflow results on GitHub.
  - As always, you only need the tests to pass on one platform. It
    doesn't matter which.
- When you're ready to submit, simply submit a link to your
  repository.


## Assignment Details

### Part 1 (20 Points)

1. Complete the constructor within the SortServer class. This
   function should accept a hostname/IP and port number, create a TCP
   socket for the server to use, and bind this socket to the provided
   host and port ("localhost" on port 20000).

3. Complete the run_server() function. This function should do the
   following:

	- Begin listening on the server socket (use a backlog parameter of
      20).
	- Accept connections from clients. (This should be in a loop of
      some sort so that we can accept consecutive connections.)
	- Parse the data provided by the client to ensure that it is valid:
		- Assume that the data is encoded using ASCII -- it will only
          send values in the range [0, 127].
		- The string starts with "LIST" followed by a space
		- "LIST" is followed by a list of items (only integers and
          floating-point numbers are allowed!)
		- If the data is found to be invalid for any reason, return
          the string "ERROR" back to the user.
	- If the data is valid, the server must sort the numbers
      numerically.
    - Once sorting is finished, the server must send the
      list back to the user with the prefix "SORTED " attached to the
      front.

| **If the client sends...** | **The server should return...** |
|----------------------------|---------------------------------|
| LIST 5 4 3 2 1             | SORTED 1 2 3 4 5                |
| LIST 4.2 7.8 -9 404        | SORTED -9 4.2 7.8 404           |
| 4.2 7.8 -9 404             | ERROR                           |
| LIST                       | ERROR                           |
| LIST 1 2 3 4 x             | ERROR                           |
| LIST 127a 0 2 4            | ERROR                           |

### Part 2 (20 Points)
1. Update your server to accept an optional parameter that specifies
   how the list should be sorted. Possible values are:

- 'a': Sort the numbers in ascending order
- 'd': Sort the numbers in descending order
- 's': Sort the numbers alphabetically (i.e., treat them all as
  strings)

This parameter should be attached to the very end of the list,
separated from number string by a pipe character ("|"). If it is not
present, sort the numbers ascending order as in Part 1.

| **If the client sends...** | **The server should return...** |
|----------------------------|---------------------------------|
| LIST 5 4 3 2 1             | SORTED 1 2 3 4 5                |
| LIST 5 4 3 2 1\|a          | SORTED 1 2 3 4 5                |
| LIST 5 4 3 2 1\|d          | SORTED 5 4 3 2 1                |
| LIST 5 404 3 2 1\|s        | SORTED 1 2 3 404 5              |
| LIST 1 2 3 4 5a            | ERROR                           |
| LIST 1 2 3 4 5\|b          | ERROR                           |


## Grading
- Q1: 20 points
- Q2: 20 points
- Submission and code style: 10 points

**Total: 50 points.**

As usual, grading will be done automatically when you submit to
github. **So far, only the clang compiler with ubuntu seems to be
working.** If you can't get the tests to pass on github but feel
confident it's because of some linux/windows cross-platform issue,
feel free to let me know and I will download and run your main file.

## Testing
You can use `lab5_test_client.py` to test your code. This can be run
on Windows by double-clicking `runclient.bat`. Make sure you start
your server first before trying to run the client.
