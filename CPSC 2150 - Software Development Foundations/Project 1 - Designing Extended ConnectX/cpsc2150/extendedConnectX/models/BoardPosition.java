package cpsc2150.extendedConnectX.models;

/*GROUP MEMBER NAMES AND GITHUB USERNAMES SHOULD GO HERE

    Prahalad Gururajan (PravClem)
    Connor Burkart (crburka)
    Sean Farrell (sfarrellClemosn)
    Parthiv Patel (Parthivp2205)

 */

/**
* @invariant (Row <= 8 AND Row >= 0) AND (Column <= 6 AND Column >= 0)
**/

public class BoardPosition
{
    private int Row;
    private int Column;

    /**
     * </Description: The constructor takes in the parameters row and column to store them in an object>
     * @param aColumn holds the column position
     * @param aRow holds the row position
     * @pre (aRow <= 8 and aRow >= 0) AND (aColumn <+ 6 and aColumn >= 0)
     * @post Column = aColumn and Row = aRow
     */
    public BoardPosition(int aRow, int aColumn)
    {
        //parameterized constructor for BoardPosition
    }
    /**
     * </Description: Will get you the current position of the row>
     * @post getRow = Row AND Row = #Row AND Column = #Column
     * @return the row stored within the Row field.
     */
    public int getRow()
    {
        //returns the row
    }
    /**
     * </Description: Will get you the current position of the column>
     * @post Row = #Row AND Column = #Column AND getColumn = Column
     * @return the column stored within the Column field
         */
    public int getColumn()
    {
        //returns the column
    }
    
    /**
     * </Description: Checks to see if two objects are equal and if so it is true>
     * @param obj its another BoardPosition object
     * @post equals iff (this.Row - obj.Row AND this.Column - obj.Column AND [this and obj are both instances of BoardPosition]) AND obj = #obj AND Row = #Row AND Column = #Column
     * @return True if the objects this and obj have equal values for Row and Column and are instances of BoardPosition, false otherwise.
     */
    @Override
    public boolean equals(Object obj)
    {

    }

    /**
     * </Description: The method makes it easier to read the current row and column>

     * @pre 0 <= column <= 8 and 0 <= row <= 6
     * @post toString = ["<Row>, <Column>"] AND Row = #Row AND Column = #Column AND self = #self
     * @return String with a format that is easy to read in  "<Rows>, <Columns>"
     */
    @Override
    public String toString()
    {

    }
}
