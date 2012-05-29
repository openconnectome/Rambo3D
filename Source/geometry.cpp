#include <stdlib.h>
#include <math.h>
#include "geometry.h"

/////////////
// Point2D //
/////////////
Point2D::Point2D(void){p[0]=p[1]=0;}
Point2D::Point2D(const double& x,const double& y){
        p[0]=x;
        p[1]=y;
}
double& Point2D::operator[] (const int& i){return p[i];}
double& Point2D::index(const int& i){return p[i];}
Point2D Point2D::unit(void) const{return scale(1.0/length());}
Point2D Point2D::negate(void) const{return scale(-1.0);}
Point2D Point2D::operator -(void) const{return scale(-1.0);}

Point2D Point2D::scale(double s) const {return Point2D(p[0]*s,p[1]*s);}
Point2D Point2D::operator* (double s) const {return scale(s);}
Point2D Point2D::operator/ (double s) const {return scale(1.0/s);}
Point2D& Point2D::operator*= (double s){
        p[0]*=s;
        p[1]*=s;
        return *this;
}
Point2D& Point2D::operator/= (double s){
        p[0]/=s;
        p[1]/=s;
        return *this;
}

double     Point2D::dot(const Point2D& q) const {return p[0]*q.p[0]+p[1]*q.p[1];}
double     Point2D::length(void) const {return sqrt(dot(*this));}
double		Point2D::squareNorm(void) const {return p[0]*p[0]+p[1]*p[1];}


Point2D Point2D::add(const Point2D& q) const {return Point2D(p[0]+q.p[0],p[1]+q.p[1]);}
Point2D  Point2D::operator+ (const Point2D& q) const {return add(q);}
Point2D& Point2D::operator+= (const Point2D& q){
        p[0]+=q.p[0];
        p[1]+=q.p[1];
        return *this;
}

Point2D Point2D::subtract(const Point2D& q) const {return Point2D(p[0]-q.p[0],p[1]-q.p[1]);}
Point2D Point2D::operator- (const Point2D& q) const {return subtract(q);}
Point2D& Point2D::operator-= (const Point2D& q){
        p[0]-=q.p[0];
        p[1]-=q.p[1];
        return *this;
}

Point2D Point2D::mult(const Point2D& q) const {return Point2D(p[0]*q.p[0],p[1]*q.p[1]);}
Point2D  Point2D::operator* (const Point2D& q) const {return Point2D(p[0]*q.p[0],p[1]*q.p[1]);}
Point2D& Point2D::operator*=(const Point2D& q){
        p[0]*=q.p[0];
        p[1]*=q.p[1];
        return *this;
}

Point2D Point2D::div(const Point2D& q) const {return Point2D(p[0]/q.p[0],p[1]/q.p[1]);}
Point2D  Point2D::operator/ (const Point2D& q) const {return Point2D(p[0]/q.p[0],p[1]/q.p[1]);}
Point2D& Point2D::operator/=(const Point2D& q){
        p[0]/=q.p[0];
        p[1]/=q.p[1];
        return *this;
}
/////////////
// Point3D //
/////////////
Point3D::Point3D(void){p[0]=p[1]=p[2]=0;}
Point3D::Point3D(const double& x,const double& y,const double& z){
        p[0]=x;
        p[1]=y;
        p[2]=z;
}
double&    Point3D::operator[] (const int& i){return p[i];}
double&    Point3D::index(const int& i){return p[i];}
Point3D Point3D::unit(void) const {return scale(1.0/length());}
Point3D Point3D::negate(void) const {return scale(-1.0);}
Point3D Point3D::operator -(void) const {return scale(-1.0);}
Point3D Point3D::scale(double s) const {return Point3D(p[0]*s,p[1]*s,p[2]*s);}
Point3D  Point3D::operator* (double s) const {return Point3D(p[0]*s,p[1]*s,p[2]*s);}
Point3D& Point3D::operator*=(double s){
        p[0]*=s;
        p[1]*=s;
        p[2]*=s;
        return *this;
}

Point3D  Point3D::operator/ (double s) const {return scale(1.0/s);}
Point3D& Point3D::operator/=(double s){
        p[0]/=s;
        p[1]/=s;
        p[2]/=s;
        return *this;
}
double     Point3D::dot(const Point3D& q) const {return p[0]*q.p[0]+p[1]*q.p[1]+p[2]*q.p[2];}
double		Point3D::squareNorm(void) const {return p[0]*p[0]+p[1]*p[1]+p[2]*p[2];}
double     Point3D::length(void) const {return sqrt(squareNorm());}

