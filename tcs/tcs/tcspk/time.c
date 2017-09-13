int tcsTime ( double *tai )
/*
**  - - - - - - - -      **********************************************
**   t c s T i m e       *** DUMMY FOR TESTING: RETURNS FIXED VALUE ***
**  - - - - - - - -      **********************************************
**
**  Read the current time.
**
**  Returned (argument):
**     tai      double*     TAI Modified Julian Date (JD-2400000.5)
**
**  Returned (function value):
**              int         status:  0 = OK
**
**  Notes:
**
**  1  A fixed result is returned, corresponding to 1994 July 27,
**     15:26:29 TAI precisely.  Obviously, the chosen date and time is
**     easily changed and the TCS developer may well want to do this for
**     test purposes.  (n.b. See also Note 3.)
**
**  2  The function is called only by the demonstration programs, not by
**     the TCSpk callable subroutines.  A real TCS application may even
**     not require a tcsTime function: the mechanism used to generate
**     the time inputs to the TCSpk calls is entirely a matter for the
**     application.
**
**  3  Note that the test date is many years in the past, and that
**     the UT1-UTC and TAI-UTC values used in the demonstration programs
**     apply to this date.  An operational TCS needs the latest values
**     and the means of updating them once every few days (at least),
**     not the numbers used in the demonstration programs.  (Similar
**     remarks apply to the site coordinates, meteorological inputs
**     etc., but these are less likely to be overlooked.)
**
**  4  Zero status (= OK) is always returned.
**
**  Last revision:   15 June 2003
**
**  Copyright P.T.Wallace.  All rights reserved.
*/
{
   *tai = 49560.0                                          /* 1994 July 27 */
        + ( 60 * ( 60 * 15.0 + 26.0 ) + 29.0 ) / 86400.0;  /* 15:26:29 TAI */
   return 0;
}
