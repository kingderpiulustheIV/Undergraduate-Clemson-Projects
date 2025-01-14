package cpsc2150.extendedConnectX.tests;

import cpsc2150.extendedConnectX.models.BoardPosition;
import cpsc2150.extendedConnectX.models.GameBoard;
import cpsc2150.extendedConnectX.models.GameBoardMem;
import cpsc2150.extendedConnectX.models.IGameBoard;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

//
class TestGameBoard
{

    private IGameBoard InitializeGameBoard(int row, int column, int numTokens) {
        IGameBoard gb = new GameBoard(row, column, numTokens);
        return gb;
    }
    private String expOutput(char[][] outputArray, IGameBoard board) {
        String output = "|";
        for (int i = 0; i < board.getNumColumns(); i++) {
            if (i < 10) {
                output += " " + i + "|";
            } else {
                output += i + "|";
            }
        }
        output += "\n";
        for (int row = board.getNumRows() - 1; row >= 0; row--) {
            for (int column = 0; column < board.getNumColumns(); column++) {
                output += "|" + outputArray[row][column] + " ";
            }
            output += "|" + "\n";
        }
        return output;
    }

    @Test
    public void test_constructor_min_values() {
        int row = 3, column = 3, numTokens = 3;
        char[][] outputArray;
        IGameBoard gb = InitializeGameBoard(row, column, numTokens);
        outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        assertEquals(gb.toString(), expOutput);
    }

    @Test
    public void test_constructor_max_values() {
        int row = 100, column = 100, numTokens = 25;
        char[][] outputArray;
        IGameBoard gb = InitializeGameBoard(row, column, numTokens);
        outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        String expectedOutput = expOutput(outputArray, gb);
        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        assertEquals(gb.toString(), expectedOutput);
    }

    @Test
    public void test_constructor_random_values() {
        int row = 27, column = 55, numTokens = 15;
        char[][] outputArray;
        IGameBoard gb = InitializeGameBoard(row, column, numTokens);
        outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        String expectedOutput = expOutput(outputArray, gb);
        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        assertEquals(gb.toString(), expectedOutput);
    }

