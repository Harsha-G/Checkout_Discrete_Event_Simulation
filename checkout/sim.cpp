#include "Header.h"

int calc_sum_vec(vector<int> *v, int ind) {
	int sum = 0;
	for (int i = 0; i < ind; i++) {
		sum = sum + v->at(i);
	}
	return sum;
}

int calc_sum_vec(vector<int> *v) {
	int sum = 0;
	for (int i = 0; i < v->size(); i++) {
		sum = sum + v->at(i);
	}
	return sum;
}

float get_proportion(int n, vector<int>* v) {
	int cnt = 0;
	for (int i = 0; i < v->size();i++) {
		if (v->at(i) >= 4) {
			cnt++;
		}
	}
	return (cnt*1.0 / v->size()*1.0);
}

int gen_random_int(int l_bnd, int u_bnd) {
	return (rand() % (u_bnd - l_bnd)) + l_bnd;
}

float gen_random_float() {
	return ((rand() % (100 - 1)) + 1)*0.01;
}

simulation::simulation() {
	clock = sno = ls = lq = b = mq = time = inter_ar_cnt = srvc_tm_cnt = 0;

	checker = false;
	evnt_lst = new fel();

}

simulation::simulation(vector<int> * it, vector<int> *st, string out_file) {
	clock = sno = ls = lq = b = p_t = mq = time = inter_ar_cnt = srvc_tm_cnt = 0;

	interarrival_times = *it;
	service_times = *st;

	evnt_lst = new fel();
	servc_lst = new fel();
	checker = false;

	customer_cnt = 1;

	no_departures = 0;

	time_max = 0;
	 
	o_file.open(out_file);
}

void simulation::sim_arrival(int t, ofstream &o_file) {

	if (t > 100 ) {
		o_file << "\n\n";
		o_file << "Server Utilization: " << (float)calc_sum_vec(&service_times, customer_cnt)*1.0 / t*1.0 << endl;
		o_file << "Maximum Line Length: " << mq << endl;
		o_file << "Average Response Time: " << calc_sum_vec(&cust_rt) / cust_rt.size() << endl;
		o_file << "Proportion that spent 4 or more time units in system: " << get_proportion(4, &cust_rt) << endl;
		o_file << "Simulation Run Length: " << t << endl;
		o_file << "Number of Departures: " << no_departures << endl;
		return;

	}

	time_max = t;

	char c[10];
	sprintf_s(c, "C%d", customer_cnt);

	//Removing the top most Event notice in Future event list
	if (evnt_lst->get_peek() != NULL) {
		evnt_lst->pop_peek();
	}

	if (ls != 0 ) {
		b = b+(t-b);
	}


	if (ls == 0) {
		ls = 1;
		evnt_lst->fel_insert(spawn_event("D", service_times[inter_ar_cnt] + t), *evnt_lst->return_peek());
		srvc_tm_cnt++;
	}
	else lq++;

	evnt_lst->fel_insert(spawn_event("A", interarrival_times[inter_ar_cnt] + t), *evnt_lst->return_peek());
	inter_ar_cnt++;


	servc_lst->fel_insert(spawn_event(c, t), *servc_lst->return_peek());
	customer_cnt++;

	if (lq > mq) mq = lq;

	o_file << t << setw(5) << lq << setw(10) << ls << setw(10) << b << setw(10) << mq<< setw(30) << evnt_lst->return_fel_str().c_str() << setw(20) << "A occurs, (a*="<< interarrival_times[inter_ar_cnt-1]<<") Schedule Next Arrival "<< endl;

	if (strcmp(evnt_lst->get_peek()->evnt, "A") == 0) {
		//Schedule next arrival at the time of the next event notice
		sim_arrival(evnt_lst->get_peek()->time, o_file);
	}
	else {
		//Schedule next departure at the time of next event notice
		sim_departure(evnt_lst->get_peek()->time, o_file);
	}
}


void simulation::sim_departure(int t, ofstream &o_file) {

	if (t > 100) {

		o_file << "\n\n";
		o_file << "Server Utilization: " << (float)calc_sum_vec(&service_times, customer_cnt)*1.0 / t*1.0 << endl;
		o_file << "Maximum Line Length: " << mq << endl;
		o_file << "Average Response Time: " << calc_sum_vec(&cust_rt) / cust_rt.size() << endl;
		o_file << "Proportion that spent 4 or more time units in system: " << get_proportion(4, &cust_rt) << endl;
		o_file << "Simulation Run Length: " << t << endl;
		o_file << "Number of Departures: " << no_departures << endl;
		return;
	}

	time_max = t;

	sno++;
	time = t;

	if (ls != 0 ) {
		b = b + (t - b);
	}

	if (lq > 0) {
		lq--;
		evnt_lst->fel_insert(spawn_event("D", service_times[srvc_tm_cnt] + t), *evnt_lst->return_peek());
		srvc_tm_cnt++;
	}
	else {
		ls = 0;
	}
	cust_rt.push_back(t - servc_lst->get_peek()->time);

	if (evnt_lst->get_peek() != NULL) {
		evnt_lst->pop_peek();
	}
	no_departures++;

	if (servc_lst->get_peek() != NULL) {
		servc_lst->pop_peek();
	}


	if (lq > mq) mq = lq;

	o_file << t << setw(5) << lq << setw(10) << ls << setw(10) << b << setw(10) << mq << setw(30) << evnt_lst->return_fel_str().c_str() << setw(20) << "D occurs, (s*=" << service_times[srvc_tm_cnt - 1] << ") Schedule Next Departure " << endl;

	if (strcmp(evnt_lst->get_peek()->evnt, "A") == 0) {
		sim_arrival(evnt_lst->get_peek()->time, o_file);
	}
	else {
		sim_departure(evnt_lst->get_peek()->time, o_file);
	}
}

void simulation::accept_interarrival_times(vector<int> * it) {
	interarrival_times = *it;
}

void simulation::accept_service_times(vector<int> * st) {
	service_times = *st;
}
