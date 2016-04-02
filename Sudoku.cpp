#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"

Sudoku::Sudoku(){
    for(int i=0; i<sudokuSize; ++i){
        map[i]=0;
        ans[i]=0;
        blankNum[i]=0;
    }
    fillPoint = 0;
}
void Sudoku::giveQuestion(){
    int question[sudokuSize]={6, 0, 0, 5, 0, 0, 3, 0, 1,
                              0, 9, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 7, 0, 0, 8, 9, 0, 4,
                              8, 0, 0, 0, 0, 1, 5, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 0, 0,
                              0, 0, 4, 9, 0, 0, 0, 0, 2,
                              3, 0, 5, 1, 0, 0, 6, 0, 0,
                              0, 0, 0, 0, 0, 0, 0, 1, 0,
                              2, 0, 1, 0, 0, 4, 0, 0, 7};
    for(int i=0; i<sudokuSize; ++i)
        map[i] = question[i];
    transform();
}
void Sudoku::readIn(){
    int i;
    for(i=0; i<sudokuSize; ++i)
        cin >> map[i];
}
void Sudoku::solve() {
   int i, result = 0;
   int test = nextBlank(-1);

   if(initial_check()==false) test=sudokuSize;
   else
      if(test==sudokuSize){
            result = 1;
            for(i=0; i<sudokuSize; ++i) ans[i] = map[i];
      }

   while(test>=0 && test<sudokuSize && result<2){
      map[test]++;
      if(map[test]>9){
         map[test] = 0;
         test = pop();
      }
      else{
         if(check(test)==true){
            blankNum[fillPoint++] = test;
            test=nextBlank(test);
            if(test==sudokuSize){
               result++;
               for(i=0; i<sudokuSize; ++i) ans[i] = map[i];
               test = pop();
            }
         }
      }
   }

   if(result==1){
        cout << "1" << endl;
        printOut(true);
   }
   else if(result>1) cout << "2";
   else
        cout << "0";

}
int Sudoku::nextBlank(int test){
   do{
      test++;
   }  while(test<sudokuSize && map[test]>0);
   return test;
}
int Sudoku::pop(){
   if(fillPoint<=0)  return -1;
   else           return blankNum[--fillPoint];
}
bool Sudoku::initial_check(){
    int i, j, k, l;
    for(i=0; i<9; ++i){
        for(j=i; j<sudokuSize; j+=9){
            if(map[j]!=0){
                for(k=j+9; k<sudokuSize; k+=9){
                    if(map[k]!=0){
                        if(map[j]==map[k]) return false;
                    }
                }
            }
        }
    }
    for(i=0; i<sudokuSize; i+=9){
        for(j=i; j<i+9; ++j){
            if(map[j]!=0){
                for(k=j+1; k<i+9; k+=9){
                    if(map[k]!=0){
                        if(map[j]==map[k]) return false;
                    }
                }
            }
        }
    }
    for(i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            for(k=i*3+j*27; k<i*3+j*27+21; ++k){
                if(map[k]!=0){
                    for(l=k; l<i*3+j*27+21; ++l){
                        if(map[l]!=0){
                            if(map[k]==map[l] && k!=l) return false;
                        }
                        if(l%3==2) l+=6;
                    }
                }
                if(k%3==2) k+=6;
            }
        }
    }
    return true;
}
bool Sudoku::check(int test){
    int x, y, i;
    x = test/9;
    y = test%9;
    for(i=9*x; i<9*(x+1); ++i){
        if(i==test) continue;
        if(map[test]==map[i]) return false;
    }
    for(i=y; i<sudokuSize; i+=9){
        if(i==test) continue;
        if(map[test]==map[i]) return false;
    }
    for(i=(x/3)*27+(y/3)*3; i<(x/3)*27+(y/3)*3+21; ++i){
        if(map[test]==map[i] && i!=test) return false;
        if(i%3==2) i+=(7-1);
    }
    return true;
}
void Sudoku::transform(){
    change();
    printOut(false);
}
void Sudoku::change(){
    srand(time(NULL));
    changeNum(rand()%sudokuNum+1, rand()%sudokuNum+1);
    changeRow(rand()%3, rand()%3);
    changeCol(rand()%3, rand()%3);
    rotate(rand()%101);
    flip(rand()%2);
}
void Sudoku::changeNum(int a, int b){
    int i;
    if(a!=b)
        for(i=0; i<sudokuSize; ++i){
            if(map[i]==a) map[i]=b;
            else if(map[i]==b) map[i]=a;
        }
}
void Sudoku::changeRow(int a, int b){
    int i, temp;
    if(a!=b)
        for(i=0; i<27; ++i){
            temp = map[i+27*a];
            map[i+27*a] = map[i+27*b];
            map[i+27*b] = temp;
        }
}
void Sudoku::changeCol(int a, int b){
    int i, temp;
    if(a!=b)
        for(i=0; i<75; ++i){
            temp = map[i+3*a];
            map[i+3*a] = map[i+3*b];
            map[i+3*b] = temp;
            if(i%3==2) i+=(7-1);
        }
}
void Sudoku::rotate(int n){
    int i, temp;
    if(n%4==1)
        for(i=0; i<32; ++i){
            temp = map[i];
            map[i] = map[(72-8*(i/10))-9*(i%10)];
            map[(72-8*(i/10))-9*(i%10)] = map[80-i];
            map[80-i] = map[i+(8-2*(i/10))+8*(i%10)];
            map[i+(8-2*(i/10))+8*(i%10)] = temp;
            if(i%8==7) i=(i/10+1)*10-1;
        }
    else if(n%4==2)
        for(i=0; i<40; ++i){
            temp = map[i];
            map[i] = map[80-i];
            map[80-i] = temp;
        }
    else if(n%4==3)
        for(i=0; i<32; ++i){
            temp = map[i];
            map[i] = map[i+(8-2*(i/10))+8*(i%10)];
            map[i+(8-2*(i/10))+8*(i%10)] = map[80-i];
            map[80-i] = map[(72-8*(i/10))-9*(i%10)];
            map[(72-8*(i/10))-9*(i%10)] = temp;
            if(i%8==7) i=(i/10+1)*10-1;
        }
}
void Sudoku::flip(int n){
    int i, temp;
    if(n==0)
        for(i=0; i<36; ++i){
            temp = map[i];
            map[i]= map[72+2*(i%9)-i];
            map[72+2*(i%9)-i] = temp;
        }
    else
        for(i=0; i<76; ++i){
            temp = map[i];
            map[i]= map[8+18*(i/9)-i];
            map[8+18*(i/9)-i] = temp;
            if(i%9==3) i+=(6-1);
        }
}
void Sudoku::printOut(bool isAns){
    int i;
    if(!isAns)
        for(i=0; i<sudokuSize; ++i)
            cout << map[i] << ((i+1)%9==0?'\n':' ');
    else
        for(i=0; i<sudokuSize; ++i)
            cout << ans[i] << ((i+1)%9==0?'\n':' ');
}
