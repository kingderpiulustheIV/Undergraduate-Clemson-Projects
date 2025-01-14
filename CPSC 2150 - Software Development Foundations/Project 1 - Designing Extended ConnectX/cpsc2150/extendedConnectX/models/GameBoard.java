package cpsc2150.extendedConnectX.models;

/*GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE

    Prahalad Gururajan (PravClem) 
    Connor Burkart (crburka)
    Sean Farrell (sfarrellClemosn)
    Parthiv Patel (Parthivp2205)

 */

public class GameBoard
{
    /**
     * </Description: The constructor of GameBoard, creates GameBoard object
     * @invariant (row <= 8 AND row >= 0) AND (column <= 6 AND column >= 0)
     * @post All positions on the GameBoard are initially set to the empty character ' '.
     * @post The GameBoard instance is now ready for use.
     */
    public GameBoard()
    {

    }
    /**
     * </Description: Checks if a column can accept another token.
     * @param c The column to check.
     * @return [true if the column can accept another token, false otherwise.]
     * @pre [The input column index (c) must be a valid column within the game board]
     * @pre c >= 0 and c <= 6
     * @post [The state of the game board is not modified. Reruns true if the colum is filled 
     *  with pieces otherwise returns false and that the topmost row contains a space for that column.]
     */
    public boolean checkIfFree(int c)
    {
        //returns true if the column can accept another token; false otherwise.
    }

    /**
     * </Description: Places the character token 'p' in column 'c'. The token will be placed in
     * the lowest available row in column 'c'
     * @param p The character token to be placed in the column
     * @param c The column where the token should be placed. colum c is intended to be a colum that is not full
     * @pre (c >= 0 and c <= 6) AND p is a valid token and checkifFree(int c) = true
     * @pre p == 'X' AND p == '0'
     * @post [The game board will be updated with the token placed in the lowest
     *  available row of column 'c'. Rest of the board has remained the same]
     * @post the lowest empty slot in column c = char p.
     */
    public void dropToken(char p, int c)
    {
        //places the character p in column c. The token will be placed in the lowest available row in column c.
    }

    /**
     * </Description: Checks if the last token placed in column 'c' resulted in the player winning the game
     * @param c The column where the last token was placed
     * @pre c >= 0 AND c <= 6
     * @return true if the last token placed in column 'c' resulted in a win, otherwise false
     * @pre The input column index 'c' must be a valid column within the game board
     * @post [Returns true if 5 of the same type of pieces are in a row horizontal or diagonally or vertically] AND self == #self
     */
    public boolean checkForWin(int c)
    {
        /*this function will check to see if the last token placed in column c resulted in the player winning the game.
        If so it will return true, otherwise false. Note: this is not checking the entire board for a win, it is just
        checking if the last token placed results in a win. You may call other methods to complete this method */
    }

    /**
     * </Description: Function that checks if the player has tied the game or not
     * @post [if every position in the board is full and 5 in a row, vertical, horizontal, or diagonal pieces of the same player returns true
     Otherwise, returns false] AND self = #self
     * @return true if games are tied with every colum being populated with none of the same type of pieces being 5 in a row
     * @return horizontally,vertically, and diagonally, otherwise return false
     */
    public boolean checkTie()
    {
        /*this function will check to see if the game has resulted in a tie. A game is tied if there are no free board
        positions remaining. You do not need to check for any potential wins because we can assume that the players
        were checking for win conditions as they played the game. It will return true if the game is tied and
        false otherwise.*/
    }

    /**
     * </Description: Detects if a player has won the game by 5 peaces horizontally next to each-other.
     * @param pos game-board position of current piece being checked
     * @param p the piece object being tested if 5 are horizontally next to each other
     * @pre pos != NULL AND p != ['']
     * @post [function returns true if 5 piece of the same type are 5 in a row horizontally from each other
     *  Otherwise, returns false] AND self = #self
     * @return true if the same type species are 5 in a row horizontally otherwise returns false
     */
    public boolean checkHorizWin(BoardPosition pos, char p)
    {
        /*checks to see if the last token placed (which was placed in position pos by player p) resulted in 5 in
        a row horizontally. Returns true if it does, otherwise false*/
    }

    /**
     * </Description: Checks if there is a vertical win starting from the given position.
     *
     * @param pos The position to start checking from.
     * @param p   The player's token ('X' or 'O')
     * @pre  p shouldn't be a blank space], p != ['']
     * @post [function returns true if 5 piece of the same type are 5 in a row vertically from each other
     * Otherwise, returns false] AND self == #self, 
     * @return true if there are 5 in a row vertically false otherwise
     *
     */
    public boolean checkVertWin(BoardPosition pos, char p)
    {
        /*checks to see if the last token placed (which was placed in position pos by player p) resulted in 5 in a row
        vertically. Returns true if it does, otherwise false*/
    }

    /**
     * </Description: Checks if there is a diagonal win starting from the given position.
     *
     * @param pos The position to start checking from.
     * @param p   The player's token ('X' or 'O')
     * @pre [pos is a valid position on the game board] AND p is not ['']
     * @post [function returns true if 5 piece of the same type are 5 in a row diagonally from each other
     *  Otherwise, returns false] AND self == #self
     * @return true if there are 5 in a row diagonally false otherwise
     */


    public boolean checkDiagWin(BoardPosition pos, char p)
    {
        /*checks to see if the last token placed (which was placed in position pos by player p) resulted in 5 in a row
        diagonally. Returns true if it does, otherwise false Note: there are two diagonals to check*/
    }

    /**
     * </Description: Retrieves the character at the specified position on the game board
     * @param pos is a BoardPosition object that gives the coordinates of a cell.
     * @return the char at the position or " " if the location is empty
     * @return [The character at position pos, or a blank space character if no marker is there.
     * @post [Returns char at pos] AND self == #self
     */
    public char whatsAtPos(BoardPosition pos)
    {
        //returns what is in the GameBoard at position pos If no marker is there, it returns a blank space char.
    }

    /**
     * </Description: Checks if a player's token is at the specified position on the game board.
     * @pre (player != NULL) AND (player == 'X') AND (player == 'O')
     * @pre pos is a valid position on the game board     
     * @param pos    The position in grid
     * @param player The player's token ('X' or 'O')
     * @post [Returns true if the player is at pos] AND self == #self
     * @return true if the player's token is at position pos false otherwise
     */
    public boolean isPlayerAtPos(BoardPosition pos, char player)
    {
        /*returns true if the player is at pos; otherwise, it returns false. Note: this method will be implemented very
        similarly to whatsAtPos, but it's asking a different question. We only know they will be similar because we
        know GameBoard will contain a 2D array. If the data structure were to change in the future,
        these two methods could be radically different.*/
    }

    /**
     * </Description: Returns a string representation of the game board.
     * @post [returns a string that represents the gameboard] AND self = #self
     * @return String with a format that is easy to read in  "<Rows>, <Columns>"
     */
    @Override
    public String toString(){

    }
}
