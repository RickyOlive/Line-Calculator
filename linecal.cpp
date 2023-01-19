// File: linecal.cpp
// Class: COP 2006, 202208, 80599
// By: Richard Olive
// Desc: Program that calculates slope, distance, and angle
//---------------------------------------------------------


// Libraries
//---------------------------------------------------------
#include <iostream>
#include <cmath>

// Structs
//---------------------------------------------------------
struct Point {
    float x;
    float y;
};

struct Line {
    Point point1;
    Point point2;
    Point point3;
};

struct Coefficients {
    float a;
    float b;
    float c;
};

// Function declarations
//---------------------------------------------------------
Line getPoints(int optionNum);
bool isNum(std::string stringNum);
Coefficients getQuadratic(Line points);
float getSlope(Line points);
float getIntercept(Line points);
float getVertexX(Coefficients coefficients);
float getVertexY(Coefficients coefficients);
float getLinearLen(Line points);
float getAngle(Line points);
void printValues(int optionNum, Line points,
                 Coefficients coefficients);


//---------------------------------------------------------
int main() {
    // declares loop var and enters loop
    std::string tryAgain = "y";

    // greets user
    std::cout << "Welcome to Ricky's Line Calculator!"
    << std::endl;

    // offers better input checking
    while (tryAgain == "y" || tryAgain == "Y") {
        // initializes menu option var
        int optionNum = 0;

        // menu options
        std::cout << std::endl << "1. Linear Line"
        << std::endl;

        std::cout << "2. Quadratic Line (only works with a"
                     " function and non-linear points): "
                     << std::endl << std::endl;

        // tells user to input value
        std::cout << "Enter option number (ex. 1): ";

        std::cin >> optionNum;

        while (optionNum != 1 && optionNum != 2) {
            std::cout << "Invalid Input! Please try again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> optionNum;
        }

        // assigns both point values to line struct var
        Line points = getPoints(optionNum);

        Coefficients coefficients = getQuadratic(points);

        // neatly prints everything
        printValues(optionNum, points, coefficients);


        // asks user for input to update loop var
        std::cout << "Would you like to try a different "
                         "set of points? Enter y/n: ";
        std::cin >> tryAgain;

        while (tryAgain != "y" && tryAgain != "Y"
                && tryAgain != "n" && tryAgain != "N")
        {
            std::cout << "Invalid input please "
                         "try again! Enter y/n: ";
            std::cin >> tryAgain;
        }
    }
    if (tryAgain == "n" || tryAgain == "N") {
        std::cout << std::endl <<
        "Thank you for using Ricky's line calculator!"
        " Have a great day!" << std::endl;
    }
    return 0;
}


/**
 * Gathers user input for point values
 * @param optionNum
 * @return Line
 */
Line getPoints(int optionNum) {
    //declares and initializes temp var of type Line
    Line temp = {0,0,0,0, 0,0};

    // declares string variables
    std::string stringNum1x;
    std::string stringNum1y;
    std::string stringNum2x;
    std::string stringNum2y;
    std::string stringNum3x;
    std::string stringNum3y;


    std::cout << "Enter values for first point "
                 "seperated by a space. (Ex. 2 4): ";

    // gathers input
    std::cin >> stringNum1x;

    // calls function to check if input is valid
    // if not it loops until it gathers a valid input
    while (!isNum(stringNum1x)) {
        std::cout << "Invalid input! Please try again: ";
        // clears error
        std::cin.clear();
        // skips line with invalid input
        std::cin.ignore(10000, '\n');
        std::cin >> stringNum1x;
    }
    // if function returns true then it converts to
    // float and stores number in the struct var
    if (isNum(stringNum1x)) {
        temp.point1.x = std::stof(stringNum1x);
    }

    std::cin >> stringNum1y;

    while (!isNum(stringNum1y)) {
        std::cout << "Invalid input! Please try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> stringNum1x;
    }
    if (isNum(stringNum1y)) {
        temp.point1.y = std::stof(stringNum1y);
    }

    std::cout << "Enter values for second point "
                 "seperated by a space. (Ex. 2 4): ";

    std::cin >> stringNum2x;

    while (!isNum(stringNum2x)) {
        std::cout << "Invalid input! Please try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> stringNum2x;
    }
    if (isNum(stringNum2x)) {
        temp.point2.x = std::stof(stringNum2x);
    }

    std::cin >> stringNum2y;

    while (!isNum(stringNum2y)) {
        std::cout << "Invalid input! Please try again: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> stringNum2y;
    }
    if (isNum(stringNum2y)) {
        temp.point2.y = std::stof(stringNum2y);
    }

    if (optionNum == 2) {
        std::cout << "Enter values for first point "
                     "seperated by a space. (Ex. 2 4): ";

        std::cin >> stringNum3x;

        while (!isNum(stringNum3x)) {
            std::cout << "Invalid input! Please try again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> stringNum3x;
        }
        if (isNum(stringNum3x)) {
            temp.point3.x = std::stof(stringNum3x);
        }

        std::cin >> stringNum3y;

        while (!isNum(stringNum3y)) {
            std::cout << "Invalid input! Please try again: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin >> stringNum3y;
        }
        if (isNum(stringNum3y)) {
            temp.point3.y = std::stof(stringNum3y);
        }
    }

    // returns updated struct
    return temp;
}

