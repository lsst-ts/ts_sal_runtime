#include <math.h>

int tcsSpm ( double v1[3], double v2[3], double v3[3],
             double v1r[3], double v2r[3], double v3r[3],
             double spm[3][3] )

/*
**  - - - - - - -
**   t c s S p m
**  - - - - - - -
**
**  Solve probe vector samples to form the sky-patch matrix.
**
**  Given:
**
**   The probe vectors before transformation
**     v1     double       1st probe vector
**     v2     double       2nd probe vector
**     v3     double       3rd probe vector
**
**   The probe vectors after transformation
**     v1r    double       1st transformed probe vector
**     v2r    double       2nd transformed probe vector
**     v3r    double       3rd transformed probe vector
**
**  Returned (argument):
**     spm   double[3][3]  sky-patch matrix
**
**  Returned (function value):
**           int           status:  0 = OK
**                                 -1 = singularity (fatal)
**
**  On the basis of three probe vectors in a small region of interest
**  which have been transformed in some locally smooth way, this routine
**  determines a matrix which describes the three probe transformations
**  exactly and which may therefore be expected to describe other
**  transformations in the same area to some useful degree of
**  approximation.
**
**  The probe vectors can be generated using the routine tcsProbev.
**
**  To show how a matrix can be devised that will produce all three of
**  the probe transformations, consider the vectors laid out as three
**  sets of simultaneous equations:
**
**  (Nomenclature:  X1 is v1[0], X1R is v1r[0] etc)
**
**     X1R  =  a*X1 + b*Y1 + c*Z1    }
**     X2R  =  a*X2 + b*Y2 + c*Z2    }-->  a,b,c
**     X3R  =  a*X3 + b*Y3 + c*Z3    }
**
**     Y1R  =  d*X1 + e*Y1 + f*Z1    }
**     Y2R  =  d*X2 + e*Y2 + f*Z2    }-->  d,e,f
**     Y3R  =  d*X3 + e*Y3 + f*Z3    }
**
**     Z1R  =  g*X1 + h*Y1 + i*Z1    }
**     Z2R  =  g*X2 + h*Y2 + i*Z2    }-->  g,h,i
**     Z3R  =  g*X3 + h*Y3 + i*Z3    }
**
**  Note that the matrix of coefficients in each case is the same,
**  and so only one inversion has to be carried out.
**
**  The solutions to these equations can be written out as:
**
**    | XR |     | a  b  c |     | X |
**    | YR |  =  | d  e  f |  x  | Y |
**    | ZR |     | g  h  i |     | Z |
**
**  Thus the relationship between the three probe vectors and their
**  transformations, and to some hopefully useful accuracy the
**  relationship between any other vector in the region and its
**  transformation, is encapsulated in the matrix, which is called
**  the "sky-patch matrix" (SPM).
**
**  The inverse SPM is obtained simply by calling the present routine
**  with the roles of the two vectors reversed.
**
**  Last revision:   25 June 2003
**
**  Copyright P.T.Wallace.   All rights reserved.
*/

{
   int i, j, k;
   double a1, b1, c1, a2, b2, c2, a3, b3, c3,
          a1b2, a1c2, a2b3, a2c3, a3b1, a3c1, b1a2, b1c2, b2a3,
          b2c3, b3a1, b3c1, c1a2, c1b2, c2a3, c2b3, c3a1, c3b1,
          d, a[3][3], v[3], w;



/* Arrange the three "before" vectors as a 3x3 matrix. */
   a1 = v1[0];  b1 = v1[1];  c1 = v1[2];
   a2 = v2[0];  b2 = v2[1];  c2 = v2[2];
   a3 = v3[0];  b3 = v3[1];  c3 = v3[2];

/* Useful products. */
   a1b2 = a1*b2;  b1a2 = b1*a2;  c1a2 = c1*a2;
   a1c2 = a1*c2;  b1c2 = b1*c2;  c1b2 = c1*b2;
   a2b3 = a2*b3;  b2a3 = b2*a3;  c2a3 = c2*a3;
   a2c3 = a2*c3;  b2c3 = b2*c3;  c2b3 = c2*b3;
   a3b1 = a3*b1;  b3a1 = b3*a1;  c3a1 = c3*a1;
   a3c1 = a3*c1;  b3c1 = b3*c1;  c3b1 = c3*b1;

/* Determinant (must be non-zero). */
   if ( ( d = a1*(b2c3-c2b3) +
              a2*(b3c1-c3b1) +
              a3*(b1c2-c1b2) ) == 0.0 ) return -1;

/* Invert using adj/det. */
   a[0][0]=(b2c3-c2b3)/d;  a[0][1]=(b3c1-c3b1)/d;  a[0][2]=(b1c2-c1b2)/d;
   a[1][0]=(c2a3-a2c3)/d;  a[1][1]=(c3a1-a3c1)/d;  a[1][2]=(c1a2-a1c2)/d;
   a[2][0]=(a2b3-b2a3)/d;  a[2][1]=(a3b1-b3a1)/d;  a[2][2]=(a1b2-b1a2)/d;

/* Solve for successive rows of the SPM. */
   for ( k = 0; k < 3; k++ ) {
      v[0] = v1r[k];
      v[1] = v2r[k];
      v[2] = v3r[k];
      for ( j = 0; j < 3; j++ ) {
         w = 0.0;
         for ( i = 0; i < 3; i++ ) {
            w += a[j][i] * v[i];
         }
         spm[k][j] = w;
      }
   }

/* Success. */
   return 0;

}
