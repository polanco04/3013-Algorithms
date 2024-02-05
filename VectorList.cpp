/**
*  Author:           Carlos Polanco
*  Email:            cpolancoguil0828@my.msutexas.edu
*  Label:            P01
*  Title:            Vector Class
*  Course:           CMPS 3013
*  Semester:         Spring 2024
* 
*  Description:
*        This program implements a class whose purpose is to use a linked list
*        as a vector. It has the typical methods of a linked list used to 
*        add(push) and remove(pop) items. It can add values to the front, 
*        middle and rear of the list. Same with removing values. Values can be
*        removed from the front, middle and rear. Values can be entered in at 
*        a specific location(index) in the list and values can be removed from 
*        a certain location. 
*        
*  Usage: 
*        
*       
*  Files:            
*       VectorList.cpp   : driver program. Includes everything that is needed.
                          no separate files for list.
 */

#include <iostream>
#include <vector>
#include <fstream>

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;


/**
 * Node
 * 
 * Description:
 *        This struct is used to create nodes to use in the linked list.
 * 
 * Methods:
 *        Constructor         Node(int)
 *        
 * Usage:
 *        Node n(8);                        // creates instance of a node with
 *                                          // the value 8 inside            
 */
struct Node
{
    int value;             // number stored in the node
    Node* next;            // pointer to the next node
    Node* prev;            // pointer to the previous node

    Node(int val)
    {
      value = val;         // value equals the number passed
      next = nullptr;      // next and prev are set to null when created
      prev = nullptr;
    }

};

/**
 * Vector List
 * 
 * Description:
 *       This class implements a doubly linked list to store integers. 
 *       Values can be added to the front, middle or rear. They can also
 *       be added to a specific location. Same goes with removing values.
 * 
 * Public Methods:
 *                                 VectorList();
 *                                 VectorList(string);
 *                                 VectorList(int*, int);
 *                                 VectorList(VectorList&);
 *      void                       sortAscending();
 *      void                       sortDescending();
 *      void                       pushFront(int);
 *      void                       pushFront(VectorList&);
 *      void                       pushRear(int);
 *      void                       pushRear(VectorList&);
 *      void                       pushLocation(int, int);
 *      void                       pushInOrder(int);
 *      int                        popFront();
 *      int                        popRear();
 *      int                        popFrom(int);
 *      int                        findVal(int);
 *      void                       print();
 *
 *  Usage:
 *      v.VectorList();                     // creates instance of VectorList
 *      
 *      v.VectorList(filename);             // creates instance of Vector List 
 *                                          // with values read from a file
 *      
 *      v.VectorList(a, 6);                 // Creates instance of VectorList 
 *                                          // with values read from array a
 *                                          // with size 6.
 *      
 *      v.VectorList(VList);                // Creates instance of VectorList
 *                                          // with values from VList
 *                                          // which is another instance 
 *      
 *      v.pushFront(7);                     // Adds 7 to front of List
 *      
 *      v.pushFront(VList);                 // Adds VList to front of List
 *      
 *      v.pushRear(8);                      // Adds 8 to rear of list
 *      
 *      v.pushRear(VList);                  // Adds Vlist to rear of list
 *      
 *      v.pushLocation(3, 7);               // Adds 7 to position 3 of List
 *      
 *      v.pushInOrder(4);                   // Adds 4 to list where its
 *                                          // supposed to go depending on 
 *                                          // order of list
 *      
 *      v.sortAscending();                  // sorts list in ascending order
 *     
 *      v.sortDescending();                 //sorts list in descending order
 *      
 *      v.popFront();                       // removes value from front of
 *                                          // list
 *      
 *      v.popRear();                        // removes value from rear of
 *                                          // list
 *      
 *      v.popFrom(4);                       // removes value from index 4 of
 *                                          // list
 *      
 *      v.findVal(7);                       // finds 7 in the list. 
 *      
 *      v.print(outfile);                   // prints out the list to terminal
 *                                          // and output file
 *
 */
class VectorList
{
   private:
   Node* front;     // pointer to the front of the list
   Node* rear;      // pointer to the rear of the list
   
