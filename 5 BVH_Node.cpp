const int MAXN = 120000 * 3; //max object number * 3 for a binary tree, used for a static BBox buffer

struct BBox {
  Point mn, mx;
  BBox(Point a, Point b){
    mn = Point (min(a.x, b.x), min(a.y, b.y), min(a.z, b.z));
    mx = Point (max(a.x, b.x), max(a.y, b.y), max(a.z, b.z));
  }
}BBox_buffer[MAXN];


bool IsRayIntersectsBBox (const Ray& r, const BBox& box){
  double mn = -INF, mx = INF, t0, t1;
  if (dcmp(r.v.x)){
    t0 = (box.mn.x - r.p.x) * r.inv.x;
    t1 = (box.mx.x - r.p.x) * r.inv.x;
    mn = max(mn, min (t0, t1));
    mx = min(mx, max (t0, t1));
  }else if (dcmp((box.mn.x - r.p.x) * (box.mx.x - r.p.x)) >= 0){
    return false;
  }

  if (dcmp(r.v.y)){
    t0 = (box.mn.y - r.p.y) * r.inv.y;
    t1 = (box.mx.y - r.p.y) * r.inv.y;
    mn = max(mn, min (t0, t1));
    mx = min(mx, max (t0, t1));
  }else if (dcmp((box.mn.y - r.p.y) * (box.mx.y - r.p.y)) >= 0){
    return false;
  }

  if (dcmp(r.v.z)){
    t0 = (box.mn.z - r.p.z) * r.inv.z;
    t1 = (box.mx.z - r.p.z) * r.inv.z;
    mn = max(mn, min (t0, t1));
    mx = min(mx, max (t0, t1));
  }else if (dcmp((box.mn.z - r.p.z) * (box.mx.z - r.p.z)) >= 0){
    return false;
  }

  if (dcmp(mx - mn) <= 0)
    return false;
  return true;
}


BBox Surround (const BBox& a, const BBox& b){
  Point new_mn = Point (min(a.mn.x, b.mn.x), min(a.mn.y, b.mn.y), min(a.mn.z, b.mn.z));
  Point new_mx = Point (max(a.mx.x, b.mx.x), max(a.mx.y, b.mx.y), max(a.mx.z, b.mx.z)); 
  return BBox(new_mn, new_mx);
}