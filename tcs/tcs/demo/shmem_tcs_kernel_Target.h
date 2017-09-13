
#ifndef __tcs_kernel_Target_H__
#define __tcs_kernel_Target_H__

class shm_tcs_kernel_Target {
   public:
  int syncI;
  char site[32];
  float t0;
  float az;
  float el;
  float azdot;
  float eldot;
  float Wavel;
  float XOffset;
  float YOffset;
  char OffSys[32];
  float focalplaneX;
  float focalplaneY;
  float Temp;
  float Press;
  float Humid;
  float TLR;
  float Tai;
  int syncO;
     static void * m_shared_mem;
     virtual void Handle();
     void * operator new (unsigned int);
};



void GetObject_tcs_kernel_Target(shm_tcs_kernel_Target ** pshm_tcs_kernel_Target);

#endif //__tcs_kernel_Target_H__

