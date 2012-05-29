#ifndef GEOMETRY_INCLUDED
#define GEOMETRY_INCLUDED

#define RAYEPS 1e-10


#define PI 3.1415926535897932384


/** This class represents a 2D vector */
class Point2D{
public:
        /** The coordinates of the point */
        double p[2];
        Point2D(void);
        Point2D(const double& x,const double& y);

        /** This method returns the value of the indexed coefficient.*/
        double& operator[] (const int& index);
        /** This method returns the value of the indexed coefficient.*/
        double& index(const int& i);

        /** This method returns the dot product of two points.*/
        double dot(const Point2D& pt) const;

        /** This method returns the length of a point. */
        double length(void) const;
        /** This method returns the square of the length of a point.*/
        double squareNorm(void) const;

        /** This method returns a unit vector that points in the same direction as the point. */
        Point2D unit(void) const;

        /** This method return the negative of the point. */
        Point2D negate(void) const;
        /** This method return the negative of the point. */
        Point2D operator- (void) const;

        /** This method scales a point by a constant factor and returns a new point. */
        Point2D scale(double scl) const;
        /** This method scales a point by a constant factor and returns a new point. */
        Point2D  operator* (double scale) const;
        /** This method scales the current point by a constant factor. */
        Point2D& operator*=(double scale);

        /** This method divides the coefficients of a point by a constant factor and returns a new point. */
        Point2D  operator/ (double scale) const;
        /** This method divides the coefficients of the current point by a constant factor. */
        Point2D& operator/=(double scale);

        /** This method adds two points and returns their sum. */
        Point2D add(const Point2D& pt) const;
        /** This method adds two points and returns their sum. */
        Point2D  operator+ (const Point2D& pt) const;
        /** This method adds a point to the current point. */
        Point2D& operator+=(const Point2D& pt);

        /** This method subtracts two points and returns their difference. */
        Point2D subtract(const Point2D& pt) const;
        /** This method subtracts two points and returns their difference. */
        Point2D  operator- (const Point2D& pt) const;
        /** This method subtracts a point from the current point. */
        Point2D& operator-=(const Point2D& pt);

        /** This method performs a component-wise multiplication of two ponts and returns the product. */
        Point2D mult(const Point2D& pt) const;
        /** This method performs a component-wise multiplication of two ponts and returns the product. */
        Point2D operator* (const Point2D& pt) const;
        /** This method multiplies the coefficients of the current point by the coefficients of the input point. */
        Point2D& operator*=(const Point2D& pt);

        /** This method performs a component-wise division of two ponts and returns the ratio. */
        Point2D div(const Point2D& pt) const;
        /** This method performs a component-wise division of two ponts and returns the ratio. */
        Point2D  operator/ (const Point2D& pt) const;
        /** This method divides the coefficients of the current point by the coefficients of the input point. */
        Point2D& operator/=(const Point2D& pt);
};

/** This class represents a 3D vector */
class Point3D{
public:
        /** The coordinates of the point */
        double p[3];
        Point3D(void);
        Point3D(const double& x,const double& y,const double& z);

        /** This method returns the value of the indexed coefficient.*/
        double& operator[] (const int& index);
        /** This method returns the value of the indexed coefficient.*/
        double& index(const int& i);

        /** This method returns the dot product of two points.*/
        double dot(const Point3D& pt) const;

        /** This method returns the length of a point. */
        double length(void) const;
        /** This method returns the square of the length of a point.*/
        double squareNorm(void) const;

        /** This method returns a unit vector that points in the same direction as the point. */
        Point3D unit(void) const;

        /** This method return the negative of the point. */
        Point3D negate(void) const;
        /** This method return the negative of the point. */
        Point3D operator- (void) const;

        /** This method scales a point by a constant factor and returns a new point. */
        Point3D  scale(double scale) const;
        /** This method scales a point by a constant factor and returns a new point. */
        Point3D  operator* (double scale) const;
        /** This method scales the current point by a constant factor. */
        Point3D& operator*=(double scale);

        /** This method divides the coefficients of a point by a constant factor and returns a new point. */
        Point3D  operator/ (double scale) const;
        /** This method divides the coefficients of the current point by a constant factor. */
        Point3D& operator/=(double scale);

