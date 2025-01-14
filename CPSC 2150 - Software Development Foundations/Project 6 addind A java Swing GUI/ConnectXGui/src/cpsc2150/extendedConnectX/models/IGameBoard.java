package cpsc2150.extendedConnectX.models;

/**
 * This is an interface for game board. Game board is a 2-D array board of blank spaces.
 * The following interface contains some of the methods which are secondary methods implemented
 * using the primary methods. This game is based on player input makers:
 * 'X', or 'O', or 'H', or 'L', or 'W', or 'C', or 'V', or 'E', or 'M', or 'Z'.
 * if they have consecutive five makers in any direction, they win.
 *
 * Initialization ensure: Game Board is created with an array of balcnk spaces of size: getNumRows() * getNumColumns
 *
 * Defines:
 numRow = Z;
 numCol = Z;
 numToWin = Z;
 * Constraints :
 *         MIN_SIZE <= rows <= MAX_ROWS
 *         MIN_SIZE <= cols <= MAX_COL
 *         MIN_SIZE <= toWin <= NUM_TO_WIN
 */
public interface IGameBoard
{
    public static final int MIN_SIZE = 3;
    public static final int MAX_ROWS = 100;
    public static final int MAX_COL = 100;
    public static final int MIN_NUM_TO_WIN = 3;

    public static final int MAX_NUM_TO_WIN = 25;

    public static final int MAX_NUM_PLAYERS = 10;
    public static final int MIN_NUM_PLAYERS = 2;




    /**
     * Places the character token 'p' in column 'c'. The token will be placed in the lowest available row in column 'c'
     * @param p The character token to be placed in the column
     * @param c The column where the token should be placed. colum c is intended to be a colum that is not full
     * @pre (c >= MIN_SIZE and c <= MAX_ROWS) AND p is a valid token and checkifFree(int c) = true
     * @pre' AND c >= MIN_SIZE and c <= MAX_COLUMNS
     * @post dropToken = [The game board will be updated with the token placed in the lowest
     *  available row of column 'c'. Rest of the board has remained the same] self =#self
     * @post the lowest empty slot in column c = char p.
     */
    public void dropToken(char p, int c);

    /**
     * Retrieves the character at the specified position on the game board
     * @param pos is a BoardPosition object that gives the coordinates of a cell.
     * @post whatsAtPos = [Returns char at pos in [pos.getRow][pos.getColumn]] AND self == #self
     * @return Returns The character at position pos, or a blank space character if no marker is there.
     */
    public char whatsAtPos(BoardPosition pos);

