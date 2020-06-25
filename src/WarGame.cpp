/* WarGame.cpp
 * Miriam Farrington
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 * HW #5 - Student-Selected Program
 * 2/16/2020
 * This program contains the implementation of the class methods defined in the WarGame.h header file
*/

#include "WarGame.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <zconf.h>


using std::string;
using std::setw;
using std::cout;
using std::cin;
using std::endl;

using namespace special_functions; //importing the special_functions namespace

/*
* Name: validateCin
* Description: helper function to validate the cin data type
* Return Type: void
*/

void special_functions::validateCin(int valToCheck) {

    while (cin.fail()) {
        // clear error state
        cin.clear();
        // discard 'bad' character(s)
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\x1b[31mINVALID ENTRY. TRY AGAIN. \x1b[0m";
        cin >> valToCheck; //
    }
}


/*  -----    Public class functions -----     */

    /*
    * Name: takeTurn
    * Description: takes the player's input and sets the board, updates turn
    * Return Type: int: (1) = success or (-1) = budget exceeded
    */

int WarGame::takeTurn(int playerSelection){

    if (currentTurn == 1) {  // US Player - User

        //set the value of the item selected
        setUS(US[playerSelection],1);

        //calculate the budget based on the weapon selected
        int newBudget = getUSBudget() - getCost(playerSelection);
        if (newBudget >= 0)
        {
            setBudget(uSBudget, newBudget);
        } else if (newBudget < 0) {

            return -1; //budget exceeded!
        }

        //change turns
        setTurn(currentTurn);
    }

    else if (currentTurn == 2) {  //USSR Player - Computer

        //set the value of the item selected
        setUSSR(USSR[playerSelection],1);

        //calculate the budget based on the weapon selected
        int newBudget = getUSSRBudget() - getCost(playerSelection);

        if (newBudget >= 0) {
            setBudget(uSSRBudget, newBudget);
        } else if (newBudget < 0) {

            return -1; //budget exceeded!
        }

        //change turns
        setTurn(currentTurn);

        //after both turns are complete, print out the game board reflecting the player selections
        printGameBoard();
    }

    return 1; //success
}

    /*
    * Name: generateSelection()
    * Input: the weapon choice made by either player
    * Description: generates a random weapon selection on behalf of the computer player
    * Return Type: int: (1) = success or (-1) = budget exceeded
    */

int WarGame::generateSelection(){
    srand(time(NULL)); //setting random seed
    int randSelect = rand() % 6; //random value between 0 and 6
    return randSelect;
}

    /*
     * Name: beginConflict()
     * Description: initiates a conflict and outcome while both sides have weapons left
     * Return Type: void
     */

void WarGame::beginConflict(){
    srand(time(NULL)); //setting random seed
    int inventoryUS = 0;
    int inventoryUSSR = 0;

    while (inventoryUS >= 0 && inventoryUSSR >= 0) { //continue attacks while both sides have weapons
        int outcome = (rand() % 1000); //random number to determine casualties

        if (getTurn() == 1) { //US Turn
            int usWeapon = pickWeapon(US);
            if (usWeapon >= 0) {
                cout << "\x1b[33mUS ATTACKS USING:  \x1b[0m" << getWeaponTypeDesc(usWeapon) << endl;
                if (attackTarget() == 0) { //unsuccessful attack
                        sleep(1);
                        cout << "ATTACK UNSUCCESSFUL." << endl;
                        cout << endl;
                        cout << endl;
                        sleep(1);
                    } else {
                        updateCasualties(ussrCasualties, outcome); //generate the casualties
                        sleep(1);
                        cout << "ATTACK SUCCESSFUL. USSR CASUALTIES: " << outcome << endl;
                        cout << endl;
                        cout << endl;
                        sleep(1);
                    }
                } else {
                    inventoryUS = -1;
                    sleep(1);
                    cout << "\x1b[31mNO WEAPONS. US CANNOT ATTACK.\x1b[0m" << endl;
                    cout << endl;
                    cout << endl;
                    sleep(1);
                }

                    setTurn(currentTurn); //flip the turn
            }
         if (getTurn() == 2){ // USSR Turn
                int ussrWeapon = pickWeapon(USSR);
                if (ussrWeapon >= 0) {
                    cout << "\x1b[31mUSSR ATTACKS USING:  \x1b[0m" << getWeaponTypeDesc(ussrWeapon) << endl;
                    if (attackTarget() == 0) { //unsuccessful attack
                        sleep(1);
                        cout << "ATTACK UNSUCCESSFUL." << endl;
                        cout << endl;
                        cout << endl;
                        sleep(1);
                    } else {
                        updateCasualties(usCasualties, outcome); //generate the casualties
                        sleep(1);
                        cout << "ATTACK SUCCESSFUL. US CASUALTIES: " << outcome << endl;
                        cout << endl;
                        cout << endl;
                        sleep(1);
                    }
                } else {
                    inventoryUSSR = -1;
                    sleep(1);
                    cout << "\x1b[31mNO WEAPONS. USSR CANNOT ATTACK.\x1b[0m" << endl;
                    cout << endl;
                    cout << endl;
                    sleep(1);
                }

                setTurn(currentTurn); //flip the turn
            }

    }  //end while loop

    //Conflict ends as one side has run out of weapons.
    sleep(1);
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "CONFLICT ENDED, CALCULATING RESULTS .... " << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    sleep(1);

    //Once both sides' weapons are exhausted, calculate casualties and determine outcome
    int totalUS = getCasualties(1);  //1 = US
    int totalUSSR = getCasualties(2); //2 = USSR

    cout << "\x1b[34mTOTAL CASUALTIES: US - \x1b[0m" << totalUS << " \x1b[34mUSSR - \x1b[0m" << totalUSSR << endl;
    sleep(1);

    if (totalUS > totalUSSR) {

        cout << "\x1b[34mWINNER = US\x1b[0m" << endl;
    }

    if (totalUSSR > totalUS){

        cout << "\x1b[34mWINNER = USSR\x1b[0m" << endl;
    }

    if (totalUSSR == totalUS){

        cout << "\x1b[34mSTALEMATE. WINNER = NONE\x1b[0m" << endl;
    }

}

/*  -----    Public getter & setter functions -----     */

int WarGame::getUSBudget(){

    return uSBudget;
}

int WarGame::getUSSRBudget(){

    return uSSRBudget;
}

int WarGame::getTurn(){
    return currentTurn; //return the first turn value
}

/*  -----    Private class functions -----     */

    /*
    * Name: createGameBoard
    * Description: sets up a new game board by initializing array values
    * Return Type: void
    */
void WarGame::createGameBoard() {

    //set the board game headers
    setHeader(header[0], "US");
    setHeader(header[1], "USSR");
    setHeader(header[2], "EST COST");
    setHeader(header[3], "DESCRIPTION");

    // set the description for each of the weapons
    setWeaponTypeDesc(weaponTypeDesc[0],"1. BALISTIC SUBMARINES");
    setWeaponTypeDesc(weaponTypeDesc[1],"2. ICBMS");
    setWeaponTypeDesc(weaponTypeDesc[2],"3. CRUISE MISSILES");
    setWeaponTypeDesc(weaponTypeDesc[3],"4. BOMBERS");
    setWeaponTypeDesc(weaponTypeDesc[4],"5. AIRBORNE HQ");
    setWeaponTypeDesc(weaponTypeDesc[5],"6. UNDERGROUND HQ");
    setWeaponTypeDesc(weaponTypeDesc[6],"7. AIR DEFENSE");

    //set the costs for each weapon
    setCost(estCost[0],3720);
    setCost(estCost[1],200);
    setCost(estCost[2],2);
    setCost(estCost[3],300);
    setCost(estCost[4],100);
    setCost(estCost[5],500);
    setCost(estCost[6],160);

    //Set the military budget for each side
    setBudget(uSBudget, 16320); //16320
    setBudget(uSSRBudget, 16320); //16320

    WarGame::printGameBoard(); //Finally call helper function to print out the starting game board to the console

}


    /*
    * Name: printGameBoard
    * Description: prints out the current game board value
    * Return Type: void
    */
void WarGame::printGameBoard (){

        //Format the array output as a table
        cout <<header[0] << setw(10) << header[1] << setw(13) << header[2] << setw(20) << header[3] << endl;
        cout <<endl;

        for (size_t i=0; i < 7; i++){
            cout << setw(1) << US[i] << setw(10) << USSR[i] << setw(11) << estCost[i] << setw(30) << weaponTypeDesc[i] << endl;
        }

        cout << endl;

        //Game board should display the current budget for each side
        cout << "\x1b[31mUS MILITARY BUDGET (IN MILLIONS OF DOLLARS): \x1b[0m" << getUSBudget() << endl;
        cout << "\x1b[31mUSSR MILITARY BUDGET (IN MILLIONS OF RUBLES): \x1b[0m" << getUSSRBudget() << endl;
        cout << endl;
}

 /*
  * Name: attackTarget
  * Description: launches a randomized attack and records outcome
  * Return Type: Int attack outcome 1 = success, 0 = failure
  */

int WarGame::attackTarget(){
    int attackPick = rand() % 100000; //generate a random number 0 and 100000
    int attackResult = -1; //result to return - success or fail

    if (attackPick % 2 == 0 ) {
        attackResult = 1;
    } else {
        attackResult = 0;
    }

    return attackResult;
}


    /*
     * Name: pickWeapon
     * Input: a reference the player's weapons inventory (array)
     * Description: selects a weapon from the player's inventory
     * Return Type: Int index of the selected weapon
     */

int WarGame::pickWeapon(int (&inventory)[7]) {
        for (int i = 0; i < 7; i++) { //loop through weapon inventory, select an available weapon
            if (inventory[i] > 0){
                inventory[i] = inventory[i] - 1; //reduce the weapon inventory by 1
                return i; //return the index of the selected weapon
            }
        }
    return -1; //return -1 if there are no weapons left in the inventory
}


/*
    * Name: updateCasualties
    * Input: a reference the player's casualty count, additional casualty to add
    * Description: updates the player's casualty total
    * Return Type: void
    */
void WarGame::updateCasualties(int &casualties, int valToSet){

    casualties = casualties + valToSet; //add to total casualties
}


/*  -----    Private Getter & Setters  -----     */

int WarGame::getUS (int weaponChoice){

    return US[weaponChoice];
}

int WarGame::getUSSR (int weaponChoice){

    return USSR[weaponChoice];
}

int WarGame::getCost (int weaponChoice){

    return estCost[weaponChoice];
}

string WarGame::getWeaponTypeDesc (int weaponChoice){

    return weaponTypeDesc[weaponChoice];
}

int WarGame::getCasualties(int casualtyToGet) {

    if (casualtyToGet == 1){
        return usCasualties;
    } else if (casualtyToGet==2){
        return ussrCasualties;
    }
}

void WarGame::setUS(int &USInp, int USToSet){
    //check whether value should be set based on index or input
    if (USToSet > 0) {
        int tmp = 0;
        tmp = USInp + 1;
        USInp = tmp;
    } else {
        USInp = USToSet;
    }
}
void WarGame::setUSSR(int &USSRInp, int USSRToSet){
    //check whether value should be set based on index or input
    if (USSRToSet > 0) {
        int tmp = 0;
        tmp = USSRInp + 1;
        USSRInp = tmp;
    } else {
        USSRInp = USSRToSet;
    }
}
void WarGame::setCost(int &CostInp, int costToSet){

    CostInp = costToSet;
}
void WarGame::setWeaponTypeDesc(string &DescInp, string descToSet){

    DescInp = descToSet;
}

void WarGame::setBudget(int &budget, int budgetToSet){

    budget = budgetToSet;
}

void WarGame::setHeader(string &headInp, string valToSet){

    headInp = valToSet;
}

void WarGame::setCasualties(int &casualties, int valToSet){

    casualties = valToSet;
}

void WarGame::setTurn(int &turnVal){

    //Turns will flip between 1 (user) and 2(computer)
    //The Player always gets to start first.

    if (turnVal == 1) {
        currentTurn += 1;
    } else if (turnVal == 2){
        currentTurn -= 1;
    }
}
