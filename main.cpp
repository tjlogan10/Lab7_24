/*
 Travis Logan
 C++ Fall 2024
 Due: Dec. 3 2024
 Lab 7: Battleship
 Lab Description: The objective of this lab is to create a simple version of battleship using all of the tools of c++ that have been learned.
 */

#include <iostream>
#include <iomanip>

using namespace std;

typedef char board[10][10][6]; //Sets the 3d array for the boards to exist on.

//Precondition:    There are no array boards.
//Postcondition:   There are array boards to
void iniBoard(board Board);
//Precondition:    Boards are initialized but don't have a display.
//Postcondition:   Boards are able to be displayed
void OutputBoard(board Board, int player);
//Precondition:    There are boards initialized that do not have ships.
//Postcondition:   The boards have user ships that can be displayed.
void uPlacement(board Board);
//Precondition:    There are boards initialized that do not have ships.
//Postcondition:   The boards have computer ships that can be displayed.
void cPlacement(board Board);
//Precondition:    There is no x input to place ship.
//Postcondition:   There is an x input to place ship
void XPlacement(int& xpoint);
//Precondition:    There is no y input to place ship.
//Postcondition:   There is an y input to place ship
void YPlacement(int& ypoint);
//Precondition:    There is no direction input to place ship.
//Postcondition:   There is an x direction to place ship
void DirectionPlacement(int& dir);
//Precondition:    You don't know the state of the ships on the board.
//Postcondition:   You know the state of the shipps on the board.
void GameState(board Board);
//Precondition:    There are enemy shipps the need shot at.
//Postcondition:   Enemy shipps can be shot.
void uFiring(board Board, int player, bool& playing, int& L);
//Precondition:    You have shipps that can be shot at.
//Postcondition:   The computer can shoot at your ships.
void cFiring(board Board);
//Precondition:    Don't know if all ships are destroyed for either player.
//Postcondition:   You know if all the ships are destroyed for either player.
void WinCheck(board Board, bool playing, int& L, int& W);
//Precondition:    The game has ended and you arn't sure if you want the fun to end.
//Postcondition:   You have the oppertunity to continue the fun as many times as you want.
void PlayAgain(bool& again, int& player, bool& playing);
//Precondition:    You are unsure how many time you won and lost.
//Postcondition:   You know exactly how many times you won and lost.
void WL(int W, int L);

