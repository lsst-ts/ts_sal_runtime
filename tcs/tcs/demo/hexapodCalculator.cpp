//
// Calculate the camera and m2 hexapod motions  based on azimuth and elevation
//

#define CAMERA_HEXAPOD 1
#define M2_HEXAPOD     2

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "SAL_hexapod.h"

int hexapodCalculator ( int deviceId, double elevation, 
                        hexapod_command_moveC *newPosition )
{
  double E6,F6,G6,H6,I6,J6,E13,F13,G13,H13,I13,J13;
  double E7,F7,G7,H7,I7,J7,E14,F14,G14,H14,I14,J14;
  double C,D,E,F,G,H,I,J;
  double N,O,P,Q,R,S;
  double PI =       3.14159265359;

  if ( deviceId == CAMERA_HEXAPOD ) {

	E7 =    -0.19930118;
	F7 = -1324.68205;
	G7 =    -9.5013145;
	H7 =    -0.0354691;
	I7 =    -0.000008631;
	J7 =    -0.000007396;
	E14 =    1.656270415;
	F14 =  -29.83178649;
	G14 = -910.2272456;
	H14 =    0.0000116088;
	I14 =   -0.0000098319;
	J14 =   -0.0000568789;

// elevation is A = e in degrees

// camera hexapod ------------------------------------------------------------
// camera zenith components
	D  = 90-elevation;
	C  = D*PI/180.;	
	E  = cos(C)*E14;
	F  = cos(C)*F14;
	G  = cos(C)*G14; 
	H  = cos(C)*H14;
	I  = cos(C)*I14; 
	J  = cos(C)*J14; 	
// puts stdout "camera zenith D E F G H I J"

// camera horizon compomnents
	N  = sin(C)*E7;
	O  = sin(C)*F7;
	P  = sin(C)*G7;
	Q  = sin(C)*H7;
	R  = sin(C)*I7;
	S  = sin(C)*J7;
//puts stdout "camera horizon N O P Q R S"

// camera combined comps
	newPosition->x  = E + N;
	newPosition->y  = F + O;
	newPosition->z  = G + P;
	newPosition->u  = H + Q;
	newPosition->v  = I + R;
	newPosition->w  = J + S;
	return 0;

   }

   if ( deviceId == M2_HEXAPOD ) {

// m2 hexapod ------------------------------------------------------------
	E6 =     4.7022581;
	F6 = -1173.5712;
	G6 =   -73.8183775;
	H6 =    -0.01315978;
	I6 =     0.00001253;
	J6 =    -0.00009770;
	E13 =    9.48870708;
	F13 =  -44.3076436;
	G13 =-1035.480953;
	H13 =    0.0001940386; 
	I13 =   -0.0000423753;
	J13 =   -0.0002111026;

// m2 elevation components
	D  = 90-elevation;
	C  = D*PI/180.;
	E  = cos(C)*E13; 
	F  = cos(C)*F13; 
	G  = cos(C)*G13; 
	H  = cos(C)*H13; 
	I  = cos(C)*I13;
	J  = cos(C)*J13;
//puts stdout "m2 elevation E F G H I J"

// m2 horizon compomnents
	N  = sin(C)*E6;
	O  = sin(C)*F6;
	P  = sin(C)*G6;
	Q  = sin(C)*H6;
	R  = sin(C)*I6;
	S  = sin(C)*J6;
//puts stdout "m2 horizon N O P Q R S"

// m2 combined comps
	newPosition->x  = E + N;
	newPosition->y  = F + O;
	newPosition->z  = G + P;
	newPosition->u  = H + Q;
	newPosition->v  = I + R;
	newPosition->w  = J + S;
	return 0;
  }
  
  return -1;

}

#ifdef SAL__BUILD_INLINE_TEST
int main ( int argc, char **argv ) {
   hexapod_command_moveC newPosition;
   double elevation=0.0;

   while ( elevation < 85.0 ) {
      hexapodCalculator(1,elevation,&newPosition);
      printf("Camera combined at %lf : X %lf Y %lf Z %lf U %lf V %lf W %lf\n",elevation,
                                     newPosition.x, newPosition.y, newPosition.z,
                                     newPosition.u, newPosition.v, newPosition.w,
            );
      elevation = elevation + 1.0;
   }
   elevation = 0.0;
   while ( elevation < 85.0 ) {
      hexapodCalculator(2,elevation,&newPosition);
      printf("M2 combined at %lf : X %lf Y %lf Z %lf U %lf V %lf W %lf\n", elevation,
                                     newPosition.x, newPosition.y, newPosition.z,
                                     newPosition.u, newPosition.v, newPosition.w,
            );
      elevation = elevation + 1.0;
   }
   exit(0);

}
#endif



