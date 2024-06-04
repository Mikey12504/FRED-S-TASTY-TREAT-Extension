#include "DataManager.h"
#include "Coin.h"
#include "Helper.h"
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <vector>

void DataManager::processLine(const std::string &line, 
                LinkedList *linkedlist, int expectedTokens) {
    std::vector<std::string> tokens = {};
    std::vector<std::string> prices = {};
    Helper::splitString(line, tokens, "|");

    if (tokens.size() == static_cast<size_t>(expectedTokens) && tokens[1].size() <= NAMELEN &&
        tokens[2].size() <= DESCLEN && FoodItem::isValidIdFormat(tokens[0]) &&
        Price::isValidPrice(tokens[3]) && !this->meals->getById(tokens[0])) {

        Node *node = createNode(tokens[0], tokens[1], tokens[2], tokens[3]);
        linkedlist->append(node);
    }
}

Node* DataManager::createNode(const std::string &id, const std::string &name,
                 const std::string &description, const std::string &priceStr) {
    std::vector<std::string> prices = {};
    Helper::splitString(Helper::floatToString(std::stof(priceStr), 2), prices, ".");
    
    Price price = {static_cast<unsigned int>(std::stoi(prices[0])),
                   static_cast<unsigned int>(std::stoi(prices[1]))};

    FoodItem *item = new FoodItem(id, name, description, price);
    Node *node = new Node();
    node->data = item;

    return node;
}

void DataManager::processMoneyLine(const std::string &line) {
    std::vector<std::string> tokens = {};
    Helper::splitString(line, tokens, DELIM);

    if (tokens.size() == 2 && Helper::isNumber(tokens[0]) &&
        Helper::isNumber(tokens[1]) && Coin::isDenomination(tokens[0]) &&
        Helper::isValidInteger(tokens[1])) {
        Coin coin;
        coin.denom = Coin::intToDenomination(std::stoi(tokens[0]));
        coin.count = std::stoi(tokens[1]);
        this->balance->insert(coin);
    }
}

void DataManager::readFormat(std::ifstream &mealFile) {
    LinkedList *linkedlist = new LinkedList();
    this->meals->insert(linkedlist);
    std::string line;

    while (std::getline(mealFile, line)) {
        processLine(line, linkedlist, DEFAULT_FORMAT_PARAM_NUM);
    }
}

void DataManager::readUpdateFormat(std::ifstream &mealFile) {
    std::string line;

    while (std::getline(mealFile, line)) {
        std::vector<std::string> tokens = {};
        Helper::splitString(line, tokens, "|");

        if (tokens.size() == NEW_FORMAT_PARAM_NUM && tokens[1].size() <= NAMELEN &&
            tokens[2].size() <= DESCLEN && FoodItem::isValidIdFormat(tokens[0]) &&
            Price::isValidPrice(tokens[3]) && !this->meals->getById(tokens[0]) &&
            tokens[4].size() <= MAX_CAT_LEN && !tokens[4].empty()) {

            if (!this->meals->getByCat(tokens[4])) {
                LinkedList *newCat = new LinkedList();
                newCat->category = tokens[4];
                this->meals->insert(newCat);
            }

            Node *node = createNode(tokens[0], tokens[1], tokens[2], tokens[3]);
            this->meals->appendNode(tokens[4], node);
        }
    }
}

DataManager::DataManager(std::string mealFileName, std::string moneyFileName) {
    this->meals = new TwoDLinkedList();
    this->balance = new Balance();

    this->mealFile = mealFileName;
    this->moneyFile = moneyFileName;

    std::ifstream mealFile(mealFileName);
    std::ifstream moneyFile(moneyFileName);

    std::string line;
    if (std::getline(mealFile, line)) {
        if (line == UPDATE_FORMAT_CHECKING && !line.empty()) {
            this->readUpdateFormat(mealFile);
        } else if (!line.empty()) {
            this->readFormat(mealFile);
        }
    }

    while (std::getline(moneyFile, line)) {
        processMoneyLine(line);
    }

    mealFile.close();
    moneyFile.close();
}


// Save the file 
void DataManager::save() {
  std::ofstream mealFile(this->mealFile);
  std::ofstream coinFile(this->moneyFile);

  if (!mealFile.is_open()) {
      std::cerr << "Failed to open file: " << this->mealFile << std::endl;
      return;
  }

  std::string line;
  LinkedList* currentCat = this->meals->getFirst();
  if (currentCat != nullptr && !currentCat->category.empty()) {
    mealFile << UPDATE_FORMAT_CHECKING << "\n";
  }
  while (currentCat) {
    Node *current = currentCat->getFirst();
    while (current) {
      mealFile << current->data->id << SEPARATOR << current->data->name 
      << "|" << current->data->description << SEPARATOR 
      << Helper::floatToString(current->data->price.value(), 2);
      if (!currentCat->category.empty()) {
        mealFile << SEPARATOR << currentCat->category ;
      }
      mealFile << "\n";
      current = current->next;
    }
    // Move to the next category
    currentCat = currentCat->next;
  }

  // Save the coin file
  for (Coin coin: this->balance->balance) {
    coinFile << coin.denom << DELIM << coin.count << "\n";
  } 

  mealFile.close();
  coinFile.close();
};

DataManager::~DataManager() {
  delete this->meals;
  delete this->balance;
}