/*
         __________________________________________________________
*/
int main() {
    bool again = true ;
    bool playing = true ;
    int player = 0 ;
    int W = 0 ;
    int L = 0 ;
    board Board;
    do{
        iniBoard(Board);
        uPlacement(Board);
        cPlacement(Board);
        do{
            GameState(Board);
            uFiring(Board, player, playing, L);
            if (!playing)
                break;
            WinCheck(Board, playing, L, W);
            cFiring(Board);
            WinCheck(Board, playing, L, W);
        }while (playing);
        PlayAgain(again, player, playing);
    }while (again);
    WL(W, L);

    return 0;
}
/*
         __________________________________________________________
*/
void iniBoard(board Board) {
    for ( int y = 0 ; y < 10 ; y++ ) {
        for ( int x = 0 ; x < 10 ; x++ ) {
            for ( int z = 0 ; z < 6 ; z ++ ) {
                Board [ y ] [ x ] [ z ] = '~' ;
            }
        }
    }
}
void OutputBoard(board Board, int player ) {
    for ( int z = 0 ; z < player+2 ; z++ ) {
        cout << endl ;
        cout << "   1 2 3 4 5 6 7 8 9 10" << endl ;
        for ( int y = 0 ; y < 10 ; y++ ) {
            cout << setw(2) << y +1 ;
            cout << ' ' ;
            for ( int x = 0 ; x < 10 ; x++ ) {
                cout << Board [ y ] [ x ] [ z ] << ' ' ;
            }
            cout << endl ;
        }
    }
}
void uPlacement(board Board){
    int dir;
    int xpoint;
    int ypoint;
    char stype;
    int slength;
    
    for (int a = 0; a < 5; a++){
        bool print = true;
        OutputBoard (Board, 0);
        switch (a) {
            case 0:
                stype = '5';
                slength = 5;
                cout << "\nPlease place your Carrier (length 5): \n";
                break;
            case 1:
                stype = '4';
                slength = 4;
                cout << "\nPlease place your Battleship (length 4): \n";
                break;
            case 2:
                stype = '3';
                slength = 3;
                cout << "\nPlease place your Cruiser (length 3): \n";
                break;
            case 3:
                stype = '2';
                slength = 3;
                cout << "\nPlease place your Submarine (length 3): \n";
                break;
            case 4:
                stype = '1';
                slength = 2;
                cout << "\nPlease place your Destroyer (length 2): \n";
                break;
        }
        XPlacement(xpoint);
        if ( !cin ){
            cout << "No input" ;
            break;
        }
        if (xpoint > 10 || xpoint < 0){
            cout << "Invalid" << endl ;
            a-- ;
            continue ;
        }
        YPlacement(ypoint);
        if ( !cin ){
            cout << "No input" ;
        }
        if (ypoint > 10 || ypoint < 0){
            cout << "Invalid" << endl ;
            a-- ;
            continue ;
        }
        DirectionPlacement(dir);
        for ( int x = 0 ; x < slength ; x++ ) {
            if ( dir == 1 ) {
                if ( Board [ ypoint-x ] [ xpoint ] [ 1 ] == '#' ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 2 ) {
                if ( Board [ ypoint+x ] [ xpoint ] [ 1 ] == '#' ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 3 ) {
                if ( Board [ ypoint ] [ xpoint-x ] [ 1 ] == '#' ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 4 ) {
                if ( Board [ ypoint ] [ xpoint+x ] [ 1 ] == '#' ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else {
                if ( Board [ ypoint ] [ xpoint+x ] [ 1 ] == '#' ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            }
            if ( !print ) {
                break ;
            }
        }
        for ( int x = 0 ; x < slength ; x++ ) {
            if ( dir == 1 ) {
                if ( ypoint-x < 0 ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 2 ) {
                if ( ypoint+x > 9 ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 3 ) {
                if ( xpoint-x < 0 ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 4 ) {
                if ( xpoint+x > 9 ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            } else {
                if ( xpoint+x > 9 ) {
                    cout << "Invalid" << endl ;
                    a-- ;
                    print = false ;
                }
            }
            if ( !print ) {
                break ;
            }
        }
        if ( print ) {
            for ( int x = 0 ; x < slength ; x++ ) {
                if ( dir == 1 ) {
                    Board [ ypoint-x ] [ xpoint ] [ 1 ] = '#' ;
                    Board [ ypoint-x ] [ xpoint ] [ 4 ] = stype ;
                } else if ( dir == 2 ) {
                    Board [ ypoint+x ] [ xpoint ] [ 1 ] = '#' ;
                    Board [ ypoint+x ] [ xpoint ] [ 4 ] = stype ;
                } else if ( dir == 3 ) {
                    Board [ ypoint ] [ xpoint-x ] [ 1 ] = '#' ;
                    Board [ ypoint ] [ xpoint-x ] [ 4 ] = stype ;
                } else if ( dir == 4 ) {
                    Board [ ypoint ] [ xpoint+x ] [ 1 ] = '#' ;
                    Board [ ypoint ] [ xpoint+x ] [ 4 ] = stype ;
                } else {
                    Board [ ypoint ] [ xpoint+x ] [ 1 ] = '#' ;
                    Board [ ypoint ] [ xpoint+x ] [ 4 ] = stype ;
                }
            }
        }
    }
}
void cPlacement(board Board){
    int dir;
    int xpoint;
    int ypoint;
    char stype;
    int slength;
    
    cout << "The computer will now place its ships...";
    
    for (int a = 0; a < 5; a++){
        bool print = true;
        switch (a) {
            case 0:
                stype = '5';
                slength = 5;
                break;
            case 1:
                stype = '4';
                slength = 4;
                break;
            case 2:
                stype = '3';
                slength = 3;
                break;
            case 3:
                stype = '2';
                slength = 3;
                break;
            case 4:
                stype = '1';
                slength = 2;
                break;
        }
        srand(time(NULL));
        
        xpoint = rand() %10;
        if ( xpoint > 10 || xpoint < 0 ) {
                    a-- ;
                    continue ;
                }
        ypoint = rand() %10;
        if ( ypoint > 10 || ypoint < 0 ) {
                    a-- ;
                    continue ;
                }
        dir = rand() %4+1;
        for ( int x = 0 ; x < slength ; x++ ) {
            if ( dir == 1 ) {
                if ( Board [ ypoint-x ] [ xpoint ] [ 3 ] == '#' ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 2 ) {
                if ( Board [ ypoint+x ] [ xpoint ] [ 3 ] == '#' ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 3 ) {
                if ( Board [ ypoint ] [ xpoint-x ] [ 3 ] == '#' ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 4 ) {
                if ( Board [ ypoint ] [ xpoint+x ] [ 3 ] == '#' ) {
                    a-- ;
                    print = false ;
                }
            } else {
                if ( Board [ ypoint ] [ xpoint+x ] [ 3 ] == '#' ) {
                    a-- ;
                    print = false ;
                }
            }
            if ( !print ) {
                break ;
            }
        }
        for ( int x = 0 ; x < slength ; x++ ) {
            if ( dir == 1 ) {
                if ( ypoint-x < 0 ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 2 ) {
                if ( ypoint+x > 9 ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 3 ) {
                if ( xpoint-x < 0 ) {
                    a-- ;
                    print = false ;
                }
            } else if ( dir == 4 ) {
                if ( xpoint+x > 9 ) {
                    a-- ;
                    print = false ;
                }
            } else {
                if ( xpoint+x > 9 ) {
                    a-- ;
                    print = false ;
                }
            }
            if ( !print ) {
                break ;
            }
        }
        if ( print ) {
            for ( int x = 0 ; x < slength ; x++ ) {
                if ( dir == 1 ) {
                    Board [ ypoint-x ] [ xpoint ] [ 3 ] = '#' ;
                    Board [ ypoint-x ] [ xpoint ] [ 5 ] = stype ;
                } else if ( dir == 2 ) {
                    Board [ ypoint+x ] [ xpoint ] [ 3 ] = '#' ;
                    Board [ ypoint+x ] [ xpoint ] [ 5 ] = stype ;
                } else if ( dir == 3 ) {
                    Board [ ypoint ] [ xpoint-x ] [ 3 ] = '#' ;
                    Board [ ypoint ] [ xpoint-x ] [ 5 ] = stype ;
                } else if ( dir == 4 ) {
                    Board [ ypoint ] [ xpoint+x ] [ 3 ] = '#' ;
                    Board [ ypoint ] [ xpoint+x ] [ 5 ] = stype ;
                } else {
                    Board [ ypoint ] [ xpoint+x ] [ 3 ] = '#' ;
                    Board [ ypoint ] [ xpoint+x ] [ 5 ] = stype ;
                }
            }
        }
    }
}
void DirectionPlacement(int& dir){
    cout << "Please choose a direction you would like your ship to point(1: Up | 2:Down | 3:Left | 4:Right): ";
    cin >> dir;
}
void XPlacement(int& xpoint){
    cout << "Please choose a x location (top) to place your ship(1-10): ";
    cin >> xpoint;
    xpoint = xpoint - 1;
}
void YPlacement(int& ypoint){
    cout << "Please choose a y location (side) to place your ship(1-10): ";
    cin >> ypoint;
    ypoint = ypoint - 1;
}
void GameState(board Board){
    int uCarrier = 0;
    int uBattleship = 0;
    int uCruiser = 0;
    int uSubmarine = 0;
    int uDestroyer = 0;
    int cCarrier = 0;
    int cBattleship = 0;
    int cCruiser = 0;
    int cSubmarine = 0;
    int cDestroyer = 0;
    
    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            if (Board [y][x][4] == '5')
                uCarrier++;
            if (Board [y][x][4] == '4')
                uBattleship++;
            if (Board [y][x][4] == '3')
                uCruiser++;
            if (Board [y][x][4] == '2')
                uSubmarine++;
            if (Board [y][x][4] == '1')
                uDestroyer++;
        }
    }
    for (int y = 0; y < 10; y++){
        for (int x = 0; x < 10; x++){
            if (Board [y][x][5] == '5')
                cCarrier++;
            if (Board [y][x][5] == '4')
                cBattleship++;
            if (Board [y][x][5] == '3')
                cCruiser++;
            if (Board [y][x][5] == '2')
                cSubmarine++;
            if (Board [y][x][5] == '1')
                cDestroyer++;
        }
    }
    if (uCarrier == 0)
        cout << "Your Carrier has been destroyed :(\n";
    if (uBattleship == 0)
        cout << "Your Battleship has been destroyed :(\n";
    if (uCruiser == 0)
        cout << "Your Cruiser has been destroyed :(\n";
    if (uSubmarine == 0)
        cout << "Your Submarine has been destroyed :(\n";
    if (uDestroyer == 0)
        cout << "Your Destroyer has been destroyed :(\n";
    
    if (cCarrier == 0)
        cout << "Enemy Carrier has been destroyed :)\n";
    if (cBattleship == 0)
        cout << "Enemy Battleship has been destroyed :)\n";
    if (cCruiser == 0)
        cout << "Enemy Cruiser has been destroyed :)\n";
    if (cSubmarine == 0)
        cout << "Enemy Submarine has been destroyed :)\n";
    if (cDestroyer == 0)
        cout << "Enemy Destroyer has been destroyed :)\n";
}
void uFiring(board Board, int player, bool& playing, int& L){
    int xshot;
    int yshot;
    bool active = true;
    
    OutputBoard(Board, player);
    
    cout << "\nYour turn to shoot.\nTo choose to surrender enter 911.";
    
    do{
        do{
            cout << "\nEnter the x-coridinate (horizontal) to shoot: ";
            cin >> xshot;
            if (xshot == 911){
                playing = false;
                active = false;
                L++;
                break;
            }
            if (xshot <= 10 && xshot >0){
                xshot -= 1;
                active = false;
            }
            else if (xshot != 911){
                cout << "\nBad Input";
            }
        }while(active);
        if(!playing)
            break;
        do{
            cout << "\nEnter the y-coridinate (vertical) to shoot:";
            cin >> yshot;
            if (xshot == 911){
                playing = false;
                active = false;
                L++;
                break;
            }
            if (yshot <= 10 && yshot >0){
                yshot -= 1;
                active = false;
            }
            else if (yshot != 911){
                cout << "\nBad Input";
            }
        }while(active);
        if(!playing)
            break;
        if (Board [yshot] [xshot] [0] == 'M' || Board [yshot] [xshot] [0] == 'H')
            cout << "\nInvalid inputs";
        else
            active = false;
    }while (active);
    
    if (xshot != 911){
        if (Board [yshot] [xshot] [3] == '#'){
            Board [yshot] [xshot] [0] = 'H';
            Board [yshot] [xshot] [3] = 'H';
            cout << "\nHit!\n";
        }else{
            Board [yshot] [xshot] [0] = 'M';
            Board [yshot] [xshot] [3] = 'M';
            cout << "\nMiss!\n";
        }
    }
}
void cFiring(board Board){
    int xshot;
    int yshot;
    bool active = true;
    
    cout << "The enemy is firing.";
    
    do{
        xshot = rand() %10;
            
        yshot = rand() %10;
            
        if (Board [yshot] [xshot] [2] == 'M' || Board [yshot] [xshot] [2] == 'H')
            active = true;
        else
            active = false;
        
    }while (active);
    
        if (Board [yshot] [ xshot] [1] == '#'){
            Board [yshot] [xshot] [2] = 'H';
            Board [yshot] [xshot] [1] = 'H';
            cout << "\nComputer Hit!\n";
        }else{
            Board [yshot] [xshot] [2] = 'M';
            Board [yshot] [xshot] [1] = 'M';
            cout << "\nComputer Miss!\n";
    }
}
void WinCheck(board Board, bool playing, int& L, int& W) {
    
    int uCarrier = 0 ;
    int uBattleship = 0 ;
    int uCruiser = 0 ;
    int uSubmarine = 0 ;
    int uDestroyer = 0 ;
    
    int cCarrier = 0 ;
    int cBattleship = 0 ;
    int cCruiser = 0 ;
    int cSubmarine = 0 ;
    int cDestroyer = 0 ;
    
    for ( int y = 0 ; y < 10 ; y++ ) {
        for ( int x = 0 ; x < 10 ; x++ ) {
            if ( Board [ y ] [ x ] [ 4 ] == '5' ) {
                uCarrier++ ;
            } else if ( Board [ y ] [ x ] [ 4 ] == '4' ) {
                uBattleship++ ;
            } else if ( Board [ y ] [ x ] [ 4 ] == '3' ) {
                uCruiser++ ;
            } else if ( Board [ y ] [ x ] [ 4 ] == '2' ) {
                uSubmarine++ ;
            } else if ( Board [ y ] [ x ] [ 4 ] == '1' ) {
                uDestroyer++ ;
            }
        }
    }
    for ( int y = 0 ; y < 10 ; y++ ) {
        for ( int x = 0 ; x < 10 ; x++ ) {
            if ( Board [ y ] [ x ] [ 5 ] == '5' ) {
                cCarrier++ ;
            } else if ( Board [ y ] [ x ] [ 5 ] == '4' ) {
                cBattleship++ ;
            } else if ( Board [ y ] [ x ] [ 5 ] == '3' ) {
                cCruiser++ ;
            } else if ( Board [ y ] [ x ] [ 5 ] == '2' ) {
                cSubmarine++ ;
            } else if ( Board [ y ] [ x ] [ 5 ] == '1' ) {
                cDestroyer++ ;
            }
        }
    }
    if ( uCarrier == 0 && uBattleship == 0 && uCruiser == 0
        && uSubmarine == 0 && uDestroyer == 0 ) {
        cout << "All of your ships have been destroyed. You lose!" << endl ;
        L++ ;
        playing = false ;
    }
    if ( cCarrier == 0 && cBattleship == 0 && cCruiser == 0
        && cSubmarine == 0 && cDestroyer == 0 ) {
        cout << "You destroyed all of the enemy ships. You win!" << endl ;
        W++ ;
        playing = false ;
        
    }
}
void PlayAgain(bool& again, int& player, bool& playing){
    int a = 0;
    cout << "\nWould you like to play again? 1:Yes 2:No\n:";
    cin >> a;
    if (a != 1){
        again = false;
    }else{
        player = 0;
        again = true;
        playing = true;
    }
}
void WL(int W, int L){
    cout << "\n\nYou ended with " << W << " wins and " << L << " loses.\n";
}