Point3D Point3D::add(const Point3D& q) const {return Point3D(p[0]+q.p[0],p[1]+q.p[1],p[2]+q.p[2]);}
Point3D  Point3D::operator+ (const Point3D& q) const {return Point3D(p[0]+q.p[0],p[1]+q.p[1],p[2]+q.p[2]);}
Point3D& Point3D::operator+=(const Point3D& q){
        p[0]+=q.p[0];
        p[1]+=q.p[1];
        p[2]+=q.p[2];
        return *this;
}
Point3D Point3D::subtract(const Point3D& q) const {return Point3D(p[0]-q.p[0],p[1]-q.p[1],p[2]-q.p[2]);}
Point3D  Point3D::operator- (const Point3D& q) const {return subtract(q);}
Point3D& Point3D::operator-=(const Point3D& q){
        p[0]-=q.p[0];
        p[1]-=q.p[1];
        p[2]-=q.p[2];
        return *this;
}

Point3D Point3D::crossProduct(const Point3D& q) const {return Point3D(p[1]*q.p[2]-p[2]*q.p[1],-p[0]*q.p[2]+p[2]*q.p[0],p[0]*q.p[1]-p[1]*q.p[0]);}
Point3D  Point3D::operator^ (const Point3D& q) const {return crossProduct(q);}
Point3D& Point3D::operator^=(const Point3D& q){
        double temp1= p[1]*q.p[2]-p[2]*q.p[1];
        double temp2=-p[0]*q.p[2]+p[2]*q.p[0];
        p[2]=      p[0]*q.p[1]-p[1]*q.p[0];
        p[0]=temp1;
        p[1]=temp2;
        return *this;
}

Point3D  Point3D::mult(const Point3D& q) const {return Point3D(p[0]*q.p[0],p[1]*q.p[1],p[2]*q.p[2]);}
Point3D  Point3D::operator* (const Point3D& pt) const {return mult(pt);}
Point3D& Point3D::operator*=(const Point3D& pt){
        p[0]*=pt.p[0];
        p[1]*=pt.p[1];
        p[2]*=pt.p[2];
        return *this;
}
Point3D  Point3D::div(const Point3D& q) const {return Point3D(p[0]/q.p[0],p[1]/q.p[1],p[2]/q.p[2]);}
Point3D  Point3D::operator/ (const Point3D& pt) const {return div(pt);}
Point3D& Point3D::operator/=(const Point3D& pt){
        p[0]/=pt.p[0];
        p[1]/=pt.p[1];
        p[2]/=pt.p[2];
        return *this;
}

/////////////
// Plane3D //
/////////////
Plane3D::Plane3D(void){
        position = Point3D(0,0,0);
        normal=Point3D(1,0,0);
        distance=0;
}
Plane3D::Plane3D(const Point3D& n,const Point3D& pt){
        position = pt;
        this->normal=n.unit();
        distance = this->normal.dot(pt);
}
Plane3D::Plane3D(const Point3D& p1,const Point3D& p2,const Point3D& p3){
        position = p1;
        normal=((p2-p1)^(p3-p1)).unit();
        distance=-normal.dot(p1);
}
void Plane3D::makePositive(const Point3D& p){
        if(evaluate(p)<0){
                normal=-normal;
                distance=-distance;
        }
}
double Plane3D::evaluate(const Point3D& p) const {return normal.dot(p)+distance;}
double Plane3D::operator()(const Point3D& p) const {return evaluate(p);}


///////////
// Ray3D //
///////////
Ray3D::Ray3D(void){
        position=Point3D(0,0,0);
        direction=Point3D(1,0,0);
}
Ray3D::Ray3D(const Point3D& p1,const Point3D& p2){
        position=p1;
        direction=p2;
}
Point3D Ray3D::operator() (double s) const {return position+direction*s;}

Ray3D Ray3D::add(const Point3D& p) const {
        Ray3D r=*this;
        r.position+=p;
        return r;
}
Ray3D  Ray3D::operator+ (const Point3D& p) const {return add(p);}
Ray3D& Ray3D::operator+=(const Point3D& p){
        position+=p;
        return *this;
}
Ray3D  Ray3D::subtract(const Point3D& p) const{
        Ray3D r=*this;
        r.position-=p;
        return r;
}
Ray3D  Ray3D::operator- (const Point3D& p) const {return subtract(p);}
Ray3D& Ray3D::operator-=(const Point3D& p){
        position-=p;
        return *this;
}

#define tor 0.0000001
#include <stdio.h>
bool Ray3D::intersect( const Plane3D& plane , Point3D& p , float& t ) const
{
    double f = plane.normal.dot( plane.normal*plane.distance - position );
    double g = plane.normal.dot( direction                              );
    if( fabs(g) > tor )
    {
        t = f / g;
        p = position + ( direction * t );
        return true;
    }
    else
        return false;
}

