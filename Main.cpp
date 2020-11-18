#include <iostream>
#include <fstream>
#include <string>
#include<cstdlib>
using namespace std;
ofstream output;
string charArrayToString(char* a, int size) { //
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}
bool strCompare(string s1, string s2,int compareLength){ // returns true if strings are identical
	if(compareLength>s1.length() || compareLength>s2.length()){return false;}
	for(int i=0;i<compareLength;i++){
		if(s1[i]!=s2[i]){
			return false;
		}
	}
	return true;
}
void readDeck(string path, string deck[52]){
	int i=0;
	ifstream deckFile;
	deckFile.open(path.c_str());
	string x;
	if (!deckFile) {
        output << "Unable to open file";
        exit(1); // terminate with error
    }

    while(i<52){
    	deckFile>>deck[i];
		i++;
	}
    deckFile.close();
}
string hearts[13]={"H01","H02","H03","H04","H05","H06","H07","H08","H09","H10","H11","H12","H13"};
string diamonds[13]={"D01","D02","D03","D04","D05","D06","D07","D08","D09","D10","D11","D12","D13"};
string clubs[13]={"C01","C02","C03","C04","C05","C06","C07","C08","C09","C10","C11","C12","C13"};
string spades[13]={"S01","S02","S03","S04","S05","S06","S07","S08","S09","S10","S11","S12","S13"};
int indexOf(string card){  //indexOf("H11")=10 indexOf("C01")=0 ... Returns the card's magnitude 0-12
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
bool colorRule(string s1, string s2){ // C-S can get H-D
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
int stringToInt(string string1){//Converts integers from 0 to 12 else returns -1
    if(!string1.compare("0"))return 0;
    if(!string1.compare("1"))return 1;
    if(!string1.compare("2"))return 2;
    if(!string1.compare("3"))return 3;
    if(!string1.compare("4"))return 4;
    if(!string1.compare("5"))return 5;
    if(!string1.compare("6"))return 6;
    if(!string1.compare("7"))return 7;
    if(!string1.compare("8"))return 8;
    if(!string1.compare("9"))return 9;
    if(!string1.compare("10"))return 10;
    if(!string1.compare("11"))return 11;
    if(!string1.compare("12"))return 12;
    return -1;

}
string stringSplitter(string string1, char parameter, int index){ // splits the string by the given parameter
//and returns the preffered indexed string from splitted strings
    char buffer[string1.length()];
    int splitTime=-1;
    int bufferIndex=0;
    for(int i=0;i<string1.length();i++){
        if(string1[i]!=parameter){
            buffer[bufferIndex]=string1[i];
            bufferIndex++;
        }
        else{
            splitTime++;
            if(splitTime== index){
                return charArrayToString(buffer,bufferIndex);
            }
            bufferIndex=0;
        }
    }
    return charArrayToString(buffer,bufferIndex);
}

class stock{
    private:
        string cards[24]={""};
        int topIndex=-1;
    public:
        string getCard(){ //returns the topmost card
            if(topIndex==-1){
                return "0";
            }
            else{
                return cards[topIndex];
            }
        }
        bool addCard(string card){
            if(topIndex==23){
                output<<"\nInvalid Move!\n";
                return false;
            }
            else{
                cards[topIndex+1]=card;
                topIndex++;
                return true;
            }
        }
        int getTopIndex(){
            return this->topIndex;
        }
        void deleteTopmostCard(){
            if(topIndex==-1){
                output<<"\nInvalid Move!\n";
            }
            else{
                cards[topIndex]="";
                topIndex--;
            }
        }
        void  displayStock(){
            if(topIndex==-1){
                output<<"___ ";
            }
            else{
                output<<"@@@ ";
            }
        }
};

class foundation{
    private:
        string cards[4][13]={};
        int topIndex0=0;
		int topIndex1=0;
		int topIndex2=0;
		int topIndex3=0;
	public:
        bool addCard(string card){  //tries to put the given card to any place at foundation area
                                    //if it succeeds, returns true
            if(card[0]=='H' && (indexOf(card)==topIndex0)){
                    this->cards[0][topIndex0]=card;
                    topIndex0++;
            }
            else if(card[0]=='D' && (indexOf(card)==topIndex1)){
                    this->cards[1][topIndex1]=card;
                    topIndex1++;
            }
            else if(card[0]=='S' && (indexOf(card)==topIndex2)){
                    this->cards[2][topIndex2]=card;
                    topIndex2++;
            }
            else if(card[0]=='C' && (indexOf(card)==topIndex3)){
                    this->cards[3][topIndex3]=card;
                    topIndex3++;
            }
            else{return false;}
            return true;
        }
        void displayFoundations(){
			if(topIndex0!=0){
				output<<cards[0][topIndex0-1]<<" ";
			}else{output<<"___ ";}

			if(topIndex1!=0){
				output<<cards[1][topIndex1-1]<<" ";
			}else{output<<"___ ";}

			if(topIndex2!=0){
				output<<cards[2][topIndex2-1]<<" ";
			}else{output<<"___ ";}

			if(topIndex3!=0){
				output<<cards[3][topIndex3-1]<<" ";
			}else{output<<"___ ";}

			output<<endl<<endl;
		}

		string getCard(int index){ //get topmost card from the given indexed foundation
		    switch(index){
                case 0:
                    if(topIndex0>0)
                        return this->cards[index][topIndex0-1];
                    break;
                case 1:
                    if(topIndex1>0)
                        return this->cards[index][topIndex1-1];
                    break;
                case 2:
                    if(topIndex2>0)
                        return this->cards[index][topIndex2-1];
                    break;
                case 3:
                    if(topIndex3>0)
                        return this->cards[index][topIndex3-1];
                    break;
		    }
		}
		void deleteTopmostCard(int index){
            switch(index){
                case 0:
                    this->topIndex0--;
                    break;
                case 1:
                    this->topIndex1--;
                    break;
                case 2:
                    this->topIndex2--;
                    break;
                case 3:
                    this->topIndex3--;
                    break;
            }
		}
		bool isFull(){
            if(topIndex0==13 && topIndex1==13 && topIndex2==13 && topIndex3==13){
                return true;
            }
            return false;
		}
};

class pile{
    /* ---Pile1---
  0  [card1][downward]
  1  [card2][downward]
  2  [card3][downward]
  3  [card4][upward]
to show whether the card is laying upward or downward,
it stores one more string:
    if its "1" that means the card is laying upward
    if its "0" that means the card is laying upward
    cards[0][0] = card1, cards[0][1] = "0"
    cards[3][0] = card4, cards[0][1] = "1"
    */
    private:
        string cards[19][2];
        int topIndex=-1;
    public:
        void addToPileDownward(string card){
            if(topIndex<18){
                cards[topIndex+1][0]=card;
                cards[topIndex+1][1]="0";
                topIndex++;
            }
            else{
                output<<"\nInvalid Move!\n";
            }
		}
		bool addToPileUpward(string card){
			if(topIndex<18){
                cards[topIndex+1][0]=card;
                cards[topIndex+1][1]="1";
                topIndex++;
                return true;
			}
			return false;
		}
		void to(int cardAmount, pile* pile2){// transfers card/cards to given pile as parameter
                                            //from the pile that function has called
		    pile* pile1= this;
		    cardAmount++;
            int startingIndex=pile1->topIndex-(cardAmount);
            //P=if the first card from selected card/cards is laying upward
            //Q=colors and magnitudes match for transfer
            //R=if king goes to an empty pile
            // P && (Q || R)
            if (((colorRule(pile1->cards[topIndex+1-cardAmount][0],pile2->getTopmostCard())&&
                  magnitudeRule(pile1->cards[topIndex+1-cardAmount][0],pile2->getTopmostCard()))
                                                ||
        ((indexOf(pile1->cards[topIndex+1-cardAmount][0])==12) &&(pile2->topIndex==-1)))
                                                &&
                        pile1->cards[topIndex+1-cardAmount][1]=="1"){
                for(int i=0;i<cardAmount;i++){
                    pile2->addToPileUpward(pile1->cards[topIndex+1-cardAmount+i][0]);
                }
                for(int i =0;i<cardAmount;i++){
                    pile1->deleteTopmostCard();
                }

            }
            else{output<<"\nInvalid Move!\n";}

		}
		int getTopIndex(){
            return this->topIndex;
        }
        void openPile(){
			if(this->topIndex==-1){
				output<<"\nInvalid Move!\n";
			}
			else if(this->cards[this->topIndex][1]=="1"){
				output<<"\nInvalid Move!\n";
			}
			else{
				this->cards[this->topIndex][1]="1";
			}
		}
		void displayPiles(pile* piles){
			int maxTopIndex=0;
			for(int i = 0; i<7;i++){
                if(piles[i].topIndex>maxTopIndex){
                        maxTopIndex=piles[i].topIndex;
                }
			}
			for(int j = 0; j<=maxTopIndex;j++){
				for(int i = 0; i<7;i++){
					if(piles[i].cards[j][0]!=""&& piles[i].cards[j][1]=="1"){ //if card layed upward
						output<<piles[i].cards[j][0]<<"   ";
					}
					else if(piles[i].cards[j][0]!=""){
						output<<"@@@   ";
					}
					else{
						output<<"      ";
					}
				}
                    output<<endl;
			}
		}
        void deleteTopmostCard(){
			cards[topIndex][0]="";
			topIndex--;
		}
        string getTopmostCard(){
            return this->cards[this->topIndex][0];
        }
		void pileToFoundation(foundation* foundation){ //transfers the card from pile to foundation
            if(foundation->addCard(this->getTopmostCard())){
               this->deleteTopmostCard();
            }else{output<< "\nInvalid Move!\n";}
		}
};

class waste{
    private:
        string cards[3]={""};
        int topIndex=-1;
        int wasteHistoryTopIndex=-1;
        string wasteHistoryCards[24]={""};
    public:
        string getCard(){
            if(topIndex==-1){
                output<<"\nInvalid Move!\n";
                return "0";
            }
            else{
                return cards[topIndex];
            }
        }
        void addCard(string card){
            if(topIndex<2){
                this->cards[topIndex+1]=card;
                this->topIndex++;
            }
        }
        void deleteTopmostCard(){
            if(topIndex!=-1){
                cards[topIndex]="";
                topIndex--;
            }
        }
        void getFromHistoryToWaste(){
            //gets the old-topmost indexed-non used waste card from history
            if(topIndex==-1 && this->wasteHistoryTopIndex!=-1){
                waste* waste1 = this;
                waste1->addCard(getWasteHistoryCard());
                deleteTopmostWasteHistoryCard();
            }
        }
        void wasteToHistory(){
            int cardAmountInWaste=this->topIndex;
            for(int i = 0;i<=cardAmountInWaste;i++){
                this->addWasteHistoryCard(this->cards[i]);
            }
            for(int i = 0;i<=cardAmountInWaste;i++){
                this->deleteTopmostCard();
            }
        }
        string getWasteHistoryCard(){
            if(wasteHistoryTopIndex==-1){
            }
            else{
                return wasteHistoryCards[wasteHistoryTopIndex];
            }
        }
        void addWasteHistoryCard(string card){
            if(this->wasteHistoryTopIndex<23){
                this->wasteHistoryCards[wasteHistoryTopIndex+1]=card;
                wasteHistoryTopIndex++;
            }
        }
        void deleteTopmostWasteHistoryCard(){
            if(wasteHistoryTopIndex>-1){
                wasteHistoryCards[wasteHistoryTopIndex]="";
                wasteHistoryTopIndex--;
            }
        }
        void displayWaste(){
			for(int i = 0;i<3;i++){
				if(cards[i]==""){
					output<<"___ ";
				}
				else{
					output<< cards[i]<<" ";
				}
			}
			output<<"        ";
		}
		void wasteToFoundation(foundation* foundation1){
            if(foundation1->addCard(getCard()) == true){
                this->deleteTopmostCard();
                this->getFromHistoryToWaste();
            }
            else{
                output<<"\nInvalid Move!\n";
            }
		}

		void historyToStock(stock* stock){
		    int i=0;
		    while(this->wasteHistoryTopIndex!=-1){
                stock->addCard(this->getWasteHistoryCard());
                i++;
                this->deleteTopmostWasteHistoryCard();
		    }

		}
		void wasteToPile(pile* pile1){
            if((magnitudeRule(this->getCard(),pile1->getTopmostCard())&&
               colorRule(this->getCard(),pile1->getTopmostCard()))
                                        ||
                        ((indexOf(this->getCard())==12) &&
                            (pile1->getTopIndex()==-1))){
                pile1->addToPileUpward(this->getCard());
                this->deleteTopmostCard();
                this->getFromHistoryToWaste();
            }
            else{
                output<<"\nInvalid Move!\n";
            }
		}

		void openFromStock(stock* stock){
		    wasteToHistory();
		    if(stock->getTopIndex()==-1){
               this->historyToStock(stock);
		    }
		    else{
                for(int i=0 ; i<=2 && stock->getTopIndex()>-1 ;i++){
                    this->addCard(stock->getCard());
                   // cout<<"loop's i="<<i<<"  i add this to waste "<<stock->getCard()<<endl;
                    stock->deleteTopmostCard();
                }
		    }

		}
};

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
				stock->addCard(deck[i]);
		}
		break;
	}
	}
}

