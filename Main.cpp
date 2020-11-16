#include <iostream>
#include <fstream>
#include <string>
#include<typeinfo>
#include<cstdlib>
using namespace std;
bool strCompare(string s1, string s2,int compareLength){
	if(compareLength>s1.length() || compareLength>s2.length()){return false;}
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
bool colorRule(string s1, string s2){
	if( ((s1[0]=='C' || s1[0]=='S') && (s2[0]=='H' || s2[0]=='D')) 
	||	((s1[0]=='H' || s1[0]=='D') && (s2[0]=='C' || s2[0]=='S'))	) {
		return true;
	}
}

bool magnitudeRule(string s1, string s2){//if magnitude s1+1=s2 return true
	if(indexOf(s1)+1==indexOf(s2)){
	return true;}
	else return false;
}

class stock{
	public:
		string cards[24]={""};
		int topIndex=-1;
};
class waste{
	public:
		string cards[3]={""};
		int topIndex=-1;
		string oldWaste[24]={""};
		int oldWasteTopIndex=0;
		
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
		void openPile(pile* pile){
			if(pile->topIndex==0){
				cout<<"Error, you cant open anything!";
			}
			else if(pile->cards[pile->topIndex-1][1]=="1"){
				cout<<"Error, you cant open anything!";
			}
			else{
				pile->cards[pile->topIndex-1][1]="1";
			}
			
			
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
		void getPile0(string card, foundation* foundations){
			foundations->cards[0][topIndex0]=card;
			topIndex0++;
		}
		void getPile1(string card, foundation* foundations){
			foundations->cards[1][topIndex1]=card;
			topIndex1++;
		}
		void getPile2(string card, foundation* foundations){
			foundations->cards[2][topIndex2]=card;
			topIndex2++;
		}
		void getPile3(string card, foundation* foundations){
			foundations->cards[3][topIndex3]=card;
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

void wasteToFoundation(waste* waste1,foundation* foundation1, stock* stock1){
	string topmostCard=waste1->cards[waste1->topIndex];
	if(topmostCard[0]=='H'){
		if(foundation1->cards[0][foundation1->topIndex0]=="" && topmostCard=="H01"){
			foundation1->cards[0][foundation1->topIndex0] = topmostCard;
			foundation1->topIndex0++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
		else if(magnitudeRule(foundation1->cards[0][foundation1->topIndex0],topmostCard)) {
			foundation1->cards[0][foundation1->topIndex0] = topmostCard;
			foundation1->topIndex0++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
	}
	else if(topmostCard[0]=='D'){
		if(foundation1->cards[1][foundation1->topIndex1]=="" && topmostCard=="D01"){
			foundation1->cards[1][foundation1->topIndex1] = topmostCard;
			foundation1->topIndex1++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
		else if(magnitudeRule(foundation1->cards[1][foundation1->topIndex1],topmostCard)) {
			foundation1->cards[1][foundation1->topIndex1] = topmostCard;
			foundation1->topIndex1++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
	}
	else if(topmostCard[0]=='S'){
		if(foundation1->cards[2][foundation1->topIndex2]=="" && topmostCard=="S01"){
			foundation1->cards[2][foundation1->topIndex2] = topmostCard;
			foundation1->topIndex2++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
		else if(magnitudeRule(foundation1->cards[2][foundation1->topIndex2],topmostCard)) {
			foundation1->cards[2][foundation1->topIndex2] = topmostCard;
			foundation1->topIndex2++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
	}
	else if(topmostCard[0]=='C'){
		if(foundation1->cards[3][foundation1->topIndex3]=="" && topmostCard=="C01"){
			foundation1->cards[3][foundation1->topIndex3] = topmostCard;
			foundation1->topIndex3++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
		else if(magnitudeRule(foundation1->cards[3][foundation1->topIndex3],topmostCard)) {
			foundation1->cards[3][foundation1->topIndex3] = topmostCard;
			foundation1->topIndex3++;
			waste1->cards[waste1->topIndex]="";
			waste1->topIndex--;
		}
	}
	if(waste1->topIndex==-1 && waste1->oldWasteTopIndex!=0){
		waste1->topIndex++;
		waste1->cards[0]=waste1->oldWaste[waste1->oldWasteTopIndex-1];
		waste1->oldWaste[waste1->oldWasteTopIndex-1]="";
		waste1->oldWasteTopIndex--;
	}
}

void wasteToPile(waste* waste1, pile* pile1, stock* stock1){
	if(waste1->topIndex==-1){
		cout<< "MAN WTF WASTE IS EMPTY";
	}
	else if(indexOf(waste1->cards[waste1->topIndex])==12 && pile1->topIndex==0){ //if King to empty pile
		pile1->cards[pile1->topIndex][0] = waste1->cards[waste1->topIndex];
		pile1->cards[pile1->topIndex][1]="1";
		waste1->cards[waste1->topIndex]="";
		waste1->topIndex--;
		pile1->topIndex++;
	}
	else if(magnitudeRule(waste1->cards[waste1->topIndex], pile1->cards[pile1->topIndex-1][0]) &&
			colorRule(waste1->cards[waste1->topIndex], pile1->cards[pile1->topIndex-1][0])){
				pile1->cards[pile1->topIndex][0] = waste1->cards[waste1->topIndex];
				pile1->cards[pile1->topIndex][1]="1";
				waste1->cards[waste1->topIndex]="";
				waste1->topIndex--;
				pile1->topIndex++;
	}
	if(waste1->topIndex==-1 && waste1->oldWasteTopIndex!=0){
		waste1->topIndex++;
		waste1->cards[0]=waste1->oldWaste[waste1->oldWasteTopIndex-1];
		waste1->oldWaste[waste1->oldWasteTopIndex-1]="";
		waste1->oldWasteTopIndex--;
	}
}




void pileToFoundation(pile* pile, foundation* foundations){
			if(pile->cards[pile->topIndex-1][0][0]=='H' && indexOf(pile->cards[pile->topIndex-1][0]) == foundations->topIndex0){
				foundations->getPile0(pile->cards[pile->topIndex-1][0], foundations);
				pile->deleteTopmost();
			}
			else if(pile->cards[pile->topIndex-1][0][0] =='D' && indexOf(pile->cards[pile->topIndex-1][0]) == foundations->topIndex1){
				foundations->getPile1(pile->cards[pile->topIndex-1][0], foundations );
				pile->deleteTopmost();
			}
			else if(pile->cards[pile->topIndex-1][0][0] =='S' && indexOf(pile->cards[pile->topIndex-1][0]) == foundations->topIndex2){
				foundations->getPile2(pile->cards[pile->topIndex-1][0], foundations );
				pile->deleteTopmost();
			}
			else if(pile->cards[pile->topIndex-1][0][0] =='C' && indexOf(pile->cards[pile->topIndex-1][0]) == foundations->topIndex3){
				foundations->getPile3(pile->cards[pile->topIndex-1][0], foundations );
				pile->deleteTopmost();
			}
			else{
				cout<<	"not any of them\n";
			}
}


void pileToPile(pile* pile1, pile* pile2, int endingIndex){
	int startingIndex=pile1->topIndex-(endingIndex+1);
	if(startingIndex<0 || pile1->cards[startingIndex][1]=="0"){
		cout<<"You cant move empty piles element\n";
	}
	else if(indexOf(pile1->cards[startingIndex][0])==12 && pile2->topIndex==0){//You can add any King card to any empty pile
		for(int i=0;i<=endingIndex;i++){
			pile2->cards[pile2->topIndex][0]=pile1->cards[startingIndex+i][0];
			pile2->cards[pile2->topIndex][1]="1";
			pile2->topIndex++;
			pile1->cards[startingIndex+i][0]="";
			pile1->topIndex--;
		}
	}
	else if(colorRule(pile1->cards[startingIndex][0],pile2->cards[pile2->topIndex-1][0]) &&
			magnitudeRule(pile1->cards[startingIndex][0],pile2->cards[pile2->topIndex-1][0])){
				for(int i=0;i<=endingIndex;i++){
					pile2->cards[pile2->topIndex][0]=pile1->cards[startingIndex+i][0];
					pile2->cards[pile2->topIndex][1]="1";
					pile2->topIndex++;
					pile1->cards[startingIndex+i][0]="";
					pile1->topIndex--;
				}		
			}
}






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

void setTable(string* deck, pile* piles,stock* stock){
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
				stock->cards[i]=deck[i];
		}
		stock->topIndex=23;
		break;
	}
	}
}

void displayTable(pile* piles,waste waste,foundation foundations,stock stock){
	//cout<<endl<<"@@@ ___ ___ ___         ___ ___ ___ ___"<<endl<<endl;
	if(stock.topIndex==-1){
		cout<<endl<<"___ ";waste.displayWaste();
	}
	else{
		cout<<endl<<"@@@ "; waste.displayWaste();
	}
	
	cout<<"        ";
	foundations.displayFoundations();
	cout<<endl<<endl;
	piles[0].displayPiles(piles);

}
void gatherTheStock(stock* stock1, waste* waste1){
	int i = 0;
	int j=0;
	for(i = 0; i<=waste1->topIndex;i++){
		stock1->cards[i]=waste1->cards[2-waste1->topIndex];
		waste1->cards[2-waste1->topIndex]="";
		stock1->topIndex++;
	}
	waste1->topIndex=-1;
	for(; j<waste1->oldWasteTopIndex;j++){
		stock1->cards[i]=waste1->oldWaste[waste1->oldWasteTopIndex-(j+1)];
		waste1->oldWaste[waste1->oldWasteTopIndex-(j+1)]="";
		stock1->topIndex++;
	}
	
	
	
	
	
}


void stockToWaste(stock* stock1, waste* waste1){
	if(stock1->topIndex!=-1){
		if(waste1->topIndex!=-1){
			for(int i =0;i<=waste1->topIndex;i++){
				waste1->oldWaste[waste1->oldWasteTopIndex]= waste1->cards[i];
				waste1->oldWasteTopIndex++;
				
			}
		}
		
		if(stock1->topIndex>=2){
			waste1->cards[0]=stock1->cards[stock1->topIndex];
			waste1->cards[1]=stock1->cards[stock1->topIndex-1];
			waste1->cards[2]=stock1->cards[stock1->topIndex-2];
			stock1->cards[stock1->topIndex]="";
			stock1->cards[stock1->topIndex-1]="";
			stock1->cards[stock1->topIndex-2]="";
			stock1->topIndex-=3;
			waste1->topIndex=2;
		}
	}
	else{
		gatherTheStock(stock1,waste1);
	}
	
}

int main(){
	string deck[52];
	pile piles[7];
	foundation foundations;
	stock stock;
	waste waste;
	string command;
	string tempCard;
	int tempIndex,tempIndex2,tempIndex3;

	readDeck("deck.txt",deck);
	setTable(deck, piles, &stock);
	
	displayTable(piles, waste,foundations,stock);
	ifstream commandFile;
	commandFile.open("commands.txt");
	
	if (!commandFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
	for( command; getline( commandFile, command ); ){

		cout<<"\n"<<command<<endl;
		cout<<endl<<"****************************************"<<endl;
		
    	
    	if(strCompare(command,"open f",6)){ //
    		stockToWaste(&stock, &waste);
		}
    	else if(strCompare(command,"open",4)){ //
			tempIndex=(int)command[5] - 48;
			piles->openPile(&piles[tempIndex]);
		}
		else if(strCompare(command,"move p",6)){
    		tempIndex=(int)command[10] - 48;
    		tempIndex2=(int)command[12] - 48;
    		tempIndex3=(int)command[14] - 48;
			pileToPile(&piles[tempIndex], &piles[tempIndex3], tempIndex2);
		}
		else if(strCompare(command,"move to foundation w",20)){ //
			wasteToFoundation(&waste, &foundations, &stock);
		}
		else if(strCompare(command,"move to foundation p",20)){ //
			tempIndex=(int)command[24] - 48;
			pileToFoundation(&piles[tempIndex], &foundations);
		}
		else if(strCompare(command,"move w",6)){ //
			tempIndex= (int)command[11] - 48;
			wasteToPile(&waste, &piles[tempIndex], &stock);
		}
		
		else if(strCompare(command,"exit",4)){ //
			cout<<"I GOEXIT YES";
		}
		
    	displayTable(piles, waste,foundations,stock);
	}		
	return 0;
}