//////////////
// Matrix3D //
//////////////
/////////////////////
// Animation stuff //
/////////////////////

//ming
Matrix3D::Matrix3D(double e1, double e2, double e3, double e4, double e5, double e6, double e7, double e8, double e9)
{
    m[0][0]=e1;
    m[0][1]=e2;
    m[0][2]=e3;
    m[1][0]=e4;
    m[1][1]=e5;
    m[1][2]=e6;
    m[2][0]=e7;
    m[2][1]=e8;
    m[2][2]=e9;
}

Matrix3D::Matrix3D(const Point3D& eulerAngle)
{
        double cosx = cos(eulerAngle.p[0]);
        double sinx = sin(eulerAngle.p[0]);
        double cosy = cos(eulerAngle.p[1]);
        double siny = sin(eulerAngle.p[1]);
        double cosz = cos(eulerAngle.p[2]);
        double sinz = sin(eulerAngle.p[2]);
        // Rotation matrices from http://mathworld.wolfram.com/RotationMatrix.html
        Matrix3D xRotation( 1, 0, 0, 0, cosx, sinx, 0, -sinx, cosx );
        Matrix3D yRotation( cosy, 0, -siny, 0, 1, 0, siny, 0, cosy );
        Matrix3D zRotation( cosz, sinz, 0, -sinz, cosz, 0, 0, 0, 1 );
        (*this) = zRotation*yRotation*xRotation;
}

Matrix3D::Matrix3D(void){
        m[0][0]=m[1][1]=m[2][2]=1;
        m[0][1]=m[1][0]=m[2][0]=m[0][2]=0;
        m[1][2]=m[2][1]=0;
}

Matrix3D::Matrix3D(const Matrix4D& n){
        m[0][0]=n.m[0][0];
        m[0][1]=n.m[0][1];
        m[0][2]=n.m[0][2];
        m[1][0]=n.m[1][0];
        m[1][1]=n.m[1][1];
        m[1][2]=n.m[1][2];
        m[2][0]=n.m[2][0];
        m[2][1]=n.m[2][1];
        m[2][2]=n.m[2][2];
}

double& Matrix3D::index(int i,int j){return m[i][j];}
double& Matrix3D::operator() (int i,int j){return index(i,j);}