   public:
   VectorList();
   VectorList(string);
   VectorList(int*, int);
   VectorList(VectorList&);
   void sortAscending();
   void sortDescending();
   void pushFront(int);
   void pushFront(VectorList&);
   void pushRear(int);
   void pushRear(VectorList&);
   void pushLocation(int, int);
   void pushInOrder(int);
   int popFront();
   int popRear();
   int popFrom(int);
   int findVal(int);
   void print(ofstream&);

};
/** Public : VectorList
 * 
 * Description:
 *          Default constructor. Creates instance of VectorList.
 * 
 * Params:
 *       
   none
 * 
 * Returns:
 *         nothing. Creates instance of the class.
 */
VectorList::VectorList()
{
  front = rear = nullptr;   // front and rear set to null when created
}

/**
 * Public : VectorList
 * 
 * Description:
 *         constructor. Creates instance of VectorList.
 * 
 * Params:
 *        string         :   input file
 * 
 * Returns:
 *         "nothing." Creates instance of the class with values read
 *          from the file.
 */
VectorList::VectorList(string fileName)
{
  int value;                   // value to be read from the file
  ifstream infile;             // variable used for input file
  
  infile.open(fileName);       // opens input file

  while (infile >> value)      // reads until eof
  {
     pushRear(value);          // adds value read from file to the list
  }

  infile.close();              // closes input file
}

/**
 * Public : VectorList
 * 
 * Description:
 *          constructor. Creates instance of VectorList.
 * 
 * Params:
 *         VectorList       :  instance of the same class
 * 
 * Returns:
 *         "nothing." Creates instance of the class with the values from
 *          the other class.
 */
VectorList::VectorList(VectorList& other)
{
  front = rear = nullptr;         // front and rear set to null when created
  Node* travel = other.front;     // Node created to traverse the list

  while(travel)
  {
    pushRear(travel->value);      // adds number to the list
    travel = travel->next;        // moves to the next node in the list
  }
}

/**
 * Public : VectorList
 * 
 * Description:
 *         constructor. Creates instance of VectorList.
 * 
 * Params:
 *         int*           :   array of integers
 *         int            :   array size
 * 
 * Returns:
 *         "nothing." Creates instance of the class with values
 *          from the array that is passed.
 */
VectorList::VectorList(int*arr, int size)
{
  front = rear = nullptr;         // front and rear set to null when created

  for(int i=0; i<size; i++)
  {
    pushRear(arr[i]);             // adds numbers from the array to the list
  }
}

/** Public : sortAscending
 * 
 * Description:
 *          Uses bubble sort to sort the list in ascending order.
 * 
 * Params:
 *       
   none
 * 
 * Returns:
 *         "nothing." Sorts the list.
 */
void VectorList::sortAscending()
{
  // print out message if list is empty or only has one element
  if(!front)
  {
    cout << "List is empty or only has 1 element. No need to sort" << endl;
  }

  bool swapped;
  Node* travel = front;

  // do while loop so that it does the comparisons at least once
  // then continue if elements were swapped. If no elements were swapped
  // then stop and no sorting was needed.
  do{
    swapped = false;
    travel = front;

    while (travel->next)
    {
      if(travel->value > travel->next->value)
      {
       int temp = travel->value;
       travel->value = travel->next->value;
       travel->next->value = temp;
       swapped = true;
      }
      travel = travel->next;
    }
  }while(swapped);
}

/** Public : sortDescending
 * 
 * Description:
 *          Uses bubble sort to sort the list in descending order.
 * 
 * Params:
 *       
   none
 * 
 * Returns:
 *         "nothing." Sorts the list.
 */
void VectorList::sortDescending()
{
  if(!front)
  {
    cout << "List is empty or only has 1 element. No need to sort" << endl;
  }

  bool swapped;
  Node* travel = rear;

  // do while loop so that it does the comparisons at least once
  // then continue if elements were swapped. If no elements were swapped
  // then stop and no sorting was needed.
  do{
    swapped = false;
    travel = rear;

    while (travel->prev)
    {
      if(travel->value > travel->prev->value)
      {
       int temp = travel->value;
       travel->value = travel->prev->value;
       travel->prev->value = temp;       
       swapped = true;
      }
      travel = travel->prev;
    }
  }while(swapped);
}

