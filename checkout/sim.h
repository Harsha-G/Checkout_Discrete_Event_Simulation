#pragma once


using namespace std;

int gen_random_int(int l_bnd, int u_bnd);


class simulation {

	int clock, ls, lq, sno, b,p_t, mq, time, inter_ar_cnt, srvc_tm_cnt;

	bool checker;

	int customer_cnt;

	vector<int> interarrival_times;
	vector<int> service_times;

	//customer response time vector
	vector<int> cust_rt;
	//no. of departures:
	int no_departures;
	//total time run
	int time_max;

	fel *evnt_lst;
	fel *servc_lst;

public:
	ofstream o_file;
	simulation();
	simulation(vector<int> * it, vector<int> *st, string out_file);
	void accept_interarrival_times(vector<int> * it);
	void accept_service_times(vector<int> *st);
	void sim_arrival(int t, ofstream &o_file);
	void sim_departure(int t, ofstream &o_file);


};
