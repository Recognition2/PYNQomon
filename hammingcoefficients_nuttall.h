/// Generated by MATLAB
// do more stuff

u16 filter_nuttall[80][45] = {
24, 35, 58, 89, 127, 172, 226, 287, 356, 430, 511, 595, 681, 768, 853, 935, 1011, 1079, 1137, 1185, 1220, 1241, 1248, 1241, 1220, 1185, 1137, 1079, 1011, 935, 853, 768, 681, 595, 511, 430, 356, 287, 226, 172, 127, 89, 58, 35, 24, 
28, 40, 67, 103, 147, 200, 261, 332, 412, 498, 591, 688, 788, 889, 988, 1082, 1170, 1249, 1317, 1372, 1412, 1437, 1445, 1437, 1412, 1372, 1317, 1249, 1170, 1082, 988, 889, 788, 688, 591, 498, 412, 332, 261, 200, 147, 103, 67, 40, 28, 
37, 54, 90, 138, 197, 267, 350, 445, 551, 668, 792, 922, 1056, 1191, 1323, 1450, 1568, 1673, 1764, 1838, 1892, 1925, 1936, 1925, 1892, 1838, 1764, 1673, 1568, 1450, 1323, 1191, 1056, 922, 792, 668, 551, 445, 350, 267, 197, 138, 90, 54, 37, 
50, 72, 121, 185, 264, 359, 470, 598, 740, 896, 1063, 1238, 1418, 1599, 1776, 1946, 2104, 2246, 2368, 2467, 2540, 2584, 2599, 2584, 2540, 2467, 2368, 2246, 2104, 1946, 1776, 1599, 1418, 1238, 1063, 896, 740, 598, 470, 359, 264, 185, 121, 72, 50, 
64, 94, 158, 241, 344, 468, 613, 779, 964, 1167, 1385, 1613, 1847, 2083, 2314, 2535, 2741, 2926, 3085, 3214, 3308, 3366, 3386, 3366, 3308, 3214, 3085, 2926, 2741, 2535, 2314, 2083, 1847, 1613, 1385, 1167, 964, 779, 613, 468, 344, 241, 158, 94, 64, 
82, 119, 199, 305, 435, 592, 776, 986, 1221, 1478, 1753, 2042, 2339, 2637, 2929, 3210, 3470, 3704, 3906, 4068, 4188, 4261, 4286, 4261, 4188, 4068, 3906, 3704, 3470, 3210, 2929, 2637, 2339, 2042, 1753, 1478, 1221, 986, 776, 592, 435, 305, 199, 119, 82, 
101, 147, 247, 377, 539, 732, 959, 1219, 1510, 1828, 2169, 2526, 2893, 3262, 3624, 3970, 4293, 4582, 4831, 5033, 5181, 5271, 5302, 5271, 5181, 5033, 4831, 4582, 4293, 3970, 3624, 3262, 2893, 2526, 2169, 1828, 1510, 1219, 959, 732, 539, 377, 247, 147, 101, 
123, 179, 300, 458, 654, 889, 1165, 1481, 1834, 2220, 2633, 3067, 3513, 3960, 4400, 4821, 5212, 5564, 5866, 6111, 6291, 6401, 6438, 6401, 6291, 6111, 5866, 5564, 5212, 4821, 4400, 3960, 3513, 3067, 2633, 2220, 1834, 1481, 1165, 889, 654, 458, 300, 179, 123, 
147, 214, 358, 548, 782, 1063, 1393, 1771, 2193, 2654, 3149, 3667, 4200, 4736, 5261, 5765, 6233, 6653, 7015, 7307, 7522, 7654, 7698, 7654, 7522, 7307, 7015, 6653, 6233, 5765, 5261, 4736, 4200, 3667, 3149, 2654, 2193, 1771, 1393, 1063, 782, 548, 358, 214, 147, 
173, 252, 423, 647, 923, 1255, 1644, 2090, 2588, 3133, 3716, 4328, 4957, 5589, 6210, 6804, 7356, 7852, 8279, 8624, 8878, 9033, 9085, 9033, 8878, 8624, 8279, 7852, 7356, 6804, 6210, 5589, 4957, 4328, 3716, 3133, 2588, 2090, 1644, 1255, 923, 647, 423, 252, 173, 
202, 294, 493, 755, 1077, 1464, 1919, 2438, 3020, 3655, 4336, 5051, 5784, 6522, 7246, 7939, 8583, 9162, 9660, 10063, 10359, 10540, 10601, 10540, 10359, 10063, 9660, 9162, 8583, 7939, 7246, 6522, 5784, 5051, 4336, 3655, 3020, 2438, 1919, 1464, 1077, 755, 493, 294, 202, 
233, 340, 570, 872, 1244, 1691, 2216, 2816, 3488, 4222, 5009, 5834, 6681, 7533, 8369, 9169, 9914, 10583, 11158, 11623, 11965, 12174, 12245, 12174, 11965, 11623, 11158, 10583, 9914, 9169, 8369, 7533, 6681, 5834, 5009, 4222, 3488, 2816, 2216, 1691, 1244, 872, 570, 340, 233, 
267, 389, 652, 997, 1424, 1936, 2536, 3223, 3992, 4832, 5732, 6677, 7646, 8621, 9578, 10494, 11346, 12112, 12770, 13302, 13694, 13933, 14014, 13933, 13694, 13302, 12770, 12112, 11346, 10494, 9578, 8621, 7646, 6677, 5732, 4832, 3992, 3223, 2536, 1936, 1424, 997, 652, 389, 267, 
303, 441, 740, 1132, 1616, 2197, 2878, 3658, 4530, 5484, 6505, 7577, 8678, 9784, 10870, 11910, 12877, 13745, 14492, 15096, 15541, 15813, 15904, 15813, 15541, 15096, 14492, 13745, 12877, 11910, 10870, 9784, 8678, 7577, 6505, 5484, 4530, 3658, 2878, 2197, 1616, 1132, 740, 441, 303, 
341, 497, 834, 1275, 1819, 2474, 3241, 4119, 5101, 6175, 7326, 8533, 9772, 11018, 12241, 13412, 14501, 15479, 16320, 17000, 17501, 17807, 17910, 17807, 17501, 17000, 16320, 15479, 14501, 13412, 12241, 11018, 9772, 8533, 7326, 6175, 5101, 4119, 3241, 2474, 1819, 1275, 834, 497, 341, 
381, 556, 932, 1425, 2034, 2766, 3624, 4605, 5703, 6904, 8191, 9540, 10926, 12318, 13686, 14995, 16212, 17306, 18246, 19007, 19566, 19909, 20024, 19909, 19566, 19007, 18246, 17306, 16212, 14995, 13686, 12318, 10926, 9540, 8191, 6904, 5703, 4605, 3624, 2766, 2034, 1425, 932, 556, 381, 
424, 617, 1035, 1583, 2259, 3072, 4024, 5114, 6334, 7667, 9096, 10594, 12133, 13680, 15198, 16652, 18004, 19219, 20263, 21107, 21729, 22109, 22237, 22109, 21729, 21107, 20263, 19219, 18004, 16652, 15198, 13680, 12133, 10594, 9096, 7667, 6334, 5114, 4024, 3072, 2259, 1583, 1035, 617, 424, 
467, 681, 1142, 1747, 2493, 3389, 4441, 5644, 6989, 8461, 10037, 11691, 13389, 15095, 16771, 18376, 19868, 21208, 22360, 23292, 23978, 24397, 24538, 24397, 23978, 23292, 22360, 21208, 19868, 18376, 16771, 15095, 13389, 11691, 10037, 8461, 6989, 5644, 4441, 3389, 2493, 1747, 1142, 681, 467, 
513, 747, 1253, 1916, 2734, 3718, 4871, 6191, 7667, 9281, 11010, 12824, 14687, 16559, 18397, 20157, 21793, 23263, 24527, 25550, 26302, 26762, 26917, 26762, 26302, 25550, 24527, 23263, 21793, 20157, 18397, 16559, 14687, 12824, 11010, 9281, 7667, 6191, 4871, 3718, 2734, 1916, 1253, 747, 513, 
559, 815, 1366, 2090, 2982, 4055, 5313, 6753, 8362, 10123, 12009, 13987, 16019, 18061, 20066, 21985, 23770, 25374, 26752, 27868, 28688, 29190, 29359, 29190, 28688, 27868, 26752, 25374, 23770, 21985, 20066, 18061, 16019, 13987, 12009, 10123, 8362, 6753, 5313, 4055, 2982, 2090, 1366, 815, 559, 
607, 884, 1482, 2267, 3235, 4399, 5764, 7325, 9072, 10982, 13028, 15174, 17378, 19593, 21768, 23850, 25787, 27527, 29022, 30232, 31122, 31666, 31850, 31666, 31122, 30232, 29022, 27527, 25787, 23850, 21768, 19593, 17378, 15174, 13028, 10982, 9072, 7325, 5764, 4399, 3235, 2267, 1482, 884, 607, 
655, 954, 1600, 2447, 3492, 4748, 6221, 7906, 9791, 11852, 14060, 16376, 18755, 21146, 23493, 25741, 27831, 29708, 31322, 32628, 33588, 34176, 34374, 34176, 33588, 32628, 31322, 29708, 27831, 25741, 23493, 21146, 18755, 16376, 14060, 11852, 9791, 7906, 6221, 4748, 3492, 2447, 1600, 954, 655, 
703, 1025, 1718, 2627, 3750, 5099, 6680, 8490, 10514, 12728, 15100, 17587, 20142, 22709, 25230, 27643, 29888, 31904, 33637, 35039, 36071, 36702, 36914, 36702, 36071, 35039, 33637, 31904, 29888, 27643, 25230, 22709, 20142, 17587, 15100, 12728, 10514, 8490, 6680, 5099, 3750, 2627, 1718, 1025, 703, 
751, 1095, 1836, 2808, 4008, 5450, 7140, 9074, 11238, 13604, 16138, 18797, 21527, 24271, 26965, 29545, 31944, 34099, 35951, 37450, 38552, 39227, 39454, 39227, 38552, 37450, 35951, 34099, 31944, 29545, 26965, 24271, 21527, 18797, 16138, 13604, 11238, 9074, 7140, 5450, 4008, 2808, 1836, 1095, 751, 
799, 1165, 1953, 2988, 4264, 5798, 7596, 9654, 11955, 14473, 17169, 19998, 22903, 25822, 28688, 31432, 33985, 36277, 38248, 39843, 41015, 41733, 41974, 41733, 41015, 39843, 38248, 36277, 33985, 31432, 28688, 25822, 22903, 19998, 17169, 14473, 11955, 9654, 7596, 5798, 4264, 2988, 1953, 1165, 799, 
847, 1234, 2069, 3164, 4516, 6141, 8045, 10225, 12663, 15329, 18185, 21181, 24257, 27349, 30385, 33292, 35995, 38423, 40511, 42199, 43442, 44201, 44457, 44201, 43442, 42199, 40511, 38423, 35995, 33292, 30385, 27349, 24257, 21181, 18185, 15329, 12663, 10225, 8045, 6141, 4516, 3164, 2069, 1234, 847, 
893, 1301, 2182, 3337, 4763, 6476, 8485, 10783, 13354, 16166, 19177, 22336, 25581, 28842, 32043, 35109, 37959, 40520, 42721, 44502, 45812, 46614, 46883, 46614, 45812, 44502, 42721, 40520, 37959, 35109, 32043, 28842, 25581, 22336, 19177, 16166, 13354, 10783, 8485, 6476, 4763, 3337, 2182, 1301, 893, 
938, 1366, 2291, 3504, 5001, 6801, 8910, 11324, 14023, 16976, 20139, 23456, 26864, 30288, 33650, 36869, 39862, 42551, 44863, 46734, 48109, 48951, 49234, 48951, 48109, 46734, 44863, 42551, 39862, 36869, 33650, 30288, 26864, 23456, 20139, 16976, 14023, 11324, 8910, 6801, 5001, 3504, 2291, 1366, 938, 
981, 1429, 2396, 3665, 5231, 7112, 9318, 11843, 14666, 17754, 21062, 24531, 28095, 31676, 35192, 38558, 41689, 44501, 46919, 48875, 50314, 51194, 51490, 51194, 50314, 48875, 46919, 44501, 41689, 38558, 35192, 31676, 28095, 24531, 21062, 17754, 14666, 11843, 9318, 7112, 5231, 3665, 2396, 1429, 981, 
1022, 1489, 2496, 3817, 5448, 7408, 9706, 12336, 15276, 18493, 21939, 25552, 29264, 32994, 36657, 40163, 43424, 46354, 48872, 50910, 52408, 53325, 53634, 53325, 52408, 50910, 48872, 46354, 43424, 40163, 36657, 32994, 29264, 25552, 21939, 18493, 15276, 12336, 9706, 7408, 5448, 3817, 2496, 1489, 1022, 
1060, 1544, 2590, 3961, 5653, 7686, 10070, 12799, 15850, 19187, 22762, 26511, 30362, 34232, 38033, 41671, 45054, 48094, 50707, 52820, 54375, 55326, 55646, 55326, 54375, 52820, 50707, 48094, 45054, 41671, 38033, 34232, 30362, 26511, 22762, 19187, 15850, 12799, 10070, 7686, 5653, 3961, 2590, 1544, 1060, 
1095, 1596, 2677, 4093, 5842, 7944, 10408, 13228, 16381, 19830, 23525, 27400, 31380, 35380, 39307, 43067, 46564, 49706, 52406, 54591, 56198, 57181, 57512, 57181, 56198, 54591, 52406, 49706, 46564, 43067, 39307, 35380, 31380, 27400, 23525, 19830, 16381, 13228, 10408, 7944, 5842, 4093, 2677, 1596, 1095, 
1128, 1643, 2756, 4215, 6015, 8179, 10716, 13619, 16866, 20417, 24221, 28211, 32309, 36427, 40471, 44342, 47942, 51176, 53957, 56206, 57861, 58873, 59213, 58873, 57861, 56206, 53957, 51176, 47942, 44342, 40471, 36427, 32309, 28211, 24221, 20417, 16866, 13619, 10716, 8179, 6015, 4215, 2756, 1643, 1128, 
1157, 1686, 2827, 4323, 6170, 8389, 10992, 13969, 17300, 20943, 24844, 28937, 33140, 37364, 41512, 45483, 49176, 52493, 55345, 57652, 59349, 60388, 60737, 60388, 59349, 57652, 55345, 52493, 49176, 45483, 41512, 37364, 33140, 28937, 24844, 20943, 17300, 13969, 10992, 8389, 6170, 4323, 2827, 1686, 1157, 
1182, 1723, 2889, 4418, 6305, 8573, 11233, 14276, 17679, 21402, 25389, 29571, 33867, 38183, 42422, 46480, 50254, 53644, 56559, 58917, 60651, 61712, 62069, 61712, 60651, 58917, 56559, 53644, 50254, 46480, 42422, 38183, 33867, 29571, 25389, 21402, 17679, 14276, 11233, 8573, 6305, 4418, 2889, 1723, 1182, 
1204, 1754, 2941, 4498, 6420, 8729, 11437, 14535, 18000, 21791, 25851, 30109, 34482, 38878, 43194, 47325, 51168, 54620, 57587, 59988, 61754, 62834, 63198, 62834, 61754, 59988, 57587, 54620, 51168, 47325, 43194, 38878, 34482, 30109, 25851, 21791, 18000, 14535, 11437, 8729, 6420, 4498, 2941, 1754, 1204, 
1221, 1779, 2984, 4563, 6513, 8856, 11603, 14746, 18261, 22107, 26225, 30545, 34982, 39441, 43819, 48011, 51909, 55411, 58421, 60857, 62648, 63744, 64113, 63744, 62648, 60857, 58421, 55411, 51909, 48011, 43819, 39441, 34982, 30545, 26225, 22107, 18261, 14746, 11603, 8856, 6513, 4563, 2984, 1779, 1221, 
1234, 1799, 3016, 4613, 6583, 8952, 11728, 14906, 18459, 22346, 26509, 30876, 35360, 39868, 44293, 48530, 52471, 56010, 59054, 61515, 63326, 64434, 64807, 64434, 63326, 61515, 59054, 56010, 52471, 48530, 44293, 39868, 35360, 30876, 26509, 22346, 18459, 14906, 11728, 8952, 6583, 4613, 3016, 1799, 1234, 
1243, 1812, 3038, 4646, 6631, 9016, 11812, 15013, 18591, 22506, 26700, 31098, 35615, 40154, 44612, 48879, 52848, 56413, 59478, 61958, 63781, 64897, 65273, 64897, 63781, 61958, 59478, 56413, 52848, 48879, 44612, 40154, 35615, 31098, 26700, 22506, 18591, 15013, 11812, 9016, 6631, 4646, 3038, 1812, 1243, 
1248, 1818, 3049, 4663, 6654, 9048, 11855, 15067, 18658, 22587, 26795, 31209, 35742, 40298, 44772, 49055, 53037, 56616, 59691, 62180, 64010, 65130, 65507, 65130, 64010, 62180, 59691, 56616, 53037, 49055, 44772, 40298, 35742, 31209, 26795, 22587, 18658, 15067, 11855, 9048, 6654, 4663, 3049, 1818, 1248, 
1248, 1818, 3049, 4663, 6654, 9048, 11855, 15067, 18658, 22587, 26795, 31209, 35742, 40298, 44772, 49055, 53037, 56616, 59691, 62180, 64010, 65130, 65507, 65130, 64010, 62180, 59691, 56616, 53037, 49055, 44772, 40298, 35742, 31209, 26795, 22587, 18658, 15067, 11855, 9048, 6654, 4663, 3049, 1818, 1248, 
1243, 1812, 3038, 4646, 6631, 9016, 11812, 15013, 18591, 22506, 26700, 31098, 35615, 40154, 44612, 48879, 52848, 56413, 59478, 61958, 63781, 64897, 65273, 64897, 63781, 61958, 59478, 56413, 52848, 48879, 44612, 40154, 35615, 31098, 26700, 22506, 18591, 15013, 11812, 9016, 6631, 4646, 3038, 1812, 1243, 
1234, 1799, 3016, 4613, 6583, 8952, 11728, 14906, 18459, 22346, 26509, 30876, 35360, 39868, 44293, 48530, 52471, 56010, 59054, 61515, 63326, 64434, 64807, 64434, 63326, 61515, 59054, 56010, 52471, 48530, 44293, 39868, 35360, 30876, 26509, 22346, 18459, 14906, 11728, 8952, 6583, 4613, 3016, 1799, 1234, 
1221, 1779, 2984, 4563, 6513, 8856, 11603, 14746, 18261, 22107, 26225, 30545, 34982, 39441, 43819, 48011, 51909, 55411, 58421, 60857, 62648, 63744, 64113, 63744, 62648, 60857, 58421, 55411, 51909, 48011, 43819, 39441, 34982, 30545, 26225, 22107, 18261, 14746, 11603, 8856, 6513, 4563, 2984, 1779, 1221, 
1204, 1754, 2941, 4498, 6420, 8729, 11437, 14535, 18000, 21791, 25851, 30109, 34482, 38878, 43194, 47325, 51168, 54620, 57587, 59988, 61754, 62834, 63198, 62834, 61754, 59988, 57587, 54620, 51168, 47325, 43194, 38878, 34482, 30109, 25851, 21791, 18000, 14535, 11437, 8729, 6420, 4498, 2941, 1754, 1204, 
1182, 1723, 2889, 4418, 6305, 8573, 11233, 14276, 17679, 21402, 25389, 29571, 33867, 38183, 42422, 46480, 50254, 53644, 56559, 58917, 60651, 61712, 62069, 61712, 60651, 58917, 56559, 53644, 50254, 46480, 42422, 38183, 33867, 29571, 25389, 21402, 17679, 14276, 11233, 8573, 6305, 4418, 2889, 1723, 1182, 
1157, 1686, 2827, 4323, 6170, 8389, 10992, 13969, 17300, 20943, 24844, 28937, 33140, 37364, 41512, 45483, 49176, 52493, 55345, 57652, 59349, 60388, 60737, 60388, 59349, 57652, 55345, 52493, 49176, 45483, 41512, 37364, 33140, 28937, 24844, 20943, 17300, 13969, 10992, 8389, 6170, 4323, 2827, 1686, 1157, 
1128, 1643, 2756, 4215, 6015, 8179, 10716, 13619, 16866, 20417, 24221, 28211, 32309, 36427, 40471, 44342, 47942, 51176, 53957, 56206, 57861, 58873, 59213, 58873, 57861, 56206, 53957, 51176, 47942, 44342, 40471, 36427, 32309, 28211, 24221, 20417, 16866, 13619, 10716, 8179, 6015, 4215, 2756, 1643, 1128, 
1095, 1596, 2677, 4093, 5842, 7944, 10408, 13228, 16381, 19830, 23525, 27400, 31380, 35380, 39307, 43067, 46564, 49706, 52406, 54591, 56198, 57181, 57512, 57181, 56198, 54591, 52406, 49706, 46564, 43067, 39307, 35380, 31380, 27400, 23525, 19830, 16381, 13228, 10408, 7944, 5842, 4093, 2677, 1596, 1095, 
1060, 1544, 2590, 3961, 5653, 7686, 10070, 12799, 15850, 19187, 22762, 26511, 30362, 34232, 38033, 41671, 45054, 48094, 50707, 52820, 54375, 55326, 55646, 55326, 54375, 52820, 50707, 48094, 45054, 41671, 38033, 34232, 30362, 26511, 22762, 19187, 15850, 12799, 10070, 7686, 5653, 3961, 2590, 1544, 1060, 
1022, 1489, 2496, 3817, 5448, 7408, 9706, 12336, 15276, 18493, 21939, 25552, 29264, 32994, 36657, 40163, 43424, 46354, 48872, 50910, 52408, 53325, 53634, 53325, 52408, 50910, 48872, 46354, 43424, 40163, 36657, 32994, 29264, 25552, 21939, 18493, 15276, 12336, 9706, 7408, 5448, 3817, 2496, 1489, 1022, 
981, 1429, 2396, 3665, 5231, 7112, 9318, 11843, 14666, 17754, 21062, 24531, 28095, 31676, 35192, 38558, 41689, 44501, 46919, 48875, 50314, 51194, 51490, 51194, 50314, 48875, 46919, 44501, 41689, 38558, 35192, 31676, 28095, 24531, 21062, 17754, 14666, 11843, 9318, 7112, 5231, 3665, 2396, 1429, 981, 
938, 1366, 2291, 3504, 5001, 6801, 8910, 11324, 14023, 16976, 20139, 23456, 26864, 30288, 33650, 36869, 39862, 42551, 44863, 46734, 48109, 48951, 49234, 48951, 48109, 46734, 44863, 42551, 39862, 36869, 33650, 30288, 26864, 23456, 20139, 16976, 14023, 11324, 8910, 6801, 5001, 3504, 2291, 1366, 938, 
893, 1301, 2182, 3337, 4763, 6476, 8485, 10783, 13354, 16166, 19177, 22336, 25581, 28842, 32043, 35109, 37959, 40520, 42721, 44502, 45812, 46614, 46883, 46614, 45812, 44502, 42721, 40520, 37959, 35109, 32043, 28842, 25581, 22336, 19177, 16166, 13354, 10783, 8485, 6476, 4763, 3337, 2182, 1301, 893, 
847, 1234, 2069, 3164, 4516, 6141, 8045, 10225, 12663, 15329, 18185, 21181, 24257, 27349, 30385, 33292, 35995, 38423, 40511, 42199, 43442, 44201, 44457, 44201, 43442, 42199, 40511, 38423, 35995, 33292, 30385, 27349, 24257, 21181, 18185, 15329, 12663, 10225, 8045, 6141, 4516, 3164, 2069, 1234, 847, 
799, 1165, 1953, 2988, 4264, 5798, 7596, 9654, 11955, 14473, 17169, 19998, 22903, 25822, 28688, 31432, 33985, 36277, 38248, 39843, 41015, 41733, 41974, 41733, 41015, 39843, 38248, 36277, 33985, 31432, 28688, 25822, 22903, 19998, 17169, 14473, 11955, 9654, 7596, 5798, 4264, 2988, 1953, 1165, 799, 
751, 1095, 1836, 2808, 4008, 5450, 7140, 9074, 11238, 13604, 16138, 18797, 21527, 24271, 26965, 29545, 31944, 34099, 35951, 37450, 38552, 39227, 39454, 39227, 38552, 37450, 35951, 34099, 31944, 29545, 26965, 24271, 21527, 18797, 16138, 13604, 11238, 9074, 7140, 5450, 4008, 2808, 1836, 1095, 751, 
703, 1025, 1718, 2627, 3750, 5099, 6680, 8490, 10514, 12728, 15100, 17587, 20142, 22709, 25230, 27643, 29888, 31904, 33637, 35039, 36071, 36702, 36914, 36702, 36071, 35039, 33637, 31904, 29888, 27643, 25230, 22709, 20142, 17587, 15100, 12728, 10514, 8490, 6680, 5099, 3750, 2627, 1718, 1025, 703, 
655, 954, 1600, 2447, 3492, 4748, 6221, 7906, 9791, 11852, 14060, 16376, 18755, 21146, 23493, 25741, 27831, 29708, 31322, 32628, 33588, 34176, 34374, 34176, 33588, 32628, 31322, 29708, 27831, 25741, 23493, 21146, 18755, 16376, 14060, 11852, 9791, 7906, 6221, 4748, 3492, 2447, 1600, 954, 655, 
607, 884, 1482, 2267, 3235, 4399, 5764, 7325, 9072, 10982, 13028, 15174, 17378, 19593, 21768, 23850, 25787, 27527, 29022, 30232, 31122, 31666, 31850, 31666, 31122, 30232, 29022, 27527, 25787, 23850, 21768, 19593, 17378, 15174, 13028, 10982, 9072, 7325, 5764, 4399, 3235, 2267, 1482, 884, 607, 
559, 815, 1366, 2090, 2982, 4055, 5313, 6753, 8362, 10123, 12009, 13987, 16019, 18061, 20066, 21985, 23770, 25374, 26752, 27868, 28688, 29190, 29359, 29190, 28688, 27868, 26752, 25374, 23770, 21985, 20066, 18061, 16019, 13987, 12009, 10123, 8362, 6753, 5313, 4055, 2982, 2090, 1366, 815, 559, 
513, 747, 1253, 1916, 2734, 3718, 4871, 6191, 7667, 9281, 11010, 12824, 14687, 16559, 18397, 20157, 21793, 23263, 24527, 25550, 26302, 26762, 26917, 26762, 26302, 25550, 24527, 23263, 21793, 20157, 18397, 16559, 14687, 12824, 11010, 9281, 7667, 6191, 4871, 3718, 2734, 1916, 1253, 747, 513, 
467, 681, 1142, 1747, 2493, 3389, 4441, 5644, 6989, 8461, 10037, 11691, 13389, 15095, 16771, 18376, 19868, 21208, 22360, 23292, 23978, 24397, 24538, 24397, 23978, 23292, 22360, 21208, 19868, 18376, 16771, 15095, 13389, 11691, 10037, 8461, 6989, 5644, 4441, 3389, 2493, 1747, 1142, 681, 467, 
424, 617, 1035, 1583, 2259, 3072, 4024, 5114, 6334, 7667, 9096, 10594, 12133, 13680, 15198, 16652, 18004, 19219, 20263, 21107, 21729, 22109, 22237, 22109, 21729, 21107, 20263, 19219, 18004, 16652, 15198, 13680, 12133, 10594, 9096, 7667, 6334, 5114, 4024, 3072, 2259, 1583, 1035, 617, 424, 
381, 556, 932, 1425, 2034, 2766, 3624, 4605, 5703, 6904, 8191, 9540, 10926, 12318, 13686, 14995, 16212, 17306, 18246, 19007, 19566, 19909, 20024, 19909, 19566, 19007, 18246, 17306, 16212, 14995, 13686, 12318, 10926, 9540, 8191, 6904, 5703, 4605, 3624, 2766, 2034, 1425, 932, 556, 381, 
341, 497, 834, 1275, 1819, 2474, 3241, 4119, 5101, 6175, 7326, 8533, 9772, 11018, 12241, 13412, 14501, 15479, 16320, 17000, 17501, 17807, 17910, 17807, 17501, 17000, 16320, 15479, 14501, 13412, 12241, 11018, 9772, 8533, 7326, 6175, 5101, 4119, 3241, 2474, 1819, 1275, 834, 497, 341, 
303, 441, 740, 1132, 1616, 2197, 2878, 3658, 4530, 5484, 6505, 7577, 8678, 9784, 10870, 11910, 12877, 13745, 14492, 15096, 15541, 15813, 15904, 15813, 15541, 15096, 14492, 13745, 12877, 11910, 10870, 9784, 8678, 7577, 6505, 5484, 4530, 3658, 2878, 2197, 1616, 1132, 740, 441, 303, 
267, 389, 652, 997, 1424, 1936, 2536, 3223, 3992, 4832, 5732, 6677, 7646, 8621, 9578, 10494, 11346, 12112, 12770, 13302, 13694, 13933, 14014, 13933, 13694, 13302, 12770, 12112, 11346, 10494, 9578, 8621, 7646, 6677, 5732, 4832, 3992, 3223, 2536, 1936, 1424, 997, 652, 389, 267, 
233, 340, 570, 872, 1244, 1691, 2216, 2816, 3488, 4222, 5009, 5834, 6681, 7533, 8369, 9169, 9914, 10583, 11158, 11623, 11965, 12174, 12245, 12174, 11965, 11623, 11158, 10583, 9914, 9169, 8369, 7533, 6681, 5834, 5009, 4222, 3488, 2816, 2216, 1691, 1244, 872, 570, 340, 233, 
202, 294, 493, 755, 1077, 1464, 1919, 2438, 3020, 3655, 4336, 5051, 5784, 6522, 7246, 7939, 8583, 9162, 9660, 10063, 10359, 10540, 10601, 10540, 10359, 10063, 9660, 9162, 8583, 7939, 7246, 6522, 5784, 5051, 4336, 3655, 3020, 2438, 1919, 1464, 1077, 755, 493, 294, 202, 
173, 252, 423, 647, 923, 1255, 1644, 2090, 2588, 3133, 3716, 4328, 4957, 5589, 6210, 6804, 7356, 7852, 8279, 8624, 8878, 9033, 9085, 9033, 8878, 8624, 8279, 7852, 7356, 6804, 6210, 5589, 4957, 4328, 3716, 3133, 2588, 2090, 1644, 1255, 923, 647, 423, 252, 173, 
147, 214, 358, 548, 782, 1063, 1393, 1771, 2193, 2654, 3149, 3667, 4200, 4736, 5261, 5765, 6233, 6653, 7015, 7307, 7522, 7654, 7698, 7654, 7522, 7307, 7015, 6653, 6233, 5765, 5261, 4736, 4200, 3667, 3149, 2654, 2193, 1771, 1393, 1063, 782, 548, 358, 214, 147, 
123, 179, 300, 458, 654, 889, 1165, 1481, 1834, 2220, 2633, 3067, 3513, 3960, 4400, 4821, 5212, 5564, 5866, 6111, 6291, 6401, 6438, 6401, 6291, 6111, 5866, 5564, 5212, 4821, 4400, 3960, 3513, 3067, 2633, 2220, 1834, 1481, 1165, 889, 654, 458, 300, 179, 123, 
101, 147, 247, 377, 539, 732, 959, 1219, 1510, 1828, 2169, 2526, 2893, 3262, 3624, 3970, 4293, 4582, 4831, 5033, 5181, 5271, 5302, 5271, 5181, 5033, 4831, 4582, 4293, 3970, 3624, 3262, 2893, 2526, 2169, 1828, 1510, 1219, 959, 732, 539, 377, 247, 147, 101, 
82, 119, 199, 305, 435, 592, 776, 986, 1221, 1478, 1753, 2042, 2339, 2637, 2929, 3210, 3470, 3704, 3906, 4068, 4188, 4261, 4286, 4261, 4188, 4068, 3906, 3704, 3470, 3210, 2929, 2637, 2339, 2042, 1753, 1478, 1221, 986, 776, 592, 435, 305, 199, 119, 82, 
64, 94, 158, 241, 344, 468, 613, 779, 964, 1167, 1385, 1613, 1847, 2083, 2314, 2535, 2741, 2926, 3085, 3214, 3308, 3366, 3386, 3366, 3308, 3214, 3085, 2926, 2741, 2535, 2314, 2083, 1847, 1613, 1385, 1167, 964, 779, 613, 468, 344, 241, 158, 94, 64, 
50, 72, 121, 185, 264, 359, 470, 598, 740, 896, 1063, 1238, 1418, 1599, 1776, 1946, 2104, 2246, 2368, 2467, 2540, 2584, 2599, 2584, 2540, 2467, 2368, 2246, 2104, 1946, 1776, 1599, 1418, 1238, 1063, 896, 740, 598, 470, 359, 264, 185, 121, 72, 50, 
37, 54, 90, 138, 197, 267, 350, 445, 551, 668, 792, 922, 1056, 1191, 1323, 1450, 1568, 1673, 1764, 1838, 1892, 1925, 1936, 1925, 1892, 1838, 1764, 1673, 1568, 1450, 1323, 1191, 1056, 922, 792, 668, 551, 445, 350, 267, 197, 138, 90, 54, 37, 
28, 40, 67, 103, 147, 200, 261, 332, 412, 498, 591, 688, 788, 889, 988, 1082, 1170, 1249, 1317, 1372, 1412, 1437, 1445, 1437, 1412, 1372, 1317, 1249, 1170, 1082, 988, 889, 788, 688, 591, 498, 412, 332, 261, 200, 147, 103, 67, 40, 28, 
24, 35, 58, 89, 127, 172, 226, 287, 356, 430, 511, 595, 681, 768, 853, 935, 1011, 1079, 1137, 1185, 1220, 1241, 1248, 1241, 1220, 1185, 1137, 1079, 1011, 935, 853, 768, 681, 595, 511, 430, 356, 287, 226, 172, 127, 89, 58, 35, 24, 
};