/**
 * Public : pushFront
 * 
 * Description:
 *         Adds value to the front of the List
 * 
 * Params:
 *         int           :  number to add to List
 * 
 * Returns:
 *         "nothing." Adds the number to the List 
 */
void VectorList::pushFront(int fVal)
{
  Node* newNode = new Node(fVal);     // new node to be added

  // sets front and rear to new node
  // if the list is empty
  if(!front)
  {
    front = rear = newNode;    
    return;
  }

  newNode->next = front;              // moves pointers around to add 
                                      // the new node to the front
  front->prev = newNode;
  front = newNode;
}

/**
 * Public : pushFront
 * 
 * Description:
 *         Adds another List to the front of the List
 * 
 * Params:
 *         VectorList           :  Instance of same class
 * 
 * Returns:
 *         "nothing." Adds the other list to the List 
 */
void VectorList::pushFront(VectorList& other)
{
  Node* travel = other.rear;      // Node created to traverse the list

  while(travel)
  {
    pushFront(travel->value);     // adds number to the front of list
    travel = travel->prev;        // moves to previous node
  }
}

/**
 * Public : pushRear
 * 
 * Description:
 *         Adds value to the rear of the List
 * 
 * Params:
 *         int           :  number to add to List
 * 
 * Returns:
 *         "nothing." Adds the number to the List 
 */
void VectorList::pushRear(int rVal)
{
  Node* newNode = new Node(rVal);    // new node to be added

  // sets front and rear to new node
  // if the list is empty
  if(!front)
  {
    front = rear = newNode;          
    return;
  }
  
  newNode->prev = rear;              // moves pointers around to add 
                                     // the new node to the rear
  rear->next = newNode;
  rear = newNode;
  
}

/**
 * Public : pushRear
 * 
 * Description:
 *         Adds value to the rear of the List
 * 
 * Params:
 *         VectorList          :  instance of same class
 * 
 * Returns:
 *         "nothing." Adds the other list to the List 
 */
void VectorList::pushRear(VectorList& other)
{
  Node* travel = other.front;   // Node created to traverse the list
  while(travel)
  {
    pushRear(travel->value);    // adds number to the rear of the list
    travel = travel->next;      // moves to next node
  }
}

/**
 * Public : pushLocation
 * 
 * Description:
 *          Adds value to a specific location on the List
 * 
 * Params:
 *          int           :       desired index
 *          int           :       number to add to list
 * 
 * Returns:
 *         "nothing." Adds the number to the List 
 */
void VectorList::pushLocation(int index, int value)
{
   int position = 0;                         // int to keep track of index
   Node* travel = front;                     // node used to traverse list
   Node* newNode = new Node(value);          // node to be added
 
   while(travel)
   {
    // add node to specific location
    if(position == index)
    {
       if(!travel->prev)
       {
         pushFront(value);
       }

       else
       {
         travel->prev->next = newNode;
         newNode->next = travel;
         newNode->prev = travel->prev;
       }
       return;
    }

    // print a message if trying to add outside the list
    if(position != index && !travel->next)
    {
      cout<< "Cannot add a value outside the range of the list." << endl;
      return;
    }
     travel = travel->next;
     position++;
   }
}

/**
 * Public : pushInOrder
 * 
 * Description:
 *         Adds value to a specific location on the List depending
 *         on the order
 * 
 * Params:
 *         int          :  number to be added to the list
 * 
 * Returns:
 *          "nothing." Adds number to the list.
 */
