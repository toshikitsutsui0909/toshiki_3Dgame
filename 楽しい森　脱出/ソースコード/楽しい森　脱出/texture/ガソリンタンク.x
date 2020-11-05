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
 181;
 -3.47144;5.79174;0.35826;,
 -3.17447;5.96773;0.56054;,
 -3.80215;6.91681;0.56054;,
 -4.09912;6.74082;0.35826;,
 -2.83677;6.16786;0.49029;,
 -3.46445;7.11694;0.49029;,
 -2.61635;6.29849;0.18038;,
 -3.24403;7.24756;0.18038;,
 -2.61635;6.29849;-0.22419;,
 -3.24403;7.24756;-0.22419;,
 -2.83677;6.16786;-0.53411;,
 -3.46445;7.11694;-0.53411;,
 -3.17447;5.96773;-0.60436;,
 -3.80215;6.91681;-0.60436;,
 -3.47144;5.79174;-0.40208;,
 -4.09912;6.74082;-0.40208;,
 -3.58872;5.72224;-0.02191;,
 -4.21640;6.67131;-0.02191;,
 -3.47144;5.79174;0.35826;,
 -4.09912;6.74082;0.35826;,
 -3.17447;5.96773;0.56054;,
 -3.47144;5.79174;0.35826;,
 -3.08742;6.01932;-0.02191;,
 -2.83677;6.16786;0.49029;,
 -2.61635;6.29849;0.18038;,
 -2.61635;6.29849;-0.22419;,
 -2.83677;6.16786;-0.53411;,
 -3.17447;5.96773;-0.60436;,
 -3.47144;5.79174;-0.40208;,
 -3.58872;5.72224;-0.02191;,
 -4.09912;6.74082;0.35826;,
 -3.80215;6.91681;0.56054;,
 -3.71510;6.96840;-0.02191;,
 -3.46445;7.11694;0.49029;,
 -3.24403;7.24756;0.18038;,
 -3.24403;7.24756;-0.22419;,
 -3.46445;7.11694;-0.53411;,
 -3.80215;6.91681;-0.60436;,
 -4.09912;6.74082;-0.40208;,
 -4.21640;6.67131;-0.02191;,
 3.29304;6.07327;0.32300;,
 3.61091;6.07327;0.50653;,
 3.61091;7.08915;0.50653;,
 3.29304;7.08915;0.32300;,
 3.97238;6.07327;0.44279;,
 3.97238;7.08915;0.44279;,
 4.20831;6.07327;0.16162;,
 4.20831;7.08915;0.16162;,
 4.20831;6.07327;-0.20543;,
 4.20831;7.08915;-0.20543;,
 3.97238;6.07327;-0.48661;,
 3.97238;7.08915;-0.48661;,
 3.61091;6.07327;-0.55034;,
 3.61091;7.08915;-0.55034;,
 3.29304;6.07327;-0.36682;,
 3.29304;7.08915;-0.36682;,
 3.16750;6.07327;-0.02191;,
 3.16750;7.08915;-0.02191;,
 3.29304;6.07327;0.32300;,
 3.29304;7.08915;0.32300;,
 3.61091;6.07327;0.50653;,
 3.29304;6.07327;0.32300;,
 3.70408;6.07327;-0.02191;,
 3.97238;6.07327;0.44279;,
 4.20831;6.07327;0.16162;,
 4.20831;6.07327;-0.20543;,
 3.97238;6.07327;-0.48661;,
 3.61091;6.07327;-0.55034;,
 3.29304;6.07327;-0.36682;,
 3.16750;6.07327;-0.02191;,
 3.29304;7.08915;0.32300;,
 3.61091;7.08915;0.50653;,
 3.70408;7.08915;-0.02191;,
 3.97238;7.08915;0.44279;,
 4.20831;7.08915;0.16162;,
 4.20831;7.08915;-0.20543;,
 3.97238;7.08915;-0.48661;,
 3.61091;7.08915;-0.55034;,
 3.29304;7.08915;-0.36682;,
 3.16750;7.08915;-0.02191;,
 2.88081;1.91143;-2.43747;,
 2.88081;-2.98977;-2.43747;,
 2.03952;-2.98977;-2.43747;,
 2.03952;1.91143;-2.43747;,
 2.88081;8.07364;-0.02191;,
 2.88081;8.07364;-1.48725;,
 2.03952;8.07364;-1.48725;,
 2.03952;8.07364;-0.02191;,
 2.88081;1.91143;2.39366;,
 3.18035;6.81264;2.19768;,
 1.84221;6.81264;2.19768;,
 2.03952;1.91143;2.39366;,
 2.88081;-2.98977;-0.02191;,
 2.88081;-2.98977;2.39366;,
 2.03952;-2.98977;2.39366;,
 2.03952;-2.98977;-0.02191;,
 -4.33820;1.91143;-2.43747;,
 -4.34335;-2.29098;-2.43747;,
 -4.34335;-2.29098;-0.02191;,
 -4.33820;1.91143;-0.02191;,
 4.63372;1.91143;2.39366;,
 4.50175;-2.24820;2.39366;,
 4.50175;-2.24820;-0.02191;,
 4.63372;1.91143;-0.02191;,
 -2.72576;1.91143;-2.43747;,
 -2.72576;-2.98977;-2.43747;,
 -4.35767;6.14136;-2.17541;,
 -3.13256;6.81264;-2.17541;,
 1.84221;6.81264;-2.17541;,
 3.18035;6.81264;-2.17541;,
 -3.13256;6.81264;-0.02191;,
 -4.35767;6.14136;-0.02191;,
 -4.35767;6.14136;2.19768;,
 -3.13256;6.81264;2.19768;,
 2.03952;8.07364;1.55546;,
 2.88081;8.07364;1.55546;,
 -2.72576;1.91143;2.39366;,
 -4.33820;1.91143;2.39366;,
 -4.34335;-2.29098;2.39366;,
 -2.72576;-2.98977;2.39366;,
 -2.72576;-2.98977;-0.02191;,
 -4.34335;-2.29098;-0.02191;,
 -4.34335;-2.29098;-2.43747;,
 -2.72576;-2.98977;-2.43747;,
 2.03952;-2.98977;-2.43747;,
 2.88081;-2.98977;-2.43747;,
 -4.34335;-2.29098;2.39366;,
 -4.33820;1.91143;2.39366;,
 -4.35767;6.14136;2.19768;,
 -4.35767;6.14136;-0.02191;,
 4.50175;-2.24820;-2.43747;,
 4.63372;1.91143;-2.43747;,
 4.26801;6.72128;-2.17541;,
 4.26801;6.72128;-0.02191;,
 4.26801;6.72128;2.19768;,
 -1.89703;-2.98977;-2.43747;,
 -1.89703;-2.98977;-0.02191;,
 -1.89703;-2.98977;2.39366;,
 -1.89703;1.91143;2.39366;,
 -1.64420;6.81264;2.19768;,
 -2.72576;8.07364;-0.02191;,
 -2.72576;8.07364;1.55546;,
 -1.89703;8.07364;1.55546;,
 -1.89703;8.07364;-0.02191;,
 -1.89703;8.07364;-1.48725;,
 -2.72576;8.07364;-1.48725;,
 -1.64420;6.81264;-2.17541;,
 -1.89703;1.91143;-2.43747;,
 -1.89703;-2.98977;-2.43747;,
 4.50175;-2.24820;-2.43747;,
 4.50175;-2.24820;-0.02191;,
 4.50175;-2.24820;2.39366;,
 4.63372;1.91143;2.39366;,
 4.26801;6.72128;2.19768;,
 3.18035;6.81264;-0.02191;,
 4.26801;6.72128;-0.02191;,
 0.01763;-2.98977;-2.43747;,
 0.01763;-2.98977;-0.02191;,
 0.01763;-2.98977;2.39366;,
 0.01763;1.91143;2.39366;,
 0.01763;6.81264;2.19768;,
 -1.64421;6.81264;-0.02191;,
 0.01763;6.81264;-0.02191;,
 0.01763;6.81264;-2.17541;,
 0.01763;1.91143;-2.43747;,
 0.01763;-2.98977;-2.43747;,
 1.84221;6.81264;-0.02191;,
 2.12859;7.56388;-0.63437;,
 -2.09334;7.56388;-0.63437;,
 -2.09334;8.00221;-0.63437;,
 2.12859;8.00221;-0.63437;,
 -2.09334;8.00221;0.59056;,
 2.12859;8.00221;0.59056;,
 -2.09334;7.56388;0.59056;,
 2.12859;7.56388;0.59056;,
 -2.09334;7.56388;-0.63437;,
 2.12859;7.56388;-0.63437;,
 -2.09334;7.56388;0.59056;,
 -2.09334;8.00221;0.59056;,
 2.12859;7.56388;0.59056;,
 2.12859;8.00221;0.59056;;
 
 128;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 3;20,21,22;,
 3;23,20,22;,
 3;24,23,22;,
 3;25,24,22;,
 3;26,25,22;,
 3;27,26,22;,
 3;28,27,22;,
 3;29,28,22;,
 3;21,29,22;,
 3;30,31,32;,
 3;31,33,32;,
 3;33,34,32;,
 3;34,35,32;,
 3;35,36,32;,
 3;36,37,32;,
 3;37,38,32;,
 3;38,39,32;,
 3;39,30,32;,
 4;40,41,42,43;,
 4;41,44,45,42;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 3;60,61,62;,
 3;63,60,62;,
 3;64,63,62;,
 3;65,64,62;,
 3;66,65,62;,
 3;67,66,62;,
 3;68,67,62;,
 3;69,68,62;,
 3;61,69,62;,
 3;70,71,72;,
 3;71,73,72;,
 3;73,74,72;,
 3;74,75,72;,
 3;75,76,72;,
 3;76,77,72;,
 3;77,78,72;,
 3;78,79,72;,
 3;79,70,72;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;96,97,98,99;,
 4;100,101,102,103;,
 4;104,105,97,96;,
 4;96,106,107,104;,
 4;83,108,109,80;,
 4;110,107,106,111;,
 4;111,112,113,110;,
 4;87,114,115,84;,
 4;116,113,112,117;,
 4;117,118,119,116;,
 4;91,94,93,88;,
 4;120,119,118,121;,
 4;121,122,123,120;,
 4;95,124,125,92;,
 4;98,126,127,99;,
 4;127,128,129,99;,
 4;129,106,96,99;,
 4;102,130,131,103;,
 4;131,132,133,103;,
 4;133,134,100,103;,
 4;120,123,135,136;,
 4;136,137,119,120;,
 4;116,119,137,138;,
 4;138,139,113,116;,
 4;140,141,142,143;,
 4;143,144,145,140;,
 4;104,107,146,147;,
 4;147,148,105,104;,
 4;92,125,149,150;,
 4;150,151,93,92;,
 4;88,93,151,152;,
 4;152,153,89,88;,
 4;154,89,153,155;,
 4;155,132,109,154;,
 4;80,109,132,131;,
 4;131,130,81,80;,
 4;136,135,156,157;,
 4;158,137,136,157;,
 4;138,137,158,159;,
 4;160,139,138,159;,
 4;161,139,160,162;,
 4;163,146,161,162;,
 4;147,146,163,164;,
 4;165,148,147,164;,
 4;83,82,165,164;,
 4;163,108,83,164;,
 4;166,108,163,162;,
 4;160,90,166,162;,
 4;91,90,160,159;,
 4;158,94,91,159;,
 4;95,94,158,157;,
 4;156,124,95,157;,
 4;154,109,85,84;,
 4;109,108,86,85;,
 4;108,166,87,86;,
 4;166,90,114,87;,
 4;90,89,115,114;,
 4;89,154,84,115;,
 4;110,113,141,140;,
 4;113,139,142,141;,
 4;139,161,143,142;,
 4;161,146,144,143;,
 4;146,107,145,144;,
 4;107,110,140,145;,
 4;167,168,169,170;,
 4;170,169,171,172;,
 4;172,171,173,174;,
 4;174,173,175,176;,
 4;168,177,178,169;,
 4;179,167,170,180;;
 
 MeshMaterialList {
  3;
  128;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  1,
  1;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.096000;0.096000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  107;
  -0.642184;-0.424714;0.638136;,
  -0.146569;-0.096935;0.984439;,
  0.420893;0.278360;0.863345;,
  0.784909;0.519104;0.338304;,
  0.784909;0.519104;-0.338304;,
  0.420893;0.278360;-0.863345;,
  -0.146569;-0.096935;-0.984440;,
  -0.642184;-0.424714;-0.638136;,
  -0.834088;-0.551632;0.000000;,
  0.509823;-0.860280;0.000000;,
  -0.509826;0.860277;0.000000;,
  -0.766044;0.000000;0.642788;,
  -0.173649;0.000000;0.984808;,
  0.499999;0.000000;0.866026;,
  0.939693;0.000000;0.342020;,
  0.939693;0.000000;-0.342020;,
  0.499999;0.000000;-0.866026;,
  -0.173649;0.000000;-0.984808;,
  -0.766044;0.000000;-0.642788;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.999497;-0.031711;-0.000000;,
  -0.999999;0.001226;0.000000;,
  0.997122;0.075814;0.000000;,
  -0.013989;0.056453;-0.998307;,
  0.997122;0.075814;0.000000;,
  -0.480525;0.876981;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;0.026706;-0.999643;,
  -0.999999;-0.001689;-0.000000;,
  0.999756;0.022084;0.000000;,
  -0.480525;0.876981;-0.000000;,
  0.000000;0.039954;0.999202;,
  0.997122;0.075814;0.000000;,
  0.000000;0.019981;0.999800;,
  -0.005236;0.021129;0.999763;,
  0.999756;0.022084;0.000000;,
  -0.999999;0.001226;0.000000;,
  0.999497;-0.031711;-0.000000;,
  -0.999999;-0.001689;-0.000000;,
  0.999756;0.022084;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.202481;-0.979286;0.000000;,
  -0.002618;0.020555;0.999785;,
  -0.770735;0.637156;0.000000;,
  -0.770735;0.637156;-0.000000;,
  -0.004767;0.200681;-0.979645;,
  -0.003499;0.027472;-0.999616;,
  0.212891;-0.977076;-0.000000;,
  0.000417;0.020050;0.999799;,
  0.000568;0.181733;0.983348;,
  0.083696;0.996491;0.000000;,
  0.000760;0.199787;-0.979839;,
  0.000558;0.026799;-0.999641;,
  0.000000;0.181642;0.983365;,
  0.000000;0.199665;-0.979864;,
  0.509825;-0.860278;0.000001;,
  0.509823;-0.860279;-0.000002;,
  0.509822;-0.860280;0.000002;,
  0.509821;-0.860281;0.000002;,
  0.509821;-0.860281;-0.000002;,
  0.509823;-0.860280;-0.000002;,
  0.509825;-0.860278;-0.000000;,
  0.509823;-0.860279;0.000002;,
  0.509821;-0.860281;-0.000000;,
  -0.509834;0.860273;0.000002;,
  -0.509831;0.860274;0.000010;,
  -0.509823;0.860279;0.000000;,
  -0.509811;0.860286;-0.000004;,
  -0.509811;0.860286;0.000004;,
  -0.509823;0.860279;-0.000000;,
  -0.509831;0.860274;-0.000010;,
  -0.509834;0.860273;-0.000002;,
  -0.509840;0.860269;0.000000;,
  -0.006998;0.028238;-0.999577;,
  -0.770735;0.637156;-0.000000;,
  -0.480525;0.876981;-0.000000;,
  -0.003563;0.182405;0.983217;,
  -0.010469;0.042249;0.999052;,
  -0.396574;-0.918003;0.000000;,
  -0.396574;-0.918003;0.000000;,
  -0.999999;-0.001689;0.000000;,
  -0.999989;-0.004604;0.000000;,
  -0.999989;-0.004604;-0.000000;,
  -0.999989;-0.004604;-0.000000;,
  0.416022;-0.909355;-0.000000;,
  0.000835;0.020120;0.999797;,
  0.001669;0.040231;0.999189;,
  0.083696;0.996491;0.000000;,
  0.083696;0.996491;0.000000;,
  0.002231;0.053763;-0.998551;,
  0.001116;0.026891;-0.999638;,
  0.000000;0.053393;-0.998574;,
  0.972928;0.231110;0.000000;,
  0.000000;0.479034;-0.877796;,
  -0.987979;0.154587;0.000000;,
  -0.987979;0.154587;0.000000;,
  0.000000;0.453823;0.891092;,
  -0.951702;0.307023;0.000000;,
  0.000000;0.453823;0.891092;,
  0.980488;0.196580;-0.000000;,
  0.980488;0.196580;0.000000;,
  0.980488;0.196580;0.000000;,
  0.000000;0.479034;-0.877796;,
  -0.951702;0.307023;0.000000;,
  1.000000;0.000000;0.000000;;
  128;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,0,0,8;,
  3;57,58,9;,
  3;59,57,9;,
  3;60,59,9;,
  3;61,60,9;,
  3;62,61,9;,
  3;63,62,9;,
  3;64,63,9;,
  3;65,64,9;,
  3;58,65,9;,
  3;66,67,10;,
  3;67,68,10;,
  3;68,69,10;,
  3;69,70,10;,
  3;70,71,10;,
  3;71,72,10;,
  3;72,73,10;,
  3;73,74,10;,
  3;74,66,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,11,11,19;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  4;54,42,42,29;,
  4;21,21,21,21;,
  4;50,51,55,35;,
  4;49,49,20,20;,
  4;30,23,38,40;,
  4;37,22,39,41;,
  4;48,42,42,75;,
  4;75,25,47,48;,
  4;29,56,53,54;,
  4;46,76,77,32;,
  4;32,27,45,46;,
  4;21,21,21,21;,
  4;44,78,79,36;,
  4;36,28,28,44;,
  4;35,28,28,50;,
  4;43,43,80,81;,
  4;81,80,43,43;,
  4;20,20,49,49;,
  4;38,23,82,40;,
  4;82,83,84,40;,
  4;84,85,30,40;,
  4;39,22,31,41;,
  4;31,24,34,41;,
  4;34,26,37,41;,
  4;43,43,20,20;,
  4;20,20,43,43;,
  4;44,28,28,35;,
  4;35,55,78,44;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;48,47,56,29;,
  4;29,42,42,48;,
  4;49,49,86,86;,
  4;86,86,49,49;,
  4;50,28,28,87;,
  4;87,88,51,50;,
  4;52,89,89,52;,
  4;52,90,90,52;,
  4;54,53,91,92;,
  4;92,42,42,54;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;35,28,28,35;,
  4;33,55,35,35;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;29,56,93,29;,
  4;42,42,29,29;,
  4;29,42,42,29;,
  4;93,56,29,29;,
  4;21,21,21,21;,
  4;21,21,21,21;,
  4;35,55,33,35;,
  4;28,28,35,35;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;94,94,94,94;,
  4;53,56,95,95;,
  4;96,96,96,96;,
  4;96,97,97,96;,
  4;55,51,98,98;,
  4;94,94,94,94;,
  4;46,45,99,99;,
  4;78,55,100,100;,
  4;101,102,102,101;,
  4;102,103,103,102;,
  4;56,47,104,104;,
  4;76,46,99,105;,
  4;42,42,42,42;,
  4;21,21,21,21;,
  4;28,28,28,28;,
  4;20,20,20,20;,
  4;19,19,19,19;,
  4;106,106,106,106;;
 }
 MeshTextureCoords {
  181;
  0.375000;0.312500;,
  0.402778;0.312500;,
  0.402778;0.688440;,
  0.375000;0.688440;,
  0.430556;0.312500;,
  0.430556;0.688440;,
  0.458333;0.312500;,
  0.458333;0.688440;,
  0.486111;0.312500;,
  0.486111;0.688440;,
  0.513889;0.312500;,
  0.513889;0.688440;,
  0.541667;0.312500;,
  0.541667;0.688440;,
  0.569445;0.312500;,
  0.569445;0.688440;,
  0.597222;0.312500;,
  0.597222;0.688440;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.527133;0.002374;,
  0.619694;0.055814;,
  0.500000;0.150000;,
  0.421875;0.020934;,
  0.353173;0.102809;,
  0.353173;0.209691;,
  0.421875;0.291566;,
  0.527133;0.310126;,
  0.619694;0.256686;,
  0.656250;0.156250;,
  0.619694;0.944186;,
  0.527133;0.997626;,
  0.500000;0.837500;,
  0.421875;0.979066;,
  0.353173;0.897191;,
  0.353173;0.790309;,
  0.421875;0.708434;,
  0.527133;0.689874;,
  0.619694;0.743314;,
  0.656250;0.843750;,
  0.375000;0.312500;,
  0.402778;0.312500;,
  0.402778;0.688440;,
  0.375000;0.688440;,
  0.430556;0.312500;,
  0.430556;0.688440;,
  0.458333;0.312500;,
  0.458333;0.688440;,
  0.486111;0.312500;,
  0.486111;0.688440;,
  0.513889;0.312500;,
  0.513889;0.688440;,
  0.541667;0.312500;,
  0.541667;0.688440;,
  0.569445;0.312500;,
  0.569445;0.688440;,
  0.597222;0.312500;,
  0.597222;0.688440;,
  0.625000;0.312500;,
  0.625000;0.688440;,
  0.527133;0.002374;,
  0.619694;0.055814;,
  0.500000;0.150000;,
  0.421875;0.020934;,
  0.353173;0.102809;,
  0.353173;0.209691;,
  0.421875;0.291566;,
  0.527133;0.310126;,
  0.619694;0.256686;,
  0.656250;0.156250;,
  0.619694;0.944186;,
  0.527133;0.997626;,
  0.500000;0.837500;,
  0.421875;0.979066;,
  0.353173;0.897191;,
  0.353173;0.790309;,
  0.421875;0.708434;,
  0.527133;0.689874;,
  0.619694;0.743314;,
  0.656250;0.843750;,
  0.430876;0.125000;,
  0.430876;0.000000;,
  0.451187;0.000000;,
  0.451187;0.125000;,
  0.430876;0.375000;,
  0.430876;0.250000;,
  0.451187;0.250000;,
  0.451187;0.375000;,
  0.430876;0.625000;,
  0.430876;0.500000;,
  0.451187;0.500000;,
  0.451187;0.625000;,
  0.430876;0.875000;,
  0.430876;0.750000;,
  0.451187;0.750000;,
  0.451187;0.875000;,
  0.625000;0.125000;,
  0.625000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.566232;0.125000;,
  0.566232;0.000000;,
  0.625000;0.250000;,
  0.566232;0.250000;,
  0.451187;0.250000;,
  0.430876;0.250000;,
  0.566232;0.375000;,
  0.625000;0.375000;,
  0.625000;0.500000;,
  0.566232;0.500000;,
  0.451187;0.500000;,
  0.430876;0.500000;,
  0.566232;0.625000;,
  0.625000;0.625000;,
  0.625000;0.750000;,
  0.566232;0.750000;,
  0.566232;0.875000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.566232;1.000000;,
  0.451187;1.000000;,
  0.430876;1.000000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.546224;1.000000;,
  0.546224;0.875000;,
  0.546224;0.750000;,
  0.546224;0.625000;,
  0.546224;0.500000;,
  0.566232;0.375000;,
  0.566232;0.500000;,
  0.546224;0.500000;,
  0.546224;0.375000;,
  0.546224;0.250000;,
  0.566232;0.250000;,
  0.546224;0.250000;,
  0.546224;0.125000;,
  0.546224;0.000000;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.375000;0.750000;,
  0.375000;0.625000;,
  0.375000;0.500000;,
  0.430876;0.375000;,
  0.375000;0.375000;,
  0.500000;1.000000;,
  0.500000;0.875000;,
  0.500000;0.750000;,
  0.500000;0.625000;,
  0.500000;0.500000;,
  0.546224;0.375000;,
  0.500000;0.375000;,
  0.500000;0.250000;,
  0.500000;0.125000;,
  0.500000;0.000000;,
  0.451187;0.375000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.125000;0.000000;,
  0.125000;0.250000;;
 }
}
