# Housing issues 

## Description:

Housing is an AUI issue:
Many students prefer to live on campus but currently AUI cannot afford to have all the students on campus given the current high number of students. Still, some considerations are made to have some students live on campus if rooms are available. We consider the following considerations:
2
1. First year student (15 points priority)
2. Student has health issues (10 points priority)
3. Others (5 points priority)

## Concepts covered:
heaps, heap sort, files, structures 
## Instructions



To work on a small scale, we will work with a heap of size 20.
We will use a structure called student_info that consists of three elements: name, ID and priority (a numerical variable).
I am providing you with a file called OnCampusRequests.txt that contains data about students who requested to live on campus for Spring2023.
You need to write a C program used to manage the requests to live on campus using the following menu:
1. Start the program
2. Add a request
3. Grant a student a room on campus
4. View requests in a sorted way
5. Cancel a request
6. Quit
Please note that each menu option should be implemented using a user defined function.
Let’s elaborate each menu option:
- Option 1: When the user chooses option1, your program should load the content of the file to the heap.
o A max heap should be constructed
o Make sure that each element of the heap has the corresponding priority
- Option 2: this option is used to add a new student to the list of students requesting living on campus
o Option 2 should not be executed if the user did not choose option 1 first
o The heap might be full
3
▪ Main function should print a message informing the user than no more requests can be added!
- Option 3: In this option, you need to send to the main function data about the student who was granted a place to live on-campus.
o The output in the main should be in the following format:
Student……….. with ID:……… was assigned a room on campus because: …….(state the reason)……..
o Option 3 should not be executed if the user did not choose option 1 first
- Option 4 is used by the housing manager to view students’ requests sorted using the priority
o From the highest to lowest
o Use heapsort
o Data about students should be display in a tabular format as follows:

o Option 4 should not be executed if the user did not choose option 1 first
- Option 5: This option is meant to drop a student request to live on campus.
o Option 5 should not be executed if the user did not choose option 1 first
o Student may or might not exists
o When the student is dropped, main should display a message in the following:
4
Student …………with ID: ….. who applied for living on campus for reason…………….., was deleted from the heap.
- Option 6: For the last option, quit, any student left in the heap should be saved in a file called ToContact.txt:
o The file should contact only the students email addresses as the housing director needs to contact students by email to inform them that no on-campus housing will be provided for next Spring.
▪ Email adopted here in AUI is studentID@aui.ma
o Option 6 should not be executed if the user did not choose option 1 first