void VectorList::pushInOrder(int oVal)
{
   Node* travel = front;
   Node* newNode = new Node(oVal);

  // sets front and rear to new node
  // if the list is empty
  if(!front)
  {
    front = rear = newNode;    
    return;
  }
  
  // find spot to add newNode if list is in ascending order
  if(rear->value > front->value)
  {
    while(travel && newNode->value >= travel->value)
    {
      travel = travel->next;
    }
   // if the node is to go at the rear, add it to the rear
    if(!travel)
    {
      pushRear(newNode->value);
    }
    // if the node is to go at the front, add it to the front
    else if (!travel->prev)
    {
      pushFront(newNode->value);
    }
    else
    {
     travel->prev->next = newNode;
     newNode->next = travel;
     newNode->prev = travel->prev;
    }
  }
  
  // find spot to add newNode if list is in ascending order
  else if(front->value > rear->value)
  {
    while(travel && newNode->value <= travel->value)
    {
      travel = travel->next;
    }
    if(!travel)
    {
      pushRear(newNode->value);
    }
    else if (!travel->prev)
    {
      pushFront(newNode->value);
    }
    else
    {
    travel->prev->next = newNode;
    newNode->next = travel;
    newNode->prev = travel->prev;
    }
  }
}

/**
 * Public : popFront
 * 
 * Description:
 *          removes value from the front of the List
 * 
 * Params:
 *        none
 * 
 * Returns:
 *         number removed from the list
 */
int VectorList::popFront()
{
  // print a message if the list is empty and return -1
   if(!front)
   {
    cout << "Cannot pop due to list being empty" << endl;
    return -1;
   }
   
   int pValue = front->value;         // number to be removed
   Node* popVal = front;              // node to be removed
   front = front->next;               
  
   if(front)
   {
    front->prev = nullptr;
   }
   else
   {
    rear = nullptr;
   }
   
   delete popVal;
   return pValue;
}

/**
 * Public : popRear
 * 
 * Description:
 *          removes value from the rear of the List
 * 
 * Params:
 *        none
 * 
 * Returns:
 *         number removed from the list
 */
int VectorList::popRear()
{  
  // print a message if the list is empty and return -1
   if(!front)
   {
    cout << "Cannot pop due to list being empty" << endl;
    return -1;
   }

   int pValue = rear->value;         // number to be removed
   Node* popVal = rear;              // node to be removed
   rear = rear->prev;

   if(rear)
   {
    rear->next = nullptr;
   }
   else
   {
    front = nullptr;
   }
   
   delete popVal;
   return pValue;
}

/**
 * Public : popFrom
 * 
 * Description:
 *          removes value from a specific location in the list
 * 
 * Params:
 *        int         :      desired index
 * 
 * Returns:
 *         number removed from the list
 */
int VectorList::popFrom(int index)
{
  // print a message if the list is empty and return -1
   if(!front)
   {
    cout << "Cannot pop due to list being empty" << endl;
    return -1;
   }

   int position = 0, pValue;            // int to keep track of index
                                        //pValue is the value to be popped
   Node* popTravel = front;

  while(popTravel)
  {
    if(position == index)
    {
      // popFront if the index indicates the frist element
      if(!popTravel->prev)
      {
        pValue = popTravel->value;
        popFront();
      }
      // popRear if the index indicates the last element
      else if(!popTravel->next)
      {
        pValue = popTravel->value;
        popRear();
      }
      //pop from the middle if the index is neither front or rear
      else
      {
         pValue = popTravel->value;
         popTravel->prev->next = popTravel->next;
         popTravel->next->prev = popTravel->prev;
         delete popTravel;
      }
       return pValue;
    }
    
    // print message if item is not found in the list
    if(position != index && !popTravel->next)
    {
      cout << "Item not found in list. Cannot remove non-existent "
              <<"values" << endl;
      return -1;
    }
    
    popTravel = popTravel->next;
    position++;
  }
  return -1;
}

/**
 * Public : findVal
 * 
 * Description:
 *          finds the position of the number that is passed.
 *          If its not found then it returns -1.
 * 
 * Params:
 *        int         :      number to be found
 * 
 * Returns:
 *         index of number if found, -1 if not found
 */
int VectorList::findVal(int fVal)
{
  int index = 0;
  Node* travel = front;

  while(travel)
  {
    // return the index if the value is found
    if(travel->value == fVal)
    {
      return index;
    }
   
   // print message if item is not found in list
    if(travel->value != fVal && !travel->next)
    {
      cout << "Item not found in list."<< endl;
      return -1;
    }

    travel = travel->next;
    index++;

  }
  return -1;
}

