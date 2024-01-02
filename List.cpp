//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA6
//
//-----------------------------------------------------------------------------


#include <stdlib.h>

#include<iostream>
#include<string>
#include<stdexcept>
#include "List.h"

List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}


List::List() {
	// make this an empty List
	frontDummy = new Node(-1000);
	backDummy = new Node(-1000);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;

}


// Copy constructor.
List::List(const List& L) {
	// make this an empty List
	frontDummy = new Node(-1000);
	backDummy = new Node(-1000);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;

	Node* N = L.frontDummy->next;

	while (N != L.backDummy) {
		this->insertBefore(N->data);
		N = N->next;
	}

}

void List::freememory() {
	Node* N = frontDummy;
	Node* M = nullptr;

	while (N != backDummy) {
		M = N;
		N = N->next;
		delete M;
	}

	delete backDummy;
}

// Destructor
List::~List() {
	freememory();
}

int List::length() const {
	return num_elements;
}


// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if (num_elements == 0) {
		throw std::length_error("List: front(): empty list");
	}

	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
	if (num_elements == 0) {
		throw std::length_error("List: back(): empty list");
	}

	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if (pos_cursor == num_elements) {
		throw std::range_error("List: peekNext(): cursor at back");
	}

	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if (pos_cursor == 0) {
		throw std::range_error("List: peekPrev(): cursor at front");
	}

	return beforeCursor->data;
}


// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	freememory();

	frontDummy = new Node(-1000);
	backDummy = new Node(-1000);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	num_elements = 0;
	pos_cursor = 0;

}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {

	beforeCursor = frontDummy;
	afterCursor = beforeCursor->next;

	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	afterCursor = backDummy;
	beforeCursor = afterCursor->prev;

	pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext() {
	if (pos_cursor == num_elements) {
		throw std::range_error("List: moveNext(): cursor at back");
	}

	pos_cursor++;
	int r = afterCursor->data;
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	return r;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev() {
	if (pos_cursor == 0) {
		throw std::range_error("List: movePrev(): cursor at front");
	}

	pos_cursor--;
	int r = beforeCursor->data;
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	return r;
}

// insertAfter()
// Inserts x after cursor. 
// Cursor location is not changed.
void List::insertAfter(ListElement x) {
	Node* N = new Node(x);
	//if (num_elements == 0) {
	//	N->next = afterCursor;
	//	afterCursor->prev = N;
	//	N->prev = beforeCursor;
	//	beforeCursor->next = N;
	//	afterCursor = N;
	//}
	//else {
	//	Node* C = beforeCursor->next; // Cursor element same as afterCursor->prev
	//	C -> next = N;
	//	N -> prev = C;
	//	N->next = afterCursor;
	//	afterCursor->prev = N;
	//	afterCursor = N;
	//}
	beforeCursor->next = N;
	N->prev = beforeCursor;
	afterCursor->prev = N;
	N->next = afterCursor;
	afterCursor = N;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	Node* N = new Node(x);

	beforeCursor->next = N;
	N->prev = beforeCursor;
	afterCursor->prev = N;
	N->next = afterCursor;
	beforeCursor = N;
	pos_cursor++;
	num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if (pos_cursor == num_elements) {
		throw std::range_error("List: setAfter(): cursor at back");
	}

	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if (pos_cursor == 0) {
		throw std::range_error("List: setBefore(): cursor at front");
	}

	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if (pos_cursor == num_elements) {
		throw std::range_error("List: eraseAfter(): cursor at back");
	}

	Node* A = afterCursor;
	Node* N = afterCursor->next; //Current element same as afterCursor->prev

	beforeCursor->next = N;
	N->prev = beforeCursor;
	afterCursor = N;

	num_elements--;
	delete A;
	// Needs to free memory
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if (pos_cursor == 0) {
		throw std::range_error("List: eraseBefore(): cursor at front");
	}

	Node* M = beforeCursor;
	Node* N = beforeCursor->prev; //Current element same as afterCursor->prev

	N->next = afterCursor;
	afterCursor->prev = N;

	beforeCursor = N;

	pos_cursor--;
	num_elements--;
	delete M;

	// Needs to free memory
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) {
	Node* N = afterCursor; // Starting from the current cursor position

	while (pos_cursor < num_elements) {
		if (N->data == x) {
			beforeCursor = N;
			afterCursor = N->next;
			pos_cursor++;
			return pos_cursor;
		}
		N = N->next;
		pos_cursor++;
	}
	afterCursor = backDummy;
	beforeCursor = backDummy->prev;
	pos_cursor = num_elements;
	return -1;

}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) {
	Node* N = beforeCursor;

	while (pos_cursor > 0) {
		if (N->data == x) {
			afterCursor = N;
			beforeCursor = N->prev;
			pos_cursor--;
			return pos_cursor;
		}
		N = N->prev;
		pos_cursor--;
	}
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
	return -1;

}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
	List L = List();
	int i;
	int b;
	int c = pos_cursor;
	List L1 = List();

	moveFront();
	L1.moveFront();
	for (i = 0; i < num_elements; i++) {
		L.moveFront();
		b = moveNext();
		if (L.findNext(b) == -1) {
			L.moveBack();
			L.insertAfter(b);
			L1.insertBefore(i);
		}
	}

	moveBack();
	while (pos_cursor > 0) {
		eraseBefore();
	}

	L.moveFront();
	for (i = 0; i < L.length(); i++) {
		insertBefore(L.moveNext());
	}

	L1.moveFront();
	if ( c == 0 ) { 
		pos_cursor = 0;
	} else {
		pos_cursor = L1.length();
		for (i = 0; i < L1.length(); i++) {
			b = L1.moveNext();
			if ( b >= c) {
				pos_cursor = i;
				break;
			}
		}
	}
	c = pos_cursor;
	if ( pos_cursor == 0 ) {
		beforeCursor = frontDummy;
		afterCursor = frontDummy->next;
	}
	else if ( pos_cursor == length() ) {
		beforeCursor = backDummy->prev;
		afterCursor = backDummy;
	} else {
		moveFront();
		Node * N = frontDummy;
		for (i = 0; i < c; i++) {
			moveNext();
			N = N->next;
		}
		beforeCursor = N->prev;
		afterCursor = N->next;
	}


}


// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	List A = List(*this);
	Node* N = L.frontDummy->next;

	while (N != L.backDummy) {
		A.insertBefore(N->data);
		N = N->next;
	}
	A.beforeCursor = A.frontDummy;
	A.afterCursor = A.beforeCursor->next;
	A.pos_cursor = 0;
	return A;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	Node* N = nullptr;
	std::string s = "(";

	for (N = frontDummy; N != backDummy; N = N->next) {
		if (N != frontDummy && N != backDummy) {
			if ( s.compare("(")==0) {
				s += std::to_string(N->data);
			} else {
			s += ", " + std::to_string(N->data);
			}
		}
	}
	s += ")";
	return s;

}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (length() == R.length());
	N = this->frontDummy;
	M = R.frontDummy;
	while (eq && N != nullptr) {
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;

}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<(std::ostream& stream, const List& L) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=(const List& L) {
	if (this != &L) { // not self assignment
		// make a copy of L
		List temp = L;

		// then swap the copy's fields with fields of this
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
		//temp.freememory();
	}

	// return this with the new data installed
	return *this;

	// the copy, if there is one, is deleted upon return
}


