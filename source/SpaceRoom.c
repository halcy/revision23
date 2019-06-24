#include "Rasterize.h"

const init_vertex_t verticesSpaceRoom[] = {
	{ F(0), F(-0.874098), F(-0.5014296) }, 
	{ F(0), F(-1.071408), F(-0.6) }, 
	{ F(0.3223128), F(-0.874098), F(-0.384117) }, 
	{ F(0.3856728), F(-1.071408), F(-0.4596264) }, 
	{ F(0.493812), F(-0.874098), F(-0.087072) }, 
	{ F(0.5908848), F(-1.071408), F(-0.1041888) }, 
	{ F(0.4342506), F(-0.874098), F(0.2507148) }, 
	{ F(0.519615), F(-1.071408), F(0.3) }, 
	{ F(0.1714992), F(-0.874098), F(0.4711896) }, 
	{ F(0.205212), F(-1.071408), F(0.5638158) }, 
	{ F(-0.1714992), F(-0.874098), F(0.4711896) }, 
	{ F(-0.205212), F(-1.071408), F(0.5638158) }, 
	{ F(-0.4342506), F(-0.874098), F(0.2507148) }, 
	{ F(-0.519615), F(-1.071408), F(0.3) }, 
	{ F(-0.4938114), F(-0.874098), F(-0.0870726) }, 
	{ F(-0.5908848), F(-1.071408), F(-0.1041888) }, 
	{ F(-0.3223128), F(-0.874098), F(-0.384117) }, 
	{ F(-0.3856728), F(-1.071408), F(-0.4596264) }, 
	{ F(0), F(-0.874098), F(-0.6) }, 
	{ F(0.3856728), F(-0.874098), F(-0.4596264) }, 
	{ F(0.5908848), F(-0.874098), F(-0.1041888) }, 
	{ F(0.519615), F(-0.874098), F(0.3) }, 
	{ F(0.205212), F(-0.874098), F(0.5638158) }, 
	{ F(-0.205212), F(-0.874098), F(0.5638158) }, 
	{ F(-0.519615), F(-0.874098), F(0.3) }, 
	{ F(-0.5908848), F(-0.874098), F(-0.1041888) }, 
	{ F(-0.3856728), F(-0.874098), F(-0.4596264) }, 
	{ F(0), F(-0.9251388), F(-0.4296012) }, 
	{ F(0.2761422), F(-0.9251388), F(-0.3290934) }, 
	{ F(0.4230744), F(-0.9251388), F(-0.0745992) }, 
	{ F(0.3720456), F(-0.9251388), F(0.2148006) }, 
	{ F(0.1469322), F(-0.9251388), F(0.4036932) }, 
	{ F(-0.1469322), F(-0.9251388), F(0.4036932) }, 
	{ F(-0.3720456), F(-0.9251388), F(0.2148006) }, 
	{ F(-0.4230744), F(-0.9251388), F(-0.0745992) }, 
	{ F(-0.2761422), F(-0.9251388), F(-0.3290934) }, 
	{ F(0), F(1.031358), F(0.5014296) }, 
	{ F(0), F(1.2286686), F(0.6) }, 
	{ F(0.3223128), F(1.031358), F(0.384117) }, 
	{ F(0.3856728), F(1.2286686), F(0.4596264) }, 
	{ F(0.493812), F(1.031358), F(0.087072) }, 
	{ F(0.5908848), F(1.2286686), F(0.1041888) }, 
	{ F(0.4342506), F(1.031358), F(-0.2507148) }, 
	{ F(0.519615), F(1.2286686), F(-0.3) }, 
	{ F(0.1714992), F(1.031358), F(-0.4711896) }, 
	{ F(0.205212), F(1.2286686), F(-0.5638158) }, 
	{ F(-0.1714992), F(1.031358), F(-0.4711896) }, 
	{ F(-0.205212), F(1.2286686), F(-0.5638158) }, 
	{ F(-0.4342506), F(1.031358), F(-0.2507148) }, 
	{ F(-0.519615), F(1.2286686), F(-0.3) }, 
	{ F(-0.4938114), F(1.031358), F(0.087072) }, 
	{ F(-0.5908848), F(1.2286686), F(0.1041888) }, 
	{ F(-0.3223128), F(1.031358), F(0.384117) }, 
	{ F(-0.3856728), F(1.2286686), F(0.4596264) }, 
	{ F(0), F(1.031358), F(0.6) }, 
	{ F(0.3856728), F(1.031358), F(0.4596264) }, 
	{ F(0.5908848), F(1.031358), F(0.1041888) }, 
	{ F(0.519615), F(1.031358), F(-0.3) }, 
	{ F(0.205212), F(1.031358), F(-0.5638158) }, 
	{ F(-0.205212), F(1.031358), F(-0.5638158) }, 
	{ F(-0.519615), F(1.031358), F(-0.3) }, 
	{ F(-0.5908848), F(1.031358), F(0.1041888) }, 
	{ F(-0.3856728), F(1.031358), F(0.4596264) }, 
	{ F(0), F(1.0823988), F(0.4296012) }, 
	{ F(0.2761422), F(1.0823988), F(0.3290934) }, 
	{ F(0.4230744), F(1.0823988), F(0.0745992) }, 
	{ F(0.3720456), F(1.0823988), F(-0.2148006) }, 
	{ F(0.1469322), F(1.0823988), F(-0.4036932) }, 
	{ F(-0.1469322), F(1.0823988), F(-0.4036932) }, 
	{ F(-0.3720456), F(1.0823988), F(-0.2148006) }, 
	{ F(-0.4230744), F(1.0823988), F(0.0745992) }, 
	{ F(-0.2761422), F(1.0823988), F(0.3290934) }, 
	{ F(-0.1343316), F(-0.8913192), F(-4.3959258) }, 
	{ F(-0.1343316), F(1.0532448), F(-4.3959258) }, 
	{ F(4.168602), F(-0.9275838), F(-1.4648568) }, 
	{ F(4.168602), F(1.0895094), F(-1.4648568) }, 
	{ F(2.6412264), F(-1.057362), F(3.635337) }, 
	{ F(2.6412264), F(1.2192876), F(3.635337) }, 
	{ F(-2.6412276), F(-1.057362), F(3.6353364) }, 
	{ F(-2.6412276), F(1.2192876), F(3.6353364) }, 
	{ F(-4.1392632), F(-0.8913192), F(-1.486173) }, 
	{ F(-4.1392632), F(1.0532448), F(-1.486173) }, 
	{ F(0.1049928), F(-0.9275838), F(-4.417242) }, 
	{ F(0.1049928), F(1.0895094), F(-4.417242) }, 
	{ F(-4.2735942), F(1.2192876), F(-1.3885758) }, 
	{ F(-4.2735942), F(-1.057362), F(-1.3885758) }, 
	{ F(-0.297645), F(-0.8913192), F(-4.620708) }, 
	{ F(-0.297645), F(1.0532448), F(-4.620708) }, 
	{ F(-4.3025766), F(1.0532448), F(-1.7109552) }, 
	{ F(-4.3025766), F(-0.8913192), F(-1.7109552) }, 
	{ F(0), F(-1.057362), F(-4.4935236) }, 
	{ F(4.2735948), F(-1.057362), F(-1.3885752) }, 
	{ F(4.2735948), F(1.2192876), F(-1.3885752) }, 
	{ F(0), F(1.2192876), F(-4.4935236) }, 
	{ F(0.291318), F(-0.9275838), F(-4.6736964) }, 
	{ F(4.3549278), F(-0.9275838), F(-1.7213112) }, 
	{ F(4.3549278), F(1.0895094), F(-1.7213112) }, 
	{ F(0.291318), F(1.0895094), F(-4.6736964) }, 
	{ F(-3.398808), F(-1.057362), F(1.3037406) }, 
	{ F(-4.1162364), F(-1.057362), F(-0.9042768) }, 
	{ F(-4.1162364), F(1.2192876), F(-0.9042768) }, 
	{ F(-3.398808), F(1.2192876), F(1.3037406) }, 
	{ F(-4.1162364), F(0.9569244), F(-0.9042768) }, 
	{ F(-3.398808), F(0.9646206), F(1.3037406) }, 
	{ F(-3.7550628), F(-1.057362), F(1.419495) }, 
	{ F(-4.4724906), F(-1.057362), F(-0.7885224) }, 
	{ F(-4.4724906), F(0.9569244), F(-0.7885224) }, 
	{ F(-3.7550628), F(0.9646206), F(1.419495) }, 
	{ F(-3.4206576), F(-1.057362), F(1.2364962) }, 
	{ F(-4.0910652), F(-1.057362), F(-0.826809) }, 
	{ F(-4.0910652), F(1.2192876), F(-0.826809) }, 
	{ F(-3.4206576), F(1.2192876), F(1.2364962) }, 
	{ F(-3.4206576), F(0.964386), F(1.2364962) }, 
	{ F(-4.0910652), F(0.9571944), F(-0.826809) }, 
	{ F(-3.7769118), F(-1.057362), F(1.3522506) }, 
	{ F(-4.44732), F(-1.057362), F(-0.7110546) }, 
	{ F(-3.7769118), F(0.964386), F(1.3522506) }, 
	{ F(-4.44732), F(0.9571944), F(-0.7110546) }, 
	{ F(-4.1162364), F(0.8832216), F(-0.9042768) }, 
	{ F(-3.398808), F(0.8906364), F(1.3037406) }, 
	{ F(-4.4724906), F(0.8832216), F(-0.7885224) }, 
	{ F(-3.7550628), F(0.8906364), F(1.419495) }, 
	{ F(-3.7769118), F(0.8904102), F(1.3522506) }, 
	{ F(-4.44732), F(0.883482), F(-0.7110546) }, 
	{ F(-3.8759304), F(-1.057362), F(1.3844232) }, 
	{ F(-4.546338), F(-1.057362), F(-0.678882) }, 
	{ F(-3.8759304), F(0.8904102), F(1.3844232) }, 
	{ F(-4.546338), F(0.883482), F(-0.678882) }, 
	{ F(3.2483886), F(-1.0718028), F(-0.8478756) }, 
	{ F(3.2483886), F(-0.2733384), F(-0.8478756) }, 
	{ F(3.5005824), F(-1.0718028), F(-1.6054662) }, 
	{ F(3.5005824), F(-0.2733384), F(-1.6054662) }, 
	{ F(4.0059792), F(0.0899016), F(-0.5956818) }, 
	{ F(4.258173), F(-1.0718028), F(-1.3532724) }, 
	{ F(4.258173), F(-0.2733384), F(-1.3532724) }, 
	{ F(2.2201302), F(-1.0718028), F(2.627106) }, 
	{ F(2.1073884), F(-0.1605972), F(2.6271018) }, 
	{ F(2.5938288), F(0.0899016), F(3.5756712) }, 
	{ F(-2.9215944), F(-1.0718028), F(2.6268834) }, 
	{ F(-2.8088532), F(-0.1605972), F(2.6268882) }, 
	{ F(-2.5478958), F(-0.2733384), F(3.5754486) }, 
	{ F(-2.5478958), F(-1.0718028), F(3.5754486) }, 
	{ F(3.2483886), F(1.2967752), F(-0.8478756) }, 
	{ F(3.5005824), F(1.2967752), F(-1.6054662) }, 
	{ F(4.258173), F(1.2967752), F(-1.3532724) }, 
	{ F(4.0059792), F(1.2967752), F(-0.5956818) }, 
	{ F(2.5938288), F(1.1922534), F(3.5756712) }, 
	{ F(2.1073884), F(1.0795122), F(2.6271018) }, 
	{ F(-2.5478958), F(1.1922534), F(3.5754486) }, 
	{ F(-2.8088532), F(1.0795122), F(2.6268882) }, 
	{ F(-2.9215944), F(-0.2733384), F(2.6268834) }, 
	{ F(2.2201302), F(-0.2733384), F(2.627106) }, 
	{ F(-2.9215944), F(1.1922534), F(2.6268834) }, 
	{ F(2.2201302), F(1.1922534), F(2.627106) }, 
	{ F(-2.6535768), F(-0.121428), F(2.7055104) }, 
	{ F(1.9521054), F(-0.121428), F(2.7057102) }, 
	{ F(-2.6535768), F(1.040343), F(2.7055104) }, 
	{ F(1.9521054), F(1.040343), F(2.7057102) }, 
};

