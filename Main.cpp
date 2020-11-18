#include <iostream>
#include <fstream>
#include <string>
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

class stock{
    private:
        string cards[24]={""};
        int topIndex=-1;
    public:
        string getCard(){
            if(topIndex==-1){
                return "0";
            }
            else{
                return cards[topIndex];
            }
        }
        bool addCard(string card){
            if(topIndex==23){
                cout<<"stock is full, you cant add more stuff\n";
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
                cout<<"STOCK IS ALREADY EMPTY\n";
            }
            else{
                cards[topIndex]="";
                topIndex--;
            }
        }
        void  displayStock(){
            if(topIndex==-1){
                cout<<"___ ";
            }
            else{
                cout<<"@@@ ";
            }
        }
        void stockTest(){
            for(int i=0;i<=topIndex;i++){
                cout<<"stock["<<i<<"]="<<cards[i]<<endl;
            }
        }
};

class foundation{
    private:
        string cards[4][12]={};
        int topIndex0=0;
		int topIndex1=0;
		int topIndex2=0;
		int topIndex3=0;
	public:
        bool addCard(string card){
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

			cout<<endl<<endl;
		}

		string getCard(int index){
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
};

class pile{
    private:
        string cards[19][2];
        int topIndex=-1;

    public:
        void setPiles(){
        }
        void addToPileDownward(string card){ // cards[x][1]="0" represents its an downward card, cards[x][1]="1" represents upward cards
            if(topIndex<18){
                cards[topIndex+1][0]=card;
                cards[topIndex+1][1]="0";
                topIndex++;
            }
            else{
                cout<<"pile is already full, cant add more\n";
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
		/*void addToPileUpwardMultiple(string* cards1){
		    int cardAmount=sizeof(cards1)/sizeof(cards1[0]);
			if(topIndex+cardAmount<18){
                for(int i = 0;i<cardAmount;i++){
                    addToPileUpward(cards1[i]);
                }
			}
		}*/
		void to(int cardAmount, pile* pile2){
		    pile* pile1= this;
		    cardAmount++;
            int startingIndex=pile1->topIndex-(cardAmount);
            string cardsToTransfer[cardAmount];




            //if colors and magnitudes match for transfer
            //or king goes to an empty pile
            if ((colorRule(pile1->cards[topIndex+1-cardAmount][0],pile2->getTopmostCard()) &&
                magnitudeRule(pile1->cards[topIndex+1-cardAmount][0],pile2->getTopmostCard()))
                                                ||
                ((indexOf(pile1->cards[topIndex+1-cardAmount][0])==12) &&
                    (pile2->topIndex==-1))){
                for(int i=0;i<cardAmount;i++){
                    pile2->addToPileUpward(pile1->cards[topIndex+1-cardAmount+i][0]);
                }
                for(int i =0;i<cardAmount;i++){
                    pile1->deleteTopmostCard();
                }

            }
            else{cout<<"invalid\n";}

		}
		int getTopIndex(){
            return this->topIndex;
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
        void openPile(){
			if(this->topIndex==-1){
				cout<<"Error, you cant open anything!";
			}
			else if(this->cards[this->topIndex][1]=="1"){
				cout<<"Error, you cant open anything!";
			}
			else{
				this->cards[this->topIndex][1]="1";
			}
		}
		void displayPiles(pile* piles){
			int maxTopIndex=1;
			for(int j = 0; j<=maxTopIndex;j++){
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
        void deleteTopmostCard(){
			cards[topIndex][0]="";
			topIndex--;
		}
        string getTopmostCard(){
            return this->cards[this->topIndex][0];
        }
		void pileToFoundation(foundation* foundation){
            if(foundation->addCard(this->getTopmostCard())){
               this->deleteTopmostCard();
            }else{cout<< "invalid\n";}
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
                cout<<"you cant get card from empty waste\n";
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
            if(topIndex==-1 && this->wasteHistoryTopIndex!=-1){
                waste* waste1 = this;
                waste1->addCard(getWasteHistoryCard());
                deleteTopmostWasteHistoryCard();
            }
        }
        void deleteTopmostCard(int x){ // use this function to save waste to history
            if(topIndex!=-1){
                cards[topIndex]="";
                topIndex--;
            }


        }

        void wasteToHistory(){
            int cardAmountInWaste=this->topIndex;
            for(int i = 0;i<=cardAmountInWaste;i++){
                cout<<"function wasteToHistory "<<i <<"th loop, i add this to history: "<<this->cards[i]<<endl;
                this->addWasteHistoryCard(this->cards[i]);
            }
            for(int i = 0;i<=cardAmountInWaste;i++){
                this->deleteTopmostCard(1);
            }

            /*for(int i=0;i<this->topIndex;i++){
                this->addWasteHistoryCard(this->cards[i]);
            }
            for(int j=topIndex;j>0;j--){
                this->deleteTopmostCard(1);
            }*/
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
					cout<<"___ ";
				}
				else{
					cout<< cards[i]<<" ";
				}
			}
			cout<<"        ";
		}
		void wasteToFoundation(foundation* foundation1){
            if(foundation1->addCard(getCard()) == true){
                this->deleteTopmostCard();
            }
		}

		void historyToStock(stock* stock){
		    int i=0;
		    while(this->wasteHistoryTopIndex!=-1){
                stock->addCard(this->getWasteHistoryCard());
                //cout<<"stock["<<i<<"] = "<<this->getWasteHistoryCard()<<endl;
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
            }
            else{
                cout<<"INVALIDDDDDD\n";
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
                    cout<<"loop's i="<<i<<"  i add this to waste "<<stock->getCard()<<endl;
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
    cout<<endl;
	displayTable(piles, waste,foundations,stock);
	ifstream commandFile;
	commandFile.open("commands.txt");
    if (!commandFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

	for( command; getline( commandFile, command ); ){
        cout<<"\n"<<command<<endl;
		cout<<endl<<"****************************************"<<endl<<endl;

        stock.stockTest();
    	if(strCompare(command,"open f",6)){ //
            waste.openFromStock(&stock);
		}
    	else if(strCompare(command,"open",4)){
			tempIndex=(int)command[5] - 48;
			piles[tempIndex].openPile();
		}
		else if(strCompare(command,"move p",6)){
    		tempIndex=(int)command[10] - 48;
    		tempIndex2=(int)command[12] - 48;
    		tempIndex3=(int)command[14] - 48;
    		piles[tempIndex].to(tempIndex2, &piles[tempIndex3]);
		}
		else if(strCompare(command,"move to foundation w",20)){ //
			waste.wasteToFoundation(&foundations);
		}
		else if(strCompare(command,"move to foundation p",20)){ //
			tempIndex=(int)command[24] - 48;
			piles[tempIndex].pileToFoundation(&foundations);
		}
		else if(strCompare(command,"move w",6)){ //
			tempIndex= (int)command[11] - 48;
			waste.wasteToPile(&piles[tempIndex]);
		}

		else if(strCompare(command,"exit",4)){ //
			cout<<"I GOEXIT YES";
		}

		displayTable(piles, waste,foundations,stock);
 //   	displayInfos(stock,waste);



	}




    return 0;
}