/**
 * Public : print
 * 
 * Description:
 *          prints the list to the screen
 * 
 * Params:
 *         output file
 * 
 * Returns:
 *         nothing. prints the list.
 */
void VectorList::print(ofstream& outfile)
{
  // print message if list is empty
  if(!front)
  {
    cout << "Empty List " << endl;
    outfile << "Empty List " << endl;
  }
  
  // print out the list
  else
  {
    Node *travel = front;
  cout << "[";
  outfile << "[";
    while(travel){
      cout<<travel->value<<" ";
      outfile << travel->value << " ";
      travel = travel->next;
    } 
  cout <<"]" << endl;
  outfile << "]" << endl;
  }
}

int main()
{
   ofstream outfile;
   outfile.open("test.out");

   //Tests with v1
    VectorList v1;
    v1.pushRear(2);
    v1.pushFront(4);
    v1.pushRear(6);
    v1.pushFront(8);
    v1.pushFront(10);
    cout << "v1: ";
    outfile << "v1: ";
    v1.print(outfile);
    
    v1.sortAscending();
    cout << "v1 after ascending sort: ";
    outfile << "v1 after ascending sort: ";
    v1.print(outfile);
    
    v1.sortDescending();
    cout << "v1 after descending sort: ";
    outfile << "v1 after descending sort: ";
    v1.print(outfile);
    
    v1.pushInOrder(1);
    v1.pushInOrder(11);
    cout << "v1 after in order push: ";
    outfile << "v1 after in order push: ";
    v1.print(outfile);
    
    v1.popFront();
    cout << "v1 after pop front: ";
    outfile << "v1 after pop front: ";
    v1.print(outfile);
    
    v1.popRear();
    cout << "v1 after pop rear: ";
    outfile << "v1 after pop rear: ";
    v1.print(outfile);
    
    v1.popFrom(1);
    cout << "v1 after pop from: ";
    outfile << "v1 after pop from: ";
    v1.print(outfile);
    outfile << endl;
    cout << endl;
    
    //tests with v2
    VectorList v2;
    v2.pushFront(1);
    v2.pushFront(3);
    v2.pushRear(5);
    v2.pushFront(7);
    v2.pushRear(9);
    cout << "v2: ";
    outfile << "v2: ";
    v2.print(outfile);
    
    int w = v2.popFrom(4);
    cout << "v2 after pop from: ";
    outfile << "v2 after pop from: ";
    v2.print(outfile);
    cout << "popped value: " << w << endl;
    outfile << "popped value: " << w << endl;

    v2.pushFront(v1);
    v2.pushLocation(7, 12);
    cout << "v2 after pushing v1 to the front and pushing at location: ";
    outfile << "v2 after pushing v1 to the front and pushing at location: ";
    v2.print(outfile);
    int x = v2.findVal(12);
    cout << "Location of value looked for: " << x << "\n\n";
    outfile << "Location of value looked for: " << x << "\n\n";

    //Tests with v3
    VectorList v3;
    cout << "v3: ";
    outfile << "v3: ";
    v3.print(outfile);

    v3.pushInOrder(9);
    cout << "v3 after in order push: ";
    outfile << "v3 after in order push: ";
    v3.print(outfile);
    cout << endl;
    outfile << endl;

    //tests with v4
    int A[] = {11,25,33,47,51};
    VectorList v4(A,5);
    cout << "v4: ";
    outfile << "v4: ";
    v4.print(outfile);
    cout << endl;
    outfile << endl;

    //tests with v5
    VectorList v5("input.dat");
    cout << "v5: ";
    outfile << "v5: ";
    v5.print(outfile);

    v5.pushRear(v3);
    cout << "v5 after pushing v3 to the rear: ";
    outfile << "v5 after pushing v3 to the rear: ";
    v5.print(outfile);

    v5.sortDescending();
    cout << "v5 after descending sort: ";
    outfile << "v5 after descending sort: ";
    v5.print(outfile);

    v5.sortAscending();
    cout << "v5 after ascending sort: ";
    outfile << "v5 after ascending sort: ";
    v5.print(outfile);
    
    outfile.close();
}