        /** This method adds two points and returns their sum. */
        Point3D  add(const Point3D& pt) const;
        /** This method adds two points and returns their sum. */
        Point3D  operator+ (const Point3D& pt) const;
        /** This method adds a point to the current point. */
        Point3D& operator+=(const Point3D& pt);

        /** This method subtracts two points and returns their difference. */
        Point3D  subtract(const Point3D& pt) const;
        /** This method subtracts two points and returns their difference. */
        Point3D  operator- (const Point3D& pt) const;
        /** This method subtracts a point from the current point. */
        Point3D& operator-=(const Point3D& pt);

        /** This method performs a component-wise multiplication of two ponts and returns the product. */
        Point3D mult(const Point3D& pt) const;
        /** This method performs a component-wise multiplication of two ponts and returns the product. */
        Point3D  operator* (const Point3D& pt) const;
        /** This method multiplies the coefficients of the current point by the coefficients of the input point. */
        Point3D& operator*=(const Point3D& pt);

        /** This method performs a component-wise division of two ponts and returns the ratio. */
        Point3D div(const Point3D& pt) const;
        /** This method performs a component-wise division of two ponts and returns the ratio. */
        Point3D  operator/ (const Point3D& pt) const;
        /** This method divides the coefficients of the current point by the coefficients of the input point. */
        Point3D& operator/=(const Point3D& pt);

        /** This method returns the cross-product of two points. */
        Point3D crossProduct(const Point3D& pt) const;
        /** This method returns the cross-product of two points. */
        Point3D  operator^ (const Point3D& pt) const;
        /** This method set the current point to be equal to the cross-product of itself with the input point. */
        Point3D& operator^=(const Point3D& pt);
};


/** This class represents a Plane in 3D. */
class Plane3D{
public:
        //ming
        Point3D position;

        /** The normal of the plane */
        Point3D normal;
        /** (Minus) the normal distance of the plane from the origin */
        double distance;

        Plane3D(void);
        /** This constructor generates a plane with the specified normal, passing through the point pt.*/
        Plane3D(const Point3D& normal,const Point3D& pt);
        /** This constructor generates a plane that contains the triangle specified by the three vertices. */
        Plane3D(const Point3D& p1,const Point3D& p2,const Point3D& p3);

        /** This method evalues the plane equation at the specified point, returning p.dot(normal)+distance. */
        double evaluate(const Point3D& p) const;
        /** This method evalues the plane equation at the specified point, returning p.dot(normal)+distance. */
        double operator()(const Point3D& p) const;

        /** This method orients the plane so that the value of the plane function at p is non-negative. */
        void makePositive(const Point3D& p);
};

/** This class represents a Ray in 3D.*/
class Ray3D{
public:
        /** The starting point of the ray */
        Point3D position;
        /** The direction of the ray */
        Point3D direction;

        Ray3D(void);
        Ray3D(const Point3D& pos,const Point3D& dir);

        /** This method computes the translation of the ray by p and returns the translated ray.*/
        Ray3D  add(const Point3D& p) const;
        /** This method computes the translation of the ray by p and returns the translated ray.*/
        Ray3D  operator+ (const Point3D& p) const;
        /** This method translates the current ray by p.*/
        Ray3D& operator+=(const Point3D& p);
        /** This method computes the translation of the ray by -p and returns the translated ray.*/
        Ray3D  subtract(const Point3D& p) const;
        /** This method computes the translation of the ray by -p and returns the translated ray.*/
        Ray3D  operator- (const Point3D& p) const;
        /** This method translates the current ray by -p.*/
        Ray3D& operator-=(const Point3D& p);

        bool intersect( const Plane3D& plane , Point3D& p , float& t ) const;

        /** This method returns the point at a distance of t along the ray. */
        Point3D operator() (double t) const;
};

/** This class represents a 3x3 matrix. */
class Matrix3D{
public:
        /** The actual matrix entries */
        double m[3][3];

