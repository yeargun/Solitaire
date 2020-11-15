#include <iostream>
#include <fstream>
#include <string>
#include<typeinfo>
#include<cstdlib>
using namespace std;


string hearts[13]={"H01","H02","H03","H04","H05","H06","H07","H08","H09","H10",
"H11","H12","H13"};
string diamonds[13]={"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10",
"D11","D12","D13"};
string clubs[13]={"C01","C02","C03","C04","C05","C06","C07","C08","C09","C10",
"C11","C12","C13"};
string spades[13]={"S01","S02","S03","S04","S05","S06","S07","S08","S09","S10",
"S11","S12","S13"};

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
		
		int pilesMaxLayerNumber(pile* piles){
			int max  = 0;
			for(int i = 0;i<7;i++){
				if(piles[i].topIndex > max){
					max=piles[i].topIndex;
				}
			}
			return max;
		}		
};


int indexOf(string card){
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

bool strCompare(string s1, string s2,int compareLength){
	for(int i=0;i<compareLength;i++){
		if(s1[i]!=s2[i]){
			return false;
		}
	}
	return true;
}

class foundation{
	public:
		string cards[13];
		int topIndex=1;
		string moveToFoundation(string card, foundation* foundations){
		
			if(card[0]=='H' && indexOf(card)==foundations[0].topIndex){
				foundations[0].cards[foundations[0].topIndex+1]=card;
				foundations[0].topIndex++;
				return "legal";
			}
			else if(card[0]=='D' && indexOf(card)==foundations[0].topIndex){
				foundations[1].cards[foundations[1].topIndex+1]=card;
				foundations[1].topIndex++;
				return "legal";
			}
			else if(card[0]=='S' && indexOf(card)==foundations[0].topIndex){
				foundations[2].cards[foundations[2].topIndex+1]=card;
				foundations[2].topIndex++;
				return "legal";
			}
			else if(card[0]=='C' && indexOf(card)==foundations[0].topIndex){
				foundations[3].cards[foundations[3].topIndex+1]=card;
				foundations[3].topIndex++;
				return "legal";
			}
		}
		
};

string pileToFoundation(pile pile1, foundation* foundations){
			/*if(pile1.cards[pile1.topIndex-1][0]=="H" && pile1.topIndex==foundations[0].topIndex){
				foundations[0].cards[foundations[0].topIndex+1]=pile1.cards[pile1.topIndex-1];
				foundations[0].topIndex++;
				return "legal";
			}
			else if(pile1.cards[pile1.topIndex-1][0]=="D" && pile1.topIndex==foundations[0].topIndex){
				foundations[1].cards[foundations[1].topIndex+1]=pile1.cards[pile1.topIndex-1];
				foundations[1].topIndex++;
				return "legal";
			}
			else if(pile1.cards[pile1.topIndex-1][0]=="S" && pile1.topIndex==foundations[0].topIndex){
				foundations[2].cards[foundations[2].topIndex+1]=pile1.cards[pile1.topIndex-1];
				foundations[2].topIndex++;
				return "legal";
			}
			else if(pile1.cards[pile1.topIndex-1][0]=="C" && pile1.topIndex==foundations[0].topIndex){
				foundations[3].cards[foundations[3].topIndex+1]=pile1.cards[pile1.topIndex-1];
				foundations[3].topIndex++;
				return "legal";
			}*/
			return "illegal";
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

void displayTable(pile* piles,waste waste,foundation* foundations){
	//cout<<endl<<"@@@ ___ ___ ___         ___ ___ ___ ___"<<endl<<endl;
	cout<<endl<<"@@@ "; waste.displayWaste();
	cout<<"        "<<foundations[0].cards[foundations[0].topIndex-1]<<" "<<
	foundations[1].cards[foundations[1].topIndex-1]<<" "<<
	foundations[2].cards[foundations[2].topIndex-1]<<" "<<
	foundations[3].cards[foundations[3].topIndex-1]<<" \n\n";
	for(int i = 0;i<piles->pilesMaxLayerNumber(piles);i++){
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
	}
}

int main(){
	string deck[52];
	pile piles[7];
	foundation foundations[4];
	stock stock;
	waste waste;
	string command;
	string tempCard;
	int tempIndex;

	readDeck("deck.txt",deck);
	setTable(deck, piles, stock);
	
	displayTable(piles, waste,foundations);
	ifstream commandFile;
	commandFile.open("commands.txt");
	
	if (!commandFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    foundations[0].cards[0]="H11";
    foundations[1].cards[0]="D11";
    foundations[2].cards[0]="S11";
    foundations[3].cards[0]="C11";
    cout<<indexOf("H11");
	for( command; getline( commandFile, command ); ){

		cout<<"\n"<<command<<endl;
		
    	
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
			tempIndex=(int)command[24] - 48;
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
	
	
	return 0;
}
