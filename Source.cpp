#include "Source.h"
using namespace std;

void In(ifstream& ifst, feature_film& f) {
	//ifst >> f.name;
	ifst >> f.director;
}
void Out(ofstream& ofst, feature_film& f)
{
	ofst << "It is feature film. Director is " << f.director << endl;
}
void In(ifstream& ifst, documentary_film& f) {
	ifst >> f.year;
}
void Out(ofstream& ofst, documentary_film& f) {
	ofst << "It is documentary film. It's year of creation is " << f.year << endl;
}
void In(ifstream& ifst, animation_film& a) {
	int t;
	ifst >> t;
	switch (t)
	{
	case 1:
		a.woc = DRAWN;
		break;
	case 2:
		a.woc = DOLL;
		break;
	case 3:
		a.woc = STOP_MOTION;
		break;
	}
}
void Out(ofstream& ofst, animation_film& a) {
	switch (a.woc)
	{
	case 0:
		ofst << "It is animation film. It's way of creation is drawing." << endl;
		break;
	case 1:
		ofst << "It is animation film. It's way of creation is using dolls" << endl;
		break;
	case 2:
		ofst << "It is animation film. It's way of creation is stop motion" << endl;
		break;
	}
}
film* InFilm(ifstream& ifst) {
	film* fl = new film;
	feature_film* f;
	animation_film* a;
	documentary_film* d;
	int k = 0;
	ifst >> k;
	ifst >> fl->name;
	switch (k) {
	case 1:
		fl->key = feature;
		f = new feature_film;
		In(ifst, *f);
		fl->obj = (void*)f;
		break;
	case 2:
		fl->key = animation;
		a = new animation_film;
		In(ifst, *a);
		fl->obj = (void*)a;
		break;
	case 3:
		fl->key = documentary;
		d = new documentary_film;
		In(ifst, *d);
		fl->obj = (void*)d;
		break;
	default:
		return 0;
	}

	ifst >> fl->country;
	feature_film f1;

	if (fl->key == feature) {
		f1 = *(feature_film*)fl->obj;
	}
	return fl;
}

void OutFilm(ofstream& ofst, film& f) {
	ofst << "This is \"" << f.name << "\". ";
	if (f.key == feature)
	{
		feature_film* pf;
		pf = (feature_film*)(f.obj);
		Out(ofst, *pf);
	}
	if (f.key == animation)
	{
		animation_film* pa;
		pa = (animation_film*)f.obj;
		Out(ofst, *pa);
	}
	if (f.key == documentary)
	{
		documentary_film* pd;
		pd = (documentary_film*)f.obj;
		Out(ofst, *pd);
	}
	ofst << "The picture was filmed in " << f.country << ".\n";

}

void Clear(container* c) {
	c->head = NULL;
	c->curr = NULL;
	c->size = 0;
}

void InCont(ifstream& ifst, container* c) {
	while (!ifst.eof()) {

		Node* newNode = new Node;
		newNode->fl = InFilm(ifst);
		if (c->head == NULL)
		{
			c->head = newNode;
			c->size = 1;
		}
		else
		{
			c->curr = c->head;
			while (c->curr->next != NULL)
			{
				c->curr = c->curr->next;
			}
			c->curr->next = newNode;
			c->size++;
		}
	}
}
void OutCont(ofstream& ofst, container* c) {
	ofst << "Container contents " << c->size
		<< " elements." << endl;

	int i = 0;
	c->curr = c->head;
	while (c->curr != NULL)
	{
		ofst << i << ": ";
		OutFilm(ofst, *(c->curr->fl));
		ofst << "Number of vowels = " << countVowel(*(c->curr->fl)) << endl;
		c->curr = c->curr->next;
		i++;
	}
}

string vowels = "aeiouyAEIOUY";

int countVowel(film& fl)
{
	int cnt = 0;
	for (int i = 0; i < fl.name.length(); i++)
	{
		if (vowels.find(fl.name[i]) < vowels.length())cnt++;
	}
	return cnt;
}

bool cmpVowels(Node* f1, Node* f2)
{
	return countVowel(*f1->fl) < countVowel(*f2->fl);
}

void Sort(container& c)
{
	Node* curri = c.head;
	Node* currj = c.head;
	while (curri != NULL)
	{
		currj = curri->next;
		while (currj != NULL) {
			if (cmpVowels(curri, currj))
			{
				swap(curri->fl, currj->fl);
			}
			currj = currj->next;
		}
		curri = curri->next;
	}
}
void OutFeature(ofstream& ofst, container* c)
{
	ofst << "Only feature films." << endl;
	c->curr = c->head;
	int i = 0;
	while (c->curr != NULL)
	{
		ofst << i << ": ";
		if (c->curr->fl->key == feature)
		{
			OutFilm(ofst, *c->curr->fl);
		}
		else
			ofst << endl;
		i++;
		c->curr = c->curr->next;
	}
}
void MultiMethod(container* c, ofstream& ofst) {
		ofst << "Multimethod." << endl;

		int i = 0, j = 1;
		c->curr = c->head;
		Node* currj = new Node;
		while (c->curr->next != NULL)
		{
			currj = c->curr->next;
			j = i+1;
			while (currj != NULL)
			{
				switch (c->curr->fl->key)
				{
				case feature:
					switch (currj->fl->key)
					{
					case feature:
						ofst << "First feature with second feature" << endl;
						break;
					case animation:
						ofst << "First feature && second animation" << endl;
						break;
					case documentary:
						ofst << "First feature + second documentary" << endl;
						break;
					default:
						ofst << "Unknown type" << endl;
					}
					break;
				case animation:
					switch (currj->fl->key)
					{
					case feature:
						ofst << "First animation plus second feature" << endl;
						break;
					case animation:
						ofst << "First animation aND second animation" << endl;
						break;
					case documentary:
						ofst << "First animation N' second documentary" << endl;
						break;
					default:
						ofst << "Unknown type" << endl;
					}
					break;
				case documentary:
					switch (currj->fl->key)
					{
					case feature:
						ofst << "First documentary 4ND second feature" << endl;
						break;
					case animation:
						ofst << "First documentary w/ second animation" << endl;
						break;
					case documentary:
						ofst << "First documentary ++ second documentary" << endl;
						break;
					default:
						ofst << "Unknown type" << endl;
					}
					break;
				default:
					ofst << "Unknown type" << endl;
				}
				ofst << i << ": ";  OutFilm(ofst, *(c->curr->fl));
				ofst << j << ": "; OutFilm(ofst, *(currj->fl));
				ofst << endl;
				currj = currj->next;
				j++;
			}
			c->curr = c->curr->next;
			i++;
		}
	}


