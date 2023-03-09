#include<stdio.h>
#include<math.h>
#include<string.h>

// 3 维向量，元素类型为 double
typedef struct vec3{
    double x;
    double y;
    double z;
}vec3;

// vec3 初始化
void vec3_init(vec3 *v, double x, double y, double z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

// 反向向量
void vec3_negate(vec3 *v) {
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}

// 向量加法
void vec3_add(vec3 *v1, vec3 *v2, vec3 *result) {
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

// 向量数乘---乘法
void vec3_multiply(vec3 *v, double t) {
    v->x *= t;
    v->y *= t;
    v->z *= t;
}

// 向量数乘---除法
void vec3_divide(vec3 *v, double t) {
    vec3_multiply(v, 1.0 / t);
}

// 返回向量长度的平方
double vec3_length_squared(vec3 *v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

// 返回向量长度
double vec3_length(vec3 *v) {
    return sqrt(vec3_length_squared(v));
}

// RGB color 和 点，向量
typedef vec3 color;
typedef vec3 point3;
typedef vec3 dir;

// 输出 RGB 序列
void write_color(FILE *fp, color pixel_color){
    fprintf(fp,"%d %d %d\n",\
    pixel_color.x, pixel_color.y, pixel_color.z);
}

// 方向向量
// origin是原点，direction是方向向量，t是标量
 point3 ray(point3 orgin, dir direction, int t){
    point3 po;
    po.x = orgin.x + t * direction.x;
    po.y = orgin.y + t * direction.y;
    po.z = orgin.z + t * direction.z;
    return po;
 }

 

// 主函数，输出
int main(){
    FILE *fp = fopen("Image.ppm","wb");
    // Image Size
    const int width = 256;
    const int height = 256;
    // render
    fprintf(fp,"P3\n%d %d\n255\n",width,height);


    return 0;
}