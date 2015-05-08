#ifndef TURTLECOMMANDER_H
#define TURTLECOMMANDER_H

//#include <string>

void initTurtles();
void clearTurtleNode();

std::string spawnTurtle(double x, double y, double theta, std::string name);
void killTurtle(std::string name);


void moveTurtle(std::string name, double ForwardSpeed, double AngularSpeed);
void moveTurtleForward(std::string name, double ForwardSpeed);
void rotateTurtle(std::string name, double AngularSpeed);

#endif // TURTLECOMMANDER_H
