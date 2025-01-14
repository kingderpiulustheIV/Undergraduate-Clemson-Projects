package cpsc2150.extendedConnectX.models;
import java.util.*;


/**
 * @invariant MIN_SIZE <= numRow <= MAX_ROWS AND MIN_SIZE <= numCol <= MAX_COL AND MIN_SIZE <= numToWin <= NUM_TO_WIN
 * @correspondence board = new HashMap<Character,List<BoardPosition>>();
 */

public class GameBoardMem extends AbsGameBoard implements IGameBoard
{

    private Map<Character, List<BoardPosition>> board;
    private int numToWin = 0;

    private int numRow = 0;
    private int numCol = 0;


    /**
     * This is constructor which will taken in r,c, numMark as parameters. It will assign values of passes on parameter
     * to numRow, numCol and numToWin. It will initialize the gameBoard using HashMap.
     *
     * @param r number of rows in game board
     * @param c number of columns in game board
     * @param numMark  number of mark/token to win game
     * @post nunRow = r AND numCol = c AND numToWin = numMark AND
     *            board =  new HashMap<>()
     *
     */
    public GameBoardMem(int r , int c , int numMark)
    {
        board = new HashMap<Character,List<BoardPosition>>();
        numToWin = numMark;
        numRow = r;
        numCol = c;

    }

    // X   : (1,2)
    // O    :
    //

    /**
     * @pre c >= MIN_SIZE and c <= MAX_COLUMNS AND [p is a valid token and checkifFree(int c) = true]
     * @param p The character token to be placed in the column
     * @param c The column where the token should be placed. colum c is intended to be a colum that is not full
     * @post dropToken = [The game board will be updated with the token placed in the lowest
     *       available row of column 'c'. Rest of the board has remained the same] board = #board.
     */
    @Override
    public void dropToken(char p, int c)
    {

        List<BoardPosition> temp = board.get(p);


        if(checkIfFree(c) == true)
        {
            for (int i = 0; i < getNumRows(); i++)
            {
                BoardPosition bp = new BoardPosition(i,c);

                if(whatsAtPos(bp) != ' ')
                {
                    continue;
                }
                else
                {
                    if(board.containsKey(p))
                    {
                        temp.add(bp);
                        board.put(p,temp);
                        return;
                    }
                    else
                    {
                        temp = new ArrayList<BoardPosition>();
                        temp.add(bp);
                        board.put(p,temp);
                        return;

                    }

                }
            }


        }





    }

    /**
     *
     *
     * @pre [pos should be valid within the board] //check this.
     * @param pos is a BoardPosition object that gives the coordinates of a cell.
     * @post whatsAtPos = key [character present at a particular position i gameboard]
     * @return [Returns key as character of the pos position] AND board = #board
     *
     */
    @Override
    public char whatsAtPos(BoardPosition pos)
    {
        for(Map.Entry<Character,List<BoardPosition>> entry: board.entrySet())
        {
            for(int i = 0; i < entry.getValue().size(); i++)
            {
                if(pos.equals(entry.getValue().get(i)))
                {
                    return entry.getKey();
                }

            }

        }


        return ' ';


    }

    /**
     * Method returns the number of rows present in a game board
     * @return Return's numRow [number of rows]
     * @post getNumRows() = numRows AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin AND board = #board
     */
    @Override
    public int getNumRows() {
        return numRow;
    }

    /**
     * Method returns the number of columns present in a game board.
     * @return Returns numCol,number of columns in a game board.
     * @post getNumColumns() = numCol AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin board = #board.
     */
    @Override
    public int getNumColumns() {
        return numCol;
    }

    /**
     * Method returns numner of wins required to win the game.
     * @return Returns numToWin number of token required to win game.
     * @post getNumToWin() = numToWin AND numRows =#numRows AND numCol = #numCol AND numToWin = #numToWin AND board = #board
     */
    @Override
    public int getNumToWin() {
        return numToWin;
    }
}
