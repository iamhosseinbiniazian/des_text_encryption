#include<iostream>
#include<stack>
using namespace std;
void CalculateKPlus(int key[64],int kplus[56]);
void COPYKeyCnDn(int Key[16][56],int R1[17][28],int R2[17][28]);
void CalculateBestKey(int key[16][48],int keycdn[16][56]);
void CNDNFIRST(int r[17][28],int r2[17][28],int k[]);
void CalculateCNDN(int CN[17][28],int DN[17][28]);
void RotateCNDN(int cn[17][28],int dn[17][28], int CN[28],int DN[28],int i);
void CopyCNDN(int cndn[17][28],int dndn[17][28],int cn[],int dn[],int i);
void CalculateIp(int ip[64],int m[64]);
void CopyLeftAndRightIP(int r[17][32],int l[17][32],int ip[64]);
void CalculateLeftAndRightForIP(int Right[17][32],int Left[17][32],int key[16][48]);
void XoREAndKey(int Key[16][48],int E[48],int Result[48],int i);
void E_BIT_SELECTION_FUNCTION(int e[48],int r[17][32],int i);
void CopyLeft(int r[17][32],int l[17][32],int i);
void XorLAndf(int l[17][32],int right[17][32],int result[32],int i);
int Xor(int a,int b);
void CalculateSBox(int e[48],int result[32]);
void CalculateBestSbox(int re[8],int result[32]);
void AtachLeftAndRighIP(int Right[17][32],int Left[17][32],int Result[64]);
void CalculateCipherText(int Cipher[64],int Result[64]);
void CreateBinary(char KEY[16],int BinaryKey[64]);
void CreateDecimal(int Ciper[64],char CIPBEST[100000],int indexCIPBEST);
void DES(int KEY[64],char PlainText[100000],char CIPBEST[100000]);
//
void ClculateCnDnFirstForDecryption(int Kplus[56],int SubCn[17][56],int SubDn[17][28]);
void RotateCnDnForDecryption(int SubCn[17][56],int SubDn[17][28]);
void CalculateCnDnForDecryptio(int CnDn[16][56],int SubCn[17][56],int SubDn[17][28]);
void CalculateBestKeyForDecryption(int CnDn[16][56],int Key[16][48]);
void DecryptionOfDes(int KEY[64],char PlainText[100000],char CIPBEST[100000]);
int PC_1[]={57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,10,2,59,
	51,43,35,27,19,11,3,60,52,44,
	36,63,55,47,39,31,23,15,7,62,
	54,46,38,30,22,14,6,61,53,45,
	37,29,21,13,5,28,20,12,4
};
int Permutation_P[32]={
16 ,7 ,20 ,21
,29 ,12 ,28 ,17,
1 ,15 ,23 ,26,
5 ,18 ,31 ,10,
2 ,8 ,24 ,14,
32 ,27 ,3 ,9
,19 ,13 ,30 ,6
,22 ,11 ,4 ,25
};
int Rotate[16]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
int PC_2[]={14,17,11,24,1,5,
            3,28,15,6,21,10,23,19,12,4,26,8,
			16,7,27,20,13,2,
			41,52,31,37,47,55,
			30,40,51,45,33,48,
			44,49,39,56,34,53,
			46,42,50,36,29,32
				};
int S1[4][16]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
		}