void displayTable(pile* piles,waste waste,foundation foundations,stock stock){
    stock.displayStock();
    waste.displayWaste();
    foundations.displayFoundations();
    piles[0].displayPiles(piles);
}

int main(char* argv[]){
    string deck[52];
	pile piles[7];
	foundation foundations;
	stock stock;
	waste waste;
	string command;
	string tempCard;
	ifstream commandFile;
	int tempIndex,tempIndex2,tempIndex3;
	int isntValidIndex=-1;
	readDeck("deck.txt",deck);
	commandFile.open("commands.txt");
	output.open("output.txt");
	setTable(deck, piles, &stock);
    output<<endl;
	displayTable(piles, waste,foundations,stock);

    if (!commandFile) {
        exit(1); // terminate with error
    }

	for( command; getline( commandFile, command ); ){
        output<<"\n"<<command<<endl;


    	if(strCompare(command,"open f",6)){ //
            waste.openFromStock(&stock);
		}
    	else if(strCompare(command,"open",4)){
			if(stringToInt(stringSplitter(command, ' ', 1)) == isntValidIndex){
                output<<"Invalid Move!\n";
			}else{
                tempIndex=stringToInt(stringSplitter(command, ' ', 1));
                piles[tempIndex].openPile();
			}
		}
		else if(strCompare(command,"move p",6)){
            if((stringToInt(stringSplitter(command, ' ', 2)) == isntValidIndex)
            || (stringToInt(stringSplitter(command, ' ', 3)) == isntValidIndex)){
                output<<"\nInvalid Move!\n";
			}else{
			    tempIndex=stringToInt(stringSplitter(command, ' ', 2));
                tempIndex2=stringToInt(stringSplitter(command, ' ', 3));
                tempIndex3=stringToInt(stringSplitter(command, ' ', 4));
                piles[tempIndex].to(tempIndex2, &piles[tempIndex3]);
			}
		}
		else if(strCompare(command,"move to foundation w",20)){ //
			waste.wasteToFoundation(&foundations);
		}
		else if(strCompare(command,"move to foundation p",20)){ //
		    if(stringToInt(stringSplitter(command, ' ', 4)) <7){
                tempIndex=stringToInt(stringSplitter(command, ' ', 4));
                piles[tempIndex].pileToFoundation(&foundations);
            }
		}
		else if(strCompare(command,"move w",6)){ //
            if(stringToInt(stringSplitter(command, ' ', 2))<7){
                tempIndex=stringToInt(stringSplitter(command, ' ', 2));
                waste.wasteToPile(&piles[tempIndex]);
            }
		}
		else if(strCompare(command,"exit",4)){ //
			output<<"\n****************************************\n\n";
			output<<"Game Over!\n";
			output.close();
			exit(0);
		}
		output<<endl<<"****************************************"<<endl<<endl;
		displayTable(piles, waste,foundations,stock);
	}
	if(foundations.isFull()){
        output<<"\n****************************************"<<endl<<endl;
        output<<"You Win!\n\nGame Over!\n";
        }
    output.close();
    return 0;
}

