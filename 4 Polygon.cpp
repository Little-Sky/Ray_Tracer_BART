struct Polygon {
  vector<Point> points;
  Vector normal;
  double min_x, min_y, min_z;
  double max_x, max_y, max_z;  //the bounding box, order:L x, y, z
  Polygon(vector<Point> points): points(points) {
    normal = Unitlize(Cross(points[1] - points[0], points[2] - points[1]));
    min_x = max_x = points[0].x;
    min_y = max_y = points[0].y;
    min_z = max_z = points[0].z;
    for (int i=1; i<points.size(); i++){
      min_x = min(min_x, points[i].x);
      min_y = min(min_y, points[i].y);
      min_z = min(min_z, points[i].z);
      
      max_x = max(max_x, points[i].x);
      max_y = max(max_y, points[i].y);
      max_z = max(max_z, points[i].z);
    }
  }
}

//Use winding number to check whether a ray intersects a polygon.
//To simplify the code, return false when point is on the edge
bool IsRayIntersectsPolygon (const Ray& r, const Polygon& poly){
  double t = LinePlaneIntersection(r.p, r.v, poly.points[0], poly.normal);
  if (dcmp(t) <= 0) //too close is regard as on the plane 
    return false;
  Point p = r.getpoint(t);  //projection on the plane
  if (dcmp(p.x-poly.max_x) >= 0 || dcmp(p.x-poly.min_x) <= 0) return false;
  if (dcmp(p.y-poly.max_y) >= 0 || dcmp(p.y-poly.min_y) <= 0) return false;
  if (dcmp(p.z-poly.max_z) >= 0 || dcmp(p.z-poly.min_z) <= 0) return false;

  //check which plane will the polygon be projected;
  int which_axis; //when doing projection, ignor which axis?
  Vector& nl = poly.normal;
  if (fabs(nl.x) > fabs(nl.y) && fabs(nl.x) > fabs(nl.z)) which_axis = 0;       //x-axis ignored
  else if (fabs(nl.y) > fabs(nl.x) && fabs(nl.y) > fabs(nl.z)) which_axis = 1;  //y-axis ignored
  else which_axis = 2;                                                          //z-axis ignored

  int wn = 0; //winding number
  int siz = poly.points.size();
  for (int i=0; i<siz; i++){
    //Two points : (x1, y1) and (x2, y2)
    double x1, x2, y1, y2;
    if (which_axis == 0){ 
      x1 = poly.points[i].y;
      y1 = poly.points[i].z;
      x2 = poly.points[(i+1)%n].y;
      y2 = poly.points[(i+1)%n].z;
    }else if (which_axis == 1){
      x1 = poly.points[i].x;
      y1 = poly.points[i].z;
      x2 = poly.points[(i+1)%n].x;
      y2 = poly.points[(i+1)%n].z;
    }else{
      x1 = poly.points[i].x;
      y1 = poly.points[i].y;
      x2 = poly.points[(i+1)%n].x;
      y2 = poly.points[(i+1)%n].y;
    }
    int k = dcmp ((x2-x1)*(p-y1) - (y2-y1)*(p-y1));
    int d1 = dcmp (y1 - p.y);
    int d2 = dcmp (y2 - p.y);
    //int k = dcmp (Cross (poly.points[(i+1)%n]-poly.points[i], p-poly.points[i]));
    //int d1 = dcmp (poly[i].y - p.y);
    //int d2 = dcmp (poly[(i+1)%n].y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;    //an edge across 'x'-axis from below to above
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;    //an edge across 'x'-axis from above to below
  }
  if (wn != 0) return true; //inside
  return false;             //outside
}