        /** This constructor generates an identity matrix */
        Matrix3D(void);
        /** This constructor generates a rotation matrix from the specified Euler angles */
        Matrix3D(const Point3D& eulerAngles);
        /** This constructor generates a rotation matrix from the specified quaternion */
        Matrix3D(const class Quaternion& q);
        /** This constructor generates a matrix from the top 3x3 matrix of the Matrix4D */
        Matrix3D(const class Matrix4D& m);

        //ming
        Matrix3D( double e1 , double e2 , double e3 , double e4 , double e5 , double e6 , double e7 , double e8 , double e9 );


        /** This method returns the entry of the matrix in the col-th column and the row-th row.*/
        double& operator() (int col,int row);
        /** This method returns the entry of the matrix in the col-th column and the row-th row.*/
        double& index(int col,int row);

        /** This method returns the determinant of the matrix.*/
        double det(void) const;

        /** This method returns the negative of the matrix */
        Matrix3D operator- (void) const;

        /** This method multiplies two matrices and returns the product.*/
        Matrix3D  operator* (const Matrix3D& m) const;
        /** This method multiplies the current matrix (on the right) by the input matrix..*/
        Matrix3D& operator*=(const Matrix3D& m);

        /** This method adds two matrices and returns the sum. */
        Matrix3D  operator+ (const Matrix3D& m) const;
        /** This method adds the input matrix to the current matrix. */
        Matrix3D& operator+=(const Matrix3D& m);

        /** This method subtracts two matrices and returns the difference. */
        Matrix3D  operator- (const Matrix3D& m) const;
        /** This method subtracts the input matrix from the current matrix. */
        Matrix3D& operator-=(const Matrix3D& m);

        /** This method scales the entries of a matrix and returns a new matrix. */
        Matrix3D  operator* (double f) const;
        /** This method scales the entries of the current matrix. */
        Matrix3D& operator*=(double f);
        /** This method divides the entries of a matrix and returns a new matrix. */
        Matrix3D  operator/ (double f) const;
        /** This method divides the entries of the current matrix. */
        Matrix3D& operator/=(double f);

        /** This method returns the transpose of a matrix. (Note that it does not change the entries of the current matrix.)*/
        Matrix3D transpose(void) const;

        /** This method returns the inverse of a matrix. (Note that it does not change the entries of the current matrix.)*/
        Matrix3D invert(void) const;

        /** This static method tries to invert the input matrix and write it out into the output. A value of 0 is returned if the matrix has 0 determinant.*/
        static int Invert(const Matrix3D& in,Matrix3D& out);

        /** This method transforms a 3D point. */
        Point3D operator*(const Point3D& p) const;

        /** This method applies transformation to a ray.*/
        Ray3D operator* (const Ray3D& ray) const;

        /** This static method returns the identity matrix. */
        static Matrix3D IdentityMatrix(void);

        /** This method returns the Euler Angles of a rotation matrix */
        Point3D toEuler(void) const;
        /** Because the Euler angles are not unique, the following method returns the
          * Euler angles closest to the input ones */
        Point3D toEuler(const Point3D& euler) const;

        /** This method returns the sum of the squares of the matrix entries */
        double squareNorm(void) const;
        /** This method returns sum of the squares of the entries of the difference matrix. */
        static double SquareL2Difference(const Matrix3D& m1,const Matrix3D& m2);

        /** This method returns the exponent of a matrix */
        static Matrix3D Exp(const Matrix3D& m,int iter=100);
        /** This method returns the logarithm of a matrix */
        static Matrix3D Log(const Matrix3D& m,double eps=0.0001);
        /** This method returns the square-root of a matrix */
        static Matrix3D SquareRoot(const Matrix3D& m,double eps=0.000001);

        /** This method computes the SVD decomposition of the upper 3x3 matrix, such that
          * r1 and r2 are rotations and the upper 3x3 matrix is equal to r1*diagonal*r2 */
        void SVD(Matrix3D& r1,Matrix3D& diagonal,Matrix3D& r2) const;

        /** This method factors a matrix as the product of a rotation and a symmetric matrix */
        void Factor(Matrix3D& rot,Matrix3D& sym) const;

        /** This method returns the closest 3x3 rotation matrix */
        Matrix3D closestRotation(void) const;

        /** This method returns nearest symmetric matrix */
        Matrix3D symmetrize(void) const;
        /** This method returns nearest skew-symmetric matrix */
        Matrix3D skewSymmetrize(void) const;
};