double  Matrix3D::det(void) const {
        return m[0][0]*(m[1][1]*m[2][2]-m[1][2]*m[2][1])-m[1][0]*(m[0][1]*m[2][2]-m[0][2]*m[2][1])+m[2][0]*(m[0][1]*m[1][2]-m[0][2]*m[1][1]);
}
Matrix3D Matrix3D::operator - (void) const {
        Matrix3D n;
        n.m[0][0]=-m[0][0];
        n.m[0][1]=-m[0][1];
        n.m[0][2]=-m[0][2];
        n.m[1][0]=-m[1][0];
        n.m[1][1]=-m[1][1];
        n.m[1][2]=-m[1][2];
        n.m[2][0]=-m[2][0];
        n.m[2][1]=-m[2][1];
        n.m[2][2]=-m[2][2];
        return n;
}
Matrix3D  Matrix3D::operator* (const Matrix3D& n) const {
        Matrix3D o;
        o.m[0][0]=m[0][0]*n.m[0][0]+m[1][0]*n.m[0][1]+m[2][0]*n.m[0][2];
        o.m[1][0]=m[0][0]*n.m[1][0]+m[1][0]*n.m[1][1]+m[2][0]*n.m[1][2];
        o.m[2][0]=m[0][0]*n.m[2][0]+m[1][0]*n.m[2][1]+m[2][0]*n.m[2][2];
        o.m[0][1]=m[0][1]*n.m[0][0]+m[1][1]*n.m[0][1]+m[2][1]*n.m[0][2];
        o.m[1][1]=m[0][1]*n.m[1][0]+m[1][1]*n.m[1][1]+m[2][1]*n.m[1][2];
        o.m[2][1]=m[0][1]*n.m[2][0]+m[1][1]*n.m[2][1]+m[2][1]*n.m[2][2];
        o.m[0][2]=m[0][2]*n.m[0][0]+m[1][2]*n.m[0][1]+m[2][2]*n.m[0][2];
        o.m[1][2]=m[0][2]*n.m[1][0]+m[1][2]*n.m[1][1]+m[2][2]*n.m[1][2];
        o.m[2][2]=m[0][2]*n.m[2][0]+m[1][2]*n.m[2][1]+m[2][2]*n.m[2][2];
        return o;
}
Matrix3D& Matrix3D::operator*=(const Matrix3D& m){
        Matrix3D temp;
        temp=*this;
        *this=temp*m;
        return *this;
}
Matrix3D Matrix3D::transpose(void) const  {
        Matrix3D n;
        n.m[0][0]=m[0][0];
        n.m[0][1]=m[1][0];
        n.m[0][2]=m[2][0];
        n.m[1][0]=m[0][1];
        n.m[1][1]=m[1][1];
        n.m[1][2]=m[2][1];
        n.m[2][0]=m[0][2];
        n.m[2][1]=m[1][2];
        n.m[2][2]=m[2][2];
        return n;
}
Matrix3D  Matrix3D::operator+ (const Matrix3D& n) const {
        Matrix3D o;
        o.m[0][0]=m[0][0]+n.m[0][0];
        o.m[0][1]=m[0][1]+n.m[0][1];
        o.m[0][2]=m[0][2]+n.m[0][2];
        o.m[1][0]=m[1][0]+n.m[1][0];
        o.m[1][1]=m[1][1]+n.m[1][1];
        o.m[1][2]=m[1][2]+n.m[1][2];
        o.m[2][0]=m[2][0]+n.m[2][0];
        o.m[2][1]=m[2][1]+n.m[2][1];
        o.m[2][2]=m[2][2]+n.m[2][2];
        return o;
}
Matrix3D& Matrix3D::operator+=(const Matrix3D& n){
        m[0][0]+=n.m[0][0];
        m[0][1]+=n.m[0][1];
        m[0][2]+=n.m[0][2];
        m[1][0]+=n.m[1][0];
        m[1][1]+=n.m[1][1];
        m[1][2]+=n.m[1][2];
        m[2][0]+=n.m[2][0];
        m[2][1]+=n.m[2][1];
        m[2][2]+=n.m[2][2];
        return *this;
}
Matrix3D  Matrix3D::operator- (const Matrix3D& n) const {
        Matrix3D o;
        o.m[0][0]=m[0][0]-n.m[0][0];
        o.m[0][1]=m[0][1]-n.m[0][1];
        o.m[0][2]=m[0][2]-n.m[0][2];
        o.m[1][0]=m[1][0]-n.m[1][0];
        o.m[1][1]=m[1][1]-n.m[1][1];
        o.m[1][2]=m[1][2]-n.m[1][2];
        o.m[2][0]=m[2][0]-n.m[2][0];
        o.m[2][1]=m[2][1]-n.m[2][1];
        o.m[2][2]=m[2][2]-n.m[2][2];
        return o;
}
Matrix3D& Matrix3D::operator-=(const Matrix3D& n){
        m[0][0]-=n.m[0][0];
        m[0][1]-=n.m[0][1];
        m[0][2]-=n.m[0][2];
        m[1][0]-=n.m[1][0];
        m[1][1]-=n.m[1][1];
        m[1][2]-=n.m[1][2];
        m[2][0]-=n.m[2][0];
        m[2][1]-=n.m[2][1];
        m[2][2]-=n.m[2][2];
        return *this;
}

Matrix3D  Matrix3D::operator* (double f) const {
        Matrix3D o;
        o.m[0][0]=m[0][0]*f;
        o.m[0][1]=m[0][1]*f;
        o.m[0][2]=m[0][2]*f;
        o.m[1][0]=m[1][0]*f;
        o.m[1][1]=m[1][1]*f;
        o.m[1][2]=m[1][2]*f;
        o.m[2][0]=m[2][0]*f;
        o.m[2][1]=m[2][1]*f;
        o.m[2][2]=m[2][2]*f;
        return o;
}
Matrix3D& Matrix3D::operator*=(double f){
        m[0][0]*=f;
        m[0][1]*=f;
        m[0][2]*=f;
        m[1][0]*=f;
        m[1][1]*=f;
        m[1][2]*=f;
        m[2][0]*=f;
        m[2][1]*=f;
        m[2][2]*=f;
        return *this;
}
Matrix3D  Matrix3D::operator/ (double f) const {
        Matrix3D o;
        o.m[0][0]=m[0][0]/f;
        o.m[0][1]=m[0][1]/f;
        o.m[0][2]=m[0][2]/f;
        o.m[1][0]=m[1][0]/f;
        o.m[1][1]=m[1][1]/f;
        o.m[1][2]=m[1][2]/f;
        o.m[2][0]=m[2][0]/f;
        o.m[2][1]=m[2][1]/f;
        o.m[2][2]=m[2][2]/f;
        return o;
}
Matrix3D& Matrix3D::operator/=(double f){
        m[0][0]/=f;
        m[0][1]/=f;
        m[0][2]/=f;
        m[1][0]/=f;
        m[1][1]/=f;
        m[1][2]/=f;
        m[2][0]/=f;
        m[2][1]/=f;
        m[2][2]/=f;
        return *this;
}

