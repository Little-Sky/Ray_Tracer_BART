//v = {0,0,0} indicates a light source

struct Ray {
  Vector v, inv; //if v.c != 0, then /v.c == *inv.c for any c = {x,y,z}
  Point p;
  Color c;
  //access inv before check v is not 0
  Line (Vector v, Point p, Color c) : v(Unitlize(v)), p(p), c(c) {
  	inv = Vector(1.0/(dcmp(v.x) ? v.x : 1.0), 1.0/(dcmp(v.y) ? v.y : 1.0), 1.0/(dcmp(v.z) ? v.z : 1.0));
  }
  Point getpoint (double t){ return p + v*t; } 
};

queue<Ray> Qray;	//used for BFS search.