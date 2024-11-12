/*Create a program that generates a random number and asks the
user to guess it. Provide feedback on whether the guess is too
high or too low until the user guesses the correct number. */
#include<bits/stdc++.h>
#include<ctime>
using namespace std;
int main(){
srand( time(NULL));
int finalanswer=rand()%100+1;
int guess;
int chances=0;
 cout << "GUESS THE NUMBER!" << endl;
 cout << "The computer has picked a  number between 1 and 100." << endl;
do{    
        cout<<"enter the number(1-100):";
        cin>>guess;
        chances++;
        //hints
        if (guess > finalanswer) {
            cout << "Too high! Try again." << endl;
        } else if (guess < finalanswer) {
            cout << "Too low! Try again." << endl;
        } else {
            cout << "Congratulations! You took " << chances <<" chances to guess the number"<<endl;
        }
   
   
    }while (finalanswer!=guess);
    
 
 
return 0;
}
