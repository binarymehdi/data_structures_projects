
# Word Wide Social media usage

Social media has had a profound impact on our lives in the 21st century. It has become a powerful tool for connecting people, sharing information, and influencing public opinion. It has also changed the way businesses market their products and services, and given individuals access to a global platform for sharing their thoughts and ideas. In this project, we work with file called social_media.txt that has data collected from www.statista.com, a leading provider of market and consumer data. We have created this program to help us take a deeper look at the data provided and to understand it better. 
-----------------------------------------------------------------------
## Concepts covered:
    Arrays, files, structures 
## Instruction:

You are asked to write a C program that will allow a user to use the 
following menu options 
1.  View the file content on screen  
2.  Load the file content to an array 
3.  Get the country with the highest number of social media users  
4.  Sort data by number of social media users 
5.  Get a country’s social media data 
6.  Quit  

## Important points to consider: 

1.  Excluding quit, and including printing the menu, each menu 
option must be solved using a user defined function  
a.  You must design your functions properly  
i.  Identify input, output arguments properly  
ii.  You will lose points for bad functions’ design  

2.  You will have to use a structure called social_media_info that 
will contain the needed elements that you will retrieve from the 
file

a.  The file has data about country name, active usage 
penetration percentage, the most used social media 
platform, and the number of active social media users (in 
millions)
b.  The number of users should be a numerical variable 
i.  Don’t change the content or the structure of the file 


3.  The first menu option is meant to display the content of the file to screen 

4.  The second menu option is used to load the content of the file to 
an array of type social_media_info declared in the main function 

5.  The third menu option is used to send to the main function the 
name of the country who has the highest number of active social 
media users 
a.  You use the content of the array not the file 
b.  Don’t sort the array 
c.  Don’t use return nor any output function as you define the 
function 

6.  The fourth menu option is used to sort the content of the array 
by number of social media users  
a.  Use selection sort 

7.  The fifth menu choice is used to send to the main function social media data of a country X 
a.  The country may or might not exist in the array 
b.  The result should be printed in the main function 

8.  Options 3,4,5 should not be executed till option 2 is chosen by the user 

9.  No global variables should be used in this project 

10. You lose points for printing results or getting input in user defined functions that must be handled by the main function 
 
 