,S2[4][16]={
	15 ,1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
3 ,13, 4, 7, 15, 2, 8 ,14, 12, 0, 1, 10, 6, 9, 11, 5,
0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
13 ,8 ,10 ,1 ,3 ,15 ,4 ,2 ,11 ,6 ,7, 12 ,0 ,5 ,14 ,9
}
,S3[4][16]={
	10, 0, 9, 14, 6, 3, 15, 5 ,1 ,13, 12, 7, 11, 4, 2, 8,
13 ,7 ,0 ,9 ,3 ,4 ,6 ,10 ,2 ,8 ,5 ,14 ,12 ,11 ,15 ,1
,13 ,6, 4, 9, 8, 15, 3, 0, 11, 1 ,2, 12, 5, 10, 14, 7,
1 ,10 ,13 ,0 ,6 ,9 ,8 ,7, 4, 15 ,14 ,3 ,11 ,5 ,2 ,12
},S4[4][16]={
	7 ,13, 14 ,3 ,0, 6, 9, 10 ,1, 2, 8, 5, 11, 12, 4, 15,
13 ,8 ,11 ,5 ,6 ,15 ,0 ,3 ,4 ,7 ,2 ,12 ,1 ,10 ,14 ,9
,10, 6, 9, 0, 12, 11, 7 ,13, 15, 1, 3, 14, 5 ,2 ,8, 4,
3 ,15 ,0 ,6 ,10 ,1 ,13 ,8 ,9 ,4 ,5 ,11 ,12 ,7 ,2 ,14
}
,S5[4][16]={
	2 ,12, 4, 1, 7, 10, 11, 6 ,8 ,5 ,3 ,15, 13, 0, 14, 9,
14 ,11 ,2 ,12 ,4 ,7 ,13 ,1 ,5 ,0 ,15 ,10 ,3 ,9, 8 ,6,
4, 2, 1, 11, 10, 13, 7, 8 ,15 ,9 ,12 ,5 ,6 ,3 ,0 ,14,
11 ,8 ,12 ,7 ,1 ,14 ,2 ,13 ,6 ,15 ,0 ,9 ,10 ,4 ,5 ,3
}
,S6[4][16]={
12, 1 ,10 ,15, 9, 2, 6, 8, 0 ,13, 3, 4 ,14, 7, 5, 11,
10 ,15 ,4 ,2 ,7 ,12 ,9 ,5 ,6 ,1 ,13 ,14 ,0 ,11 ,3 ,8
,9 ,14, 15, 5 ,2 ,8 ,12 ,3 ,7 ,0 ,4 ,10 ,1 ,13, 11, 6,
4 ,3 ,2 ,12 ,9 ,5 ,15 ,10 ,11 ,14 ,1 ,7 ,6 ,0 ,8 ,13

}
,S7[4][16]={
4, 11, 2, 14, 15, 0 ,8 ,13 ,3 ,12 ,9 ,7 ,5 ,10 ,6 ,1
,13 ,0 ,11 ,7 ,4 ,9 ,1 ,10 ,14 ,3 ,5 ,12 ,2 ,15 ,8 ,6,
1, 4 ,11 ,13 ,12 ,3 ,7 ,14 ,10 ,15 ,6 ,8 ,0 ,5 ,9 ,2,
6 ,11 ,13 ,8 ,1 ,4 ,10 ,7 ,9 ,5 ,0 ,15 ,14 ,2 ,3 ,12

}
,S8[4][16]={
	13 ,2 ,8 ,4 ,6 ,15 ,11 ,1 ,10 ,9 ,3 ,14 ,5 ,0 ,12 ,7
,1 ,15 ,13 ,8 ,10 ,3 ,7 ,4 ,12 ,5 ,6 ,11 ,0 ,14 ,9 ,2,
7 ,11 ,4 ,1 ,9 ,12 ,14 ,2 ,0 ,6 ,10 ,13 ,15 ,3 ,5 ,8
,2 ,1 ,14 ,7 ,4 ,10 ,8 ,13 ,15 ,12 ,9 ,0 ,3 ,5 ,6 ,11
};
int RESRE[16][4]={0,0,0,0 ,0,0,0,1 ,0,0,1,0 ,0,0,1,1 ,0,1,0,0, 0,1,0,1, 0,1,1,0 ,0,1,1,1, 1,0,0,0,
	1,0,0,1, 1,0,1,0, 1,0,1,1, 1,1,0,0, 1,1,0,1, 1,1,1,0, 1,1,1,1};
