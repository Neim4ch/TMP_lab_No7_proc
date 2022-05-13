#include "Source.h"
using namespace std;

void In(ifstream& ifst, feature_film& f) {
	ifst >> f.director;
}
void Out(ofstream& ofst, feature_film& f) {
	ofst << "It is feature film. Director is " << f.director << endl;
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
	int k = 0;
	ifst >> k;
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
	default:
		return 0;
	}
	feature_film f1;
	if (fl->key == feature) {
		f1 = *(feature_film*)fl->obj;

	}
	return fl;
}

	void OutFilm(ofstream & ofst, film & f) {
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
	}

	void Clear(container * c) {
		c->head = NULL;
		c->curr = NULL;
		c->size = 0;
	}
	void InCont(ifstream & ifst, container * c) {
		while (!ifst.eof()) {

			Node* newNode = new Node;
			newNode->fl = InFilm(ifst);
			//feature_film* f1 = (feature_film*)newNode->fl->obj;
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
	void OutCont(ofstream & ofst, container * c) {
		ofst << "Container contents " << c->size
			<< " elements." << endl;
		int i = 0;
		c->curr = c->head;
		while (c->curr != NULL)
		{
			ofst << i << ": ";
			OutFilm(ofst, *(c->curr->fl));
			c->curr = c->curr->next;
			i++;
		}
	}
void MultiMethod(container* c, ofstream& ofst) {
		ofst << "Multimethod." << endl;

		int i = 0, j = 1;
		c->curr = c->head;
		Node* currj = new Node;
		while (c->curr->next != NULL)
		{
			//ofst << i << ": ";
			//OutFilm(ofst, *(c->curr->fl));
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
						ofst << "First feature and second animation" << endl;
						break;
					default:
						ofst << "Unknown type" << endl;
					}
					break;
				case animation:
					switch (currj->fl->key)
					{
					case feature:
						ofst << "First animation and second feature" << endl;
						break;
					case animation:
						ofst << "First animation && second animation" << endl;
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


