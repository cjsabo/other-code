#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void manager(int, int, int, int, int, int, float);
void supplier(int &, int &, int &);
float robber(float &);
float customer(int, int &, int, int &, int, int &, float &);
void bum(int, int &, int, int &, int, int &);

int main () {
	
	srand(time(0));
	int ref = 0;
	int hi = 100;
	int hs = 0;
	int ci = 100;
	int cs = 0;
	int mi = 100;
	int ms = 0;
	float money = 100;
	char who;
	
	while(ref == 0) {
	
		cout << "Who is it? " ;
		cin >> who;
		if(who == 'Q') {
			cout << "Sorry, but the store is closed." << endl;
			ref = 1;
		}
		else if(who == 'M') {
			manager(hi, hs, ci, cs, mi, ms, money);
		}
		else if(who == 'S') {
			supplier(hi, ci,mi);
		}
		else if (who == 'R') {
			cout << "Oh no! The robber stole $" << robber(money) << "!!!" << endl;
		}
		else if (who == 'C') {
			cout << "Your total is: $" << customer(hi,hs,ci,cs,mi,ms,money) << endl;
		}
		else if(who == 'B'){
			bum(hi, hs, ci, cs, mi, ms);
		}
		else {
			cout << "I don't know who you are! Get the hell out of my store!" << endl;
		}
	}
	
	
	
	
	
	return 0;
}
void manager(int hi, int hs, int ci, int cs, int mi, int ms, float cash) {
	cout << "Hello manager, nice to see you. This is how our store is doing:" << endl;
	cout << "             " << "Hashbrowns" << "   " << "Coke" << "          " << "Machetes" << endl;
	cout << "Inventory" << "    " << hi << "           " << ci << "               " << mi << endl;
	cout << "Sold" << "          " << hs << "              " << cs << "                " << ms << endl;
	cout << "Remaining" << "    " << hi-hs << "             " << ci-cs << "            " << mi-ms<< endl;
	cout << "Total Money: $" << cash << endl;
	return; 
}
void supplier(int & h, int & c, int & m) {
	int hb;
	int cb;
	int mb;
	cout << "How many hashbrowns would you like? " ;
	cin >> hb;
	h+=hb;
	cout << "How many cokes do you want? " ;
	cin >> cb;
	c+=cb;
	cout << "And how many machetes do you want? " ;
	cin >> mb;
	m+=mb;
	return;
}
float robber (float & cash) {
	int stolen = cash;
	cash = 0;
	return stolen;
}
float customer(int hi, int & hs, int ci, int & cs, int mi, int & ms, float & cash) {
	int hb;
	int cb;
	int mb;
	float total = 0;
	cout << "Hello customer! How many hashbrowns would you like? " ;
	cin >> hb;
	while (hb > hi-hs){
		cout << "I'm sorry. We don't have that many. How many hashbrowns woudl you like? " ;
		cin >> hb ;
	}
	hs+=hb;
	
	cout << "Alright. Now how many cokes? ";
	cin >> cb;
	while(cb > ci-cs){
		cout << "I'm sorry. We don't have that many. How many cokes? " ;
		cin >> cb ;
	}
	cs+=cb;
	
	cout << "Ok. Now how many machetes? " ;
	cin >> mb;
	while(mb > mi-ms){
		cout << "I'm sorry. We don't have that many. How many machetes? " ;
		cin >> mb;
	}
	ms+=mb;
	total = (13.27*hb)+(24.29*cb)+(17.00*mb);
	cash+=total;
	
	return total;
}
void bum(int hi, int & hs, int ci, int & cs, int mi, int & ms){
	int x = 3 + rand() % 15;
	if (x > hi-hs){
		x = hi-hs;
	}
	
	int y = 2 + rand() % 8;
	if (y > ci-cs){
		y = ci-cs;
	}
	
	int z = 4 + rand() % 4; 
	if (z > mi-ms){
		z = mi-ms;
	}
	
	hs = hs + x ;
	
	cs = cs + y ;
	
	ms = ms + z ;
	
	cout << "Hey, you filthy bum, get outta here!" << endl;
	
	return;
}