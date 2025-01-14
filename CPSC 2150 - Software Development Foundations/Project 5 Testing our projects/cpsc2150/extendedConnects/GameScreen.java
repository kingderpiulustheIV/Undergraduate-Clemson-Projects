package cpsc2150.extendedConnects;

import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;

import java.util.Scanner;

/*GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE

    Prahalad Gururajan (PravClem)
    Connor Burkart (crburka)
    Sean Farrell (sfarrellClemosn)
    Parthiv Patel (Parthivp2205)

 */

public class GameScreen {

    public static void main(String[] args) {


        IGameBoard board = null;

        Boolean stopPlaying = false; // status if player is playing the game
        Character playAgain;         // Used for input if the play does or does not want to play again
        Character choice;       // This is used for user input
        int numPlayers;     // The number of players in the game
        int row = 0;        // User input for Row
        int col = 0;        // User input for Row
        int numWin = 0;     // User input for Win Num
        int spotOfPlayer = 0;       // This increments through the string that is the list of players
        String allPlayers = "";     // This is the list of players
        Scanner myObj = new Scanner(System.in);        // scanner for user Input
        int move; // Int used for players selected column

        System.out.println("How many players are playing?");
        numPlayers = myObj.nextInt();

        while (numPlayers > board.MAX_NUM_PLAYERS || numPlayers < board.MIN_NUM_PLAYERS)
        {
            if(numPlayers > board.MAX_NUM_PLAYERS)
            {
                System.out.println("Enter a number of players less than 10");
                numPlayers = myObj.nextInt();
            }
            else
            {
                System.out.println("Enter a number of players more than 1");
                numPlayers = myObj.nextInt();
            }


        }

        for (int i = 0; i < numPlayers; i++) {
            Character currentPlayer;
            System.out.println("What is player " + (i + 1) + " marker?");
            currentPlayer = myObj.next().charAt(0);
            allPlayers = allPlayers + currentPlayer;    // Gets List of players

            for (int j = 0; j < i; j++) {
                while (currentPlayer == allPlayers.charAt(j)) {
                    System.out.println("Enter a new marker");
                    currentPlayer = myObj.next().charAt(0);
                }
            }


        }



        Character currentPlayer = allPlayers.toUpperCase().charAt(0);
        int maxNumPlayer = allPlayers.length() - 1;

        while (row > board.MAX_ROWS || col > board.MAX_COL || row < board.MIN_SIZE || col < board.MIN_SIZE || numWin > board.MAX_NUM_TO_WIN || numWin < board.MIN_SIZE) {
            if (row > board.MAX_ROWS) {
                System.out.println("Enter a number less than 100 for row");
                row = myObj.nextInt();

            } else if (col > board.MAX_COL) {
                System.out.println("Enter a number less than 100 for column");
                col = myObj.nextInt();
            } else if (numWin > board.MAX_NUM_TO_WIN) {
                System.out.println("Enter a number less than 25 for number to win");
                numWin = myObj.nextInt();
            }
            if (row < board.MIN_SIZE) {
                System.out.println("Enter a number more than 3 for row");
                row = myObj.nextInt();
            } else if (col < board.MIN_SIZE) {
                System.out.println("Enter a number more than 3 for column");
                col = myObj.nextInt();
            } else if (numWin < board.MIN_SIZE) {
                System.out.println("Enter a number more than 3 for number to win");
                numWin = myObj.nextInt();
            }
            if (numWin > row || numWin > col) {
                System.out.println("Enter a number less than the total row or column");
                numWin = myObj.nextInt();

            }

        }

        System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
        choice = myObj.next().charAt(0);

        if (choice == 'F' || choice == 'f') {
            choice = 'F';
        } else {
            choice = 'M';
        }

        if (choice == 'M') {
            board = new GameBoardMem(row, col, numWin);   // Creates the game board

        } else {
            board = new GameBoard(row, col, numWin);   // Creates the game board
        }

        while (stopPlaying == false) {

            // Prints out gameboard to the console
            System.out.println(board);

            // Asks a player where they would like to placer their piece in.
            System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
            move = myObj.nextInt();

            // Validates that the player is selecting a valid column in the game board
            while (move > board.MAX_COL || move < 0 || board.checkIfFree(move) == false) {
                while (move < 0 || move > board.MAX_COL) {
                    if (move < 0) {
                        System.out.println("Column cannot be less than 0");
                        System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
                        move = myObj.nextInt();
                    }
                    if (move > board.MAX_COL) {
                        System.out.println("Column cannot be greater than 6");
                        System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
                        move = myObj.nextInt();
                    }
                }
                // Prompts the user to place a piece in another column if chosen column is full of pieces
                while (board.checkIfFree(move) == false) {
                    System.out.println("Column is full");
                    System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
                    move = myObj.nextInt();

                    while (move < 0 || move > board.MAX_COL) {
                        if (move < 0) {
                            System.out.println("Column cannot be less than 0");
                            System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
                            move = myObj.nextInt();
                        }
                        if (move > board.MAX_COL) {
                            System.out.println("Column cannot be greater than 6");
                            System.out.println("Player " + currentPlayer + ", what column do you want to place your marker in?");
                            move = myObj.nextInt();
                        }
                    }
                }
            }
            // Inserts a player's piece in the board if the input is valid
            board.dropToken(currentPlayer, move);

            // Displays the gameboard object with the newly inserted piece.
            System.out.println(board);

            // If the player wins the game it asks if the player wants to play another game or exit the program
            if (board.checkForWin(move)) {
                System.out.println("Player " + currentPlayer + " Won!");
                System.out.println("Would you like to play again? Y/N");
                playAgain = myObj.next().charAt(0);

                if (playAgain == 'n' || playAgain == 'N') {
                    stopPlaying = true;

                } else {
                    System.out.println("How many players are playing?");
                    numPlayers = myObj.nextInt();

                    while (numPlayers > board.MAX_NUM_PLAYERS || numPlayers < board.MIN_NUM_PLAYERS)
                    {
                        if(numPlayers > board.MAX_NUM_PLAYERS)
                        {
                            System.out.println("Enter a number of players less than 10");
                            numPlayers = myObj.nextInt();
                        }
                        else
                        {
                            System.out.println("Enter a number of players more than 1");
                            numPlayers = myObj.nextInt();
                        }


                    }
                    allPlayers = "";
                    spotOfPlayer = -1;


                    for (int i = 0; i < numPlayers; i++) {
                        System.out.println("What is player " + (i + 1) + " marker?");
                        currentPlayer = myObj.next().charAt(0);
                        allPlayers = allPlayers + currentPlayer;

                        for (int j = 0; j < i; j++) {
                            while (currentPlayer == allPlayers.charAt(j)) {
                                System.out.println("Enter a new marker");
                                currentPlayer = myObj.next().charAt(0);
                            }
                        }


                    }


                    currentPlayer = allPlayers.toUpperCase().charAt(0);
                    maxNumPlayer = allPlayers.length() - 1;

                    while (row > board.MAX_ROWS || col > board.MAX_COL || row < board.MIN_SIZE || col < board.MIN_SIZE || numWin > board.MAX_NUM_TO_WIN || numWin < board.MIN_SIZE) {
                        if (row > board.MAX_ROWS) {
                            System.out.println("Enter a number less than 100 for row");
                            row = myObj.nextInt();

                        } else if (col > board.MAX_COL) {
                            System.out.println("Enter a number less than 100 for column");
                            col = myObj.nextInt();
                        } else if (numWin > board.MAX_NUM_TO_WIN) {
                            System.out.println("Enter a number less than 25 for number to win");
                            numWin = myObj.nextInt();
                        }
                        if (row < board.MIN_SIZE) {
                            System.out.println("Enter a number more than 3 for row");
                            row = myObj.nextInt();
                        } else if (col < board.MIN_SIZE) {
                            System.out.println("Enter a number more than 3 for column");
                            col = myObj.nextInt();
                        } else if (numWin < board.MIN_SIZE) {
                            System.out.println("Enter a number more than 3 for number to win");
                            numWin = myObj.nextInt();
                        }
                        if (numWin > row || numWin > col) {
                            System.out.println("Enter a number less than the total row or column");
                            numWin = myObj.nextInt();

                        }

                    }

                    System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
                    choice = myObj.next().charAt(0);

                    if (choice == 'F' || choice == 'f') {
                        choice = 'F';
                    } else {
                        choice = 'M';
                    }


                    if (choice == 'M') {
                        board = new GameBoardMem(row, col, numWin);   // Creates the game board

                    } else {
                        board = new GameBoard(row, col, numWin);   // Creates the game board
                    }

                }

            }
            // If the player ties in the game it asks if the player wants to play another game or exit the program
            if (board.checkTie()) {
                System.out.println("The Game is Tied!");
                System.out.println("Would you like to play again? Y/N");
                playAgain = myObj.next().charAt(0);


                while (playAgain == 'n' || playAgain == 'N' || playAgain == 'y' || playAgain == 'Y') {

                    if (playAgain == 'n' || playAgain == 'N') {
                        stopPlaying = true;

                    } else if (playAgain == 'y' || playAgain == 'Y') {
                        System.out.println("How many players are playing?");
                        numPlayers = myObj.nextInt();
                        allPlayers = "";
                        spotOfPlayer = -1;


                        while (numPlayers > board.MAX_NUM_PLAYERS || numPlayers < board.MIN_NUM_PLAYERS)
                        {
                            if(numPlayers > board.MAX_NUM_PLAYERS)
                            {
                                System.out.println("Enter a number of players less than 10");
                                numPlayers = myObj.nextInt();
                            }
                            else
                            {
                                System.out.println("Enter a number of players more than 1");
                                numPlayers = myObj.nextInt();
                            }


                        }


                        for (int i = 0; i < numPlayers; i++) {
                            System.out.println("What is player " + (i + 1) + " marker?");
                            currentPlayer = myObj.next().charAt(0);
                            allPlayers = allPlayers + currentPlayer;

                            for (int j = 0; j < i; j++) {
                                while (currentPlayer == allPlayers.charAt(j)) {
                                    System.out.println("Enter a new marker");
                                    currentPlayer = myObj.next().charAt(0);
                                }
                            }


                        }

                        currentPlayer = allPlayers.toUpperCase().charAt(0);
                        maxNumPlayer = allPlayers.length() - 1;

                        while (row > board.MAX_ROWS || col > board.MAX_COL || row < board.MIN_SIZE || col < board.MIN_SIZE || numWin > board.MAX_NUM_TO_WIN || numWin < board.MIN_SIZE) {
                            if (row > board.MAX_ROWS) {
                                System.out.println("Enter a number less than 100 for row");
                                row = myObj.nextInt();

                            } else if (col > board.MAX_COL) {
                                System.out.println("Enter a number less than 100 for column");
                                col = myObj.nextInt();
                            } else if (numWin > board.MAX_NUM_TO_WIN) {
                                System.out.println("Enter a number less than 25 for number to win");
                                numWin = myObj.nextInt();
                            }
                            if (row < board.MIN_SIZE) {
                                System.out.println("Enter a number more than 3 for row");
                                row = myObj.nextInt();
                            } else if (col < board.MIN_SIZE) {
                                System.out.println("Enter a number more than 3 for column");
                                col = myObj.nextInt();
                            } else if (numWin < board.MIN_SIZE) {
                                System.out.println("Enter a number more than 3 for number to win");
                                numWin = myObj.nextInt();
                            }
                            if (numWin > row || numWin > col) {
                                System.out.println("Enter a number less than the total row or column");
                                numWin = myObj.nextInt();

                            }

                        }

                        System.out.println("Would you like a Fast Game (F/f) or a Memory Efficient Game (M/m)?");
                        choice = myObj.next().charAt(0);

                        if (choice == 'F' || choice == 'f') {
                            choice = 'F';
                        } else {
                            choice = 'M';
                        }

                        if (choice == 'M') {
                            board = new GameBoardMem(row, col, numWin);   // Creates the game board

                        } else {
                            board = new GameBoard(row, col, numWin);   // Creates the game board
                        }

                    } else {
                        System.out.println("Please Answer with Y/N!");
                        System.out.println("Would you like to play again? Y/N");
                        playAgain = myObj.next().charAt(0);

                    }
                }

            }
            // Switchers the turn to the different player
            else {

                if (spotOfPlayer == maxNumPlayer) {
                    spotOfPlayer = 0;
                    currentPlayer = allPlayers.toUpperCase().charAt(0);
                } else {
                    spotOfPlayer++;
                    currentPlayer = allPlayers.toUpperCase().charAt(spotOfPlayer);
                }
            }

        }


    }

}
