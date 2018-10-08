#pragma once


struct event_notice {
	char evnt[10];
	float time;
	char cli[10];

	event_notice *right, *left;

	event_notice(char evnt_[], float t);
	event_notice(char evnt_[], float t, char cli_[]);
};

event_notice* spawn_event(char e[], int t);
event_notice* spawn_event(char e[], int t, char c[]);

class fel {
	event_notice *peek;
	int length;
public:
	fel();
	void fel_insert(event_notice *new_ev, event_notice* &cur);
	void delete_evnt(event_notice *trgt, event_notice* &cur);
	event_notice* get_next();
	event_notice* get_peek();
	void pop_peek();
	int get_length();
	void display_lst(event_notice* &cur);
	event_notice** return_peek();
//	void export_event_list(event_notice* &cur, ofstream &o_file);
	string return_fel_str();
};