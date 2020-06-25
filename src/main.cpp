/* main.cpp
 * Miriam Farrington
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 * HW #5 - Student-Selected Program
 * 2/16/2020
 *
 * This program is my version of the DOS program from the 1983 cult classic 'War Games',
 * In this movie, a young hacker unwittingly accesses a military supercomputer programmed to predict outcomes of nuclear war.
 * Thinking it is a computer game, he runs a simulation. The computer, tied into the nuclear weapons control system
 * and unable to tell the difference between simulation and reality, attempts to start World War III.
 *
 * Screenshots from the original: https://www.mobygames.com/game/dos/global-thermonuclear-war/screenshots/gameShotId,676012/
 *
 * [Notes] This game features the use of several C++ constructs (arrays, loops, etc) and is purposely slowed
 * down in many places to simulate the output of a 1980's computer :-)
 *
 *.... Are you ready to play?
 *
*/

#include <iostream>
#include <stdlib.h>
#include <zconf.h>
#include "WarGame.h"


using std::cout;
using std::cin;
using std::endl;

using namespace special_functions;

//1. Game Intro and Visual
int main() {

    cout << endl;
    cout << "\x1b[31m         *******************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[31m      *************************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[31m   *******************************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[31m*************************************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[33m                          GLOBAL    " << endl;
    cout << "                      THERMONUCLEAR    " << endl;
    cout << "                           WAR    \x1b[0m" << endl;
    sleep(1);
    cout << "\x1b[31m*************************************************************\x1b[0m" << endl;
    sleep(1);
    cout << "\x1b[31m   *******************************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[31m      *************************************************\x1b[0m  \n";
    sleep(1);
    cout << "\x1b[31m         *******************************************\x1b[0m  \n";
    cout << endl;
    cout << endl;

//2. Prompt Player to make a selection
    cout << endl;
    cout << endl;
    cout << endl;
    sleep(1);
    cout << "   \x1b[31mSHALL WE PLAY A GAME?\x1b[0m  " << endl;
    sleep(1);
    cout << "1. YES  2. NO OR -1 TO EXIT: ";

    int response = 0;

    cin >> response; //read in the user's response

        /*  -----    Start Input Validations -----     */

        validateCin(response); //first check the user has actually entered an integer

    //3. Print appropriate response based on input
        if (response >= 0) {

                while (response > 2) //Check a valid int value is entered, otherwise prompt the user to re-enter
                {
                    sleep(1);
                    cout << "ENTER 1. YES  2. NO OR -1 TO EXIT: ";
                    response = 0; //set the value back to 0
                    cin >> response; //read in the new value
                    validateCin(response); //check the new entered value is an integer
                }


                if (response == 2) { // 'No' Selection

                    cout << endl;
                    cout << endl;
                    sleep(1);
                    cout << "\x1b[31mA STRANGE GAME.\x1b[0m" << endl;
                    cout << "\x1b[31mTHE ONLY WINNING MOVE IS NOT TO PLAY.\x1b[0m" << endl;
                    cout << "\x1b[31mHOW ABOUT A NICE GAME OF CHESS?\x1b[0m";
                    cout << endl;
                    cout << endl;
                }

                if (response >= 0 && response != 2) {

                    /*  -----    End Input Validations -----     */

                    //Print out instructions to play the game
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    sleep(2);
                    cout << " -----------  INSTRUCTIONS ------------" << endl;
                    cout << endl;
                    sleep(2);
                    cout << "PLAYERS TAKE TURNS SELECTING WEAPONS FROM THE LIST (1-7)" <<endl;
                    cout << "THE COST OF EACH WEAPON IS DEDUCTED FROM THE MILITARY BUDGET. " <<endl;
                    cout << "MAKING A SELECTION THAT EXCEEDS THE BUDGET WILL START THE GLOBAL CONFLICT." <<endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    sleep(9);
                    cout << "\x1b[31mCHOOSE YOUR WEAPONS CAREFULLY.\x1b[0m" <<endl;
                    sleep(3);
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    sleep(1);
                    cout << "\x1b[31mCREATING NEW GAME....\x1b[0m" << endl;
                    cout << endl;
                    sleep(2);


                    // 4. Launch a new Game
                    WarGame newGame; //Create a new game object

                    int playerSelection = 0; // variable to hold the player's selection
                    int computerSelection = 0; //variable to hold the computer's (generated) selection
                    int turnResult = 0; //keep track of the outcome of each turn

                            /* Allow players to take turns selecting their weapons
                             * Once either player exhausts their budget,
                             * initiate a conflict (i.e. GLOBAL THERMONUCLEAR WAR)
                             */

                    // 5. Begin taking turns
                    while (turnResult >=0 ) {

                        if (newGame.getTurn()== 1){ //Player's Turn
                            sleep(1);
                            cout << "\x1b[31mUS TURN. WHAT ITEM?: \x1b[0m ";

                            cin >> playerSelection;
                            validateCin(playerSelection);

                            while (playerSelection < 1 || playerSelection > 7) {
                                sleep(1);
                                cout << "\x1b[31mENTER A VALID SELECTION: \x1b[0m";
                                playerSelection = 0; //set the value back to 0
                                cin >> playerSelection; //read in the new value
                                validateCin(playerSelection); //check the new entered value is an integer
                            }

                            //take turn (subtract 1 from player selection to index properly)
                            if (newGame.takeTurn(playerSelection - 1) < 0){
                                sleep(1);
                                cout << "\x1b[31mUS BUDGET EXCEEDED.\x1b[0m " << endl;
                                cout << endl;
                                turnResult = -1;
                            }
                        }

                        if (newGame.getTurn()== 2){ //Computer's Turn
                            sleep(1);
                            cout << "\x1b[31mUSSR TURN. WHAT ITEM?:  \x1b[0m ";
                            cout <<endl;

                            //call function to generate a selection for the Computer
                            computerSelection = newGame.generateSelection();
                            sleep(1);
                            cout << "\x1b[31mUSSR SELECTED: \x1b[0m" << computerSelection + 1 << endl;
                            sleep(1);
                            cout <<endl;

                            //take turn
                            if (newGame.takeTurn(computerSelection) < 0){
                                sleep(1);
                                cout << "\x1b[31mUSSR BUDGET EXCEEDED.\x1b[0m " << endl;
                                sleep(1);
                                cout << endl;
                                turnResult = -1;
                            }

                        }

                    }

                    // 6. Launch a conflict

                    //The first player to exhaust their budget launches the conflict
                    sleep(1);
                    cout << "\x1b[33m LAUNCHING GLOBAL CONFLICT IN\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;
                    cout << "\x1b[33m .............5.............\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;
                    cout << "\x1b[33m .............4.............\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;
                    cout << "\x1b[33m .............3.............\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;
                    cout << "\x1b[33m .............2.............\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;
                    cout << "\x1b[33m .............1.............\x1b[0m " << endl;
                    sleep(1);
                    cout << endl;
                    cout << endl;

                    newGame.beginConflict(); //start the Conflict
                }
        }

    // 7. Exit Game
    cout << endl;
    cout << endl;
    sleep(2);
    cout << "\x1b[31mGAME OVER.\x1b[0m " << endl;
    cout << endl;
    cout << endl;


} //end of main