int IPINVERSE[64]={
40 ,8 ,48 ,16 ,56 ,24 ,64 ,32,
39 ,7 ,47 ,15 ,55 ,23 ,63 ,31,
38 ,6 ,46 ,14 ,54 ,22 ,62 ,30,
37 ,5 ,45 ,13 ,53 ,21 ,61 ,29,
36 ,4 ,44 ,12 ,52 ,20 ,60 ,28,
35 ,3 ,43 ,11 ,51 ,19 ,59 ,27,
34 ,2 ,42 ,10 ,50 ,18 ,58 ,26,
33 ,1 ,41 ,9 ,49 ,17 ,57 ,25,
};
int E_BIT_SELECTION_TABLE[48]={
	32, 1  ,2 ,3  ,4  ,5
	,4  ,5  ,6 ,7  ,8  ,9
	,8  ,9 ,10 ,11 ,12 ,13
	,12 ,13 ,14 ,15 ,16 ,17
	,16 ,17 ,18 ,19 ,20 ,21
	,20 ,21 ,22 ,23 ,24 ,25
	,24 ,25 ,26 ,27 ,28 ,29
	,28 ,29 ,30 ,31 ,32 ,1
};
static int IP_[]={
	58,50,42,34,26,18,10,2,
	60,52,44,36,28,20,12,4,
	62,54,46,38,30,22,14,6,
	64,56,48,40,32,24,16,8,
	57,49,41,33,25,17,9,1,
	59,51,43,35,27,19,11,3,
	61,53,45,37,29,21,13,5,
	63,55,47,39,31,23,15,7
};
void KeyForDecryption(int Key[16][48],int SubKeyCn[17][28],int SubKeyDn[17][28]){
	int RotateDecryptio[16]={0, 1, 2 ,2 ,2 ,2 ,2 ,2 ,1 ,2 ,2 ,2 ,2 ,2 ,2 ,1 };
	int cn[16][28],dn[16][28],cndnkoli[16][56];
	int index=15;
	for(int i=0;i<28;i++){
		cn[0][i]=SubKeyCn[16][i];
		dn[0][i]=SubKeyDn[16][i];
	}
	for(int i=1;i<16;i++){
		for(int j=0;j<28;j++){
			cn[i][(j+RotateDecryptio[i])%28]=cn[i-1][j];
			dn[i][(j+RotateDecryptio[i])%28]=dn[i-1][j];
		}
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<28;j++){
			cndnkoli[i][j]=cn[i][j];
			cndnkoli[i][j+28]=dn[i][j];
		}
	}
	index=15;
/*for(int i=0;i<16;i++){
		for(int j=0;j<48;j++){
			Key[index][j]=cndnkoli[i][PC_2[j]-1];			
		}
		index-=1;
	}*/
