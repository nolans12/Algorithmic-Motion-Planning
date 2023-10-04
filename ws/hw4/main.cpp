// This includes all of the necessary header files in the toolbox
#include "AMPCore.h"

// Include the correct homework header
#include "hw/HW4.h"

// Include the header of the shared class
#include "HelpfulClass.h"
#include "helperFuncs.h"

using namespace amp;

int main(int argc, char** argv) {
    /* Include this line to have different randomized environments every time you run your code (NOTE: this has no affect on grade()) */
    amp::RNG::seed(amp::RNG::randiUnbounded());

std::cout << "/////// EXERCISE 1 ////////" << std::endl;
    amp::Polygon obstacle = amp::HW4::getEx1TriangleObstacle();
    amp::Polygon robot = amp::HW4::getEx1TriangleObstacle();

    // get the vertices of the robot
    std::vector<Eigen::Vector2d> vertices = robot.verticesCCW();
    // get the reference point
    Eigen::Vector2d refPoint = vertices[0]; // told to use lower left

    // test case
    // std::vector<Eigen::Vector2d> vRob;
    // vRob.push_back(Eigen::Vector2d(0,1));
    // vRob.push_back(Eigen::Vector2d(2,1));
    // vRob.push_back(Eigen::Vector2d(2,3));
    // vRob.push_back(Eigen::Vector2d(0,3));
    // amp::Polygon obstacle(vRob);

    amp::Polygon negRobot = negativeVert(robot, refPoint); // told to chose lower left vertex as reference point
    //output the original vertices of robot, including x and y for each line
    vertices = negRobot.verticesCCW();
    std::cout << "Robot: " << std::endl;
    for (int i = 0; i < vertices.size(); i++){
        std::cout << "x: " << vertices[i].x() << " y: " << vertices[i].y() << std::endl;
    }
    // output all vertices of Obstacle, including x and y for each line
    vertices = obstacle.verticesCCW();
    std::cout << "Obstacle: " << std::endl;
    for (int i = 0; i < vertices.size(); i++){
        std::cout << "x: " << vertices[i].x() << " y: " << vertices[i].y() << std::endl;
    }
    // do minkowski sum on negative robot + obstacle
    amp::Polygon cObst = minkowski(negRobot, obstacle);

    // now plot
    std::vector<Polygon> origPolygons;
    std::vector<Polygon> resultPolygons;
    // plot the polygons, original
    origPolygons.push_back(obstacle);
    origPolygons.push_back(negRobot);
    std::vector<std::string> labels;
    labels.push_back("obstacle");
    labels.push_back("negative robot");
    // result
    resultPolygons.push_back(cObst);
    // plot
    amp::Visualizer::makeFigure(origPolygons, labels, true);
    amp::Visualizer::makeFigure(resultPolygons, true);
    //amp::Visualizer::showFigures();

// 1B
    // use 12 equally spaced rotation angles, rotating about ref point of robot, (0,0) or [0]
    // get the angles
    std::vector<double> angles;
    for (int i = 0; i < 12; i++){
        angles.push_back(i*M_PI/6);
    }
    // rotate the robot
    std::vector<Polygon> rotatedRobots;
    for (int i = 0; i < angles.size(); i++){
        rotatedRobots.push_back(rotatePolygon(robot, refPoint, angles[i]));
    }
    // plot the rotated robots
    amp::Visualizer::makeFigure(rotatedRobots, true);
    //amp::Visualizer::showFigures();

    // now perform minkowski difference on all
    std::vector<Polygon> negRotatedRobots;
    std::vector<Polygon> minkowskiRobots;
    for (int i = 0; i < angles.size(); i++){
        // negate all robots around ref point
        negRotatedRobots.push_back(negativeVert(rotatedRobots[i], refPoint));
        minkowskiRobots.push_back(minkowski(negRotatedRobots[i], obstacle));
    }
    // plot the minkowski robots
    // add a heights going from 1 to 360 to be able to visualize results
    std::vector<double> heights;
    for (int i = 0; i < angles.size(); i++){
        heights.push_back(i*360/12);
    }
    amp::Visualizer::makeFigure(minkowskiRobots, heights);
    //amp::Visualizer::showFigures();


std::cout << "/////// EXERCISE 2 ////////" << std::endl;

// 2a
// inputs:
    double a1 = 0.5;
    double a2 = 1;
    double a3 = 0.5;
    double t1 = M_1_PI*10/6;
    double t2 = M_1_PI*10/3;
    double t3 = 7*M_1_PI*10/4;
    Eigen::Vector2d base(0,0);

    std::vector<double> link_lengths;
    link_lengths.push_back(a1);
    link_lengths.push_back(a2);
    link_lengths.push_back(a3);
    std::vector<double> link_angles;
    link_angles.push_back(t1);
    link_angles.push_back(t2);
    link_angles.push_back(t3);


    // make the link manipulator
    Link2d manipulator(base, link_lengths);
    
    // perform forward kinematics
    manipulator.getJointLocation(link_angles, 0);

    amp::Visualizer::makeFigure(manipulator, link_angles);
    amp::Visualizer::showFigures();


    // Grade method
    //amp::HW4::grade<MyLinkManipulator>(constructor, "nonhuman.biologic@myspace.edu", argc, argv);
    return 0;
}