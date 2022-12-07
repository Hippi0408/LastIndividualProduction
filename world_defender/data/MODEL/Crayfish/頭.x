xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 250;
 0.16064;-0.14951;-0.09047;,
 46.28432;45.97428;-0.09047;,
 0.16064;65.07927;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 65.38941;-0.14951;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 46.28432;-46.27321;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 0.16064;-65.37825;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 -45.96308;-46.27321;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 -65.06810;-0.14951;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 -45.96308;45.97428;-0.09047;,
 0.16064;-0.14951;-0.09047;,
 0.16064;65.07927;-0.09047;,
 0.16064;21.51237;-534.11339;,
 0.16064;67.39667;-429.61631;,
 47.92299;47.61292;-429.61631;,
 0.16064;21.51237;-534.11339;,
 51.50193;-0.14951;-429.61631;,
 0.16064;21.51237;-534.11339;,
 30.49768;-21.66191;-429.61631;,
 0.16064;21.51237;-534.11339;,
 0.16064;-34.22800;-429.61641;,
 0.16064;21.51237;-534.11339;,
 -30.17637;-21.66191;-429.61631;,
 0.16064;21.51237;-534.11339;,
 -51.18061;-0.14951;-429.61631;,
 0.16064;21.51237;-534.11339;,
 -47.60174;47.61292;-429.61631;,
 0.16064;21.51237;-534.11339;,
 0.16064;67.39667;-429.61631;,
 67.54279;67.23270;-49.53047;,
 0.16064;95.14332;-50.10317;,
 95.45339;-0.14951;-49.08998;,
 67.54279;-67.53169;-49.04008;,
 0.16064;-95.44220;-49.40947;,
 -67.22153;-67.53169;-49.98179;,
 -95.13215;-0.14951;-50.42201;,
 -67.22153;67.23270;-50.47230;,
 0.16064;95.14332;-50.10317;,
 67.54279;67.23270;-184.47171;,
 0.16064;95.14332;-185.52830;,
 95.45339;-0.14951;-183.30559;,
 67.54279;-67.53169;-182.71282;,
 0.16064;-95.44220;-183.04104;,
 -67.22153;-67.53169;-184.09766;,
 -95.13215;-0.14951;-185.26345;,
 -67.22153;67.23270;-185.85618;,
 0.16064;95.14332;-185.52830;,
 47.44930;49.44124;-431.17921;,
 55.73041;46.87908;-435.96036;,
 47.44930;46.87908;-440.74141;,
 47.44930;49.44124;-431.17921;,
 55.73041;46.87908;-426.39796;,
 47.44930;49.44124;-431.17921;,
 47.44930;46.87908;-421.61661;,
 47.44930;49.44124;-431.17921;,
 39.16824;46.87908;-426.39796;,
 47.44930;49.44124;-431.17921;,
 39.16824;46.87908;-435.96036;,
 47.44930;49.44124;-431.17921;,
 47.44930;46.87908;-440.74141;,
 61.79269;39.87926;-439.46016;,
 47.44930;39.87926;-447.74122;,
 61.79269;39.87926;-422.89776;,
 47.44930;39.87926;-414.61680;,
 33.10603;39.87926;-422.89776;,
 33.10603;39.87926;-439.46016;,
 47.44930;39.87926;-447.74122;,
 64.01143;30.31689;-440.74141;,
 47.44930;30.31689;-450.30323;,
 64.01143;30.31689;-421.61661;,
 47.44930;30.31689;-412.05469;,
 30.88711;30.31689;-421.61661;,
 30.88711;30.31689;-440.74141;,
 47.44930;30.31689;-450.30323;,
 61.79269;20.75475;-439.46016;,
 47.44930;20.75475;-447.74122;,
 61.79269;20.75475;-422.89776;,
 47.44930;20.75475;-414.61680;,
 33.10603;20.75475;-422.89776;,
 33.10603;20.75475;-439.46016;,
 47.44930;20.75475;-447.74122;,
 55.73041;13.75474;-435.96036;,
 47.44930;13.75474;-440.74141;,
 55.73041;13.75474;-426.39796;,
 47.44930;13.75474;-421.61661;,
 39.16824;13.75474;-426.39796;,
 39.16824;13.75474;-435.96036;,
 47.44930;13.75474;-440.74141;,
 47.44930;11.19255;-431.17921;,
 47.44930;11.19255;-431.17921;,
 47.44930;11.19255;-431.17921;,
 47.44930;11.19255;-431.17921;,
 47.44930;11.19255;-431.17921;,
 47.44930;11.19255;-431.17921;,
 -46.77353;49.44124;-431.17921;,
 -38.49251;46.87908;-435.96036;,
 -46.77353;46.87908;-440.74141;,
 -46.77353;49.44124;-431.17921;,
 -38.49251;46.87908;-426.39796;,
 -46.77353;49.44124;-431.17921;,
 -46.77353;46.87908;-421.61661;,
 -46.77353;49.44124;-431.17921;,
 -55.05463;46.87908;-426.39796;,
 -46.77353;49.44124;-431.17921;,
 -55.05463;46.87908;-435.96036;,
 -46.77353;49.44124;-431.17921;,
 -46.77353;46.87908;-440.74141;,
 -32.43026;39.87926;-439.46016;,
 -46.77353;39.87926;-447.74122;,
 -32.43026;39.87926;-422.89776;,
 -46.77362;39.87926;-414.61680;,
 -61.11688;39.87926;-422.89776;,
 -61.11688;39.87926;-439.46016;,
 -46.77353;39.87926;-447.74122;,
 -30.21144;30.31689;-440.74141;,
 -46.77353;30.31689;-450.30323;,
 -30.21144;30.31689;-421.61661;,
 -46.77362;30.31689;-412.05469;,
 -63.33579;30.31689;-421.61661;,
 -63.33579;30.31689;-440.74141;,
 -46.77353;30.31689;-450.30323;,
 -32.43026;20.75475;-439.46016;,
 -46.77353;20.75475;-447.74122;,
 -32.43026;20.75475;-422.89776;,
 -46.77362;20.75475;-414.61680;,
 -61.11688;20.75475;-422.89776;,
 -61.11688;20.75475;-439.46016;,
 -46.77353;20.75475;-447.74122;,
 -38.49251;13.75474;-435.96036;,
 -46.77353;13.75474;-440.74141;,
 -38.49251;13.75474;-426.39796;,
 -46.77353;13.75474;-421.61661;,
 -55.05463;13.75474;-426.39796;,
 -55.05463;13.75474;-435.96036;,
 -46.77353;13.75474;-440.74141;,
 -46.77353;11.19255;-431.17921;,
 -46.77353;11.19255;-431.17921;,
 -46.77353;11.19255;-431.17921;,
 -46.77353;11.19255;-431.17921;,
 -46.77353;11.19255;-431.17921;,
 -46.77353;11.19255;-431.17921;,
 -165.18990;189.17222;336.87718;,
 -157.48972;190.44329;337.63968;,
 -138.82412;171.77810;-26.31276;,
 -146.52493;170.50716;-27.07257;,
 -154.00218;183.52891;338.86956;,
 -135.33667;164.86341;-25.08195;,
 -159.54698;177.98389;338.86956;,
 -140.88147;159.31865;-25.08195;,
 -166.46133;181.47156;337.63968;,
 -147.79607;162.80598;-26.31276;,
 -165.18990;189.17222;336.87718;,
 -146.52493;170.50716;-27.07257;,
 -90.04227;122.99614;-441.64659;,
 -97.74281;121.72476;-442.40753;,
 -86.55482;116.08152;-440.41612;,
 -92.09978;110.53679;-440.41612;,
 -99.01411;114.02422;-441.64659;,
 -97.74281;121.72476;-442.40753;,
 -72.37194;105.32571;-495.74971;,
 -79.33645;103.31834;-498.74366;,
 -70.07554;99.60241;-490.90694;,
 -75.62039;94.05763;-490.90694;,
 -81.34371;96.35400;-495.74971;,
 -79.33645;103.31834;-498.74366;,
 -50.92660;83.88045;-531.14298;,
 -56.22838;80.21035;-535.60557;,
 -51.31964;80.84663;-523.92266;,
 -56.86456;75.30181;-523.92266;,
 -59.89837;74.90860;-531.14298;,
 -56.22838;80.21035;-535.60557;,
 -27.56413;60.51799;-531.24932;,
 -30.69878;54.68079;-535.44337;,
 -31.46458;60.99144;-524.46270;,
 -37.00945;55.44666;-524.46270;,
 -36.53593;51.54622;-531.24932;,
 -30.69878;54.68079;-535.44337;,
 3.05239;29.90146;-490.90440;,
 -0.08188;24.06399;-495.09932;,
 -0.84813;30.37499;-484.11846;,
 -6.39293;24.83017;-484.11846;,
 -5.91933;20.92964;-490.90440;,
 -0.08188;24.06399;-495.09932;,
 -160.53755;184.51924;659.53897;,
 -160.53755;184.51924;659.53897;,
 -160.53755;184.51924;659.53897;,
 -160.53755;184.51924;659.53897;,
 -160.53755;184.51924;659.53897;,
 -2.03767;26.01971;-489.02930;,
 -2.03767;26.01971;-489.02930;,
 -2.03767;26.01971;-489.02930;,
 -2.03767;26.01971;-489.02930;,
 -2.03767;26.01971;-489.02930;,
 160.80323;185.40293;345.98060;,
 162.07461;177.70240;346.74231;,
 143.40928;159.03701;-17.20885;,
 142.13831;166.73799;-17.96930;,
 155.16028;174.21487;347.97200;,
 136.49468;155.54949;-15.97824;,
 149.61538;179.75970;347.97200;,
 130.94978;161.09412;-15.97824;,
 153.10291;186.67408;346.74231;,
 134.43753;168.00884;-17.20885;,
 160.80323;185.40293;345.98060;,
 142.13831;166.73799;-17.96930;,
 94.62738;110.25508;-432.54307;,
 93.35601;117.95537;-433.30430;,
 87.71312;106.76765;-431.31270;,
 82.16814;112.31257;-431.31270;,
 85.65567;119.22710;-432.54307;,
 93.35601;117.95537;-433.30430;,
 76.95692;92.58480;-486.64678;,
 74.94974;99.54941;-489.64024;,
 71.23362;90.28839;-481.80391;,
 65.68873;95.83334;-481.80391;,
 67.98518;101.55665;-486.64678;,
 74.94974;99.54941;-489.64024;,
 55.51172;71.13957;-522.03878;,
 51.84161;76.44121;-526.50079;,
 52.47778;71.53276;-514.81837;,
 46.93299;77.07736;-514.81837;,
 46.53989;80.11137;-522.03878;,
 51.84161;76.44121;-526.50079;,
 32.14926;47.77712;-522.14542;,
 26.31221;50.91171;-526.33888;,
 32.62288;51.67761;-515.35909;,
 27.07799;57.22246;-515.35909;,
 23.17757;56.74896;-522.14542;,
 26.31221;50.91171;-526.33888;,
 1.53286;17.16062;-481.80128;,
 -4.30459;20.29497;-485.99620;,
 2.00646;21.06114;-475.01475;,
 -3.53844;26.60603;-475.01475;,
 -7.43887;26.13244;-481.80128;,
 -4.30459;20.29497;-485.99620;,
 156.15061;180.74988;668.64269;,
 156.15061;180.74988;668.64269;,
 156.15061;180.74988;668.64269;,
 156.15061;180.74988;668.64269;,
 156.15061;180.74988;668.64269;,
 -2.34890;22.25079;-479.92618;,
 -2.34890;22.25079;-479.92618;,
 -2.34890;22.25079;-479.92618;,
 -2.34890;22.25079;-479.92618;,
 -2.34890;22.25079;-479.92618;;
 
 192;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,35,2,1;,
 4;36,34,1,4;,
 4;37,36,4,6;,
 4;38,37,6,8;,
 4;39,38,8,10;,
 4;40,39,10,12;,
 4;41,40,12,14;,
 4;42,41,14,16;,
 4;43,19,18,44;,
 4;43,44,35,34;,
 4;45,21,19,43;,
 4;45,43,34,36;,
 4;46,23,21,45;,
 4;46,45,36,37;,
 4;47,25,23,46;,
 4;47,46,37,38;,
 4;48,27,25,47;,
 4;48,47,38,39;,
 4;49,29,27,48;,
 4;49,48,39,40;,
 4;50,31,29,49;,
 4;50,49,40,41;,
 4;51,33,31,50;,
 4;51,50,41,42;,
 3;52,53,54;,
 3;55,56,53;,
 3;57,58,56;,
 3;59,60,58;,
 3;61,62,60;,
 3;63,64,62;,
 4;54,53,65,66;,
 4;53,56,67,65;,
 4;56,58,68,67;,
 4;58,60,69,68;,
 4;60,62,70,69;,
 4;62,64,71,70;,
 4;66,65,72,73;,
 4;65,67,74,72;,
 4;67,68,75,74;,
 4;68,69,76,75;,
 4;69,70,77,76;,
 4;70,71,78,77;,
 4;73,72,79,80;,
 4;72,74,81,79;,
 4;74,75,82,81;,
 4;75,76,83,82;,
 4;76,77,84,83;,
 4;77,78,85,84;,
 4;80,79,86,87;,
 4;79,81,88,86;,
 4;81,82,89,88;,
 4;82,83,90,89;,
 4;83,84,91,90;,
 4;84,85,92,91;,
 3;87,86,93;,
 3;86,88,94;,
 3;88,89,95;,
 3;89,90,96;,
 3;90,91,97;,
 3;91,92,98;,
 3;99,100,101;,
 3;102,103,100;,
 3;104,105,103;,
 3;106,107,105;,
 3;108,109,107;,
 3;110,111,109;,
 4;101,100,112,113;,
 4;100,103,114,112;,
 4;103,105,115,114;,
 4;105,107,116,115;,
 4;107,109,117,116;,
 4;109,111,118,117;,
 4;113,112,119,120;,
 4;112,114,121,119;,
 4;114,115,122,121;,
 4;115,116,123,122;,
 4;116,117,124,123;,
 4;117,118,125,124;,
 4;120,119,126,127;,
 4;119,121,128,126;,
 4;121,122,129,128;,
 4;122,123,130,129;,
 4;123,124,131,130;,
 4;124,125,132,131;,
 4;127,126,133,134;,
 4;126,128,135,133;,
 4;128,129,136,135;,
 4;129,130,137,136;,
 4;130,131,138,137;,
 4;131,132,139,138;,
 3;134,133,140;,
 3;133,135,141;,
 3;135,136,142;,
 3;136,137,143;,
 3;137,138,144;,
 3;138,139,145;,
 4;146,147,148,149;,
 4;147,150,151,148;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 4;149,148,158,159;,
 4;148,151,160,158;,
 4;151,153,161,160;,
 4;153,155,162,161;,
 4;155,157,163,162;,
 4;159,158,164,165;,
 4;158,160,166,164;,
 4;160,161,167,166;,
 4;161,162,168,167;,
 4;162,163,169,168;,
 4;165,164,170,171;,
 4;164,166,172,170;,
 4;166,167,173,172;,
 4;167,168,174,173;,
 4;168,169,175,174;,
 4;171,170,176,177;,
 4;170,172,178,176;,
 4;172,173,179,178;,
 4;173,174,180,179;,
 4;174,175,181,180;,
 4;177,176,182,183;,
 4;176,178,184,182;,
 4;178,179,185,184;,
 4;179,180,186,185;,
 4;180,181,187,186;,
 3;188,147,146;,
 3;189,150,147;,
 3;190,152,150;,
 3;191,154,152;,
 3;192,156,154;,
 3;193,183,182;,
 3;194,182,184;,
 3;195,184,185;,
 3;196,185,186;,
 3;197,186,187;,
 4;198,199,200,201;,
 4;199,202,203,200;,
 4;202,204,205,203;,
 4;204,206,207,205;,
 4;206,208,209,207;,
 4;201,200,210,211;,
 4;200,203,212,210;,
 4;203,205,213,212;,
 4;205,207,214,213;,
 4;207,209,215,214;,
 4;211,210,216,217;,
 4;210,212,218,216;,
 4;212,213,219,218;,
 4;213,214,220,219;,
 4;214,215,221,220;,
 4;217,216,222,223;,
 4;216,218,224,222;,
 4;218,219,225,224;,
 4;219,220,226,225;,
 4;220,221,227,226;,
 4;223,222,228,229;,
 4;222,224,230,228;,
 4;224,225,231,230;,
 4;225,226,232,231;,
 4;226,227,233,232;,
 4;229,228,234,235;,
 4;228,230,236,234;,
 4;230,231,237,236;,
 4;231,232,238,237;,
 4;232,233,239,238;,
 3;240,199,198;,
 3;241,202,199;,
 3;242,204,202;,
 3;243,206,204;,
 3;244,208,206;,
 3;245,235,234;,
 3;246,234,236;,
 3;247,236,237;,
 3;248,237,238;,
 3;249,238,239;;
 
 MeshMaterialList {
  2;
  192;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.053600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  192;
  0.000000;0.000000;1.000000;,
  0.000251;0.965280;-0.261218;,
  0.745776;0.594194;-0.301251;,
  0.912166;-0.238224;-0.333470;,
  0.565117;-0.751550;-0.340318;,
  0.000546;-0.933217;-0.359312;,
  -0.564448;-0.751826;-0.340816;,
  -0.911943;-0.238229;-0.334076;,
  -0.745454;0.594412;-0.301618;,
  0.715787;0.526554;-0.458683;,
  -0.001046;0.962796;0.270228;,
  0.679561;0.681109;0.272557;,
  0.961682;0.000522;0.274166;,
  0.679743;-0.680261;0.274218;,
  -0.001034;-0.962104;0.272680;,
  -0.681467;-0.679973;0.270629;,
  -0.963121;0.000538;0.269067;,
  -0.681326;0.680863;0.268738;,
  0.000250;0.998399;-0.056558;,
  0.732090;0.677821;-0.067836;,
  0.992027;-0.084638;-0.093381;,
  0.668642;-0.734888;-0.113393;,
  0.000551;-0.992561;-0.121750;,
  -0.668081;-0.735315;-0.113928;,
  -0.991966;-0.084657;-0.094002;,
  -0.731824;0.678074;-0.068190;,
  -0.000000;-0.853854;-0.520512;,
  -0.715787;0.526554;-0.458683;,
  -0.001995;0.856825;0.515603;,
  0.602650;0.605601;0.519673;,
  0.852650;0.000995;0.522482;,
  0.602381;-0.603368;0.522575;,
  -0.001972;-0.854228;0.519895;,
  -0.606994;-0.604142;0.516305;,
  -0.858047;0.001026;0.513569;,
  -0.607416;0.606532;0.512995;,
  -0.000000;1.000000;-0.000003;,
  -0.000001;0.870413;-0.492321;,
  0.426357;0.870417;-0.246160;,
  0.426358;0.870418;0.246155;,
  0.000000;0.870420;0.492310;,
  -0.426359;0.870417;0.246153;,
  -0.426359;0.870415;-0.246160;,
  -0.000001;0.506745;-0.862096;,
  0.746593;0.506748;-0.431051;,
  0.746593;0.506750;0.431048;,
  0.000000;0.506752;0.862092;,
  -0.746591;0.506756;0.431045;,
  -0.746592;0.506752;-0.431050;,
  -0.000000;-0.000003;-1.000000;,
  0.866023;-0.000003;-0.500004;,
  0.866023;-0.000003;0.500004;,
  -0.000000;-0.000003;1.000000;,
  -0.866023;-0.000003;0.500004;,
  -0.866023;-0.000003;-0.500004;,
  -0.000001;-0.506741;-0.862099;,
  0.746595;-0.506744;-0.431052;,
  0.746595;-0.506748;0.431048;,
  -0.000002;-0.506748;0.862094;,
  -0.746594;-0.506749;0.431048;,
  -0.746594;-0.506747;-0.431051;,
  -0.000001;-0.870410;-0.492328;,
  0.426363;-0.870413;-0.246164;,
  0.426363;-0.870415;0.246156;,
  -0.000002;-0.870416;0.492316;,
  -0.426366;-0.870413;0.246158;,
  -0.426365;-0.870412;-0.246164;,
  -0.000000;-1.000000;-0.000003;,
  0.000001;1.000000;-0.000003;,
  0.000001;0.870414;-0.492321;,
  0.426359;0.870416;-0.246160;,
  0.426359;0.870417;0.246153;,
  -0.000000;0.870420;0.492309;,
  -0.426359;0.870417;0.246154;,
  -0.426357;0.870416;-0.246160;,
  0.000002;0.506745;-0.862096;,
  0.746593;0.506749;-0.431050;,
  0.746592;0.506753;0.431046;,
  -0.000001;0.506753;0.862091;,
  -0.746591;0.506755;0.431046;,
  -0.746591;0.506753;-0.431050;,
  0.000002;-0.000004;-1.000000;,
  0.866024;-0.000003;-0.500003;,
  0.866023;-0.000003;0.500004;,
  -0.000001;-0.000003;1.000000;,
  -0.866023;-0.000003;0.500004;,
  -0.866023;-0.000004;-0.500005;,
  0.000002;-0.506741;-0.862098;,
  0.746595;-0.506745;-0.431051;,
  0.746594;-0.506749;0.431047;,
  0.000000;-0.506751;0.862092;,
  -0.746593;-0.506753;0.431046;,
  -0.746592;-0.506749;-0.431051;,
  0.000001;-0.870410;-0.492328;,
  0.426365;-0.870412;-0.246163;,
  0.426365;-0.870414;0.246157;,
  0.000001;-0.870418;0.492314;,
  -0.426363;-0.870414;0.246156;,
  -0.426363;-0.870412;-0.246164;,
  0.000001;-1.000000;-0.000003;,
  -0.164443;0.986247;0.016593;,
  -0.160801;0.986763;-0.021022;,
  0.891278;0.453033;0.019608;,
  0.706417;-0.706397;0.044483;,
  -0.453041;-0.891274;0.019607;,
  -0.152909;0.983600;-0.095651;,
  0.889637;0.455205;0.036546;,
  0.702146;-0.702150;0.118223;,
  -0.455207;-0.889635;0.036545;,
  -0.135280;0.961429;-0.239485;,
  0.882413;0.461317;0.092380;,
  0.675825;-0.675843;0.294104;,
  -0.461320;-0.882412;0.092378;,
  -0.087485;0.889343;-0.448794;,
  0.863157;0.473443;0.175530;,
  0.601104;-0.601118;0.526622;,
  -0.473439;-0.863159;0.175531;,
  0.184086;0.656688;-0.731351;,
  0.767677;0.579095;0.274446;,
  0.311766;-0.311771;0.897553;,
  -0.579091;-0.767679;0.274451;,
  0.627968;0.211216;-0.749028;,
  0.596142;0.750967;0.284011;,
  -0.252686;0.252688;0.933969;,
  -0.750966;-0.596145;0.284010;,
  0.798154;0.004305;-0.602438;,
  0.512713;0.825168;0.237114;,
  -0.482040;0.482042;0.731624;,
  -0.825166;-0.512719;0.237109;,
  0.643437;-0.643431;0.414711;,
  -0.986758;0.160832;-0.021024;,
  -0.983598;0.152924;-0.095652;,
  -0.961428;0.135286;-0.239485;,
  -0.889344;0.087483;-0.448793;,
  -0.656691;-0.184094;-0.731346;,
  -0.211218;-0.627971;-0.749025;,
  -0.004305;-0.798154;-0.602437;,
  0.891525;0.452660;0.016772;,
  0.707024;-0.706995;0.016593;,
  -0.452674;-0.891518;0.016771;,
  -0.986241;0.164479;0.016592;,
  0.643460;-0.643453;0.414642;,
  0.643452;-0.643426;0.414695;,
  0.643432;-0.643405;0.414760;,
  0.643408;-0.643428;0.414762;,
  0.643432;-0.643446;0.414697;,
  0.986242;0.164473;0.016593;,
  0.986759;0.160825;-0.021023;,
  0.453035;-0.891277;0.019607;,
  -0.706399;-0.706415;0.044483;,
  -0.891276;0.453037;0.019607;,
  0.983600;0.152914;-0.095651;,
  0.455214;-0.889632;0.036544;,
  -0.702137;-0.702158;0.118223;,
  -0.889629;0.455220;0.036543;,
  0.961429;0.135283;-0.239484;,
  0.461336;-0.882404;0.092371;,
  -0.675829;-0.675839;0.294103;,
  -0.882406;0.461331;0.092377;,
  0.889336;0.087498;-0.448805;,
  0.473453;-0.863153;0.175526;,
  -0.601106;-0.601109;0.526630;,
  -0.863155;0.473447;0.175530;,
  0.656665;-0.184058;-0.731378;,
  0.579091;-0.767677;0.274455;,
  -0.311769;-0.311772;0.897551;,
  -0.767677;0.579092;0.274455;,
  0.211196;-0.627945;-0.749054;,
  0.750963;-0.596148;0.284011;,
  0.252679;0.252680;0.933973;,
  -0.596148;0.750962;0.284013;,
  0.004292;-0.798143;-0.602453;,
  0.825164;-0.512725;0.237103;,
  0.482041;0.482043;0.731622;,
  -0.512725;0.825164;0.237105;,
  -0.643444;-0.643439;0.414688;,
  0.160803;0.986763;-0.021022;,
  0.152913;0.983600;-0.095652;,
  0.135294;0.961427;-0.239485;,
  0.087504;0.889334;-0.448807;,
  -0.184053;0.656661;-0.731383;,
  -0.627942;0.211193;-0.749057;,
  -0.798143;0.004293;-0.602453;,
  0.452660;-0.891526;0.016771;,
  -0.707005;-0.707014;0.016592;,
  -0.891527;0.452657;0.016771;,
  0.164448;0.986246;0.016594;,
  -0.643460;-0.643453;0.414642;,
  -0.643442;-0.643446;0.414680;,
  -0.643425;-0.643436;0.414723;,
  -0.643440;-0.643423;0.414720;,
  -0.643453;-0.643437;0.414677;;
  192;
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,1,2;,
  3;9,2,3;,
  3;26,3,4;,
  3;26,4,5;,
  3;26,5,6;,
  3;26,6,7;,
  3;27,7,8;,
  3;27,8,1;,
  4;11,10,28,29;,
  4;12,11,29,30;,
  4;13,12,30,31;,
  4;14,13,31,32;,
  4;15,14,32,33;,
  4;16,15,33,34;,
  4;17,16,34,35;,
  4;10,17,35,28;,
  4;19,2,1,18;,
  4;19,18,10,11;,
  4;20,3,2,19;,
  4;20,19,11,12;,
  4;21,4,3,20;,
  4;21,20,12,13;,
  4;22,5,4,21;,
  4;22,21,13,14;,
  4;23,6,5,22;,
  4;23,22,14,15;,
  4;24,7,6,23;,
  4;24,23,15,16;,
  4;25,8,7,24;,
  4;25,24,16,17;,
  4;18,1,8,25;,
  4;18,25,17,10;,
  3;36,38,37;,
  3;36,39,38;,
  3;36,40,39;,
  3;36,41,40;,
  3;36,42,41;,
  3;36,37,42;,
  4;37,38,44,43;,
  4;38,39,45,44;,
  4;39,40,46,45;,
  4;40,41,47,46;,
  4;41,42,48,47;,
  4;42,37,43,48;,
  4;43,44,50,49;,
  4;44,45,51,50;,
  4;45,46,52,51;,
  4;46,47,53,52;,
  4;47,48,54,53;,
  4;48,43,49,54;,
  4;49,50,56,55;,
  4;50,51,57,56;,
  4;51,52,58,57;,
  4;52,53,59,58;,
  4;53,54,60,59;,
  4;54,49,55,60;,
  4;55,56,62,61;,
  4;56,57,63,62;,
  4;57,58,64,63;,
  4;58,59,65,64;,
  4;59,60,66,65;,
  4;60,55,61,66;,
  3;61,62,67;,
  3;62,63,67;,
  3;63,64,67;,
  3;64,65,67;,
  3;65,66,67;,
  3;66,61,67;,
  3;68,70,69;,
  3;68,71,70;,
  3;68,72,71;,
  3;68,73,72;,
  3;68,74,73;,
  3;68,69,74;,
  4;69,70,76,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,73,79,78;,
  4;73,74,80,79;,
  4;74,69,75,80;,
  4;75,76,82,81;,
  4;76,77,83,82;,
  4;77,78,84,83;,
  4;78,79,85,84;,
  4;79,80,86,85;,
  4;80,75,81,86;,
  4;81,82,88,87;,
  4;82,83,89,88;,
  4;83,84,90,89;,
  4;84,85,91,90;,
  4;85,86,92,91;,
  4;86,81,87,92;,
  4;87,88,94,93;,
  4;88,89,95,94;,
  4;89,90,96,95;,
  4;90,91,97,96;,
  4;91,92,98,97;,
  4;92,87,93,98;,
  3;93,94,99;,
  3;94,95,99;,
  3;95,96,99;,
  3;96,97,99;,
  3;97,98,99;,
  3;98,93,99;,
  4;101,101,105,105;,
  4;102,102,106,106;,
  4;103,103,107,107;,
  4;104,104,108,108;,
  4;130,130,131,131;,
  4;105,105,109,109;,
  4;106,106,110,110;,
  4;107,107,111,111;,
  4;108,108,112,112;,
  4;131,131,132,132;,
  4;109,109,113,113;,
  4;110,110,114,114;,
  4;111,111,115,115;,
  4;112,112,116,116;,
  4;132,132,133,133;,
  4;113,113,117,117;,
  4;114,114,118,118;,
  4;115,115,119,119;,
  4;116,116,120,120;,
  4;133,133,134,134;,
  4;117,117,121,121;,
  4;118,118,122,122;,
  4;119,119,123,123;,
  4;120,120,124,124;,
  4;134,134,135,135;,
  4;121,121,125,125;,
  4;122,122,126,126;,
  4;123,123,127,127;,
  4;124,124,128,128;,
  4;135,135,136,136;,
  3;100,101,101;,
  3;137,102,102;,
  3;138,103,103;,
  3;139,104,104;,
  3;140,130,130;,
  3;129,141,142;,
  3;129,142,143;,
  3;129,143,144;,
  3;129,144,145;,
  3;129,145,141;,
  4;147,147,151,151;,
  4;148,148,152,152;,
  4;149,149,153,153;,
  4;150,150,154,154;,
  4;176,176,177,177;,
  4;151,151,155,155;,
  4;152,152,156,156;,
  4;153,153,157,157;,
  4;154,154,158,158;,
  4;177,177,178,178;,
  4;155,155,159,159;,
  4;156,156,160,160;,
  4;157,157,161,161;,
  4;158,158,162,162;,
  4;178,178,179,179;,
  4;159,159,163,163;,
  4;160,160,164,164;,
  4;161,161,165,165;,
  4;162,162,166,166;,
  4;179,179,180,180;,
  4;163,163,167,167;,
  4;164,164,168,168;,
  4;165,165,169,169;,
  4;166,166,170,170;,
  4;180,180,181,181;,
  4;167,167,171,171;,
  4;168,168,172,172;,
  4;169,169,173,173;,
  4;170,170,174,174;,
  4;181,181,182,182;,
  3;146,147,147;,
  3;183,148,148;,
  3;184,149,149;,
  3;185,150,150;,
  3;186,176,176;,
  3;175,187,188;,
  3;175,188,189;,
  3;175,189,190;,
  3;175,190,191;,
  3;175,191,187;;
 }
 MeshTextureCoords {
  250;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.125000;0.619510;,
  0.000000;0.622520;,
  0.250000;0.617200;,
  0.375000;0.616940;,
  0.500000;0.618880;,
  0.625000;0.621880;,
  0.750000;0.624190;,
  0.875000;0.624460;,
  1.000000;0.622520;,
  0.125000;0.809850;,
  0.000000;0.812430;,
  0.250000;0.807350;,
  0.375000;0.806410;,
  0.500000;0.807590;,
  0.625000;0.810190;,
  0.750000;0.812670;,
  0.875000;0.813590;,
  1.000000;0.812430;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.166670;,
  0.000000;0.166670;,
  0.400000;0.000000;,
  0.400000;0.166670;,
  0.600000;0.000000;,
  0.600000;0.166670;,
  0.800000;0.000000;,
  0.800000;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.200000;0.333330;,
  0.000000;0.333330;,
  0.400000;0.333330;,
  0.600000;0.333330;,
  0.800000;0.333330;,
  1.000000;0.333330;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.666670;,
  0.000000;0.666670;,
  0.400000;0.666670;,
  0.600000;0.666670;,
  0.800000;0.666670;,
  1.000000;0.666670;,
  0.200000;0.833330;,
  0.000000;0.833330;,
  0.400000;0.833330;,
  0.600000;0.833330;,
  0.800000;0.833330;,
  1.000000;0.833330;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.166670;,
  0.000000;0.166670;,
  0.400000;0.000000;,
  0.400000;0.166670;,
  0.600000;0.000000;,
  0.600000;0.166670;,
  0.800000;0.000000;,
  0.800000;0.166670;,
  1.000000;0.000000;,
  1.000000;0.166670;,
  0.200000;0.333330;,
  0.000000;0.333330;,
  0.400000;0.333330;,
  0.600000;0.333330;,
  0.800000;0.333330;,
  1.000000;0.333330;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.666670;,
  0.000000;0.666670;,
  0.400000;0.666670;,
  0.600000;0.666670;,
  0.800000;0.666670;,
  1.000000;0.666670;,
  0.200000;0.833330;,
  0.000000;0.833330;,
  0.400000;0.833330;,
  0.600000;0.833330;,
  0.800000;0.833330;,
  1.000000;0.833330;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.100000;0.000000;,
  0.300000;0.000000;,
  0.500000;0.000000;,
  0.700000;0.000000;,
  0.900000;0.000000;,
  0.100000;1.000000;,
  0.300000;1.000000;,
  0.500000;1.000000;,
  0.700000;1.000000;,
  0.900000;1.000000;;
 }
}