/** This class represents a 4x4 matrix, used to represnt projective transformations. */
class Matrix4D{
        double subDet(int col1,int row1,int col2,int row2) const;
        double subDet(int col,int row) const;
public:
        /** The actual matrix entries */
        double m[4][4];

        /** This constructor generates an identity matrix */
        Matrix4D(void);
        /** This constructor initializes the upper 3x3 entries of the matrix */
        Matrix4D(const Matrix3D& m);
        /** This constructor initializes the upper 3x3 entries of the matrix with the matrix and sets the last
          * colume to the translation*/
        Matrix4D(const Matrix3D& m,const Point3D& p);

        /** This method returns the entry of the matrix in the col-th column and the row-th row.*/
        double& operator() (int col,int row);
        /** This method returns the entry of the matrix in the col-th column and the row-th row.*/
        double& index(int col,int row);

        /** This method returns the determinant of the matrix.*/
        double det(void) const;

        /** This method returns the negative of a matrix */
        Matrix4D operator- (void) const;

        /** This method multiplies two matrices and returns the product.*/
        Matrix4D  mult(const Matrix4D& m) const;
        /** This method multiplies two matrices and returns the product.*/
        Matrix4D  operator* (const Matrix4D& m) const;
        /** This method multiplies the current matrix (on the right) by the input matrix..*/
        Matrix4D& operator*=(const Matrix4D& m);

        // Adds two matrices
        /** This method adds two matrices and returns the sum. */
        Matrix4D  add(const Matrix4D& m) const;
        /** This method adds two matrices and returns the sum. */
        Matrix4D  operator+ (const Matrix4D& m) const;
        /** This method adds the input matrix to the current matrix. */
        Matrix4D& operator+=(const Matrix4D& m);

        // Subtracts two matrics
        /** This method subtracts two matrices and returns the difference. */
        Matrix4D  subtract(const Matrix4D& m) const;
        /** This method subtracts two matrices and returns the difference. */
        Matrix4D  operator- (const Matrix4D& m) const;
        /** This method subtracts the input matrix from the current matrix. */
        Matrix4D& operator-=(const Matrix4D& m);

        /** This method scales the entries of a matrix and returns a new matrix. */
        Matrix4D  mult(double f) const;
        /** This method scales the entries of a matrix and returns a new matrix. */
        Matrix4D  operator* (double f) const;
        /** This method scales the entries of the current matrix. */
        Matrix4D& operator*=(double f);
        /** This method divides the entries of a matrix and returns a new matrix. */
        Matrix4D  div(double f) const;
        /** This method divides the entries of a matrix and returns a new matrix. */
        Matrix4D  operator/ (double f) const;
        /** This method divides the entries of the current matrix. */
        Matrix4D& operator/=(double f);

        /** This method returns the transpose of a matrix. (Note that it does not change the entries of the current matrix.)*/
        Matrix4D transpose(void) const;

        /** This method returns the inverse of a matrix. (Note that it does not change the entries of the current matrix.)*/
        Matrix4D invert(void) const;

        /** This static method tries to invert the input matrix and write it out into the output. A value of 0 is returned if the matrix has 0 determinant.*/
        static int Invert(const Matrix4D& in,Matrix4D& out);

        /** This method applies the full projective transformation to a 3D point. */
        Point3D operator*(const Point3D& p) const;
        /** This method applies the full projective transformation to a 3D point. */
        Point3D multPosition(const Point3D& position) const;

        /** This method applies the linear part of the transformation to a 3D point. */
        Point3D multDirection(const Point3D& direction) const;

        /** This method applies the linear part of the transformatoin to a normal, (i.e. multiplying by the inverse transpose).*/
        Point3D multNormal(const Point3D& normal) const;


        /** This method applies the projective transformation to a ray.*/
        Ray3D mult(const Ray3D& ray) const;
        /** This method applies the projective transformation to a ray.*/
        Ray3D operator* (const Ray3D& ray) const;

        /** This static method returns the identity matrix. */
        static Matrix4D IdentityMatrix(void);

        /** This method returns the Euler Angles of a rotation matrix */
        Point3D toEuler(void) const;

