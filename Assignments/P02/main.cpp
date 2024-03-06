/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it
 * lets you decide what to do based on what character you are pressing.
 *
 * You can test which characters are being pressed using their ascii values.
 *
 * An ascii table here should be helpful
 *      http://www.asciitable.com/
 *
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between
 *                            the two (in this context).
 *
 * Code below is a basic example of using a "getch" function along with
 * searching an array of words for partial matches.
 *
 * https://repl.it/@rugbyprof/getchexample#main.cpp

 rang only depends on C++ standard library, unistd.h system header on unix and
 windows.h & io.h system headers on windows based systems. In other words, you
 don't need any 3rd party dependencies.
 */

 /**
  this is a slightly modified version of the program described above. It uses
  getch, but instead of reading from a text file, it reads from a json file.
  This program finds words on a json filed called dictionary, and is able to 
  print out the definition of such words. The user is given the option to see
  the definition of the word they typed by pressing enter or typing a 
  colon. Depends on the situation. 

  the original code without the slight modifications made by me, can be found
  here:
        https://replit.com/@rugbyprof/3013-P02-Starter?v=1#main.cpp

 */

#include "./headers/animals.hpp"
#include "./headers/console.hpp"
#include "./headers/json.hpp"
#include "./headers/rang.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;
using namespace rang;
using json = nlohmann::json;

consoleSize console_size; // used to store the size of console (width=cols and
                          // height=rows)

/**
 * partialMatch
 *
 * Description:
 *      Finds partial matches in an array of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      vector<string>  array       - array to search
 *      string          substring   - substring to search for in each word
 *
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> partialMatch(json array, string substring) {
  vector<string> matches; // to hold any matches
  size_t found;           // size_t is an integer position of
                          // found item. -1 if its not found.
  int i = 0;

for (auto &element : array.items()) 
{
        string key = element.key();
        
        if (substring.size() == 0) {
           return matches;
         }
        // Check if the key contains the partialKey substring
        if (key.find(substring) != string::npos) {
            // Found a match, do something with it
            if((key > substring || key == substring) && key[0] == substring[0])
            {
              matches.push_back(key);  
            } 
        }
}
  return matches;
}

/**
* Prints a long background row of gray, with text centered.
* Not a good function since colors are hard coded, but using
* rang, I don't want to invest the time to figuere out how to
* interact with rang's enumerated class types and ostream.
* I guess you could add a switch statement to change background
* color:
* switch(color){
  "black" : cout<<bgB::black;
            break;
  "red" : cout<<bgB::red;
          break;
  ...
  ...
  ...
}
But still not a good solution.
*/
void titleBar(string title, int length = console_size.width) {
  string padding = string((length / 2) - (title.size() / 2), ' ');
  title = padding + title + padding;
  cout << bgB::black << fg::gray << title << fg::reset << bg::reset << endl;
}

/**
 * horizontalBar
 *
 * Description:
 *      Prints a horizontal bar of a given length
 * Params:
 *      int length - length of the bar
 * Returns:
 *      void
 */
void horizontalBar(int length = console_size.width) {
  string line = string(length, '_');
  cout << fg::gray << line << fg::reset << bg::reset << endl;
}

/**
 * printMenu
 *
 * Description:
 *      Prints the menu to the screen.
 * Params:
 *      vector<string> options - vector of options
 * Returns:
 *      void
 */
void printMenu(vector<string> options) {
  int i = 1;
  for (auto s : options) {
    cout << fg::black << style::bold << i << ". " << style::reset << fg::cyan
         << s << fg::reset << bg::reset << endl;
    i++;
  }
  cout << fg::reset << bg::reset;
}

/**
 * printHighlightedSubstr
 *
 * Description:
 *      Given a word, print the substr underlined and red vs blue for the rest
 * of the word.
 * Params:
 *      string word - word to print
 *      string substr - substring to highlight in red
 *      int loc - location of substr in word
 * Returns:
 *      void
 */
void printHighlightedSubstr(string word, string substr, int loc) {
  for (int j = 0; j < word.size(); j++) {
    // if we are printing the substring turn it red
    if (j >= loc && j <= loc + substr.size() - 1) {
      cout << fg::red << style::underline << word[j] << fg::blue
           << style::reset;
    } else {
      cout << fg::blue << word[j] << fg::reset << style::reset;
    }
  }
}

/**
 * printCurrent
 *
 * Description:
 *      Prints the current key pressed and the current substr to the screen.
 * Params:
 *      char k - last character pressed.
 *      string word - current substring being printed.
 * Returns:
 *      void
 */
