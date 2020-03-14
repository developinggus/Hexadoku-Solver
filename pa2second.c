#include<stdlib.h>
#include<stdio.h>
//-----------------------------------------------------------------------------
/* Strategy 
 * Rules:
 * 1. Each number is unique to the row and col its in.
 * 2. Each number is unique to its 4x4 NONOVERLAPPING squares(0-3,4-7,8-11,12-15)
 * 3. Each row and col will have all 15 decimals present
 *
 * Create an array of size 15 that has all the elements we need inside.
 * After creating the 2D array and filling in the elements from the testcases. Go to empty space to empty space, and try each number from the arr created earlier to see which ones fits best
 * CREATE SEPERATE METHODS
 * CHECH IF THE HEXIDOKU IS EVEN IN THE RIGHT FORMAT FIRSTTT BEFORE DOING ALL THIS
 * THEN PRINT EVERYTHING OUT!!!!
 * FREE SPACE
 */
//----------------------------------------------------------------------------
char** fillMe(char** hex, char dom [] );
int validHex(char** hex, char dom [] );
int rowCheck(char** hex, char ch, int row);
int colCheck(char**hex, char ch, int col);
int quadCheck(char**hex, char ch, int row, int col);
int isItFilled(char**hex);
int prowCheck(char** hex, char ch, int row);
int pcolCheck(char** hex, char ch, int col);
int pquadCheck(char** hex, char ch, int row, int col);
int recSolve(char** hex, int row, int col,char dom []);
//----------------------------------------------------------------------------
int main ( int argc, char** argv ) {
  //creating the 16x16
  int i,j,k,valid;
  char dom [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; //A reps 10, B == 11, etc...
  FILE* fefe;
  fefe = fopen(argv[1],"r");
  char**  hex = (char**) malloc(16 * sizeof(char *));//the first col
  for (i = 0; i < 16; i++ ) {
    hex[i] = (char*) malloc(16*sizeof(char *));
  }
  //now lets fill it in, we will be reading th eenputs from left to right, so we will fill it row by row
  for (j = 0; j < 16; j++) {
    for ( k = 0; k < 16; k++ ) {
      fscanf(fefe, "%c\t" , &hex[j][k]);
    }
    fscanf(fefe,"\n");
  }
  //now we're going to starting filling it in
  valid = validHex(hex,dom); // returns 1 if VALID
  //printf("Line 41\n");
  if ( valid == 0 ) {
    printf("no-solution\n");
    return 0;
  }
  //printf("Line 50\n");
  fillMe(hex,dom);
  /*
  for ( m = 0; m < 16; m++ ) {
    for ( n = 0; n < 16; n++ ) {
      printf("%c\t", hex[m][n]);
    }
    printf("\n");
  }
  */
  return 0;     
}
//-----------------------------------------------------------------------------
int isItFilled(char**hex) {
 int i,j;
 for ( i = 0; i < 16; i++ ) {
  for ( j = 0; j < 16; j++ ) {
    if (hex[i][j] == '-') {
      return 0;
    }
  }
 }
return 1;
}
//-----------------------------------------------------------------------------
int pquadCheck(char** hex, char ch, int row, int col ) {
 int newI = (row/4) * 4;
 int newJ = (col/4) * 4;
 int newIE = newI + 4;
 int newJE = newJ + 4;
 int i,j;
 int count = 0;
 int chcount = 0;
 for ( i = newI; i < newIE; i++ ) {
  for ( j = newJ; j < newJE; j++ ) {
   if ( hex[i][j] == ch ) {
    chcount++;
   }
   if ( hex[i][j] == '-' ) {
    count++;
   }
  }
 }
 if ( count > 1 ) {
  return 0;
 }
 if ( chcount == 0 ) {
  return 1;
 }
 return 0; 
}
//-----------------------------------------------------------------------------
int pcolCheck(char** hex, char ch, int col ) {
 int i;
 int count = 0;
 int chcount = 0;
 for ( i = 0; i < 16; i++ ) {
  if ( hex[i][col] == '-' ) {
   count++;
  }
  if ( hex[i][col] == ch ) {
   chcount++;
  }
 }
 if ( count > 1 ) {
  return 0;
 }
 if ( chcount == 0 ) {
  return 1;
 }
 return 0;
}
//-----------------------------------------------------------------------------
int prowCheck(char** hex, char ch, int row) {
 int i;
 int count = 0;
 int chcount = 0;
 for ( i = 0; i < 16; i++ ) {
  if( hex[row][i] == '-' ) {
   count++;
  }
  if ( hex[row][i] == ch ) {
   chcount++;
  }
 }
 if ( count > 1 ) {
  return 0;
 }
 if ( chcount == 0 ) {
  return 1;
 }
 return 0;
}
//-----------------------------------------------------------------------------
int quadCheck(char**hex, char ch, int row, int col ) {
 //using the row and col, we gonna find put what quadrant its in
 //calculating the quad can be done by:
 int newI = (row/4) * 4;
 int newJ = (col/4) * 4;
 int newIE = newI + 4;
 int newJE = newJ + 4;
 int i,j;
 //int count = 0;
 for ( i = newI; i < newIE; i++ ) {
  for ( j = newJ; j < newJE; j++ ) {
   if ( hex[i][j] == ch ) {
     return 0;
   }
   /*
   if ( hex[i][j] == '-' ) {
     count++;
   }
   */
  }
 }
 /*
 if ( count == 1 ) {
   return 2;
 }
 */
 return 1;
}
//----------------------------------------------------------------------------
int colCheck(char**hex, char ch, int col) {
  //same as rowcheck, but cheching cols instead......
  int i;
  //int count = 0;
  for ( i = 0; i < 16; i++ ) {
    if ( hex[i][col] == ch ) {
      return 0;
    }
    /*
    if ( hex[i][col] == '-' ) {
     count++;
    }
    */
  }
  return 1;
}
//----------------------------------------------------------------------------
int rowCheck(char** hex, char ch, int row) {
  //check if this row has an element that can be added with 100%, first we have to check that there are no more than one '-'
  int i;
  //int count = 0;
  for ( i = 0; i < 16; i++ ) {
    if ( hex[row][i] == ch ) {
      return 0;
    }
  }
  return 1;
}
//-----------------------------------------------------------------------------
char** fillMe(char** hex, char dom[]) {
 int m,n,q;
 //int k;
 char ch;
 int potRow;
 int potCol;
 int potQuad;
 int x = 0;
 //int foo;
 while (x<100) { //priority fill, only fills those that have a single element missing, imporves
  for ( m = 0; m < 16; m++ ) {
   for ( n = 0; n < 16; n++ ) {
    if ( hex[m][n] == '-' ) {
     for ( q = 0; q < 16; q++ ) {
      ch = dom[q];
      potRow = prowCheck(hex,ch,m);
      potCol = pcolCheck(hex,ch,n);
      potQuad = pquadCheck(hex,ch,m,n);  
      if ( potRow == 1 || potCol == 1 || potQuad == 1 ) {
       hex[m][n] = ch;
       return fillMe(hex,dom);
      }
     }
    }
   }
  }
  x++;
 }

 recSolve(hex, 0, 0, dom ); //We solved all we could, now we're goinna rec solve with backtracking 
 /*
 while ( isItFilled(hex) == 0 ) { //fill in the rest
  for ( i = 0; i < 16; i++ ) {
   for ( j = 0; j < 16; j++ ) {
    if ( hex[i][j] == '-' ) {
     for ( k = 0; k < 16; k++ ) {
      ch = dom[k];
      potRow = rowCheck(hex,ch,i);
      potCol = colCheck(hex,ch,j);
      potQuad = quadCheck(hex,ch,i,j);
      if ( potRow == 1 && potCol == 1 && potQuad == 1 ) {
       hex[i][j] = ch;
       return fillMe(hex,dom);
       //count++;
      }
     }
    }
   }
  }
 }
 */       
 return hex;
}
//-----------------------------------------------------------------------------
int recSolve(char** hex, int row, int col, char dom []) {
 //base cases
 int i,j;
 if ( col == 16 ) { //we are done with the row, move on to the next
  col = 0;
  row++;
  
  if ( row == 16 ) {
   //print it
   for ( i = 0; i < 16; i++ ) {
    for ( j = 0; j < 16; j++ ) {
     printf("%c\t", hex[i][j]);
    }
    printf("\n");
   }
   return 1;
  }
 }

 if ( hex[row][col] != '-' ) {
  return recSolve(hex,row,col+1,dom);
 }

 int rowChecks,colChecks,quadChecks;
 char ch;
 for ( i = 0; i < 16; i++ ) { //similair to how we solved it in part 1 of pa2, but
  ch = dom[i];                //only cont. when it is true or 1
  rowChecks = rowCheck(hex,ch,row);
  colChecks = colCheck(hex,ch,col);
  quadChecks =  quadCheck(hex,ch,row,col);
  if ( rowChecks == 1 && colChecks == 1 && quadChecks == 1 ) {
   hex[row][col] = ch;
   if ( recSolve(hex,row,col+1,dom) == 1 /*meaning that it is a VALID entry*/) {
    return 1;
   }
  }
 }
 
 hex[row][col] = '-';

 return 0;

  

}
//----------------------------------------------------------------------------
int validHex(char** hex, char dom []) { //this will check each row and col, and make sure its in the right format
  //we will grab a char from dom, and all the rows, according to the rules, there cant be duplicates, if the rules are violated, we will return 0
  int i,r,c,rowC,colC,r1,c1;
  char ch;
  for ( i = 0; i < 16; i++ ) {
    ch = dom[i];
    for ( r = 0; r < 16; r++ ) {//checks every row iin the hex, if rowC is more than 1, than we return 0
      rowC = 0;
      for ( c = 0; c < 16; c++ ) {
        if ( ch == hex[r][c] ) {
          rowC++;
        }
      }
      if ( rowC > 1 ) { //duplicates found in the row!!!!
        return 0;
      }
    }
    for ( c1 = 0; c1 < 16; c1++ ) { //checks collumn
      colC = 0;
      for ( r1 = 0; r1 < 16; r1++ ) {
        if ( ch == hex[r1][c1] ) {
          colC++;
        }
      }
      if ( colC > 1 ) { //duplicates in the col!!!!
        return 0;
      }
    }
    // now we have to do the tedious task of checking each 4x4 in the 16x16 hex
    // 1st (0-3,0-3), 2nd (4-7),(0,3) etc...
    rowC = 0;
    int ti,tj;
   // printf("Line 88\n");
    for(ti = 0; ti < 4; ti++ ) {
      for ( tj = 0; tj < 4; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;
   // printf("Line 99\n");
    for(ti = 0; ti < 4; ti++ ) {
      for ( tj = 4; tj < 8; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 0; ti < 4; ti++ ) {
      for ( tj = 8; tj < 12; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;
   // printf("Line 123\n");
    for(ti = 0; ti < 4; ti++ ) {
      for ( tj = 12; tj < 16; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 4; ti < 8; ti++ ) {
      for ( tj = 0; tj < 4; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 4; ti < 8; ti++ ) {
      for ( tj = 4; tj < 8; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 4; ti < 8; ti++ ) {
      for ( tj = 8; tj < 12; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 4; ti < 8; ti++ ) {
      for ( tj = 12; tj < 16; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 8; ti < 12; ti++ ) {
      for ( tj = 0; tj < 4; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;
   // printf("Line 195\n");
    for(ti = 8; ti < 12; ti++ ) {
      for ( tj = 4; tj < 8; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 8; ti < 12; ti++ ) {
      for ( tj = 8; tj < 12; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 8; ti < 12; ti++ ) {
      for ( tj = 12; tj < 16; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 12; ti < 16; ti++ ) {
      for ( tj = 0; tj < 4; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 12; ti < 16; ti++ ) {
      for ( tj = 4; tj < 8; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 12; ti < 16; ti++ ) {
      for ( tj = 8; tj < 12; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;

    for(ti = 12; ti < 16; ti++ ) {
      for ( tj = 12; tj < 16; tj++ ) {
        if( ch == hex[ti][tj] ) {
          rowC++;
        }
      }
    }
    if ( rowC > 1 ) {
      return 0;
    }
    rowC =0;
  }
  return 1;
  //probably could've thought of a better way, but was told it doesn't matter
}
//----------------------------------------------------------------------------
