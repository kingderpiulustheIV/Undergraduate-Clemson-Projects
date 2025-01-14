package cpsc2150.extendedConnectX.models;

/*GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE

    Prahalad Gururajan (PravClem) 
    Connor Burkart (crburka)
    Sean Farrell (sfarrellClemosn)
    Parthiv Patel (Parthivp2205)

 */
/**
 * @invariants (row <= MAX_ROWS AND row >= MIN_SIZE) AND (column <= MAX_COL AND column >= MIN_SIZE)
 * @correspondences: Board = position[0..MAX_ROW][0..MAX_COL]
 */
public class GameBoard extends AbsGameBoard implements IGameBoard
{
    Character[][] board;
    int numToWin = 0;
    int numRow = 0;
    int numCol = 0;





    public GameBoard(int r, int c,int numMark)
    {

        board = new Character[r][c];

        for (int i = 0; i < r; i++)
        {
            for(int j = 0; j < c;j++)
            {
                board[i][j] = ' ';
            }
        }
        numRow = r;
        numCol = c;
        numToWin = numMark;
    }


    /**
     * Places the character token 'p' in column 'c'. The token will be placed in the lowest available row in column 'c'
     * @param p The character token to be placed in the column
     * @param c The column where the token should be placed. colum c is intended to be a colum that is not full
     * @pre (c >= MIN_SIZE and c <= MAX_ROWS) AND checkifFree(int c) = true
     * @pre p == 'X' AND p == '0' AND c >= MIN_SIZE and c <= MAX_COLUMNS
     * @post dropToken = [The game board will be updated with the token placed in the lowest
     *  available row of column 'c'. Rest of the board has remained the same] self =#self
     * @post the lowest empty slot in column c = char p.
     */
    public void dropToken(char p, int c)
    {
        if(checkIfFree(c) == true)
        {
            for (int i = 0; i < getNumRows(); i++)
            {
                BoardPosition temp = new BoardPosition(i,c);

                if(whatsAtPos(temp) != ' ')
                {
                    continue;
                }
                else
                {
                    board[i][c] = p;
                    break;
                }
            }


        }
    }


    /**
     * Retrieves the character at the specified position on the game board
     * @param pos is a BoardPosition object that gives the coordinates of a cell.
     * @post whatsAtPos = [Returns char at pos in [pos.getRow][pos.getColumn]] AND self == #self
     * @return Returns The character at position pos, or a blank space character if no marker is there.
     */
    public char whatsAtPos(BoardPosition pos)
    {
        return board[pos.getRow()][pos.getColumn()];
    }
    /**
     * Returns number of rows
     *
     * @return Returns the number of rows.
     * @post getNumRows() = numRows AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    @Override
    public int getNumRows() {
        return numRow;
    }
    /**
     * Returns number of rows
     *
     * @return Returns the number of Columns.
     * @post getNumColumns() = numCol AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    @Override
    public int getNumColumns() {
        return numCol;
    }
    /**
     * Returns number of rows
     *
     * @return Returns the number in a row to win.
     * @post getNumRows() = numToWin AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin
     */
    @Override
    public int getNumToWin() {
        return numToWin;
    }



}
