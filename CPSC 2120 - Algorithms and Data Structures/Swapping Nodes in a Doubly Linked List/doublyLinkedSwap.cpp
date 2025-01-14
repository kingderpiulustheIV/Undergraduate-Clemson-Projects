 /*
 * Name: Sean Farrell
 * Date Submitted: 9/26/2023
 * Lab Section: 6
 * Assignment Name: Swapping Nodes in a Doubly Linked List
 */
#include "doublyLinkedSwap.h"

// Implement the following function:
// p and afterp are pointers to the nodes to be swapped.
void swapWithNext(Node * p) {
	// Creates a temp node for the double linked list
	
	struct Node * temp = p -> next;
	
	// Exectues the following code if p and the temp value does not equal zero or if temp is not a null pointer
	
	if (temp != nullptr && p-> value != 0 && temp-> value != 0) {
		
		// Creates a node that is infront and behind the node p in the double linked list.
		
		Node *before = p -> prev;
		Node *after = temp -> next;
		
		// Switches the order of temp and the p node in the order of the linked list. 
		
		temp -> prev = p -> prev;
		p -> next = temp -> next;
		temp -> next = p;
		p -> prev = temp;
	
		// Sets the before node hat takes place before the after node in the order of the linked list.
		
		before -> next = temp;
		
		// Sets the after node that is after the before node in the order of the linked list. 
		
		after -> prev = p;
	}
}
/*
//Be sure to comment out the main() function when submitting to codePost
int main()
{
    int array[] = {1, 3, 6, 10, 15, 21, 28, 36, 45, 55};
    Node * head = arrayToList(array, 10);
    printForwards(head);
    printBackwards(getTail(head));
    
    cout << "Swap [0],[1]" << endl;
    Node * p = getNode(head, 0);
    swapWithNext(p);
    printForwards(head);
    printBackwards(getTail(head));
    
    cout << "Swap [4],[5]" << endl;
    p = getNode(head, 4);
    swapWithNext(p);
    printForwards(head);
    printBackwards(getTail(head));
    
    cout << "Swap [8],[9]" << endl;
    p = getNode(head, 8);
    swapWithNext(p);
    printForwards(head);
    printBackwards(getTail(head));
}
*/
//Do not modify any functions below this line
Node * arrayToList(int array[], int size)
{
    Node * head;
    Node * p;
    int pos = 0;
    if (size > 0)
    {
        head = new Node();
        head->prev = nullptr;
        head->value = 0;
        p = head;
        while (pos < size)
        {
            p->next = new Node();
            p->next->prev = p;
            p = p->next;
            p->value = array[pos];
            pos++;
        }
        p->next = new Node();
        p->next->prev = p;
        p = p->next;
        p->value = 0;
        p->next = nullptr;
    }
    else
    {
        return nullptr;
    }
    return head;
}

//Return pointer to end of the list
Node * getTail(Node * head)
{
    Node * p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    return p;
}

//Return pointer to node with "index"
//First node "index" 0, second node "index" 1, ...
Node * getNode(Node * head, int index)
{
    int pos = 0;
    Node * p = head->next;
    if (pos == index)
    {
        return p;
    }
    else if (index < 0)
    {
        return head;
    }
    else
    {
        while (pos < index && p->next != nullptr)
        {
            p = p->next;
            pos++;
        }
    }
    return p;
}

//Print list forwards from start
void printForwards(Node * head)
{
    Node * p = head->next;
    while (p->next != nullptr)
    {
        cout << p->value << " ";
        p = p->next;
    }
    cout << endl;
}

//Print list backwards from end
void printBackwards(Node * tail)
{
    Node * p = tail->prev;
    while (p->prev != nullptr)
    {
        cout << p->value << " ";
        p = p->prev;
    }
    cout << endl;
}