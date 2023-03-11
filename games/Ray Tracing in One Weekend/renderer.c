#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>

// 3 维向量，元素类型为 double
typedef struct vec3{
    double x;
    double y;
    double z;
}vec3;

// RGB color and Point
typedef vec3 color;
typedef vec3 point3;

// ray
typedef struct ray{
    point3 orgin;
    vec3 direction;
    int t;
}ray;

// 坐标初始化
point3 point3_init(const double x, const double y, const double z){
    point3 p;
    p.x = x; p.y = y; p.z = z;
    return p;
}

// A,B两点求向量
vec3 point3_vec(const point3 a, const point3 b){
    vec3 vec;
    vec.x = b.x - a.x;
    vec.y = b.y - a.y;
    vec.z = b.z - a.z;
    return vec;
}

// color 初始化
color color_init(const double x, const double y, const double z){
    color co;
    co.x = x; co.y = y; co.z = z;
    return co;
}

// vec3 初始化
vec3 vec3_init(const double x, const double y, const double z){
    vec3 vec;
    vec.x = x; vec.y = y; vec.z = z;
    return vec;
}

// 反向向量
vec3 vec3_negate(const vec3 *v) {
    vec3 u;
    u.x = -v->x;
    u.y = -v->y;
    u.z = -v->z;
    return u;
}

// 向量加法
vec3 vec3_add(const vec3 *v1, const vec3 *v2) {
    vec3 v;
    v.x = v1->x + v2->x;
    v.y = v1->y + v2->y;
    v.z = v1->z + v2->z;
    return v;
}

// 向量减法
vec3 vec3_minus(const vec3 *v1, const vec3 *v2) {
    vec3 v;
    v.x = v1->x - v2->x;
    v.y = v1->y - v2->y;
    v.z = v1->z - v2->z;
    return v;
}

// 向量数乘---乘法
vec3 vec3_multiply(const vec3 *v, const double t) {
    vec3 u;
    u.x = v->x * t;
    u.y = v->y * t;
    u.z = v->z * t;
    return u;
}

// 向量数乘---除法
vec3 vec3_divide(const vec3 *v, const double t) {
    vec3 u = vec3_multiply(v, 1.0 / t);
    return u;
}

// 向量点乘
double vec3_dot_product(const vec3 *u, const vec3 *v) {
    return u->x * v->x + u->y * v->y + u->z * v->z;
}

// 向量叉乘
vec3 vec3_cross_product(const vec3 *u, const vec3 *v){
    double i = u->y * v->z - u->z * v->y;
    double j = u->z * v->x - u->x * v->z;
    double k = u->x * v->y - u->y * v->x;
    vec3 vec = vec3_init(i, j, k);
    return vec;
}

// 向量长度
double vec3_length(const vec3 *v) {
    return sqrt(vec3_dot_product(v, v));
}

// 单位向量
vec3 vec3_unit(vec3 *v){
    vec3 u = vec3_init(v->x/vec3_length(v),\
    v->y/vec3_length(v), v->z/vec3_length(v) );
    return u;
}

// 输出 RGB 序列
void write_color(FILE *fp, const color pixel_color){
    int x = (int)(pixel_color.x * 255.999);
    int y = (int)(pixel_color.y * 255.999);
    int z = (int)(pixel_color.z * 255.999);
    fprintf(fp,"%d %d %d\n", x, y, z);
}


// P(t) = point3 + t * directon
// 线的初始化
ray ray_init(const point3 orgin, const vec3 direction){
    ray r;
    r.orgin.x = orgin.x; r.orgin.y = orgin.y; r.orgin.y = orgin.y;
    r.direction.x = direction.x;
    r.direction.y = direction.y;
    r.direction.y = direction.y;
    return r;
}

// 线的交点
point3 ray_inter(ray *r, int t){
    point3 po;
    po.x = r->orgin.x + t * r->direction.x;
    po.y = r->orgin.y + t * r->direction.y;
    po.z = r->orgin.z + t * r->direction.z;
    return po;
}

// 球
double hit_sphere(const point3 center, double radius, const ray *r){
    vec3 oc = point3_vec(r->orgin, center);
    double a = vec3_dot_product(&r->direction, &r->direction);
    double half_b = vec3_dot_product(&oc, &r->direction);
    double c = vec3_dot_product(&oc, &oc) -radius * radius;
    double delta = half_b * half_b - 4*a*c;
    if(delta < 0)
        return -1.0;
    else
        return (-half_b - sqrt(delta)) / a;
}

// 光线
color ray_color(ray *r){
    double t = hit_sphere(point3_init(0,0,-1), 0.5, r);
    color co;
    if (t > 0.0){
        vec3 n = ray_inter(r, t);
        const vec3 center = vec3_init(0, 0, -1);
        const vec3 addi = vec3_init(1.0, 1.0, 1.0);
        n = vec3_minus(&n, &center);
        n = vec3_unit(&n);
        co = vec3_add(&n, &addi);
        co = vec3_multiply(&co, 0.5);
        return co;
    }
    vec3 tem = r->direction;
    vec3 unit_dir = vec3_unit(&tem);
    t = 0.5 * (unit_dir.y + 1.0);
    color co1 = color_init(1.0, 1.0, 1.0);
    co1 = vec3_multiply(&co1, 1.0 - t);
    color co2 = color_init(0.5, 0.7, 1.0);
    co2 = vec3_multiply(&co2, t);
    co = vec3_add(&co1, &co2);
    return co;
    }

// 主函数，输出
int main(){
    // 写一个ppm文件
    FILE *fp = fopen("Image.ppm","wb");

    // Image Size
    const int width = 1600/4;
    const int height = 900/4;

    // camera
    double view_height = 16.0 / 8;
    double view_width = 9.0 / 8;
    double focal_length = 1.0; // 焦距
    point3 origin = point3_init(0,0,0);
    vec3 hori = vec3_init(view_width/2, 0, 0);
    vec3 verti = vec3_init(0, view_height/2, 0);
    // llc = lower_left_corner
    // llc = origin - hori - verti + center
    const vec3 center = vec3_init(0, 0, -focal_length); 
    point3 tem = origin;
    tem = vec3_minus(&tem, &hori);
    tem = vec3_minus(&tem, &verti);
    point3 llc = vec3_add(&tem, &center);

    // render
    if (fp != NULL){
        fprintf(fp,"P3\n%d %d\n255\n", width, height);
        for(int j = height -1 ; j >= 0; j--){
            for(int i = 0; i < width; i++){
                double u = (double)i / (width - 1);
                double v = (double)j / (height - 1);
                // direction rp = llc + u*hori + v*verti -origin
                point3 temp = llc;
                point3 htem = vec3_multiply(&hori, 2*u);
                point3 vtem = vec3_multiply(&verti, 2*v);
                tem = vec3_add(&tem, &htem);
                tem = vec3_add(&tem, &vtem);
                // rp ray和projection的交点，也是方向向量（camer在原点）
                point3 rp = vec3_minus(&tem, &origin);
                ray r = ray_init(origin, rp);
                color pixel_color = ray_color(&r);
                write_color(fp, pixel_color);
            }
        }
    }
    return 0;
}