Matrix3D Matrix3D::invert(void) const {
        Matrix3D n;
        double d;

        n.m[0][0]= m[1][1]*m[2][2]-m[1][2]*m[2][1];
        n.m[1][0]=-m[0][1]*m[2][2]+m[0][2]*m[2][1];
        n.m[2][0]= m[0][1]*m[1][2]-m[0][2]*m[1][1];
        n.m[0][1]=-m[1][0]*m[2][2]+m[1][2]*m[2][0];
        n.m[1][1]= m[0][0]*m[2][2]-m[0][2]*m[2][0];
        n.m[2][1]=-m[0][0]*m[1][2]+m[0][2]*m[1][0];
        n.m[0][2]= m[1][0]*m[2][1]-m[1][1]*m[2][0];
        n.m[1][2]=-m[0][0]*m[2][1]+m[0][1]*m[2][0];
        n.m[2][2]= m[0][0]*m[1][1]-m[0][1]*m[1][0];
        d=m[0][0]*n.m[0][0]+m[1][0]*n.m[1][0]+m[2][0]*n.m[2][0];
        return n/d;
}
int Matrix3D::Invert(const Matrix3D& m,Matrix3D& n){
        double d;

        n.m[0][0]= m.m[1][1]*m.m[2][2]-m.m[1][2]*m.m[2][1];
        n.m[1][0]=-m.m[0][1]*m.m[2][2]+m.m[0][2]*m.m[2][1];
        n.m[2][0]= m.m[0][1]*m.m[1][2]-m.m[0][2]*m.m[1][1];
        n.m[0][1]=-m.m[1][0]*m.m[2][2]+m.m[1][2]*m.m[2][0];
        n.m[1][1]= m.m[0][0]*m.m[2][2]-m.m[0][2]*m.m[2][0];
        n.m[2][1]=-m.m[0][0]*m.m[1][2]+m.m[0][2]*m.m[1][0];
        n.m[0][2]= m.m[1][0]*m.m[2][1]-m.m[1][1]*m.m[2][0];
        n.m[1][2]=-m.m[0][0]*m.m[2][1]+m.m[0][1]*m.m[2][0];
        n.m[2][2]= m.m[0][0]*m.m[1][1]-m.m[0][1]*m.m[1][0];
        d=m.m[0][0]*n.m[0][0]+m.m[1][0]*n.m[1][0]+m.m[2][0]*n.m[2][0];
        if(d!=0){
                n/=d;
                return 1;
        }
        else{return 0;}
}

Point3D Matrix3D::operator*(const Point3D& p) const {
        return Point3D(m[0][0]*p.p[0]+m[1][0]*p.p[1]+m[2][0]*p.p[2],m[0][1]*p.p[0]+m[1][1]*p.p[1]+m[2][1]*p.p[2],m[0][2]*p.p[0]+m[1][2]*p.p[1]+m[2][2]*p.p[2]);
}
Ray3D Matrix3D::operator* (const Ray3D& r) const {
        return Ray3D((*this)*r.position,(*this)*r.direction);
}

Matrix3D Matrix3D::IdentityMatrix(void){
        return Matrix3D();
}
Point3D Matrix3D::toEuler(void) const {
        Point3D e;
        e[1]=asin(-m[0][2]);
        if(sqrt(m[0][0]*m[0][0]+m[0][1]*m[0][1])>0.000001){
                e[2]=atan2(m[0][1],m[0][0]);
                e[0]=atan2(m[1][2],m[2][2]);
        }
        else{
                e[2]=atan2(m[1][0],m[0][2]);
                e[0]=0;
        }
        return e;
}
Point3D Matrix3D::toEuler(const Point3D& e) const{
        Point3D euler=toEuler();
        for(int i=0;i<3;i++){
                double d=fabs(euler.p[i]-e.p[i]);
                double a=euler.p[i];
                if(euler.p[i]<e.p[i]){
                        while(euler.p[i]<e.p[i]){
                                euler.p[i]+=2*PI;
                                if(fabs(euler.p[i]-e.p[i])<d){
                                        d=fabs(euler.p[i]-e.p[i]);
                                        a=euler.p[i];
                                }
                        }
                }
                else{
                        while(euler.p[i]>e.p[i]){
                                euler.p[i]-=2*PI;
                                if(fabs(euler.p[i]-e.p[i])<d){
                                        d=fabs(euler.p[i]-e.p[i]);
                                        a=euler.p[i];
                                }
                        }
                }
                euler.p[i]=a;
        }
        return euler;
}
double Matrix3D::squareNorm(void) const{
        double n=0;
        for(int i=0;i<3;i++){for(int j=0;j<3;j++){n+=m[i][j]*m[i][j];}}
        return n;
}
double Matrix3D::SquareL2Difference(const Matrix3D& m1,const Matrix3D& m2){
        double n=0;
        for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                        double temp=m1.m[i][j]-m2.m[i][j];
                        n+=temp*temp;
                }
        }
        return n;
}

