package cpsc2150.extendedConnectX.controllers;

import cpsc2150.extendedConnectX.models.*;
import cpsc2150.extendedConnectX.views.*;


/**
 * The controller class will handle communication between our View and our Model ({@link IGameBoard})
 * <p>
 * This is where you will write code
 * <p>
 * You will need to include your your {@link BoardPosition} class, {@link IGameBoard} interface
 * and both of the {@link IGameBoard} implementations from Project 4.
 * If your code was correct you will not need to make any changes to your {@link IGameBoard} implementation class.
 *
 * @version 2.0
 */
public class ConnectXController {

    /**
     * <p>
     * The current game that is being played
     * </p>
     */
    private IGameBoard curGame;

    /**
     * <p>
     * The screen that provides our view
     * </p>
     */
    private ConnectXView screen;

    /**
     * <p>
     * Constant for the maximum number of players.
     * </p>
     */
    public static final int MAX_PLAYERS = 10;
    
    /**
     * <p>
     * The number of players for this game. Note that our player tokens are hard coded.
     * </p>
     */
    private int numPlayers;

    /**
     * <p>
     * This creates a controller for running the Extended ConnectX game
     * </p>
     * 
     * @param model
     *      The board implementation
     * @param view
     *      The screen that is shown
     * @param np
     *      The number of players for this game.
     * 
     * @post [ the controller will respond to actions on the view using the model. ]
     */
    // boolean that is used to see if the game has won or is still in progress
    private boolean gameCondition = false;
    //Accumulator variable used to determine who's turn it is.
    private int turns = 0;
    // represents all players.
    private char[] tokens = new char[] {'X', 'O', 'H', 'L', 'W', 'C', 'V', 'E', 'M', 'Z'};
    public ConnectXController(IGameBoard model, ConnectXView view, int np) {
        this.curGame = model;
        this.screen = view;
        this.numPlayers = np;

        // Some code is needed here.
    }


    /**
     * <p>
     * This processes a button click from the view.
     * </p>
     * 
     * @param col 
     *      The column of the activated button
     * 
     * @post [ will allow the player to place a token in the column if it is not full, otherwise it will display an error
     * and allow them to pick again. Will check for a win as well. If a player wins it will allow for them to play another
     * game hitting any button ]
     */
    public void processButtonClick(int col) {
        // starts a new game if a user ties or wins
        if (gameCondition) {
            newGame();
            gameCondition = false;
        }
        // If a user clicks on a full column prompts the user.
        if(!curGame.checkIfFree(col)) {
            screen.setMessage("Column: " + (col + 1) + " is full!\nPlayer " + tokens[turns] + " place a piece in a unfilled column");
            return;
        }
        else {
            //drops a token in the board.
            curGame.dropToken(tokens[turns], col);
            int row = 0;
            //matches the gui board reprezentation with the state of the board object

            while (row < curGame.getNumRows() && curGame.whatsAtPos(new BoardPosition(row, col)) != ' ') {
                row++;
            }
            screen.setMarker(row - 1, col, tokens[turns]);
            // If a player wins prompts the user to start a new game.
            if (curGame.checkForWin(col)) {
                 screen.setMessage("Player " + tokens[turns] + " wins! Click any button to start a new game.");
                 gameCondition =true;
                 return;
            }

            // If a player wins prompts the user to start a new game.
            else if (curGame.checkTie()) {
                screen.setMessage("The game is tied! Click a button to start a new game!");
                gameCondition = true;

            }
            else {
                // Changes to the next players turn
                turns = (turns + 1) % numPlayers;
                screen.setMessage("It is " + tokens[turns] + "'s turn. ");
            }
        }
    }



    /**
     * <p>
     * This method will start a new game by returning to the setup screen and controller
     * </p>
     * 
     * @post [ a new game gets started ]
     */
    private void newGame() {
        //close the current screen
        screen.dispose();
        
        //start back at the set up menu
        SetupView screen = new SetupView();
        SetupController controller = new SetupController(screen);
        screen.registerObserver(controller);
    }
}