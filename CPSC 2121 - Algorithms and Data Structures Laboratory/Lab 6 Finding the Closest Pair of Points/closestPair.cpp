/*
 * Name: Sean Farrell
 * Date Submitted: 10/30/2023
 * Lab Section: 006
 * Assignment Name: Lab 6 Finding the Closest Pair of points
 *
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/

//Caculates distance from 2 points

double distCalc(point left, point right) {
    // variables needed to calculate distance
    double xDist = left.x - right.x;
    double yDist = left.y - right.y;

    // Calculates distance
    double dist = sqrt(pow(xDist, 2) + pow(yDist, 2));

    //returns distance
    return dist;
}

//compares amd returns the shortest distance
double shorter(double newDistance, double oldDistance) {
    if (newDistance < oldDistance)
        return newDistance;
    return oldDistance;
}

double closestPair(string filename) {
    //initialize variables
    int xPos = 0;
    int yPos = 0;
    double pointDistance = 0.0;
    double shortestDistance = 2.0;
    int num_points = 0;
    int b = 0;
    point value;

    //open file & read data
    ifstream input;
    input.open(filename);
    if (input.is_open())
    {
        input >> num_points;
        b = sqrt(num_points); /** I chose B as the square root of the quantity of points in the .txt file to be scalable to different sizes of datasets in the .txt files
        Therefore since the directions state that b^2 scales with number of points i choose square root of b*/
    }

    //declares vector for points
    vector<vector<vector<point>>> points(b, vector<vector<point>>(b));

    //populates the point vector from text file to be compared
    for (int i = 0; i < num_points; i++)
    {
        // from input file
        input >> value.x;
        input >> value.y;

        // two points
        xPos = (int)(value.x * b);
        yPos = (int)(value.y * b);

        points[xPos][yPos].push_back(value);

    }
    //declare x and variables
    int x, y;

    //goes through every point in the .txt file
    for (int j = 0; j < points.size(); j++) {
        for (int k = 0; k < points.size(); k++) {
            for (int n = 0; n < points[j][k].size(); n++) {
                //set value equal to a specific point in the vector

                point value = points[j][k][n];

                for (int m = 0; m < points[j][k].size(); m++) {
                    //set a point two equal to a specific point
                    point two = points[j][k][m];

                    //if the values are not the same it checks for a shorter distance
                    if (two.x != value.x && two.y != value.y) {
                        pointDistance = distCalc(points[j][k][m], value);
                        shortestDistance = shorter(pointDistance, shortestDistance);
                    }
                }
                //check all points in the vector
                if (j != b - 1) {
                    for(int z = 0; z < points[j + 1][k].size(); z++) {
                        x = j + 1;
                        y = k;
                        pointDistance = distCalc(points[x][y][z], value);
                        shortestDistance = shorter(pointDistance, shortestDistance);

                    }
                }
                if (k != b - 1) {
                    for(int z = 0; z < points[j][k + 1].size(); z++){
                        pointDistance = distCalc(points[j][k+ 1][z], value);
                        shortestDistance = shorter(pointDistance, shortestDistance);
                    }
                }
                if (j != b - 1 && k != 0) {
                    for(int z = 0; z < points[j + 1][k - 1].size(); z++){
                        pointDistance = distCalc(points[j + 1][k - 1][z], value);
                        shortestDistance = shorter(pointDistance, shortestDistance);
                    }
                }
                if (j != b - 1 && k != b - 1) {
                    for(int z = 0; z < points[j + 1][k + 1].size(); z++) {
                        pointDistance = distCalc(points[j + 1][k + 1][z], value);
                        shortestDistance = shorter(pointDistance, shortestDistance);

                    }
                }
            }
        }
    }
    // returns shortest distance between points
    return shortestDistance;
}


//int main()
//{
//    double min;
//    string filename;
//    cout << "File with list of points within unit square: ";
//    cin >> filename;
//    min = closestPair(filename);
//    cout << setprecision(16);
//    cout << "Distance between closest pair of points: " << min << endl;
//    return 0;
//}
//int main()
//{
//    double min = closestPair("points10.txt");
//
//    //ASSERT_NEAR(min, 0.068553744951327016954, 0.00000000000001e-02);
//    if (std::abs(min - 0.068553744951327016954) > 0.00000000000001e-02)
//    {
//        std::cout << std::setprecision(22);
//        std::cout << "expected/correct value for min is 0.068553744951327016954, actual value when testing " << min << ".\n";
//        return 1;
//    }
//    std::cout << "Passed" << std::endl;
//    return 0;
//}