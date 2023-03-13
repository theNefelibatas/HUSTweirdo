#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

// 3 维向量，元素类型为 double
typedef struct vec3{
    double x, y, z;
}vec3;

// RGB color and Point
typedef vec3 color;
typedef vec3 point3;

// ray
typedef struct ray{
    point3 orgin;
    vec3 direction;
}ray;

// hit record
typedef struct hit_record{
    double t;
    point3 p; // 交点
    vec3 normal; // 交点法线
}hit_record;

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
    // debug
    double x = u->x * v->x;
    double y = u->y * v->y;
    double z = u->z * v->z;
    double dot_product = u->x * v->x + u->y * v->y + u->z * v->z;
    return dot_product;
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
    double length = sqrt(vec3_dot_product(v, v));
    return length;
}

// 单位向量
vec3 vec3_unit(vec3 *v){
    double vlen = vec3_length(v);
    vec3 u = vec3_init(v->x/vlen,v->y/vlen, v->z/vlen);
    return u;
}

// 产生[0，1)的随机数
inline double random_double(){
    srand(time(NULL));
    return rand()/(RAND_MAX + 1.0);
}

// 输出 RGB 序列
inline double clamp(double x, double min, double max){
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
void write_color(FILE *fp, const color pixel_color, const int sample_per_pixel){
    double scale = 1.0 / sample_per_pixel;
    double x = clamp(pixel_color.x * scale, 0.0, 0.999);
    double y = clamp(pixel_color.y * scale, 0.0, 0.999);
    double z = clamp(pixel_color.z * scale, 0.0, 0.999);
    int r = (int)(x * 255.999);
    int g = (int)(y * 255.999);
    int b = (int)(z * 255.999);
    fprintf(fp,"%d %d %d\n", r, g, b);
}


// P(t) = point3 + t * directon
// 线的初始化
ray ray_init(const point3 orgin, const vec3 direction){
    ray r;
    r.orgin.x = orgin.x; r.orgin.y = orgin.y; r.orgin.z = orgin.z;
    r.direction.x = direction.x;
    r.direction.y = direction.y;
    r.direction.z = direction.z;
    return r;
}

// 线的交点
point3 ray_inter(ray *r, double t){
    point3 po;
    po.x = r->orgin.x + t * r->direction.x;
    po.y = r->orgin.y + t * r->direction.y;
    po.z = r->orgin.z + t * r->direction.z;
    return po;
}

// 球的交点
double hit_sphere(const point3 center, double radius, const ray *r){
    vec3 oc = point3_vec(center, r->orgin);
    double a = vec3_dot_product(&r->direction, &r->direction);
    double half_b = vec3_dot_product(&oc, &r->direction);
    double c = vec3_dot_product(&oc, &oc) -radius * radius;
    double delta = half_b * half_b - a*c;
    double rate = 0;
    if(delta<0) rate = -1.0;
    else rate = (-half_b - sqrt(delta))/a;
    return rate;
}

// 光线
point3 random_in_unit_sphere(){
    point3 p;
    vec3 vec_1 = vec3_init(1,1,1);
    do{
        point3 rand_p = point3_init(random_double(), random_double(), random_double());
        p = vec3_multiply(&rand_p, 2.0);
        p = vec3_minus(&p, &vec_1);
    }while (vec3_length(&p) >= 1.0);
    return p;
}
color ray_color(ray *r){
    // color co = vec3_init(1,0,0);
    // const vec3 center = vec3_init(0, 0, -1);
    // const vec3 center_ground = vec3_init(0, -100.25, -1);
    // double inter = hit_sphere(center, 0.25, r);
    static color co;
    static vec3 center, center_ground;
    center = vec3_init(0, 0, -1);
    center_ground = vec3_init(0, -100.25, -1);
    static vec3 addi;
    addi = vec3_init(1.0, 1.0, 1.0);
    static double inter;
    inter = hit_sphere(center, 0.25, r);
    if (inter > 0.0){
        // point3 n = ray_inter(r, inter);
        // const vec3 addi = vec3_init(1.0, 1.0, 1.0);
        static point3 n;
        n = ray_inter(r, inter);
        // vec3 nor = vec3_minus(&n, &center);
        static vec3 nor;
        nor = vec3_minus(&n, &center);
        nor = vec3_unit(&nor); // 交点法线
        // co = 0.5*(n+1)
        // co = vec3_add(&n, &addi);
        // co = vec3_multiply(&co, 0.5);
        static ray ray_tem;
        // point3 rand_p = random_in_unit_sphere();
        static point3 rand_p;
        rand_p = random_in_unit_sphere();
        ray_tem.orgin = n;
        ray_tem.direction = vec3_add(&nor, &rand_p);
        co = ray_color(&ray_tem);
        co = vec3_multiply(&co, 0.5);
        return co;
    }

    // ground
    static double inter_ground;
    inter_ground = hit_sphere(center_ground, 100, r);
    if (inter_ground > 0.0){
        /*
        static point3 n_ground;
        n_ground = ray_inter(r, inter_ground);
        static vec3 nor_ground;
        nor_ground = vec3_minus(&n_ground, &center);
        nor_ground = vec3_unit(&nor_ground); // 交点法线
        static ray ray_tem;
        // point3 rand_p = random_in_unit_sphere();
        static point3 rand_p;
        rand_p = random_in_unit_sphere();
        ray_tem.orgin = n_ground;
        ray_tem.direction = vec3_add(&nor_ground, &rand_p);
        co = ray_color(&ray_tem);
        co = vec3_multiply(&co, 0.5);*/
        co = vec3_init(0.1, 0.8, 0.1);
        return co;
    }

//    vec3 tem = r->direction;
//    vec3 unit_dir = vec3_unit(&tem);
    double t = 0.5 * (r->direction.y/0.5625 + 1.0); // 0.5625 = view_height / 2
    // co = (1.0-t)*color(1.0,1.0,1.0) + t*color(0.5,0.7,1.0)
    // co = color(1.0-0.5t, 1.0-0.3t, 1.0)
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
    FILE *fp = fopen("Image-8-1.ppm","wb");
    FILE *fptext = fopen("Image-8-1.txt","w"); // debug

    // Image Size
    const int width = 1600/4;
    const int height = 900/4;
    const int samples_per_pixel = 100;

    // camera
    double view_width = 16.0 / 8;
    double view_height = 9.0 / 8;
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
        fprintf(fptext,"P3\n%d %d\n255\n", width, height); // debug
        for(int j = height - 1; j >= 0; j--){
            for(int i = 0; i < width; i++){
                color pixel_color = color_init(0,0,0);
                for (int s = 0; s <samples_per_pixel; s++){
                    double u = 1.0 * (i + random_double()) / (width-1);
                    double v = 1.0 * (j + random_double()) / (height-1);
                    // direction rp = llc + u*hori + v*verti -origin
                    point3 temp = llc;
                    point3 htem = vec3_multiply(&hori, 2*u);
                    point3 vtem = vec3_multiply(&verti, 2*v);
                    temp = vec3_add(&temp, &htem);
                    temp = vec3_add(&temp, &vtem);
                    // rp ray和projection的交点，也是方向向量（camera在原点）
                    point3 rp = vec3_minus(&temp, &origin);
                    ray r = ray_init(origin, rp);
                    color pixel_color_tem = ray_color(&r);
                    pixel_color = vec3_add(&pixel_color, &pixel_color_tem);
                }
                // pixel_color = vec3_divide(&pixel_color, (double)samples_per_pixel);
                // int ir = (int)(255.999 * pixel_color.x);
                // int ig = (int)(255.999 * pixel_color.y);
                // int ib = (int)(255.999 * pixel_color.z);
                // fprintf(fp,"%d %d %d\n", ir, ig, ib);
                // fprintf(fptext,"%d %d %d\n", ir, ig, ib); // debug
                write_color(fp, pixel_color, samples_per_pixel);
                write_color(fptext, pixel_color, samples_per_pixel); // debug
            }
        }
    }
    return 0;
}