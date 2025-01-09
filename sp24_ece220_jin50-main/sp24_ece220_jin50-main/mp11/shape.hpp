//jin50, jaypark3
/*
This program uses the concept of polymorphism, templates, and operator overleading. 
First, we utilize the use of file I/O to read the file then, we use the concept 
of base class, shape, and derived classes for various geometries. We also utilize 
operator overloading to get length, width, and radius. There are rectangles, circle, 
rectprism, and sphere. Each class calculates area and volume for each geometrical shape.
*/

#ifndef SHAPE_H_
#define SHAPE_H_

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <list>
#include <fstream>
#include <iomanip>

using namespace std; //namespace standard

class Shape { //parent class
public:
    Shape(string name) : name_(name) {}

    string getName() const { //returning name
        return name_;
    }

    virtual double getArea() const = 0; //initialize virtual function for area
    virtual double getVolume() const = 0; //initilize virtual function for volume

private:
    string name_;
};

// Rectangle
template <class T>
class Rectangle : public Shape { //rectangle derived class
public:
    Rectangle(T width = 0, T length = 0) : Shape("Rectangle"), width_(width), length_(length) {} //constructor

    double getArea() const override { //getting area
        return width_ * length_;
    }

    double getVolume() const override { //getting volume
        return 0;
    }

    Rectangle<T> operator + (const Rectangle<T>& rec) { //operator overloading +
        return Rectangle<T>(width_ + rec.width_, length_ + rec.length_);
    }

    Rectangle<T> operator - (const Rectangle<T>& rec) { //operator overloading -
        T newWidth = max(0.0, static_cast<double>(width_ - rec.width_));
        T newLength = max(0.0, static_cast<double>(length_ - rec.length_));
        return Rectangle<T>(newWidth, newLength);
    }

    T getWidth() const { //giving width
        return width_;
    }

    T getLength() const {  //giving length
        return length_;
    }

private:
    T width_; //only accessible within this class
    T length_;
};

// Circle
class Circle : public Shape { //circle derived class
public:
    Circle(double radius) : Shape("Circle"), radius_(radius) {} //constructor

    double getArea() const override { //getting area
        return M_PI * radius_ * radius_;
    }

    double getVolume() const override { //getting vol
        return 0;
    }

    Circle operator + (const Circle& cir) { //overload op
        return Circle(radius_ + cir.radius_);
    }

    Circle operator - (const Circle& cir) {
        double newRadius = max(0.0, radius_ - cir.radius_);
        return Circle(newRadius);
    }

    double getRadius() const { //getting r
        return radius_;
    }

private:
    double radius_;
};

// Sphere
class Sphere : public Shape { //sphere derived class
public:
    Sphere(double radius) : Shape("Sphere"), radius_(radius) {}

    double getVolume() const override { //finding volume
        return (4.0 / 3.0) * M_PI * pow(radius_, 3);
    }

    double getArea() const override { //finding area
        return 4 * M_PI * radius_ * radius_;
    }

    Sphere operator + (const Sphere& sph) { //overload op.
        return Sphere(radius_ + sph.radius_);
    }

    Sphere operator - (const Sphere& sph) {
        double newRadius = max(0.0, radius_ - sph.radius_);
        return Sphere(newRadius);
    }

    double getRadius() const {
        return radius_;
    }

private:
    double radius_;
};

// RectPrism
class RectPrism : public Shape { //rectprism derived class
public:
    RectPrism(double width, double length, double height) : Shape("RectPrism"), width_(width), length_(length), height_(height) {}

    double getVolume() const override { //getting volume
        return width_ * length_ * height_;
    }

    double getArea() const override { //getting area
        return 2 * (width_ * length_ + width_ * height_ + length_ * height_);
    }

    RectPrism operator + (const RectPrism& rectp) {
        return RectPrism(width_ + rectp.width_, length_ + rectp.length_, height_ + rectp.height_);
    }

    RectPrism operator - (const RectPrism& rectp) {
        double newWidth = max(0.0, width_ - rectp.width_);
        double newLength = max(0.0, length_ - rectp.length_);
        double newHeight = max(0.0, height_ - rectp.height_);
        return RectPrism(newWidth, newLength, newHeight);
    }

    double getWidth() const { //getting width
        return width_;
    }

    double getLength() const {
        return length_;
    }

    double getHeight() const {
        return height_;
    }

private: //private variables
    double length_;
    double width_;
    double height_;
};


static list<Shape*> CreateShapes(char* file_name) { //creating shapes
    list<Shape*> shapes;
    ifstream file(file_name);
    string type;
    double width, length, height, radius;

    while (file >> type) {
        if (type == "Rectangle") { //checking for rectangle
            file >> width >> length;
            shapes.push_back(new Rectangle<double>(width, length));
        } else if (type == "Circle") { //checking for shapes
            file >> radius;
            shapes.push_back(new Circle(radius));
        } else if (type == "Sphere") {
            file >> radius;
            shapes.push_back(new Sphere(radius));
        } else if (type == "RectPrism") {
            file >> width >> length >> height;
            shapes.push_back(new RectPrism(width, length, height));
        }
    }
    file.close(); //close file I/O
    return shapes;
}


static double MaxArea(list<Shape*> shapes) { //finding area
    double max_area = 0;
    for (Shape* shape : shapes) { //for loop for finding area
        double area = shape->getArea();
        if (area > max_area) { //new area found
            max_area = area;
        }
    }
    return max_area;
}


static double MaxVolume(list<Shape*> shapes) { //finding volume
    double max_volume = 0; //initialized
    for (Shape* shape : shapes) { //for loop for finding volume
        double volume = shape->getVolume();
        if (volume > max_volume) { //new volume found
            max_volume = volume;
        }
    }
    return max_volume;
}

#endif