const init_vertex_t normalsSpaceRoom[] = {
	{ F(0.342020531956806), F(0), F(-0.939692479335651) }, 
	{ F(0.866025397496536), F(0), F(-0.500000010890967) }, 
	{ F(0.984807582486792), F(0), F(0.173649144761847) }, 
	{ F(0.642788122496614), F(-1.2811907562035e-16), F(0.766044012819941) }, 
	{ F(0), F(0), F(1) }, 
	{ F(-0.642788122496614), F(1.2811907562035e-16), F(0.766044012819941) }, 
	{ F(-0.984807582486792), F(0), F(0.173649144761847) }, 
	{ F(0), F(-1), F(0) }, 
	{ F(-0.866025397496536), F(0), F(-0.500000010890967) }, 
	{ F(-0.342020531956806), F(0), F(-0.939692479335651) }, 
	{ F(-0.387703934158649), F(0.79762027112316), F(-0.462047143191389) }, 
	{ F(0), F(1), F(0) }, 
	{ F(-0.206293156909905), F(0.797620733278752), F(0.56678417343466) }, 
	{ F(0.522350783682028), F(0.797621221664909), F(0.301579252496834) }, 
	{ F(1.38813966345826e-17), F(0.797619895303702), F(-0.603160428589038) }, 
	{ F(-0.522350513142316), F(0.797621289287514), F(0.301579542236013) }, 
	{ F(0.206293207997966), F(0.797620620324565), F(0.566784313797554) }, 
	{ F(0.38770354269568), F(0.79762073165421), F(-0.462046676664406) }, 
	{ F(-0.593996727761933), F(0.797620045998277), F(-0.104738482086688) }, 
	{ F(0.593997218739203), F(0.797619831971403), F(-0.10473732751986) }, 
	{ F(0.342020531956806), F(1.28118831290456e-16), F(0.939692479335651) }, 
	{ F(0.866025397496536), F(0), F(0.500000010890967) }, 
	{ F(0.984807582486792), F(6.40593715036337e-17), F(-0.173649144761847) }, 
	{ F(0.642788122496614), F(-1.2811875916306e-16), F(-0.766044012819941) }, 
	{ F(0), F(0), F(-1) }, 
	{ F(-0.642788122496614), F(1.2811875916306e-16), F(-0.766044012819941) }, 
	{ F(-0.984807582486792), F(-6.40593715036337e-17), F(-0.173649144761847) }, 
	{ F(-0.866025397496536), F(0), F(0.500000010890967) }, 
	{ F(-0.342020531956806), F(-1.28118831290456e-16), F(0.939692479335651) }, 
	{ F(-0.38770354269568), F(-0.797620731654209), F(0.462046676664407) }, 
	{ F(-0.206293156909906), F(-0.797620733278752), F(-0.566784173434661) }, 
	{ F(0.522352249067743), F(-0.797620172438625), F(-0.301579489376927) }, 
	{ F(-2.77627932691651e-17), F(-0.797619895303701), F(0.603160428589039) }, 
	{ F(-0.522349417114591), F(-0.797622246316493), F(-0.301578909443413) }, 
	{ F(0.206293207997967), F(-0.797620620324564), F(-0.566784313797555) }, 
	{ F(0.387703934158649), F(-0.797620271123159), F(0.462047143191389) }, 
	{ F(-0.59399342743158), F(-0.79762258019777), F(0.104737900144776) }, 
	{ F(0.593997145143816), F(-0.797619864053222), F(0.104737500584634) }, 
	{ F(0.642788122496614), F(0), F(0.766044012819941) }, 
	{ F(-0.642788122496614), F(0), F(0.766044012819941) }, 
	{ F(-0.387703341540782), F(0.797620770153547), F(-0.462046778992965) }, 
	{ F(-0.206293161593847), F(0.797620610881643), F(0.566784343976092) }, 
	{ F(0.52235063521556), F(0.797621382179419), F(0.301579085117145) }, 
	{ F(0), F(0.797619895303702), F(-0.603160428589038) }, 
	{ F(-0.522349553943061), F(0.797622326323744), F(0.301578460844579) }, 
	{ F(0.206293101963944), F(0.797620742721622), F(0.566784180144702) }, 
	{ F(0.38770379845463), F(0.797620232623506), F(-0.462047323521602) }, 
	{ F(-0.5939933616243), F(0.797622792052695), F(-0.104736659982675) }, 
	{ F(0.593997253189936), F(0.797619803866776), F(-0.104737346168099) }, 
	{ F(0.342020531956806), F(0), F(0.939692479335651) }, 
	{ F(0.984807582486792), F(0), F(-0.173649144761847) }, 
	{ F(0.642788122496614), F(0), F(-0.766044012819941) }, 
	{ F(-0.642788122496614), F(0), F(-0.766044012819941) }, 
	{ F(-0.984807582486792), F(0), F(-0.173649144761847) }, 
	{ F(-0.342020531956806), F(0), F(0.939692479335651) }, 
	{ F(-0.387703798454631), F(-0.797620232623505), F(0.462047323521603) }, 
	{ F(-0.206293161593847), F(-0.797620610881643), F(-0.566784343976093) }, 
	{ F(0.522350833225027), F(-0.797621209281399), F(-0.30157919943789) }, 
	{ F(0), F(-0.797619895303701), F(0.603160428589039) }, 
	{ F(-0.522350833225027), F(-0.797621209281399), F(-0.30157919943789) }, 
	{ F(0.206293101963944), F(-0.797620742721621), F(-0.566784180144703) }, 
	{ F(0.387703341540782), F(-0.797620770153547), F(0.462046778992966) }, 
	{ F(-0.593997213765242), F(-0.797619834139661), F(0.104737339216488) }, 
	{ F(0.593996669858471), F(-0.797620251786884), F(0.104737243311412) }, 
	{ F(-0.951056495483244), F(1.40254148116266e-16), F(-0.309017058427412) }, 
	{ F(1.13583573004319e-07), F(0), F(-0.999999999999994) }, 
	{ F(0.951056795611099), F(0), F(-0.309016134727538) }, 
	{ F(0.587785960810882), F(0), F(0.809016479605718) }, 
	{ F(0.587785314062791), F(0), F(0.809016949496181) }, 
	{ F(0.587785208773602), F(-9.29570812004545e-07), F(0.809017025992722) }, 
	{ F(0.587785208773851), F(-1.30143853718299e-07), F(0.809017025993065) }, 
	{ F(0.809017726612586), F(0), F(-0.587784244452506) }, 
	{ F(-0.809017726612586), F(0), F(0.587784244452506) }, 
	{ F(-0.587785291254231), F(-8.85579038683157e-07), F(0.809016966067088) }, 
	{ F(-0.587784574805535), F(0), F(0.809017486597587) }, 
	{ F(-0.80901583642937), F(0), F(-0.587786846064529) }, 
	{ F(0.809016736496766), F(0), F(0.587785607231176) }, 
	{ F(0.951056636062705), F(0), F(-0.309016625768085) }, 
	{ F(0.309017944680873), F(0), F(0.951056207521516) }, 
	{ F(0.951057288575871), F(0), F(-0.309014617529191) }, 
	{ F(0.951055123734389), F(0), F(-0.309021280203429) }, 
	{ F(-0.309017473934807), F(0), F(-0.951056360476576) }, 
	{ F(0.00102531765985818), F(-0.999994495464517), F(0.00315559255335994) }, 
	{ F(0.00102430559493317), F(-0.999994506325957), F(0.00315247774839176) }, 
	{ F(0.00102435168025132), F(-0.999994505814865), F(0.003152624893547) }, 
	{ F(0.951054147096311), F(0), F(-0.309024285924116) }, 
	{ F(0.951056638054961), F(0), F(-0.30901661963654) }, 
	{ F(0.951056641082084), F(0), F(-0.309016610320002) }, 
	{ F(0.951056556775182), F(0), F(-0.309016869790203) }, 
	{ F(-0.309012707589983), F(0), F(-0.951057909145341) }, 
	{ F(0.309014401252927), F(0), F(0.951057358847664) }, 
	{ F(0.000986824203393862), F(-0.999994900903188), F(0.0030371607818968) }, 
	{ F(-0.951056495483244), F(0), F(-0.309017058427412) }, 
	{ F(1.13583573004319e-07), F(0), F(-0.999999999999993) }, 
	{ F(0.587785960810882), F(-9.12548176731804e-18), F(0.809016479605718) }, 
	{ F(0.58778531406279), F(0), F(0.809016949496181) }, 
	{ F(0.587785235722131), F(9.68340618027268e-08), F(0.809017006413999) }, 
	{ F(0.587785235721898), F(8.9626085126727e-07), F(0.809017006413678) }, 
	{ F(-0.587785256051145), F(8.42065619880409e-07), F(0.809016991643674) }, 
	{ F(-0.587785256051145), F(8.42065619727208e-07), F(0.809016991643674) }, 
	{ F(-0.587784574805535), F(4.63529315762741e-18), F(0.809017486597587) }, 
	{ F(-0.80901583642937), F(1.40481164068637e-17), F(-0.587786846064529) }, 
	{ F(0.809016736496766), F(1.40481160301651e-17), F(0.587785607231177) }, 
	{ F(0.951057288575871), F(-4.13024778525615e-17), F(-0.309014617529191) }, 
	{ F(0.951055123734389), F(1.45176742740976e-17), F(-0.309021280203429) }, 
	{ F(0.00102531878660241), F(-0.999994495435648), F(0.00315560133573569) }, 
	{ F(0.00102430636609256), F(-0.999994506300947), F(0.00315248543114588) }, 
	{ F(0.00102435315316899), F(-0.999994505815804), F(0.00315262411709359) }, 
	{ F(0.951054147096311), F(1.43895512832522e-17), F(-0.309024285924115) }, 
	{ F(0.951057288575871), F(-1.73625094873414e-18), F(-0.309014617529191) }, 
	{ F(0.309017944680873), F(-7.06698327233371e-18), F(0.951056207521516) }, 
	{ F(0.951056638054961), F(4.16286484284657e-17), F(-0.30901661963654) }, 
	{ F(0.000986818879094348), F(-0.999994900902316), F(0.00303716279882544) }, 
	{ F(-0.948809614901255), F(0), F(-0.315848562876156) }, 
	{ F(0.315848562876155), F(0), F(-0.948809614901255) }, 
	{ F(-0.457696908655371), F(0.87550276858439), F(-0.154946577917632) }, 
	{ F(4.3292867103695e-05), F(0), F(-0.999999999062864) }, 
	{ F(-0.958900705496022), F(0), F(-0.283741849220787) }, 
	{ F(-0.930401234609653), F(0), F(0.366542688696464) }, 
	{ F(-0.930401234609654), F(0), F(0.366542688696464) }, 
	{ F(-0.315848562876155), F(0), F(0.948809614901255) }, 
	{ F(0.930401234609653), F(0), F(-0.366542688696464) }, 
	{ F(1.9345903699122e-05), F(-0.895057189576985), F(-0.445951372923422) }, 
	{ F(4.34478240040776e-05), F(-8.72439001915875e-07), F(-0.999999999055763) }, 
	{ F(4.34478240032605e-05), F(-6.19459335363998e-06), F(-0.999999999036957) }, 
	{ F(4.25753850037753e-05), F(0), F(-0.999999999093668) }, 
	{ F(3.72532636266209e-05), F(0), F(-0.999999999306097) }, 
	{ F(4.33811954745117e-05), F(0), F(-0.999999999059036) }, 
	{ F(0.451730804827992), F(0), F(-0.892154291571505) }, 
	{ F(1.93756794166938e-05), F(0.895056471328253), F(-0.445952814497228) }, 
	{ F(-0.45165241097208), F(0), F(-0.892193980961039) }, 
	{ F(0.315848562876155), F(-3.9252308879696e-17), F(-0.948809614901255) }, 
	{ F(-0.397255621007517), F(0.910148421353929), F(-0.117549235152266) }, 
	{ F(4.3292867103695e-05), F(-4.4158873051071e-20), F(-0.999999999062864) }, 
	{ F(0.930401234609653), F(-3.01871883810754e-17), F(-0.366542688696464) }, 
	{ F(1.93756794166938e-05), F(-0.895056471328254), F(-0.445952814497227) }, 
	{ F(4.32928671029054e-05), F(6.03963562833068e-06), F(-0.999999999044625) }, 
	{ F(4.32928671036839e-05), F(7.17482101231077e-07), F(-0.999999999062606) }, 
	{ F(1.93459036991202e-05), F(0.895057189576985), F(-0.445951372923423) }, 
	{ F(-0.45165241097208), F(7.42904908222527e-18), F(-0.892193980961039) }, 
};

