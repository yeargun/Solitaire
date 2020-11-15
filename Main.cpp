#include <iostream>
#include <fstream>
#include <string>
#include<typeinfo>
#include<cstdlib>
using namespace std;
bool strCompare(string s1, string s2,int compareLength){
	for(int i=0;i<compareLength;i++){
		if(s1[i]!=s2[i]){
			return false;
		}
	}
	return true;
}
string hearts[13]={"H01","H02","H03","H04","H05","H06","H07","H08","H09","H10","H11","H12","H13"};
string diamonds[13]={"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13"};
string clubs[13]={"C01","C02","C03","C04","C05","C06","C07","C08","C09","C10","C11","C12","C13"};
string spades[13]={"S01","S02","S03","S04","S05","S06","S07","S08","S09","S10","S11","S12","S13"};
int indexOf(string card){  //indexOf("H11")=10 
	if(card[0]=='H'){
		for(int i=0;i<13;i++){
			if(hearts[i]==card){
				return i;
			}
		}
	}
	else if(card[0]=='D'){
		for(int i=0;i<13;i++){
			if(diamonds[i]==card){
				return i;
			}
		}
	}
	else if(card[0]=='S'){
		for(int i=0;i<13;i++){
			if(spades[i]==card){
				return i;
			}
		}
	}
	else if(card[0]=='C'){
		for(int i=0;i<13;i++){
			if(clubs[i]==card){
				return i;
			}
		}
	}
}

class stock{
	public:
		string cards[25]={""};
};

void wasteToFoundation(){
}

void wasteToPile(){
	
}
class pile{
	public:
		string cards[19][2];
		int topIndex=0;
		void addToPileDownward(string Card){
			cards[topIndex][0]=Card;
			cards[topIndex][1]="0";
			topIndex++;
		}
		void addToPileUpward(string Card){
			cards[topIndex][0]=Card;
			cards[topIndex][1]="1";
			topIndex++;
		}
		void addToPileUpwardMultiple(string* Cards){
			for(int i = 0;i<sizeof(Cards)/sizeof(Cards[0]);i++){
				addToPileUpward(Cards[i]);
			}	
		}
		void deleteTopmost(){
			cards[topIndex-1][0]="";
			topIndex--;
			cout<<	"ntered the deleetetopmost function tho";
		}
		
		int pilesMaxLayerNumber(pile* piles){
			int max  = 0;
			for(int i = 0;i<7;i++){
				if(piles[i].topIndex > max){
					max=piles[i].topIndex;
				}
			}
			return max;
		}
		
		void displayPiles(pile* piles){
			int maxTopIndex=1;
			for(int j = 0; j<maxTopIndex;j++){
				for(int i = 0; i<7;i++){
					if(piles[i].topIndex>maxTopIndex){
								maxTopIndex=piles[i].topIndex;}
					if(piles[i].cards[j][0]!=""&& piles[i].cards[j][1]=="1"){ //if card layed upward 
						cout<<piles[i].cards[j][0]<<"   ";
					}
					else if(piles[i].cards[j][0]!=""){
						cout<<"@@@   ";
					}
					else{
						cout<<"      ";
					}
				}
				cout<<endl;
			}
		}		
};

class foundation{
	public:
		string cards[4][12];
		int topIndex0=0;
		int topIndex1=0;
		int topIndex2=0;
		int topIndex3=0;
		void getPile0(string card, foundation foundations){
			foundations.cards[0][topIndex0]=card;
			topIndex0++;
		}
		void getPile1(string card, foundation foundations){
			foundations.cards[1][topIndex1]=card;
			topIndex1++;
		}
		void getPile2(string card, foundation foundations){
			foundations.cards[2][topIndex2]=card;
			topIndex2++;
		}
		void getPile3(string card, foundation foundations){
			foundations.cards[3][topIndex3]=card;
			topIndex3++;
		}
		void displayFoundations(){
			if(topIndex0!=0){
				cout<<cards[0][topIndex0-1]<<" ";
			}else{cout<<"___ ";}
			
			if(topIndex1!=0){
				cout<<cards[1][topIndex1-1]<<" ";
			}else{cout<<"___ ";}
			
			if(topIndex2!=0){
				cout<<cards[2][topIndex2-1]<<" ";
			}else{cout<<"___ ";}
			
			if(topIndex3!=0){
				cout<<cards[3][topIndex3-1]<<" ";
			}else{cout<<"___ ";}
			
		}
};

void pileToFoundation(pile pile, foundation foundations){
			if(pile.cards[pile.topIndex-1][0][0]=='H' && indexOf(pile.cards[pile.topIndex-1][0]) == foundations.topIndex0){
				foundations.getPile0(pile.cards[pile.topIndex-1][0], foundations);
				pile.deleteTopmost();
			}
			else if(pile.cards[pile.topIndex-1][0][0] =='D' && indexOf(pile.cards[pile.topIndex-1][0]) == foundations.topIndex1){
				foundations.getPile1(pile.cards[pile.topIndex-1][0], foundations );
				pile.deleteTopmost();
			}
			else if(pile.cards[pile.topIndex-1][0][0] =='S' && indexOf(pile.cards[pile.topIndex-1][0]) == foundations.topIndex2){
				foundations.getPile2(pile.cards[pile.topIndex-1][0], foundations );
				pile.deleteTopmost();
			}
			else if(pile.cards[pile.topIndex-1][0][0] =='C' && indexOf(pile.cards[pile.topIndex-1][0]) == foundations.topIndex3){
				foundations.getPile3(pile.cards[pile.topIndex-1][0], foundations );
				pile.deleteTopmost();
			}
			else{
				cout<<	"not any of them\n";
			}
}