// Code borrowed from:
// Linear Combination of Transformations
// Marc Alexa
Matrix3D Matrix3D::SquareRoot(const Matrix3D& m,double eps){
        Matrix3D X,Y;
        X=m;
        Y=IdentityMatrix();
        while(SquareL2Difference(X*X,m)>eps*eps){
                Matrix3D iX=X.invert();
                Matrix3D iY=Y.invert();
                X=(X+iY)/2;
                Y=(Y+iX)/2;
        }
        return X;
}
Matrix3D Matrix3D::Log(const Matrix3D& m,double eps){
        Matrix3D I=IdentityMatrix();
        Matrix3D X,Z,A=m;
        int i,k=0;
        while(SquareL2Difference(A,I)>0.25){
                A=SquareRoot(A,eps);
                k++;
        }
        A=I-A;
        X=Z=A;
        i=1;
        while(Z.squareNorm()>eps*eps){
                Z=Z*A;
                i++;
                X+=Z*(1.0/i);
        }
        return X*(-pow(2.0,(double)k));
}
Matrix3D Matrix3D::symmetrize(void) const{
        Matrix3D n;
        n.m[0][0]=m[0][0];
        n.m[1][1]=m[1][1];
        n.m[2][2]=m[2][2];
        n.m[1][0]=n.m[0][1]=(m[0][1]+m[1][0])/2;
        n.m[1][2]=n.m[2][1]=(m[2][1]+m[1][2])/2;
        n.m[0][2]=n.m[2][0]=(m[2][0]+m[0][2])/2;
        return n;
}
Matrix3D Matrix3D::skewSymmetrize(void) const{
        Matrix3D n;
        n.m[0][0]=n.m[1][1]=n.m[2][2]=0;
        n.m[1][0]=(m[1][0]-m[0][1])/2;
        n.m[0][1]=-n.m[1][0];
        n.m[2][0]=(m[2][0]-m[0][2])/2;
        n.m[0][2]=-n.m[2][0];
        n.m[1][2]=(m[1][2]-m[2][1])/2;
        n.m[2][1]=-n.m[1][2];
        return n;
}

//////////////
// Matrix4D //
//////////////
Matrix4D::Matrix4D(void){
        m[0][0]=m[1][1]=m[2][2]=m[3][3]=1;
        m[0][1]=m[1][0]=m[2][0]=m[0][2]=m[3][0]=m[0][3]=0;
        m[1][2]=m[2][1]=m[1][3]=m[3][1]=m[2][3]=m[3][2]=0;
}
Matrix4D::Matrix4D(const Matrix3D& n){
        m[3][0]=m[3][1]=m[3][2]=0;
        m[0][3]=m[1][3]=m[2][3]=0;
        m[3][3]=1;

        m[0][0]=n.m[0][0];
        m[1][1]=n.m[1][1];
        m[2][2]=n.m[2][2];
        m[1][0]=n.m[1][0];
        m[0][1]=n.m[0][1];
        m[2][0]=n.m[2][0];
        m[0][2]=n.m[0][2];
        m[2][1]=n.m[2][1];
        m[1][2]=n.m[1][2];
}
Matrix4D::Matrix4D(const Matrix3D& n,const Point3D& p){
        m[3][0]=p.p[0];
        m[3][1]=p.p[1];
        m[3][2]=p.p[2];
        m[0][3]=m[1][3]=m[2][3]=0;
        m[3][3]=1;

        m[0][0]=n.m[0][0];
        m[1][1]=n.m[1][1];
        m[2][2]=n.m[2][2];
        m[1][0]=n.m[1][0];
        m[0][1]=n.m[0][1];
        m[2][0]=n.m[2][0];
        m[0][2]=n.m[0][2];
        m[2][1]=n.m[2][1];
        m[1][2]=n.m[1][2];
}

double& Matrix4D::index(int i,int j){return m[i][j];}
double& Matrix4D::operator() (int i,int j){return index(i,j);}