        /** This method returns the sum of the squares of the matrix entries */
        double squareNorm(void) const;
        /** This method returns sum of the squares of the entries of the difference matrix. */
        static double SquareL2Difference(const Matrix4D& m1,const Matrix4D& m2);
};


/*
 * This class represents a bounding box object that surrounds a shape.
 * The box is assumed to be lined up with the coordinate axis and is
 * defined by (any) two antipodal points on the box. The constructors
 * make sure that the the (x,y,z) coordinates of p[0] are all less than
 * or equal to the (x,y,z) coordinates of p[1]
 */
/** This class represents a bounding box. */
class BoundingBox3D {
public:
        /** The end-points of the bounding box (all of the coefficients of p[0] are assumed to be less than or equal to the coefficients of p[1]).\n */
        Point3D p[2];

        BoundingBox3D(void);
        /** This constructor creates a bounding box with the specified antipodal vertices */
        BoundingBox3D(const Point3D& p1,const Point3D& p2);

        /** This constructor generates the minimal bounding box that contains all of the points in the input array.*/
        BoundingBox3D(const Point3D* pList,const int pSize);

        /** This method returns the bounding box containing the union of the two bounding boxes.\n
          * If one of the boundinb boxes has two end points that are equal, it is assumed to be empty and
          * the union just returns the other bounding box. */
        BoundingBox3D  operator+ (const BoundingBox3D& b) const;
        /** This method returns the bounding box containing the union of the two bounding boxes.\n
          * If one of the boundinb boxes has two end points that are equal, it is assumed to be empty and
          * the union just returns the other bounding box. */
        BoundingBox3D& operator+=(const BoundingBox3D& b);

        /** This method returns the bounding box generated by first transforming the initial bounding box according to the specified transformation and then
          * finding the minimal axis-aligned bounding box containing the transformed box. */
        BoundingBox3D transform(const Matrix4D& m) const;

        /** This method returns the distance along the ray to the box if the ray intersects, otherwise it returns -1.0. (The distance is 0.0 if the
         * starting position of the ray is in the box */
        double intersect(const Ray3D& ray) const;

};

/** This class represents a quaternion */
class Quaternion{
public:
        /** The real component of the quaternion */
        double real;
        /** The imaginary components of the quaternion */
        Point3D imag;

        /** This constructor generates the identity quaternion. */
        Quaternion(void);
        /** This constructor generates a quaternion with real value r and imaginary components i.*/
        Quaternion(double r,const Point3D& i);
        /** This constructor generates a quaternion corresponding to the 3x3 rotation matrix.*/
        Quaternion(const Matrix3D& rot);
        /** Because the quaternion of a rotation is unique up to sign, the following method sets the quaternion so that it is closest to the input ones */
        Quaternion(const Matrix3D& rot,const Quaternion& quat);
        /** Because the quaternion of a rotation is unique up to sign, the following method sets the quaternion so that it is closest to the input ones */
        Quaternion(const Point3D& eulerAngle,const Quaternion& quat);

        /** This method returns the dot product of two quaternions.*/
        double dot(const Quaternion& q) const;

        /** This method returns the length of a quaternion. */
        double length(void) const;
        /** This method returns the square of the length of a quaternion.*/
        double squareNorm(void) const;

        /** This method returns a unit vector that points in the same direction as the quaternion. */
        Quaternion unit(void) const;

        /** This method return the negative of the quaternion. */
        Quaternion operator- (void) const;

        /** This method returns the complex conjugate of a quaternion */
        Quaternion conjugate(void) const;
        /** This method returns the reciprocal of a quaternion. */
        Quaternion invert(void) const;

        /** This method scales a quaternion by a constant factor and returns a new quaternion. */
        Quaternion  operator* (double scale) const;
        /** This method scales the current quaternion by a constant factor. */
        Quaternion& operator*=(double scale);

        /** This method divides the coefficients of a quaternion by a constant factor and returns a new quaternion. */
        Quaternion  operator/ (double scale) const;
        /** This method divides the coefficients of the current quaternion by a constant factor. */
        Quaternion& operator/=(double scale);