class waste{
	public:
		string cards[3]={""};
		
	void displayWaste(){
		for(int i = 0;i<3;i++){
			if(cards[i]==""){
				cout<<"___ ";
			}
			else{
				cout<< cards[i]<<" ";
			}
		}
	}
};




void readDeck(string path, string deck[52]){
	int i=0;
	ifstream deckFile;
	deckFile.open(path.c_str());
	string x;
	if (!deckFile) {
        std::cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while(i<52){
    	deckFile>>deck[i];
		i++;
	}
    deckFile.close();
}

void setTable(string* deck, pile* piles,stock stock){
	int j=0;
	int layer=0;
	int pileNumber = 0;
	for(j=0;j<=27;j++){
		if(layer==pileNumber){
			piles[pileNumber].addToPileUpward(deck[51-j]);
		}
		else if(layer<pileNumber){
			piles[pileNumber].addToPileDownward(deck[51-j]);	
		}
		pileNumber++;
		if(pileNumber==7){
			layer++;
			pileNumber=layer;;
		}	
		if(layer==7){
			for(int i=0;i<24;i++){
				stock.cards[i]=deck[i];
		}
		stock.cards[24]="23";
		break;
	}
	}
}

void displayTable(pile* piles,waste waste,foundation foundations){
	//cout<<endl<<"@@@ ___ ___ ___         ___ ___ ___ ___"<<endl<<endl;
	cout<<endl<<"@@@ "; waste.displayWaste();
	cout<<"        ";
	foundations.displayFoundations();
	cout<<endl<<endl;
	piles[0].displayPiles(piles);
	/*for(int i = 0;i<piles->pilesMaxLayerNumber(piles);i++){
		for(int j =0;j<7;j++){
			if(piles[j].cards[i][1]=="1"){
				cout<<piles[j].cards[i][0]<<"   ";
			}
			else if(piles[j].cards[i][0]!=""){
				cout<<"@@@   ";
			}
			else{
				cout<<"      ";
			}
		}
		cout<<endl;
	}*/
	
}

int main(){
	string deck[52];
	pile piles[7];
	foundation foundations;
	stock stock;
	waste waste;
	string command;
	string tempCard;
	int tempPileIndex;

	readDeck("deck.txt",deck);
	setTable(deck, piles, stock);
	
	displayTable(piles, waste,foundations);
	ifstream commandFile;
	commandFile.open("commands.txt");
	
	if (!commandFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    cout<<indexOf("H11");
	for( command; getline( commandFile, command ); ){

		cout<<"\n"<<command<<endl;
		cout<<endl<<"****************************************"<<endl;
		
    	
    	if(strCompare(command,"open",4)){ //
			cout<<"OPEN";
		}
		else if(strCompare(command,"move p",6)){
    		cout<<"bruh i moved pile";
		}
		else if(strCompare(command,"move to foundation w",20)){ //
		//	foundations.moveToFoundation(piles[stoi(command[24)]].cards[piles[stoi(command[24])].topIndex], foundations)
		}
		else if(strCompare(command,"move to foundation p",20)){ //
			tempPileIndex=(int)command[24] - 48;
			pileToFoundation(piles[tempPileIndex], foundations);
		
		//	if(pileToFoundation(piles[tempIndex], foundations)){
			//	piles[tempIndex].cards[topIndex]="";
			//	piles[tempIndex].topIndex--;
			//}
			//cout<<"TEMP INDEXCHECK THIS "<<piles[tempIndex].topIndex<<endl;
		//	tempCard=piles[tempIndex].cards[piles[tempIndex].topIndex];
		//cout<<foundations[0].moveToFoundation(tempCard , foundations);
		}
		else if(strCompare(command,"move w",6)){ //
			cout<<"WASTE move";
		}
		else if(strCompare(command,"open f",6)){ //
			cout<<"open from stock";
		}
		else if(strCompare(command,"exit",4)){ //
			cout<<"I GOEXIT YES";
		}
		
    	displayTable(piles, waste,foundations);
	}
	
//	cout<<"asdgadga  |"<<piles[0].cards[0][0];
	
//	pileToFoundation(piles[6],foundations);
//	cout<<"asdgadga  |"<<piles[6].cards[6][0];
		piles[6].deleteTopmost();
		displayTable(piles,waste,foundations);
		cout<<piles[6].topIndex;
		piles[6].deleteTopmost();
		displayTable(piles,waste,foundations);
		cout<<piles[6].topIndex;
	
	
	return 0;
}