double  Matrix4D::det(void) const {
        double d=0.0;
        int i;
        for(i=0;i<4;i++){
                if((i%2)==0){d+=subDet(i,0)*m[i][0];}
                else{d-=subDet(i,0)*m[i][0];}
        }
        return d;
}
double Matrix4D::subDet(int c1,int r1,int c2,int r2) const {
        return this->m[c1][r1]*this->m[c2][r2]-this->m[c1][r2]*this->m[c2][r1];
}
double Matrix4D::subDet(int c,int r) const {
        int i;
        int c1,r1,c2,r2,row;
        double d=0,sgn=1.0;
        row=0;
        if(row==r){row++;}
        for(i=0;i<4;i++){
                if(i==c){continue;}
                c1=0;
                while(c1==i || c1==c){c1++;}
                c2=c1+1;
                while(c2==i || c2==c){c2++;}
                r1=0;
                while(r1==row || r1==r){r1++;}
                r2=r1+1;
                while(r2==row || r2==r){r2++;}

                d+=sgn*this->m[i][row]*subDet(c1,r1,c2,r2);
                sgn*=-1.0;
        }
        return d;
}
Matrix4D Matrix4D::operator- (void) const{
        Matrix4D n;
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){n.m[i][j]=-m[i][j];}}
        return n;
}

Matrix4D Matrix4D::mult(const Matrix4D& n) const {
        int i,j,k;
        Matrix4D o;
        for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                        o(i,j)=0.0;
                        for(k=0;k<4;k++){o(i,j)+=m[k][j]*n.m[i][k];}
                }
        }
        return o;
}
Matrix4D  Matrix4D::operator* (const Matrix4D& m) const {return mult(m);}
Matrix4D& Matrix4D::operator*=(const Matrix4D& m){
        Matrix4D temp;
        temp=*this;
        *this=temp*m;
        return *this;
}
Matrix4D Matrix4D::transpose(void) const  {
        int i,j;
        Matrix4D n;
        for(i=0;i<4;i++){
                for(j=0;j<4;j++){n(i,j)=this->m[j][i];}
        }
        return n;
}
Matrix4D Matrix4D::add(const Matrix4D& n) const {
        Matrix4D o;
        int i,j;

        for(i=0;i<4;i++){for(j=0;j<4;j++){o(i,j)=m[i][j]+n.m[i][j];}}
        return o;
}
Matrix4D  Matrix4D::operator+ (const Matrix4D& m) const {return add(m);}
Matrix4D& Matrix4D::operator+=(const Matrix4D& n){
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){m[i][j]+=n.m[i][j];}}
        return *this;
}
Matrix4D Matrix4D::subtract(const Matrix4D& n) const {
        Matrix4D o;
        int i,j;

        for(i=0;i<4;i++){for(j=0;j<4;j++){o(i,j)=m[i][j]-n.m[i][j];}}
        return o;
}
Matrix4D  Matrix4D::operator- (const Matrix4D& m) const {return subtract(m);}
Matrix4D& Matrix4D::operator-=(const Matrix4D& n){
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){m[i][j]-=n.m[i][j];}}
        return *this;
}

Matrix4D Matrix4D::mult(double f) const {
        Matrix4D n;
        for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                        n(i,j)=m[i][j]*f;
                }
        }
        return n;
}
Matrix4D  Matrix4D::operator* (double f) const {return mult(f);}
Matrix4D& Matrix4D::operator*=(double f){
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){this->m[i][j]*=f;}}
        return *this;
}
Matrix4D  Matrix4D::div(double f) const {return mult(1.0/f);}
Matrix4D  Matrix4D::operator/ (double f) const {return mult(1.0/f);}
Matrix4D& Matrix4D::operator/=(double f){
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){this->m[i][j]/=f;}}
        return *this;
}

Matrix4D Matrix4D::invert(void) const {
        int i,j;
        Matrix4D m;
        double d;

        d=det();
        for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                        if((i+j)%2==0){m(j,i)=subDet(i,j)/d;}
                        else{m(i,j)=-subDet(j,i)/d;}
                }
        }
        return m;
}
int Matrix4D::Invert(const Matrix4D& in,Matrix4D& out){
        int i,j;
        double d;

        d=in.det();
        if(d==0.0){return 0;}
        for(i=0;i<4;i++){
                for(j=0;j<4;j++){
                        if((i+j)%2==0){out(j,i)=in.subDet(i,j)/d;}
                        else{out(i,j)=-in.subDet(j,i)/d;}
                }
        }
        return 1;
}

Point3D Matrix4D::operator*(const Point3D& p) const {return multPosition(p);}
Point3D Matrix4D::multPosition(const Point3D& p) const {
        Point3D q;
        double t=0;
        int i,j;
        for(i=0;i<3;i++){
                q[i]=this->m[3][i];
                for(j=0;j<3;j++){q[i]+=this->m[j][i]*p.p[j];}
        }
        t=m[0][3]+m[1][3]+m[2][3]+m[3][3];
        return q/t;
}
Point3D Matrix4D::multDirection(const Point3D& p) const {
        Point3D q;
        int i,j;
        for(i=0;i<3;i++){
                q[i]=0.0;
                for(j=0;j<3;j++){q[i]+=this->m[j][i]*p.p[j];}
        }
        return q;
}
Point3D Matrix4D::multNormal(const Point3D& p) const {
        return transpose().invert().multDirection(p);
}

