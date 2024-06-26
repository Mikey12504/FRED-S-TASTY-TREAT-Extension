#ifndef MANAGER_H
#define MANAGER_H

#include "Balance.h"
#include "LinkedList.h"
#include "TwoDLinkedList.h"
#include <array>

#define EMPTY_SPACE " "
#define SEPARATOR "|"
// Representing the number of separators to display the meals and balance
#define SEPARATOR_NUM 2
#define MONEY_SYMBOL "$"
#define DENOM_LENGTH 7
// The extra padding of LINEs
#define EXCESS_LINE 4
#define LINE "-"
#define DEFAULT_QUANTITY_LENGTH 9
// This is for dynamically printing out the values of balance
#define DEFAULT_VALUE_LENGTH 6

// Indicators in the first line of file to determine the format of the file
#define UPDATE_FORMAT_CHECKING "#updateformat"
#define NEW_FORMAT_PARAM_NUM 5
#define DEFAULT_FORMAT_PARAM_NUM 4

class DataManager {
private:
  /*
    Read the default format
  */
  void readFormat (std::ifstream &mealFile); 
  /*
    Read the new format 
  */
  void readUpdateFormat (std::ifstream &mealFile);

  // Read the food file
  void processLine(const std::string &line, LinkedList *linkedlist, int expectedTokens);

  Node* createNode(const std::string &id, const std::string &name, const std::string &description, const std::string &priceStr);

  // Read the coin file 
  void processMoneyLine(const std::string &line);
public:
  /*
   * Read the money data file and meal data file into meals and balance
   * This method assumes mealFile and moneyFile are valid
   */
  TwoDLinkedList *meals;
  Balance *balance;
  // Hold the name of the files so we can save it
  std::string mealFile;
  std::string moneyFile;

  DataManager(std::string mealFileName, std::string moneyFileName);
  ~DataManager();

  /*
   * Save all data to data files
   */
  void save();
};

#endif // !MANAGER_H