/**
 * checks if input if numerical
 * @param stringNum
 * @return true if num
 */
bool isNum(std::string stringNum) {
    // declared and initialized accumulators
    int validatorNum = 0;
    int decimalCtr = 0;

    // Not sure if the user can enter a null
    // value, so I decided to just play it safe
    if (stringNum.empty()) {
        return false;
    }

    // validates negative sign
    if (stringNum[0] == '-') {
        validatorNum += 1;
    }

    // looping through char array from string; every time
    // it views a char as valid it adds to the accumulator
    for (int i = 0; i < stringNum.size(); i++) {
        if (isdigit(stringNum[i])) {
            validatorNum += 1;
        }
        if (stringNum[i] == '.') {
            validatorNum += 1;
            decimalCtr += 1;
        }

    }

    // only allows for the placement of one decimal point
    if (decimalCtr > 1) {
        return false;
    }

    // checks to make sure the amount of valid char is
    // equal to the amount in the array
    if (validatorNum == stringNum.size()) {
        return true;
    }
    else
        return false;

}

/**
 * calculates value of the coefficients
 * @param points
 * @return quadratic coefficients
 */
Coefficients getQuadratic(Line points) {
    // to store coefficient var
    Coefficients temp = {0,0,0};

    // arrays used when solving system of equations
    float firstEq[3] = {0.0,0.0,0.0};
    float secondEq[3] = {0.0,0.0,0.0};
    float thirdEq[3] = {0.0,0.0,0.0};
    float firstSecEq[3] = {0.0,0.0,0.0};
    float newFirstSecEq[3] = {0.0,0.0,0.0};
    float secThirdEq[3] = {0.0,0.0,0.0};
    float newThirdSecEq[3] = {0.0,0.0,0.0};
    float sumEq[3] = {0.0,0.0,0.0};

    // plugs in x and y to from points to make equation
    // y = ax^2 + bx + c
    // stores for x in equation
    firstEq[0] = pow(points.point1.x, 2);
    firstEq[1] = points.point1.x;
    // stores for y in equation
    firstEq[2] = points.point1.y;

    // c will be canceled when the equations are added
    secondEq[0] = pow(points.point2.x, 2) * -1;
    secondEq[1] = points.point2.x * -1;
    secondEq[2] = points.point2.y * -1;

    thirdEq[0] = pow(points.point3.x, 2);
    thirdEq[1] = points.point3.x;
    thirdEq[2] = points.point3.y;

    // adds first and second equations
    firstSecEq[0] = firstEq[0] + secondEq[0];
    firstSecEq[1] = firstEq[1] + secondEq[1];
    firstSecEq[2] = firstEq[2] + secondEq[2];

    // adds second and third equations
    secThirdEq[0] = secondEq[0] + thirdEq[0];
    secThirdEq[1] = secondEq[1] + thirdEq[1];
    secThirdEq[2] = secondEq[2] + thirdEq[2];

    // multiplies entire equation by the first
    // coefficient so that they can cancel when added
    newFirstSecEq[0] = firstSecEq[0] * secThirdEq[0];
    newFirstSecEq[1] = firstSecEq[1] * secThirdEq[0];
    newFirstSecEq[2] = firstSecEq[2] * secThirdEq[0];

    // multiplies entire equation by the first
    // coefficient so that they can cancel when added
    // multiplies by -1 so that the "a" term cancels
    newThirdSecEq[0] = (secThirdEq[0] * firstSecEq[0]) * -1;
    newThirdSecEq[1] = (secThirdEq[1] * firstSecEq[0]) * -1;
    newThirdSecEq[2] = (secThirdEq[2] * firstSecEq[0]) * -1;

    // this will always equal 0
    sumEq[0] = newFirstSecEq[0] + newThirdSecEq[0];

    // adds both equations in system of equations
    sumEq[1] = newFirstSecEq[1] + newThirdSecEq[1];
    sumEq[2] = newFirstSecEq[2] + newThirdSecEq[2];

    // solves for b
    temp.b = sumEq[2] / sumEq[1];

    // solves for a
    temp.a = (firstSecEq[2] - (firstSecEq[1] * temp.b))
            / firstSecEq[0];

    // solves for c
    temp.c = firstEq[2] - ((firstEq[0] * temp.a) +
            (firstEq[1] * temp.b));

    return temp;

}

