#include<iostream>
#include<vector>

using namespace std;

struct people{
	int id;
	int age;
};
vector<people> old, other;

void mergeSort(int l, int r){
	if(l + 1 >= r) return;
	
	vector<people> temp;
	int m = (l + r) / 2;
	mergeSort(l, m);
	mergeSort(m + 1, r);
	
	int left = l;
	int right = m + 1;
	vector<people>::iterator it;
	
	it = temp.begin();
	it = it + left;
	cout << it -> age << endl;
	while(left <= m && right <= r){
		if(old[left].age >= old[right].age){
			*it = old[left++];
			it++;
		}
		else{
			*it = old[right++];
			it++;
		}
	}
	while(left <= m){
		*it = old[left++];
		it++;
	}
	while(right <= r){
		*it = old[right++];
		it++;
	}
	for(int i = l; i <= r; ++i){
		old[i] = temp[i];
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		people p;
		scanf("%d %d", &p.id, &p.age);
		if(p.age >= 60){
			old.push_back(p);
		}
		else{
			other.push_back(p);
		}
	}
	mergeSort(0, old.size() - 1);
	
	vector<people>::iterator it;
	for(it = old.begin(); it != old.end(); ++it){
		printf("%06d %d\n", it -> id, it -> age);
	}
	for(it = other.begin(); it != other.end(); ++it){
		printf("%06d %d\n", it -> id, it -> age);
	}
	return 0;
}