for(int i=0;i<16;i++){
		for(int j=0;j<48;j++){
			Key[i][j]=cndnkoli[i][PC_2[j]-1];			
		}
		//index-=1;
	}
}
void main(){
	char PLainTExt[100000];
	char CIPBEST[100000];
	char a[100000];
	char KEYTEXT[9];
	cout<<"Plaese Enter Plain Text"<<endl;
	gets(PLainTExt);
	cout<<"Please Enter Key Text"<<endl;
	gets(KEYTEXT);
	int strlenn=strlen(PLainTExt);
	while(strlenn%8){
		PLainTExt[strlenn]=' ';
		PLainTExt[strlenn+1]='\0';
		 strlenn=strlen(PLainTExt);
	}
	int BinaryKey[64];//={0,0,0,1,0,0,1,1 ,0,0,1,1,0,1,0,0, 0,1,0,1,0,1,1,1, 0,1,1,1,1,0,0,1, 
		              // 1,0,0,1,1,0,1,1, 1,0,1,1,1,1,0,0, 1,1,0,1,1,1,1,1, 1,1,1,1,0,0,0,1};
	CreateBinary(KEYTEXT,BinaryKey);
		DES(BinaryKey,PLainTExt,CIPBEST);
		cout<<"Ciper is :"<<CIPBEST<<endl;
		cin.get();
		DecryptionOfDes(BinaryKey,CIPBEST,a);
			cout<<"Plain is"<<a;
		cin.get();
}
void CreateDecimal(int Ciper[64],char CIPBEST[100000],int indexCIPBEST){
	int m=indexCIPBEST;
	int f[8];
	int h=0;
	cout<<"in DEcimal"<<endl;
	for(int i=0;i<64;i=i+8){
		f[0]=Ciper[i];
		f[1]=Ciper[i+1];
		f[2]=Ciper[i+2];
		f[3]=Ciper[i+3];
		f[4]=Ciper[i+4];
		f[5]=Ciper[i+5];
		f[6]=Ciper[i+6];
		f[7]=Ciper[i+7];
		h=128*f[0]+64*f[1]+32*f[2]+16*f[3]+8*f[4]+4*f[5]+2*f[6]+f[7];
		CIPBEST[m]=h;
		cout<<CIPBEST[m]<<"="<<h<<endl;
		CIPBEST[m+1]='\0';
		m++;
	}
}
void DES(int BinaryKey[64],char PlainText[100000],char CIPBEST[100000]){
	int SubKeyCn[17][28];
	int SubKeyDn[17][28];
	int KeyPlus[56];
	int KeyCNDN[16][56];
	int Key[16][48];
	int IPM[64];
	int RightIP[17][32],LeftIp[17][32];
	int Result[64],CipherText[64];
	int BinaryPlain[64];
	int IndexPain=0;
	int indexCIPBEST=0;
	char TXT[8];
	CalculateKPlus(BinaryKey,KeyPlus);
	CNDNFIRST(SubKeyCn,SubKeyDn,KeyPlus);
	CalculateCNDN(SubKeyCn,SubKeyDn);
	COPYKeyCnDn(KeyCNDN,SubKeyCn,SubKeyDn);
	CalculateBestKey(Key,KeyCNDN);
	while(PlainText[IndexPain]){
		for(int ind=0;ind<8;ind++){
		TXT[ind]=PlainText[IndexPain];
		IndexPain++;
		}
		CreateBinary(TXT,BinaryPlain);
	CalculateIp(IPM,BinaryPlain);
	CopyLeftAndRightIP(RightIP,LeftIp,IPM);
	CalculateLeftAndRightForIP(RightIP,LeftIp,Key);
	AtachLeftAndRighIP(RightIP,LeftIp,Result);
	CalculateCipherText(CipherText,Result);
	CreateDecimal(CipherText,CIPBEST,indexCIPBEST);
	indexCIPBEST+=8;
	}
		
	

}
void CreateBinary(char KEY[8],int BinaryKey[64]){
	 unsigned char ch;
	int FOUR[8];
	int k=0;
	int Index=0;
	cout<<"in binary"<<endl;
	for(int i=0;i<8;i++){
		k=0;
		ch=KEY[i];
		cout<<KEY[i]<<"="<<(int)ch<<endl;
		for(int h=0;h<8;h++)
			FOUR[h]=0;
		while(ch){
			FOUR[k]=ch%2;
			ch=ch/2;
			k++;
		}
		for(int f=7;f>=0;f--){
			BinaryKey[Index]=FOUR[f];
			Index++;
		}
	}
}
void CalculateCipherText(int Cipher[64],int Result[64]){
	for(int i=0;i<64;i++){
	Cipher[i]=Result[(IPINVERSE[i]-1)];
	}
}
void AtachLeftAndRighIP(int Right[17][32],int Left[17][32],int Result[64]){
	for(int i=0;i<32;i++){
	Result[i]=Right[16][i];
	Result[i+32]=Left[16][i];
	}
}
void CopyLeftAndRightIP(int r[17][32],int l[17][32],int ip[64]){
	for(int i=0;i<32;i++){
		l[0][i]=ip[i];
		r[0][i]=ip[i+32];
	}
}
void CalculateLeftAndRightForIP(int Right[17][32],int Left[17][32],int key[16][48]){

	int E[48];
	int XorEAndKn[48];
	int Sbox[32];
	for(int i=1;i<17;i++){
		CopyLeft(Right,Left,i);
		E_BIT_SELECTION_FUNCTION(E,Right,i);
		XoREAndKey(key,E,XorEAndKn,i);//result=xoreankey
		CalculateSBox(XorEAndKn,Sbox);
		XorLAndf(Left,Right,Sbox,i);
		//SUMOfTWoBinaryNumber(Left,Right,Sbox,i);
	}
}
void XorLAndf(int l[17][32],int right[17][32],int result[32],int i){
	for(int j=0;j<32;j++){
		right[i][j]=Xor(l[i-1][j],result[j]);
	}
	/*for(int j=0;j<32;j++){
		cout<<right[i][j];
	}
	cin.get();*/


}
void CalculateSBox(int e[48],int result[32]){
	int f[6];
	int kk=0;
	int RE[8];
	int iii,kkk;
	for(int j=0;j<48;j=j+6){
		iii=0;
		kkk=0;
		f[0]=e[j];
		f[1]=e[j+1];
		f[2]=e[j+2];
		f[3]=e[j+3];
		f[4]=e[j+4];
		f[5]=e[j+5];
		iii=f[0]*2+f[5];
		kkk=f[1]*8+f[2]*4+f[3]*2+f[4];
		if(j==0){
			RE[kk]=S1[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S1[iii][kkk]<<endl;
			kk++;
			
		}
		else if(j>=6&&j<12){
		RE[kk]=S2[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S2[iii][kkk]<<endl;
			kk++;
		}
		else if(j>=12&&j<18){
		RE[kk]=S3[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S3[iii][kkk]<<endl;
			kk++;
		}
		else if(j>=18&&j<24){
		RE[kk]=S4[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S4[iii][kkk]<<endl;
			kk++;
		}
		else if(j>=24&&j<30){
		RE[kk]=S5[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S5[iii][kkk]<<endl;
			kk++;
		}
		else if(j>=30&&j<36){
		RE[kk]=S6[iii][kkk];
				//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S6[iii][kkk]<<endl;
			kk++;
		}
		else if(j>=36&&j<42){
		RE[kk]=S7[iii][kkk];
			//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S7[iii][kkk]<<endl;
			kk++;
		}
		else{
		RE[kk]=S8[iii][kkk];
				//cout<<RE[kk]<<" "<<iii<<" "<<kkk<<" "<<S8[iii][kkk]<<endl;
			kk++;
		}
	}
	//cin.get();
	CalculateBestSbox(RE,result);
}
void CalculateBestSbox(int re[8],int result[32]){
	int k=0;
	int kk=0;
	int res[32];
	/*for(int i=0;i<8;i++){
	 cout<<i<<"="<<re[i];
	cout<<"\n";
	}*/
	int m=0;
	int Four[4];
	for(int i=0;i<8;i++){
	//	cout<<"RE["<<i<<"]"<<"="<<re[i]<<endl;
			kk=0;
			m=re[i];
			for(int l=0;l<4;l++){
				Four[l]=RESRE[m][l];
			}
		for(int j=0;j<4;j++){
		res[k]=Four[j];
		k++;
		}

}
	/*cout<<"THIS IS A RE RESULT"<<endl;
		
	/*for(int i=0;i<32;i++)
	{
		cout<<res[i];
	}
	cin.get();*/

	for(int i=0;i<32;i++){
		result[i]=res[Permutation_P[i]-1];
	}
/*	for(int i=0;i<32;i++){
		cout<<result[i];
	}
	cin.get();*/
}
void XoREAndKey(int Key[16][48],int E[48],int Result[48],int i){
/*	cout<<"This is XOR E AND F"<<" "<<i<<endl;
	cout<<"This is a key"<<" "<<i<<endl;
		for(int k=0;k<48;k++){
			cout<<Key[i-1][k];
		}
		cout<<endl;
		cout<<"This is a E"<<endl;
		for(int k=0;k<48;k++){
			cout<<E[k];
	}*/
		//cout<<endl;
	for(int j=0;j<48;j++){
		Result[j]=Xor(E[j],Key[i-1][j]);
	}
/*	for(int k=0;k<48;k++){
	cout<<Result[k];
	}
	cin.get();*/
}
int Xor(int a,int b){
return(a ^ b);
}
void CopyLeft(int r[17][32],int l[17][32],int i){
	for(int j=0;j<32;j++){
		l[i][j]=r[i-1][j];
	}
}
void E_BIT_SELECTION_FUNCTION(int e[48],int r[17][32],int i){
//cout<<"This is a E_BIT_SELECTION_FUNCTION"<<" "<<i<<endl;
	for(int j=0;j<48;j++){
		e[j]=r[i-1][E_BIT_SELECTION_TABLE[j]-1];
	}
	/*for(int k=0;k<48;k++)
		cout<<e[k];
	cin.get();*/
}
void CalculateIp(int ip[64],int m[64]){
	for(int i=0;i<64;i++){
		ip[i]=m[IP_[i]-1];
	}
}
void CalculateBestKey(int key[16][48],int keycdn[16][56]){
	for(int i=0;i<16;i++){
		for(int j=0;j<48;j++){
			key[i][j]=keycdn[i][PC_2[j]-1];
		}
	}
}
void COPYKeyCnDn(int Key[16][56],int R1[17][28],int R2[17][28]){
	for(int i=0;i<16;i++){
		for(int j=0;j<28;j++){
			Key[i][j]=R1[i+1][j];
			Key[i][j+28]=R2[i+1][j];
		}
	}
}
void CalculateCNDN(int CN[17][28],int DN[17][28]){
	int Cn[28], Dn[28];
	for(int i=1;i<17;i++){
		CopyCNDN(CN,DN,Cn,Dn,i-1);
		RotateCNDN(CN,DN,Cn,Dn,i);
	}
}
void RotateCNDN(int cn[17][28],int dn[17][28], int CN[28],int DN[28],int i){

	for(int j=0;j<28;j++){
		cn[i][j]=CN[(j+Rotate[i-1])%28];
		dn[i][j]=DN[(j+Rotate[i-1])%28];
	}
		
}
void CopyCNDN(int cndn[17][28],int dndn[17][28],int cn[],int dn[],int i){
	for(int j=0;j<28;j++){
	cn[j]=cndn[i][j];
	dn[j]=dndn[i][j];
	}
}

void CNDNFIRST(int r[17][28],int r2[17][28],int k[]){
	for(int i=0;i<28;i++){
			r[0][i]=k[i];
	}
	for(int i=0;i<28;i++){
			r2[0][i]=k[i+28];
	}
}
void CalculateKPlus(int key[64],int kplus[56]){
	for(int i=0;i<56;i++){
		kplus[i]=key[PC_1[i]-1];
	}
}
void ClculateCnDnFirstForDecryption(int Kplus[56],int SubCn[17][28],int SubDn[17][28]){
	for(int j=0;j<28;j++){
		SubCn[1][j]=Kplus[j];
		SubDn[1][j]=Kplus[j+28];
	}
}
void RotateCnDnForDecryption(int SubCn[17][28],int SubDn[17][28]){
	for(int i=1;i<16;i++){
		for(int j=0;j<28;j++){
			SubCn[i+1][(j+Rotate[i])%28]=SubCn[i][j];
			SubDn[i+1][(j+Rotate[i])%28]=SubDn[i][j];
		}
	}

}
void CalculateCnDnForDecryptio(int CnDn[16][56],int SubCn[17][28],int SubDn[17][28]){

	for(int i=0;i<16;i++){
		for(int j=0;j<28;j++){
			CnDn[i][j]=SubCn[i+1][j];
			CnDn[i][j+28]=SubDn[i+1][j];
		}
	}
	for(int i=0;i<16;i++){
		for(int j=0;j<28;j++){
			cout<<CnDn[i][j]<<" ";
		}
		cout<<endl;
	}
}
void CalculateBestKeyForDecryption(int CnDn[16][56],int Key[16][48]){
int m=15;
for(int i=0;i<16;i++){
	for(int j=0;j<48;j++){
		Key[i][j]=CnDn[i][PC_2[j]-1];
	}
	//m--;
}
}
void DecryptionOfDes(int BinaryKey[64],char PlainText[100000],char CIPBEST[100000]){
	int SubKeyCn[17][28];
	int SubKeyDn[17][28];
	int KeyPlus[56];
	int KeyCNDN[16][56];
	int Key[16][48];
	int IPM[64];
	int RightIP[17][32],LeftIp[17][32];
	int Result[64],CipherText[64];
	int BinaryPlain[64];
	int IndexPain=0;
	int indexCIPBEST=0;
	char TXT[8];
	cout<<"IN DECRYPT"<<endl;
	CalculateKPlus(BinaryKey,KeyPlus);
	CNDNFIRST(SubKeyCn,SubKeyDn,KeyPlus);
	CalculateCNDN(SubKeyCn,SubKeyDn);
	KeyForDecryption(Key,SubKeyCn,SubKeyDn);
	while(PlainText[IndexPain]){
		for(int ind=0;ind<8;ind++){
		TXT[ind]=PlainText[IndexPain];
		cout<<TXT[ind]<<"="<<((unsigned int)TXT[ind]%255)<<endl;
		IndexPain++;
		}
		CreateBinary(TXT,BinaryPlain);
	CalculateIp(IPM,BinaryPlain);
	CopyLeftAndRightIP(RightIP,LeftIp,IPM);
	CalculateLeftAndRightForIP(RightIP,LeftIp,Key);
	AtachLeftAndRighIP(RightIP,LeftIp,Result);
	CalculateCipherText(CipherText,Result);
	CreateDecimal(CipherText,CIPBEST,indexCIPBEST);
	indexCIPBEST+=8;
	}
		
	
	


}