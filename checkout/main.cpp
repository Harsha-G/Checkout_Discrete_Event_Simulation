#include "Header.h"


using namespace std;

static double saveNormal;
static int NumNormals = 0;
static double PI = 3.1415927;

//function to generate a double
double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

static double box_mueller(double r, double mean, double sigma) {
	double returnNormal;
	if (NumNormals == 0) {
		//to get next double value
		double r1 = fRand(0, r)/100;
		double r2 = fRand(0, r)/100;
		returnNormal = sqrt(-2 * log(r1)) * cos(2 * PI*r2);
		saveNormal = sqrt(-2 * log(r1)) * sin(2 * PI*r2);
	}
	else {
		NumNormals = 0;
		returnNormal = saveNormal;
	}
	return returnNormal*sigma + mean;
}

//function to produce a pointer to a vector<int> that contains random variates
vector<int>* produce_variates(int no, double mean, double sigma) {
	vector<int>* tmp = new vector<int>;
	for (int i = 0; i < no; i++) {
		double n = box_mueller(fRand(0, 10), mean, sigma);
		if (n < 0)n*=-1.0;
		tmp->push_back(n);
	}
	return tmp;
}

int main() {

	string file("C://Users//hgstr//Desktop//chkout.txt");


	vector<int> *inter_arr_t = produce_variates(100, 5, 2);
	vector<int> *serv_t = produce_variates(100, 4, 2);

	simulation s(inter_arr_t, serv_t, file);

	s.sim_arrival(0, s.o_file);


}