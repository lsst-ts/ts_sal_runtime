#include <stdio.h>

int main ( )

/*
**   - - - - - -
**    S T A R S
**   - - - - - -
**
**  Output list of more or less equally spaced stars.
**
**  This revision:   25 September 2004
**
**  Copyright P.T.Wallace.  All rights reserved.
*/

#define R2D 57.29577951308232

{
/* Test stars (RA,Dec, 10 deg spacing, all over the sky) */
   double stars[][2] = { { 0.2023839951, -1.4602692127 },
                         { 4.7540435791, -1.4920477867 },
                         { 3.3970603943, -1.4061105251 },
                         { 1.1609034538, -1.3824869394 },
                         { 4.8487205505, -1.3393758535 },
                         { 2.4034888744, -1.4011769295 },
                         { 0.4627968669, -1.2892031670 },
                         { 4.1826639175, -1.2839213610 },
                         { 1.7049577236, -1.2869338989 },
                         { 5.3807797432, -1.2733820677 },
                         { 2.5887894630, -1.2510886192 },
                         { 6.0900831223, -1.2700991631 },
                         { 3.5777547359, -1.2642232180 },
                         { 1.1808561087, -1.2025345564 },
                         { 4.7986021042, -1.1644046307 },
                         { 2.0998678207, -1.1621278524 },
                         { 5.6782350540, -1.1485576630 },
                         { 2.9675607681, -1.1602735519 },
                         { 0.1784265190, -1.1480511427 },
                         { 3.6732277870, -1.1259524822 },
                         { 0.7969769239, -1.1368205547 },
                         { 4.3370394707, -1.1347736120 },
                         { 1.6460179090, -1.1320241690 },
                         { 5.2815775871, -1.1111669540 },
                         { 2.5617871284, -1.0786845684 },
                         { 6.0678405762, -1.0653810501 },
                         { 3.2719535828, -1.0494248867 },
                         { 0.4630443156, -1.0242053270 },
                         { 3.9402253628, -1.0160945654 },
                         { 1.1137742996, -1.0132803917 },
                         { 4.5678291321, -1.0055269003 },
                         { 1.7264263630, -0.9898629189 },
                         { 5.1165647507, -0.9900610447 },
                         { 2.2711219788, -1.0043405294 },
                         { 5.7454738617, -0.9948738217 },
                         { 2.9253358841, -0.9944746494 },
                         { 0.1114246249, -0.9882577062 },
                         { 3.5926563740, -0.9769857526 },
                         { 0.8004332781, -0.9698514938 },
                         { 4.2564477921, -0.9622449875 },
                         { 1.4162840843, -0.9531301856 },
                         { 4.8416447639, -0.9284466505 },
                         { 1.9839632511, -0.9113613367 },
                         { 5.3955187798, -0.8985093832 },
                         { 2.5247206688, -0.8815792203 },
                         { 5.9403634071, -0.8632101417 },
                         { 3.0614681244, -0.8470860720 },
                         { 0.1718508154, -0.8319614530 },
                         { 3.5540935993, -0.8253006935 },
                         { 0.6563051939, -0.8375213146 },
                         { 4.0546464920, -0.8454928994 },
                         { 1.1731717587, -0.8454608321 },
                         { 4.5697884560, -0.8401048183 },
                         { 1.6886136532, -0.8334519267 },
                         { 5.1023015976, -0.8316051364 },
                         { 2.2360634804, -0.8396403790 },
                         { 5.6476354599, -0.8424904943 },
                         { 2.7785413265, -0.8465523124 },
                         { 6.1901812553, -0.8445417285 },
                         { 3.3075125217, -0.8357475400 },
                         { 0.4189701974, -0.8178796768 },
                         { 3.8134932518, -0.8038007617 },
                         { 0.9197949767, -0.7893531322 },
                         { 4.2994918823, -0.7749593258 },
                         { 1.3903527260, -0.7590028644 },
                         { 4.7606577873, -0.7362155914 },
                         { 1.8511022329, -0.7112608552 },
                         { 5.2220883369, -0.6880164146 },
                         { 2.3000984192, -0.6755435467 },
                         { 5.6584720612, -0.6694545746 },
                         { 2.7346415520, -0.6693354249 },
                         { 6.0974965096, -0.6685055494 },
                         { 3.1790897846, -0.6657978892 },
                         { 0.2608600259, -0.6618583202 },
                         { 3.6245069504, -0.6620541215 },
                         { 0.7004449964, -0.6672249436 },
                         { 4.0566754341, -0.6702769995 },
                         { 1.1309324503, -0.6707017422 },
                         { 4.4918165207, -0.6710267067 },
                         { 1.5768318176, -0.6758371592 },
                         { 4.9537525177, -0.6882690191 },
                         { 2.0517404079, -0.7044513822 },
                         { 5.4259667397, -0.7110539675 },
                         { 2.5105042458, -0.7072287202 },
                         { 5.8769946098, -0.6978838444 },
                         { 2.9617164135, -0.6863729358 },
                         { 0.0467984602, -0.6711441278 },
                         { 3.4133045673, -0.6545349956 },
                         { 0.4937753081, -0.6376830935 },
                         { 3.8508093357, -0.6230504513 },
                         { 0.9193373919, -0.6112432480 },
                         { 4.2683033943, -0.6018658876 },
                         { 1.3335889578, -0.5933133364 },
                         { 4.6799950600, -0.5834034681 },
                         { 1.7412793636, -0.5740225315 },
                         { 5.0827813148, -0.5658733249 },
                         { 2.1392600536, -0.5611502528 },
                         { 5.4799308777, -0.5566346049 },
                         { 2.5368406773, -0.5505263209 },
                         { 5.8732509613, -0.5424134731 },
                         { 2.9229888916, -0.5344704986 },
                         { 6.2556810379, -0.5261051655 },
                         { 3.3071894646, -0.5177214146 },
                         { 0.3606971204, -0.5086211562 },
                         { 3.6967961788, -0.5005220771 },
                         { 0.7491182089, -0.4945575893 },
                         { 4.0847001076, -0.4891374111 },
                         { 1.1371048689, -0.4839305878 },
                         { 4.4721608162, -0.4794651866 },
                         { 1.5246816874, -0.4766630530 },
                         { 4.8617568016, -0.4741349220 },
                         { 1.9169961214, -0.4699570835 },
                         { 5.2551212311, -0.4635477960 },
                         { 2.3094048500, -0.4584203660 },
                         { 5.6469717026, -0.4544793665 },
                         { 2.7017011642, -0.4524823129 },
                         { 6.0395450592, -0.4514925182 },
                         { 3.0936710835, -0.4514961243 },
                         { 0.1479065716, -0.4510366917 },
                         { 3.4856116772, -0.4494118989 },
                         { 0.5402652621, -0.4455334842 },
                         { 3.8767201900, -0.4402543902 },
                         { 0.9287418723, -0.4347916842 },
                         { 4.2631735802, -0.4297549427 },
                         { 1.3143420219, -0.4251430333 },
                         { 4.6483588219, -0.4203492999 },
                         { 1.6993246078, -0.4162187874 },
                         { 5.0342216492, -0.4127006829 },
                         { 2.0885281563, -0.4105729759 },
                         { 5.4277677536, -0.4077326357 },
                         { 2.4843261242, -0.4032979906 },
                         { 5.8243193626, -0.3962554634 },
                         { 2.8810281754, -0.3876963854 },
                         { 6.2197728157, -0.3779101670 },
                         { 3.2729098797, -0.3679995835 },
                         { 0.3235772252, -0.3579129875 },
                         { 3.6555399895, -0.3483421206 },
                         { 0.7033516169, -0.3394651115 },
                         { 4.0328555107, -0.3310492933 },
                         { 1.0777544975, -0.3230058253 },
                         { 4.4042468071, -0.3152219355 },
                         { 1.4462779760, -0.3076301515 },
                         { 4.7697610855, -0.2995646596 },
                         { 1.8080918789, -0.2909673750 },
                         { 5.1273379326, -0.2817419767 },
                         { 2.1613538265, -0.2728131115 },
                         { 5.4768023491, -0.2640656233 },
                         { 2.5077443123, -0.2562538385 },
                         { 5.8209204674, -0.2493184954 },
                         { 2.8504796028, -0.2444042563 },
                         { 6.1636309624, -0.2415126264 },
                         { 3.1946749687, -0.2404644936 },
                         { 0.2270207703, -0.2401286364 },
                         { 3.5438153744, -0.2400860637 },
                         { 0.5787768364, -0.2397169620 },
                         { 3.8976926804, -0.2385824323 },
                         { 0.9339070320, -0.2367471755 },
                         { 4.2533040047, -0.2343633473 },
                         { 1.2894903421, -0.2316925824 },
                         { 4.6083955765, -0.2287003398 },
                         { 1.6437102556, -0.2257483602 },
                         { 4.9616289139, -0.2227757722 },
                         { 1.9960818291, -0.2199642211 },
                         { 5.3132157326, -0.2168084681 },
                         { 2.3466672897, -0.2134643644 },
                         { 5.6628561020, -0.2097269297 },
                         { 2.6958019733, -0.2056189775 },
                         { 6.0123558044, -0.2008607984 },
                         { 3.0465092659, -0.1954771429 },
                         { 0.0815951079, -0.1894450188 },
                         { 3.4006862640, -0.1830452383 },
                         { 0.4373295903, -0.1764405370 },
                         { 3.7573606968, -0.1697675884 },
                         { 0.7943120003, -0.1630458534 },
                         { 4.1142244339, -0.1562730372 },
                         { 1.1508078575, -0.1495262235 },
                         { 4.4701566696, -0.1427846402 },
                         { 1.5061373711, -0.1361587346 },
                         { 4.8250169754, -0.1295293570 },
                         { 1.8606729507, -0.1230495200 },
                         { 5.1792416573, -0.1166224480 },
                         { 2.2144000530, -0.1105955020 },
                         { 5.5325002670, -0.1048469171 },
                         { 2.5671486855, -0.0996660069 },
                         { 5.8847446442, -0.0950180888 },
                         { 2.9187555313, -0.0911669508 },
                         { 6.2356452942, -0.0879074559 },
                         { 3.2691140175, -0.0850544721 },
                         { 0.3026749790, -0.0822316110 },
                         { 3.6194555759, -0.0791850984 },
                         { 0.6532686949, -0.0757094547 },
                         { 3.9703242779, -0.0716736242 },
                         { 1.0043638945, -0.0671677440 },
                         { 4.3215489388, -0.0622532777 },
                         { 1.3556607962, -0.0571228564 },
                         { 4.6728887558, -0.0517867655 },
                         { 1.7070165873, -0.0464191251 },
                         { 5.0242195129, -0.0409984738 },
                         { 2.0582959652, -0.0356193222 },
                         { 5.3755221367, -0.0302315019 },
                         { 2.4095942974, -0.0249168631 },
                         { 5.7268786430, -0.0196970496 },
                         { 2.7610163689, -0.0146226482 },
                         { 6.0784306526, -0.0097199772 },
                         { 3.1126620770, -0.0049902657 },
                         { 0.1469794959, -0.0003721840 },
                         { 3.4644839764,  0.0042350441 },
                         { 0.4989354610,  0.0089065917 },
                         { 3.8165266514,  0.0137842214 },
                         { 0.8510131836,  0.0188407283 },
                         { 4.1685881615,  0.0240316074 },
                         { 1.2030098438,  0.0291943774 },
                         { 4.5204725266,  0.0342931449 },
                         { 1.5547407866,  0.0392231457 },
                         { 4.8720049858,  0.0440423414 },
                         { 1.9060536623,  0.0487070717 },
                         { 5.2230935097,  0.0532152690 },
                         { 2.2568376064,  0.0575001650 },
                         { 5.5735983849,  0.0615154915 },
                         { 2.6070127487,  0.0652143881 },
                         { 5.9234485626,  0.0684865713 },
                         { 2.9564647675,  0.0713424310 },
                         { 6.2725815773,  0.0738446191 },
                         { 3.3054902554,  0.0762231126 },
                         { 0.3387455344,  0.0787003934 },
                         { 3.6558024883,  0.0816973001 },
                         { 0.6906884313,  0.0854406506 },
                         { 4.0095839500,  0.0901507810 },
                         { 1.0460264683,  0.0957538038 },
                         { 4.3659663200,  0.1021646932 },
                         { 1.4029723406,  0.1091611758 },
                         { 4.7231326103,  0.1166619509 },
                         { 1.7601743937,  0.1244925633 },
                         { 5.0801982880,  0.1324812770 },
                         { 2.1170539856,  0.1406393796 },
                         { 5.4370861053,  0.1487996727 },
                         { 2.4740860462,  0.1570789367 },
                         { 5.7944397926,  0.1652925909 },
                         { 2.8317294121,  0.1735981405 },
                         { 6.1522989273,  0.1818111837 },
                         { 3.1893541813,  0.1898214221 },
                         { 0.2258560359,  0.1971825957 },
                         { 3.5446403027,  0.2035795450 },
                         { 0.5793867111,  0.2085016370 },
                         { 3.8963735104,  0.2119737267 },
                         { 0.9297687411,  0.2142822146 },
                         { 4.2461423874,  0.2159397900 },
                         { 1.2795206308,  0.2172725201 },
                         { 4.5961976051,  0.2185788155 },
                         { 1.6299921274,  0.2199485600 },
                         { 4.9470825195,  0.2215248197 },
                         { 1.9814056158,  0.2233090997 },
                         { 5.2992444038,  0.2248938680 },
                         { 2.3342766762,  0.2262085825 },
                         { 5.6527638435,  0.2267320007 },
                         { 2.6881549358,  0.2264607251 },
                         { 6.0066800117,  0.2249250859 },
                         { 3.0414304733,  0.2225911170 },
                         { 0.0754416436,  0.2199601978 },
                         { 3.3915340900,  0.2180384099 },
                         { 0.4232532978,  0.2177386880 },
                         { 3.7368254662,  0.2205064595 },
                         { 0.7666984797,  0.2264596820 },
                         { 4.0798225403,  0.2351221144 },
                         { 1.1106543541,  0.2455006540 },
                         { 4.4258279800,  0.2567885220 },
                         { 1.4594755173,  0.2682545185 },
                         { 4.7781381607,  0.2794939280 },
                         { 1.8160492182,  0.2900789678 },
                         { 5.1393370628,  0.2995068431 },
                         { 2.1816344261,  0.3082937002 },
                         { 5.5090546608,  0.3162871897 },
                         { 2.5552601814,  0.3241128325 },
                         { 5.8866233826,  0.3312930763 },
                         { 2.9363355637,  0.3385369778 },
                         { 6.2708821297,  0.3456029892 },
                         { 3.3241117001,  0.3525262773 },
                         { 0.3790899813,  0.3592298031 },
                         { 3.7178192139,  0.3665938377 },
                         { 0.7735407352,  0.3739280999 },
                         { 4.1119351387,  0.3806509674 },
                         { 1.1662164927,  0.3864303529 },
                         { 4.5021176338,  0.3915942311 },
                         { 1.5532438755,  0.3966866732 },
                         { 4.8863563538,  0.4023737013 },
                         { 1.9366176128,  0.4087981880 },
                         { 5.2704610825,  0.4150218070 },
                         { 2.3215966225,  0.4216045737 },
                         { 5.6563081741,  0.4279641509 },
                         { 2.7087180614,  0.4348045290 },
                         { 6.0457029343,  0.4404633641 },
                         { 3.1000351906,  0.4445187449 },
                         { 0.1541401595,  0.4468442202 },
                         { 3.4912087917,  0.4485506117 },
                         { 0.5457291007,  0.4495195448 },
                         { 3.8838305473,  0.4511438608 },
                         { 0.9391320348,  0.4544331431 },
                         { 4.2776403427,  0.4595726430 },
                         { 1.3333925009,  0.4655076563 },
                         { 4.6726279259,  0.4707975686 },
                         { 1.7285672426,  0.4735226631 },
                         { 5.0657219887,  0.4746959507 },
                         { 2.1183829308,  0.4771388471 },
                         { 5.4538173676,  0.4801138341 },
                         { 2.5063197613,  0.4837603867 },
                         { 5.8418173790,  0.4864909649 },
                         { 2.8940932751,  0.4905028045 },
                         { 6.2307147980,  0.4957173765 },
                         { 3.2838082314,  0.5007488728 },
                         { 0.3344646394,  0.5052315593 },
                         { 3.6671962738,  0.5118573308 },
                         { 0.7188867331,  0.5199378133 },
                         { 4.0567312241,  0.5281804204 },
                         { 1.1138632298,  0.5357629061 },
                         { 4.4548311234,  0.5431380868 },
                         { 1.5136538744,  0.5520054102 },
                         { 4.8566880226,  0.5627722740 },
                         { 1.9180593491,  0.5747620463 },
                         { 5.2648510933,  0.5854102373 },
                         { 2.3306810856,  0.5957382321 },
                         { 5.6815428734,  0.6059652567 },
                         { 2.7532718182,  0.6190117002 },
                         { 6.1150336266,  0.6323872209 },
                         { 3.1989486217,  0.6449341774 },
                         { 0.2844809890,  0.6569168568 },
                         { 3.6511018276,  0.6697030067 },
                         { 0.7322590351,  0.6812549233 },
                         { 4.0954518318,  0.6897210479 },
                         { 1.1784754992,  0.6922538877 },
                         { 4.5522069931,  0.6851828098 },
                         { 1.6510941982,  0.6726416945 },
                         { 5.0274505615,  0.6647042632 },
                         { 2.1106753349,  0.6634134650 },
                         { 5.4707145691,  0.6628856063 },
                         { 2.5452916622,  0.6617949605 },
                         { 5.9034624100,  0.6546838880 },
                         { 2.9812569618,  0.6489675641 },
                         { 0.0639998689,  0.6488913894 },
                         { 3.4310538769,  0.6525344849 },
                         { 0.5125744939,  0.6528801918 },
                         { 3.8720481396,  0.6522467732 },
                         { 0.9449617863,  0.6550730467 },
                         { 4.3012828827,  0.6644693613 },
                         { 1.3791576624,  0.6806787848 },
                         { 4.7484369278,  0.7064419985 },
                         { 1.8399198055,  0.7363327742 },
                         { 5.2144570351,  0.7587296367 },
                         { 2.3108315468,  0.7752645612 },
                         { 5.6965699196,  0.7879756689 },
                         { 2.8076953888,  0.8028543591 },
                         { 6.2052445412,  0.8169250488 },
                         { 3.3175539970,  0.8285622597 },
                         { 0.4374469221,  0.8300954103 },
                         { 3.8450274467,  0.8283985257 },
                         { 0.9720923305,  0.8251551986 },
                         { 4.3833909035,  0.8211348057 },
                         { 1.5110023022,  0.8132632375 },
                         { 4.9176568985,  0.8150259852 },
                         { 2.0404567719,  0.8275998235 },
                         { 5.4438920021,  0.8341895938 },
                         { 2.5670380592,  0.8345547915 },
                         { 5.9670395851,  0.8173551559 },
                         { 3.0691235065,  0.8043031693 },
                         { 0.1683581173,  0.8112451434 },
                         { 3.5600657463,  0.8329078555 },
                         { 0.6809320450,  0.8571899533 },
                         { 4.0897483826,  0.8773648739 },
                         { 1.2155671120,  0.8977969289 },
                         { 4.6341590881,  0.9152768850 },
                         { 1.7833057642,  0.9372192025 },
                         { 5.2180685997,  0.9557137489 },
                         { 2.3859107494,  0.9622805715 },
                         { 5.8525724411,  0.9580721259 },
                         { 3.0503053665,  0.9572334886 },
                         { 0.2366534173,  0.9649416804 },
                         { 3.6993684769,  0.9773906469 },
                         { 0.8861275911,  0.9849122167 },
                         { 4.3555502892,  0.9854708910 },
                         { 1.5082149506,  0.9667450786 },
                         { 4.9138832092,  0.9672702551 },
                         { 2.0665163994,  0.9904084206 },
                         { 5.5214734077,  1.0006765127 },
                         { 2.6895153522,  1.0186048746 },
                         { 6.1628890038,  1.0291427374 },
                         { 3.3620169163,  1.0536923409 },
                         { 0.5747972727,  1.0665990114 },
                         { 4.0882081985,  1.0719833374 },
                         { 1.3661947250,  1.0934808254 },
                         { 4.9651031494,  1.1157166958 },
                         { 2.2682723999,  1.1271880865 },
                         { 5.8248257637,  1.1236610413 },
                         { 2.9930546284,  1.1084972620 },
                         { 0.1732579172,  1.1233972311 },
                         { 3.6783876419,  1.1452090740 },
                         { 0.9394987822,  1.1514806747 },
                         { 4.5209345818,  1.1590665579 },
                         { 1.8333736658,  1.1817091703 },
                         { 5.4463019371,  1.1881698370 },
                         { 2.9385728836,  1.2539292574 },
                         { 0.4475953579,  1.2562826872 },
                         { 4.0868000984,  1.2409744263 },
                         { 1.3049967289,  1.2496130466 },
                         { 4.8822417259,  1.2765957117 },
                         { 2.3550693989,  1.2865910530 },
                         { 6.1203932762,  1.2974059582 },
                         { 3.6884040833,  1.3512307405 },
                         { 1.6482454538,  1.3855227232 },
                         { 5.4595737457,  1.3605339527 },
                         { 2.8616786003,  1.4297649860 },
                         { 0.5994768143,  1.4295963049 },
                         { 4.7056641579,  1.4949979782 } };
   int nstars = sizeof(stars)/(2*sizeof(double));
   int i;

   for ( i = 0; i < nstars; i++ ) {
      printf ( "%10.6f %+10.6f\n", stars[i][0]*R2D, stars[i][1]*R2D );
   }

   return 1;

}
