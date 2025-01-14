import cpsc2150.extendedConnectX.models.BoardPosition;
import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class GameBoardTest {
    @Test
    void checkIfFree()
    {
        IGameBoard board = new GameBoard(3,3,3);

        board.dropToken('X',0);
        board.dropToken('X',0);
        board.dropToken('X',0);

        board.dropToken('X',1);
        board.dropToken('X',1);

        int result = 0;

        if(board.checkIfFree(0))
        {
            result = 1;
        }

        assertEquals(true,board.checkIfFree(1));
        assertEquals(false,board.checkIfFree(0));

    }

    @Test
    void dropToken()
    {

        IGameBoard board = new GameBoard(4,4,3);

        board.dropToken('X',0);
        board.dropToken('O',0);
        board.dropToken('Z',0);

        assertEquals('X',board.whatsAtPos(new BoardPosition(0,0)));
        assertEquals('O',board.whatsAtPos(new BoardPosition(1,0)));
        assertEquals('Z',board.whatsAtPos(new BoardPosition(2,0)));
        assertEquals(' ',board.whatsAtPos(new BoardPosition(3,0)));


    }


    @Test
    void isPlayerAtPos()
    {
        IGameBoard board = new GameBoard(4,4,3);

        board.dropToken('X',0);
        board.dropToken('O',0);
        board.dropToken('Z',0);

        assertEquals(true,board.isPlayerAtPos(new BoardPosition(0,0),'X'));
        assertEquals(true,board.isPlayerAtPos(new BoardPosition(1,0),'O'));
        assertEquals(true,board.isPlayerAtPos(new BoardPosition(2,0),'Z'));
        assertEquals(false,board.isPlayerAtPos(new BoardPosition(3,0),'Z'));


    }

    @Test
    void checkVertWin()
    {
        IGameBoard board = new GameBoard(11,11,5);


        for(int i = 0; i < board.getNumRows();i++)
        {
            for(int j = 0; j < board.getNumColumns();j++)
            {
                if(j != 6) {
                    board.dropToken('X', i);
                }
                else
                {
                    board.dropToken('O', i);

                }
            }
        }

        // Top down
        for(int i = 0; i < board.getNumColumns();i++)
        {
            assertEquals(false,board.checkVertWin(new BoardPosition(0,i),'X'));
        }

        // Top down
        for(int i = 0; i < board.getNumColumns();i++)
        {
            assertEquals(true,board.checkVertWin(new BoardPosition(11,i),'X'));
        }


    }

    @Test
    void checkHorzWin()
    {

        IGameBoard board = new GameBoard(13,13,6);


        for(int i = 0; i < board.getNumRows();i++)
        {
            for(int j = 0; j < board.getNumColumns();j++)
            {
                if(i != 6) {
                    board.dropToken('X', i);
                }
                else
                {
                    board.dropToken('O', i);

                }
            }
        }

        // Left to right
        for(int i = 0; i < board.getNumRows();i++)
        {
            assertEquals(true,board.checkHorizWin(new BoardPosition(i,0),'X'));
        }

        // right to left
        for(int i = 0; i < board.getNumRows();i++)
        {
            assertEquals(true,board.checkHorizWin(new BoardPosition(i,12),'X'));
        }

        // left to right
        for(int i = 0; i < board.getNumRows();i++)
        {
            assertEquals(false,board.checkHorizWin(new BoardPosition(i,6),'X'));
        }

    }

}