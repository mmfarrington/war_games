/* WarGame.h
 * Miriam Farrington
 * CIS 554-M401 Object Oriented Programming in C++
 * Syracuse University
 * HW #5 - Student-Selected Program
 * 2/16/2020
 * This program defines the public and private interfaces for the WarGame Class
*/

#include <string>
using std::string;

namespace special_functions { //New namespace to define generic helper functions separate from the class

    /*
     * Name: validateCin
     * Description: helper function to validate the cin data type
     * Return Type: void
     */
    void validateCin(int valToCheck);

} // end namespace declaration


class WarGame { //Start class definition

public:

    /*  -----   Public class constructor  -----     */

    WarGame() {   // Start Constructor body

        // loop through the game table arrays and initialize values to 0
        for (int i =0; i<7; i++)
         {
            setUS(US[i], 0);
            setUSSR(USSR[i],0);
            setCost(estCost[i],0);

        }
        //initialize string variables to blank
        string header = {""};
        string weaponTypeDesc = {""};

        //the US Player always starts first
        currentTurn = 1;

        //initialize the casualties for each side to 0
        setCasualties(ussrCasualties, 0);
        setCasualties(usCasualties,0);

        //setup and print the game board...
        WarGame::createGameBoard(); //each new Game object should automatically create a GameBoard

    }

    /*  -----   Public Class Functions -----     */

    /*
     * Name: takeTurn
     * Description: takes the player's input and sets the board, updates turn
     * Return Type: int: the random selection
     */
    int takeTurn(int playerSelection);


    /*
     * Name: generateSelection()
     * Input: the weapon choice made by either player
     * Description: generates a random weapon selection on behalf of the computer player
     * Return Type: int: (1) = success or (-1) = budget exceeded
     */
    int generateSelection();


    /*
     * Name: beginConflict()
     * Description: initiates a conflict and outcome while both sides have weapons left
     * Return Type: void
     */
    void beginConflict();

    /*  -----   Public Getter & Setter Functions -----     */

    int getUSBudget();
    int getUSSRBudget();
    int getTurn();

private:

    /*  -----    Private Data members  -----     */

    int US [7];
    int USSR [7];
    int estCost [7];
    string header[4];
    string weaponTypeDesc[7];

    int uSBudget;
    int uSSRBudget;
    int currentTurn;
    int ussrCasualties = 0;
    int usCasualties;


    /*  -----    Private class functions -----     */

    /*
     * Name: createGameBoard
     * Description: sets up a new game board by initializing array values
     * Return Type: void
     */
    void createGameBoard ();

    /*
    * Name: printGameBoard
    * Description: prints out the current game board value
    * Return Type: void
    */
    void printGameBoard ();

    /*
    * Name: attackTarget
    * Description: launches a randomized attack and records outcome
    * Return Type: Int attack outcome 1 = success, 0 = failure
    */
    int attackTarget();


    /*
     * Name: pickWeapon
     * Input: a reference the player's weapons inventory (array)
     * Description: selects a weapon from the player's inventory
     * Return Type: Int index of the selected weapon
     */
    int pickWeapon(int (&inventory)[7]);

    /*
     * Name: updateCasualties
     * Input: a reference the player's casualty count, additional casualty to add
     * Description: updates the player's casualty total
     * Return Type: void
     */
    void updateCasualties(int &casualties, int valToSet);

    /*  -----    Private Getter & Setters  -----     */

    int getUS (int weaponChoice);
    int getUSSR (int weaponChoice);
    int getCost (int weaponChoice);
    int getCasualties(int casualtyToGet);
    string getWeaponTypeDesc (int weaponChoice);

    void setUS(int &USInp, int USToSet);
    void setUSSR(int &USSRInp,int USSRToSet);
    void setCost(int &CostInp, int costToSet);
    void setHeader(string &headInp, string valToSet);
    void setWeaponTypeDesc(string &DescInp, string descToSet);
    void setBudget(int &budget, int budgetToSet);
    void setTurn(int &turnVal);
    void setCasualties(int &casualties, int valToSet);
};