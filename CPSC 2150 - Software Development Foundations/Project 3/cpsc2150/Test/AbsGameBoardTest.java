import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class AbsGameBoardTest {

    @Test
    void testToString()
    {
        IGameBoard board = new GameBoardMem(20,20,3);

        board.dropToken('X',0);



        System.out.println(board.toString());

    }
}