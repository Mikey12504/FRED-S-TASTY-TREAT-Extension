#ifndef MACHINE_H
#define MACHINE_H
#include "Balance.h"
#include "DataManager.h"
#include "LinkedList.h"
#include <string>

#define GREEN "\033[32m"
#define RED "\033[31m"
#define WHITE "\033[37m"

class Machine {
private:
  // A pointer to an object to handle reading / saving / containing data
  DataManager *data;

  // To toggle configurations
  bool useTwoDLinkedList;
  bool useColour;
  /*
   * Purchase a meal given an id
   */
  void purchaseMeal();

  /*
   * Add a new food item to the associated LinkedList member variable
   * Automatically generate item ID then prompts for details for item
   */
  void addFood();

  /*
   * Remove a food item given food ID
   */
  void removeFood();

  /*
   * Formatted display the balance
   */
  void displayBalance();

  /*
   * Formatted display all meals
   */
  void displayMeals();

  /*
   * Terminate program, all progam data will be lost and freeup memory
   */
  void abort();

  /*
   * Save all data to data files
   */
  void save();

public:
  // Initialize and destroy member variables
  Machine(std::string mealFile, std::string moneyFile, bool useTwoDLinkedList,
          bool useColour);
  ~Machine();

  /*
   * This is the main menu, displaying 9 options
   * This method should be able to call other methods in this class
   * Imagine menu is the main while loop, while other methods in this class in
   * smaller while loops encompassed by this main loop
   */
  void start();
};

#endif // MACHINE_H