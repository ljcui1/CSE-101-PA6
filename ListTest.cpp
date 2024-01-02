//-----------------------------------------------------------------------------
// Name: Lia Cui
// CRUZID: ljcui
// Assignment Name: PA6
//
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;


   return( EXIT_SUCCESS );
}

/*
output:

A = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 0
B = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B.position() = 0
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C.position() = 10
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
D.position() = 10

A = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 10
B = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B.position() = 10
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C.position() = 0
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
D.position() = 0

B: 10 9 8 7 6 5 4
B.position() = 3

C: 1 2 3 4 5 6 7
C.position() = 7

A==B is false
B==C is true
C==D is false
D==A is true

5
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
(1, 2, 3, 4, 7, 8, 9, 10)
4
1
(3, 4, 7, 8, 9, 10)
0
-1
6
-1
0

A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5, 5, 6, 4, 7, 3, 8, 2, 9, 1, 10)
15
A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5)
10

E==A is true

F = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5, 3, 4, 7, 8, 9, 10)
length: 16
front: 10
back: 10
position: 0
peekNext: 10
10
peekNext: 1
1
peekNext: 9
9
peekNext: 2
2
peekNext: 8
8
peekNext: 3
3
peekNext: 7
7
F = (-1, 10, -2, 1, -3, 9, -4, 2, -5, 8, -6, 3, -7, 7, 4, 6, 5, 3, 4, 7, 8, 9, 10)

test exceptions:
A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5)
List: peekPrev(): cursor at front
   continuing without interruption
List: movePrev(): cursor at front
   continuing without interruption
List: setBefore(): cursor at front
   continuing without interruption
List: eraseBefore(): cursor at front
   continuing without interruption
List: peekNext(): cursor at back
   continuing without interruption
List: moveNext(): cursor at back
   continuing without interruption
List: setAfter(): cursor at back
   continuing without interruption
List: eraseAfter(): cursor at back
   continuing without interruption
List: front(): empty list
   continuing without interruption
List: back(): empty list
   continuing without interruption

*/