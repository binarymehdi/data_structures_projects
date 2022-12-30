# Wait for your turn !

This project helps manage a queue 

## Concepts covered: 
Circular queues, round robin algorithm, files, structures



## Instructions: 

I will use a circular queue to manage students requests using the following menu:
    -----------------------------------
    1. Add a student to a queue
    2. Time is up
    3. Print the content of the queue
    4. Student is no more interested
    5. I need my toy back
    ------------------------------------

- Each student will be represented with a name and an ID

- Option1: is used to add an already created node to the queue
o You are using enqueue() but your queue must be circular

- Option2: The time allocated for the first student in the queue is over
o Queue might be empty!
o The first student in the queue has the choice to remain in the queue (as he/she still want to play more with toy) or leave the queue
▪ If the student decide to stop playing: dequeue()
▪ Otherwise, decide what to do…..
• Remember front should point to the node to serve and rear must point to the last element in the queue!

- Option 3: You need to print the list of the students interested to have the toy from me
o Probably no student is interested so far

- Option 4: A student X wants to leave the queue as he/she is not interested in getting the toy from me. Let’s design a function that will remove a student with ID Y from the queue.
o The student is probably not in the queue!

- Option 5: I decided to have my toy back! Let’s destroy the queue!!
o Remember this is not serving!!