void printCurrent(char k, string word) {
  cout << fg::green << style::bold << "KeyPressed: \t\t" << style::reset
       << fgB::yellow;
  if (int(k) == 127) {
    cout << "del";
  } else if (int(k)== 10) {
    cout << "ent";
  }
  else
  {
    cout << k;
  }
  cout << " = " << (int)k << fg::reset << endl;
  cout << fg::green << style::bold << "Current Substr: \t" << fg::reset
       << fgB::blue << word << fg::reset << style::reset << endl;
  cout << endl;
}

/**
 * errorMessage
 *
 * Description:
 *      Prints an error message to the screen.
 * Params:
 *      string message - message to print
 * Returns:
 *      void
 */
void errorMessage(string message) {
  cout << bgB::red << fgB::gray << message << fg::reset << bg::reset << endl;
  sleep(1);
}

int main() {
  console_size = getConsoleSize(); // get width and height of console
  char k;                          // holder for character being typed
  json jDictionary;    
  string filePath = "./data/dictionary.json";
  ifstream fileStream(filePath);
  string partialKey = " ";

  string key;                      // string version of char for printing
  string substr = "";              // var to concatenate letters to 
  vector<string> matches; // any matches found in vector of animals
  int loc;                // location of substring to change its color
  bool deleting = false;
  string str = "";
  vector<string> mainMenu;

  //Loads json object
  if (fileStream.is_open()) 
  {
    fileStream >> jDictionary;
    fileStream.close();
  } 
  else 
  {
    cerr << "Failed to open file: " << filePath << endl;
    return 1;
  }

  // print the menu for instructions on what to do
  mainMenu.push_back("Type letters or words to find them in the dictionary.");
  mainMenu.push_back(
      "Hit the DEL key to erase a letter from your search string.");
  mainMenu.push_back(
      "When a single word is found, hit enter to see it's definition.");
  mainMenu.push_back(
      "If you want to stop, type a capital z.");

  clearConsole();
  titleBar("Dictionary Lookup", console_size.width);
  printMenu(mainMenu);

  
  // While capital Z is not typed keep looping
  while ((k = getch()) != 'Z') {

    clearConsole();

    // Tests for a backspace and if pressed deletes
    // last letter from "substr".
    if ((int)k == 127) {
      if (substr.size() > 0) {
        substr = substr.substr(0, substr.size() - 1);
        deleting = true;
      }
    } else {
      deleting = false;

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value between 64 and 97 
      // is capital so we lower it.
      if ((int)k < 97 && (int)k > 64) {
       k += 32;
      }
      substr += k; // append char to substr
    }
    horizontalBar();
    printCurrent(k, substr);

    // Find any animals in the array that partially match
    // our substr word
    matches = partialMatch(jDictionary, substr);

    if ((int)k != 32) { // if k is not a space print it

      key = to_string(k);

      horizontalBar();

      cout << style::bold << style::underline << fg::black
           << "MATCHES: " << fg::green << matches.size() << style::reset
           << fg::reset << endl
           << endl;

      for (auto &c : substr)
        c = tolower(c);
      // This prints out all found matches
      for (int i = 0; i < matches.size(); i++) {
        // if i == 10, then break out the loop so it only prints 10 results.
        if(i == 10)
        {
          break;
        }
        // find the substring in the substr
        loc = matches[i].find(substr);
        // if its found
        if (loc != string::npos) {
          printHighlightedSubstr(matches[i], substr, loc);
        }
        cout << " ";

      }
      cout << fg::reset << endl << endl << endl << endl;
      
      //if something is typed
      if(matches.size() != 0)
      {
      // if the user types something and there is only one result, 
      // ask them if that is the word they are looking for
      // and tell them to press enter to see the definition of that word.
      // print the definition when they press enter.
      if (matches.size() == 1) {
        cout << "Is this the word you are looking for?"<< endl
             << "If so, press enter to see the definition." << "\n\n";
             if((k = getch()) == 10)
             {
               cout << "The definition of " << matches[0] << " is:" << endl;
               cout << jDictionary[matches[0]] << endl;
             }
      }
      // if there is more than one result and  the user wants to see the 
      // definition of the word/substring they typed, 
      // then ask them to type a colon to see the definition of that word.
      // print the definition when they type a colon.
      else{
        cout << "would you like to see the definition of the current word 
                 you typed?" << endl << "if so, type a colon (:)." 
                 << "\n\n";
        if((k = getch()) == 58)
             {
               cout << "The definition of " << matches[0] << " is:" << endl;
               cout << jDictionary[matches[0]] << endl;
             }
       } 
      }
    }
  }
   return 0;
}
