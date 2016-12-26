static unsigned long x=123456789, y=362436069, z=521288629;

//a random number generated found on stack overflow to improve the program performance
unsigned long long random(void) {          //period 2^96-1
unsigned long long t;
  x ^= x << 16;
  x ^= x >> 5;
  x ^= x << 1;

  t = x, x = y, y = z;
  z = t ^ x ^ y;
  return z;
}

struct Camera{
  Point from;
  Vector at, up;
  double angle, hither, pixelx, pixely;
  Camera(Point from, Vector at, Vector up, double a, double b, double c, double d): from (from), at(at), up(up), 
}

struct Frame{
  
}