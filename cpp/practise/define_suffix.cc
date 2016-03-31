#define DEF_COPY_MASK(suffix, type) \  
static void copyMask##suffix(const uchar* src, size_t sstep, const uchar* mask, size_t mstep, \  
                             uchar* dst, size_t dstep, Size size, void*) \  
{ \  
    copyMask_<type>(src, sstep, mask, mstep, dst, dstep, size); \  
}  
  
  
DEF_COPY_MASK(8u, uchar);  
DEF_COPY_MASK(16u, ushort);  
DEF_COPY_MASK(8uC3, Vec3b);  
DEF_COPY_MASK(32s, int);  
DEF_COPY_MASK(16uC3, Vec3s);  
DEF_COPY_MASK(32sC2, Vec2i);  
DEF_COPY_MASK(32sC3, Vec3i);  
DEF_COPY_MASK(32sC4, Vec4i);  
DEF_COPY_MASK(32sC6, Vec6i);  
DEF_COPY_MASK(32sC8, Vec8i); 
