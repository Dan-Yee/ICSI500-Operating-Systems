# Programming Project 2
The goal of this project was expand on the synchronous Producer and Consumer from Project 1. 

The changes/additions made include the creation of the Application module. In this module, fork() was used to allow for concurrent execution of the Producer and Consumer. pipe() was used to allow the parent (producer) to communicate with the child (consumer) by sending an encoded dataframe.