    @Test
    void checkVertWinBottomTrue()
    {

        int row = 11, column = 11, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(j != 6) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(j != 6) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkVertWin( new BoardPosition(10,0), 'X'));


    }

    @Test
    void checkVertWinBottomFlase()
    {

        int row = 11, column = 11, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(j != 3) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(j != 3) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkVertWin(new BoardPosition(0,0),'X'));


    }

    @Test
    void checkVertWinTopFalse()
    {

        int row = 11, column = 11, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(j != 6) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(j != 6) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkVertWin(new BoardPosition(0,0),'X'));


    }

    @Test
    void checkVertWinTopRightTrue()
    {

        int row = 11, column = 11, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(j != 3) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(j != 3) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkVertWin(new BoardPosition(10,10),'X'));


    }

    @Test
    void checkHorzWinBotLeftTrue()
    {

        int row = 11, column = 11, numTokens = 6;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i != 6) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i != 6) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkHorizWin(new BoardPosition(10,0),'X'));




    }

    @Test
    void checkHorzWinTopRightTrue()
    {

        int row = 11, column = 11, numTokens = 6;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i != 4) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i != 4) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkHorizWin(new BoardPosition(0,10),'X'));




    }

    @Test
    void checkHorzWinBotRightFalse()
    {

        int row = 11, column = 11, numTokens = 6;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i != 7) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i != 7) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkHorizWin(new BoardPosition(0,10),'X'));


    }

    @Test
    void checkHorzWinTopLeftTrue()
    {

        int row = 11, column = 11, numTokens = 6;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i != 7) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i != 7) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkHorizWin(new BoardPosition(0,2),'X'));


    }

    @Test
    void checkIfFreeFalse()
    {

        int row = 5, column = 5, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(j != 0) {
                    gb.dropToken('X', i);
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(j != 0) {
                    outputArray[j][i] = 'X';
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkIfFree(3));


    }

    @Test
    void checkIfFreeTrue()
    {

        int row = 5, column = 5, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == 0)
                {
                    continue;
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == 0)
                {
                    continue;
                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkIfFree(0));


    }


    @Test
    void checkIfFree99True()
    {

        int row = 5, column = 5, numTokens = 5;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == 4 && j == 4)
                {
                    continue;
                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }

        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == 4 && j == 4)
                {
                    continue;
                }
                else
                {
                    outputArray[j][i] = 'O';

                }


            }
        }

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkIfFree(4));


    }


    @Test
    void checkWhatsAtPos_checks_False() {
        // Tests checkWhatsAtPos if a position of a populated 'X' game piece at bottom left of the board checks for 'O'
        // If it is false (true value of the position  'X') test passes
        IGameBoard gb = InitializeGameBoard(13, 13, 6);
        char[][] outputArray = new char[13][13];
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                outputArray[i][j] = ' ';
            }
        }


        gb.dropToken('X', 0);
        outputArray[0][0] = 'X';
        assertNotEquals('O', gb.whatsAtPos(new BoardPosition(0, 0)));
    }

    @Test
    void checkWhatsAtPos_checks_true() {
        IGameBoard gb = InitializeGameBoard(13, 13, 6);
        char[][] outputArray = new char[13][13];
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                outputArray[i][j] = ' ';
            }
        }

        gb.dropToken('X', 12);
        outputArray[0][12] = 'X';
        assertEquals('X', gb.whatsAtPos(new BoardPosition(0, 12)));
    }
    @Test
    void checkWhatsAtPos_empty_position() {
        // Tests checkWhatsAtPos if a position of the game-board top left are empty.
        IGameBoard gb = InitializeGameBoard(13, 13, 6);
        char[][] outputArray = new char[13][13];
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                outputArray[i][j] = ' ';
            }
        }
        assertEquals(' ', gb.whatsAtPos(new BoardPosition(12, 12)));
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
    }
    @Test
    void checkWhatsAtPos_top_of_inserted_column() {
        // Fills the most right colum up with all 'X' peaces then checks if the top piece on the column is 'X'.
        IGameBoard gb = InitializeGameBoard(13, 13, 6);
        char[][] outputArray = new char[13][13];
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 13; j++) {
                outputArray[i][j] = ' ';
            }
        }
        for (int k = 0; k < 13; k++) {
            gb.dropToken('X', 0);
            outputArray[k][0] = 'X';
        }
        assertEquals('X', gb.whatsAtPos(new BoardPosition(12, 0)));
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);


    }

    @Test
    void checksWhatsAtPos_rightmost_position_inserted_row() {
        // Creates a new game board 13 rows by 13 columns.
        // Then fills most bottom row up with all 'O' peaces then checks if the rightmost piece in the row is 'O'.
        IGameBoard gb = InitializeGameBoard(13, 13, 6);
        char[][] outputArray = new char[13][13];
        for(int i = 0; i < 13; i++ ) {
            for(int j = 0; j < 13; j++) {
                outputArray[i][j] = ' ';
            }
        }
        for(int k = 0; k < 13; k++) {
            gb.dropToken('O', k);
            outputArray[0][k] = 'O';
        }

        assertEquals('O', gb.whatsAtPos(new BoardPosition(0,12)));
        String expOutputTwo = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutputTwo);

    }
    @Test
    void checkTie_full_board_no_wins() {
        /* tests check() with a scenario where the game-board is populated,
         with not enough game pieces in a row to declare a winner.
        */
        IGameBoard gb = InitializeGameBoard(3, 3, 3);
        char[][] outputArray = new char[3][3];
        gb.dropToken('O', 0);
        outputArray[0][0] = 'O';
        gb.dropToken('X', 1);
        outputArray[0][1] = 'X';
        gb.dropToken('X', 2);
        outputArray[0][2] = 'X';
        gb.dropToken('X', 0);
        outputArray[1][0] = 'X';
        gb.dropToken('O', 1);
        outputArray[1][1] = 'O';
        gb.dropToken('O', 2);
        outputArray[1][2] = 'O';
        gb.dropToken('O', 0);
        outputArray[2][0] = 'O';
        gb.dropToken('O', 1);
        outputArray[2][1] = 'O';
        gb.dropToken('X', 2);
        outputArray[2][2] = 'X';
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true, gb.checkTie());
    }
    @Test
    void checkTie_partially_filled_board_with_win() {
        /* tests check() with a scenario where the game-board is not fully populated,
        with enough game pieces in a row to declare a winner.
        */
        IGameBoard gbTwo = InitializeGameBoard(3, 3, 3);
        char[][] outputArrayTwo = new char[3][3];
        gbTwo.dropToken('O', 0);
        outputArrayTwo[0][0] = 'O';
        gbTwo.dropToken('X', 1);
        outputArrayTwo[0][1] = 'X';
        gbTwo.dropToken('X', 2);
        outputArrayTwo[0][2] = 'X';
        gbTwo.dropToken('X', 0);
        outputArrayTwo[1][0] = 'X';
        gbTwo.dropToken('O', 1);
        outputArrayTwo[1][1] = 'O';
        gbTwo.dropToken('O', 2);
        outputArrayTwo[1][2] = 'O';
        gbTwo.dropToken('O', 2);
        outputArrayTwo[2][0] = ' ';
        outputArrayTwo[2][1] = ' ';
        outputArrayTwo[2][2] = 'O';

        String expOutputTwo = expOutput(outputArrayTwo, gbTwo);
        assertEquals(gbTwo.toString(), expOutputTwo);
        assertEquals(false, gbTwo.checkTie());
    }
    @Test
    void checkTie_empty_board() {
        /* tests check() with a scenario where the game-board is empty.
         */
        IGameBoard gbThree = InitializeGameBoard(3, 3, 3);
        char[][] outputArrayThree = new char[3][3];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                outputArrayThree[i][j] = ' ';
            }
        }
        String expOutputThree = expOutput(outputArrayThree, gbThree);
        assertEquals(gbThree.toString(), expOutputThree);
        assertEquals(false, gbThree.checkTie());
    }

    @Test
    void checkTie_partaily_filled_board_with_no_win() {


        /* tests check() with a scenario where the game-board is not fully populated,
        with enough game pieces in a row to declare a winner.
        */
        IGameBoard gbFour = new GameBoardMem(3, 3, 3);
        char[][] outputArrayFour = new char[3][3];
        gbFour.dropToken('O', 0);
        outputArrayFour[0][0] = 'O';
        gbFour.dropToken('X', 1);
        outputArrayFour[0][1] = 'X';
        gbFour.dropToken('X', 2);
        outputArrayFour[0][2] = 'X';
        gbFour.dropToken('X', 0);
        outputArrayFour[1][0] = 'X';
        gbFour.dropToken('O', 1);
        outputArrayFour[1][1] = 'O';
        gbFour.dropToken('O', 2);
        outputArrayFour[1][2] = 'O';
        gbFour.dropToken('O', 0);
        outputArrayFour[2][0] = 'O';
        outputArrayFour[2][1] = ' ';
        outputArrayFour[2][2] = ' ';
        String expOutputFour = expOutput(outputArrayFour, gbFour);
        assertEquals(gbFour.toString(), expOutputFour);
        assertEquals(false, gbFour.checkTie());

    }

    @Test
    void checkDiagtWinLeftToRightBotTrue()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 0;
        int tempy = 0;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == tempx && j == tempy)
                {


                    if(tempx == 4)
                    {
                        gb.dropToken('O', i);
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        gb.dropToken('X', i);

                    }

                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }
        tempx = 0;
        tempy = 0;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(tempx == 4)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        outputArray[j][i] = 'X';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkDiagWin(new BoardPosition(0,0),'X'));


    }

    @Test
    void checkDiagtWinLeftToRightFalse()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 0;
        int tempy = 0;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == tempx && j == tempy)
                {


                    if(tempx == 3)
                    {
                        gb.dropToken('O', i);
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        gb.dropToken('X', i);

                    }

                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }
        tempx = 0;
        tempy = 0;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(tempx == 3)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        outputArray[j][i] = 'X';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkDiagWin(new BoardPosition(0,0),'X'));


    }

    @Test
    void checkDiagtWinLeftToRightTopRightTrue()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 3;
        int tempy = 3;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == tempx && j == tempy)
                {


                    if(tempx == 7)
                    {
                        gb.dropToken('O', i);
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        gb.dropToken('X', i);

                    }

                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }
        tempx = 3;
        tempy = 3;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(tempx == 7)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else
                    {
                        tempx++;
                        tempy++;
                        outputArray[j][i] = 'X';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkDiagWin(new BoardPosition(0,0),'X'));


    }

    @Test
    void checkDiagtWinRightToLeftBotRightTrue()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 3;
        int tempy = 3;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(i == tempx && j == tempy)
                {


                    if(tempx == 0 )
                    {
                        gb.dropToken('O', i);
                    }
                    else
                    {
                        tempx++;
                        tempy--;
                        gb.dropToken('X', i);

                    }

                }
                else
                {
                    gb.dropToken('O', i);

                }
            }
        }
        tempx = 3;
        tempy = 3;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(tempx == 0)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else
                    {
                        tempx++;
                        tempy--;
                        outputArray[j][i] = 'X';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkDiagWin(new BoardPosition(0,6),'X'));


    }

    @Test
    void checkDiagtWinRightToLeftTopLeftTrue()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 0;
        int tempy = 6;
        int count = 0;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(count == 4)
                {
                    gb.dropToken('O', i);

                }
                else if(i == tempx && j == tempy)
                {
                    gb.dropToken('X', i);
                    tempy--;
                    tempx++;
                    count++;

                }
                else
                {
                    gb.dropToken('O', i);

                }



            }
        }

        tempx = 0;
        tempy = 6;
        count = 0;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(count == 4)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else if(i == tempx && j == tempy)
                    {
                        outputArray[j][i] = 'X';

                        tempy--;
                        tempx++;
                        count++;
                    }
                    else
                    {
                        outputArray[j][i] = 'O';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }

        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkDiagWin(new BoardPosition(5,1),'X'));


    }

    @Test
    void checkDiagtWinRightToLeftFalse()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 0;
        int tempy = 6;
        int count = 0;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(count == 3)
                {
                    gb.dropToken('O', i);

                }
                else if(i == tempx && j == tempy)
                {
                    gb.dropToken('X', i);
                    tempy--;
                    tempx++;
                    count++;

                }
                else
                {
                    gb.dropToken('O', i);

                }



            }
        }

        tempx = 0;
        tempy = 6;
        count = 0;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(count == 3)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else if(i == tempx && j == tempy)
                    {
                        outputArray[j][i] = 'X';

                        tempy--;
                        tempx++;
                        count++;
                    }
                    else
                    {
                        outputArray[j][i] = 'O';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(false,gb.checkDiagWin(new BoardPosition(5,1),'X'));


    }

    @Test
    void checkDiagtWinRightToLeftBotLeftTrue()
    {

        int row = 7, column = 7, numTokens = 4;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        int tempx = 0;
        int tempy = 6;
        int count = 0;
        for(int i = 0; i < gb.getNumRows();i++)
        {
            for(int j = 0; j < gb.getNumColumns();j++)
            {
                if(count == 7)
                {
                    gb.dropToken('O', i);

                }
                else if(i == tempx && j == tempy)
                {
                    gb.dropToken('X', i);
                    tempy--;
                    tempx++;
                    count++;

                }
                else
                {
                    gb.dropToken('O', i);

                }



            }
        }

        tempx = 0;
        tempy = 6;
        count = 0;
        for(int i = 0; i < row;i++)
        {
            for(int j = 0; j < column;j++)
            {
                if(i == tempx && j == tempy)
                {
                    if(count == 7)
                    {
                        outputArray[j][i] = 'O';
                    }
                    else if(i == tempx && j == tempy)
                    {
                        outputArray[j][i] = 'X';

                        tempy--;
                        tempx++;
                        count++;
                    }
                    else
                    {
                        outputArray[j][i] = 'O';

                    }

                }
                else
                {
                    outputArray[j][i] = 'O';

                }
            }
        }


        assertEquals(gb.getNumRows(), row);
        assertEquals(gb.getNumColumns(), column);
        assertEquals(gb.getNumToWin(), numTokens);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals(true,gb.checkDiagWin(new BoardPosition(0,6),'X'));


    }

    // test isPlayerAtPos should be false on an empty spot on an empty board
    @Test
    public void isPlayerAtPos_false_empty_spot_empty_board()
    {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }

        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        BoardPosition pos = new BoardPosition(0, 0);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertFalse(gb.isPlayerAtPos(pos, 'X'));
    }
    // test isPlayerAtPos on a board with only one char on the board
    @Test
    public void isPlayerAtPos_one_char_on_board() {

        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        gb.dropToken('O', 4);
        outputArray[0][4] = 'O';
        BoardPosition pos = new BoardPosition(0, 4);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertTrue(gb.isPlayerAtPos(pos, 'O'));
    }
    // test isPlayerAtPos on a board with only one full row
    @Test
    public void isPlayerAtPos_one_filled_row() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);



        for (int i = 0; i < column; i++)
            gb.dropToken('X', i);
        for (int i = 0; i < column; i++)
            outputArray[0][i] = 'X';

        BoardPosition pos = new BoardPosition(0, 1);

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertTrue(gb.isPlayerAtPos(pos, 'X'));
    }
    // test isPlayerAtPos on an almost full board with one empty space
    @Test
    public void isPlayerAtPos_false_almost_full_board_empty_space() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for (int j = 0; j < column-1; j++)
            for (int i = 0; i < column; i++)
                gb.dropToken('X', i);
        for (int i = 0; i < column-1; i++)
            gb.dropToken('X', i);

        for (int j = 0; j < column-1; j++)
            for (int i = 0; i < column; i++)
                outputArray[i][j] = 'X';
        for (int i = 0; i < column-1; i++)
            outputArray[i][column-1] = 'X';
        BoardPosition pos = new BoardPosition(column-1, column-1);

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertFalse(gb.isPlayerAtPos(pos, 'O'));
    }
    // test isPlayerAtPos on an almost full board with one empty space
    @Test
    public void isPlayerAtPos_full_board() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);


        for (int i = 0; i < column; i++)
            for (int j = 0; j < column; j++)
                gb.dropToken('X', j);

        for (int i = 0; i < column; i++)
            for (int j = 0; j < column; j++)
                outputArray[i][j] = 'X';



        BoardPosition pos = new BoardPosition(column-1, column-1);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertTrue(gb.isPlayerAtPos(pos, 'X'));
    }
    // test dropToken on empty board
    @Test
    public void dropToken_on_empty_board() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        gb.dropToken('X', 0);
        outputArray[0][0] = 'X';

        BoardPosition pos = new BoardPosition(0, 0);

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals('X', gb.whatsAtPos(pos));
    }
    // test dropToken on partly filled column
    @Test
    public void dropToken_in_partly_filled_column() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        gb.dropToken('O', 0);
        gb.dropToken('X', 0);
        outputArray[0][0] = 'O';
        outputArray[1][0] = 'X';
        BoardPosition pos = new BoardPosition(1, 0);


        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals('X', gb.whatsAtPos(pos));
    }
    // test dropToken to fill up a column completely
    @Test
    public void dropToken_fill_up_column() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for (int i = 0; i < column-1; i++)
            gb.dropToken('O', 0);
        gb.dropToken('X', 0);

        for (int i = 0; i < column-1; i++)
            outputArray[i][0] = 'O';
        outputArray[column-1][0] = 'X';

        BoardPosition pos = new BoardPosition(column-1, 0);

        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals('X', gb.whatsAtPos(pos));
    }
    // tests dropToken to fill up a row completely
    @Test
    public void dropToken_to_fill_up_row() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for (int i = 0; i < column-1; i++)
            gb.dropToken('O', i);
        gb.dropToken('X', 4);

        for (int i = 0; i < column-1; i++)
            outputArray[0][i] = 'O';
        outputArray[0][column-1] = 'X';

        BoardPosition pos = new BoardPosition(0, 4);


        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals('X', gb.whatsAtPos(pos));
    }
    // tests dropToken to fill up a board completely
    @Test
    public void dropToken_to_fill_board() {
        int row = 5, column = 5, numTokens = 3;

        char[][] outputArray = new char[row][column];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                outputArray[i][j] = ' ';
            }
        }
        IGameBoard gb = InitializeGameBoard(row,column,numTokens);

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i == 4 && j == 4)
                    gb.dropToken('X', 4);
                else
                    gb.dropToken('O', j);
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i == 4 && j == 4)
                    outputArray[i][j] = 'X';
                else
                    outputArray[i][j] = 'O';
            }
        }

        BoardPosition pos = new BoardPosition(4, 4);
        String expOutput = expOutput(outputArray, gb);
        assertEquals(gb.toString(), expOutput);
        assertEquals('X', gb.whatsAtPos(pos));
    }
}