        /** This method adds two quaternion and returns their sum. */
        Quaternion  operator+ (const Quaternion& q) const;
        /** This method adds a point to the current quaternion. */
        Quaternion& operator+=(const Quaternion& q);

        /** This method subtracts two quaternion and returns their difference. */
        Quaternion  operator- (const Quaternion& q) const;
        /** This method subtracts a quaternion from the current quaternion. */
        Quaternion& operator-=(const Quaternion& q);

        /** This method returns the product of two quaternions. */
        Quaternion  operator* (const Quaternion& q) const;
        /** This method multiplies the current quaternion by another quaternion.*/
        Quaternion& operator*=(const Quaternion& q);

        /** This method returns the quotient of two quaternions.*/
        Quaternion  operator/ (const Quaternion& q) const;
        /** This method divides the current quaternion by another quaternion.*/
        Quaternion& operator/=(const Quaternion& q);
};




/** This class represents a transformation by the Euler angles and the translation */
class EulerAnglesAndTranslation{
public:
        /** The Euler angles of the transformation */
        Point3D eulerAngles;
        /** The translation vector */
        Point3D translate;

        /** This constructor sets the Euler angles and translation vector from the transformation matrix */
        EulerAnglesAndTranslation(const Matrix4D& m);
        /** Because the Euler angles are not unique, the following method sets the Euler angles so that they are closest to the input ones */
        EulerAnglesAndTranslation(const Matrix4D& m,const EulerAnglesAndTranslation& euler);
        EulerAnglesAndTranslation(void);

        /** This method returns the negative of the transformation parameters */
        EulerAnglesAndTranslation operator - (void) const;

        /** This method scales the transformation parameters. */
        EulerAnglesAndTranslation  operator* (double scale) const;
        /** This method scales the current transformation parameters by a constant factor. */
        EulerAnglesAndTranslation& operator*=(double scale);

        /** This method divides the coefficients of a the transformation parameters by a constant factor. */
        EulerAnglesAndTranslation  operator/ (double scale) const;
        /** This method divides the coefficients of the current transformation parameters by a constant factor. */
        EulerAnglesAndTranslation& operator/=(double scale);

        /** This method adds two sets of transformation parameters and returns their sum. */
        EulerAnglesAndTranslation  operator+ (const EulerAnglesAndTranslation& q) const;
        /** This method adds a set of transformation parameters to the current transformation parameters. */
        EulerAnglesAndTranslation& operator+=(const EulerAnglesAndTranslation& q);

        /** This method subtracts two sets of transformation parameters and returns their difference. */
        EulerAnglesAndTranslation  operator- (const EulerAnglesAndTranslation& q) const;
        /** This method subtracts a set of transformation parameters from the current transformation parameters. */
        EulerAnglesAndTranslation& operator-=(const EulerAnglesAndTranslation& q);
};
/** This class represents a transformation by a 3x3 matrix and the translation */
class RotationAndTranslation{
public:
        /** The rotation */
        Matrix3D rotation;
        /** The translation vector */
        Point3D translate;

        /** This constructor sets the rotation matrix and translation vector from the transformation matrix */
        RotationAndTranslation(const Matrix4D& m);
        RotationAndTranslation(void);

        /** This method returns the negative of the transformation parameters */
        RotationAndTranslation operator - (void) const;

        /** This method scales the transformation parameters. */
        RotationAndTranslation  operator* (double scale) const;
        /** This method scales the current transformation parameters by a constant factor. */
        RotationAndTranslation& operator*=(double scale);

        /** This method divides the coefficients of a the transformation parameters by a constant factor. */
        RotationAndTranslation  operator/ (double scale) const;
        /** This method divides the coefficients of the current transformation parameters by a constant factor. */
        RotationAndTranslation& operator/=(double scale);

        /** This method adds two sets of transformation parameters and returns their sum. */
        RotationAndTranslation  operator+ (const RotationAndTranslation& q) const;
        /** This method adds a set of transformation parameters to the current transformation parameters. */
        RotationAndTranslation& operator+=(const RotationAndTranslation& q);

