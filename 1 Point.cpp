struct Point {
  double x, y, z;
  Point(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
  void read(){ scanf("%llf%llf%llf", &x, &y, &z); }
};

typedef Point Vector;
typedef Point Color;


//3D basics

const double eps = 1e-8;
const double INF = 1e20;

int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

double ACOS(double x){
  if (!dcmp(1-x)) x = 1;
  if (!dcmp(1+x)) x = -1;
  return acos(x); //loss precision significantly (14->7, 8->5 and so on). Avoid if possible!
}

double SQRT(double x){
  if (dcmp(x) < 0) return 0;
  return sqrt(x);
}

Vector operator + (const Vector& A, const Vector& B){ return Vector(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector operator - (const Point& A, const Point& B){ return Vector(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector operator * (const Vector& A, const double& p){ return Vector(A.x*p, A.y*p, A.z*p); }
Vector operator / (const Vector& A, const double& p){ return Vector(A.x/p, A.y/p, A.z/p); }
bool operator == (const Vector& A, const Vector& B){ return dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0 && dcmp(A.z-B.z) == 0; }
double Dot(const Vector& A, const Vector& B){ return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector& A){ return sqrt(Dot(A, A)); }
//double Angle(const Vector& A, const Vector& B){ return ACOS(Dot(A, B) / Length(A) / Length(B));}
Vector Cross(const Vector& A, const Vector& B){ return Vector(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
//double Area2(const Point& A, const Point& B, const Point& C){ return Length(Cross(B-A, C-A)); } // 2*area
//double Volume6(const Point& A, const Point& B, const Point& C, const Point& D){ return Dot(D-A, Cross(B-A, C-A)); } //6*volumn
Vector PiecewiseMulti (const Color& A, const Color& B) { return Color(A.x*B.x, A.y*B.y, A.z*B.z); }

//The length of A is not expected to be 0 (though protected)
Vector Unitlize(Vector& A){
  double len = Length(A);
  len = dcmp(len) ? len : 1;
  return A/len; 
}

//input: incident direction and normal direction
//output: reflected direction
Vector Reflect(const Vector& I, const Vector& N){
  return I - (N*2*Dot(N, I));
}

// distance from point p to plane p0-n. n must be unit vector
double DistanceToPlane(const Point& p, const Point& p0, const Vector& n) {
  return fabs(Dot(p-p0, n));
}

//Line p1-v intersection with plan p0-n. return t of the intersection on the line
double LinePlaneIntersection(const Point& p1, const Vector& v, const Point& p0, const Vector& n){
  if (dcmp(Dot(n, v)) == 0)
    return -1;  //plane and line are parralel
  double t = (Dot(n, p0-p1) / Dot(n, v));
  return t;
}