const index_triangle_t facesSpaceRoom[] = {
	{19, 1, 18, 0},
	{20, 3, 19, 1},
	{21, 5, 20, 2},
	{22, 7, 21, 3},
	{23, 9, 22, 4},
	{24, 11, 23, 5},
	{25, 13, 24, 6},
	{5, 13, 17, 7},
	{26, 15, 25, 8},
	{18, 17, 26, 9},
	{30, 8, 6, 10},
	{19, 0, 2, 11},
	{20, 2, 4, 11},
	{21, 4, 6, 11},
	{22, 6, 8, 11},
	{23, 8, 10, 11},
	{24, 10, 12, 11},
	{25, 12, 14, 11},
	{16, 25, 14, 11},
	{18, 16, 0, 11},
	{28, 35, 31, 11},
	{27, 2, 0, 12},
	{14, 35, 16, 13},
	{31, 10, 8, 14},
	{28, 4, 2, 15},
	{35, 0, 16, 16},
	{32, 12, 10, 17},
	{4, 30, 6, 18},
	{33, 14, 12, 19},
	{55, 37, 54, 20},
	{56, 39, 55, 21},
	{57, 41, 56, 22},
	{58, 43, 57, 23},
	{59, 45, 58, 24},
	{60, 47, 59, 25},
	{61, 49, 60, 26},
	{41, 49, 53, 11},
	{62, 51, 61, 27},
	{54, 53, 62, 28},
	{42, 67, 44, 29},
	{55, 36, 38, 7},
	{56, 38, 40, 7},
	{57, 40, 42, 7},
	{58, 42, 44, 7},
	{59, 44, 46, 7},
	{48, 59, 46, 7},
	{50, 60, 48, 7},
	{52, 61, 50, 7},
	{54, 52, 36, 7},
	{71, 69, 67, 7},
	{63, 38, 36, 30},
	{70, 52, 50, 31},
	{67, 46, 44, 32},
	{38, 65, 40, 33},
	{71, 36, 52, 34},
	{46, 69, 48, 35},
	{65, 42, 40, 36},
	{69, 50, 48, 37},
	{19, 3, 1, 0},
	{20, 5, 3, 1},
	{21, 7, 5, 2},
	{22, 9, 7, 38},
	{23, 11, 9, 4},
	{24, 13, 11, 39},
	{25, 15, 13, 6},
	{1, 3, 17, 7},
	{3, 5, 17, 7},
	{5, 7, 9, 7},
	{9, 11, 5, 7},
	{11, 13, 5, 7},
	{13, 15, 17, 7},
	{26, 17, 15, 8},
	{18, 1, 17, 9},
	{30, 31, 8, 40},
	{19, 18, 0, 11},
	{20, 19, 2, 11},
	{21, 20, 4, 11},
	{22, 21, 6, 11},
	{23, 22, 8, 11},
	{24, 23, 10, 11},
	{25, 24, 12, 11},
	{16, 26, 25, 11},
	{18, 26, 16, 11},
	{28, 27, 35, 11},
	{35, 34, 31, 11},
	{34, 33, 31, 11},
	{33, 32, 31, 11},
	{31, 30, 29, 11},
	{29, 28, 31, 11},
	{27, 28, 2, 41},
	{14, 34, 35, 42},
	{31, 32, 10, 43},
	{28, 29, 4, 44},
	{35, 27, 0, 45},
	{32, 33, 12, 46},
	{4, 29, 30, 47},
	{33, 34, 14, 48},
	{55, 39, 37, 49},
	{56, 41, 39, 21},
	{57, 43, 41, 50},
	{58, 45, 43, 51},
	{59, 47, 45, 24},
	{60, 49, 47, 52},
	{61, 51, 49, 53},
	{37, 39, 53, 11},
	{39, 41, 53, 11},
	{41, 43, 45, 11},
	{45, 47, 41, 11},
	{47, 49, 41, 11},
	{49, 51, 53, 11},
	{62, 53, 51, 27},
	{54, 37, 53, 54},
	{42, 66, 67, 55},
	{55, 54, 36, 7},
	{56, 55, 38, 7},
	{57, 56, 40, 7},
	{58, 57, 42, 7},
	{59, 58, 44, 7},
	{48, 60, 59, 7},
	{50, 61, 60, 7},
	{52, 62, 61, 7},
	{54, 62, 52, 7},
	{64, 63, 71, 7},
	{71, 70, 69, 7},
	{69, 68, 67, 7},
	{67, 66, 65, 7},
	{65, 64, 67, 7},
	{64, 71, 67, 7},
	{63, 64, 38, 56},
	{70, 71, 52, 57},
	{67, 68, 46, 58},
	{38, 64, 65, 59},
	{71, 63, 36, 60},
	{46, 68, 69, 61},
	{65, 66, 42, 62},
	{69, 70, 50, 63},
	{74, 94, 82, 11},
	{76, 92, 91, 64},
	{78, 77, 76, 65},
	{110, 100, 93, 7},
	{102, 118, 84, 66},
	{73, 88, 87, 7},
	{90, 109, 108, 11},
	{72, 93, 73, 67},
	{81, 85, 80, 68},
	{80, 90, 72, 69},
	{73, 84, 81, 70},
	{80, 88, 81, 71},
	{80, 86, 89, 11},
	{73, 86, 72, 72},
	{82, 91, 74, 73},
	{75, 93, 83, 73},
	{83, 90, 82, 74},
	{74, 92, 75, 74},
	{75, 95, 74, 75},
	{83, 96, 75, 7},
	{82, 97, 83, 76},
	{103, 101, 79, 77},
	{102, 120, 118, 78},
	{123, 106, 117, 79},
	{113, 100, 110, 80},
	{98, 121, 119, 81},
	{109, 105, 115, 11},
	{103, 116, 112, 82},
	{113, 106, 102, 83},
	{112, 117, 113, 84},
	{108, 104, 98, 11},
	{108, 115, 114, 11},
	{103, 111, 101, 85},
	{112, 110, 111, 86},
	{121, 116, 107, 87},
	{122, 117, 116, 88},
	{114, 126, 122, 89},
	{104, 122, 121, 87},
	{119, 107, 103, 81},
	{115, 120, 123, 79},
	{118, 105, 99, 78},
	{124, 127, 126, 86},
	{115, 124, 114, 11},
	{123, 125, 115, 90},
	{122, 127, 123, 91},
	{74, 95, 94, 11},
	{76, 77, 92, 92},
	{78, 79, 77, 93},
	{93, 92, 111, 7},
	{92, 77, 101, 7},
	{77, 79, 101, 7},
	{101, 111, 92, 7},
	{111, 110, 93, 7},
	{100, 84, 93, 7},
	{118, 99, 85, 66},
	{85, 84, 118, 66},
	{84, 100, 102, 66},
	{73, 81, 88, 7},
	{91, 90, 108, 11},
	{90, 85, 99, 11},
	{90, 99, 109, 11},
	{78, 76, 98, 11},
	{76, 91, 98, 11},
	{108, 98, 91, 11},
	{72, 90, 93, 94},
	{81, 84, 85, 95},
	{80, 85, 90, 96},
	{73, 93, 84, 97},
	{80, 89, 88, 71},
	{80, 72, 86, 11},
	{73, 87, 86, 72},
	{82, 90, 91, 98},
	{75, 92, 93, 99},
	{83, 93, 90, 100},
	{74, 91, 92, 74},
	{75, 96, 95, 101},
	{83, 97, 96, 7},
	{82, 94, 97, 102},
	{79, 78, 119, 77},
	{78, 98, 119, 77},
	{119, 103, 79, 77},
	{102, 106, 120, 78},
	{123, 120, 106, 103},
	{113, 102, 100, 104},
	{98, 104, 121, 81},
	{109, 99, 105, 11},
	{103, 107, 116, 105},
	{113, 117, 106, 106},
	{112, 116, 117, 107},
	{108, 114, 104, 11},
	{108, 109, 115, 11},
	{103, 112, 111, 108},
	{112, 113, 110, 86},
	{121, 122, 116, 87},
	{122, 123, 117, 88},
	{114, 124, 126, 89},
	{104, 114, 122, 87},
	{119, 121, 107, 81},
	{115, 105, 120, 109},
	{118, 120, 105, 110},
	{124, 125, 127, 111},
	{115, 125, 124, 11},
	{123, 127, 125, 90},
	{122, 126, 127, 112},
	{129, 130, 128, 113},
	{131, 133, 130, 114},
	{132, 151, 137, 115},
	{135, 150, 151, 116},
	{128, 151, 129, 117},
	{140, 138, 141, 118},
	{140, 152, 150, 119},
	{143, 145, 144, 11},
	{129, 143, 131, 113},
	{132, 142, 129, 120},
	{131, 144, 134, 114},
	{153, 148, 146, 11},
	{137, 153, 146, 121},
	{149, 157, 156, 122},
	{136, 150, 139, 123},
	{149, 153, 147, 124},
	{139, 152, 149, 125},
	{147, 151, 136, 126},
	{154, 157, 155, 127},
	{149, 154, 139, 128},
	{139, 155, 136, 129},
	{136, 157, 147, 130},
	{129, 131, 130, 113},
	{131, 134, 133, 131},
	{132, 129, 151, 132},
	{135, 138, 150, 133},
	{128, 135, 151, 117},
	{140, 150, 138, 118},
	{140, 148, 152, 119},
	{143, 142, 145, 11},
	{129, 142, 143, 113},
	{132, 145, 142, 120},
	{131, 143, 144, 114},
	{153, 152, 148, 11},
	{137, 151, 153, 134},
	{149, 147, 157, 135},
	{136, 151, 150, 136},
	{149, 152, 153, 137},
	{139, 150, 152, 125},
	{147, 153, 151, 126},
	{154, 156, 157, 127},
	{149, 156, 154, 128},
	{139, 154, 155, 138},
	{136, 155, 157, 139},
};
const vec2_t texcoordsSpaceRoom[] = {
	{ F(0.042154), F(0.130000) }, 
	{ F(0.000000), F(1.000000) }, 
	{ F(0.444444), F(1.000000) }, 
	{ F(0.404269), F(0.433851) }, 
	{ F(0.947525), F(0.284829) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.457846), F(0.130000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.332085), F(0.024474) }, 
	{ F(0.333333), F(1.000000) }, 
	{ F(0.167915), F(0.024474) }, 
	{ F(0.095731), F(0.433851) }, 
	{ F(0.042154), F(0.130000) }, 
	{ F(0.222222), F(1.000000) }, 
	{ F(0.666667), F(1.000000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.444444), F(0.500000) }, 
	{ F(0.750000), F(0.490000) }, 
	{ F(0.904269), F(0.433851) }, 
	{ F(0.986354), F(0.291676) }, 
	{ F(0.957846), F(0.130000) }, 
	{ F(0.832085), F(0.024474) }, 
	{ F(0.667915), F(0.024474) }, 
	{ F(0.542154), F(0.130000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.595731), F(0.433851) }, 
	{ F(0.750000), F(0.450572) }, 
	{ F(0.878925), F(0.403647) }, 
	{ F(0.947525), F(0.284829) }, 
	{ F(0.111111), F(0.500000) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.681400), F(0.061524) }, 
	{ F(0.576300), F(0.149714) }, 
	{ F(0.552475), F(0.284829) }, 
	{ F(0.621075), F(0.403647) }, 
	{ F(0.542154), F(0.130000) }, 
	{ F(0.000000), F(1.000000) }, 
	{ F(0.878925), F(0.403647) }, 
	{ F(0.404269), F(0.433851) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.513646), F(0.291676) }, 
	{ F(0.457846), F(0.130000) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.332085), F(0.024474) }, 
	{ F(0.681400), F(0.061524) }, 
	{ F(0.167915), F(0.024474) }, 
	{ F(0.576300), F(0.149714) }, 
	{ F(0.042154), F(0.130000) }, 
	{ F(0.552475), F(0.284829) }, 
	{ F(0.878925), F(0.403647) }, 
	{ F(0.832085), F(0.024474) }, 
	{ F(0.986354), F(0.291676) }, 
	{ F(0.750000), F(0.490000) }, 
	{ F(0.904269), F(0.433851) }, 
	{ F(0.986354), F(0.291676) }, 
	{ F(0.957846), F(0.130000) }, 
	{ F(0.832085), F(0.024474) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.595731), F(0.433851) }, 
	{ F(0.750000), F(0.450572) }, 
	{ F(0.878925), F(0.403647) }, 
	{ F(0.947525), F(0.284829) }, 
	{ F(0.923700), F(0.149714) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.681400), F(0.061524) }, 
	{ F(0.576300), F(0.149714) }, 
	{ F(0.552475), F(0.284829) }, 
	{ F(0.621075), F(0.403647) }, 
	{ F(0.006287), F(0.536466) }, 
	{ F(0.006287), F(0.963534) }, 
	{ F(0.804914), F(0.528502) }, 
	{ F(0.804914), F(0.971498) }, 
	{ F(0.891068), F(0.055836) }, 
	{ F(0.391068), F(0.055836) }, 
	{ F(0.400000), F(0.500000) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.193713), F(0.536466) }, 
	{ F(0.193713), F(0.963534) }, 
	{ F(0.995086), F(0.528502) }, 
	{ F(0.995086), F(0.971498) }, 
	{ F(0.750000), F(0.450572) }, 
	{ F(0.200000), F(0.500000) }, 
	{ F(0.576300), F(0.149714) }, 
	{ F(0.006287), F(0.963534) }, 
	{ F(0.681400), F(0.061524) }, 
	{ F(0.193713), F(0.536466) }, 
	{ F(0.888889), F(0.500000) }, 
	{ F(0.800000), F(0.500000) }, 
	{ F(0.888889), F(0.500000) }, 
	{ F(1.000000), F(1.000000) }, 
	{ F(0.995086), F(0.528502) }, 
	{ F(1.000000), F(1.000000) }, 
	{ F(0.621075), F(0.403647) }, 
	{ F(1.000000), F(0.500000) }, 
	{ F(0.307180), F(0.500000) }, 
	{ F(0.530151), F(0.298298) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.068469), F(0.180367) }, 
	{ F(0.219280), F(0.942380) }, 
	{ F(0.307180), F(0.944070) }, 
	{ F(0.307180), F(0.500000) }, 
	{ F(0.777778), F(0.500000) }, 
	{ F(0.777778), F(1.000000) }, 
	{ F(0.888889), F(1.000000) }, 
	{ F(0.567302), F(0.183958) }, 
	{ F(0.531495), F(0.294160) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.304503), F(0.944018) }, 
	{ F(0.222364), F(0.942439) }, 
	{ F(0.304503), F(0.500000) }, 
	{ F(0.531495), F(0.294160) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.818600), F(0.061524) }, 
	{ F(0.219280), F(0.926193) }, 
	{ F(0.307180), F(0.927821) }, 
	{ F(0.219280), F(0.926193) }, 
	{ F(0.307180), F(0.927821) }, 
	{ F(0.304503), F(0.927772) }, 
	{ F(0.222364), F(0.926250) }, 
	{ F(0.621075), F(0.403647) }, 
	{ F(0.777778), F(0.500000) }, 
	{ F(0.304503), F(0.927772) }, 
	{ F(0.555556), F(0.500000) }, 
	{ F(0.375000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.666667), F(1.000000) }, 
	{ F(0.625000), F(0.250000) }, 
	{ F(0.625000), F(0.750000) }, 
	{ F(0.444444), F(0.500000) }, 
	{ F(0.625000), F(0.500000) }, 
	{ F(0.375000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.750000) }, 
	{ F(0.222222), F(0.500000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.750000) }, 
	{ F(0.222222), F(0.500000) }, 
	{ F(0.486354), F(0.291676) }, 
	{ F(0.625000), F(0.250000) }, 
	{ F(0.444444), F(0.500000) }, 
	{ F(0.625000), F(0.750000) }, 
	{ F(0.042154), F(0.130000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.333333), F(1.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.333333), F(0.500000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.625000), F(0.000000) }, 
	{ F(0.923700), F(0.149714) }, 
};