        /** This method subtracts two sets of transformation parameters and returns their difference. */
        RotationAndTranslation  operator- (const RotationAndTranslation& q) const;
        /** This method subtracts a set of transformation parameters from the current transformation parameters. */
        RotationAndTranslation& operator-=(const RotationAndTranslation& q);
};
/** This class represents a transformation by the skew-symmetric log of the rotation and the translation */
class LogRotationAndTranslation{
public:
        /** The rotation */
        Matrix3D skewSymmetric;
        /** The translation vector */
        Point3D translate;

        /** This constructor sets the log of the rotation matrix and translation vector from the transformation matrix */
        LogRotationAndTranslation(const Matrix4D& m);
        LogRotationAndTranslation(void);
        /** Because the Logarithm of a rotation is not unique, the following method sets the Logarithm so that it is closest to the input ones */
        LogRotationAndTranslation(const Matrix4D& m,const LogRotationAndTranslation& lg);

        /** This method returns the negative of the transformation parameters */
        LogRotationAndTranslation operator - (void) const;

        /** This method scales the transformation parameters. */
        LogRotationAndTranslation  operator* (double scale) const;
        /** This method scales the current transformation parameters by a constant factor. */
        LogRotationAndTranslation& operator*=(double scale);

        /** This method divides the coefficients of a the transformation parameters by a constant factor. */
        LogRotationAndTranslation  operator/ (double scale) const;
        /** This method divides the coefficients of the current transformation parameters by a constant factor. */
        LogRotationAndTranslation& operator/=(double scale);

        /** This method adds two sets of transformation parameters and returns their sum. */
        LogRotationAndTranslation  operator+ (const LogRotationAndTranslation& q) const;
        /** This method adds a set of transformation parameters to the current transformation parameters. */
        LogRotationAndTranslation& operator+=(const LogRotationAndTranslation& q);

        /** This method subtracts two sets of transformation parameters and returns their difference. */
        LogRotationAndTranslation  operator- (const LogRotationAndTranslation& q) const;
        /** This method subtracts a set of transformation parameters from the current transformation parameters. */
        LogRotationAndTranslation& operator-=(const LogRotationAndTranslation& q);
};
/** This class represents a transformation by a quaternion and a translation */
class QuaternionAndTranslation{
public:
        /** The rotation */
        Quaternion quaternion;
        /** The translation vector */
        Point3D translate;

        /** This constructor sets the quaternion and translation vector from the transformation matrix */
        QuaternionAndTranslation(const Matrix4D& m);
        /** Because the quaternion of a rotation is unique up to sign, the following method sets the quaternion so that it is closest to the input ones */
        QuaternionAndTranslation(const Matrix4D& m,const QuaternionAndTranslation& quat);
        QuaternionAndTranslation(void);

        /** This method returns the negative of the transformation parameters */
        QuaternionAndTranslation operator - (void) const;

        /** This method scales the transformation parameters. */
        QuaternionAndTranslation  operator* (double scale) const;
        /** This method scales the current transformation parameters by a constant factor. */
        QuaternionAndTranslation& operator*=(double scale);

        /** This method divides the coefficients of a the transformation parameters by a constant factor. */
        QuaternionAndTranslation  operator/ (double scale) const;
        /** This method divides the coefficients of the current transformation parameters by a constant factor. */
        QuaternionAndTranslation& operator/=(double scale);

        /** This method adds two sets of transformation parameters and returns their sum. */
        QuaternionAndTranslation  operator+ (const QuaternionAndTranslation& q) const;
        /** This method adds a set of transformation parameters to the current transformation parameters. */
        QuaternionAndTranslation& operator+=(const QuaternionAndTranslation& q);

        /** This method subtracts two sets of transformation parameters and returns their difference. */
        QuaternionAndTranslation  operator- (const QuaternionAndTranslation& q) const;
        /** This method subtracts a set of transformation parameters from the current transformation parameters. */
        QuaternionAndTranslation& operator-=(const QuaternionAndTranslation& q);
};


/////////////////
// mTriangle3D //
/////////////////
class mTriangle3D{
public:
    Point3D vertex[3];
    mTriangle3D(){};
    mTriangle3D( Point3D v1 , Point3D v2 , Point3D v3){ vertex[0]=v1 , vertex[1]=v2 , vertex[2]=v3; };
};
#endif // GEOMETRY_INCLUDED

