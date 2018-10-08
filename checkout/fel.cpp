#include "Header.h"

event_notice* spawn_event(char e[], int t) {
	event_notice* new_evnt = new event_notice(e, t);
	return new_evnt;
}

event_notice* spawn_event(char e[], int t, char c[]) {
	event_notice* new_evnt = new event_notice(e, t, c);
	return new_evnt;
}

event_notice::event_notice(char evnt_[], float t) {
	strcpy_s(evnt, evnt_);
	time = t;
	right = NULL;
	left = NULL;
}

event_notice::event_notice(char evnt_[], float t, char cli_[]) {
	strcpy_s(evnt, evnt_);
	strcpy_s(cli, cli_);
	time = t;
	right = NULL;
	left = NULL;
}

fel::fel() {
	peek = NULL;
	length = 0;
}

event_notice* fel::get_peek() {
	event_notice *p = peek;
	return p;
}

void fel::pop_peek() {
	peek = peek->right;
	length--;
}

void fel::fel_insert(event_notice *new_ev, event_notice* &cur) {

	if (cur == NULL) {
		cur = new_ev;
		length++;
	}

	else if (new_ev->time < cur->time) {

		event_notice* tmp = cur;
		if (tmp->left != NULL)
			tmp->left->right = new_ev;

		cur = new_ev;
		cur->right = tmp;
		tmp->left = cur;


		length++;



	}

	else if (new_ev->time == cur->time) {

		if (cur->right == NULL) {

			cur->right = new_ev;
			new_ev->left = cur;
			length++;

		}
		else {
			event_notice* tmp = cur->right;

			//fel_insert(new_ev, cur->right);

			cur->right = new_ev;
			new_ev->left = cur;

			new_ev->right = tmp;
			tmp->left = new_ev;
			length++;

		}

	}

	else {

		fel_insert(new_ev, cur->right);
		if (cur->right == new_ev)
		{
			new_ev->left = cur;
		}
	}

}

void fel::delete_evnt(event_notice *trgt, event_notice* &cur) {
	if (cur->evnt == trgt->evnt && cur->time == trgt->time) {

		if (cur->left == NULL) {

			peek = cur->right;
			length--;

		}
		else {

			event_notice* tmp = cur->left;
			cur->left->right = cur->right;
			cur->right->left = tmp;
			length--;
		}
	}
}

event_notice* fel::get_next() {
	if (peek != NULL) {

		event_notice *tmp;
		tmp = peek;
		peek = peek->right;
		length--;
		return tmp;

	}
	return NULL;
}

event_notice** fel::return_peek() {
	return &peek;
}

int fel::get_length() {

	return length;

}

void fel::display_lst(event_notice* &cur) {

	if (cur->right == NULL) {
		cout << "(" << cur->evnt << ", " << cur->time << ")";
	}
	else {
		cout << "(" << cur->evnt << ", " << cur->time << "),";
		display_lst(cur->right);
	}
}

//void fel::export_event_list(event_notice* &cur, ofstream &o_file) {
//	if (cur->right == NULL) {
//		o_file << "(" << cur->evnt << ", " << cur->time << ")";
//	}
//	else {
//		o_file << "(" << cur->evnt << ", " << cur->time << "),";
//		export_event_list(cur->right, o_file);
//	}
//}

string fel::return_fel_str() {
	char bf[256];
	
	string str = "";
	event_notice *tmp = peek;
	while (tmp != NULL) {
		sprintf_s(bf, "(%s,%f) ", tmp->
			evnt, tmp->time);
		str += bf;
		tmp = tmp->right;
	}

	return str;

}