Ray3D Matrix4D::mult(const Ray3D& r) const {
        Ray3D q;
        q.position=multPosition(r.position);
        q.direction=multDirection(r.direction);
        return q;
}
Ray3D Matrix4D::operator* (const Ray3D& r) const {return mult(r);}

double det(const Matrix4D& m){return m.det();}
Matrix4D Matrix4D::IdentityMatrix(void){
        Matrix4D m;
        int i,j;
        for(i=0;i<4;i++){for(j=0;j<4;j++){m(i,j)=(i==j)?1.0:0.0;}}
        return m;
}
Point3D Matrix4D::toEuler(void) const {
        Point3D e;
        e[1]=asin(-m[0][2]);
        if(sqrt(m[0][0]*m[0][0]+m[0][1]*m[0][1])>0.000001){
                e[2]=atan2(m[0][1],m[0][0]);
                e[0]=atan2(m[1][2],m[2][2]);
        }
        else{
                e[2]=atan2(m[1][0],m[0][2]);
                e[0]=0;
        }
        return e;
}
double Matrix4D::squareNorm(void) const{
        double n=0;
        for(int i=0;i<4;i++){for(int j=0;j<4;j++){n+=m[i][j]*m[i][j];}}
        return n;
}
double Matrix4D::SquareL2Difference(const Matrix4D& m1,const Matrix4D& m2){
        double n=0;
        for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                        double temp=m1.m[i][j]-m2.m[i][j];
                        n+=temp*temp;
                }
        }
        return n;
}

/* While these Exp and Log implementations are the direct implementations of the Taylor series, the Log
 * function tends to run into convergence issues so we use the other ones:*/

///////////////////
// BoundingBox3D //
///////////////////
BoundingBox3D::BoundingBox3D(void){p[0]=p[1]=Point3D(0,0,0);}
BoundingBox3D::BoundingBox3D(const Point3D& p1,const Point3D& p2){
        p[0]=Point3D((p1.p[0]<=p2.p[0])? p1.p[0]:p2.p[0],(p1.p[1]<=p2.p[1])? p1.p[1]:p2.p[1],(p1.p[2]<=p2.p[2])? p1.p[2]:p2.p[2]);
        p[1]=Point3D((p1.p[0]>=p2.p[0])? p1.p[0]:p2.p[0],(p1.p[1]>=p2.p[1])? p1.p[1]:p2.p[1],(p1.p[2]>=p2.p[2])? p1.p[2]:p2.p[2]);
}
BoundingBox3D::BoundingBox3D(const Point3D* pList,int pSize){
        Point3D vMin,vMax;

        if(pSize<=0){p[0]=p[1]=Point3D(0,0,0);}
        else{
                vMin=vMax=pList[0];
                for(int i=0;i<pSize;i++){
                        for(int j=0;j<3;j++){
                                if(vMin[j]>pList[i].p[j]){vMin[j]=pList[i].p[j];}
                                if(vMax[j]<pList[i].p[j]){vMax[j]=pList[i].p[j];}
                        }
                }
                p[0]=vMin;
                p[1]=vMax;
        }
}
BoundingBox3D BoundingBox3D::operator+ (const BoundingBox3D& b) const {
        Point3D pList[4];
        Point3D q;

        if((b.p[0]-b.p[1]).squareNorm()==0.0){return *this;}
        if((p[0]-p[1]).squareNorm()==0.0){return b;}
        pList[0]=p[0];
        pList[1]=p[1];
        pList[2]=b.p[0];
        pList[3]=b.p[1];
        return BoundingBox3D(pList,4);
}
BoundingBox3D& BoundingBox3D::operator+=(const BoundingBox3D& b){
        //Point3D pList[4];
        Point3D q;

        if((b.p[0]-b.p[1]).squareNorm()==0.0){return *this;}
        if((p[0]-p[1]).squareNorm()==0.0){
                p[0]=b.p[0];
                p[1]=b.p[1];
                return *this;
        }

        for(int i=0;i<3;i++){
                if(b.p[0].p[i]<p[0].p[i]){p[0].p[i]=b.p[0].p[i];}
                if(b.p[1].p[i]>p[1].p[i]){p[1].p[i]=b.p[1].p[i];}
        }
        return *this;
}


BoundingBox3D BoundingBox3D::transform(const Matrix4D& m) const {
        Point3D v[8];
        int i,j,k;

        for(i=0;i<2;i++){
                for(j=0;j<2;j++){
                        for(k=0;k<2;k++){
                                v[i+2*j+4*k]=m.multPosition(Point3D(p[i].p[0],p[j].p[1],p[k].p[2]));
                        }
                }
        }
        return BoundingBox3D(v,8);
}