    /**
     * Checks if a player's token is at the specified position on the game board.
     * @pre (player != NULL) AND (player == 'X') AND (player == 'O')
     * @pre pos is a valid position on the game board
     * @param pos    The position in grid
     * @param player The player's token ('X', or 'O', or 'H', or 'L', or 'W', or 'C', or 'V', or 'E', or 'M', or 'Z')
     * @post isPlayerAtPos = [Returns true if the player is at pos] AND self == #self
     * @return Returns true if the player's token is at position pos false otherwise
     */
    public default boolean isPlayerAtPos(BoardPosition pos, char player)
    {
        if(whatsAtPos(pos) == player)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Checks if a column can accept another token.
     * @param c The column to check.
     * @pre c >= MIN_SIZE and c <= MAX_COL
     * @post checkIfFree = [Returns true if the column is filled with pieces otherwise returns false] AND self = #self
     * @return Returns true if the column can accept another token, false otherwise.
     */
    public default boolean checkIfFree(int c) {
        BoardPosition temp = new BoardPosition(getNumRows()-1,c);

        if(whatsAtPos(temp) == ' ')
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    /**
     * Checks if the last token placed in column 'c' resulted in the player winning the game
     * @param c The column where the last token was placed
     * @pre c >= MIN_SIZE AND c <= MAX_COL
     * @pre The input column index 'c' must be a valid column within the game board
     * @post checkForWin = [Returns true if 5 of the same type of pieces are in a row horizontal or diagonally or vertically] AND self == #self
     * @return Returns true if the last token placed in column 'c' resulted in a win, otherwise false
     */
    public default boolean checkForWin(int c)
    {
       // Loops to make sure it doesn't account unfilled spaces in the board to calculate a win
        for(int r = 0; r < getNumRows(); r++) {
            BoardPosition pos = new BoardPosition(r, c);
            char token = whatsAtPos(pos);
            if (token == ' ') {
                continue;
            }
            // Returns true if there are a vertical win or a horizontal win or a diagonal win.
            if (checkVertWin(pos, token) || checkHorizWin(pos, token) || checkDiagWin(pos, token)) {
            return true;
            }
        }
        // Returns false if the game is still being played or if there is a tie
        return false;
    }

    /**
     * Checks if there is a vertical win starting from the given position.
     *
     * @param pos The position to start checking from.
     * @param p  = [ ('X', or 'O', or 'H', or 'L', or 'W', or 'C', or 'V', or 'E', or 'M', or 'Z')]
     * @post checkVertWin = [returns true if 5 piece of the same type are 5 in a row vertically from each other
     * Otherwise, returns false] AND self == #self,
     * @return Returns true if there are numToWin many in a row vertically false otherwise
     *
     */
    public default boolean checkVertWin(BoardPosition pos, char p)  {
        // accumulator of how many pieces in a vertical row
        int count = 0;
        // loops through the column verifying the game pieces
        while (pos.getRow() >= 0 && count < getNumToWin()) {

            // if pieces are not in a row returns false
            if (whatsAtPos(pos) != p) {
                return false;
            }
            // updates the position of the next piece to be checked
            pos = new BoardPosition(pos.getRow() - 1, pos.getColumn());
            //accumulates how many pieces in a row
            count++;
        }
        // Returns true if count equals a win
        if (count == getNumToWin()) {
            return true;
        }
        return false;

    }

    /**
     * Detects if a player has won the game by 5 peaces horizontally next to each-other.
     * @param pos game-board position of current piece being checked
     * @param p the piece object being tested if 5 are horizontally next to each other
     * @pre  MIN_SIZE <= pos.getRow() < getNumRows() AND
     *      MIN_SIZE <= pos.getColumn() < getNumColumns()
     * @post checkHorizWin = [returns true if 5 piece of the same type are numToWin many in a row horizontally from each other  Otherwise, returns false] AND self = #self
     * @return Returns true if the same type species are 5 in a row horizontally otherwise returns false
     */
    public default boolean checkHorizWin(BoardPosition pos, char p)
    {
        //accumulator how many peices are in a row horzontaly
        int count = 1;

        // gets position of a column to be checked for a horizontal win
        int column = pos.getColumn() - 1;
        // adds to the accumulator if a piece is the same to the right of the piece
        while (column >= 0 && count < getNumToWin() && whatsAtPos(pos) == whatsAtPos(new BoardPosition(pos.getRow(), column))) {

            count++;
            column--;
        }

        column = pos.getColumn() + 1;
        // adds to the accumulator if a piece is the same to the left of the piece.
        while (column < getNumColumns() && count < getNumToWin() && whatsAtPos(pos) == whatsAtPos(new BoardPosition(pos.getRow(), column))) {

            count++;
            column++;
        }
        //Returns true if there as much or more pieces in a row horizontally needed to win
        return count >= getNumToWin();

    }

    /**
     * Checks if there is a diagonal win starting from the given position.
     *
     * @param pos The position to start checking from.
     * @param p   The player's token ('X', or 'O', or 'H', or 'L', or 'W', or 'C', or 'V', or 'E', or 'M', or 'Z')
     * @pre [pos is a valid position on the game board]
     * @post checkDiadWin = [returns true if  piece of the same type are numToWin many in a row diagonally from each other
     *  Otherwise, returns false] AND self == #self
     * @return Returns true if there are 5 in a row diagonally false otherwise
     */
    public default boolean checkDiagWin(BoardPosition pos, char p)
{
    // Accumulator of how many peaces diagonally adjacent to each other are the same.
    int count = 1;

    // Checks to see if there is a positive slope diagonal win from bottem left to top right.
    BoardPosition currentPos = new BoardPosition(pos.getRow() + 1,
            pos.getColumn() + 1);
    while (currentPos.getRow() < getNumRows() && currentPos.getColumn() < getNumColumns()
            && whatsAtPos(currentPos) == p) {

        count++;
        currentPos = new BoardPosition(currentPos.getRow() + 1,
                currentPos.getColumn() + 1);
    }
    if (count == getNumToWin()) {
        return true;
    }

    // Checks to see if there is a positive slope diagonal win from top right to bottem left.
    currentPos = new BoardPosition(pos.getRow() - 1, pos.getColumn() - 1);
    while (currentPos.getRow() >= 0 && currentPos.getColumn() >= 0
            && whatsAtPos(currentPos) == p) {

        count++;
        currentPos = new BoardPosition(currentPos.getRow() - 1,
                currentPos.getColumn() - 1);
    }
    if (count == getNumToWin()) {
        return true;
    }

    count = 1;
    // Checks to see if there is a negative slope diagonal win from top left to bottom right.
    currentPos = new BoardPosition(pos.getRow() + 1, pos.getColumn() - 1);
    while (currentPos.getRow() < getNumRows() && currentPos.getColumn() >= 0
            && whatsAtPos(currentPos) == p) {

        count++;
        currentPos = new BoardPosition(currentPos.getRow() + 1,
                currentPos.getColumn() - 1);
    }
    if (count == getNumToWin()) {
        return true;
    }

    // Checks to see if there is a negative slope diagonal win from bottom right to top Left.
    currentPos = new BoardPosition(pos.getRow() - 1, pos.getColumn() + 1);
    while (currentPos.getRow() >= 0 && currentPos.getColumn() < getNumColumns()
            && whatsAtPos(currentPos) == p) {

        count++;
        currentPos = new BoardPosition(currentPos.getRow() - 1,
                currentPos.getColumn() + 1);
    }

    // Returns true if there are enough peices diagonally next to eachother for a win
    return count >= getNumToWin();

}

    /**
     *
     * Function that checks if the player has tied the game or not by using checkIfFree function.
     * @pre checkForWin() != true
     * @post checkTie = [returns true if board is full and there are no wins, Otherwise, returns false] AND self = #self
     * @return Returns true if games are tied with every colum being populated with none of the same type of pieces being 5 in a row; horizontally,vertically, and diagonally, otherwise return false
     */
    public default boolean checkTie()
    {
        // Checks if every column in the board is full for a tie
        for(int i = 0; i < getNumColumns();i++)
        {
            if(checkIfFree(i) == true)
            {
                // Returns false if a column is not full
                return false;

            }
        }
        // Returns true if all columns are ful;
        return true;


    }
    /**
     * Returns number of rows
     *
     * @return Returns the number of rows.
     * @post getNumRows() = numRows AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    public int getNumRows();
    /**
     * Returns number of rows
     *
     * @return Returns the number of Columns.
     * @post getNumColumns() = numCol AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    public int getNumColumns();
    /**
     * Returns number of rows
     *
     * @return Returns the number in a row to win.
     * @post getNumToWin() = numToWin AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    public int getNumToWin();
}