/**
 * calculates slope
 * @param points
 * @return slope
 */
float getSlope(Line points) {
    float slope = (points.point2.y - points.point1.y)/
            (points.point2.x - points.point1.x );
    return slope;
}

/**
 * calculates y-intercept
 * @param points
 * @return y-intercept
 */
float getIntercept(Line points) {
    float intercept = points.point1.y -
            (getSlope(points) * points.point1.x);
    return intercept;
}

/**
 * calculates x value of vertex
 * @param coefficients
 * @return vertex x value
 */
float getVertexX(Coefficients coefficients) {

    float vertexX = (coefficients.b / (2 * coefficients.a)) * -1;

    return vertexX;
}

/**
 * calculates y value
 * @param coefficients
 * @return vertex y value
 */
float getVertexY(Coefficients coefficients) {

    float vertexX = getVertexX(coefficients);
    float vertexY = (coefficients.a * pow(vertexX, 2))
            + (coefficients.b * vertexX) + coefficients.c;

    return vertexY;
}

/**
 * calculates length of linear line
 * @param points
 * @return length of linear line
 */
float getLinearLen(Line points) {
    float len = sqrt(pow(points.point2.x
            - points.point1.x, 2)
            + pow(points.point2.y
            - points.point1.y, 2) );
    return len;
}

/**
 * calculates angle produced by the line and x-axis
 * @param points
 * @return angle in degrees
 */
float getAngle(Line points) {
    float angle = atan(getSlope(points))
            * 180 / M_PI;
    if (angle <= 0) {
        angle += 180;
    }
    return angle;

}


/**
 * neatly outputs values
 * @param optionNum
 * @param points
 * @param coefficients
 */
void printValues(int optionNum, Line points, Coefficients coefficients) {

    if (optionNum == 1) {
        std::cout << "Properties of Line: " << std::endl
                  << std::endl;

        std::cout << "Point 1: " << "( " << points.point1.x
                  << " , " << points.point1.y << " )" << std::endl;
        std::cout << "Point 2: " << "( " << points.point2.x
                  << " , " << points.point2.y << " )" << std::endl;


        std::cout << "Equation: y = " << getSlope(points)
                  << "x + " <<
                  getIntercept(points) << std::endl;

        std::cout << "Slope: " << getSlope(points)
                  << std::endl;

        std::cout << "Y-Intercept: " << getIntercept(points)
                  << std::endl;

        std::cout << "Length: " << getLinearLen(points)
                  << std::endl;

        std::cout << "Angle: " << getAngle(points)
                  << " degrees" << std::endl;
    }
    else if (optionNum == 2) {
        std::cout << "Properties of Line: " << std::endl
                  << std::endl;

        std::cout << "Point 1: " << "( " << points.point1.x
                  << " , " <<points.point1.y << " )" << std::endl;
        std::cout << "Point 2: " << "( " << points.point2.x
                  << " , " << points.point2.y << " )" << std::endl;
        std::cout << "Point 3: " << "( " << points.point3.x
                  << " , " << points.point3.y << " )" << std::endl;

        std::cout << "Equation: y = " << coefficients.a
        << "x^2 + " << coefficients.b << "x + " << coefficients.c << std::endl;

        std::cout << "Vertex: ( " <<
        getVertexX(coefficients) << " , " <<
        getVertexY(coefficients) << " )" << std::endl;

        std::cout << "Y-Intercept: " << coefficients.c
                  << std::endl;
    }
}

//---------------------------------------------------------



